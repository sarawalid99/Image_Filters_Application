#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include "bmplib.h"
#include<bits/stdc++.h>
#define SIZE 256

using namespace std;
unsigned char photo[SIZE][SIZE][RGB];
unsigned char image[SIZE][SIZE][RGB];
unsigned char shuffled[SIZE][SIZE][RGB];
unsigned char NewImage[SIZE][SIZE][RGB];
unsigned char output_image[SIZE][SIZE][RGB];
unsigned char modified_image[SIZE][SIZE][RGB];
unsigned char New_image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
char photoName[100];


void loadImage() {
    char imageName[100];
    // Get RGB image file name
    cout << "Enter the source image file name: ";
    cin >> imageName;

    // Add to it .bmp extension and load image
    strcat (imageName, ".bmp");
    readRGBBMP(imageName, image);
}

void loadImageMerge(unsigned  char image[SIZE][SIZE][RGB]){
    char FileName[100];
    // Get RGB scale image file name
    cout<<"Enter image file name : ";
    cin>>FileName;
    // Add to it .bmp extension and load image
    strcat(FileName, ".bmp");
    readRGBBMP(FileName,image);
}

//_________________________________________________________

void toBlacknWhite(){
    int ave;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            ave = (image[i][j][0] * 0.3) + (image[i][j][1] * 0.59) + (image[i][j][2] * 0.11);
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = ave;
                if (image[i][j][0] > 127){
                    image[i][j][0] = 255;
                    image[i][j][1] = 255;
                    image[i][j][2] = 255;
                }
                else{
                    image[i][j][0] = 0;
                    image[i][j][1] = 0;
                    image[i][j][2] = 0;
                }
            }
        }
    }
}

void Flip(){
    char choice;
    cout << "Flip (h)orizontally or (v)ertically ?\n";
    cin >> choice;
    if (choice == 'h'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    NewImage[i][j][k] = image[i][255 - j][k];
                }
            }
        }
    }
    else if (choice == 'v') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    NewImage[i][j][k] = image[255 - i][j][k];
                }
            }
        }
    }

}

void detectEdges() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                NewImage[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                if (i == 0 ||i == 256
                    || j == 0 || j == 256)
                {
                    NewImage[i][j][k] = 255;
                }
                if (image[i][j][k] > 110)
                {
                    NewImage[i][j][k] = 255;
                } else {
                    if ((image[i][j][k]) < 110 && (image[i - 1][j - 1][k] > 110 || image[i - 1][j][k] > 110
                                                   || image[i - 1][j + 1][k] > 110 ||
                                                   image[i][j - 1][k] > 110 || image[i][j + 1][k] > 110 ||
                                                   image[i + 1][j - 1][k] > 110 ||
                                                   image[i + 1][j][k] > 110 || image[i + 1][j + 1][k] > 110))
                    {
                        NewImage[i][j][k] = 0;
                    }
                    else {
                        NewImage[i][j][k] = 255;
                    }
                }
            }
        }
    }
}

void mirroring() {
    char choice;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
    cin >> choice;
    if (choice == 'r'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[i][SIZE-1-j][k];
                }
            }
        }
    }
    else if (choice == 'l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][SIZE-1-j][k] = image[i][j][k];
                }
            }
        }
    }
    else if (choice == 'd'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k]= image[SIZE-1-i][j][k];
                }
            }
        }
    }
    else if (choice == 'u'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image[SIZE-1-i][j][k] = image[i][j][k];
                }
            }
        }
    }
}

void InvertFilter()
{
    for(int i=0 ; i<SIZE ;i++){
        for (int j=0 ; j<SIZE ; j++){
            for(int k=0 ; k<RGB ; k++){
                if (image[i][j][k]==0){
                    image[i][j][k] = 255;
                }
                else if(image[i][j][k]==255){
                    image[i][j][k] = 0;
                }
                else
                    image[i][j][k] = (255-image[i][j][k]);
                output_image[i][j][k] = image[i][j][k];
            }
        }
    }
}


