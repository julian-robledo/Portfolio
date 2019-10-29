#include <stdio.h>
#include <stdlib.h>

//defining CREW struct to include level, hours, and cost per hour of a crew.
typedef struct{
  int level;
  int hours;
  int cost;
}CREW;

//defining MAINT_DATA struct to include job ID, level, and number of hours required.
typedef struct{
  int ID;
  int level;
  int num_of_hours;
}MAINT_DATA;

//function prototypes.
void scan_crew_data(CREW *, int);
void scan_maintenance_data(MAINT_DATA *, int);
int match_crew_to_maintenance(CREW *, int, int);
int find_earliest_time(CREW *, int, int);
void print_schedule(CREW *, MAINT_DATA *, int, int);

//reads the level and the cost of each crew into crew array.
void scan_crew_data(CREW *crew, int size){

  for(int i = 0; i < size; i++){
    scanf("%d %d", &crew[i].level, &crew[i].cost);
  }

  return;
}

//reads job ID, level, and number of hours required into maint array.
void scan_maintenance_data(MAINT_DATA *maint, int size){

  for(int i = 0; i < size; i++){
    scanf("%d %d %d", &maint[i].ID, &maint[i].level, &maint[i].num_of_hours);
  }

  return;
}

//checks maintenance level required against crew level and returns number of cheapest capable crew.
int match_crew_to_maintenance(CREW *crew, int size_crew_arr, int maint_level){

  //Declaration of capable_crews array and initial_index array in order to match their indeces to the initial crew array.
  int *initial_index = (int *) calloc(size_crew_arr, sizeof(int));
  CREW *capable_crews = (CREW *) calloc (size_crew_arr, sizeof(CREW));

  //This loop assimilates all crews capable of doing the job into the capable_crews array, and stores their crew array indeces into initial_index array.
  int index_capable_crews = 0;
  for(int i = 0; i < size_crew_arr; i++){
    if(crew[i].level >= maint_level){
      capable_crews[index_capable_crews] = crew[i];
      initial_index[index_capable_crews] = i;
      index_capable_crews++;
    }
  }

  //This loop finds the cheapest crew out of the capable_crews array.
  int min_price = capable_crews[0].cost;
  int i_lowest = 0;
  for(int i = 0; i < index_capable_crews; i++){
    if(min_price - capable_crews[i].cost > 0){
      min_price = capable_crews[i].cost;
      i_lowest = i;
    }
  }

  //Assigning cheapes capable crew to a variable in order to free initial_index and capable_crews arrays.
  int cheapest_capable_crew = initial_index[i_lowest];
  free(initial_index);
  free(capable_crews);
  return cheapest_capable_crew;
}

//This function finds the crews capable of doing the job, sees which one can do it sooner, and if there are more than one, checks which is cheapest.
int find_earliest_time(CREW *crew, int size_crew_arr, int maint_level){

  //Declaration of capable_crews array and initial_index array in order to match their indeces to the initial crew array.
  int *initial_index = (int *) calloc(size_crew_arr, sizeof(int));
  CREW *capable_crews = (CREW *) calloc(size_crew_arr, sizeof(CREW));

  //This loop assimilates all crews capable of doing the job into the capable_crews array, and stores their crew array indeces into initial_index array.
  int index_capable_crews = 0;
  for(int i = 0; i < size_crew_arr; i++){
    if(crew[i].level >= maint_level){
      capable_crews[index_capable_crews] = crew[i];
      initial_index[index_capable_crews] = i;
      index_capable_crews++;
    }
  }

  //This loop finds which crews can do the job at the earliest time and stores their indeces in i_earliest array.
  int earliest_time = capable_crews[0].hours;
  int *i_earliest = (int *) calloc(index_capable_crews, sizeof(int));
  int i_earliest_index = 0;
  for(int i = 0; i < index_capable_crews; i++){
    if(earliest_time - capable_crews[i].hours > 0){
      earliest_time = capable_crews[i].hours;
      i_earliest[i_earliest_index] = i;
      i_earliest_index++;
    }
  }

  //This loop finds the cheapest crew out of the earliest available ones. i_lowest is the index for the lowest of the earliest capable crews.
  int min_price = capable_crews[0].cost;
  int i_lowest = 0;
  int k = 0;
  for(int i = 0; i < index_capable_crews; i++){
    if(i == i_earliest[k]){
      if(min_price - capable_crews[i].cost > 0){
        min_price = capable_crews[i].cost;
        i_lowest = i;
      }
    }
    k++;
  }

  /*sets the value of the earliest cheapest crew from the initial_index array equal to a variable in order to free
  the memory of all dynamically allocated arrays in this function.*/
  int earliest_cheapest_crew = initial_index[i_earliest[i_lowest]];
  free(capable_crews);
  free(initial_index);
  free(i_earliest);
  return earliest_cheapest_crew;
}

//accumulates hours for each crew member and prints out the job information (job ID, start time, end time, crew number).
void print_schedule(CREW *crew, MAINT_DATA *maint, int crew_number, int index){

  crew[crew_number].hours += maint[index].num_of_hours;
  printf("%d %9d %9d %5d\n", maint[index].ID, crew[crew_number].hours - maint[index].num_of_hours, crew[crew_number].hours, crew_number);

  return;
}
