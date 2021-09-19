/* Program that reads the date and highest and lowest temperatures
 * in San Jose from a formatted file and prints out the year and month 
 * with the averages of the highest temperatures and the lowest 
 * temperatures per month.
 * 
 * Andrew Li, July 19
 */

#include <stdio.h>

int main(void){
	//Acquires input file name and sets up a pointer to it
	char input_file[260];
	printf("Enter input file name: ");
	scanf("%s", input_file);
	FILE* input = fopen(input_file, "r");
	if(input == NULL){
		printf("%s could not be opened", input_file);
	}
	else{
		_Bool invalid = 1;
		//Continuously asks user for a valid output file
		do{
			char output_file[260];
			printf("Enter output file name: ");
			scanf("%s", output_file);
			FILE* output = fopen(output_file, "w");
			if(output == NULL){
				printf("%s could not be opened", output_file);
			}
			//Reads data from formatted input file and writes it formatted in output file
			else{
				invalid = 0;
				int status;
				int year;
				int month;
				int day;
				double high;
				double low;
				double max_sum = 0;
				double min_sum = 0;
				double max_average[12]; 
				double min_average[12];
				char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
				int index = 0;
				int day_counter = 0;
				int current = 1;
				while((status = fscanf(input, "%d %d %d %lf %lf", &year, &month, &day, &high, &low)) == 5){
					if(month == current){
						max_sum += high;
						min_sum += low;
						day_counter++;
					}
					else{
						max_average[index] = max_sum/day_counter;
						min_average[index] = min_sum/day_counter;
						current = month;
						max_sum = 0;
						min_sum = 0;
						day_counter = 0;
						index++;
					}
				}
				//Extra iteration since loop cancels without calculating and storing December values
				max_average[index] = max_sum/day_counter;
				min_average[index] = min_sum/day_counter;
				current = month;
				max_sum = 0;
				min_sum = 0;
				day_counter = 0;
				index++;
				//Writes the date and average temperature highs and lows per month
				fprintf(output, "Mon./Year Avg Max  Avg Min (°C)\n");
				for(int i = 0; i < 12; i++){
					fprintf(output, "%s %d   %.2lf    %.2lf\n", months[i], year, max_average[i], min_average[i]);
				}  
			}
		}
		while(invalid);
	}
	return 0;
}
