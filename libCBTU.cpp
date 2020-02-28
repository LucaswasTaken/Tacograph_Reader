//
// Created by Lucas on 10/11/17.
//

//
// Created by Lucas on 8/14/17.

#include "libCBTU.h"


void joinCharts(int ** vet, Mat mat, int xysize, int ymin,int ret[2],int i)
{
	Vec3b color;
	for (int j = 0; j < mat.cols; ++j) {
		for (int k = 0; k < mat.rows; ++k) {
			color = mat.at<Vec3b>(Point(j, k));
			if (color.val[2] == 255 && color.val[0] != 255)
			{
				vet[xysize][0] = xysize;
				vet[xysize][1] = mat.rows - k;

				if (vet[xysize][1]<ymin)
				{
					ymin = vet[xysize][1];
					ret[2] = xysize;
					ret[3] = i;
				}
				xysize += 1;
				break;

			}
		}

	}
	ret[0] = ymin;
	ret[1] = xysize;


}


void regulaChart(int ** xy, int xysize, int ** sepics, int ymin, int xmin, int imgmin, int nimg)
{
	int def;
	for (int l = 0; l < xysize; ++l) {
	
		xy[l][1] = xy[l][1] - ymin;

	}

	
	for (int i = imgmin+1; i < nimg; i++)
	{

		def = xy[sepics[i][0]][1]- xy[sepics[i-1][1]][1];

		if (def > 8)
		{
			cout << "Imagens Fora de ordem ou de baixa qualidade" << endl;
			def = 8;

		}

		if (def < -8)
		{
			cout << "Imagens Fora de ordem ou de baixa qualidade" << endl;
			def = -8;

		}

		for (int l = sepics[i][0]; l < sepics[i][1];  l++)
		{
			xy[l][1] = xy[l][1] - def;
			

			if ((xy[l][1] == xy[l + 1][1]) && (xy[l][1] == xy[l + 2][1])
				&& (xy[l][1] == xy[l + 3][1]) && (xy[l][1] == xy[l + 4][1]) && (xy[l][1] == xy[l + 5][1]) && (xy[l][1] == xy[l + 6][1])&& (xy[l][1] <3))
			{
				xy[l][1] = 0;
				xy[l+1][1] = 0;
				xy[l+2][1] = 0;
				xy[l+3][1] = 0;
				xy[l+4][1] = 0;
				xy[l+5][1] = 0;
				xy[l+6][1] = 0;

			}
			else if (xy[l][1] < 0)
			{
				xy[l][1] = 0;
			}
		}
	}

	
	for (int i = imgmin; i > 0; i--)
	{
		def = -xy[sepics[i][0]][1] + xy[sepics[i - 1][1]][1];

		if (def > 8)
		{
			cout << "Imagens de Fora de ordem ou de baixa qualidade" << endl;
			def = 8;

		}

		if (def < -8)
		{
			cout << "Imagens de Fora de ordem ou de baixa qualidade" << endl;
			def = -8;

		}

		for (int l = sepics[i-1][0]; l < sepics[i-1][1]; l++)
		{
			xy[l][1] = xy[l][1] - def;
			if ((xy[l][1] == xy[l + 1][1]) && (xy[l][1] == xy[l + 2][1])
				&& (xy[l][1] == xy[l + 3][1]) && (xy[l][1] == xy[l + 4][1]) && (xy[l][1] == xy[l + 5][1]) && (xy[l][1] == xy[l + 6][1]) && (xy[l][1] <3))
			{
				xy[l][1] = 0;
				xy[l + 1][1] = 0;
				xy[l + 2][1] = 0;
				xy[l + 3][1] = 0;
				xy[l + 4][1] = 0;
				xy[l + 5][1] = 0;
				xy[l + 6][1] = 0;

			}
			else if (xy[l][1] < 0)
			{
				xy[l][1] = 0;
			}
		}
	}
	
}


