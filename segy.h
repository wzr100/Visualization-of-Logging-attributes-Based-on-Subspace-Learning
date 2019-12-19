#include <iostream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <osg/Geode>
#include <osg/Geometry>
#include<osgGA/GUIEventHandler>
#include <winsock2.h> 
#pragma  comment(lib,"ws2_32.lib")
#include <chrono>

using namespace std;

//shader

#define GLSL400(src) "#version 400\n" #src

const char* vertSource1 = GLSL400(
	uniform mat4 ModelViewProjectionMatrix;
uniform float maxValue;
layout(location = 0) in vec4 Vertex;
layout(location = 1) in float intense;
out vec4 pixColor;
void main(void)
{
	gl_Position = ModelViewProjectionMatrix * Vertex;
	float tmp = step(0, intense);
	float r = 1.0;
	float g= 1.0;
	float b= 1.0;
	int vmin=0;
	int dv =400;
	if(intense==0){
		r = 1.0;
		g= 1.0;
		b= 1.0;
	}else if(intense<200){
		r = 0;
		g = 4 * (intense - vmin) / dv;
	}else if(intense<250){
		r = 0;
	    b = 1 + 4 * (vmin + 0.25 * dv - intense) / dv;
	}else if(intense<300){
		r = 4 * (intense - vmin - 0.5 * dv) / dv;
		b = 0;
	}else{
	    g = 1 + 4 * (vmin + 0.75 * dv - intense) / dv;
		b = 0;
	}
	pixColor = vec4(r, g, b, 1);
}
);

const char* vertSource2 = GLSL400(
	uniform mat4 ModelViewProjectionMatrix;
uniform float maxValue;
layout(location = 0) in vec4 Vertex;
layout(location = 1) in float intense;
out vec4 pixColor;
void main(void)
{
	gl_Position = ModelViewProjectionMatrix * Vertex;
	float tmp = step(0, intense);
	float r = 1.0;
	float g= 1.0;
	float b= 1.0;
	int vmin=0;
	int dv =800;
	if(intense==0){
		r = 1.0;
		g= 1.0;
		b= 1.0;
	}else if(intense<200){
		r = 0;
		g = 4 * (intense - vmin) / dv;
	}else if(intense<400){
		r = 0;
	    b = 1 + 4 * (vmin + 0.25 * dv - intense) / dv;
	}else if(intense<600){
		r = 4 * (intense - vmin - 0.5 * dv) / dv;
		b = 0;
	}else{
	    g = 1 + 4 * (vmin + 0.75 * dv - intense) / dv;
		b = 0;
	}
	pixColor = vec4(r, g, b, 1);
}
);

const char* vertSource3= GLSL400(
	uniform mat4 ModelViewProjectionMatrix;
uniform float maxValue;
layout(location = 0) in vec4 Vertex;
layout(location = 1) in float intense;
out vec4 pixColor;
void main(void)
{
	gl_Position = ModelViewProjectionMatrix * Vertex;
	float tmp = step(0, intense);
	float r = 1.0;
	float g= 1.0;
	float b= 1.0;
	int vmin=0;
	int dv =400;
	if(intense==0){
		r = 1.0;
		g= 1.0;
		b= 1.0;
	}else if(intense<240){
		r = 0;
		g = 4 * (intense - vmin) / dv;
	}else if(intense<250){
		r = 0;
	    b = 1 + 4 * (vmin + 0.25 * dv - intense) / dv;
	}else if(intense<255){
		r = 4 * (intense - vmin - 0.5 * dv) / dv;
		b = 0;
	}else{
	    g = 1 + 4 * (vmin + 0.75 * dv - intense) / dv;
		b = 0;
	}
	pixColor = vec4(r, g, b, 1);
}
);

const char* vertSource4 = GLSL400(
	uniform mat4 ModelViewProjectionMatrix;
uniform float maxValue;
layout(location = 0) in vec4 Vertex;
layout(location = 1) in float intense;
out vec4 pixColor;
void main(void)
{
	gl_Position = ModelViewProjectionMatrix * Vertex;
	float tmp = step(0, intense);
	float r = 1.0;
	float g= 1.0;
	float b= 1.0;
	int vmin=0;
	int dv =400;
	if(intense==0){
		r = 1.0;
		g= 1.0;
		b= 1.0;
	}
	else if(intense<50){
		r = 0;
		g = 4 * (intense - vmin) / dv;
	}else if(intense<150){
		r = 0;
	    b = 1 + 4 * (vmin + 0.25 * dv - intense) / dv;
	}else if(intense<600){
		r = 4 * (intense - vmin - 0.5 * dv) / dv;
		b = 0;
	}else{
	    g = 1 + 4 * (vmin + 0.75 * dv - intense) / dv;
		b = 0;
	}
	pixColor = vec4(r, g, b, 1);
}
);


//fragment shader�еĽ���˵��

//	if (intense>0)
//	{
//		pixColor = vec4(1.0-intense/maxValue, 1-intense/maxValue, 1.0,                1.0); //��ɫ�ڰ�ɫ����ɫ��
//	}
//	else
//	{
//		pixColor = vec4(1.0,                  1+intense/maxValue, 1+intense/maxValue, 1.0); //��ɫ�ڰ�ɫ���ɫ��
//	}

const char* fragSource1 = GLSL400(
	in vec4 pixColor;
void main(void)
{
	gl_FragColor = pixColor;
}
);

