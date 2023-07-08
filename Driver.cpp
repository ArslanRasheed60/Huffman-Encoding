#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <fstream>
#include "Heapclass.h";

using namespace std;

int count_alphabets = 0;
bool readdataflag = false;
bool compresdataflag = false;

void readData(string& str)
{
	ifstream fin;
	cout << "\n\nEnter File name:  ";
	string filename = "";
	cin >> filename;
	fin.open(filename);
	if (!fin)
	{
		cout << "\nSorry!! File with this name does not exist  :-( ";
		readdataflag = true;
	}
	else
	{
		getline(fin, str);
		while (!fin.eof())
		{
			string temp;
			getline(fin, temp);
			str = str + "\n" + temp;
			//str = str + temp;
		}
	}
	fin.close();
}
void writeCompressedData(string BinData, int& zerocount, int*& arr)
{
	int int_index = 0;
	int charac_index = 0;
	ofstream fout;
	fout.open("comdata.bin");
	int count = 0;
	if (BinData.length() % 8 != 0)
	{
		while (BinData.length() % 8 != 0)
		{
			BinData = BinData + "0";
			count++;
		}
	}
	zerocount = count;
	int div = BinData.length() / 8;
	for (int i = 0; i < div; i++)
	{
		int x = 0;
		for (int j = 0; j < 8; j++)
		{
			x = x + (int)BinData[i * 8 + j];
			x = x - 48;
			if (j != 7)
			{
				x = x << 1;
			}
			charac_index++;
		}

		if (6 < x && x <= 32 && x != 10)
		{
			arr[int_index] = charac_index;
			x = x + 30;
			int_index++;
		}

		fout << (char)x;
	}
	fout.close();
}
void readCompressedData(string& readcomdata)
{

	cout << "\n\nEnter binary file name for reading of compressed data: ";
	string filename = "";
	cin >> filename;

	ifstream fin;
	fin.open(filename);
	if (!fin)
	{
		cout << "\nFile does not exist: ";
		compresdataflag = true;
	}
	else
	{
		fin >> readcomdata;
		string data;
		/*unsigned char ch = 13;
		if (!fin.eof())
		{
			readcomdata.push_back(ch);
		}*/
		while (!fin.eof())
		{
			fin >> data;
			readcomdata = readcomdata + "\n" + data;
		}
	}
	fin.close();
}
void convertCompressDataToBinary(string readcomdata, string& newbinarydata, int zerocount, int* arr)
{
	int int_index = 0;
	for (int i = 0; i < readcomdata.length(); i++)
	{
		unsigned char charac = readcomdata[i];
		int back_chara = charac;

		if (i * 8 == arr[int_index] - 8)
		{
			back_chara = back_chara - 30;
			int_index++;
		}

		string newvalue = "";

		int count = 0;
		char chch[8] = { '\0' };
		int m = 7;
		while (back_chara != 0)
		{
			int quotient = back_chara % 2;
			chch[m] = quotient + 48;
			m--;
			back_chara = back_chara / 2;
			count++;
		}

		for (int i = count; i < 8 && m >= 0; i++)
		{
			chch[m] = 48;
			m--;
		}

		for (int i = 0; i < 8; i++)
		{
			newvalue.push_back(chch[i]);
		}

		newbinarydata = newbinarydata + newvalue;
	}

	string temp = newbinarydata.substr(0, newbinarydata.length() - zerocount);
	newbinarydata = temp;
}
void writedatabacktofile(string latestdata)
{
	ofstream fout;
	fout.open("newGeneratedData.txt");
	fout << latestdata;
	fout.close();
}

struct alpha_freq
{
	string ch;
	int freq;
	alpha_freq()
	{
		ch = "";
		freq = 0;
	}
	alpha_freq(string c, int v)
	{
		ch = c;
		freq = v;
	}
};

