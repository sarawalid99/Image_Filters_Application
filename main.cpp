// FCAI – Programming 1 – 2022 - Assignment 3.
// Author1: Sara Walid farouk Mohamed
// Author2: Howida Adel Abd El-Halim
// Author3: Hadeer Abdelnasser
// Teaching Assistant: Afaf Abdelmonem

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include "bmplib.h"
#include<bits/stdc++.h>
#include <iomanip>
#include <cstdlib>
#define SIZE 256
using namespace std;
unsigned char outputImage[SIZE][SIZE];
unsigned char photo[SIZE][SIZE];
unsigned char image[SIZE][SIZE];
unsigned char shuffled[SIZE][SIZE];
unsigned char modified_photo[SIZE][SIZE];
unsigned char NewPhoto[SIZE][SIZE];
unsigned char photo2[SIZE][SIZE];
unsigned char newimage[SIZE][SIZE];
char photoName[100];
void sendPhoto () {
    cout << "Please enter file name of the photo to process:\n";
    // Get gray scale image file name
    //cout << "Enter the source image file name: \n";
    cin >> photoName;
    // Add to it .bmp extension and load image
    strcat (photoName, ".bmp");
    readGSBMP(photoName, photo);
}

void toBlacknWhite(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (photo[i][j] > 120)
                photo[i][j] = 255;
            else
                photo[i][j] = 0;
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
                int Phlip = photo[i][j];
                photo[i][j] = photo[j][i];
                photo[j][i] = Phlip;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE/2; j++) {
                int Phlip = photo[i][j];
                photo[i][j] = photo[i][SIZE-1-j];
                photo[i][SIZE-1-j] = Phlip;
            }
        }
    }
    else if (choice == 'v') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                int Phlip = photo[i][j];
                photo[i][j] = photo[j][i];
                photo[j][i] = Phlip;
            }
        }
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j< SIZE; j++) {
                int Phlip = photo[i][j];
                photo[i][j] = photo[SIZE-1-i][j];
                photo[SIZE-1-i][j] = Phlip;
            }
        }
    }
}

void detectEdges(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            photo2[i][j] = photo[i][j];
        }

    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == 0 || i == 256 || j == 0 || j == 256){
                photo2[i][j] = 255;
            }
            if (photo[i][j] > 110){
                photo2[i][j] = 255;
            }
            else {
                if ((photo[i][j]) < 110 && (photo[i-1][j-1] > 110 || photo[i-1][j] > 110
                                            || photo[i-1][j+1] > 110 || photo[i][j-1] > 110 || photo[i][j+1] > 110
                                            || photo[i+1][j-1] > 110 || photo[i+1][j] > 110 || photo[i+1][j+1] > 110)){
                    photo2[i][j] = 0;
                }
                else {
                    photo2[i][j] = 255;
                }
            }
        }
    }
}


void mirroring(){
    char choice;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
    cin >> choice;
    if (choice == 'r'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                photo[i][j]= photo[i][SIZE-1-j];
            }
        }
    }
    else if (choice == 'l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                photo[i][SIZE-1-j] = photo[i][j];
            }
        }
    }
    else if (choice == 'd'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                photo[i][j]= photo[SIZE-1-i][j];
            }
        }
    }
    else if (choice == 'u'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                photo[SIZE-1-i][j]= photo[i][j];
            }
        }
    }
}
void InvertFilter(){
    for (int i = 0 ; i < SIZE; i++){
        for (int j = 0 ; j < SIZE; j++){
            photo[i][j] = 255 - photo[i][j];
        }
    }
}

void moveQuarter(int idx, int i, int j ){
    int temp = j;
    if (idx==1)
        for (int k=0; k < SIZE/2; i++,k++)
        {
            j = temp;
            for (int z=0; z< SIZE/2; j++,z++)
                shuffled[i][j]=image[k][z];
        }
    else if (idx==2)
        for (int k = 0; k< SIZE/2; i++,k++)
        {
            j = temp;
            for (int z = SIZE/2; z< SIZE; j++,z++)
                shuffled[i][j]=image[k][z];
        }
    else if (idx ==3)
        for (int k=  SIZE/2 ; k<SIZE; i++,k++)
        {
            j = temp;
            for (int z=0; z< SIZE/2; j++,z++)
                shuffled[i][j]=image[k][z];
        }
    else if (idx ==4)
        for (int k =  SIZE/2; k < SIZE; i++,k++)
        {
            j = temp;
            for (int z = SIZE/2; z< SIZE; j++,z++)
                shuffled[i][j]=image[k][z];
        }
}

void shuffleImage() {//for postioning the quarter{
    int n ;
    cout << "Enter the order of quarters you want: \n";
    for (int i =0 ; i <4 ; i++){
        cin>>n;
        if (i==0) moveQuarter(n,0,0);
        else if (i==1) moveQuarter(n,0,SIZE/2);
        else if (i==2) moveQuarter(n,SIZE/2,0);
        else if (i==3) moveQuarter(n,SIZE/2,SIZE/2);
    }
}

