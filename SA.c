#include "decs.h"

int ExitCriterion(double T){
    if(T > FinalTemp){
        return False;
    }else{
        return True;
    }
}

Coordinatetype move_candidate(int *level){
    Coordinatetype p;
    while (1){
        p.x = rand() % floor_width;
        p.y = rand() % floor_height;
        *level = rand() % n_box ;
        if(map[p.x][p.y].floor_kind == Shelf) break;
    }
    return p;
}

//変数を定義する
//型を変えてreturnしておく？
//その方が元に戻しやすいかも
void PerturbPlacementViaMove(){ //元の状態を記憶しておく
    Coordinatetype p, q;
    int level_p, level_q;
    int OLD_1, OLD_2;
    while(1){
        //ランダムに2つのボックスの座標を生成
        p = move_candidate(&level_p);
        q = move_candidate(&level_q);

        if((map[p.x][p.y].box[level_p] != Empty) || (map[q.x][q.y].box[level_q] != Empty)){//どちらかは部品が入っている
            //元の状態を保持
            OLD_1 = map[p.x][p.y].box[level_p]; 
            OLD_2 = map[q.x][q.y].box[level_q];
            //部品を入れ替える
            map[p.x][p.y].box[level_p] = OLD_2;
            map[q.x][q.y].box[level_q] = OLD_1;

            item_info[OLD_1].position = q;
            item_info[OLD_2].position = p;

            item_info[OLD_1].box_level = level_q;
            item_info[OLD_2].box_level = level_p;

            //map[p.x][p.y].n_empty--;
            //SAの空のボックスの数の入れ替え

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
    num = (double)(s-t)*rand()/(1 + RAND_MAX) + s;
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