//typedef struct {
//    double r,g,b;
//} COLOUR;
//
//COLOUR GetColour(double v,double vmin,double vmax)
//{
//   COLOUR c = {1.0,1.0,1.0}; // white 
//   double dv;
//
//   if (v < vmin)
//      v = vmin;
//   if (v > vmax)
//      v = vmax;
//   dv = vmax - vmin;
//
   //if (v < (vmin + 0.25 * dv)) {
   //   c.r = 0;
   //   c.g = 4 * (v - vmin) / dv;
   //} else if (v < (vmin + 0.5 * dv)) {
   //   c.r = 0;
   //   c.b = 1 + 4 * (vmin + 0.25 * dv - v) / dv;
   //} else if (v < (vmin + 0.75 * dv)) {
   //   c.r = 4 * (v - vmin - 0.5 * dv) / dv;
   //   c.b = 0;
   //} else {
   //   c.g = 1 + 4 * (vmin + 0.75 * dv - v) / dv;
   //   c.b = 0;
   //}
//
//   return(c);
//}

//double interpolate( double val, double y0, double x0, double y1, double x1 ) {
//    return (val - x0)*(y1 - y0)/(x1 - x0) + y0;
//}
//
//double base( double val ) {
//    if ( val <= -0.75 ) return 0;
//    else if ( val <= -0.25 ) return interpolate( val, 0.0, -0.75, 1.0, -0.25 );
//    else if ( val <= 0.25 ) return 1.0;
//    else if ( val <= 0.75 ) return interpolate( val, 1.0, 0.25, 0.0, 0.75 );
//    else return 0.0;
//}
//
//double red( double gray ) {
//    return base( gray - 0.5 );
//}
//
//double green( double gray ) {
//    return base( gray );
//}
//double blue( double gray ) {
//    return base( gray + 0.5 );
//}

/*
	segy�ļ���ȡ�����ӻ���
*/
class segy
{
public:
	segy();
    ~segy();
    void ReadAllTrace(string folderName);												//��ȡ���е�����
	void ReadOneTrace(int typeNum,int pos);							    //��ȡ��������,typenumΪ�������ͣ�posΪλ��
    void drawAllTrace();                                                //������
	void colorMap();                                                    //ǿ��--��ɫӳ��
	void readFaceData();                                                //������������
	void setUnitGeom(osg::ref_ptr<osg::Geometry> geom);                 //����ͼԪ��Ԫ	
	void setSliceUnitGeom(osg::ref_ptr<osg::Geometry> geom);            //������ƬͼԪ
	void setShader(osg::ref_ptr<osg::Geometry> geom,
		osg::ref_ptr<osg::Camera> camera,osg::ref_ptr<osg::FloatArray> intensity,const char* vertSource1);	                            //����shader
	int traceNum;														// ������ĵ���   
	int sampleNum;														//��������
	int InLine;															//�����ϵ�����
	int CrossLine;														//��������������ϵ�����������traceNum
	float maxValue;														//���ĵ���ǿ��ֵ�����ڱ�׼������ǿ�ȣ���ɫӳ�䣩
	char* buffer;                                                       // ����ļ�����
	osg::ref_ptr<osg::FloatArray> intensity;							//���ڴ�ŵ���ǿ�����ݣ������Ҫ���Ƶĵ����ݣ�
	osg::ref_ptr<osg::FloatArray> cache;
	osg::ref_ptr<osg::FloatArray> sp;
	osg::ref_ptr<osg::FloatArray> gr	;
	int tempInLine;                                                     //�����ݴ�InLine����
	void outputFile();													//�����ļ�
	void datapre(string filename, float *dataset[],int row);
    std::string filename_;
	osg::ref_ptr<osg::Vec3Array> data;                                 //��������
	osg::ref_ptr<osg::Vec4Array> color;                               //��ɫ����
	osg::ref_ptr<osg::Group> root;										 //ģ�͸��ڵ�
	osg::ref_ptr<osg::Geometry> geom;								 // ģ���ӽڵ�
	osg::ref_ptr<osgViewer::Viewer> viewer;
	osg::ref_ptr<osg::Camera> camera;
	int sliceIdensity;                                                 //�Ƿ�����Ƭ�ı�ʶ 0���ǣ�1������
	int sliceType;													//��Ƭ������ 1-���� 2-���� 3-���� 0 ������
	int slicePos;													   //��Ƭ��λ�� 0 ������
	string itos(int i);
private:
};

segy::segy(){
	data = new osg::Vec3Array;
	color = new osg::Vec4Array;
	intensity = new osg::FloatArray;
	cache = new osg::FloatArray;	
	sp = new osg::FloatArray;
	gr = new osg::FloatArray;
	maxValue = 0.0;
	tempInLine = 0;
	sliceIdensity = 1; //������Ƭ
	sliceType = 0;
	slicePos = 0;
	root = new osg::Group;
	geom = new osg::Geometry;
	viewer = new osgViewer::Viewer;
	camera = viewer->getCamera();
	// turn lights off
	osg::StateSet* stateset = root->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
}

segy::~segy(){
}

//����ת�ַ���
string segy::itos(int i) {
    stringstream s;
    s << i;
    return s.str();
}

//��ȡtxt�ļ�
void segy::datapre(string filename, float *dataset[],int row){
	ifstream infile_feat_(filename); //���������ļ�
	//���ļ���ȡ������
	string rowdata; //�洢��ȡ��ÿ������
	float onePoint;  //�洢ÿ�а��ո�ֿ���ÿһ��float����
	int rownum =0;
	while(!infile_feat_.eof()){	
		getline(infile_feat_, rowdata); //һ�ζ�ȡһ������
		stringstream stringin(rowdata); //ʹ�ô���ʵ�ֶ�string�������������
		int k=0;
		while (stringin >> onePoint) {      //���ո�һ�ζ�ȡһ�����ݴ���feat_onePoint 
			//cout<<onePoint<<endl;
			if(onePoint<0){
					onePoint=1;
			}
			//dataset[rownum][k]=600*(onePoint-136.94)/272.33;
			dataset[rownum][k]= onePoint;	
			k++;
			if(k>1000) break;	
		}
		rownum++; //�洢��������
	}
	//cout<<rownum<<endl;
	infile_feat_.close();
}

