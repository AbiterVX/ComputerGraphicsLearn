#include"triangle_mesh.h"
#include"vectors.h"

class Spline {
public:
	Spline() {}
	//--���ڻ�ͼ��FOR VISUALIZATION
	virtual void Paint(ArgParser *args) {}
	//--����ʵ����������ת����FOR CONVERTING BETWEEN SPLINE TYPES
	virtual void OutputBezier(FILE *file) {}
	virtual void OutputBSpline(FILE *file) {}
	//--���ڵõ����Ƶ��FOR CONTROL POINT PICKING
	virtual int getNumVertices() { return 0; }
	virtual Vec3f getVertex(int i)
	{
		Vec3f v;
		return v;
	};
	//--���ڱ༭������FOR EDITING OPERATIONS
	virtual void moveControlPoint(int selectedPoint, float x, float y) { cout << "moveControlPoint" << endl; }
	virtual void addControlPoint(int selectedPoint, float x, float y) { cout << "addControlPoint" << endl; }
	virtual void deleteControlPoint(int selectedPoint) { cout << "deleteControlPoint" << endl; }
	//--���ڲ��������ε�FOR GENERATING TRIANGLES
	virtual TriangleMesh* OutputTriangles(ArgParser *args) 
	{
		TriangleMesh *t=new TriangleMesh(1,1);
		return t;
	}
};