int main()
{
	string mydata = "";
	string binarycode = "";
	//for reading
	string compres = "";
	string newbinary = "";
	//maintaining of the zero count
	int zerocount = 0;
	//For calculating frequencies of the characters:
	alpha_freq array_alpha[100];
	//mainting of the characters which disturbs the binary formula
	int* arr = new int[500];
	for (int i = 0; i < 500; i++)
	{
		arr[i] = 0;
	}
	char Ctemp = '\0';



	cout << "\n1: Read data from file for compression: ";
	cout << "\n2: Read binary file for decompression: ";
	cout << "\n-1: To exit: ";
	cout << "\nEnter choice: ";
	int choice = 0;
	cin >> choice;
	while ((choice < 0 || choice > 2) && choice != -1)
	{
		cout << "\nInvalid Input Enter value Again: ";
		cout << "\nEnter choice: ";
		cin >> choice;
	}

	while (true)
	{
		if (choice == 1)
		{
			readData(mydata);
			if (!readdataflag)
			{
				cout << "\n\n ------------------>  Data Readed Successfully <------------------ \n";

				int ll = mydata.length();
				Ctemp = mydata[ll - 1];

				//calculating the frequency of the characters
				for (int i = 0; i < mydata.length(); i++)
				{
					string ch;
					ch.push_back(mydata[i]);
					for (int j = 0; j < 100; j++)
					{
						if (ch == array_alpha[j].ch)
						{
							array_alpha[j].freq++;
							break;
						}
						else if (array_alpha[j].ch == "")
						{
							array_alpha[j].ch = ch;
							array_alpha[j].freq++;
							break;
						}
					}
				}

				cout << "\n\t\t1: Check characters and Frequencies: ";
				cout << "\n\t\t2: Skip prinitng";
				cout << "\n\t\tEnter choice: ";
				int cho = 0;
				cin >> cho;
				while (cho != 1 && cho != 2)
				{
					cout << "\n\t\t!! Invalid input Enter valid data !!  ";
					cin >> cho;
				}
				if (cho == 1)
				{
					cout << endl;
					cout << "\nCharacters and frequencies are: \n";
				}

				for (int i = 0; i < 100; i++)
				{
					if (array_alpha[i].ch == "")
						break;
					if (cho == 1)
					{
						cout << array_alpha[i].ch << " " << array_alpha[i].freq << endl;
					}
					count_alphabets++;
				}

				int tem_mod = count_alphabets % 10;
				int temp_int = 10 - tem_mod;
				count_alphabets = count_alphabets + temp_int;

				//creating of the object of heap class
				MinHeap mH1(count_alphabets);
				for (int i = 0; i < count_alphabets; i++)
				{
					if (array_alpha[i].ch == "")
						break;
					mH1.insert(array_alpha[i].ch, array_alpha[i].freq);
				}
				mH1.menu();
				mH1.assigning_0_1();

				//generator of binary code

				for (int i = 0; i < mydata.length(); i++)
				{
					mH1.LVR(mydata[i], binarycode);
				}

				//maintenance of the characters which disturbs the binary formula
				for (int i = 0; i < 100; i++)
				{
					arr[i] = 0;
				}

				//writing of the compressed data to the file
				writeCompressedData(binarycode, zerocount, arr);

				//cout << storing tree in file
				mH1.storeTreeInFile(zerocount,arr);

				cout << "\n\n ------------------>  Compression successfull <------------------ \n";
			}
			else
			{
				cout << "\n\n ------------------>  Reading Unsuccessfull <------------------ \n";
			}
		}
		else if (choice == 2)
		{
			if (!compresdataflag)
			{

				MinHeap Mheap2;
				Mheap2.getTreeFromfile(zerocount, arr);

				if (MinHeap::treeflag == false)
				{
					//reading of the compressed data
					readCompressedData(compres);

					cout << "\n\n ------------------>  Data Successfully <------------------ \n";

					//converting of the compressed data into the original binary code.
					convertCompressDataToBinary(compres, newbinary, zerocount, arr);

					string latestDecompressedData = Mheap2.writeBinaryToOriginalData(newbinary);

					latestDecompressedData.push_back(Ctemp);

					//writing data back to file
					writedatabacktofile(latestDecompressedData);

					cout << "\n\n ------------------>  Decompression Successfull <------------------ \n";
				}
				else
				{
					cout << "\n\n ~~~~~~~~~~~~~~~~~~~~ PROGRAM EXITED ~~~~~~~~~~~~~~~~~~~~ ";
					break;
				}
			}
			else
			{
				cout << "\n\n ------------------>  Reading Unsuccessfull <------------------ \n";
			}
		}
		else if (choice == -1)
		{
			cout << "\n\n ~~~~~~~~~~~~~~~~~~~~ PROGRAM EXITED ~~~~~~~~~~~~~~~~~~~~ ";
			break;
		}
		else
		{
			cout << "\n   -----   Invalid Choice  -----  \n";
		}

		readdataflag = false;
		compresdataflag = false;
		cout << "\n1: Read data from file for compression: ";
		cout << "\n2: Read binary file for decompression: ";
		cout << "\n-1: To exit: ";
		cout << "\nEnter choice: ";
		choice = 0;
		cin >> choice;
	}

	//deallocating temp array
	delete[]arr;
	arr = nullptr;
}