/*
��ȡ�⾮����,��ʡʱ�䣬д�����Ϳ�
*/
void segy::ReadAllTrace(string folderName)
{
	clock_t tstart;
	tstart  = clock();
	cout<<"ִ��"<<endl;
	string filename1 = folderName+"data_"+itos(1)+".txt";
	string filename2 = folderName+"data_"+itos(2)+".txt";
	string filename3 = folderName+"data_"+itos(3)+".txt";
	string filename4 = folderName+"data_"+itos(4)+".txt";

	string filename2_1="C://Users//18810//Desktop//SpData//data_1.txt";
	string filename2_2="C://Users//18810//Desktop//SpData//data_2.txt";
	string filename2_3="C://Users//18810//Desktop//SpData//data_3.txt";
	string filename2_4="C://Users//18810//Desktop//SpData//data_4.txt";
	
	//string filename1="C://Users//18810//Desktop//AcGanData//dataF.txt";
	//string filename2="C://Users//18810//Desktop//AcGanData//dataB.txt";
	//string filename3="C://Users//18810//Desktop//AcGanData//dataR.txt";
	//string filename4="C://Users//18810//Desktop//AcGanData//dataL.txt";
	
	CrossLine=200;
	InLine=180;
	sampleNum=1000;
	maxValue=800;
	//float (*dataset1)[1001]=new float[][1001];
	float *dataset1[200];
	float *dataset2[200];
	float *dataset3[180];
	float *dataset4[180];

	float *dataset2_1[200];
	float *dataset2_2[200];
	float *dataset2_3[180];
	float *dataset2_4[180];
	
	//��ʼ��
	for (int i=0;i<CrossLine;i++){                                                                                        
		dataset1[i]=new float [sampleNum];
		dataset2[i]=new float [sampleNum];
		dataset2_1[i]=new float [sampleNum];
		dataset2_2[i]=new float [sampleNum];
		for(int j=0;j<sampleNum;j++){
			dataset1[i][j]=0.0;
			dataset2[i][j]=0.0;
			dataset2_1[i][j]=0.0;
			dataset2_2[i][j]=0.0;
		}
	}
	for (int i=0;i<InLine;i++){                                                                                        
		dataset3[i]=new float [sampleNum];
		dataset4[i]=new float [sampleNum];
		dataset2_3[i]=new float [sampleNum];
		dataset2_4[i]=new float [sampleNum];
		for(int j=0;j<sampleNum;j++){
			dataset3[i][j]=0.0;
			dataset4[i][j]=0.0;
			dataset2_3[i][j]=0.0;
			dataset2_4[i][j]=0.0;
		}
	}
	datapre(filename1,dataset1,200);
	datapre(filename2,dataset2,200);
	datapre(filename3,dataset3,180);
	datapre(filename4,dataset4,180);

	datapre(filename2_1,dataset2_1,200);
	datapre(filename2_2,dataset2_2,200);
	datapre(filename2_3,dataset2_3,180);
	datapre(filename2_4,dataset2_4,180);
	//������������ȷ��
	////����
	//cout<<dataset1[9][0] <<endl;
	////����
	//cout<<dataset2[9][0] <<endl;
	////�Ҳ���
	//cout<<dataset3[9][0]<<endl;
	////�����
	//cout<<dataset4[0][0]<<endl;
	//cout<<"crossLine:"<<CrossLine<<endl;
	//��������
	for(int i=0;i<CrossLine;i++){
		for (int n = 0; n < sampleNum; n++)
		{
			float tempValue = dataset1[i][n];                                       // �õ����ݺ�ֱ�ӷ���intensity��	
/*			float tempValue = dataset1[i][n]+50;					*/				
			intensity->push_back(tempValue);  //�õ�ǿ��
			gr->push_back(tempValue+50);  
			cache->push_back(600*(tempValue-136.94)/272.33);
			//sp->push_back(600*(dataset2_1[i][n]-136.94)/272.33);
			sp->push_back(dataset2_1[i][n]);
		}
	}
	if(InLine!=0)
	{  
		//���Ʊ���
		for(int i=0;i<CrossLine;i++){
			for (int n = 0; n < sampleNum; n++){
						float tempValue = dataset2[i][n];									// �õ����ݺ�ֱ�ӷ���intensity��	
						//float tempValue = dataset2[i][n]-100;
						intensity->push_back(tempValue);  //�õ�ǿ��
						gr->push_back(tempValue-100);  
						cache->push_back(600*(tempValue-136.94)/272.33);
						//sp->push_back(600*(dataset2_3[i][n]-136.94)/272.33);
						sp->push_back(dataset2_2[i][n]);
					}
		}						
		//�����Ҳ���
		for(int i=0;i<InLine;i++){
			for (int n = 0; n < sampleNum; n++)
			{		
				float tempValue = dataset3[i][n];									// �õ����ݺ�ֱ�ӷ���intensity��	
				//float tempValue = dataset3[i][n]+75;	
				intensity->push_back(tempValue);  //�õ�ǿ��
				gr->push_back(tempValue+75);  
				cache->push_back(600*(tempValue-136.94)/272.33);
				//sp->push_back(600*(dataset2_3[i][n]-136.94)/272.33);
				sp->push_back(dataset2_3[i][n]);
			}
		}
		//�����
		for(int i=0;i<InLine;i++){
			for (int n = 0; n < sampleNum; n++)
			{		
				float tempValue = dataset4[i][n];									// �õ����ݺ�ֱ�ӷ���intensity��	
				//float tempValue = dataset4[i][n]+300;
				intensity->push_back(tempValue);  //�õ�ǿ��	
				gr->push_back(tempValue+300);  
				cache->push_back(600*(tempValue-136.94)/272.33);
				sp->push_back(dataset2_4[i][n]);
			}
		}
	}
	cout<<"time:"<<clock()-tstart<<"ms"<<endl;
	//delete []dataset1;
	//delete []dataset2;
	//delete []dataset3;
	//delete []dataset4;
}


