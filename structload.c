#include <stdio.h>
#include <string.h>

struct dataBlock {
	int block[24];
	char description[20];
	char filename[20];
} data;

int load(struct dataBlock *data);
int save(struct dataBlock *data);
int printBlock(struct dataBlock *data);

int main(int argc, char *argv[]){
	
	fprintf(stdout, "starting program\n");
	
	/** save **/
	
	int i = 0;
	while(i < 24){
		data.block[i] = i;
		i++;
	}
	
	strcpy(data.description, "data block 1");
	strcpy(data.filename, "data.dat");
	
	save(&data);
	
	printBlock(&data);
	
	/** load **/
		
	load(&data);
	printBlock(&data);
	
	/** edit then save **/
	
	data.block[0] = 33;
	data.block[8] = 42;
	data.block[11] = 88;
	data.block[17] = 102;
	
	strcpy(data.description, "update 1\n");
	save(&data);
	
	/** load data again **/
	
	load(&data);
	printBlock(&data);
	
	/** edit then save **/
	
	data.block[2] = 31;
	data.block[10] = 0;
	data.block[10] = 22;
	data.block[20] = 4;
	
	strcpy(data.description, "update 2\n");
	save(&data);
	
	/** load data again **/
	
	load(&data);
	printBlock(&data);
	
	return 0;	
}

int load(struct dataBlock *data){
	
		int result = 0;
		
		FILE *fp;
		if((fp = fopen(data->filename, "rb")) == NULL){
			fprintf(stderr, "cannot open file");
			return 0;
		}
		
		fread(&data, sizeof(data), 1, fp);
		
		if(ferror(fp)){
				result = 1;
		}
		fclose(fp);
		
		return result;
}

int save(struct dataBlock *data){
	
		int result = 0;
		
		FILE *fp;
		if((fp = fopen(data->filename, "wb")) == NULL){
			fprintf(stderr, "cannot open file");
			return 0;
		}
		
		fwrite(&data, sizeof(data), 1, fp);
		
		if(ferror(fp)){
				result = 1;
		}
		fclose(fp);
		
		return result;
}

int printBlock(struct dataBlock *data){
	
	fprintf(stdout, "-----------\n");
	fprintf(stdout, "%s\n", data->filename);
	fprintf(stdout, "%s\n", data->description);
	fprintf(stdout, "%d %d %d %d\n", data->block[0], data->block[1], data->block[2], data->block[3]);
	fprintf(stdout, "%d %d %d %d\n", data->block[4], data->block[5], data->block[6], data->block[7]);
	fprintf(stdout, "%d %d %d %d\n", data->block[8], data->block[9], data->block[10], data->block[11]);
	fprintf(stdout, "%d %d %d %d\n", data->block[12], data->block[13], data->block[14], data->block[15]);
	fprintf(stdout, "%d %d %d %d\n", data->block[16], data->block[17], data->block[18], data->block[19]);
	fprintf(stdout, "%d %d %d %d\n", data->block[20], data->block[21], data->block[22], data->block[23]);
	fprintf(stdout, "-----------\n");
}
