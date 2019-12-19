#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>
using namespace std;

double function(double x, double y)
{
	double func = cos(x) * cos(y);
	return func;
}

double random()
{
	double r;
	r = rand() % 10000 / 1000. - 7.;
	if (r < -2.)
	{
		while (r < -2)
			r += 1;
	}
	if (r > 2.)
	{
		while (r > 2)
			r -= 1;
	}
	return r;
}

void mutation(double X[4], double Y[4])
{
	double delta = 0.05;
	int section;
	section = rand() % 4;
	double population;
	population = rand() % 2;
	if (population <= 0.5)
		if (population <= 0.5)
			X[section] += delta;
		else
			X[section] -= delta;
	else
		if (population <= 0.5)
			Y[section] += delta;
		else
			Y[section] -= delta;
}

void Ghenetic_Algorithm()
{
	int N = 1;
	double X[4], Y[4], func[4], probability[4];
	double func_average = 0.;
	double func_max;
	double rand_probability;
	double sum_probability = 0.;
	int weak_ghen, strong_ghen;
	ofstream out;
	X[0] = random();
	Y[0] = random();
	func[0] = function(X[0], Y[0]);
	X[1] = random();
	Y[1] = random();
	func[1] = function(X[1], Y[1]);
	X[2] = random();
	Y[2] = random();
	func[2] = function(X[2], Y[2]);
	X[3] = random();
	Y[3] = random();
	func[3] = function(X[3], Y[3]);
	cout << "      X          Y        FIT      max_fit   average_fit" << endl;
	cout << "--------------------------------------------------------";
	for (int u = 0; u < 10; u++)
	{
		func_average = 0;
		for (int i = 0; i < 4; i++)
		{
			func_average += func[i];
		}
		func_average /= 4;
		for (int i = 0; i < 4; i++)
		{
			sum_probability += func[i];
		}
		for (int i = 0; i < 4; i++)
		{
			probability[i] = func[i] / sum_probability;
			probability[i] = 1 - probability[i];
		}
		rand_probability = rand() % (int)(probability[0] + probability[1] + probability[2] + probability[3]) + 1;
		for (int i = 0; i < 4; i++)
		{
			if (rand_probability > probability[i])
			{
				probability[i + 1] = probability[i] + probability[i + 1];
			}
			if (rand_probability <= probability[i])
			{
				weak_ghen = i;
			}
		}
		func_max = -999999;
		for (int i = 0; i < 4; i++)
		{
			if (i == weak_ghen)
			{
				continue;
			}
			else
			{
				if (func_max < func[i])
				{
					func_max = func[i];
					strong_ghen = i;
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			cout << endl;
			if (X[i] < 0)
				cout << fixed << setprecision(6) << " |" << X[i];
			else
				cout << fixed << setprecision(6) << " | " << X[i];
			if (Y[i] < 0)
				cout << fixed << setprecision(6) << " |" << Y[i];
			else
				cout << fixed << setprecision(6) << " | " << Y[i];
			if (func[i] < 0)
				cout << fixed << setprecision(6) << " |" << func[i];
			else
				cout << fixed << setprecision(6) << " | " << func[i];

		}
		cout << " | " << fixed << setprecision(6) << func_max << " | " << fixed << setprecision(6) << func_average;
		cout << "\n--------------------------------------------------------";
		cout << endl;
		N++;
		int j = 0;
		double population[3][2] = { 0, 0, 0,
							 0, 0, 0 };
		for (int i = 0; i < 4; i++)
		{
			if (i == strong_ghen)
			{
				population[0][0] = X[i];
				population[0][1] = Y[i];
			}
			else
				if (i == weak_ghen)
				{
					j += 1;
					population[j][0] = X[i];
					population[j][1] = Y[i];
				}
		}
		X[0] = population[1][0];
		X[1] = population[2][0];
		X[3] = population[0][0];
		X[2] = population[2][0];
		Y[0] = population[2][1];
		Y[1] = population[0][1];
		Y[2] = population[1][1];
		Y[3] = population[2][1];
		for (int i = 0; i < 4; i++)
		{
			func[i] = function(X[i], Y[i]);
		}
		double p;
		p = rand() % 100;
		if (p <= 25)
		{
			mutation(X, Y);
		}
		else
			continue;
		func_average = 0;
	}
	func_average = 0;
	for (int i = 0; i < 4; i++)
	{
		func_average += func[i];
	}
	func_average /= 4;
}

int main()
{
	ofstream out;
	out.open("../out.txt");
	Ghenetic_Algorithm();
	system("pause");
	return 0;
}