/*
��ɫӳ�亯��
�����ݱ�׼����0-1֮�䣬Ȼ���ں�-��-������������ɫ��ӳ��
*/
void segy::colorMap()  
{
	auto it =intensity->begin();
	float value;
	for (it;it<intensity->end();it++)
	{
		if (*it>0)																	//��ɫ
		{
			value = 1-*it/(float)maxValue;
			color->push_back(osg::Vec4f(value,value,1.0f,1.0f)); 
		}
		else																		//��ɫ
		{
			value = 1-(-*it)/(float)maxValue;
			color->push_back(osg::Vec4f(1.0f,value,value,1.0f)); 
		}
	}
	for (int i = 0; i < 8; i++)														//����ƽ��
	{
		color->push_back(osg::Vec4f(1.0f,1.0f,1.0f,1.0f)); 
	}
	
}

/*
��Ҫ���Ƶ������ݵ������趨
*/
void segy::readFaceData()
{
	//traceNum=traceNum/2;
	//sampleNum=sampleNum/2+1;
	//InLine/=2;
	traceNum=CrossLine;
	sampleNum = sampleNum;
	cout<<"traceNum:"<<traceNum<<endl;
	cout<<"sample:"<<sampleNum<<endl;
	cout<<"sliceIdensity:"<<sliceIdensity<<endl;
	if (sliceIdensity != 0)																//InLine!=0 ������   InLine = 0 ������
	{
		int flag = 0;
		int index = 0;
		float back = 0.0;
//		float fvalue;  
		while(flag < 2)																// �����뱳�涥�㸳ֵ
		{
			flag++;		
			for (int i = 0; i < traceNum; i++)
			{
				for (int j = 0; j < sampleNum; j++)
				{
//													//��indexΪ0ʱ��ʾ���� indexΪInLine-1Ϊ����
					data->push_back(osg::Vec3f(i/(float)traceNum,back,(sampleNum-1)/((float)traceNum*5) - j/((float)traceNum*5)));
				}
			}
			index = InLine-1;														//���һ��
			back = (InLine-1)/(float)traceNum;
		}
		flag = 0;
		index = traceNum-1;
		back = (traceNum-1)/(float)traceNum;
		while (flag<2)																//����
		{
			flag++;
			for (int i = 0; i < InLine; i++)
			{
				for (int j = 0; j < sampleNum; j++)
				{     
			//										//index = 0 ��ʾ�� index = traceNum-1 ��ʾ��
					data->push_back(osg::Vec3f(back,i/(float)traceNum,(sampleNum-1)/((float)traceNum*5)-j/((float)traceNum*5)));				
				}
			}
			index = 0; 
			back = 0.0;
		}
		back = 0.0;
		while (flag>0)															//���¿հ�ƽ��
		{
			data->push_back(osg::Vec3f(0.0f,0.0f,back));
			data->push_back(osg::Vec3f(0.0f,(InLine-1)/(float)traceNum,back));
			data->push_back(osg::Vec3f((traceNum-1)/(float)traceNum,(InLine-1)/(float)traceNum,back));
			data->push_back(osg::Vec3f((traceNum-1)/(float)traceNum,0.0f,back));
			flag--;
			back = (sampleNum-1)/((float)traceNum*5);
		}
		for (int i = 0; i < 8; i++)
		{
			intensity->push_back(0.0);
			cache->push_back(0.0);
			sp->push_back(0.0);
			gr->push_back(0.0);
		}
	}
	else if(sliceIdensity == 0)														// ������
	{
		if (sliceType==0||sliceType==1)
		{
			for (int i = 0; i < traceNum; i++)
			{
				for (int j = 0; j < sampleNum; j++)
				{
					data->push_back(osg::Vec3f(i/(float)traceNum,slicePos/(float)traceNum,(sampleNum-j)/(float)traceNum));  //slicePos ����λ�� Ĭ��Ϊ0
				}
			}
		}
		else if (sliceType==2)
		{
			for (int i = 0; i < InLine; i++)
			{
				for (int j = 0; j < sampleNum; j++)
				{
					data->push_back(osg::Vec3f(slicePos/(float)traceNum,i/(float)traceNum,(sampleNum-j)/(float)traceNum));  //slicePos ����λ�� Ĭ��Ϊ0
				}
			}
		}
		else if (sliceType==3)
		{
			for (int i = 0; i < InLine; i++)
			{
				for (int j = 0; j < traceNum; j++)
				{
					data->push_back(osg::Vec3f(j/(float)traceNum,i/(float)traceNum,(sampleNum-slicePos)/(float)traceNum));  //slicePos ����λ�� Ĭ��Ϊ0
				}
			}
		}
		
	}
	else
	{
		std::cout<<"���ݴ���";
		exit(0);
	}
}

