//接下来要填的坑：1 完成特效  2 bg图片裁剪框   3 美化ui  4 确定解的唯一性

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <cstring>
#include <QKeyEvent>
#include <QLabel>
#include <qlcdnumber.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <qtextstream.h>
#include <qtimer.h>
using namespace cv;
using namespace std;
Mainwindow::Mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init(); //初始化，为棋盘申请内存，设置背景图，初始化计数器
	timer = new QTimer(this);
	connect(ui.gameStart, SIGNAL(clicked(bool)), this, SLOT(start()));
	connect(ui.imgSelection, SIGNAL(clicked(bool)), this, SLOT(loadImg()));
	connect(ui.difficulty, SIGNAL(valueChanged(int)), this, SLOT(setDifficulty(int)));
	connect(timer, SIGNAL(timeout()),this,SLOT(updateTime()));
}
void Mainwindow::init() {
	cover = imread("03-landscape.png");

	cover = cover(Rect(200, 0, 500, 500));
	frame = imread("frame.png", -1);
	cross = imread("cross.png", -1);
	outline = imread("outline.png", -1);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			chessBoard[i][j] = new QLabel;
			coverBoard[i][j] = cover(Rect(50 * j, 50 * i, 50, 50));
			coverBoard[i][j].copyTo(outlinedCoverBoard[i][j]);
			cvAdd4cMat_q(outlinedCoverBoard[i][j], outline, 1.0);
			chessBoard[i][j]->setParent(ui.table);
			chessBoard[i][j]->setGeometry(50 * j, 50 * i, 50, 50);
			chessBoard[i][j]->setPixmap(QPixmap::fromImage(Mat2QImage(coverBoard[i][j])));
		}
	}

	//初始化计数器
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 10; ++j) {
			numBoardUp[i][j] = new QLCDNumber;
			numBoardUp[i][j]->setParent(ui.numUp);
			numBoardUp[i][j]->setGeometry(50 * j, 30 * i, 50, 30);
			numBoardUp[i][j]->display(0);
			numBoardUp[i][j]->setSegmentStyle(QLCDNumber::Flat);
			numBoardUp[i][j]->show();
		}
	}
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 5; ++j) {
			numBoardDown[i][j] = new QLCDNumber;
			numBoardDown[i][j]->setParent(ui.numDown);
			numBoardDown[i][j]->setGeometry(40 * j, 50 * i, 40, 50);
			numBoardDown[i][j]->display(0);
			numBoardDown[i][j]->setSegmentStyle(QLCDNumber::Flat);
			numBoardDown[i][j]->show();
		}
	}
}

void Mainwindow::keyPressEvent(QKeyEvent *k)
{
	if (k->key() == Qt::Key_A)
	{
		removeFrame(x, y, statBoard[x][y]);
		y = (y + 9) % 10;
		addFrame(x, y, statBoard[x][y]);
	}
	else if (k->key() == Qt::Key_D)
	{
		removeFrame(x, y, statBoard[x][y]);
		y = (y + 1) % 10;
		addFrame(x, y, statBoard[x][y]);
	}
	else if (k->key() == Qt::Key_W)
	{
		removeFrame(x, y, statBoard[x][y]);
		x = (x + 9) % 10;
		addFrame(x, y, statBoard[x][y]);
	}
	else if (k->key() == Qt::Key_S)
	{
		removeFrame(x, y, statBoard[x][y]);
		x = (x + 1) % 10;
		addFrame(x, y, statBoard[x][y]);
	}
	else if (k->key() == Qt::Key_K) {
		if (statBoard[x][y] == 1) {
			statBoard[x][y] = 0;
			chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(outlinedCoverBoard[x][y])));
		}
		else {
			statBoard[x][y] = 1;
			chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(outlinedbgBoard[x][y])));
		}
		detectCompletion();
	}
	else if (k->key() == Qt::Key_L) {
		if (statBoard[x][y] == 2) {
			statBoard[x][y] = 0;
			chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(coverBoard[x][y])));
			addFrame(x, y, statBoard[x][y]);
		}
		else {
			statBoard[x][y] = 2;
			chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(crossBoard[x][y])));
			addFrame(x, y, statBoard[x][y]);
		}
	}
}

