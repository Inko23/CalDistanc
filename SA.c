#include "decs.h"

int InitialPlacement(){

}

int InitialTemperature(){

}

int ExitCriterion(){

}

int InnerLoopCriterion(){

}

double PerturbPlacementViaMove(){

}

double Cost(){

}

double UpdateTemp(){
    
}

void SA(){

    P = InitialPlacement();
    T = InitialTemperature();
    
    while(ExitCriterion() == False){
        while(InnerLoopCriterion() == False){ /*One templerature*/
            P_new = PerturbPlacementViaMove(P);
            diff_Cost = Cost(P_new) - Cost(P);
           r = random(0,1);
            if(r < pow(e, -diff_Cost/T));{
                P = P_new; /*Accept move*/
            }
        } /*End one temperature*/
        T = UpdateTemp(T);
    }
}


//InitialPlacement()
//InitialTemperature()
//PerturbPlacementViaMove()
//Cost()
//UpdateTemp()