/*
��ȡһ���������ݲ���ʾ��
typeNum:1-���棬2-���棬3-����
pos:����λ��

����Լ����ʹ����buffer����Ҫ��buffer�ƻص�һ����ͷλ��
�˳�����һ�����⣬�ȵ��Ժ�ʵ��ϵͳʱ�޸ģ�
1.û������Ƭ���׵Ķ������ݣ��ҵ������ǵ���һ����������ĺ�����Ȼ��ȴ��InLine��TraceNum��SampleNum�޸���
�´μ������׵��㷨
*/
void segy::ReadOneTrace(int typeNum,int pos)
{
	int iTrace = 0;
	if (typeNum == 1)																//��ȡ���棬��traceNum �ߣ�SampleNum
	{
		buffer+=(240+sampleNum*sizeof(float))*CrossLine*(pos-1);
		while (iTrace<CrossLine)   //һ��ѭ����һ����������
		{
			buffer += 240;
			uint8_t* ubuffer = new uint8_t[sampleNum*sizeof(float)];	
			std::memcpy(reinterpret_cast<char*>(ubuffer),buffer,sampleNum*sizeof(float));// �����ݶ���buf��
			buffer += sampleNum*sizeof(float);
			//����
			for (size_t n = 0; n < sampleNum; n++)
			{
				uint32_t ibmSample = *(reinterpret_cast<uint32_t*>(ubuffer + n*4));
				float tempValue = 0;									// �õ����ݺ�ֱ�ӷ���intensity��	
				intensity->push_back(tempValue);  //�õ�ǿ��
				if (maxValue<tempValue)
				{
					maxValue = tempValue;
				}
			}
			iTrace++;	
		}
		buffer-=(240+sampleNum*sizeof(float))*CrossLine*pos;

		/*****************************************/

		ofstream out("out1.txt");
		out<<"626";
		out<<"\t";
		out<<"601";
		out<<"\t";
		out<<"1";
		out<<"\n";
		for (int j = 0; j < 601; j++)
		{
			for (int k = 0; k < 626; k++)
			{
				if (out.is_open())   
				{  
					out << intensity->at(j*626+k);  
					out << "\t";    
				}  
			}
			out<<"\n";
		}
		out.close();
		cout<<"д�ļ�����";


		/*************************************/


	}
	else if(typeNum == 2)
	{
		//�����
//		buffer -=(240+sampleNum*sizeof(float))*(CrossLine-1);  //�ص��ļ�ͷ
		int currentIndex = (240+sampleNum*sizeof(float))*(pos-1); //�����ݳ���λ��
		iTrace = 0;
		while (iTrace<InLine)
		{
			currentIndex += 240;
			uint8_t* ubuffer = new uint8_t[sampleNum*sizeof(float)];	
			std::memcpy(reinterpret_cast<char*>(ubuffer),&(buffer[currentIndex]),sampleNum*sizeof(float));// �����ݶ���buf��
			currentIndex+= sampleNum*sizeof(float);
			for (size_t n = 0; n < sampleNum; n++)
			{		
				uint32_t ibmSample = *(reinterpret_cast<uint32_t*>(ubuffer+ n*4));
				float tempValue = 0;									// �õ����ݺ�ֱ�ӷ���intensity��	
				intensity->push_back(tempValue);  //�õ�ǿ��
				if (maxValue<tempValue)
				{
					maxValue = tempValue;
				}
			}			
			iTrace++;																	  // ���Ƶ���
			currentIndex = (240+sampleNum*sizeof(float))*CrossLine*iTrace+(240+sampleNum*sizeof(float))*(pos-1);
		}
	}
	else if(typeNum == 3)
	{
		//����
		int currentIndex = 0; //�����ݳ���λ��
		iTrace = 0;
		currentIndex += 240+(pos-1)*sizeof(float);
		while (iTrace<InLine)
		{
			
			for (size_t n = 0; n < CrossLine; n++)
			{		
				uint8_t* ubuffer = new uint8_t[sizeof(float)];	 
				std::memcpy(reinterpret_cast<char*>(ubuffer),&(buffer[currentIndex]),sizeof(float));// �����ݶ���buf��
				currentIndex += 240+sampleNum*sizeof(float); //��һ��
				uint32_t ibmSample = *(reinterpret_cast<uint32_t*>(ubuffer));
				float tempValue = 0;									// �õ����ݺ�ֱ�ӷ���intensity��	
				intensity->push_back(tempValue);  //�õ�ǿ��
				if (maxValue<tempValue)
				{
					maxValue = tempValue;
				}
			}			
			iTrace++;																	  // ���Ƶ���
//			currentIndex = (240+sampleNum*sizeof(float))*CrossLine*iTrace+(pos-1)*sizeof(float);
		}
	}
	else
	{
		cout<<"��Ƭ���ʹ���";
		exit(0);
	}
}

