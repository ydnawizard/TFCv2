#ifndef READDIRECTORY_H
#define READDIRECTORY_H

//Define directory struct that gets passed out
struct DIRECTORY
{
	char** FILES;
	char** SUB_DIRECTORIES;
	int FILECOUNT;
	int SUBCOUNT;
};

void readDirectory(struct DIRECTORY* directory,char* dirName)
{
	int i=0;
	int j=0;
	DIR* rawDir;
	rawDir=opendir(dirName);
	struct dirent* cleanDir;
	directory->FILES=(char**)malloc(sizeof(char*));
	directory->SUB_DIRECTORIES=(char**)malloc(sizeof(char*));
	if(rawDir)
	{
		while((cleanDir=readdir(rawDir))!=NULL)
		{
			if(cleanDir->d_type==DT_REG)
			{
				directory->FILES=(char**)realloc(directory->FILES,(i+1)*sizeof(char*));
				directory->FILES[i]=(char*)malloc(strlen(cleanDir->d_name)*sizeof(char));
				strcpy(directory->FILES[i],cleanDir->d_name);
				i+=1;
			}else if(cleanDir->d_type==DT_DIR&&strcmp(cleanDir->d_name,".")!=0&&strcmp(cleanDir->d_name,"..")!=0)
			{
				directory->SUB_DIRECTORIES=(char**)realloc(directory->SUB_DIRECTORIES,(j+1)*sizeof(char*));
				directory->SUB_DIRECTORIES[j]=(char*)malloc(strlen(cleanDir->d_name)*sizeof(char));
				strcpy(directory->SUB_DIRECTORIES[j],cleanDir->d_name);
				j+=1;
			}
		}
	}
	directory->FILECOUNT=i;
	directory->SUBCOUNT=j;
	closedir(rawDir);
	free(cleanDir);
}

#endif
