#ifndef RECCHECK
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please


#endif


#include "schedwork.h"


using namespace std;


// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;




// Add prototypes for any helper functions here
bool scheduleHelp(
const AvailabilityMatrix& avail,
   const size_t dailyNeed,
   const size_t maxShifts,
   DailySchedule& sched
);
bool hasShifts(DailySchedule& sched, int worker, const size_t maxShifts);
bool workingToday(DailySchedule& sched, int worker, const size_t maxShifts, int r);
// Add your implementation of schedule() and other helper functions here
bool backtrack(const AvailabilityMatrix& avail,const size_t dailyNeed,const size_t maxShifts,DailySchedule& sched, int r, int c);


bool schedule(
   const AvailabilityMatrix& avail,
   const size_t dailyNeed,
   const size_t maxShifts,
   DailySchedule& sched
)
{
   if(avail.size() == 0U){
       return false;
   }
   sched.clear();
   // Add your code below


   return scheduleHelp(avail,dailyNeed,maxShifts,sched);
}


bool scheduleHelp(const AvailabilityMatrix& avail,const size_t dailyNeed,const size_t maxShifts,DailySchedule& sched){
 size_t days = avail.size();
 size_t workers = avail[0].size();
   if (days == 0 || workers == 0 || dailyNeed == 0){
     return false;
   }


   sched.resize(days, vector<Worker_T>(dailyNeed, INVALID_ID));
   return backtrack(avail, dailyNeed, maxShifts, sched, 0, 0);
}


bool hasShifts(DailySchedule& sched, int worker, const size_t maxShifts){
 int shifts=0;
 for(vector<vector<Worker_T>>::iterator it = sched.begin(); it!=sched.end(); it++){
   vector<Worker_T> curr=*it;
   for(vector<Worker_T>::iterator wor = curr.begin(); wor!=curr.end(); wor++){
     if(worker==*wor){
             shifts++;
               if (shifts >= maxShifts){
                return false;
               }
       }
   }
 }
 return true;
}


bool workingToday(DailySchedule& sched, int worker, const size_t maxShifts, int r){
 vector<Worker_T> curr=sched[r];
  if(find(curr.begin(),curr.end(),worker)!=curr.end()){return true;}
   return false;
}


bool backtrack(const AvailabilityMatrix& avail,const size_t dailyNeed,const size_t maxShifts,DailySchedule& sched, int r, int c){
 size_t workers=avail[0].size();
 if (r>= avail.size()) {
       return true;
   }
   for(int i=0; i<workers; i++){
     if(avail[r][i] && hasShifts(sched,i,maxShifts) && !workingToday(sched,i,maxShifts,r)){
         sched[r][c] = i;
         if(c+1==dailyNeed){
           if(backtrack(avail,dailyNeed,maxShifts,sched,r+1,0)){return true;}
         }else{
           if(backtrack(avail,dailyNeed,maxShifts,sched,r,c+1)){return true;}
         }
     }
     sched[r][c]=INVALID_ID;
   }
 return false;
}
