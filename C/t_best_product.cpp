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

struct Customer {
    string name;
    int age;
    ll asset;
    string risk;
};

struct Product {
    string name;
    string desc;
};

vector<Customer> customers;
vector<Product> products = {
    { "정기예금",    "안전, 원금보장" },
    { "적금",        "소액 적립식" },
    { "채권형펀드",  "중위험 중수익" },
    { "주식형펀드",  "고위험 고수익" },
    { "청년우대적금","35세 이하 우대" }
};

void load_customers(){
    ifstream fin("data/customers.csv");
    if(!fin){ cout << "[error] 고객 파일 열기 실패" << endl; return; }

    string line;
    bool is_header = true;
    while(getline(fin, line)){
        if(is_header){ is_header = false; continue; }
        if(line.empty()) continue;
        stringstream ss(line);
        string name, age_str, asset_str, risk;
        getline(ss, name, ',');
        getline(ss, age_str, ',');
        getline(ss, asset_str, ',');
        getline(ss, risk, ',');
        customers.push_back({ name, stoi(age_str), stoll(asset_str), risk });
    }
    fin.close();
}

int calc_score(const Customer& c, const string& product_name){
    int score = 0;
    if(product_name == "정기예금"){
        if(c.risk == "안정형") score += 50;
        if(c.age >= 50) score += 30;
        if(c.asset >= 50000000) score += 20;
    }
    else if(product_name == "적금"){
        if(c.asset < 50000000) score += 40;
        if(c.age < 40) score += 30;
        if(c.risk == "안정형") score += 20;
    }
    else if(product_name == "채권형펀드"){
        if(c.risk == "중립형") score += 60;
        if(c.asset >= 30000000) score += 20;
    }
    else if(product_name == "주식형펀드"){
        if(c.risk == "공격형") score += 60;
        if(c.asset >= 100000000) score += 30;
    }
    else if(product_name == "청년우대적금"){
        if(c.age <= 35) score += 70;
        else score = 0;
    }
    return score;
}

string best_product(const Customer& c, int& outScore){
    string best = "";
    int best_score = -1;
    for(auto& p : products){
        int s = calc_score(c, p.name);
        if(s > best_score){
            best_score = s;
            best = p.name;
        }
    }
    outScore = best_score;
    return best;
}

int main(){
    load_customers();

    cout << left << setw(12) << "고객명"
         << setw(6) << "나이"
         << setw(10) << "성향"
         << setw(16) << "추천상품"
         << "적합도" << endl;
    cout << string(50, '-') << endl;

    for(auto& c : customers){
        int score;
        string rec = best_product(c, score);
        cout << left << setw(12) << c.name
             << setw(6) << c.age
             << setw(10) << c.risk
             << setw(16) << rec
             << score << endl;
    }
    cout << string(50, '-') << endl;
    cout << "총 " << customers.size() << "명 추천 완료" << endl;

    return 0;
}