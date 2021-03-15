#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>
using namespace std;
float clampedDepth ( float depthInput, float depthMin , float depthMax);
#include "bitmap_image.hpp"




void drawPicture(SceneParser* scene_parser,int Width,int Height,char *output_file_name) {
	int width = Width;											//��Ļ���
	int height = Height;										//��Ļ�߶�
	Vector3f ambient_light = scene_parser->getAmbientLight();	//��������
	int light_number = scene_parser->getNumLights();			//��Դ����
	Light **lights = new Light*[light_number];					//��Դ
	for (int i = 0; i < light_number; i++) {					//���ù�Դ
		lights[i] = scene_parser->getLight(i);
	}
	Camera *camera = scene_parser->getCamera();					//͸��ͶӰ���
	float tmin = camera->getTMin();								//����t����Сֵ
	Image image(width, height);									//����ͼƬ
	
	for (int i = 0; i < width; i++) {														//����ÿ�����ص�
		for (int j = 0; j < height; j++) {
			Vector2f position((float)i / (float)width, (float)j / (float)height);			//��߷ֱ���ռ����
			Ray ray = camera->generateRay(position);										//��ʼ����

			Hit hit;																		//��ʼ����
			bool result = scene_parser->getGroup()->intersect(ray, hit, tmin);				//��
			Vector3f current_color = Vector3f::ZERO;										//��ǰ������ɫ
			if (result) {																	//�н��㣬���ơ�			
				current_color += ambient_light;												//���ϻ�����

				Vector3f intersection = ray.pointAtParameter(hit.getT());	//����
				Vector3f direction_to_light;
				Vector3f light_color;
				float distance_to_light_source;
				for (int k = 0; k < light_number; k++) {
					lights[k]->getIllumination(intersection, direction_to_light, light_color, distance_to_light_source);
					current_color+=hit.getMaterial()->Shade(ray, hit, direction_to_light, light_color);
				}
				//current_color += hit.getMaterial()->getDiffuseColor();
				//current_color.print();
				image.SetPixel(i, j, current_color);
			}
			else {
				current_color += ambient_light;
				image.SetPixel(i, j, scene_parser->getBackgroundColor());
			}
		}
	}

	string file_name = output_file_name;

	file_name = "Result_Picture/" + file_name;
	cout << file_name << endl;
	const char* const_file_name = file_name.c_str();
	image.SaveImage(const_file_name);
	//image.SaveImage("Result_Picture/result.bmp");

	cout << "Draw Picture finish!" << endl;
}



int main( int argc, char* argv[] )
{
	// Fill in your implementation here.
	// This loop loops over each of the input arguments.
	// argNum is initialized to 1 because the first
	// "argument" provided to the program is actually the
	// name of the executable (in our case, "a4").
	
	
	SceneParser* scene_parser;
	int width = 0;
	int height = 0;
	char *file_name;
	char *output_file_name;
	for (int argNum = 1; argNum < argc; ++argNum)
	{
		std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
		if (!strcmp(argv[argNum], "-input") && argNum + 1 < argc) {
			scene_parser = new SceneParser(argv[argNum + 1]);
			file_name = argv[argNum + 1];
		}
		if (!strcmp(argv[argNum], "-size") && argNum + 2< argc) {
			width = atoi(argv[argNum + 1]);
			height = atoi(argv[argNum + 2]);
		}
		if (!strcmp(argv[argNum], "-output") && argNum + 1 < argc) {
			output_file_name= argv[argNum + 1];
		}
	}
	cout << endl<< "width: " << width <<","<<"height: " << height<<","<< "file name: " << file_name << endl<<endl;
	
	// First, parse the scene using SceneParser.
	// Then loop over each pixel in the image, shooting a ray
	// through that pixel and finding its intersection with
	// the scene.  Write the color at the intersection to that
	// pixel in your output image.
	drawPicture(scene_parser, width, height, output_file_name);
	

	
	return 0;
}



//-----------------------------------------------------------
/*float radius = 1;

Vector3f d_color(0.1,0.1,0.1);
Vector3f s_color(0.3,0.3,0.3);
float s = 25;

Material* material = new Material(d_color, s_color,s);
Sphere sphere(Vector3f(-1, -1, -1), radius,material);
Sphere sphere2(Vector3f(0.,0.,0.), radius, material);
Hit h;
Vector3f d(-1, -1, -1);
d.normalize();
Ray ray(Vector3f(1,1,1),d);

bool result=sphere.intersect(ray, h,0);
result= sphere2.intersect(ray, h, 0);
if (result) {
cout<<"T:"<<h.getT();
}*/
//-----------------------------------------------------------
///TODO: below demonstrates how to use the provided Image class
///Should be removed when you start

//Vector3f pixelColor (1.0f,0,0);
//width and height
/*Image image( 10 , 15 );
image.SetPixel( 5,5, pixelColor );
image.SaveImage("test_1.bmp");*/