/*
���û���ͼԪ
*/
void segy::setUnitGeom(osg::ref_ptr<osg::Geometry> geom)
{
	int time = traceNum;									//����ѭ������
	int span = 0;
	int flag = 0;
	int oddFlag = 0;
	if (InLine != 0 && sliceType == 0)
	{
		while (flag<4)										//0--ǰ�� 1 ���� 2���� 3����
		{
			osg::DrawElementsUInt* base = new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP,0);
			if (time%2==0)  //ż�����һ�е�����ȡ
			{
				time -= 1;
				oddFlag = 1;
			}
			int pand = 0;
			for (int j = 0; j < time/2; j++)
			{
				pand += sampleNum;
				for (int i = 0+span; i < sampleNum+span; i++)
				{
					base->push_back(i+pand-sampleNum);
					base->push_back(i+pand);
				}
				for (int i = sampleNum-1+span; i >= 0+span; i--)
				{
					base->push_back(i+pand);
					base->push_back(i+pand+sampleNum);
				}
				pand += sampleNum;
			}
			if (oddFlag == 1)  //ż��
			{
				oddFlag = 0;
				time += 1;
				pand += sampleNum;
				for (int i = 0+span; i < sampleNum+span; i++)
				{
					base->push_back(i+pand-sampleNum);
					base->push_back(i+pand);
				}
			}
			geom->addPrimitiveSet(base);  //�ĸ���Ƭ�ĸ�base

			if (++flag == 1)								//������Ƭ����λ�ã���Ҫ�����ĳ��ȣ�
			{
				span = traceNum*sampleNum;
			}
			else if(flag == 2)								//����
			{
				time = InLine;
				span *= 2;
			}
			else if(flag == 3)								//����
			{
				span += InLine*sampleNum;
			}
		}
		span += InLine*sampleNum;							//����ƽ��
		flag = 0;
		while (flag<2)
		{
			osg::DrawElementsUInt* base = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS,0);
			for (int i = 0; i < 4; i++)
			{		
				base->push_back(span++);
			}
			geom->addPrimitiveSet(base);
			flag++;
		}
	}
	else if (InLine == 0)
	{
		osg::DrawElementsUInt* base = new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP,0);
		int span = 0;
		int travelTime = traceNum;
		if (traceNum%2==0)  //ż�����һ�е�����ȡ
		{
			travelTime -= 1;
		}
		for (int j = 0; j < travelTime/2; j++)
		{
			span += sampleNum;
			for (int i = 0; i < sampleNum; i++)
			{
				base->push_back(i+span-sampleNum);
				base->push_back(i+span);
			}
			for (int i = sampleNum-1; i >= 0; i--)
			{
				base->push_back(i+span);
				base->push_back(i+span+sampleNum);
			}
			span += sampleNum;
		}
		if (traceNum%2==0)  //ż��
		{
			span += sampleNum;
			for (int i = 0; i < sampleNum; i++)
			{
				base->push_back(i+span-sampleNum);
				base->push_back(i+span);
			}
		}
		geom->addPrimitiveSet(base);
	}
	else if(InLine != 0 && sliceType != 0)  //inline��= 0 ������ sliceType!= 0 ��Ƭ
	{
		if (sliceType == 1)  //����
		{
			osg::DrawElementsUInt* base = new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP,0);
			int span = 0;
			int travelTime = traceNum;
			if (traceNum%2==0)  //ż�����һ�е�����ȡ
			{
				travelTime -= 1;
			}
			for (int j = 0; j < travelTime/2; j++)
			{
				span += sampleNum;
				for (int i = 0; i < sampleNum; i++)
				{
					base->push_back(i+span-sampleNum);
					base->push_back(i+span);
				}
				for (int i = sampleNum-1; i >= 0; i--)
				{
					base->push_back(i+span);
					base->push_back(i+span+sampleNum);
				}
				span += sampleNum;
			}
			if (traceNum%2==0)  //ż��
			{
				span += sampleNum;
				for (int i = 0; i < sampleNum; i++)
				{
					base->push_back(i+span-sampleNum);
					base->push_back(i+span);
				}
			}
			geom->addPrimitiveSet(base);
		}
		else if (sliceType == 2)
		{
			osg::DrawElementsUInt* base = new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP,0);
			int span = 0;
			int travelTime = InLine;
			if (InLine%2==0)  //ż�����һ�е�����ȡ
			{
				travelTime -= 1;
			}
			for (int j = 0; j < travelTime/2; j++)
			{
				span += sampleNum;
				for (int i = 0; i < sampleNum; i++)
				{
					base->push_back(i+span-sampleNum);
					base->push_back(i+span);
				}
				for (int i = sampleNum-1; i >= 0; i--)
				{
					base->push_back(i+span);
					base->push_back(i+span+sampleNum);
				}
				span += sampleNum;
			}
			if (InLine%2==0)  //ż��
			{
				span += sampleNum;
				for (int i = 0; i < sampleNum; i++)
				{
					base->push_back(i+span-sampleNum);
					base->push_back(i+span);
				}
			}
			geom->addPrimitiveSet(base);
		}
		else if (sliceType == 3)
		{
			osg::DrawElementsUInt* base = new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP,0);
			int span = 0;
			int travelTime = InLine;
			if (InLine%2==0)  //ż�����һ�е�����ȡ
			{
				travelTime -= 1;
			}
			for (int j = 0; j < travelTime/2; j++)
			{
				span += traceNum;
				for (int i = 0; i < traceNum; i++)
				{
					base->push_back(i+span-traceNum);
					base->push_back(i+span);
				}
				for (int i = traceNum-1; i >= 0; i--)
				{
					base->push_back(i+span);
					base->push_back(i+span+traceNum);
				}
				span += traceNum;
			}
			if (InLine%2==0)  //ż��
			{
				span += traceNum;
				for (int i = 0; i < traceNum; i++)
				{
					base->push_back(i+span-traceNum);
					base->push_back(i+span);
				}
			}
			geom->addPrimitiveSet(base);
		}
	}
}

/*
void segy::drawAllTrace()
{
	readFaceData();										//������
	colorMap();												//��ɫӳ��
} */

//��ת�������
struct ModelViewProjectionMatrixCallback:public osg::Uniform::Callback{
	ModelViewProjectionMatrixCallback(osg::Camera* camera):_camera(camera){}
	virtual void operator()(osg::Uniform* uniform, osg::NodeVisitor* nv) {
		osg::Matrixd viewMatrix = _camera->getViewMatrix();
		osg::Matrixd modelMatrix = osg::computeLocalToWorld(nv->getNodePath());
		osg::Matrixd modelViewProjectionMatrix = modelMatrix * viewMatrix * _camera->getProjectionMatrix();
		uniform->set(modelViewProjectionMatrix);
	}

