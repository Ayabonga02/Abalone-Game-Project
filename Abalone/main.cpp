/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:38 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include "board.h"
#include "agent.h"
#include "cell.cpp"
#include "board.cpp"
#include "agent.cpp"
#include <ctype.h>

using namespace std;

int main(int argc, char** argv) {
        time_t now = time(NULL);
        srand(now);
        cout<<"Seed: "<<now<<endl;
        board abalone;
        string state(abalone);
        cout<<"Initial State:"<<endl<<state;
            agent* w;
            agent* b;
        string player = "";
        cout<<"Choose if you want to play with (human vs bot) or (bot vs bot)"<<endl;
        cout<<"Input Human or h for human vs bot) otherwise press any key to continue"<<endl;
        cin>>player;
        transform(player.begin(), player.end(), player.begin(), ::tolower);
        if(player == "human" || player == "h"){
            w = new humanAgent('O');
            b = new distAgent('@');
        }else{
            w = new randAgent('O');
            b = new distAgent('@');
        }
        movement* pom=nullptr;//previous opponent's move
        movement* mym=nullptr;//player's chosen move
        char c='O';
        int i=0;
        while(abalone.inPlay()){
            try{
                if(c=='O'){
                    movement mm = w->move(pom,abalone);
                    mym = new movement(mm);
                    if(pom)
                        delete pom;
                    pom = new movement(mm);
                }
                else{
                    movement mm = b->move(pom,abalone);
                    mym = new movement(mm);
                    if(pom)
                        delete pom;
                    pom = new movement(mm);
                }
            }
            catch(const string& s){
                cout<<s;
                return 1;
            }
                 
            bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
            cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;i++;  
            if(valid){
                string state(abalone);         
                cout<<"Next State:"<<endl<<state; 
            }
            else{
                cout<<"Invalid move!!"<<endl;
            }
            if(c=='O') 
                c='@';
                
            else
                c='O'; 
               
            delete mym;
            SLP(1);
            //system(CL);
            
        }
            //if(c='O'){
            if(abalone.woc == 3){
                cout<<"WINNER IS : "<<'@'<<endl;
            }else{
                cout<<"WINNER IS : "<<'O'<<endl;
            }
        if(pom)
            delete pom;
        delete w;
        delete b;
        
        return 0;

}

