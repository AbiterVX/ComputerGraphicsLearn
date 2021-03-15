#include "RayTracer.h"
#include "Camera.h"
#include "Ray.h"
#include "Hit.h"
#include "Group.h"
#include "Material.h"
#include "Light.h"

#define EPSILON 0.001

//IMPLEMENT THESE FUNCTIONS
//These function definitions are mere suggestions. Change them as you like.
Vector3f mirrorDirection( const Vector3f& normal, const Vector3f& incoming)
{
	Vector3f Vision = incoming.normalized();
	Vector3f Normal = normal.normalized();
	return (Vision - 2 * (Vector3f::dot(Vision, Normal))*Normal);

}
bool transmittedDirection( const Vector3f& normal, const Vector3f& incoming, float index_n, float index_nt, Vector3f& transmitted){
	Vector3f L = -incoming.normalized();
	Vector3f N = normal.normalized();
	float index_nr = index_n / index_nt;
	float delta = 1 - pow(index_nr, 2)*(1 - pow((Vector3f::dot(N, L)), 2));
	if (delta<0) {
		transmitted = Vector3f::ZERO;
		return false;
	}
	else {
		delta = sqrt(delta);
		transmitted = (index_nr * Vector3f::dot(N, L)  - delta)*N-index_nr*L;
		transmitted.normalize();
		return true;
	}
}




RayTracer::RayTracer( SceneParser * scene, int max_bounces) :m_scene(scene){
	group =scene->getGroup();
	m_maxBounces = max_bounces;

	light_number = scene->getNumLights();						//��Դ����
	lights = new Light*[light_number];							//��Դ
	for (int i = 0; i < light_number; i++) {					//���ù�Դ
		lights[i] = scene->getLight(i);
	}
}

RayTracer::~RayTracer(){

}
Vector3f RayTracer::traceRay( Ray& ray, float tmin, int bounces,float refr_index, Hit& hit ) const{
	Vector3f color = Vector3f::ZERO;
	bool intersected = group->intersect(ray, hit, tmin);														//����
	if (intersected) {
		color += hit.getMaterial()->getDiffuseColor()*m_scene->getAmbientLight();
		Vector3f intersection = ray.pointAtParameter(hit.getT());												//����
		
		for (int k = 0; k < light_number; k++) {																//����Ӱ��
			Vector3f direction_to_light;																		//ָ���ķ���
			Vector3f light_color;																				//�����ɫ
			float distance_to_light_source;																		//����ľ���
			lights[k]->getIllumination(intersection, direction_to_light, light_color, distance_to_light_source);//

			Hit new_hit;																						//�����Ƿ��н��㣡��������
			Ray to_light_ray(intersection, direction_to_light);													//ָ���Դ�Ĺ���		
			bool hidden = group->intersect(to_light_ray, new_hit, tmin);										//���Ƿ��ڵ�����Ӱ��
			if (!hidden) {
				color += hit.getMaterial()->Shade(ray, hit, direction_to_light, light_color);					//��ǰ��Դ��������
			}
		}

		bounces++;																								//����һ�η������
		if (bounces <= m_maxBounces) {																			//�ڷ��������Χ��
			Ray reflected_light(intersection, mirrorDirection(hit.getNormal(),ray.getDirection() ));			//�������

			Vector3f reflected_color;		//�������ɫ
			Vector3f transmitted_color;		//�������ɫ
			Vector3f sum_color;				//����ɫ

			Hit new_hit;
			reflected_color = hit.getMaterial()->getSpecularColor()*traceRay(reflected_light, tmin, bounces, refr_index, new_hit);	//���淴��
			//reflected_color = hit.getMaterial()->Shade(reflected_light, hit, reflected_light.getDirection(), color)*color;

			Vector3f ray_direction = ray.getDirection().normalized();		//���߷���,��Դ����ǰ����
			Vector3f N = hit.getNormal().normalized();						//��ǰ���彻��ķ�����
			float d_dot_N = Vector3f::dot(ray_direction, N);					//d���N


			float n = refr_index;											//��ǰ����ϵ��
			float nt = hit.getMaterial()->getRefractionIndex();				//���������������ϵ��

			if (d_dot_N > 0) {												//�ڵ�ǰ������
				N = -N;
				nt = (float)1.0;
			}
			else {															//���ڵ�ǰ������
				nt = hit.getMaterial()->getRefractionIndex();
			}


			if (nt > 0) {																												//��ǰ������������
				Vector3f transmitted_direction;
				bool iftransmitted = transmittedDirection(N, ray_direction, n, nt, transmitted_direction);	//����
				
				if (iftransmitted) {																									//���������
					Ray transmit_ray(intersection, transmitted_direction);	//���������
					Hit new_hit;
					transmitted_color = hit.getMaterial()->getSpecularColor()*traceRay(transmit_ray, tmin, bounces, nt, new_hit);													//������ɫ

					
					float R0 = pow((nt - n) / (nt + n), 2);
					float C;
					if (n <= nt) {
						C = abs(Vector3f::dot(ray_direction, N));
					}
					else {
						C = abs(Vector3f::dot(transmitted_direction, N));
					}
					float R = R0 + (1.0 - R0)*pow((1.0 - C), 5);

					//cout << R << endl;
					sum_color = R * reflected_color + (1.0 - R)*transmitted_color;
					//sum_color = R * transmitted_color+ (1.0 - R)*reflected_color;
					//sum_color=(1.0 - R)*transmitted_color;
					//sum_color = reflected_color;
				}
				else {
					sum_color = reflected_color;															//ȫ����
				}
			}
			else {
				sum_color = reflected_color;																//ȫ����
			}
			
			color += sum_color;
		}	
	}
	else {
		color = m_scene->getBackgroundColor(ray.getDirection());
	}

	return color;
}