	osg::Camera* _camera;
};

void segy::setShader(osg::ref_ptr<osg::Geometry> geom,osg::ref_ptr<osg::Camera> camera,	
					 osg::ref_ptr<osg::FloatArray> intensity,const char* vertSource)
{
	//��������shader �е�����
	geom->setVertexAttribArray(0,data,osg::Array::BIND_PER_VERTEX);
	geom->setVertexAttribArray(1,intensity,osg::Array::BIND_PER_VERTEX);
	//����shader
	osg::ref_ptr<osg::Shader> vertShader = new osg::Shader(osg::Shader::VERTEX,vertSource);
	osg::ref_ptr<osg::Shader> fragShader = new osg::Shader(osg::Shader::FRAGMENT,fragSource1);
	osg::ref_ptr<osg::Program> Program = new osg::Program;
	Program->addShader(vertShader.get());
	Program->addShader(fragShader.get());

	osg::DisplaySettings* displaySettings = new osg::DisplaySettings;
	viewer->setDisplaySettings(displaySettings);
	geom->setUseDisplayList(false);
	osg::StateSet* stateset = geom->getOrCreateStateSet();
	stateset->setAttributeAndModes(Program.get(),osg::StateAttribute::ON); //����shader����
	// add uniforms
	osg::Uniform* modelViewProjectionMatrix = new osg::Uniform(osg::Uniform::FLOAT_MAT4, "ModelViewProjectionMatrix");
	modelViewProjectionMatrix->setUpdateCallback(new ModelViewProjectionMatrixCallback(camera));
	stateset->addUniform(modelViewProjectionMatrix);
	stateset->addUniform(new osg::Uniform("maxValue",maxValue));
}

void segy::outputFile()
{
	ofstream out("out.txt");
	out<<"626";
	out<<"\t";
	out<<"601";
	out<<"\t";
	out<<"301";
	out<<"\n";
	for (int i = 0; i < 300; i++)
	{
		for (int j = 0; j < 601; j++)
		{
			for (int k = 0; k < 626; k++)
			{
				if (out.is_open())   
				{  
//					out << VolumeTrace[i][j][k];  
					out << "\t";    
				}  
			}
			out<<"\n";
		}
		out<<"\n";
	}
	out.close();
	cout<<"д�ļ�����";
}