void merge() {  //filter 3 merge
    cin >> photoName;
    strcat (photoName, ".bmp");
    readGSBMP(photoName, photo2);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            NewPhoto[i][j]=(photo[i][j]+photo2[i][j])/2;
        }
    }
}

void lightoDark() {                 // filter 6
    string choice;
    cout<<"What do you want, lighten or darken : \n";
    cin>>choice;
    if (choice=="lighten"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                photo2[i][j]=((photo[i][j])+255)/2;
            }}}
    if(choice=="darken"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                photo2[i][j]=((photo[i][j])/2);
            }
        }
    }
}

void RotateImage() {
    unsigned char newimage[SIZE][SIZE];
        int degreeofrotation;
        cout << "Please Enter The Degree of Rotation to apply:\n";
        cout << "{90,180,270}\n";
        cin >> degreeofrotation;
        if (degreeofrotation == 270) {
            char imageFileName[100];
            cout << "Enter the source image file name: ";
            cin >> imageFileName;
            strcat(imageFileName, ".bmp");
            readGSBMP(imageFileName, image);
            for (int i = 0; i < SIZE; i++) {
                for (int j = i; j < SIZE; j++) {
                    swap(image[i][j], image[j][i]);
                }
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < (SIZE / 2); j++) {
                    swap(image[i][j], image[i][SIZE - 1 - j]);
                }
            }
            cout << "Enter the target image file name: ";
            cin >> imageFileName;
            strcat(imageFileName, ".bmp");
            writeGSBMP(imageFileName, image);
        } else if (degreeofrotation == 180) {
            char imageFileName[100];
            cout << "Enter the source image file name: ";
            cin >> imageFileName;
            strcat(imageFileName, ".bmp");
            readGSBMP(imageFileName, image);
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    newimage[i][j] = image[SIZE - i][SIZE - j];
                }
            }
            cout << "Enter the target image file name: ";
            cin >> imageFileName;
            strcat(imageFileName, ".bmp");
            writeGSBMP(imageFileName, newimage);
        } else if (degreeofrotation == 90) {
            char imageFileName[100];
            cout << "Enter the source image file name: ";
            cin >> imageFileName;
            strcat(imageFileName, ".bmp");
            readGSBMP(imageFileName, image);
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    newimage[i][j] = image[j][SIZE - i];
                }
            }
            cout << "Enter the target image file name: ";
            cin >> imageFileName;
            strcat(imageFileName, ".bmp");
            writeGSBMP(imageFileName, newimage);
        }
    }



void savePhoto (){
    char photoName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: \n";
    cin >> photoName;
    // Add to it .bmp extension and load image
    strcat (photoName, ".bmp");
    writeGSBMP(photoName, photo);
}

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
                "0- Exit";
        cin >> selection;
        if (selection == 1){
            sendPhoto();
            toBlacknWhite();
            savePhoto();
        }
        else if (selection == 2){
            sendPhoto();
            InvertFilter();
            savePhoto();
        }
        else if (selection == 3){
            sendPhoto();
            cout << "Please enter name of image file to merge with: \n";
            merge();
            char photoName[100];
            // Get gray scale image target file name
            cout << "Enter the target image file name: \n";
            cin >> photoName;
            // Add to it .bmp extension and load image
            strcat (photoName, ".bmp");
            writeGSBMP(photoName, NewPhoto);
        }
        else if (selection == 4){
            sendPhoto();
            Flip();
            savePhoto();
        }
        else if (selection == 5){
            sendPhoto();
            lightoDark();
            char photoName[100];
            // Get gray scale image target file name
            cout << "Enter the target image file name: \n";
            cin >> photoName;
            // Add to it .bmp extension and load image
            strcat (photoName, ".bmp");
            writeGSBMP(photoName, photo2);
        }
        else if (selection == 6){
            RotateImage();
        }
        else if (selection == 7){
            sendPhoto();
            detectEdges();
            char photoName[100];
            // Get gray scale image target file name
            cout << "Enter the target image file name: \n";
            cin >> photoName;
            // Add to it .bmp extension and load image
            strcat (photoName, ".bmp");
            writeGSBMP(photoName, photo2);
        }
        else if (selection == 8){

        }
        else if (selection == 9){

        }
        else if (selection == 10){
            sendPhoto();
            mirroring();
            savePhoto();
        }
        else if (selection == 11){
            char imageFileName[100];
            cout << "Enter the source image file name: ";
            cin >> imageFileName;

            // Add to it .bmp extension and load image
            strcat (imageFileName, ".bmp");
            readGSBMP(imageFileName, image);
            shuffleImage();
            char imageName[100];
            // Get gray scale image target file name
            cout << "Enter the target image file name: \n";
            cin >> imageName;
            // Add to it .bmp extension and load image
            strcat (imageName, ".bmp");
            writeGSBMP(imageName, shuffled);

        }
        else if (selection == 12){

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