void moveQuarter(int idx, int i, int j )
{
    int temp = j;
    if (idx==1)
        for (int k=0; k < SIZE/2; i++,k++)
        {
            j = temp;
            for (int z=0; z< SIZE/2; j++ , z++){
                shuffled[i][j][0]=image[k][z][0];
                shuffled[i][j][1]=image[k][z][1];
                shuffled[i][j][2]=image[k][z][2];

            }

        }
    else if (idx==2)
        for (int k = 0; k< SIZE/2; i++,k++)
        {
            j = temp;
            for (int z = SIZE/2; z< SIZE; j++,z++){
                shuffled[i][j][0]=image[k][z][0];
                shuffled[i][j][1]=image[k][z][1];
                shuffled[i][j][2]=image[k][z][2];

            }

        }
    else if (idx ==3)
        for (int k=  SIZE/2 ; k<SIZE; i++,k++)
        {
            j = temp;
            for (int z=0; z< SIZE/2; j++,z++){
                shuffled[i][j][0]=image[k][z][0];
                shuffled[i][j][1]=image[k][z][1];
                shuffled[i][j][2]=image[k][z][2];
            }

        }
    else if (idx ==4)
        for (int k =  SIZE/2; k < SIZE; i++,k++)
        {
            j = temp;
            for (int z = SIZE/2; z< SIZE; j++,z++){
                shuffled[i][j][0]=image[k][z][0];
                shuffled[i][j][1]=image[k][z][1];
                shuffled[i][j][2]=image[k][z][2];
            }

        }
}


void shuffleImage() //for postioning the quarter
{
    int n ;
    cerr<<"Enter the order of quarters you want: ";
    for (int i =0 ; i <4 ; i++)
    {
        cin>>n;
        if (i==0) moveQuarter(n,0,0);
        else if (i==1) moveQuarter(n,0,SIZE/2);
        else if (i==2) moveQuarter(n,SIZE/2,0);
        else if (i==3) moveQuarter(n,SIZE/2,SIZE/2);
    }

}

void Enlarge_Image(){
    cout<<"which quarter do you want to enlarge?"<<endl
        <<"1. First quarter" <<endl
        <<"2. second quarter"<<endl
        <<"3. Third quarter" <<endl
        <<"4. Fourth quarter"<<endl;
    int choice;
    cin>>choice;
    if (choice==1){
        for (int i = 0, l=0; i <= SIZE/2; i++, l+=2) {
            for (int j = 0, k=0; j< SIZE/2; j++, k+=2) {
                for(int r=0 ; r<RGB ; r++){
                    output_image[l][k][r]=image[i][j][r];
                    output_image[l][k-1][r]=image[i][j][r];
                    output_image[l-1][k][r]=image[i][j][r];
                    output_image[l-1][k-1][r]=image[i][j][r];
                }
            }
        }
    }
    if (choice==2){
        for (int i = 0, l=0; i <= SIZE/2; i++, l+=2) {
            for (int j = SIZE/2, k=0; j< SIZE; j++, k+=2){
                for(int r=0 ; r<RGB ; r++){
                    output_image[l][k][r]=image[i][j][r];
                    output_image[l][k-1][r]=image[i][j][r];
                    output_image[l-1][k][r]=image[i][j][r];
                    output_image[l-1][k-1][r]=image[i][j][r];
                }
            }
        }
    }
    if (choice == 3){
        for (int i = SIZE/2, l=0; i <= SIZE; i++, l+=2) {
            for (int j = 0, k=0; j< SIZE/2; j++, k+=2) {
                for(int r=0 ; r<RGB ; r++){
                    output_image[l][k][r]=image[i][j][r];
                    output_image[l][k-1][r]=image[i][j][r];
                    output_image[l-1][k][r]=image[i][j][r];
                    output_image[l-1][k-1][r]=image[i][j][r];
                }
            }
        }
    }
    if (choice == 4){
        for (int i = SIZE/2, l=0; i <= SIZE; i++, l+=2) {
            for (int j = SIZE/2, k=0; j< SIZE; j++, k+=2) {
                for(int r=0 ; r<RGB ; r++){
                    output_image[l][k][r]=image[i][j][r];
                    output_image[l][k-1][r]=image[i][j][r];
                    output_image[l-1][k][r]=image[i][j][r];
                    output_image[l-1][k-1][r]=image[i][j][r];
                }
            }
        }
    }
}

void Rotate_Image()
{
    cout<<"Do you want to rotate"<<endl<<"1. 90 degrees"<<endl<<"2. 180degrees"<<endl<<"3. 270 degrees"<<endl;
    int choice;
    cin>>choice;
    if (choice == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0 ; k<RGB ; k++)
                    output_image[j][SIZE-i][k]= image[i][j][k];
            }
        }
    }
    if (choice == 2){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0 ; k<RGB ; k++)
                    output_image[i][j][k] = image[SIZE-i][SIZE-j][k];
            }
        }
    }
    if (choice == 3){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0 ; k<RGB ; k++)
                    output_image[SIZE-j][i][k]= image[i][j][k];
            }
        }
    }
}