void readTrajetos(float * data)
{
	ifstream myReadFile;
	myReadFile.open("Dados_de_Trajeto.txt");
	char output[100];
	string outputs;
	int count = 0;
	if (myReadFile.is_open()) {

		myReadFile >> output;
		myReadFile >> output;
		myReadFile >> output;
		outputs = string(output);
		data[0] = stof(outputs);
		count += 1;

		for (int i = 0; i < data[0]; ++i) {
			myReadFile >> output;
			outputs = string(output);
			data[count] = stof(outputs);
			count += 1;
			myReadFile >> output;
			outputs = string(output);
			data[count] = stof(outputs);
			count += 1;
		}

		myReadFile >> output;
		myReadFile >> output;
		outputs = string(output);
		data[count] = stof(outputs);
		int stack = count;
		count += 1;
		for (int i = 0; i < data[stack]; ++i) {
			myReadFile >> output;
			outputs = string(output);
			data[count] = stof(outputs);
			count += 1;
			myReadFile >> output;
			outputs = string(output);
			data[count] = stof(outputs);
			count += 1;
			myReadFile >> output;
			myReadFile >> output;
			outputs = string(output);
			data[count] = stof(outputs);
			count += 1;
		}
		myReadFile >> output;
		myReadFile >> output;
		outputs = string(output);
		data[count] = stof(outputs);
		stack = count;
		count += 1;
		for (int i = 0; i < data[stack]; ++i) {
			myReadFile >> output;
			outputs = string(output);
			data[count] = stof(outputs);
			count += 1;
			myReadFile >> output;
			outputs = string(output);
			data[count] = stof(outputs);
			count += 1;
			myReadFile >> output;
			myReadFile >> output;
			outputs = string(output);
			data[count] = stof(outputs);
			count += 1;
		}

	}

	myReadFile.close();

}


int checkpoints(int ** xy, int xysize, int ** wstations, int detecstations)
{
	int verifyentrada = 0;
	int countst = 0;

	for (int l = 0; l < xysize; l++)
	{

		if ((xy[l][1] == 0) && (xy[l][1] == xy[l + 1][1]) && (xy[l][1] == xy[l + 2][1])
			&& (xy[l][1] == xy[l + 3][1]) && (xy[l][1] == xy[l + 4][1]) && (xy[l][1] == xy[l + 5][1]) && (xy[l][1] == xy[l + 6][1])
			&& (xy[l][1] == xy[l + 7][1]) && (xy[l][1] == xy[l + 8][1]) && (xy[l][1] == xy[l + 9][1]) && (xy[l][1] == xy[l + 10][1])
			&& (verifyentrada == 0))
		{
			wstations[countst][0] = l;
			verifyentrada = 1;
		}
		else if (((xy[l][1] > 0) && (verifyentrada ==1))||(l==xysize-1) && (verifyentrada == 1))
		{
			wstations[countst][1] = l;
			verifyentrada = 0;
			countst = countst + 1;
			detecstations = detecstations + 1;
		}
	}
	return detecstations;
}


