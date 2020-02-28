//
// Created by Lucas on 10/11/17.
//

#ifndef tachCBTU_LIBCBTU_H
#define tachCBTU_LIBCBTU_H
#endif //CONTADOR_LIBCBTU_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

using namespace cv;
void joinCharts(int **vet, Mat mat, int xysize, int ymin,int ret[2], int i);


void regulaChart(int ** xy, int xysize, int ** sepics, int ymin, int xmin, int imgmin, int nimg);


void readTrajetos(float * data);


int checkpoints(int ** xy, int xysize, int ** wstations, int detecstations);


float processData( int trajeto, int ** targets, float * stations, float hora_inicial, int ymin, float total_height, int xysize, int nimg, int ** xy,
				   int ** wstations, float * tempo, float * velocidades, float * deslocamentos, float * posicao, int detecstations, int * final);

void processPrec(float ** precs, int nprecs, float ** data_prec, int xysize,  int ** xy, float * tempo, float * velocidades, float * posicao);


void imprimeData(float vmax, float ** data_prec, int nprecs);