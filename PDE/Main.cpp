#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>
#include <GL/glut.h>
#include "Gauss.h"
#include "Function.h"
#include "PDE.h"
#include "Integral.h"
#define SIZE 999
using namespace std;


void displayText(GLdouble x, GLdouble y, GLdouble r, GLdouble g, GLdouble b, string str)
{
	glColor3d(r, g, b);
	glRasterPos2d(x, y);
	for (size_t i = 0; i < str.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
	}
}

void displayGraph()
{
	GLdouble a, b, c, d;
	vector <GLdouble> A, B, C, D;
	int count = 0;
	ifstream file1("ValueU.txt", ios::in);
	ifstream file2("ValueX.txt", ios::in);
	ifstream file3("ValueAB.txt", ios::in);
	ifstream file4("MaxU.txt", ios::in);
	if (file3.is_open() && file4.is_open() && file1.is_open() && file2.is_open())
	{

		while (!file3.eof() && !file4.eof() && !file1.eof() && !file2.eof())
		{
			string str1, str2;
			string::size_type s1;
			getline(file3, str1);
			getline(file4, str2);
			a = (GLdouble) stod(str1, &s1);
			b = (GLdouble) stod(str1.substr(s1 + 1));
			c = (GLdouble) ceil(stod(str2, &s1) * 10) / 10;

			C.resize(SIZE);
			D.resize(SIZE);

			for (int i = 1; i <= SIZE; i++)
			{
				C[i - 1] = a + i * (b - a) / (SIZE + 1);
				
				D[i - 1] = (GLdouble)F(C[i - 1]);
				
			}
			d = D[0];
			for (int i = 1; i < SIZE; i++)
			{
				if (d < D[i])
				{
					d = D[i];
				}
			}
			d = (GLdouble) ceil(d * 10) / 10;

			glClear(GL_COLOR_BUFFER_BIT);
			glColor3d(1.0, 1.0, 1.0);


			glColor3d(0.0, 0.0, 1.0);
			glPointSize(5);
			glBegin(GL_POINTS);
			{
				glVertex2d(0.0, 0.525);
				glVertex2d(1.0, 0.525);
			}
			glEnd();
			glColor3d(0.0, 0.0, 0.0);
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
			{
				glVertex2d(0.0, 1.0);
				glVertex2d(0.0, 0.05);
				glVertex2d(1.0, 0.05);
				glVertex2d(1.0, 1.0);
			}
			glEnd();
			glColor3d(0.0, 0.0, 0.0);
			glLineWidth(2);
			glBegin(GL_LINES);
			{
				glVertex2d(0.0, 0.525);
				glVertex2d(1.0, 0.525);
			}
			glEnd();
			glColor3d(0.0, 0.0, 0.0);
			glLineWidth(2);
			glBegin(GL_LINES);
			{
				glVertex2d(a / (a - b), 0.05);
				glVertex2d(a / (a - b), 1.0);
			}
			glEnd();
			glColor3d(0.0, 0.0, 0.0);
			glLineWidth(2);
			glBegin(GL_LINES);
			{
				for (GLdouble i = 0.05; i <= 1; i += 0.05)
				{
					glVertex2d(i, 0.53);
					glVertex2d(i, 0.52);
				}
				for (GLdouble i = 0.0975; i <= 0.9525; i += 0.0475)
				{
					glVertex2d(a / (a - b) + 0.005, i);
					glVertex2d(a / (a - b) - 0.005, i);
				}
			}
			glEnd();
			for (int i = 0; i <= 20; i++)
			{
				char buffer[9];
				int j = snprintf(buffer, 9, "%.2f", a + 0.05 * i * (b - a));
				if (j >= 0 && j < 9)
				{
					displayText((GLdouble) 0.05 * i - 0.0065, 0.01, 0.0, 0.0, 0.0, buffer);
				}
			}

			/*for (GLdouble i = 1; i <= 10; i++)
			{
				char buffer[9];
				int j = snprintf(buffer, 9, "%.1f", -a - 0.1 * i * (b - a));
				if (j >= 0 && j < 9)
				{
					displayText(-0.05 * i + 0.49, 0.01, 0.0, 0.0, 0.0, buffer);
				}
			}*/
			for (int i = 0; i <= 10; i++)
			{
				int j;
				char buffer[9];
				if (c > d)
				{
					j = snprintf(buffer, 9, "%.2f", 0.1 * i * c);
				}
				else
				{
					j = snprintf(buffer, 9, "%.2f", 0.1 * i * d);
				}
				if (j >= 0 && j < 9)
				{
					displayText(-0.07, (GLdouble) 0.52 + 0.0475 * i, 0.0, 0.0, 0.0, buffer);
				}
			}
			for (int i = 1; i <= 10; i++)
			{
				int j;
				char buffer[9];
				if (c > d)
				{
					j = snprintf(buffer, 9, "%.2f", -0.1 * i * c);
				}
				else
				{
					j = snprintf(buffer, 9, "%.2f", -0.1 * i * d);
				}
				if (j >= 0 && j < 9)
				{
					displayText(-0.075, (GLdouble) 0.52 - 0.0475 * i, 0.0, 0.0, 0.0, buffer);
				}
			}


			string str3, str4;
			string::size_type s2;

			while (file1 >> str3)
			{
				A.push_back((GLdouble) stod(str3, &s2));
			}
			while (file2 >> str4)
			{
				B.push_back((GLdouble) stod(str4, &s2));
			}


			glColor3d(255.0, 0.0, 0.0);
			glLineWidth(1.5);
				glBegin(GL_LINE_STRIP);
				{
					glVertex2d(0.0, 0.525);
					for (int i = 1; i <= SIZE; i++)
					{

						if (c > d)
						{
							glVertex2d((GLdouble)i / (SIZE + 1), 0.525 + 0.475 * D[i - 1] / c);
						}
						else
						{
							glVertex2d((GLdouble)i / (SIZE + 1), 0.525 + 0.475 * D[i - 1] / d);
						}

					}
					glVertex2d(1.0, 0.525);
				}
				glEnd();
			


			glColor3d(0.0, 0.0, 1.0);
			glPointSize(5);
			glBegin(GL_POINTS);
			{
				for (size_t i = 0; i < A.size(); i++)
				{
					if (c > d)
					{
						glVertex2d((B[i] - a) / (b - a), 0.525 + 0.475 * A[i] / c);
					}
					else
					{
						glVertex2d((B[i] - a) / (b - a), 0.525 + 0.475 * A[i] / d);
					}
				}
			}
			glEnd();

			glColor3d(0.0, 0.0, 1.0);
			glLineWidth(1.5);
				glBegin(GL_LINE_STRIP);
				{
					glVertex2d(0.0, 0.525);
					for (size_t i = 0; i < A.size(); i++)
					{
						if (c > d)
						{
							glVertex2d((B[i] - a) / (b - a), 0.525 + 0.475 * A[i] / c);
						}
						else
						{
							glVertex2d((B[i] - a) / (b - a), 0.525 + 0.475 * A[i] / d);
						}
					}
					glVertex2d(1.0, 0.525);
				}
				glEnd();
			
		}
		file1.close();
		file2.close();
		file3.close();
		file4.close();
	}
	else cout << "Error: Cannot open file, hence cannot display the solution!" << endl;
	glFlush();
}
void initGraph()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.1, 1.1, -0.1, 1.1, 0.0, 1.0);
}