float processData( int trajeto, int ** targets, float * stations, float hora_inicial, int ymin, float total_height, int xysize, int nimg, int ** xy,
				   int ** wstations, float * tempo, float * velocidades, float * deslocamentos, float * posicao, int detecstations, int * final)
{
	float vmed = 0;
	float vmax = 0;
	float nimfloat = float(nimg);
	float xysizefloat = float(xysize-1);
	int countstation = targets[trajeto - 1][0];
	cout << countstation << endl;
	int wcountstation = 1;
	float propstation;


	for (int l = 0; l <xysize; ++l) {
		
		//Calculo do Tempo

		tempo[l] = float(xy[l][0]);
		tempo[l] = hora_inicial + tempo[l] * (nimfloat*5.0 / 60.0) / xysizefloat;


		//Calculo da Velocidade

		velocidades[l] = 150 * (xy[l][1]) / (total_height - ymin);

		//Determinacao da Velocidade M�xima

		if (velocidades[l]>vmax)
			vmax = velocidades[l];

		//Calculo dos Deslocamentos a partir da velocidade media

		if (l != 0)
			vmed = (vmed*(l)+velocidades[l]) / (l + 1);
		else                                                                                                                                                                                                                      
			vmed = velocidades[0];
		deslocamentos[l] = vmed * (tempo[l] - hora_inicial);

		//Calculo das posi��es
		if (l == 0)
		{
			posicao[l] = stations[(targets[trajeto - 1][0] - 1)];
		}
		else
		{
			if (targets[trajeto - 1][0] < targets[trajeto - 1][1])
				posicao[l] = posicao[l-1] + velocidades[l-1]*(tempo[l]-tempo[l-1]);
			else
				posicao[l] = posicao[l-1] - velocidades[l - 1] * (tempo[l] - tempo[l - 1]);
		}
		
		//Verificacaoo da estacao limite

		if ((targets[trajeto - 1][0] < targets[trajeto - 1][1]) && (posicao[l] >= stations[(targets[trajeto - 1][1] - 1)]))
		{
			cout << "saiu antes" << endl;
			final[0] = l;
			return vmax;
		}
		if ((targets[trajeto - 1][0] > targets[trajeto - 1][1]) && (posicao[l] <= stations[(targets[trajeto - 1][1] - 1)]))
		{
			cout << "saiu antes" << endl;
			final[0] = l;
			return vmax;
		}
		
		
		//Verificacaoo dos checkpoints
		
		if ((detecstations > 1)&&(wcountstation<detecstations))
		{
			
			if ((targets[trajeto - 1][0] < targets[trajeto - 1][1]) && (l > wstations[wcountstation][0]))
			{
				if (posicao[l] >= stations[countstation + 1])
				{
					propstation = (stations[countstation] - posicao[l])
						/ (wstations[wcountstation][0] - wstations[wcountstation - 1][1]);
					for (int i = wstations[wcountstation - 1][1]; i < wstations[wcountstation][0]; i++)
					{
						posicao[i] = posicao[i] + propstation*(i - wstations[wcountstation - 1][1]);
						tempo[i] = float(xy[i][0]);
						tempo[i] = hora_inicial + tempo[i] * (nimfloat*5.0 / 60.0) / xysizefloat;
						velocidades[i] = 150 * (xy[i][1]) / (total_height - ymin);
					}
					for (int i = wstations[wcountstation][0]; i < wstations[wcountstation][1]+1; i++)
					{
						posicao[i] = stations[countstation];
						tempo[i] = float(xy[i][0]);
						tempo[i] = hora_inicial + tempo[i] * (nimfloat*5.0 / 60.0) / xysizefloat;
						velocidades[i] = 150 * (xy[i][1]) / (total_height - ymin);
					}
				}
				else
				{
					propstation = (stations[countstation] - posicao[l])
						/ (wstations[wcountstation][0] - wstations[wcountstation - 1][1]);
					for (int i = wstations[wcountstation - 1][1]; i < wstations[wcountstation][0]; i++)
					{
						posicao[i] = posicao[i] + propstation*(i - wstations[wcountstation - 1][1]);
						tempo[i] = float(xy[i][0]);
						tempo[i] = hora_inicial + tempo[i] * (nimfloat*5.0 / 60.0) / xysizefloat;
						velocidades[i] = 150 * (xy[i][1]) / (total_height - ymin);
					}
					for (int i = wstations[wcountstation][0]; i < wstations[wcountstation][1]+1; i++)
					{
						posicao[i] = stations[countstation];
						tempo[i] = float(xy[i][0]);
						tempo[i] = hora_inicial + tempo[i] * (nimfloat*5.0 / 60.0) / xysizefloat;
						velocidades[i] = 150 * (xy[i][1]) / (total_height - ymin);
					}
				}
				l = wstations[wcountstation][1];
				wcountstation = wcountstation + 1;
				countstation = countstation + 1;
			}

			if ((targets[trajeto - 1][0] > targets[trajeto - 1][1]) && (l > wstations[wcountstation][0]))
			{
				if (posicao[l] >= stations[countstation])
				{
					propstation = (stations[countstation] - posicao[l])
						/ (wstations[wcountstation][0] - wstations[wcountstation - 1][1]);
					for (int i = wstations[wcountstation - 1][1]; i < wstations[wcountstation][0]; i++)
					{
						posicao[i] = posicao[i] + propstation*(i - wstations[wcountstation - 1][1]);
						tempo[i] = float(xy[i][0]);
						tempo[i] = hora_inicial + tempo[i] * (nimfloat*5.0 / 60.0) / xysizefloat;
						velocidades[i] = 150 * (xy[i][1]) / (total_height - ymin);
					}
					for (int i = wstations[wcountstation][0]; i < wstations[wcountstation][1]+1; i++)
					{
						posicao[i] = stations[countstation];
						tempo[i] = float(xy[i][0]);
						tempo[i] = hora_inicial + tempo[i] * (nimfloat*5.0 / 60.0) / xysizefloat;
						velocidades[i] = 150 * (xy[i][1]) / (total_height - ymin);
					}
				}
				else
				{
					propstation = (stations[countstation] - posicao[l])
						/ (wstations[wcountstation][0] - wstations[wcountstation - 1][1]);
					for (int i = wstations[wcountstation - 1][1]; i < wstations[wcountstation][0]; i++)
					{
						posicao[i] = posicao[i] + propstation*(i - wstations[wcountstation - 1][1]);
						tempo[i] = float(xy[i][0]);
						tempo[i] = hora_inicial + tempo[i] * (nimfloat*5.0 / 60.0) / xysizefloat;
						velocidades[i] = 150 * (xy[i][1]) / (total_height - ymin);
					}
					for (int i = wstations[wcountstation][0]; i < wstations[wcountstation][1]+1; i++)
					{
						posicao[i] = stations[countstation];
						tempo[i] = float(xy[i][0]);
						tempo[i] = hora_inicial + tempo[i] * (nimfloat*5.0 / 60.0) / xysizefloat;
						velocidades[i] = 150 * (xy[i][1]) / (total_height - ymin);
					}
				}
				l = wstations[wcountstation][1];
				wcountstation = wcountstation + 1;
				countstation = countstation - 1;
			}
		}
	}
	

	return vmax;

}


