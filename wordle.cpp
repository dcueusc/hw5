#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif


#include "wordle.h"
#include "dict-eng.h"
using namespace std;




// Add prototypes of helper functions here
void backTrackHelper(const std::string& in,const std::string& floating,const std::set<std::string>& dict, std::string currW, std::set<std::string>& words, int free);
bool isValid(const std::string& in,const std::string& floating,const std::set<std::string>& dict, std::string currW, std::set<std::string>& words);
// Definition of primary wordle function
std::set<std::string> wordle(
   const std::string& in,
   const std::string& floating,
   const std::set<std::string>& dict)
{
   // Add your code here
   std::string currW="";
   std::set<std::string>* words = new std::set<std::string>();
   int req = floating.size(); //1
   int dCount = 0;
   for(int i=0; i<in.size(); i++){ //1
     if(in.at(i)=='-'){dCount++;}
   }


   backTrackHelper(in, floating, dict, currW, *words, dCount-req);
   return *words;
}


// Define any helper functions here
 void backTrackHelper(const std::string& in,const std::string& floating,const std::set<std::string>& dict, std::string currW, std::set<std::string>& words, int free){
   if(isValid(in,floating,dict,currW,words)){
     words.insert(currW);
     return;
   }
   if(currW.size()>=in.size()){return;}
   if(in.at(currW.size())=='-'){
   for(char c='a'; c<='z'; c++){
     if(free==0 && (floating.find(c) == std::string::npos)){}
     else if(free<0){return;}
     else{
     currW+=c;
     bool minus=false;
     if(floating.find(c) == std::string::npos){free--; minus=true;}
     backTrackHelper(in,floating,dict,currW,words,free);
     if(minus){free++;}
     if(currW.size()!=0){currW.pop_back();} }
     }
   }else{
     currW+=in.at(currW.size());
     backTrackHelper(in,floating,dict,currW,words,free);
     currW.pop_back();
   }
}


   bool isValid(const std::string& in,const std::string& floating,const std::set<std::string>& dict, std::string currW, std::set<std::string>& words){
     if(currW.size()!=in.size()){return false;}
     //create a map from letter to number, each time you search


     if(dict.find(currW)!=dict.end()){
       map<char,int> req;
       for(int i=0; i<floating.length();i++){
         char ch= floating.at(i);
         map<char,int>::iterator it = req.find(ch);
         if(it==req.end()){req.insert(std::pair<char,int>(ch,1) );}
         else{it->second++;}
       }


       for(int i=0; i<currW.length(); i++){
         map<char,int>::iterator it = req.find(currW.at(i));
            if(it!=req.end()){
             if(it->second>0){
                 it->second--;
             }
              
            }
       }
       for (auto i = req.begin(); i != req.end(); i++){
       if(i->second!=0){return false;}}
       return true;
     }
     return false;
   }
