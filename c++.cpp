#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// define structure
struct pointDetails {
  string pointName;
  float pointDistance;
  float pointCoordinateX;
  float pointCoordinateY;
};


// define all required function prototype
int lengthOfArray(pointDetails array[]);
float getSquareRoot (float number);
float calculateDistance (float x1, float x2, float y1, float y2);
string *findNearestDistance (pointDetails listofAllPoints [], pointDetails aPoint);
void sortAndPrintpoints (struct pointDetails listofAllPoints []);

int main (){
	struct pointDetails listOfPoints [1000];
	char morePoints = 'y';
	char sequenceAtoZ = 'A';
	int pointCounter=0;

	// taking point defination from user
	while (morePoints=='y'||morePoints=='Y'){
		cout<<"Enter X value of coordinate "<<sequenceAtoZ<< " : "; 		// store X value
    	cin>>listOfPoints [pointCounter].pointCoordinateX;
    	cout<<"Enter Y value of coordinate "<<sequenceAtoZ<< " : "; 		// store Y value
    	cin>>listOfPoints [pointCounter].pointCoordinateY;
    	listOfPoints [pointCounter].pointName =sequenceAtoZ ;				// store pointName (A-Z)
    	cout<<"Do you want to insert one more point <y / n or any key>: ";
    	cin>>morePoints;
		pointCounter++;				// increment pointCounter
		++sequenceAtoZ;				// get A - Z sequentially
		cout<< ""<<endl;cout<< ""<<endl;
	}

	sortAndPrintpoints (listOfPoints);    // calculate distance, sort obstacles and print obstacles
	return 0;
}




// implementation of functions
float getSquareRoot (float number){
	float estimation = 1;
    int cycle=50;
    if (number == 0){
    	cout<<"ERROR!! ivalid value for calculating square root "<<endl;
    	return 0;
    }
    while(cycle>0){
        estimation = ( estimation + ( number / estimation ) ) / 2;
        --cycle;
    }
return 	estimation;
}


float calculateDistance (float x1, float x2, float y1, float y2){

	double x = x1 - x2;
    double y = y1 - y2;
    double dist;
//	cout << "x: "<< x << " y" << y << endl;
    dist = ((x*x) + (y*y));		           //calculating distance by euclidean formula
    //cout<< "dist is: "<< dist << endl;
    dist = getSquareRoot(dist);                  //sqrt is function in math.h

    return dist;

}

string *findNearestDistance (struct pointDetails listofAllPoints [], struct pointDetails aPoint){
	int i,j=0, k=0;
	float oldNearestPoint, newNearestPoint;
	string *nearestPointName;
	string currentPointName, samePoint;
	samePoint = aPoint.pointName;

	while ( k<1){
		  if ( listofAllPoints [j].pointName != samePoint){
		  	oldNearestPoint = calculateDistance (aPoint.pointCoordinateX, listofAllPoints [j].pointCoordinateX, aPoint.pointCoordinateY, listofAllPoints [j].pointCoordinateY);
		  	//cout << "Current distance: " <<listofAllPoints [j].pointName <<" =  " << oldNearestPoint<< endl;
		  	nearestPointName = &(listofAllPoints [j].pointName);
			k=3;										// de activate while loop
		  }	else {
		  	j++;
		  }
	}
	for (i=0; i<lengthOfArray(listofAllPoints); i++){
		if ( listofAllPoints [i].pointName != samePoint){       // prevent obstacle to get distance 0 and to get same point
			newNearestPoint = calculateDistance (aPoint.pointCoordinateX, listofAllPoints [i].pointCoordinateX, aPoint.pointCoordinateY, listofAllPoints [i].pointCoordinateY);
		//	cout << "Current distance: " <<listofAllPoints [i].pointName <<" =  " << newNearestPoint<< endl;
			if (oldNearestPoint>newNearestPoint){			   // check and get nearest value
				oldNearestPoint = newNearestPoint;
				nearestPointName = &(listofAllPoints [i].pointName);
			}
		}

	}
//	cout<< "Final output as nearest Point: " << *nearestPointName << endl;

return nearestPointName;
}

int lengthOfArray(pointDetails array[]) {
    int i = 0;
    int foundLength = 1;

    while(foundLength == 1) {
    	if (array[i].pointName.empty()){
    		foundLength =0;
    	}else {
    		i++;
    	}
    }
    return i;
}


void sortAndPrintpoints (struct pointDetails listofAllPoints []){
	struct pointDetails tmpPointHolder [1000];
	struct pointDetails *tmpPoint;
	float contstantX1 = 0.0;
	float constantY1 = 0.0;
	int i,j;

	// set the precision for printing of float
	cout << fixed;
    cout << setprecision(3);

		// calculate distance for all the points
		for (i=0; i<lengthOfArray(listofAllPoints); i++){
			float distance = calculateDistance (contstantX1, listofAllPoints [i].pointCoordinateX,constantY1,listofAllPoints [i].pointCoordinateY);
			listofAllPoints[i].pointDistance = distance;
		//	cout<< "Name: "<< listofAllPoints[i].pointName <<"  dist: " << listofAllPoints[i].pointDistance << endl;
		}
	 // print the sorted points with nearest distance (print in Desnding Series)

	 	if (lengthOfArray(listofAllPoints)<2){
	 		cout<< "obstacle " << listofAllPoints[0].pointName<<":  (" << listofAllPoints[0].pointCoordinateX << ".  "<<listofAllPoints[0].pointCoordinateY << ".)  ";
			cout << "distance: " << listofAllPoints[0].pointDistance << "m. ";
			cout<< "nearest to this: " << "no one" << endl;
			cout<< ""<< endl;

	 	}else {
	 		// Sort the points:: Aesnding Series:: low to high
	 		for( i=0;i<lengthOfArray(listofAllPoints);i++){
        		for(int j=0;j<lengthOfArray(listofAllPoints);j++){
        			if(listofAllPoints[i].pointDistance>listofAllPoints[j].pointDistance){
                		struct pointDetails temp =listofAllPoints [i];
                		listofAllPoints[i]=listofAllPoints[j];
                		listofAllPoints[j]=temp;
            		}
        		}
    		}
	 	// print the obstaceles
	 		for (i=lengthOfArray(listofAllPoints)-1; i>=0; i--){
				string *res = findNearestDistance (listofAllPoints,listofAllPoints[i]);
				cout<< "obstacle" << listofAllPoints[i].pointName<<": (" << listofAllPoints[i].pointCoordinateX << " , "<<listofAllPoints[i].pointCoordinateY << ")\t";
				cout << "distance: " << listofAllPoints[i].pointDistance << "m\t";
			//cout<< "nearest to this: " << *findNearestDistance (listofAllPoints,listofAllPoints[i]) << endl;
				cout<< "nearest to this: " << *res << endl;
				cout<< ""<< endl;
			}
	 	}
		 // Now remove array elements from heap
		 //cout<< "before: "<< lengthOfArray(listofAllPoints)<<endl;
		 cout<< "delete: ";
		 int arrayLength = lengthOfArray(listofAllPoints);
		 for (j=0;j<arrayLength; j++){
		 	for( i=0;i<lengthOfArray(listofAllPoints);i++){
		 		if (i==0){
		 			cout<< listofAllPoints [i].pointName<<" ";
		 		}
				listofAllPoints [i] = listofAllPoints [i+1];
			}
		 }
		//cout<< "after: "<< lengthOfArray(listofAllPoints);
}
