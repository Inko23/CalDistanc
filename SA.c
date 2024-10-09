#include "decs.h"

int ExitCriterion(double T){
    if(T > FinalTemp){
        return False;
    }else{
        return True;
    }
}

void PerturbPlacementViaMove(){
    
}

double random(int s,int t){
    rand();
}

double UpdateTemp(double Temp){
    return CoolingRate * Temp;
    //return (Temp / (x + 1)); //xが引数に必要
}

void SA(){
    int i;
    double T;
    T = InitialTemperature;
    
    while(ExitCriterion(T) == False){
        old_cost = cal_all_dist();
        for(i=0; i<InnerLoopCount; i++){ /*One templerature*/
            PerturbPlacementViaMove();
            new_cost = cal_all_dist();
            diff_Cost = new_cost - old_cost;
           r = random(0,1);
            if(r < pow(e, -diff_Cost/T));{
                old_cost = new_cost; /*Accept move*/
            }
        } /*End one temperature*/
        T = UpdateTemp(T);
    }
}