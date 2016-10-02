//Written by Nick Sallinger
//for CS0449 with Dr.Misurda
//Assignment 1 part 2, Image Transformations
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)
struct header{
	//Struct for bmp header
    unsigned short identifier;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;

};

struct DIB{
	//struct for DIB header
    unsigned int DIBsize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bits;
    unsigned int compression;
    unsigned int size;
    unsigned int horizontal_resolution;
    unsigned int vertical_resolution;
    unsigned int num_colors;
    unsigned int important_colors;

};

struct colors{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

//int main() {
int main ( int argc, char *argv[] ){  
  	struct header head;
    	struct DIB DIB;
    	int counter=0;
	FILE *image; //file pointer
	struct colors BGR;
	unsigned int height;
	int invert;
	//handle user input and open files

	if(strcmp(argv[1],"-invert") == 0){
		printf("Inverting image\n");
		invert = 0;
	}

	else if(strcmp(argv[1],"-grayscale") == 0){
		printf("Converting to grayscale\n");
		invert = 1;
	}
	else{
		printf("Operation and file must be specified\n");
		exit(0);
	}

    	image = fopen(argv[2],"rb+");
		unsigned int width;
		unsigned int rows;
    	
	if(image==NULL){
       	 	printf("Error opening file");
		exit(0);
	}
    
	//red bitmap header
    	fread(&head,1,sizeof(head),image);

    	//verify its a bitmap
    	if (head.identifier == NULL){
       		printf("Header was not read correctly");
		exit(0);    
	}

	if(head.identifier != 0x4D42){
		printf("File type not supported");
		exit(0);
	}
    	
	//read DIB header
    	fread(&DIB, sizeof(DIB),1,image);
    	
	if(sizeof(DIB) != 40){
	printf("File not supported");
	exit(0);	
	}

	//move to beggining of data
    	fseek(image,head.offset, SEEK_SET);

	//printf("Identifier: %u\n",head.identifier);
	//printf("Size: %u\n",head.size);
	//printf("reserved1: %u\n",head.reserved1);
	//printf("Reserved2: %u\n",head.reserved2);
	//printf("Offset: %u\n",head.offset);
	//printf("DIB header size: %d\n",DIB.DIBsize );
	//printf("width: %u\n",DIB.width);
	//printf("Heigth: %u\n",DIB.height);
	//printf("planes: %u\n",DIB.planes);
   	//printf("bits: %u\n", DIB.bits);
   	//printf("compression: %u\n",DIB.compression);
   	//printf("size: %u\n",DIB.size);	
	//printf("x res: %u\n",DIB.horizontal_resolution);
	//printf("y res: %u\n",DIB.vertical_resolution);
	//printf("number of colors: %u\n",DIB.num_colors);
	//printf("important colors: %u\n",DIB.important_colors);
	

	//The number of rows is the height as specified 
	//in the DIB header and the number of pixels per
	// row is the width from the DIB header.
	//height is 273
	//width is 307

	int padding;
	int j;

	if(invert == 0){
	for(height = 0; height < DIB.height; height++){
	//This is for inverting the bmp			
		for(counter = 0; counter < DIB.width; counter++){
			fread(&BGR,sizeof(BGR),1,image);
			fseek(image,-sizeof(BGR),SEEK_CUR);
			BGR.blue = ~BGR.blue;
			BGR.green = ~BGR.green;
			BGR.red = ~BGR.red;
						
			//fwrite(&BGR,sizeof(BGR),1,out);
			fwrite(&BGR,sizeof(BGR),1,image);
		}
		
		int padding = (DIB.width*sizeof(BGR))%4;
		fseek(image,padding,SEEK_CUR);
		
		}
	}
	
	
float blue;
float green;
float red;
float Y;

	if(invert == 1){
		//for converting to grayscale
		for(height = 0; height < DIB.height; height++){
			for(counter = 0;counter < DIB.width; counter++){
				fread(&BGR,sizeof(BGR),1,image);
				fseek(image,-sizeof(BGR),SEEK_CUR);
			//	printf("blue before: %u\n",BGR.blue);
				blue =  BGR.blue/255.0;
				green = BGR.green/255.0;
				red = BGR.red/255.0;
			//	printf("blue normalized: %f\n", blue); 
				Y = (0.2126*red + 0.7152*green + .0722*blue);
								
				if(Y > 0.0031308){
				blue = 255*(1.0555*pow(Y,(1/2.4))-0.055);
			//	printf("float blue with y : %f\n", blue);
				
				BGR.blue = (char) blue;
				BGR.red = (char) blue;
				BGR.green = (char) blue;
			//	printf("All Done:\nBlue: %u\n,Green: %u,Red: % u",BGR.blue,BGR.green,BGR.red);
				}
				else if(Y <= 0.0031308){
				blue = 255*(12.92*Y);
				BGR.blue = (char) blue;
				BGR.red = (char) blue;
				BGR.green = (char) blue;
	//printf("All Done:\nBlue: %u\n,Green: %u\n,Red: % u\n",BGR.blue,BGR.green,BGR.red);
				}

			

				//DO bit manipulation
				fwrite(&BGR,sizeof(BGR),1,image);		
			}
			int padding = (DIB.width*sizeof(BGR))%4;
			fseek(image,padding,SEEK_CUR);
		}		
	}



}



