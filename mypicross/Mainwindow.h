#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Mainwindow.h"
#include <qlcdnumber.h>
#include <qlabel.h>
#include <qfile.h>
#include <qtimer.h>
#include <opencv2\opencv.hpp>
using namespace cv;
class Mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	Mainwindow(QWidget *parent = Q_NULLPTR);
	void init();
	void keyPressEvent(QKeyEvent *k);
	QImage Mat2QImage(Mat const& src);
	int cvAdd4cMat_q(Mat &dst, Mat &scr, double scale);
	
	void addFrame(int x, int y, int stat);
	void removeFrame(int x, int y, int stat);
	void setUpNum(int x);
	void setDownNum(int y);
	void detectCompletion();

		 
public slots:
	void start();
	void loadImg();
	void setDifficulty(int);
	void updateTime();

private:
	Ui::MainwindowClass ui;
	int x = 0;
	int y = 0;
	QLabel* chessBoard[10][10];
	QLCDNumber* numBoardUp[5][10];
	QLCDNumber* numBoardDown[10][5];
	Mat bgBoard[10][10];
	Mat outlinedbgBoard[10][10];
	Mat coverBoard[10][10];
	Mat outlinedCoverBoard[10][10];
	Mat crossBoard[10][10];
	int statBoard[10][10];// 0:cover   1:bg    2:cross
	bool mask[10][10];
	Mat src, cover, frame, cross, outline;
	QString filePath;
	int blockNum = 90;
	QFile rec;
	double startTime;
	int timee = 0;
	QTimer *timer;
};
