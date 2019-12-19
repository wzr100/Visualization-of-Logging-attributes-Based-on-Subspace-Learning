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
	segy文件读取，可视化类
*/
class segy
{
public:
	segy();
    ~segy();
    void ReadAllTrace(string folderName);												//读取所有的数据
	void ReadOneTrace(int typeNum,int pos);							    //读取切面数据,typenum为切面类型，pos为位置
    void drawAllTrace();                                                //绘制面
	void colorMap();                                                    //强度--颜色映射
	void readFaceData();                                                //读出顶点数据
	void setUnitGeom(osg::ref_ptr<osg::Geometry> geom);                 //设置图元单元	
	void setSliceUnitGeom(osg::ref_ptr<osg::Geometry> geom);            //设置切片图元
	void setShader(osg::ref_ptr<osg::Geometry> geom,
		osg::ref_ptr<osg::Camera> camera,osg::ref_ptr<osg::FloatArray> intensity,const char* vertSource1);	                            //设置shader
	int traceNum;														// 地震道的道数   
	int sampleNum;														//采样点数
	int InLine;															//纵向上的数量
	int CrossLine;														//地震道数，横向上的数量，等于traceNum
	float maxValue;														//最大的地震强度值，用于标准化地震强度（颜色映射）
	char* buffer;                                                       // 存放文件内容
	osg::ref_ptr<osg::FloatArray> intensity;							//用于存放地震强度数据（存放需要绘制的点数据）
	osg::ref_ptr<osg::FloatArray> cache;
	osg::ref_ptr<osg::FloatArray> sp;
	osg::ref_ptr<osg::FloatArray> gr	;
	int tempInLine;                                                     //用于暂存InLine数据
	void outputFile();													//导出文件
	void datapre(string filename, float *dataset[],int row);
    std::string filename_;
	osg::ref_ptr<osg::Vec3Array> data;                                 //顶点数据
	osg::ref_ptr<osg::Vec4Array> color;                               //颜色数据
	osg::ref_ptr<osg::Group> root;										 //模型根节点
	osg::ref_ptr<osg::Geometry> geom;								 // 模型子节点
	osg::ref_ptr<osgViewer::Viewer> viewer;
	osg::ref_ptr<osg::Camera> camera;
	int sliceIdensity;                                                 //是否是切片的标识 0：是，1：不是
	int sliceType;													//切片的类型 1-正面 2-侧面 3-上面 0 体数据
	int slicePos;													   //切片的位置 0 体数据
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
	sliceIdensity = 1; //不是切片
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

//整数转字符串
string segy::itos(int i) {
    stringstream s;
    s << i;
    return s.str();
}

//读取txt文件
void segy::datapre(string filename, float *dataset[],int row){
	ifstream infile_feat_(filename); //加载数据文件
	//从文件读取点数据
	string rowdata; //存储读取的每行数据
	float onePoint;  //存储每行按空格分开的每一个float数据
	int rownum =0;
	while(!infile_feat_.eof()){	
		getline(infile_feat_, rowdata); //一次读取一行数据
		stringstream stringin(rowdata); //使用串流实现对string的输入输出操作
		int k=0;
		while (stringin >> onePoint) {      //按空格一次读取一个数据存入feat_onePoint 
			//cout<<onePoint<<endl;
			if(onePoint<0){
					onePoint=1;
			}
			//dataset[rownum][k]=600*(onePoint-136.94)/272.33;
			dataset[rownum][k]= onePoint;	
			k++;
			if(k>1000) break;	
		}
		rownum++; //存储所有数据
	}
	//cout<<rownum<<endl;
	infile_feat_.close();
}

/*
读取测井数据,节省时间，写死长和宽
*/
void segy::ReadAllTrace(string folderName)
{
	clock_t tstart;
	tstart  = clock();
	cout<<"执行"<<endl;
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
	
	//初始化
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
	//抽查检验数据正确性
	////正面
	//cout<<dataset1[9][0] <<endl;
	////背面
	//cout<<dataset2[9][0] <<endl;
	////右侧面
	//cout<<dataset3[9][0]<<endl;
	////左侧面
	//cout<<dataset4[0][0]<<endl;
	//cout<<"crossLine:"<<CrossLine<<endl;
	//绘制正面
	for(int i=0;i<CrossLine;i++){
		for (int n = 0; n < sampleNum; n++)
		{
			float tempValue = dataset1[i][n];                                       // 得到数据后直接放入intensity中	
/*			float tempValue = dataset1[i][n]+50;					*/				
			intensity->push_back(tempValue);  //得到强度
			gr->push_back(tempValue+50);  
			cache->push_back(600*(tempValue-136.94)/272.33);
			//sp->push_back(600*(dataset2_1[i][n]-136.94)/272.33);
			sp->push_back(dataset2_1[i][n]);
		}
	}
	if(InLine!=0)
	{  
		//绘制背面
		for(int i=0;i<CrossLine;i++){
			for (int n = 0; n < sampleNum; n++){
						float tempValue = dataset2[i][n];									// 得到数据后直接放入intensity中	
						//float tempValue = dataset2[i][n]-100;
						intensity->push_back(tempValue);  //得到强度
						gr->push_back(tempValue-100);  
						cache->push_back(600*(tempValue-136.94)/272.33);
						//sp->push_back(600*(dataset2_3[i][n]-136.94)/272.33);
						sp->push_back(dataset2_2[i][n]);
					}
		}						
		//绘制右侧面
		for(int i=0;i<InLine;i++){
			for (int n = 0; n < sampleNum; n++)
			{		
				float tempValue = dataset3[i][n];									// 得到数据后直接放入intensity中	
				//float tempValue = dataset3[i][n]+75;	
				intensity->push_back(tempValue);  //得到强度
				gr->push_back(tempValue+75);  
				cache->push_back(600*(tempValue-136.94)/272.33);
				//sp->push_back(600*(dataset2_3[i][n]-136.94)/272.33);
				sp->push_back(dataset2_3[i][n]);
			}
		}
		//左侧面
		for(int i=0;i<InLine;i++){
			for (int n = 0; n < sampleNum; n++)
			{		
				float tempValue = dataset4[i][n];									// 得到数据后直接放入intensity中	
				//float tempValue = dataset4[i][n]+300;
				intensity->push_back(tempValue);  //得到强度	
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
颜色映射函数
将数据标准化到0-1之间，然后在红-白-蓝三种三种颜色间映射
*/
void segy::colorMap()  
{
	auto it =intensity->begin();
	float value;
	for (it;it<intensity->end();it++)
	{
		if (*it>0)																	//蓝色
		{
			value = 1-*it/(float)maxValue;
			color->push_back(osg::Vec4f(value,value,1.0f,1.0f)); 
		}
		else																		//红色
		{
			value = 1-(-*it)/(float)maxValue;
			color->push_back(osg::Vec4f(1.0f,value,value,1.0f)); 
		}
	}
	for (int i = 0; i < 8; i++)														//上下平面
	{
		color->push_back(osg::Vec4f(1.0f,1.0f,1.0f,1.0f)); 
	}
	
}

/*
需要绘制的面数据的坐标设定
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
	if (sliceIdensity != 0)																//InLine!=0 体数据   InLine = 0 面数据
	{
		int flag = 0;
		int index = 0;
		float back = 0.0;
//		float fvalue;  
		while(flag < 2)																// 正面与背面顶点赋值
		{
			flag++;		
			for (int i = 0; i < traceNum; i++)
			{
				for (int j = 0; j < sampleNum; j++)
				{
//													//当index为0时表示正面 index为InLine-1为背面
					data->push_back(osg::Vec3f(i/(float)traceNum,back,(sampleNum-1)/((float)traceNum*5) - j/((float)traceNum*5)));
				}
			}
			index = InLine-1;														//最后一层
			back = (InLine-1)/(float)traceNum;
		}
		flag = 0;
		index = traceNum-1;
		back = (traceNum-1)/(float)traceNum;
		while (flag<2)																//右左
		{
			flag++;
			for (int i = 0; i < InLine; i++)
			{
				for (int j = 0; j < sampleNum; j++)
				{     
			//										//index = 0 表示左 index = traceNum-1 表示右
					data->push_back(osg::Vec3f(back,i/(float)traceNum,(sampleNum-1)/((float)traceNum*5)-j/((float)traceNum*5)));				
				}
			}
			index = 0; 
			back = 0.0;
		}
		back = 0.0;
		while (flag>0)															//上下空白平面
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
	else if(sliceIdensity == 0)														// 面数据
	{
		if (sliceType==0||sliceType==1)
		{
			for (int i = 0; i < traceNum; i++)
			{
				for (int j = 0; j < sampleNum; j++)
				{
					data->push_back(osg::Vec3f(i/(float)traceNum,slicePos/(float)traceNum,(sampleNum-j)/(float)traceNum));  //slicePos 切面位置 默认为0
				}
			}
		}
		else if (sliceType==2)
		{
			for (int i = 0; i < InLine; i++)
			{
				for (int j = 0; j < sampleNum; j++)
				{
					data->push_back(osg::Vec3f(slicePos/(float)traceNum,i/(float)traceNum,(sampleNum-j)/(float)traceNum));  //slicePos 切面位置 默认为0
				}
			}
		}
		else if (sliceType==3)
		{
			for (int i = 0; i < InLine; i++)
			{
				for (int j = 0; j < traceNum; j++)
				{
					data->push_back(osg::Vec3f(j/(float)traceNum,i/(float)traceNum,(sampleNum-slicePos)/(float)traceNum));  //slicePos 切面位置 默认为0
				}
			}
		}
		
	}
	else
	{
		std::cout<<"数据错误。";
		exit(0);
	}
}

/*
读取一个切面数据并显示：
typeNum:1-正面，2-侧面，3-上面
pos:切面位置

我们约定：使用完buffer后需要将buffer移回第一道道头位置
此程序有一个问题，等到以后实现系统时修改：
1.没有与切片配套的顶点数据，我的做法是调用一个绘制正面的函数，然而却将InLine，TraceNum，SampleNum修改了
下次加上配套的算法
*/
void segy::ReadOneTrace(int typeNum,int pos)
{
	int iTrace = 0;
	if (typeNum == 1)																//读取正面，宽：traceNum 高：SampleNum
	{
		buffer+=(240+sampleNum*sizeof(float))*CrossLine*(pos-1);
		while (iTrace<CrossLine)   //一次循环读一条测线数据
		{
			buffer += 240;
			uint8_t* ubuffer = new uint8_t[sampleNum*sizeof(float)];	
			std::memcpy(reinterpret_cast<char*>(ubuffer),buffer,sampleNum*sizeof(float));// 将数据读到buf中
			buffer += sampleNum*sizeof(float);
			//单面
			for (size_t n = 0; n < sampleNum; n++)
			{
				uint32_t ibmSample = *(reinterpret_cast<uint32_t*>(ubuffer + n*4));
				float tempValue = 0;									// 得到数据后直接放入intensity中	
				intensity->push_back(tempValue);  //得到强度
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
		cout<<"写文件结束";


		/*************************************/


	}
	else if(typeNum == 2)
	{
		//左侧面
//		buffer -=(240+sampleNum*sizeof(float))*(CrossLine-1);  //回到文件头
		int currentIndex = (240+sampleNum*sizeof(float))*(pos-1); //道数据乘以位置
		iTrace = 0;
		while (iTrace<InLine)
		{
			currentIndex += 240;
			uint8_t* ubuffer = new uint8_t[sampleNum*sizeof(float)];	
			std::memcpy(reinterpret_cast<char*>(ubuffer),&(buffer[currentIndex]),sampleNum*sizeof(float));// 将数据读到buf中
			currentIndex+= sampleNum*sizeof(float);
			for (size_t n = 0; n < sampleNum; n++)
			{		
				uint32_t ibmSample = *(reinterpret_cast<uint32_t*>(ubuffer+ n*4));
				float tempValue = 0;									// 得到数据后直接放入intensity中	
				intensity->push_back(tempValue);  //得到强度
				if (maxValue<tempValue)
				{
					maxValue = tempValue;
				}
			}			
			iTrace++;																	  // 控制道数
			currentIndex = (240+sampleNum*sizeof(float))*CrossLine*iTrace+(240+sampleNum*sizeof(float))*(pos-1);
		}
	}
	else if(typeNum == 3)
	{
		//上面
		int currentIndex = 0; //道数据乘以位置
		iTrace = 0;
		currentIndex += 240+(pos-1)*sizeof(float);
		while (iTrace<InLine)
		{
			
			for (size_t n = 0; n < CrossLine; n++)
			{		
				uint8_t* ubuffer = new uint8_t[sizeof(float)];	 
				std::memcpy(reinterpret_cast<char*>(ubuffer),&(buffer[currentIndex]),sizeof(float));// 将数据读到buf中
				currentIndex += 240+sampleNum*sizeof(float); //加一道
				uint32_t ibmSample = *(reinterpret_cast<uint32_t*>(ubuffer));
				float tempValue = 0;									// 得到数据后直接放入intensity中	
				intensity->push_back(tempValue);  //得到强度
				if (maxValue<tempValue)
				{
					maxValue = tempValue;
				}
			}			
			iTrace++;																	  // 控制道数
//			currentIndex = (240+sampleNum*sizeof(float))*CrossLine*iTrace+(pos-1)*sizeof(float);
		}
	}
	else
	{
		cout<<"切片类型错误！";
		exit(0);
	}
}

/*
设置绘制图元
*/
void segy::setUnitGeom(osg::ref_ptr<osg::Geometry> geom)
{
	int time = traceNum;									//控制循环次数
	int span = 0;
	int flag = 0;
	int oddFlag = 0;
	if (InLine != 0 && sliceType == 0)
	{
		while (flag<4)										//0--前面 1 后面 2上面 3下面
		{
			osg::DrawElementsUInt* base = new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP,0);
			if (time%2==0)  //偶数最后一行单独读取
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
			if (oddFlag == 1)  //偶数
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
			geom->addPrimitiveSet(base);  //四个面片四个base

			if (++flag == 1)								//后面面片数据位置（需要跳过的长度）
			{
				span = traceNum*sampleNum;
			}
			else if(flag == 2)								//左面
			{
				time = InLine;
				span *= 2;
			}
			else if(flag == 3)								//右面
			{
				span += InLine*sampleNum;
			}
		}
		span += InLine*sampleNum;							//左右平面
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
		if (traceNum%2==0)  //偶数最后一行单独读取
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
		if (traceNum%2==0)  //偶数
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
	else if(InLine != 0 && sliceType != 0)  //inline！= 0 体数据 sliceType!= 0 切片
	{
		if (sliceType == 1)  //正面
		{
			osg::DrawElementsUInt* base = new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP,0);
			int span = 0;
			int travelTime = traceNum;
			if (traceNum%2==0)  //偶数最后一行单独读取
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
			if (traceNum%2==0)  //偶数
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
			if (InLine%2==0)  //偶数最后一行单独读取
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
			if (InLine%2==0)  //偶数
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
			if (InLine%2==0)  //偶数最后一行单独读取
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
			if (InLine%2==0)  //偶数
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
	readFaceData();										//体数据
	colorMap();												//颜色映射
} */

//旋转相机设置
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
	//设置输入shader 中的数据
	geom->setVertexAttribArray(0,data,osg::Array::BIND_PER_VERTEX);
	geom->setVertexAttribArray(1,intensity,osg::Array::BIND_PER_VERTEX);
	//定义shader
	osg::ref_ptr<osg::Shader> vertShader = new osg::Shader(osg::Shader::VERTEX,vertSource);
	osg::ref_ptr<osg::Shader> fragShader = new osg::Shader(osg::Shader::FRAGMENT,fragSource1);
	osg::ref_ptr<osg::Program> Program = new osg::Program;
	Program->addShader(vertShader.get());
	Program->addShader(fragShader.get());

	osg::DisplaySettings* displaySettings = new osg::DisplaySettings;
	viewer->setDisplaySettings(displaySettings);
	geom->setUseDisplayList(false);
	osg::StateSet* stateset = geom->getOrCreateStateSet();
	stateset->setAttributeAndModes(Program.get(),osg::StateAttribute::ON); //设置shader属性
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
	cout<<"写文件结束";
}


class KeyboardHandler :public osgGA::GUIEventHandler//人机交互事件处理器  
{  
public:  
	KeyboardHandler(segy sgy1):sgy(sgy1){}
	segy sgy;
	//重构父类GUIEventHandler.handle，事件处理函数，自定义交互操作，  
	//参数1:当前传入此处理器的事件，只可以被获取，不能被修改  
	//参数2：反馈动作，动作适配器，可以获取也可以修改的参数，大部分时候这个传入值表示当前所用的视图对象View，可以用它来获取  
	//        或控制视景器的状态变化。如：osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);  
	//参数3：对象指针obj，保存该处理器的对象，可能是当前事件回调所在的Node节点指针，也可能是Drawable指针  
	//参数4：传递该事件的访问器（EventVisitor），nv通常为当前时间访问器指针。  
	virtual bool handle(const osgGA::GUIEventAdapter& ea,  
		osgGA::GUIActionAdapter& aa,  
		osg::Object* obj, osg::NodeVisitor* nv)  
	{  
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);  
		if (!viewer)return false;  
		switch (ea.getEventType())//判断事件，做出响应  
		{  
		case osgGA::GUIEventAdapter::KEYDOWN://ea.getEventType()获取到的如果是键盘事件  
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)//空格，控制鼠标到屏幕中间  
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
					sgy.readFaceData();                        //读入体素的位置坐标  -> data  [float,float,float]
					sgy.setUnitGeom(sgy.geom);                 // 将需要绘制成图元的体素在intensity中的坐标存在base中
					sgy.setShader(sgy.geom,sgy.camera,sgy.gr,vertSource2);				//添加数据，设置shader
					sgy.slicePos = 0;  //切面位置 
					sgy.sliceType = 0;  //侧面
					sgy.sliceIdensity = 1;  //不是切片
					root->insertChild(0,sgy.geom);					

					cout<<(clock()-start)*3<<"ms"<<endl;
				}  
				else if (ea.getKey() == '3')  
				{  
					clock_t start;
					start  = clock();

					cout<<"you press 3"<<endl;
					sgy.readFaceData();                        //读入体素的位置坐标  -> data  [float,float,float]
					sgy.setUnitGeom(sgy.geom);                 // 将需要绘制成图元的体素在intensity中的坐标存在base中
					sgy.setShader(sgy.geom,sgy.camera,sgy.sp, vertSource2);				//添加数据，设置shader
					sgy.slicePos = 0;  //切面位置 
					sgy.sliceType = 0;  //侧面
					sgy.sliceIdensity = 1;  //不是切片
					root->insertChild(0,sgy.geom);					

					cout<<(clock()-start)*3<<"ms"<<endl;
				}  
				else if (ea.getKey() == '4')  
				{ 
					clock_t start;
					start  = clock();

					cout<<"you press 4"<<endl;
					sgy.readFaceData();                        //读入体素的位置坐标  -> data  [float,float,float]
					sgy.setUnitGeom(sgy.geom);                 // 将需要绘制成图元的体素在intensity中的坐标存在base中
					sgy.setShader(sgy.geom,sgy.camera,sgy.cache, vertSource2);				//添加数据，设置shader
					sgy.slicePos = 0;  //切面位置 
					sgy.sliceType = 0;  //侧面
					sgy.sliceIdensity = 1;  //不是切片
					root->insertChild(0,sgy.geom);					

					cout<<(clock()-start)*3<<"ms"<<endl;
				}  
				else if (ea.getKey() == '5')  
				{  
					clock_t start;
					start  = clock();

					cout<<"you press 5"<<endl;  //显示整个数据体
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
	
					//初始化
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

					//绘制正面
					for(int i=0;i < sgy.CrossLine;i++){
						for (int n = 0; n < sgy.sampleNum; n++)
						{                         // 得到数据后直接放入intensity中	
							float tempValue = dataset1[i][n];									
							sgy.intensity->push_back(tempValue);  //得到强度
						}
					}
					if(sgy.InLine!=0)
					{  
						//绘制背面
						for(int i=0;i < sgy.CrossLine;i++){
							for (int n = 0; n<sgy.sampleNum; n++){
										//float tempValue = dataset2[i][n];									// 得到数据后直接放入intensity中	
										float tempValue = dataset2[i][n]；
										sgy.intensity->push_back(tempValue);  //得到强度
									}
						}						
						//绘制右侧面
						for(int i=0;i < sgy.InLine;i++){
							for (int n = 0; n<sgy.sampleNum; n++)
							{		
								//float tempValue = dataset3[i][n];									// 得到数据后直接放入intensity中	
								float tempValue = dataset3[i][n];	
								sgy.intensity->push_back(tempValue);  //得到强度
							}
						}
						//左侧面
						for(int i=0;i < sgy.InLine;i++){
							for (int n = 0; n < sgy.sampleNum; n++)
							{		
								//float tempValue = dataset4[i][n];									// 得到数据后直接放入intensity中	
								float tempValue = dataset4[i][n];
								sgy.intensity->push_back(tempValue);  //得到强度	
							}
						}
					}
					//sgy.ReadAllTrace();
					sgy.readFaceData();                        //读入体素的位置坐标  -> data  [float,float,float]
					sgy.setUnitGeom(sgy.geom);                 // 将需要绘制成图元的体素在intensity中的坐标存在base中
					sgy.setShader(sgy.geom,sgy.camera,sgy.intensity,vertSource2);				//添加数据，设置shader
					sgy.slicePos = 0;  //切面位置 
					sgy.sliceType = 0;  //侧面
					sgy.sliceIdensity = 1;  //不是切片
					root->insertChild(0,sgy.geom);					

					cout<<clock()-start<<"ms"<<endl;
				}  
/*				else if (ea.getKey() == '6')
				{
					cout<<"you press 6";
					sgy.geom = new osg::Geometry;
					//sgy.ReadTraceHeader("pg_lm.segy");
					sgy.ReadAllTrace();      //地震数据
					sgy.readFaceData();
					sgy.setUnitGeom(sgy.geom); 
					sgy.setShader(sgy.geom,sgy.camera);				//添加数据，设置shader
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