void Mainwindow::start() {
	timee = 0;
	timer->start(1000);
	//设置底图
	if (!filePath.length()) src = imread("default.jpg"); //使用默认图片
	else src = imread(filePath.toStdString());
	if (src.cols < 500 || src.rows < 500) {  //放大尺寸小于500*500的图片
		double coeff = 500.0 / min(src.cols, src.rows);
		cv::resize(src, src, Size(src.cols*coeff, src.rows*coeff));
	}
	Mat bg = src(Rect(0, 0, 500, 500));
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			chessBoard[i][j]->setPixmap(QPixmap::fromImage(Mat2QImage(outlinedCoverBoard[i][j])));
			bgBoard[i][j] = bg(Rect(50 * j, 50 * i, 50, 50));
			bgBoard[i][j].copyTo(outlinedbgBoard[i][j]);
			cvAdd4cMat_q(outlinedbgBoard[i][j], outline, 1.0);
			outlinedCoverBoard[i][j].copyTo(crossBoard[i][j]);
			cvAdd4cMat_q(crossBoard[i][j], cross, 1.0);
			statBoard[i][j] = 0;
		}
	}

	addFrame(0, 0, 0); //左上角一格加框
	x = y = 0;
	
	memset(mask, 0, sizeof(mask));
	srand((unsigned int)time(NULL));
	for (int i = 0; i < blockNum; i++) {
		int r = rand() % 100;
		mask[r / 10][r % 10] = true;
	}

	for (int i = 0; i < 10; ++i) {
		setUpNum(i);
		setDownNum(i);
	}
	
	rec.setFileName("rec.txt");
	rec.open(QIODevice::ReadWrite);
	int line = 0;
	while (!rec.atEnd()) {
		if(line == ui.difficulty->value()){
			QString onecount = rec.readLine();
			ui.record->display(onecount.mid(0,onecount.length()-1));
			break;
		}
		else {
			QString temp = rec.readLine();
		}
		line++;
	}
	rec.close();
}

void Mainwindow::loadImg() {
	filePath = QFileDialog::getOpenFileName(this, "选择图片");
	//src = imread(filePath.toStdString());
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			chessBoard[i][j]->setPixmap(QPixmap::fromImage(Mat2QImage(coverBoard[i][j])));
			statBoard[i][j] = 0;
			x = 0;
			y = 0;
		}
	}
}

void Mainwindow::addFrame(int x, int y, int stat) {
	if (stat == 0) {
		Mat temp;
		outlinedCoverBoard[x][y].copyTo(temp);
		cvAdd4cMat_q(temp, frame, 1.0);
		chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(temp)));
	}
	else if (stat == 1) {
		Mat temp;
		outlinedbgBoard[x][y].copyTo(temp);
		cvAdd4cMat_q(temp, frame, 1.0);
		chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(temp)));
	}
	else {
		Mat temp;
		crossBoard[x][y].copyTo(temp);
		cvAdd4cMat_q(temp, frame, 1.0);
		chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(temp)));
	}
}

void Mainwindow::removeFrame(int x, int y, int stat) {
	if (stat == 0) {
		chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(outlinedCoverBoard[x][y])));
	}
	else if (stat == 1) {
		chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(outlinedbgBoard[x][y])));
	}
	else {
		chessBoard[x][y]->setPixmap(QPixmap::fromImage(Mat2QImage(crossBoard[x][y])));
	}

}

