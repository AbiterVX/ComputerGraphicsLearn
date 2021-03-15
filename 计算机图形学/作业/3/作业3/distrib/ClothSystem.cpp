#include "ClothSystem.h"
#include"math.h"
#include<iostream>
//TODO: Initialize here

#define M_PI 3.14159265358979f

ClothSystem::ClothSystem(int numParticles)
{
	m_numParticles = numParticles* numParticles;
	number = numParticles;
	//----���ɻ���ϵ��----
	gap_position = 0.25;
	gap_connect = 0.25;
	gap_anti_shear = 0.25*sqrt((double)2);
	gap_anti_bend = 0.25*2;
	k_connect = 35;
	k_anti_shear = 30;
	k_anti_bend = 10;
	k_resistance = 0.8;
	gravity= 0.15*9.8;

	//-----�ڶ�----
	swing=0;
	step = 0.05;
	sum_velocity = 0;
	//----���޷���
	wind = 0;
	
	//------���գ��淨������ʼ��-------
	face_normal = new Vector3f**[number];
	for (int i = 0; i < number; i++) {
		face_normal[i] = new Vector3f*[number];
		for (int j = 0; j < number; j++) {
			face_normal[i][j] = new Vector3f[2];
		}
	}
	//------�����ק���������е���ɫ------
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			Vector3f current_color(0, 0.5, 0.9);
			colors.push_back(current_color);
		}
	}
	//-----�����ק����ǰ�㣬��ǰlookat����-----
	current_point_index = -1;
	m_m = Matrix4f::identity();


	//-----��ʼ�����ĵ��뵯�ɣ��ٶȵ�---------
	for (int i = 0; i < number;i++) {
		for (int j = 0; j < number;j++) {
			//Vector3f position(i*gap_position,-j*gap_position,0);
			Vector3f position(i*gap_position,0, j * gap_position);
			Vector3f velocity(0,0,0);
			m_vVecState.push_back(position);
			m_vVecState.push_back(velocity);

			vector<Vector3f> new_spring_connect;
			if (i>0) {
				int N = (i-1) * number + j;
				Vector3f spring_attribute(N, k_connect, gap_connect);
				new_spring_connect.push_back(spring_attribute);
			}
			if (i< number -1) {
				int N = (i+1) * number +j;
				Vector3f spring_attribute(N, k_connect, gap_connect);
				new_spring_connect.push_back(spring_attribute);
			}
			if (j>0) {
				int N = i * number + j-1;
				Vector3f spring_attribute(N, k_connect, gap_connect);
				new_spring_connect.push_back(spring_attribute);
			}
			if (j< number -1) {
				int N = i * number + j+1;
				Vector3f spring_attribute(N, k_connect, gap_connect);
				new_spring_connect.push_back(spring_attribute);
			}
			spring_connect.push_back(new_spring_connect);

			//----------------------------
			vector<Vector3f> new_anti_shearing;
			if (i>0 && j>0) {			
				int N = (i-1) * number + j - 1;
				Vector3f spring_attribute(N, k_anti_shear, gap_anti_shear);
				new_anti_shearing.push_back(spring_attribute);
			}
			if (i< number -1 && j< number -1) {
				int N = (i + 1) * number + j + 1;
				//cout <<i<<j<<":"<< N << endl;
				Vector3f spring_attribute(N, k_anti_shear, gap_anti_shear);
				new_anti_shearing.push_back(spring_attribute);
			}
			if (i>0 && j< number - 1) {
				int N = (i - 1) * number + j + 1;
				Vector3f spring_attribute(N, k_anti_shear, gap_anti_shear);
				new_anti_shearing.push_back(spring_attribute);
			}
			if (i< number - 1 && j>0) {
				int N = (i + 1) * number + j - 1;
				Vector3f spring_attribute(N, k_anti_shear, gap_anti_shear);
				new_anti_shearing.push_back(spring_attribute);
			}
			spring_anti_shearing.push_back(new_anti_shearing);

			//----------------------------
			
			vector<Vector3f> new_anti_bending;
			if (i - 2 >= 0) {
				int N = (i - 2) * number + j;
				Vector3f spring_attribute(N, k_anti_bend, gap_anti_bend);
				new_anti_bending.push_back(spring_attribute);
			}
			if (i + 2 <= number - 1) {
				int N = (i + 2) * number + j;
				Vector3f spring_attribute(N, k_anti_bend, gap_anti_bend);
				new_anti_bending.push_back(spring_attribute);
			}
			if (j - 2 >= 0) {
				int N = i * number + j - 2;
				Vector3f spring_attribute(N, k_anti_bend, gap_anti_bend);
				new_anti_bending.push_back(spring_attribute);
			}
			if (j + 2 <= number - 1) {
				int N = i * number + j + 2;
				Vector3f spring_attribute(N, k_anti_bend, gap_anti_bend);
				new_anti_bending.push_back(spring_attribute);
			}
			spring_anti_bending.push_back(new_anti_bending);
		}
	}

}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	Vector3f gravity(0, -gravity, 0);
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			Vector3f sum_f(0, 0, 0);
			Vector3f velocity(0, 0, 0);
			int N = i * number + j;
			if (wind) {
				Vector3f wind_f(0,0,-2);
				sum_f += wind_f;
			}
			if ( (i== 0 && j==0) || (i== number - 1 &&j== 0) ) {
				if (swing) {
					if (sum_velocity > 1.5) {
						step = -0.005;
					}
					else if (sum_velocity < -1.5) {
						step = 0.005;
					}
					sum_velocity += step;
					Vector3f v(0, 0, sum_velocity);
					velocity = v;
				}				
			}
			else {
				sum_f = sum_f + gravity;
				for (int connect = 0; connect < spring_connect[N].size(); connect++) {
					Vector3f distance = state[N * 2] - state[spring_connect[N][connect].x() * 2];
					float d = distance.abs();
					sum_f = sum_f + (-spring_connect[N][connect].y()*(d - spring_connect[N][connect].z()) * distance / d);					
				}
				for (int shearing = 0; shearing < spring_anti_shearing[N].size(); shearing++) {
					Vector3f distance = state[N * 2] - state[spring_anti_shearing[N][shearing].x() * 2];
					float d = distance.abs();
					sum_f = sum_f + (-spring_anti_shearing[N][shearing].y()*(d - spring_anti_shearing[N][shearing].z()) * distance / d);
				}
				for (int bending = 0; bending < spring_anti_bending[N].size(); bending++) {
					Vector3f distance = state[N * 2] - state[spring_anti_bending[N][bending].x() * 2];
					float d = distance.abs();
					sum_f = sum_f + (-spring_anti_bending[N][bending].y()*(d - spring_anti_bending[N][bending].z()) * distance / d);
				}

				sum_f = sum_f + (-k_resistance *state[N * 2 + 1]);
				velocity = state[N * 2 + 1];
			}
			
			f.push_back(velocity);
			f.push_back(sum_f);
		}
	}
		
	return f;	
}