void blur (){

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            modified_image[i][j][RGB]=(image[i][j][RGB]+image[i-2][j-2][RGB]+image[i-2][j-1][RGB]+image[i-2][j][RGB]
                                       +image[i-2][j+1][RGB]+image[i-2][j+1][RGB]+image[i-1][j+2][RGB]+ image[i-1][j-2][RGB]+image[i-1][j+1][RGB]+image[i-1][j+1][RGB]+image[i-1][j+2][RGB]+image[i][j-2][RGB]+image[i][j-1][RGB]+image[i][j+1][RGB]
                                       +image[i][j+2][RGB]+image[i+1][j-2][RGB]+image[i+1][j-1][RGB]+image[i+1][j][RGB]+image[i+1][j+1][RGB]+image[i+1][j+2][RGB]+image[i+2][i-2][RGB]+image[1+2][j-1][RGB]+image[i+2][j][RGB]
                                       +image[i+2][j+1][RGB]+image[i+2][j+2][RGB])/25;
            // red only

            modified_image[i][j][RGB-1]=(image[i][j][RGB-1]+image[i-2][j-2][RGB-1]+image[i-2][j-1][RGB-1]+image[i-2][j][RGB-1]+image[i-2][j+1][RGB-1]+
                                         image[i-2][j+1][RGB-1]+image[i-1][j+2][RGB-1]+ image[i-1][j-2][RGB-1]+image[i-1][j+1][RGB-1]+image[i-1][j+1][RGB-1]+
                                         image[i-1][j+2][RGB-1]+image[i][j-2][RGB-1]+image[i][j-1][RGB-1]+image[i][j+1][RGB-1]+image[i][j+2][RGB-1]+image[i+1][j-2][RGB-1]+
                                         image[i+1][j-1][RGB-1]+image[i+1][j][RGB-1]+image[i+1][j+1][RGB-1]+image[i+1][j+2][RGB-1]+image[i+2][i-2][RGB-1]+
                                         image[1+2][j-1][RGB-1]+image[i+2][j][RGB-1]+image[i+2][j+1][RGB-1]+image[i+2][j+2][RGB-1])/25;
            // only blue
            modified_image[i][j][RGB-2]=(image[i][j][RGB-2]+image[i-2][j-2][RGB-2]+image[i-2][j-1][RGB-2]+image[i-2][j][RGB-2]+
                                         image[i-2][j+1][RGB-2]+image[i-2][j+1][RGB-2]+image[i-1][j+2][RGB-2]+ image[i-1][j-2][RGB-2]+image[i-1][j+1][RGB-2]
                                         +image[i-1][j+1][RGB-2]+image[i-1][j+2][RGB-2]+image[i][j-2][RGB]+image[i][j-1][RGB-2]+image[i][j+1][RGB-2]+image[i][j+2][RGB-2]+
                                         image[i+1][j-2][RGB-2]+image[i+1][j-1][RGB-2]+image[i+1][j][RGB-2]+image[i+1][j+1][RGB-2]+image[i+1][j+2][RGB-2]+
                                         image[i+2][i-2][RGB-2]+image[1+2][j-1][RGB-2]+image[i+2][j][RGB-2]+image[i+2][j+1][RGB-2]+image[i+2][j+2][RGB-2])/25;
            // only  green

        }


    }}//take average of matrix 5*5 and store it in modified image to make blur

void shrinkImage() {
    int size;
    int k=0;
    int l=0;
    cout<<"Shrink to (1/2), (1/3) or (1/4)? \n";
    cout<<"if you want a certain size ,enter its inverse \n"
        <<"ex: if you want 1/2 ,enter 2\n";
    cin>>size;
    for (int i = 0; i < SIZE; i+=size) {
        for (int j = 0; j< SIZE; j+=size) {
            modified_image[k][l][RGB]=image[i][j][RGB]; //Red
            modified_image[k][l][RGB-1]=image[i][j][RGB-1];//blue
            modified_image[k][l][RGB-2]=image[i][j][RGB-2];//Green
            l++;
        }
        l=0;
        k++;
    }
}

void lightORdark (){
    string choice;
    cout<<"What do you want, lighten or darken : ";
    cin>>choice;
    if (choice=="lighten"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                modified_image[i][j][RGB]=((image[i][j][RGB])+255)/2;
                modified_image[i][j][RGB-1]=((image[i][j][RGB-1])+255)/2;
                modified_image[i][j][RGB-2]=((image[i][j][RGB-2])+255)/2;
            }
        }
    }
    if(choice=="darken"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                modified_image[i][j][RGB]=((image[i][j][RGB])/2);
                modified_image[i][j][RGB-1]=((image[i][j][RGB-1])/2);
                modified_image[i][j][RGB-2]=((image[i][j][RGB-2])/2);
            }
        }
    }
}

