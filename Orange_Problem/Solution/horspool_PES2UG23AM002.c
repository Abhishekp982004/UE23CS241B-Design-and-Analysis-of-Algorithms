#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>

// Fill in the TODO sections as required and DO NOT TOUCH any of the fprintf statements

void init_table(int* shift_table,int n)
{
	for(int i=0;i<26;i++)
	{
		shift_table[i]=n;

	}
}

// Construct the Bad Character Shift table
void preprocess(int* shift_table,char* pattern)
{
	int len = strlen(pattern);
    for(int i = 0; i < len - 1; i++) {
        if (pattern[i] >= 'a' && pattern[i] <= 'z') {  // Ensure only valid lowercase letters
            shift_table[(int)(pattern[i] - 'a')] = len - i - 1;
        }
    }
}

int string_match(int* shift_table,char* pattern,char* text,FILE* output_file)
{
	// Variables initialization
	int matches = 0;
	int star_pos = strlen(pattern) - 1;
	char star_char;
	int cmp = 0;
	int occurance = 0;
	int index;

	fprintf(output_file,"Occurrences:");
	while(star_pos < strlen(text))
	{
		matches = 0;
		for(int i = 0; i < strlen(pattern); i++)
		{
			cmp++;
			if(pattern[strlen(pattern)-1-i] == text[star_pos-i])
				matches++;
			else
				break;
		}
		
		if(matches == strlen(pattern))
		{
			index = star_pos - strlen(pattern) + 1;
			fprintf(output_file,"%d,",index);
			star_pos++;
		}
		else
		{
			star_char = text[star_pos];
			if(star_char < 'a' || star_char > 'z')
				star_pos++;
			else
				star_pos += shift_table[star_char - 'a'];
		}
	}
	fprintf(output_file,"\n");
	fprintf(output_file,"Comparisons:%d\n\n",cmp);
	return cmp;
}

void print_table(int* shift_table, FILE* output_file)
{
	fprintf(output_file,"BCST:\n");
	for(int i=0;i<26;i++)
	{
		fprintf(output_file,"%c:%d",(char)(i+97), shift_table[i]);
	}
	fprintf(output_file, "\n");
}

void testcase(FILE* values_file, FILE* input_file, FILE* output_file)
{
	char text[2000];
	char pattern[100];
	fscanf(input_file,"%s",text);
	fscanf(input_file,"%s",pattern);

	int* shift_table=calloc(26,sizeof(int));
	init_table(shift_table,strlen(pattern));
	preprocess(shift_table,pattern);
	print_table(shift_table, output_file);
	clock_t start = clock();
	int cmp = string_match(shift_table,pattern,text,output_file);
	clock_t end = clock();
	int elapse=(int)(((double)(end-start))/CLOCKS_PER_SEC*1000000000); //seconds to nanoseconds
	fprintf(values_file,"%ld,%ld,%d,%d\n",strlen(pattern),strlen(text),cmp,elapse);
	free(shift_table);
}

int main()
{	
	FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("horspool_output.txt", "w");
    FILE *values_file = fopen("horspool_values.txt", "w");

    if (!input_file || !output_file || !values_file) {
        printf("Error opening file!\n");
        return 1;
    }
    int testcases;
	fscanf(input_file,"%d",&testcases);
	int count = 0;
	fprintf(values_file, "patternlen,textlen,cmp,timetaken\n");
	while(count < testcases)
	{
		testcase(values_file, input_file, output_file);
		count += 1;
	}
	fclose(input_file);
	fclose(output_file);
	fclose(values_file);
	return 0;
}
