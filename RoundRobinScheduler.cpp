#include<bits/stdc++.h>
using namespace std;
#define lli long long int

class RoundRobinScheduler{
private:
    int nProcesses ; 
    int timeQuanta ;
    vector <pair<string,pair <int,int>>> Processes ; 
    vector <pair<int, pair<int, int>>> PIDs ;   
    vector <int> TurnAroundTime ; 
    vector <int> WaitingTime ;
    vector <int> FinishTime ; 
    
    float AverageTurnAroundTime ; 
    float AverageWaitingTime ;

    queue<int> q;
public:
    RoundRobinScheduler(vector <pair<string,pair <int,int>>> Processes, int timeQuanta) ; 
    
    void FinishTimeCalc(){
        int i,ts,m,nextval,nextarr; 
        nextval = PIDs[0].second.first ; 

        i = 0 ;
        
        for(int i = 0 ; i < nProcesses && PIDs[i].second.first <= nextval ; i++ ){
            q.push(PIDs[i].first) ;
        }

        while (!q.empty()) {

            m = q.front() ; 
            q.pop() ; 

            if(PIDs[m].second.second >= timeQuanta){
                nextval += timeQuanta ;
                PIDs[m].second.second -= timeQuanta ;  
            }
            else{
                nextval += PIDs[m].second.second ;
                 PIDs[m].second.second = 0 ;
            }
            
            while (i < nProcesses && PIDs[i].second.first <= nextval ){
                q.push(PIDs[i].first) ;
                i++;
            }

            if(PIDs[m].second.second > 0 ){
                q.push(m) ;
            }

            if(PIDs[m].second.second <= 0 ){
                FinishTime[m] = nextval ;
            }

        }
    }

    void TurnAround(){
        for (int i = 0; i < nProcesses; i++){
          TurnAroundTime[i] = FinishTime[i] - PIDs[i].second.first ; 
          WaitingTime[i] = TurnAroundTime[i] - Processes[i].second.second ;
          AverageTurnAroundTime += TurnAroundTime[i] ;
          AverageWaitingTime += WaitingTime[i] ;
        }
        AverageTurnAroundTime /= nProcesses ; 
        AverageWaitingTime /= nProcesses ; 
    }   

    void PrintStats() { 
        FinishTimeCalc() ; 
        TurnAround() ;
        printf("\nProcess\tAT\tBT\tFT\tTAT\tWT");
        for( int i = 0 ; i < nProcesses ; i++){
            printf("\nP%d\t\t%d\t%d\t%d\t%d\t%d",PIDs[i].first,Processes[i].second.first,Processes[i].second.second,FinishTime[i],TurnAroundTime[i],WaitingTime[i]);
        }
        printf("\n \n \nAverage Turn Around Time: %f",AverageTurnAroundTime);
        printf("\nAverage Waiting Time: %f\n",AverageWaitingTime);

    }
};

RoundRobinScheduler::RoundRobinScheduler(vector <pair<string,pair <int,int>>> Processes , int timeQuantum){
    this->Processes = Processes ; 
    nProcesses = Processes.size() ; 
    timeQuanta = timeQuantum ;  
    AverageTurnAroundTime = 0 ;
    AverageWaitingTime = 0 ;

    for( int i = 0 ; i < nProcesses ; i++ ){
        PIDs.push_back({i,{Processes[i].second.first , Processes[i].second.second}}) ;
        FinishTime.push_back(0) ;
        WaitingTime.push_back(0) ;
        TurnAroundTime.push_back(0) ; 
    }
}

int main(void){
    std::ios_base::sync_with_stdio(false);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int n_Proceeses, timeQuanta ;
    int arrivalTime , burstTime ; 
    string processName ;

    cin >> n_Proceeses >> timeQuanta ;

    vector <pair<string,pair <int,int>>> Processes ;  
    for (int i = 0; i < n_Proceeses; i++){
        cin >> processName >> arrivalTime >> burstTime ;        
        Processes.push_back({ processName, {arrivalTime,burstTime}}) ;
    }

    RoundRobinScheduler RRS(Processes,timeQuanta) ; 
    RRS.PrintStats() ;
    return 0;
}