void merge() {                                      //merge two photos together
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            New_image[i][j][RGB]=(image[i][j][RGB]+image2[i][j][RGB])/2; // red only
            New_image[i][j][RGB-1]=(image[i][j][RGB-1]+image2[i][j][RGB-1])/2; //blue only
            New_image[i][j][RGB-2]=(image[i][j][RGB-2]+image2[i][j][RGB-2])/2; } //green only
    }}


//*********************************************************
void saveImagelod () {
    char imageFileName[100];
    // Get RGB image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, modified_image);
}

void saveImageMerge() {
    char FileName[100];
    // Get RGB image target file name
    cout << "Enter the target image file name: ";
    cin >> FileName;
    strcat(FileName, ".bmp");
    writeRGBBMP(FileName, New_image);
}


void savePhoto (){
    char photoName[100];
    // Get RGB scale image target file name
    cout << "Enter the target image file name: \n";
    cin >> photoName;
    // Add to it .bmp extension and load image
    strcat (photoName, ".bmp");
    writeRGBBMP(photoName, photo);
}

void savePhoto2 (){
    char photoName[100];
    // Get RGB scale image target file name
    cout << "Enter the target image file name: \n";
    cin >> photoName;
    // Add to it .bmp extension and load image
    strcat (photoName, ".bmp");
    writeRGBBMP(photoName, output_image);
}

void saveImage2 () {
    char imageFileName[100];
    // Get  RGB image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
void savedetect() {
    char FileName[100];
    // Get RGB image target file name
    cout << "Enter the target image file name: ";
    cin >> FileName;
    strcat(FileName, ".bmp");
    writeRGBBMP(FileName, NewImage);
}

//_____________________________________________________________


int main() {
    int selection;
    bool isOn = 1;
    while (isOn){
        cout << "Ahlan ya user ya habibi \n";
        cout << "Please select a filter to apply or 0 to exit:\n";
        cout << "1- Black & White Filter\n"
                "2- Invert Filter\n"
                "3- Merge Filter \n"
                "4- Flip Image\n"
                "5- Darken and Lighten Image \n"
                "6- Rotate Image\n"
                "7- Detect Image Edges \n"
                "8- Enlarge Image\n"
                "9- Shrink Image\n"
                "10- Mirror 1/2 Image\n"
                "11- Shuffle Image\n"
                "12- Blur Image\n"
                "13- Save the image to a file\n"
                "0- Exit\n";
        cin >> selection;
        if (selection == 1){
            loadImage();
            toBlacknWhite();
            saveImage2();
        }
        else if (selection == 2){
            loadImage();
            InvertFilter();
            savePhoto2();
        }
        else if (selection == 3){

            loadImageMerge(image);
            cout <<"Please enter name of image file to merge with: \n";
            loadImageMerge(image2);
            merge();
            saveImageMerge();
        }
        else if (selection == 4){
            loadImage();
            Flip();
            savedetect();
        }
        else if (selection == 5){
            loadImage();
            lightORdark();
            saveImagelod();
        }
        else if (selection == 6){
            loadImage();
            Rotate_Image();
            savePhoto2();
        }
        else if (selection == 7){
            loadImage();
            detectEdges();
            savedetect();
        }
        else if (selection == 8){
            loadImage();
            Enlarge_Image();
            savePhoto2();
        }
        else if (selection == 9){
            loadImage();
            shrinkImage();
            saveImagelod();
        }
        else if (selection == 10){
            loadImage();
            mirroring();
            saveImage2();
        }
        else if (selection == 11){
            char imageFileName[100];
            cout << "Enter the source image file name: ";
            cin >> imageFileName;

            // Add to it .bmp extension and load image
            strcat (imageFileName, ".bmp");
            readRGBBMP(imageFileName, image);
            shuffleImage();
            char imageName[100];
            // Get RGB scale image target file name
            cout << "Enter the target image file name: \n";
            cin >> imageName;
            // Add to it .bmp extension and load image
            strcat (imageName, ".bmp");
            writeRGBBMP(imageName, shuffled);

        }
        else if (selection == 12){
            loadImage();
            blur();
            saveImage2();
        }
        else if (selection == 13){
            savePhoto();
            isOn = 0;
        }
        else {
            isOn = 0;
        }
    }
}