int main(int argc, char**argv)
{
	double a, b;
	int n, option; 
	bool isExit = false; 
	do
	{
		cout << "Please select one of choices:\n" << endl;
		cout << "1. Run the program" << endl;
		cout << "2. Exit" << endl; 
		cin >> option;
		if (!cin.fail())
		{
			if (option == 1)
			{
				cout << "Please enter the domain (a, b) and number of elements (n):\n" << endl;
				cout << "a = ";
				cin >> a;

				while (floor(fabs(F(a))) != 0 || cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Your value is invalid!" << endl; 
					cout << "a = ";
					cin >> a;
				}

				cout << "b = ";
				cin >> b;

				while (floor(fabs(F(b))) != 0 || cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Your value is invalid!" << endl;
					cout << "b = ";
					cin >> b;
				}

				cout << "n = ";
				cin >> n;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Your value is invalid!" << endl;
					cout << "n = ";
					cin >> n;
				}
				clock_t begin = clock(); 
				PDE p(a, b, n);
				initGauss();
				clock_t t1 = clock();
				p.setVectorLandMatrixA();
				clock_t t2 = clock();
				p.setVectorU();
				clock_t t3 = clock();
				p.findErrorforPoint();
				p.displayResult();
				clock_t end = clock();

			
				

				cout << "\nRuntime for setVectorLandMatrixA: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " s" << endl;
				cout << "\nRuntime for setVectorU: " << (double)(t3 - t2) / CLOCKS_PER_SEC << " s" << endl;
				cout << "\nTotal runtime: " << (double)(end - begin) / CLOCKS_PER_SEC << " s" << endl;

				
				


				p.getInfoToFile();


				glutInit(&argc, argv);
				glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
				glutInitWindowSize(500, 500);
				glutInitWindowPosition(800, 150);
				glutCreateWindow("Graph of the function u");
				initGraph();
				glutDisplayFunc(displayGraph);
				glutMainLoop();
		
				isExit = true;
			}
			else if (option == 2)
			{
				exit(0);
			}
			else
			{
				cout << "Your choice is invalid!" << endl;
			}
		}
		else
		{
			cout << "Your choice is invalid!" << endl;
			isExit = true;
		}
		
	} while (!isExit);
	
 
	system("pause");
	return 0;
}