#include <iostream>
#include<random>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>
#include<algorithm>
#include <unistd.h>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<utility>
#include<windows.h>
#include<time.h>

using namespace std;



bool Check_intersection(vector<int> inter,vector<vector<int>> street_check)
{
    float y1,y2,y3,y4;
    float x1,x2,x3,x4;
    float xi,yi;
    float x_num,x_den;
    float y_num,y_den;
    for(int i=0;i<inter.size()-2;i+=2)
    {
        x1 = inter[i];
        y1 = inter[i+1];
        x2 = inter[i+2];
        y2 = inter[i+3];
        for(int j=0;j<street_check.size();j++)
        {
            for(int k=0;k<street_check[j].size()-2;k+=2)
            {
                x3 = street_check[j][k];
                y3 = street_check[j][k+1];
                x4 = street_check[j][k+2];
                y4 = street_check[j][k+3];

                x_den = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
                x_num = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));



                if(x_den == 0)
                {
                    continue;
                }
                xi = x_num/x_den;

                y_den = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
                y_num = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);

                if(y_den == 0)
                {
                    continue;
                }
                yi = y_num/y_den;

                if((min(x1,x2)<=xi && xi<=max(x1,x2)) && (min(y1,y2)<=yi && yi<=max(y1,y2))
                    && (min(x3,x4)<=xi && xi<=max(x3,x4)) && (min(y3,y4)<=yi && yi<=max(y3,y4)))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool intersect(vector<int> vect, int x, int y, int j)
{
    float x1,x2,x3,x4;
    float y1,y2,y3,y4;
    int len = vect.size();
    float xi,yi;
    x3 = vect[len-2];
    y3 = vect[len-1];
    x4 = (float)x;
    y4 = (float)y;

    float x_num,x_den;
    float y_num,y_den;


    if(j==2)
    {
        return true;
    }
    for(int i=0; i<vect.size()-4; i+=2)
    {
        x1 = vect[i];
        y1 = vect[i+1];

        x2 = vect[i+2];
        y2 = vect[i+3];

        x_den = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
        x_num = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));


        if(x_den == 0)
        {
            return true;
        }
        xi = x_num/x_den;

        y_den = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
        y_num = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);


        if(y_den == 0)
        {
            return true;
        }
        yi = y_num/y_den;

        if((min(x1,x2)<=xi && xi<=max(x1,x2)) && (min(y1,y2)<=yi && yi<=max(y1,y2))
            && (min(x3,x4)<=xi && xi<=max(x3,x4)) && (min(y3,y4)<=yi && yi<=max(y3,y4)))
        {
            return false;
        }
    }
    return true;
}

