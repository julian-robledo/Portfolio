#include "scheduling.h"

int main(void){
  //reading size of CREW struct array from input
  int size_crew_arr;
  scanf("%d", &size_crew_arr);
  //dynamically allocating memory for the CREW array, in which crews's info will be stored.
  CREW *crew = (CREW *) calloc(size_crew_arr, sizeof(CREW));
  scan_crew_data(crew, size_crew_arr);//reading data into crew[]

  //Below, creating maint array of structs MAINT_DATA. calling function scan_maintenance_data to read data into maint array.
  int size_maint_arr;
  scanf("%d", &size_maint_arr);
  MAINT_DATA *maint = (MAINT_DATA *) calloc(size_maint_arr, sizeof(MAINT_DATA));
  scan_maintenance_data(maint, size_maint_arr);

  /*The two loops below find the max level of crew/maint arrays and compare them to ensure max level
  of maint[] does not exceed max level of crew[]. If it does, program exits.*/
  int max_level_crew = crew[0].level;
  for(int i = 0; i < size_crew_arr; i++){
    if(max_level_crew - crew[i].level < 0){
      max_level_crew = crew[i].level;
    }
  }
  int max_level_maint = maint[0].level;
  for(int i = 0; i < size_maint_arr; i++){
    if(max_level_maint - maint[i].level < 0){
      max_level_maint = maint[i].level;
    }
  }
  if(max_level_maint > max_level_crew){
    printf("ERROR: Max level of maintenance exceeds max level of crews. Exiting program.\n");
    exit(-1);
  }

  //printing out the output begins here. First, lowest cost schedule is printed.
  printf("LOWEST COST SCHEDULE:\n\n");
  printf("CREW SCHEDULES:\n");
  printf("JOB START TIME  END_TIME  CREW\n\n");

  /*this loop gets the output from match_crew_to_maintenance, adds to the total cost by multiplying
  the hourly rate of the returned crew by the num_of_hours, and then prints the next line in the schedule.*/
  int crew_number, total_cost = 0;
  for(int i = 0; i < size_maint_arr; i++){
    crew_number = match_crew_to_maintenance(crew, size_crew_arr, maint[i].level);
    total_cost += maint[i].num_of_hours*crew[crew_number].cost;
    print_schedule(crew, maint, crew_number, i);
  }

  //calculates the job finished time by calculating the max crew[i].hours.
  int end_time = crew[0].hours;
  for(int i = 0; i < size_crew_arr; i++){
    if(end_time - crew[i].hours < 0){
      end_time = crew[i].hours;
    }
  }

  printf("\n\nALL JOBS FINISHED AT %d AT A COST OF %d\n\n\n", end_time, total_cost);

  //printing of fastest schedule output begins here.
  printf("FASTEST SCHEDULE:\n\n");
  printf("CREW SCHEDULES:\n");
  printf("JOB START TIME  END_TIME  CREW\n\n");

  //This loop sorts the array maint[] in descending order of the maint[i].level values.
  MAINT_DATA temp;
  for(int i = 0; i < size_maint_arr; i++){
    for(int j = i + 1; j < size_maint_arr; j++){
      if(maint[i].level < maint[j].level){
        temp = maint[i];
        maint[i] = maint[j];
        maint[j] = temp;
      }
    }
  }

  //resets all crew[i].hours values to 0 so that the fastest schedule can be calculated.
  for(int i = 0; i < size_crew_arr; i++){
    crew[i].hours = 0;
  }

  /*this loop gets the output from find_earliest_time, adds to the total cost by multiplying
  the hourly rate of the returned crew by the num_of_hours, and then prints the next line in the schedule.*/
  total_cost = 0;
  for(int i = 0; i < size_maint_arr; i++){
    crew_number = find_earliest_time(crew, size_crew_arr, maint[i].level);
    total_cost += maint[i].num_of_hours*crew[crew_number].cost;
    print_schedule(crew, maint, crew_number, i);
  }

  //calculates the job finished time by calculating the max crew[i].hours.
  end_time = 0;
  for(int i = 0; i < size_crew_arr; i++){
    if(end_time - crew[i].hours < 0){
      end_time = crew[i].hours;
    }
  }

  printf("\n\nALL JOBS FINISHED AT %d AT A COST OF %d", end_time, total_cost);

  //freeing maint and crew dynamically allocated arrays.
  free(crew);
  free(maint);

  return 0;
}