void Mainwindow::setUpNum(int x) {
	vector<int> v;
	v.clear();
	int cnt = 0;
	for (int i = 0; i < 10; i++) {
		if (!mask[i][x]) {
			if (cnt) {
				v.push_back(cnt);
				cnt = 0;
			}
		}
		else {
			cnt++;
		}
	}
	if (cnt) v.push_back(cnt);
	int times = v.size();
	for (int i = 0; i < times; i++)
	{
		numBoardUp[4-i][x]->display(v.back());
		v.pop_back();
	}
	for (int i = times; i < 5; i++)
	{
		numBoardUp[4 - i][x]->setVisible(false);
	}
}

void Mainwindow::setDownNum(int y) {
	vector<int> v;
	v.clear();
	int cnt = 0;
	for (int i = 0; i < 10; i++) {
		if (!mask[y][i]) {
			if (cnt) {
				v.push_back(cnt);
				cnt = 0;
			}
		}
		else {
			cnt++;
		}
	}
	if (cnt) v.push_back(cnt);
	int times = v.size();
	for (int i = 0; i < times; i++)
	{
		numBoardDown[y][4-i]->display(v.back());
		v.pop_back();
	}
	for (int i = times; i < 5; i++)
	{
		numBoardDown[y][4 - i]->setVisible(false);
	}
}

QImage Mainwindow::Mat2QImage(cv::Mat const& src)
{
	cv::Mat temp; // make the same cv::Mat
	cvtColor(src, temp, CV_BGR2RGB); // cvtColor Makes a copt, that what i need
	QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	dest.bits(); // enforce deep copy, see documentation
				 // of QImage::QImage ( const uchar * data, int width, int height, Format format )
	return dest;
}

int Mainwindow::cvAdd4cMat_q(Mat &dst, Mat &scr, double scale)
{
	if (dst.channels() != 3 || scr.channels() != 4)
	{
		return true;
	}
	if (scale < 0.01)
		return false;
	std::vector<cv::Mat>scr_channels;
	std::vector<cv::Mat>dstt_channels;
	split(scr, scr_channels);
	split(dst, dstt_channels);
	CV_Assert(scr_channels.size() == 4 && dstt_channels.size() == 3);

	if (scale < 1)
	{
		scr_channels[3] *= scale;
		scale = 1;
	}
	for (int i = 0; i < 3; i++)
	{
		dstt_channels[i] = dstt_channels[i].mul(255.0 / scale - scr_channels[3], scale / 255.0);
		dstt_channels[i] += scr_channels[i].mul(scr_channels[3], scale / 255.0);
	}
	merge(dstt_channels, dst);
	return true;
}

void Mainwindow::detectCompletion() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
		{
			if (mask[i][j]) {
				if (statBoard[i][j] != 1) {
					return;
				}
			}
			if (!mask[i][j]) if (statBoard[i][j] == 1) return;
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
		{
			chessBoard[i][j]->setPixmap(QPixmap::fromImage(Mat2QImage(bgBoard[i][j])));
		}
	}
	timer->stop();
	rec.setFileName("rec.txt");
	rec.open(QIODevice::ReadOnly);
	QTextStream stream(&rec);
	QString strAll = rec.readAll();
	QStringList strList = strAll.split('\n');	
	rec.close();
	rec.open(QIODevice::WriteOnly);
	for (int i = 0; i < strList.count(); i++)
	{
		if (i == ui.difficulty->value()) {
			QString temp = strAll.at(i);
			temp.replace(0, temp.length(), QString::fromStdString(to_string(timee / 60)) + ":" + QString::fromStdString(to_string(timee % 60)));
			stream << temp << '\n';
		}
		else
		{
			stream << strList.at(i) << '\n';
		}
	}
	rec.close();
}

void Mainwindow::setDifficulty(int num) {
	switch (num) {
		case 0:
			blockNum = 105;
			break;
		case 1:
			blockNum = 80;
			break;
		case 2:
			blockNum = 60;
			break;
		default:
			blockNum = 90;
	}

}

void Mainwindow::updateTime() {
	timee++;
	int minute = timee / 60;
	int second = timee % 60;
	QString temp = QString::number(minute) + ":";
	if (second < 10) temp += "0";
	temp += QString::number(second);
	ui.timeRecorder->display(temp);
}
