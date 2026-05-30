#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
#define endl "\n"
#define ll long long

struct Data{
    string name;
    string product;
    ll amount;

    bool operator<(const Data &other) const{
        return amount > other.amount;
    }
};

struct Ndata{
    string name;
    string product;

    bool operator<(const Ndata &other) const{
        return name < other.name;
    }
};

vector<Data> v1;
vector<Ndata> v2;
ifstream fin;
ofstream fout;

void input(){
    fin.open("data/input.csv");
    if(!fin){
        cout << "[error] 파일 열기 실패" << endl;
        return;
    }
}

void output(){
    int num = 1;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    fout.open("data/output1.csv");
    fout << "번호,고객명,상품,금액" << endl; 
    for(auto &data : v1){
        fout << num << ',' 
            << data.name << ','
            << data.product << ','
            << data.amount << endl;
        num++;
    }

    fout.close();
    num = 1;

    fout.open("data/output2.csv");
    fout << "번호,고객명,상품,금액" << endl;
    for(auto &data : v2){
        fout << num << ','
            << data.name << ','
            << data.product << ','
            << "N/A" << endl;
        num++;
    }

    fout.close();

    cout << endl;
    cout << string(38, '-') << endl;
    cout << "정상 데이터 총 " << v1.size() << "건 -> output1.csv (금액순)" << endl;
    cout << "누락 데이터 총 " << v2.size() << "건 -> output2.csv (이름순)" << endl;
    cout << string(38, '-') << endl;
    cout << endl;
}

void func(){
    string line;
    bool is_header = true;
    int num = 1;
    int null_cnt = 0;

    cout << left << setw(8) << "번호"
        << left << setw(12) << "고객명"
        << left << setw(10) << "상품"
        << right << setw(15) << "금액" << endl;
    cout << string(38, '-') << endl;

    while(getline(fin, line)){
        if(is_header){
            is_header = false;
            continue;
        }
        if(line.empty()) continue;

        stringstream ss(line);
        string name, product, amount;

        getline(ss, name, ',');
        getline(ss, product, ',');
        getline(ss, amount, ',');

        cout << left << setw(6) << num
            << left << setw(12) << name
            << left << setw(8) << product;

        if(amount.empty()){
            cout << right << setw(15) << "N/A";
            null_cnt++;
            v2.push_back({name, product});
        }
        else{
            ll amountl = stoll(amount);
            cout << right << setw(15) << amountl;
            v1.push_back({name, product, amountl});
        }
        cout << endl;
        num++;
    }
    cout << string(38, '-') << endl;
    cout << "총 " << num - 1 << "건의 데이터 (누락 금액 데이터: " << null_cnt << "건)" << endl;
}

int main(){
    input();
    func();
    output();

    fin.close();
    fout.close();
}