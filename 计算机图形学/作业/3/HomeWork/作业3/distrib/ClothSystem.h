#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vecmath.h>
#include <vector>
#ifdef _WIN32
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include "particleSystem.h"
#include<iostream>

class ClothSystem: public ParticleSystem
{
///ADD MORE FUNCTION AND FIELDS HERE
public:
	ClothSystem(int numParticles);
	vector<Vector3f> evalF(vector<Vector3f> state);
	void draw();


	//-------������Ħ����ײ-------
	void setState(const vector<Vector3f>  & newState) {
		Vector3f centre(-1, -2, 0);
		Vector3f Epsilon(0.03, 0.03, 0.03);
		Vector3f direction;
		for (int i = 0; i < number; i++) {
			for (int j = 0; j < number; j++) {
				int N = i * number + j;
				direction = newState[N * 2] - centre;
				if (direction.abs() < 1.03) {
					direction.normalize();
					direction += centre;
					m_vVecState[N * 2] = direction + Epsilon;	
					m_vVecState[N * 2 + 1] = newState[N * 2 + 1];
				}
				else {
					m_vVecState[N * 2] = newState[N * 2];
					m_vVecState[N * 2 + 1] = newState[N * 2 + 1];
				}	
				
			}
		}
	}

	//----�滭�任---
	int spring_type;
	void set_spring_type() {
		spring_type += 1;
		spring_type %= 5;
	};
	//----�����任----
	bool wind;
	void set_wind() {
		wind = !wind;
	};

	//----�����ק-------
	void set_drag_point(int fixed_x, int fixed_y, Matrix4f m, Matrix4f rotate, Vector3f transform);  //������ק�㣬ͶӰ��ѡȡģʽ
	void move_drag_point(int x, int y, Matrix4f m, Matrix4f rotate);								 //�ƶ������µ�����
	void release_drag_point() { current_point_index = -1; };										 //�ͷ���ק��
	Matrix4f m_m;			//look_at����
	Matrix4f m_rotate;		//��ת����
	Vector3f transform;		//ƽ�ƾ���
	int fixed_x;			//�̶�������x
	int fixed_y;			//�̶�������y
	int current_point_index;//��ǰѡ�еĵ�
	vector<Vector3f> colors;//���е���ɫ



private:
	int number;											//���ɹ�ģ����ĸ���Ϊnumber*number���ñ�����ҪΪ������㡣
	vector<vector<Vector3f>> spring_connect;			//�ṹ����
	vector<vector<Vector3f>> spring_anti_shearing;		//��������
	vector<vector<Vector3f>> spring_anti_bending;		//���䵯��
	//-----��������-------
	float gap_position;
	float gap_connect;
	float gap_anti_shear;
	float gap_anti_bend;
	float k_connect;
	float k_anti_shear;
	float k_anti_bend;
	float k_resistance;
	float gravity;
	//---�滭----
	void draw_connect();
	void draw_anti_shearing();
	void draw_anti_bending();
	void draw_faces();
	
	//-----�㷨��������---------
	Vector3f ***face_normal;									//�洢�淨����
	Vector3f GetPointNormal(int i, int j);						//�õ�ĳλ���淨����
	Vector3f GetNormal(Vector3f v1, Vector3f v2, Vector3f v3);	//�����淨����
	
	//------ҡ��------
	float step;			 //ҡ�ڼ���
	float sum_velocity;  //ҡ����
	
};


#endif