void processPrec(float ** precs, int nprecs, float ** data_prec, int xysize,  int ** xy, float * tempo, float * velocidades, float * posicao)
{

	float ** verifyprec = new float *[nprecs];
	float enters = 0;
	float exits = 0;
	int verifyex = 0;

	for (int index = 0; index<nprecs; ++index)
	{
		verifyprec[index] = new float[2];
	}

	int countprec = 0;

	for (int l = 0; l <xysize; ++l) {

		//Precaucoes
		if (countprec < nprecs)
		{
			//Entrada em Estacao
			if ((verifyex == 0) && (xy[l][1] == 0) && (xy[l][1] == xy[l + 1][1]) && (xy[l][1] == xy[l + 2][1])
				&& (xy[l][1] == xy[l + 3][1]) && (xy[l][1] == xy[l + 4][1]) && (xy[l][1] == xy[l + 5][1]) && (xy[l][1] == xy[l + 6][1])
				&& (xy[l][1] == xy[l + 7][1]) && (xy[l][1] == xy[l + 8][1]) && (xy[l][1] == xy[l + 9][1]) && (xy[l][1] == xy[l + 10][1])
				&& (verifyprec[countprec][0] == 1))
			{
				enters = tempo[l];
				verifyex = 1;
			}

			//Saida da Estacao
			else if ((verifyex == 1) && (xy[l][1] > 0))
			{
				exits = tempo[l];
				verifyex = 0;
			}


			//Velocidade Maxima na Precaucao
			if ((verifyprec[countprec][0] == 1) && (data_prec[countprec][3] < velocidades[l]))
				data_prec[countprec][3] = velocidades[l];


			//Dados da precaucao
			if ((posicao[l] > precs[countprec][0]) && (posicao[l] < precs[countprec][1])
				&& (verifyprec[countprec][0] != 1) && (verifyprec[countprec][1] != 1))
			{
				data_prec[countprec][0] = tempo[l];
				data_prec[countprec][3] = 0;
				verifyprec[countprec][0] = 1;
			}


			else if (((posicao[l] < precs[countprec][0] && posicao[l] <= precs[countprec][1])
				|| (posicao[l] > precs[countprec][0] && posicao[l] > precs[countprec][1]))
				&& (verifyprec[countprec][1] != 1) && (verifyprec[countprec][0] == 1))
			{
				data_prec[countprec][1] = tempo[l];
				data_prec[countprec][2] = abs(precs[countprec][1] - precs[countprec][0])
					/ (data_prec[countprec][1] - data_prec[countprec][0] - (exits - enters));
				verifyprec[countprec][1] = 1;
				countprec += 1;
				enters = 0;
				exits = 0;
			}
		}
	}


	for (int index = 0; index<nprecs; ++index)
	{
		delete[] verifyprec[index];
	}
	delete[] verifyprec;
}


void imprimeData(float vmax, float ** data_prec, int nprecs)
{

	ofstream myfile;
	myfile.open("output.txt");
	myfile << "Velocidade Maxima - " << int(vmax)+1 << endl;
	int tempohi;
	float tempomfi;
	int tempomi;
	float temposfi;
	int temposi;
	int tempohf;
	float tempomff;
	int tempomf;
	float temposff;
	int temposf;
	float tempototal;
	int tempototalh;
	float tempototalmin;
	int tempototalmini;
	float tempototalseg;
	int tempototalsegi;

	for (int i = 0; i < nprecs; ++i) {

		tempototal = data_prec[i][1] - data_prec[i][0];
		tempototalh = int(tempototal);
		tempototalmin = 60*(tempototal - float(tempototalh));
		tempototalmini = int(tempototalmin);
		tempototalseg = 60*(tempototalmin - float(tempototalmini));
		tempototalsegi = int(tempototalseg);

		tempohi = int(data_prec[i][0]);
		tempomfi = 60*(data_prec[i][0] - float(tempohi));
		tempomi = int(tempomfi);
		temposfi = 60 * (tempomfi-float(tempomi));
		temposi = int(temposfi);
		tempohf = int(data_prec[i][1]);
		tempomff = 60 * (data_prec[i][1] - float(tempohf));
		tempomf = int(tempomff);
		temposff = 60 * (tempomff - float(tempomf));
		temposf = int(temposff);

		myfile << "Prec - " << i + 1 << " Vmed - " << data_prec[i][2]
			<< " Vmax - " << int(data_prec[i][3])+1
			<< " Chegada- " << tempohi << ":" << tempomi << ":" << temposi
			<< " Saida - " << tempohf << ":" << tempomf << ":" << temposf
			<< " Tempo - " << tempototalh << ":" << tempototalmini << ":" << tempototalsegi << endl;
	}
	myfile.close();
}