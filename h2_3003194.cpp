/*************************************************
Aufgabe Nr./Task No.: H2
Nachname/Last,Family Name: Rahman
Vorname/First,Given Name: Md.Mashiur
Matrikelnummer/Matriculation number: 3003194
Uni-Email: md.rahman.omi@stud.uni-due.de
Studiengang/Course of Studies: ISE CE(Software)
*************************************************/
#include <iostream>
#include <fstream>
#include<string.h>
#include <sstream>
#include<string>

using namespace std;
int getNumberOfWords(string stringLine);
int getNumberOfSpaces (char stringLine[],int textWidth);
string IntToString (int a);


int main(){
char inputFileName [100];
char outputFileName [100];
int textWidth;
string outPutString = "";
string str;

cout<<"Please enter input text file name <e.g input.txt>: ";
cin>>inputFileName;
cout<<"Please enter output text file name <e.g output.txt>: ";
cin>>outputFileName;
cout<<"Please enter text width to format (>10): ";
cin>>textWidth;
int i;


ofstream file; // out file stream
ifstream fileInput(inputFileName);
if (!fileInput){
	cout<<"Error ! can not open " << inputFileName <<endl;
	return 1;
}
file.open(outputFileName);
if (!file){
	cout<<"Error ! can not open " << outputFileName <<endl;
	return 1;
}

cout<< "start formatting...";
int lineNumber = 0;
 while (std::getline(fileInput, str))
    {
    lineNumber++;
    //cout<<str<<endl;
    if (str.length() != textWidth){
    	cout << "Error! at line number " << lineNumber<< " text width is not same as was given as text width"<<endl;
    	cout<< "still rest of lines will be formatted please see the result in output file" << endl;

    }else{
    //cout << "string length is: "<< str.length()<<endl;
	outPutString = "";
	int numberOfWords = getNumberOfWords (str);
	//cout << ":counted words is: " << numberOfWords << endl;
	int numberOfWords2 = getNumberOfWords (str);
	outPutString.append(IntToString (numberOfWords2));
	outPutString += " Worte,\t";
	outPutString += IntToString(numberOfWords-1);
	outPutString += " Wortzwischenraueme,\t";
	char myArray[str.size()+1];
	strcpy(myArray, str.c_str());
	int numberOfSpace = getNumberOfSpaces (myArray,textWidth);
	int spaceDistance = numberOfSpace/ (numberOfWords-1);
	int spaceBeforeLastWord = numberOfSpace% (numberOfWords-1);
	outPutString += IntToString(spaceDistance)+  " Leerzeichen Abstand,\t";
	outPutString +=IntToString (spaceDistance) + "+" + IntToString (spaceBeforeLastWord) + " Leerzeichen vor dem letzen Wort";
	file << outPutString <<endl;
	}
}
file.close();
fileInput.close();

cout<<"done"<<endl;

return 0;

}

int getNumberOfWords(string stringLine){
  int i = 0;
  int numberOfWords = 0;
  while(isspace(stringLine.at(i)))
    i++;
  for(; i < stringLine.length(); i++)
  {
    if(isspace(stringLine.at(i)))
    {
      numberOfWords++;
      while(isspace(stringLine.at(i++)))
        if(stringLine.at(i) == '\0')
          numberOfWords--;
    }
  }
  return numberOfWords + 1;
}

int getNumberOfSpaces (char stringLine[], int textWidth){
	int numberOfSpaces = 0;
	int i;
	for (i = 0; i<textWidth; i++){
		if (stringLine[i]==' '){
			numberOfSpaces++;
		}
	}
return numberOfSpaces;
}

string IntToString (int a){
	ostringstream temp;
    temp<<a;
    return temp.str();
}
