#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere : public Object3D
{
public:
	Sphere() {
		//unit ball at the center
		center = Vector3f::ZERO;
		radius = 0;
	}
	Sphere(Vector3f center, float radius, Material* material) :Object3D(material) {
		Sphere::center = center;
		Sphere::radius = radius;
	}
	~Sphere() {}


	virtual bool intersect(const Ray& r, Hit& h, float tmin) {			//��

		float a = Vector3f::dot(r.getDirection(),r.getDirection());		// r.getDirection() *r.getDirection();										//ϵ��a
		float b = 2 * Vector3f::dot(r.getDirection(), (r.getOrigin() - center));						//ϵ��b��ע���������겻һ��ʱԭ��
		float c = Vector3f::dot((r.getOrigin() - center), (r.getOrigin() - center)) - radius* radius;	//ϵ��c
		float delta = b*b - 4 * a*c;																	//�б�ʽ
		
		if (delta<0) {								//�б�ʽС��0���޽���
			return false;
		}
		else if (delta == 0) {						//�б�ʽ����0����һ������
			float t = -b / (2 * a);					
			if (t >= tmin) {
				return set_hit_t(h, t, r);
				//return true;
			}
			else {
				return false;
			}
		}
		else {										//�б�ʽ����0������������
			float d = sqrt(delta);					//
			float t_plus = (-b + d) / (2 * a);		//t1
			float t_minus = (-b - d) / (2 * a);		//t2

			if (t_minus >= tmin) {					//����t������tmin
				return set_hit_t(h, t_minus, r);			//ֻȡ��С��t
				//return true;
			}
			else {									//tmin<��С��t
				if (t_plus >= tmin) {				//�ϴ��t����tmin
					return set_hit_t(h, t_plus, r);
					//return true;
				}
				else {								//�ϴ��tС��tmin���޽��㡣
					return false;
				}
			}
		}
	}

	bool set_hit_t(Hit& h, float t, Ray r) {								//����hit�����t
		if (t < h.getT()) {													//�����ǰhit�ڵ�t����Ҫ���µ�t
			Vector3f intersection = r.pointAtParameter(t);	//�������꣬���ݹ�ʽ�ó�
			Vector3f normal = intersection - center;						//������
			normal.normalize();

			h.set(t, material, normal);
			return true;
		}
		return false;
	}

protected:
	Vector3f center;		//����
	float radius;			//��뾶

};


#endif
