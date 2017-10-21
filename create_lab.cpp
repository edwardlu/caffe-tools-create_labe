#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <vector>
#include <fstream>

using namespace std;

int const MAX_STR_LEN = 128;

void create_lables(const char * dir_name,int class_type)
{
	ofstream lab_file;
	lab_file.open("./train.txt",ios::app);
	if(!lab_file.is_open())
		cout<<"create train.txt failed"<<endl;
	
	// check the parameter !
	if(NULL == dir_name)
	{
		cout<<" dir_name is null ! "<<endl;
		return;
	}

	// check if dir_name is a valid dir
	struct stat s;
	lstat(dir_name , &s);
	if(!S_ISDIR(s.st_mode))
	{
		cout<<"dir_name is not a valid directory !"<<endl;
		return;
	}

	struct dirent *filename;    // return value for readdir()
	DIR * dir;                   // return value for opendir()
	dir = opendir(dir_name);
	if(NULL == dir)
	{
		cout<<"Can not open dir "<<dir_name<<endl;
		return;
	}

	/* read all the files in the dir ~ */
	while((filename = readdir(dir)) != NULL)
	{
		// get rid of "." and ".."
		if(strcmp(filename->d_name , ".") == 0 || 
		strcmp(filename->d_name , "..") == 0 ||
		strcmp(filename->d_name , "train.txt") == 0)
			continue;
		cout<<filename ->d_name <<endl;
		lab_file << filename ->d_name <<" "<<class_type<<endl;
	}
	lab_file.close();	
	closedir(dir);
} 

int main(int argc,char **argv)
{
	if(argc<2)
	{
		cout<<"help"<<endl;
	}else{
		string file_dir(argv[1]);
		int class_t = atoi(argv[2]);
		create_lables(file_dir.c_str(),class_t);
	}
	return 0;
}