class KeyboardHandler :public osgGA::GUIEventHandler//�˻������¼�������  
{  
public:  
	KeyboardHandler(segy sgy1):sgy(sgy1){}
	segy sgy;
	//�ع�����GUIEventHandler.handle���¼����������Զ��彻��������  
	//����1:��ǰ����˴��������¼���ֻ���Ա���ȡ�����ܱ��޸�  
	//����2���������������������������Ի�ȡҲ�����޸ĵĲ������󲿷�ʱ���������ֵ��ʾ��ǰ���õ���ͼ����View��������������ȡ  
	//        ������Ӿ�����״̬�仯���磺osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);  
	//����3������ָ��obj������ô������Ķ��󣬿����ǵ�ǰ�¼��ص����ڵ�Node�ڵ�ָ�룬Ҳ������Drawableָ��  
	//����4�����ݸ��¼��ķ�������EventVisitor����nvͨ��Ϊ��ǰʱ�������ָ�롣  
	virtual bool handle(const osgGA::GUIEventAdapter& ea,  
		osgGA::GUIActionAdapter& aa,  
		osg::Object* obj, osg::NodeVisitor* nv)  
	{  
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);  
		if (!viewer)return false;  
		switch (ea.getEventType())//�ж��¼���������Ӧ  
		{  
		case osgGA::GUIEventAdapter::KEYDOWN://ea.getEventType()��ȡ��������Ǽ����¼�  
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)//�ո񣬿�����굽��Ļ�м�  
			{  
				int width = ea.getWindowWidth();  
				int heigth = ea.getWindowHeight();  
				viewer->requestWarpPointer(width*0.5, heigth*0.5);  
			}  
			else  
			{  
				osg::Group* root = dynamic_cast<osg::Group*>(viewer->getSceneData());  
				if (!root) return false;   
				if (ea.getKey() == '1')  
				{  
					cout<<"you press 1"<<endl;
					root->removeChild(0,1);
					sgy.data->clear();
					sgy.intensity->clear();
				}  
				else if (ea.getKey() == '2')  
				{  
					clock_t start;
					start  = clock();

					cout<<"you press 2"<<endl;
					sgy.readFaceData();                        //�������ص�λ������  -> data  [float,float,float]
					sgy.setUnitGeom(sgy.geom);                 // ����Ҫ���Ƴ�ͼԪ��������intensity�е��������base��
					sgy.setShader(sgy.geom,sgy.camera,sgy.gr,vertSource2);				//������ݣ�����shader
					sgy.slicePos = 0;  //����λ�� 
					sgy.sliceType = 0;  //����
					sgy.sliceIdensity = 1;  //������Ƭ
					root->insertChild(0,sgy.geom);					

					cout<<(clock()-start)*3<<"ms"<<endl;
				}  
				else if (ea.getKey() == '3')  
				{  
					clock_t start;
					start  = clock();

					cout<<"you press 3"<<endl;
					sgy.readFaceData();                        //�������ص�λ������  -> data  [float,float,float]
					sgy.setUnitGeom(sgy.geom);                 // ����Ҫ���Ƴ�ͼԪ��������intensity�е��������base��
					sgy.setShader(sgy.geom,sgy.camera,sgy.sp, vertSource2);				//������ݣ�����shader
					sgy.slicePos = 0;  //����λ�� 
					sgy.sliceType = 0;  //����
					sgy.sliceIdensity = 1;  //������Ƭ
					root->insertChild(0,sgy.geom);					

					cout<<(clock()-start)*3<<"ms"<<endl;
				}  
				else if (ea.getKey() == '4')  
				{ 
					clock_t start;
					start  = clock();

					cout<<"you press 4"<<endl;
					sgy.readFaceData();                        //�������ص�λ������  -> data  [float,float,float]
					sgy.setUnitGeom(sgy.geom);                 // ����Ҫ���Ƴ�ͼԪ��������intensity�е��������base��
					sgy.setShader(sgy.geom,sgy.camera,sgy.cache, vertSource2);				//������ݣ�����shader
					sgy.slicePos = 0;  //����λ�� 
					sgy.sliceType = 0;  //����
					sgy.sliceIdensity = 1;  //������Ƭ
					root->insertChild(0,sgy.geom);					

					cout<<(clock()-start)*3<<"ms"<<endl;
				}  
				else if (ea.getKey() == '5')  
				{  
					clock_t start;
					start  = clock();

					cout<<"you press 5"<<endl;  //��ʾ����������
					//string fName= "C://Users//18810//Desktop//GRData//";
					string folderName = "C://Users//18810//Desktop//AcGanData//";
					string filename1 = folderName+"data_"+sgy.itos(1)+".txt";
					string filename2 = folderName+"data_"+sgy.itos(2)+".txt";
					string filename3 = folderName+"data_"+sgy.itos(3)+".txt";
					string filename4 = folderName+"data_"+sgy.itos(4)+".txt";
					sgy.CrossLine=200;
					sgy.InLine=180;
					sgy.sampleNum=1000;
					sgy.maxValue=800;
					//float (*dataset1)[1001]=new float[][1001];
					float *dataset1[200];
					float *dataset2[200];
					float *dataset3[180];
					float *dataset4[180];
	
					//��ʼ��
					for (int i=0;i<sgy.CrossLine;i++){                                                                                        
						dataset1[i]=new float [sgy.sampleNum];
						dataset2[i]=new float [sgy.sampleNum];
						for(int j=0;j<sgy.sampleNum;j++){
							dataset1[i][j]=0.0;
							dataset2[i][j]=0.0;
						}
					}
					for (int i=0;i<sgy.InLine;i++){                                                                                        
						dataset3[i]=new float [sgy.sampleNum];
						dataset4[i]=new float [sgy.sampleNum];
						for(int j=0;j<sgy.sampleNum;j++){
							dataset3[i][j]=0.0;
							dataset4[i][j]=0.0;
						}
					}
					sgy.datapre(filename1,dataset1,200);
					sgy.datapre(filename2,dataset2,200);
					sgy.datapre(filename3,dataset3,180);
					sgy.datapre(filename4,dataset4,180);

					//��������
					for(int i=0;i < sgy.CrossLine;i++){
						for (int n = 0; n < sgy.sampleNum; n++)
						{                         // �õ����ݺ�ֱ�ӷ���intensity��	
							float tempValue = dataset1[i][n];									
							sgy.intensity->push_back(tempValue);  //�õ�ǿ��
						}
					}
					if(sgy.InLine!=0)
					{  
						//���Ʊ���
						for(int i=0;i < sgy.CrossLine;i++){
							for (int n = 0; n<sgy.sampleNum; n++){
										//float tempValue = dataset2[i][n];									// �õ����ݺ�ֱ�ӷ���intensity��	
										float tempValue = dataset2[i][n]��
										sgy.intensity->push_back(tempValue);  //�õ�ǿ��
									}
						}						
						//�����Ҳ���
						for(int i=0;i < sgy.InLine;i++){
							for (int n = 0; n<sgy.sampleNum; n++)
							{		
								//float tempValue = dataset3[i][n];									// �õ����ݺ�ֱ�ӷ���intensity��	
								float tempValue = dataset3[i][n];	
								sgy.intensity->push_back(tempValue);  //�õ�ǿ��
							}
						}
						//�����
						for(int i=0;i < sgy.InLine;i++){
							for (int n = 0; n < sgy.sampleNum; n++)
							{		
								//float tempValue = dataset4[i][n];									// �õ����ݺ�ֱ�ӷ���intensity��	
								float tempValue = dataset4[i][n];
								sgy.intensity->push_back(tempValue);  //�õ�ǿ��	
							}
						}
					}
					//sgy.ReadAllTrace();
					sgy.readFaceData();                        //�������ص�λ������  -> data  [float,float,float]
					sgy.setUnitGeom(sgy.geom);                 // ����Ҫ���Ƴ�ͼԪ��������intensity�е��������base��
					sgy.setShader(sgy.geom,sgy.camera,sgy.intensity,vertSource2);				//������ݣ�����shader
					sgy.slicePos = 0;  //����λ�� 
					sgy.sliceType = 0;  //����
					sgy.sliceIdensity = 1;  //������Ƭ
					root->insertChild(0,sgy.geom);					

					cout<<clock()-start<<"ms"<<endl;
				}  
/*				else if (ea.getKey() == '6')
				{
					cout<<"you press 6";
					sgy.geom = new osg::Geometry;
					//sgy.ReadTraceHeader("pg_lm.segy");
					sgy.ReadAllTrace();      //��������
					sgy.readFaceData();
					sgy.setUnitGeom(sgy.geom); 
					sgy.setShader(sgy.geom,sgy.camera);				//������ݣ�����shader
					root->insertChild(0,sgy.geom);
				}*/
				return true;  
			}  
			break;  
		default:break;  
		}  
		return false;  
	}  
};  