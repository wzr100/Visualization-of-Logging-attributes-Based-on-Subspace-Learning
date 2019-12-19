#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>				
#include <osg/Geometry>
#include <osgUtil/Optimizer>
#include <osg/LineWidth>
#include <osg/BoundingBox>
#include <osg/ComputeBoundsVisitor>


#include <iostream>
#include <cstring>
#include "segy.h"
#include <windows.h>
#include <time.h>

using namespace std;

/*#define GLSL400(src) "#version 400\n" #src

const char* vertSource1 = GLSL400 (
uniform mat4 ModelViewProjectionMatrix;
uniform float maxValue;
layout(location = 0) in vec4 Vertex;
layout(location = 1) in float intense;
out vec4 pixColor; 
void main(void)
{
	gl_Position = ModelViewProjectionMatrix * Vertex;
	float tmp = step(0,intense);
	pixColor = vec4(1.0-intense/maxValue*tmp,1-intense/maxValue*(2*tmp-1),1.0-intense/maxValue*(tmp-1),1.0);
}
);

//fragment shader中的解释说明

//	if (intense>0)
//	{
//		pixColor = vec4(1.0-intense/maxValue, 1-intense/maxValue, 1.0,                1.0); //颜色在白色与蓝色间
//	}
//	else
//	{
//		pixColor = vec4(1.0,                  1+intense/maxValue, 1+intense/maxValue, 1.0); //颜色在白色与红色间
//	}

const char* fragSource1 = GLSL400(
	in vec4 pixColor;
void main(void)
{
	gl_FragColor = pixColor;
}
);*/

/*
struct ModelViewProjectionMatrixCallback:public osg::Uniform::Callback{
	ModelViewProjectionMatrixCallback(osg::Camera* camera):_camera(camera){}
	virtual void operator()(osg::Uniform* uniform, osg::NodeVisitor* nv) {
		osg::Matrixd viewMatrix = _camera->getViewMatrix();
		osg::Matrixd modelMatrix = osg::computeLocalToWorld(nv->getNodePath());
		osg::Matrixd modelViewProjectionMatrix = modelMatrix * viewMatrix * _camera->getProjectionMatrix();
		uniform->set(modelViewProjectionMatrix);
	}

	osg::Camera* _camera;
};*/


osg::ref_ptr<osg::Node> cretateBoundingBox(osg::Node * node)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	geode->addDrawable(geom);
	osg::ComputeBoundsVisitor boundVisitor;
	node->accept(boundVisitor);
	osg::BoundingBox boundingBox = boundVisitor.getBoundingBox();
	cout<<boundingBox.xMax()<<endl;
	cout<<boundingBox.zMax()<<endl;
	float length = boundingBox.xMax() - boundingBox.xMin();
	float width = boundingBox.yMax() - boundingBox.yMin();
	float height = boundingBox.zMax() - boundingBox.zMin();
	//cout<<"length:"<<length<<endl;
	//cout<<"width:"<<width<<endl;
	//cout<<"height:"<<height<<endl;

	osg::Vec3Array* vertices = new osg::Vec3Array;
	osg::Vec4Array* colors = new osg::Vec4Array;
	vertices->setName("Vertex");
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMin(),boundingBox.zMin()));
	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMin(),boundingBox.zMin()));

	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMin(),boundingBox.zMin()));
	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMax(),boundingBox.zMin()));

	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMax(),boundingBox.zMin()));
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMax(),boundingBox.zMin()));

	
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMax(),boundingBox.zMin()));
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMin(),boundingBox.zMin()));

	//上面
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMin(),boundingBox.zMax()));
	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMin(),boundingBox.zMax()));

	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMin(),boundingBox.zMax()));
	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMax(),boundingBox.zMax()));

	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMax(),boundingBox.zMax()));
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMax(),boundingBox.zMax()));

	
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMax(),boundingBox.zMax()));
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMin(),boundingBox.zMax()));

	//上下
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMin(),boundingBox.zMin()));
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMin(),boundingBox.zMax()));

	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMin(),boundingBox.zMin()));
	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMin(),boundingBox.zMax()));

	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMax(),boundingBox.zMin()));
	vertices->push_back(osg::Vec3f(boundingBox.xMax(),boundingBox.yMax(),boundingBox.zMax()));

	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMax(),boundingBox.zMin()));
	vertices->push_back(osg::Vec3f(boundingBox.xMin(),boundingBox.yMax(),boundingBox.zMax()));

	colors->setName("Color");
	colors->push_back(osg::Vec4f(1.0f,1.0f,1.0f,1.0f));

    // defaults
    geom->setVertexArray(vertices);
	geom->setColorArray(colors, osg::Array::BIND_OVERALL);

    // set attributes
    geom->setVertexAttribArray(0, vertices, osg::Array::BIND_PER_VERTEX);
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,2,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,4,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,6,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,8,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,10,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,12,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,14,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,16,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,18,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,20,2));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,22,2));	
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;
	stateset = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::LineWidth> linewidth = new osg::LineWidth(0.001);
	stateset->setAttribute(linewidth);
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	return geode;
}

segy RunSegy()
{
	segy sgy;
	string fName = "C://Users//18810//Desktop//AcGanData//";
	sgy.ReadAllTrace(fName);                        //测井数据读入vector中  -> intensity [float]
	sgy.readFaceData();									 //读入体素的位置坐标  -> data  [float,float,float]
	sgy.setUnitGeom(sgy.geom);                  // 将需要绘制成图元的体素在intensity中的坐标存在base中
	sgy.setShader(sgy.geom,sgy.camera,sgy.intensity, vertSource2);		//添加数据，设置shader
	return sgy;
}

/*
压力测试	
*/
void MmTest()
{
	int Length1=1024*1024*1024;
	int Length2=Length1/2;
	//int Length3=Length1/4;
	//int Length4=Length1/8;
	//char* buf1 = new char[Length1];
	char* buf2 = new char[Length2];
	//char* buf3 = new char[Length3];
	//char* buf4 = new char[Length4];
}

int main( int argc, char** argv )
{
	clock_t start;
	start  = clock();
	MmTest();
	
	segy sgy = RunSegy();                                  //初始化操作，设置模型场景结果，准备geom数据

	sgy.root->addChild(sgy.geom.get());
	sgy.root->addChild(cretateBoundingBox(sgy.geom));
	osgUtil::Optimizer optimzer;
	optimzer.optimize(sgy.root);
	sgy.viewer->setSceneData(sgy.root.get());
	sgy.viewer->realize();
	osg::ref_ptr<KeyboardHandler> hand = new KeyboardHandler(sgy);
	sgy.viewer->addEventHandler(hand);          //时间响应
	sgy.viewer->run();
	//cout<<"1"<<endl;
	cout<<clock()-start<<"ms"<<endl;
}