///TODO: render the system (ie draw the particles)
void ClothSystem::draw()
{
	if (spring_type%5==0) {
		draw_faces();
	}
	else if (spring_type % 5 ==1) {
		draw_connect();
	}
	else if (spring_type % 5 ==2) {
		draw_anti_shearing();
	}
	else if (spring_type % 5 ==3) {
		draw_anti_bending();
	}
	else if (spring_type % 5 == 4) {
		for (int i = 0; i < number; i++) {
			for (int j = 0; j < number; j++) {
				int N = i * number + j;
				Vector3f pos = m_vVecState[N * 2];
				glPushMatrix();
				glTranslatef(pos[0], pos[1], pos[2]);
				glutSolidSphere(0.055f, 10.0f, 10.0f);
				glPopMatrix();
			}
		}
	}
	
	glPushMatrix();	
	glEnable(GL_COLOR_MATERIAL);	
	glPushMatrix();
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			int N = i * number + j;
			Vector3f pos = m_vVecState[N * 2];
			glPushMatrix();
			glColor3f(colors[N].x(), colors[N].y(), colors[N].z());
			glTranslatef(pos[0], pos[1], pos[2]);
			if ((i == 0 && j == 0) || (i == number - 1 && j == 0)) {
				glutSolidSphere(0.075f, 10.0f, 10.0f);				
			}			
			if (colors[N].x()==1) {
				glutSolidSphere(0.075f, 10.0f, 10.0f);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
	glTranslatef(-1, -2, 0);
	glColor3f(1.0,1.0,0);
	glutSolidSphere(1.0f, 20.0f, 20.0f);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
//-----------�����ק-------------
void ClothSystem::move_drag_point(int x, int y, Matrix4f m, Matrix4f rotate) {
	if (current_point_index!=-1) {
		//for (int i = 0; i < hits; i++) {		
		if (m_vVecState[current_point_index * 2]== Vector3f::ZERO) {
			m_vVecState[current_point_index * 2][0] = 0.00001;
			m_vVecState[current_point_index * 2][2] = 0;
		}
		Vector3f horizontal(1,0,0);
		horizontal = rotate.getSubmatrix3x3(0, 0).inverse()*horizontal;
		/*Vector3f horizontal = rotate.getSubmatrix3x3(0,0).inverse() *m_vVecState[current_point_index * 2];
		horizontal[1] = 0;
		if (horizontal[0]<0) {
			horizontal[0] = -horizontal[0];
		}
		if (horizontal[2]<0) {
			horizontal[2] = -horizontal[2];
		}
		horizontal.normalize();*/

		Vector3f vertical(0, -1, 0);
		m_vVecState[current_point_index * 2] += horizontal * (x - fixed_x)*0.005 + vertical * (y - fixed_y)*0.005;
		fixed_x = x;
		fixed_y = y;			
	}
	m_m = m;
	m_rotate = rotate;
}
void ClothSystem::set_drag_point(int fixed_x,int fixed_y,Matrix4f m, Matrix4f rotate, Vector3f transform) {
	m_m =m ;
	m_rotate = rotate;
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			int N = i * number + j;
			Vector3f current_color(0, 0.5, 0.9);
			colors[N]=current_color;
		}
	}

	GLuint selectBuff[5*1];		//����һ������ѡ���������� 
	GLint hits;					//�����¼�ĸ���
	GLint viewport[4];          //�ӿ�

	glGetIntegerv(GL_VIEWPORT, viewport);	//����ӿ�

	glSelectBuffer(5, selectBuff);			//ָ���洢�����¼������
	glRenderMode(GL_SELECT);				//����ѡ��ģʽ
	   
	glInitNames();					//��ʼ������ջ 
	glPushName(0);					//������ջ�з���һ����ʼ�����֣�����Ϊ��0�� 

	
	glMatrixMode(GL_PROJECTION);			//����ͶӰ�׶�׼��ʰȡ    		
	glPushMatrix();							//������ǰ��ͶӰ���� 	 
	glLoadIdentity();						//���뵥λ���� 
		
	//������ѡ������ѡ���������������(x,viewport[3]-y)����С��(8,8)
	gluPickMatrix((GLdouble)fixed_x, (GLdouble)(viewport[3] - fixed_y), 8, 8, viewport);
	//ͶӰ
	//gluLookAt(asd);
	//glOrtho(-5,5,-5,5,0,100);
	//gluPerspective(5 * M_PI / 180.f ,1.0, 0.1f, 100.f);
	//glMultMatrixf(m.inverse());
	gluPerspective(50.0f, (GLfloat)(viewport[2] - viewport[0]) / (GLfloat)(viewport[3] - viewport[1]), 0.1f, 1000.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
	glTranslatef(transform[0], transform[1], transform[2]);

	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			int N = i * number + j;
			Vector3f pos = m_vVecState[N * 2];
			glPushName(N);
			glPushMatrix();	
			glTranslatef(pos[0], pos[1], pos[2]);			
			glutSolidSphere(0.075f, 10.0f, 10.0f);
			glPopMatrix();
			glPopName();

		}
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	hits = glRenderMode(GL_RENDER);  //�˳�ʰȡģʽ�����ص�ĸ���

	//for (int i = 0; i < hits; i++) {
	Vector3f red(1.0, 0, 0);
	if (hits==1) {
		current_point_index = selectBuff[4];
		colors[current_point_index] = red;
		ClothSystem::fixed_x = fixed_x;
		ClothSystem::fixed_y = fixed_y;
	}
	else {
		current_point_index = -1;
	}
	glutPostRedisplay();
	//printf("hits = %d\n", hits);		//���һ�������ĵ���ĸ���
}
//-----------�滭��ͬ����----------
void ClothSystem::draw_connect() {
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			int N = i * number + j;
			for (int connect = 0; connect < spring_connect[N].size(); connect++) {
				glVertex3f(	m_vVecState[N * 2].x(),
							m_vVecState[N * 2].y(), 
							m_vVecState[N * 2].z());
				glVertex3f(	m_vVecState[spring_connect[N][connect].x() * 2].x(),
							m_vVecState[spring_connect[N][connect].x() * 2].y(),
							m_vVecState[spring_connect[N][connect].x() * 2].z() );								
			}
		}
	}
	glEnd();
}
void ClothSystem::draw_anti_shearing() {
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0, 1.0, 0.0);
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			int N = i * number + j;
			for (int shearing = 0; shearing < spring_anti_shearing[N].size(); shearing++){
				glVertex3f(m_vVecState[N * 2].x(),
					m_vVecState[N * 2].y(),
					m_vVecState[N * 2].z());
				glVertex3f(m_vVecState[spring_anti_shearing[N][shearing].x() * 2].x(),
					m_vVecState[spring_anti_shearing[N][shearing].x() * 2].y(),
					m_vVecState[spring_anti_shearing[N][shearing].x() * 2].z());				
			}
		}
	}
	glEnd();
}
void ClothSystem::draw_anti_bending() {
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0, 0.0, 1.0);
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			int N = i * number + j;
			for (int bending = 0; bending < spring_anti_bending[N].size(); bending++) {
				glVertex3f(m_vVecState[N * 2].x(),
					m_vVecState[N * 2].y(),
					m_vVecState[N * 2].z());
				glVertex3f(m_vVecState[spring_anti_bending[N][bending].x() * 2].x(),
					m_vVecState[spring_anti_bending[N][bending].x() * 2].y(),
					m_vVecState[spring_anti_bending[N][bending].x() * 2].z());
			}
		}
	}
	glEnd();
}
Vector3f ClothSystem::GetNormal(Vector3f v1, Vector3f v2, Vector3f v3) {
	Vector3f edge1 = v2-v1;
	Vector3f edge2 = v3-v1;
	edge1.normalize();
	edge2.normalize();
	return Vector3f::cross(edge1, edge2);
}
Vector3f ClothSystem::GetPointNormal(int i,int j) {
	Vector3f Normal(0,0,0);
	if (i>0 && j>0) {				//����
		Normal = Normal + face_normal[i-1][j-1][0] + face_normal[i-1][j-1][1];
	}
	if (i< number &&j< number) {	//����
		Normal = Normal + face_normal[i][j][0] + face_normal[i][j][1];
	}
	if (i>0 && j<number ) {			//����
		Normal = Normal + face_normal[i-1][j][1];
	}
	if (i<number && j>0) {			//����
		Normal = Normal + face_normal[i][j-1][0];
	}
	Normal.normalize();
	return Normal;
}
void ClothSystem::draw_faces() {
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < number - 1; i++) {
		for (int j = 0; j < number - 1; j++) {
			int N = i * number + j;
			int N_next_row = (i + 1) * number + j;

			Vector3f Normal_1 = GetNormal(m_vVecState[N * 2], m_vVecState[(N + 1) * 2], m_vVecState[(N_next_row + 1) * 2]);			
			Vector3f Normal_2 = GetNormal(m_vVecState[N * 2], m_vVecState[(N_next_row + 1) * 2], m_vVecState[N_next_row * 2]);			

			face_normal[i][j][0] = Normal_1;
			face_normal[i][j][1] = Normal_2;
		}
	}
	for (int i = 0; i < number-1; i++) {
		for (int j = 0; j < number-1; j++) {
			int N = i * number + j;
			int N_next_row= (i + 1) * number + j;
		
			//--------------ǰ 0
			Vector3f Normal_1=GetPointNormal(i,j);
			glNormal3f(Normal_1.x(), Normal_1.y(), Normal_1.z());
			glVertex3f(m_vVecState[N * 2].x(), m_vVecState[N * 2].y(), m_vVecState[N * 2].z());

			Vector3f Normal_2 = GetPointNormal(i, j+1);
			glNormal3f(Normal_2.x(), Normal_2.y(), Normal_2.z());
			glVertex3f(m_vVecState[(N + 1) * 2].x(), m_vVecState[(N + 1) * 2].y(), m_vVecState[(N + 1) * 2].z());

			Vector3f Normal_3 = GetPointNormal(i+1, j+1);
			glNormal3f(Normal_3.x(), Normal_3.y(), Normal_3.z());
			glVertex3f(m_vVecState[(N_next_row + 1) * 2].x(), m_vVecState[(N_next_row + 1) * 2].y(), m_vVecState[(N_next_row + 1) * 2].z());		
			//-------------��0
			glNormal3f(-Normal_1.x(), -Normal_1.y(), -Normal_1.z());
			glVertex3f(m_vVecState[N * 2].x(), m_vVecState[N * 2].y(), m_vVecState[N * 2].z());
			
			glNormal3f(-Normal_3.x(), -Normal_3.y(), -Normal_3.z());			
			glVertex3f(m_vVecState[(N_next_row + 1) * 2].x(), m_vVecState[(N_next_row + 1) * 2].y(), m_vVecState[(N_next_row + 1) * 2].z());
			
			glNormal3f(-Normal_2.x(), -Normal_2.y(), -Normal_2.z());
			glVertex3f(m_vVecState[(N + 1) * 2].x(), m_vVecState[(N + 1) * 2].y(), m_vVecState[(N + 1) * 2].z());			
			//-------------ǰ1			
			Vector3f Normal_4 = GetPointNormal(i, j);
			glNormal3f(Normal_4.x(), Normal_4.y(), Normal_4.z());
			glVertex3f(m_vVecState[N * 2].x(),m_vVecState[N * 2].y(),m_vVecState[N * 2].z());

			Vector3f Normal_5 = GetPointNormal(i + 1, j + 1);
			glNormal3f(Normal_5.x(), Normal_5.y(), Normal_5.z());
			glVertex3f(m_vVecState[(N_next_row + 1) * 2].x(),m_vVecState[(N_next_row + 1) * 2].y(),m_vVecState[(N_next_row + 1) * 2].z());	

			Vector3f Normal_6 = GetPointNormal(i + 1, j);
			glNormal3f(Normal_6.x(), Normal_6.y(), Normal_6.z());
			glVertex3f(m_vVecState[N_next_row * 2].x(),m_vVecState[N_next_row * 2].y(),m_vVecState[N_next_row * 2].z());
			//-------------��1	
			glNormal3f(-Normal_4.x(), -Normal_4.y(), -Normal_4.z());
			glVertex3f(m_vVecState[N * 2].x(), m_vVecState[N * 2].y(), m_vVecState[N * 2].z());

			glNormal3f(-Normal_6.x(), -Normal_6.y(), -Normal_6.z());
			glVertex3f(m_vVecState[N_next_row * 2].x(), m_vVecState[N_next_row * 2].y(), m_vVecState[N_next_row * 2].z());

			glNormal3f(-Normal_5.x(), -Normal_5.y(), -Normal_5.z());
			glVertex3f(m_vVecState[(N_next_row + 1) * 2].x(),m_vVecState[(N_next_row + 1) * 2].y(),m_vVecState[(N_next_row + 1) * 2].z());								
		}
	}
	glEnd();
}