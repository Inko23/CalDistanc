#include "decs.h"

double cal_all_dist(void);

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
SWAPtype PerturbPlacementViaMove(){ //元の状態を記憶しておく
    Coordinatetype p, q;
    int level_p, level_q;
    int item_p, item_q;
    SWAPtype rtn_val;
    while(1){
        //ランダムに2つのボックスの座標を生成
        p = move_candidate(&level_p);
        q = move_candidate(&level_q);

        if((map[p.x][p.y].box[level_p] != Empty) || (map[q.x][q.y].box[level_q] != Empty)){//どちらかは部品が入っている
            //マップ情報の更新------------------begin-----------------------
            //元の状態を保持
            item_p = map[p.x][p.y].box[level_p]; 
            item_q = map[q.x][q.y].box[level_q];
            //部品を入れ替える
            map[p.x][p.y].box[level_p] = item_q;
            map[q.x][q.y].box[level_q] = item_p;

            //SAの空のボックスの数の入れ替え
            if(item_p == Empty && item_q !=Empty){ //pの元の状態が空&&qが空でないなら
                map[p.x][p.y].n_empty--;
                map[q.x][q.y].n_empty++;
            }else if(item_q == Empty && item_p !=Empty){ //qの元の状態が空&&pが空でないなら
                map[q.x][q.y].n_empty--;
                map[p.x][p.y].n_empty++;
            }
            //マップ情報の更新--------------------end---------------------

            
            //部品情報の更新------------------begin-----------------------
            if(item_p != Empty){
                item_info[item_p].position = q;
                item_info[item_p].box_level = level_q;
            }
            if(item_q != Empty){
                item_info[item_q].position = p;
                item_info[item_q].box_level = level_p;
            }
            //部品情報の更新--------------------end---------------------

            break;
        }    
    }
    rtn_val.p = p;
    rtn_val.q = q;
    rtn_val.level_p = level_p;
    rtn_val.level_q = level_q;

    return rtn_val;    
}

//Acceptされなかった時の元の座標に戻す関数
void UndoPlacement(SWAPtype rev_val){
    int item_p, item_q;

    //マップ情報を戻す--------------------begin---------------------
    item_p = map[rev_val.p.x][rev_val.p.y].box[rev_val.level_p]; 
    item_q = map[rev_val.q.x][rev_val.q.y].box[rev_val.level_q];
    
    map[rev_val.p.x][rev_val.p.y].box[rev_val.level_p] = item_q;
    map[rev_val.q.x][rev_val.q.y].box[rev_val.level_q] = item_p;

    //SAの空のボックスの数の入れ替え
    if(item_p == Empty && item_q !=Empty){ //pの元の状態が空&&qが空じゃないなら
        map[rev_val.p.x][rev_val.p.y].n_empty--;
        map[rev_val.q.x][rev_val.q.y].n_empty++;
    }else if(item_q == Empty && item_p !=Empty){ //qの元の状態が空&&pが空じゃないなら
        map[rev_val.q.x][rev_val.q.y].n_empty--;
        map[rev_val.p.x][rev_val.p.y].n_empty++;
    }
    //マップ情報を戻す--------------------end---------------------

    //部品情報を戻す------------------begin-----------------------
    if(item_p != Empty){
        item_info[item_p].position = rev_val.q;
        item_info[item_p].box_level = rev_val.level_q;
    }
    if(item_q != Empty){
        item_info[item_q].position = rev_val.p;
        item_info[item_q].box_level = rev_val.level_p;
    }
    //部品情報を戻す--------------------end---------------------

}

double myrandom(int s,int t){
    double num = 0.0;
    num = (double)(s-t)*rand()/(1.0 + (double)RAND_MAX) + s;
    return num;
}

double UpdateTemp(double Temp){
    return CoolingRate * Temp;
    //return (Temp / (x + 1)); //xが引数に必要
}

void SA(){
    int i;
    double T;
    double r = 0;
    SWAPtype swap_info;
    T = InitialTemperature;
    
    while(ExitCriterion(T) == False){
        old_cost = cal_all_dist();
        for(i=0; i<InnerLoopCount; i++){ /*One templerature*/
            swap_info = PerturbPlacementViaMove();
            new_cost = cal_all_dist();
            diff_cost = new_cost - old_cost;
            r = myrandom(0,1);
            if(r < pow(exp(1.0), -diff_cost/T)){
                old_cost = new_cost; /*Accept move*/
            }else{
                UndoPlacement(swap_info);
            }
        } /*End one temperature*/
        T = UpdateTemp(T);
    }
}
