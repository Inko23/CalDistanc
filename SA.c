#include "decs.h"

int ExitCriterion(double T){
    if(T > FinalTemp){
        return False;
    }else{
        return True;
    }
}

//変数を定義する
void PerturbPlacementViaMove(){ //元の状態を記憶しておく
    while(1){
        srand((unsigned)time(NULL));
        //ランダムに2つのボックスの座標を生成
        rndm[0] = (int)rand() * (double)(/*x軸のボックスの数*/ / (1 + RAND_MAX));
        rndm[1] = (int)rand() * (double)(/*y軸のボックスの数*/ / (1 + RAND_MAX));
        rndm[2] = rand() %  + n_box /*1つの棚に収納されているボックスの数*/;
        rndm[3] = (int)rand() * (double)(/*x軸のボックスの数*/ / (1 + RAND_MAX));
        rndm[4] = (int)rand() * (double)(/*y軸のボックスの数*/ / (1 + RAND_MAX));
        rndm[5] = rand() %  + n_box /*1つの棚に収納されているボックスの数*/;

        if((map[rndm[0]][rndm[1]].box[rndm[2]] != Empty) || (map[rndm[3]][rndm[4]].box[rndm[5]] != Empty)){//どちらかは部品が入っている
            //元の状態を保持
            OLD_1 = map[rndm[0]][rndm[1]].box[rndm[2]]; 
            OLD_2 = map[rndm[3]][rndm[4]].box[rndm[5]];
            //部品を入れ替える
            map[rndm[0]][rndm[1]].box[rndm[2]] = OLD_2;
            map[rndm[3]][rndm[4]].box[rndm[5]] = OLD_1;
            break;
        }    
    }    
}

//Acceptされなかった時の元の座標に戻す関数
void UndoPlacement(){
    map[rndm[0]][rndm[1]].box[rndm[2]] = OLD_1;
    map[rndm[3]][rndm[4]].box[rndm[5]] = OLD_2;
}

double random(int s,int t){
    double num = 0.0;
    num = (double)rand(s, t)/(1 + RAND_MAX);
    return num;
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
            if(r < pow(exp(1.0), -diff_Cost/T));{
                old_cost = new_cost; /*Accept move*/
            }else{
                UndoPlacement();
            }
        } /*End one temperature*/
        T = UpdateTemp(T);
    }
}