int main (int argc, char **argv)
{
    srand(time(0));
    ofstream outfile;
    outfile.open("out.txt");
    int s_flag,n_flag = 0;
    int l_flag,c_flag = 0;
    string s_v,n_v,l_v,c_v;
    int s_streets = 10;
    int n_segments = 5;
    int c_positive = 20;
    int c_negative = 20*(-1);
    int sleep_time = 5*(1000);
    int x_coor[500];
    int y_coor[500];
    static constexpr char Random_char[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                           "abcdefghijklmnopqrstuvwxyz"
                                          };
    vector<vector<int>> myVector;
    vector<int> myVector2;
    string pass;
    int random_street,random_linesegment,random_coordinates;
    int command;

    while(!cin.eof()){
    while ((command = getopt (argc, argv, "s:n:l:c:?")) != -1)
        switch (command)
        {
        case 's':
            if(s_flag);
            s_v = optarg;
            s_streets = atoi(s_v.c_str());
            if(s_streets < 2){
                std::cerr<<"Error: -s must have value greater than or equal to 2"<<std::endl;
                return 1;
            }
            break;

        case 'n':
            if(n_flag);
            n_v = optarg;
            n_segments = atoi(n_v.c_str());
            if(n_segments < 1){
                std::cerr<<"Error: -n must have value greater than or equal to 1"<<std::endl;
                return 1;
            }

            break;

        case 'l':
            if(l_flag);

            l_v = optarg;
            int l1;
            l1 = atoi(l_v.c_str());
            sleep_time = l1*1000;
            if(l1 < 5){
                std::cerr<<"Error: -l must have value greater than or equal to 5"<<std::endl;
                return 1;
            }

            break;

        case 'c':
            if(c_flag);

            c_v = optarg;
            c_positive = atoi(c_v.c_str());

            c_negative = c_positive*(-1);
            if(c_positive < 1){
                std::cerr<<"Error: -c must have value greater than or equal to 1"<<std::endl;
                return 1;
            }
            break;

        case '?':

                std::cerr<<"Error: unknown option"<<std::endl;
                return 1;
        default:
            return 0;


        }


        const unsigned int Size = 500;
        char Array1[Size];
        char Array2[Size];
        char Array3[Size];


        random_street = (rand()% (s_streets - 2 + 1)) + 2;

        int counter;
        int inter_flag;
        int flag_street_intersect;

        for (int i=0;i<random_street;i++)
        {

            random_linesegment = (rand()% (n_segments - 1 + 1)) + 1;
            Array1[i] = Random_char[rand()%(sizeof(Random_char)-1)]  ;
            Array2[i] = Random_char[rand()%(sizeof(Random_char)-1)]  ;
            Array3[i] = Random_char[rand()%(sizeof(Random_char)-1)]  ;
            cout<<"a"<<" "<<'"'<<Array1[i]<<Array2[i]<<Array3[i]<<'"';
            outfile<<"a"<<" "<<'"'<<Array1[i]<<Array2[i]<<Array3[i]<<'"';
            vector<int> vect2;

            if(i==random_street-1)
            {


                do


                {
                    if(counter==2)
                    {
                        std::cerr<<"Error: Failed to generate valid graph specification after 35 simultaneous attempts"<<std::endl;
                        return 1;
                    }
                    counter++;
                    vect2.clear();
                    for(int j=0;j<random_linesegment + 1;j++)
                    {
                        if(j>=2)
                        {
                            inter_flag = 0;
                            while(!inter_flag)

                            {
                                x_coor[j] = (rand()%(c_positive - c_negative +1)) + c_negative;

                                y_coor[j] = (rand()%(c_positive - c_negative + 1)) + c_negative;

                                if(intersect(vect2,x_coor[j],y_coor[j],j)/*&& overlap(myVector,temp)*/)
                                {
                                    vect2.push_back(x_coor[j]);
                                    vect2.push_back(y_coor[j]);
                                    inter_flag = 1;
                                }
                            }
                        }
                        else if(j==1)
                        {
                            inter_flag = 0;
                            while(!inter_flag)

                            {
                                x_coor[j] = (rand()%(c_positive - c_negative +1)) + c_negative;

                                y_coor[j] = (rand()%(c_positive - c_negative + 1)) + c_negative;

                                if(true/*overlap(myVector,temp)*/)
                                {
                                    vect2.push_back(x_coor[j]);
                                    vect2.push_back(y_coor[j]);
                                    inter_flag = 1;
                                }
                            }

                        }
                        else
                        {
                            x_coor[j] = (rand()%(c_positive - c_negative +1)) + c_negative;
                            vect2.push_back(x_coor[j]);
                            y_coor[j] = (rand()%(c_positive - c_negative + 1)) + c_negative;
                            vect2.push_back(y_coor[j]);
                        }

                    }
                    if(!flag_street_intersect)
                    {
                        if(Check_intersection(vect2,myVector))
                        {
                            flag_street_intersect = 1;
                        }
                    }

                }while(!flag_street_intersect);
                for(int j=0;j<random_linesegment+1;j++)
                {
                    cout<<" "<<"("<<x_coor[j]<<","<<y_coor[j]<<")";
                    outfile<<" "<<"("<<x_coor[j]<<","<<y_coor[j]<<")";
                }
            }
            else{
                for(int j=0;j<random_linesegment + 1;j++)
                {
                    if(j>=2)
                    {
                        inter_flag = 0;
                        while(!inter_flag)
                        {
                            x_coor[j] = (rand()%(c_positive - c_negative +1)) + c_negative;

                            y_coor[j] = (rand()%(c_positive - c_negative + 1)) + c_negative;

                            if(true/*intersect(temp,Arrayx[j],Arrayy[j],j) && overlap(myVector,temp)*/)
                            {
                                vect2.push_back(x_coor[j]);
                                vect2.push_back(y_coor[j]);
                                inter_flag = 1;
                            }
                        }
                    }
                    else if(j==1)
                    {
                        inter_flag = 0;
                        while(!inter_flag)
                        {
                            x_coor[j] = (rand()%(c_positive - c_negative +1)) + c_negative;

                            y_coor[j] = (rand()%(c_positive - c_negative + 1)) + c_negative;

                            if(true/*overlap(myVector,temp)*/)
                            {
                                vect2.push_back(x_coor[j]);
                                vect2.push_back(y_coor[j]);
                                inter_flag = 1;
                            }
                        }

                    }
                    else
                    {
                        x_coor[j] = (rand()%(c_positive - c_negative +1)) + c_negative;
                        vect2.push_back(x_coor[j]);
                        y_coor[j] = (rand()%(c_positive - c_negative + 1)) + c_negative;
                        vect2.push_back(y_coor[j]);
                    }

                    //pair<int,int> pairs = make_pair(Arrayx[j],Arrayy[j]);
                    //cout<<" "<<pairs.first<<" "<<pairs.second;
                    cout<<" "<<"("<<x_coor[j]<<","<<y_coor[j]<<")";
                    outfile<<" "<<"("<<x_coor[j]<<","<<y_coor[j]<<")";
                }
                if(!flag_street_intersect && i!=0)
                {
                    if(Check_intersection(vect2,myVector))
                    {
                        flag_street_intersect = 1;
                    }
                }
            }

            myVector.push_back(vect2);
            cout<<endl;
            outfile<<endl;
        }

        cout<<"g"<<endl;
        outfile<<"g"<<endl;

Sleep(sleep_time);
for(int i=0;i<random_street;i++)
{
    cout<<"r"<<" "<<'"'<<Array1[i]<<Array2[i]<<Array3[i]<<'"'<<endl;
    outfile<<"r"<<" "<<'"'<<Array1[i]<<Array2[i]<<Array3[i]<<'"'<<endl;
}


for(int i=0;i<myVector.size();i++){
    myVector.clear();
}
//outfile.close();

    }


}

