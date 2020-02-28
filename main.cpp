//
// Created by Lucas Gouveia on 19/05/2018.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "libCBTU.h"
using namespace std;
using namespace cv;


int main(int argc, char** argv)
{

	if (argc != 6)
	{
		printf("uso: ./tachCBTU  [Numero de Imagens] [Hora de Saida] [Minutos de Saida] [Segundos de Saida] [Trajeto] \n");
		return -1;
	}

	//Leitura do Arquivo de Trajeto e declaracao das variaveis de auxilio

	int reading;
	int indexread;
	float * data = new float[200];
	readTrajetos(data);
	reading = int(data[0]);
	int detecstations = 0;
	int ** wstations = new int * [reading];

	for (int index = 0; index<reading; ++index)
	{
		wstations[index] = new int[2];
	}

	float * stations = new float[reading];
	
	//Leitura das Estacoes

	for (int j = 0; j < reading; ++j) {
		stations[j] = data[2 * j + 2];
		indexread = 2 * j + 3;
	}

	//leitura dos trajetos

	reading = int(data[indexread]);
	int indexread2;
	int ** targets = new int *[reading];

	for (int index = 0; index<reading; ++index)
	{
		targets[index] = new int [2];
	}

	for (int j = 0; j < reading; ++j) {
		targets[j][0] = int(data[indexread + 3 * j + 2]);
		targets[j][1] = int(data[indexread + 3 * j + 3]);
		indexread2 = indexread + 3 * j + 4;
	}

	//leitura das precaucoes

	reading = int(data[indexread2]);
	int nprecs = reading;
	
	float ** precs = new float *[nprecs];

	for (int index = 0; index<nprecs; ++index)
	{
		precs[index] = new float [2];
	}

	for (int j = 0; j < nprecs; ++j) {
		precs[j][0] = data[indexread2 + 3 * j + 2];
		precs[j][1] = data[indexread2 + 3 * j + 3];
	}
	
	//Declaracao das Variaveis de Auxilio

	int nimg = stoi(argv[1], NULL);
	float horas = stof(argv[2], NULL);
	float minutos = stof(argv[3], NULL);
	float segundos = stof(argv[4], NULL);
	float hora_inicial = horas + minutos / 60 + segundos / 3600;
	int trajeto = stoi(argv[5], NULL);
	string nameim;
	int xysize = 0;
	int ymin = 1000000;
	int xmin;
	int imgmin;
	int ret[4];
	Mat input = imread("1.png");
	int ** xy = new int * [(nimg*input.cols + nimg * 10)];

	for (int index = 0; index<(nimg*input.cols + nimg * 10); ++index)
	{
		xy[index] = new int [2];
	}

	int ** sepics = new int *[nimg];

	for (int index = 0; index<(nimg); ++index)
	{
		sepics[index] = new int[2];
	}


	//Leitura das Imagens e Armazenamento em Vetor

	for (int i = 0; i < nimg; i++) {

		sepics[i][0] = xysize;
		nameim = to_string(i + 1) + ".png";
		input = imread(nameim);
		joinCharts(xy, input, xysize, ymin,ret,i);
		xysize = ret[1];
		sepics[i][1] = xysize-1;
		ymin = ret[0];
		xmin = ret[2];
		imgmin = ret[3];

	}

	//Calibracao vertical e horizontal dos dados coletados pelo tacografo

	regulaChart(xy, xysize, sepics, ymin, xmin, imgmin, nimg);
	
	detecstations = checkpoints(xy, xysize, wstations, detecstations);

	//Processamento dos dados (vmax, tempo_precs e vmed_precs)

	float ** data_prec = new float *[nprecs];

	for (int index = 0; index<nprecs; ++index)
	{
		data_prec[index] = new float [4];
	}


	float vmax;
	float height = input.rows;
	delete[] data;
	int * final = new int[1];
	final[0] = xysize;
	float * tempo = new float[xysize];
	float * velocidades = new float[xysize];
	float * deslocamentos = new float[xysize];
	float * posicao = new float[xysize];
	
	vmax = processData( trajeto, targets, stations, hora_inicial, ymin, height, xysize, nimg, xy,
			wstations, tempo, velocidades, deslocamentos, posicao, detecstations, final);

	processPrec(precs, nprecs, data_prec, xysize, xy, tempo, velocidades, posicao);

	imprimeData(vmax, data_prec, nprecs);

	return 0;
}