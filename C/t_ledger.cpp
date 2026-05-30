#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>

using namespace std;
#define endl "\n"
#define ll long long

const string FILE_PATH = "data/ledger.csv";

void show_mene(){
    cout << endl;
    cout << "============ 가계부 ============" << endl;
    cout << "1. 내역 입력" << endl;
    cout << "2. 전체 조회" << endl;
    cout << "3. 통계 보기" << endl;
    cout << "0. 종료" << endl;
    cout << "===============================" << endl;
    cout << "선택: ";
}

void add_entry(){
    string date, category, type, memo;
    ll amount;

    cout << "날짜(YYYY-MM-DD): "; cin >> date;
    cout << "분류(식비/월급 등): "; cin >> category;
    cout << "수입/지출: "; cin >> type;
    cout << "금액: "; cin >> amount;
    cout << "메모: "; cin >> memo;

    ofstream fout(FILE_PATH, ios::app);
    if(!fout){
        cout << "[error] 파일 열기 실패" << endl;
        return;
    }

    fout << date << ',' << category << ',' << type << ',' << amount << ',' << memo << endl;
    fout.close();

    cout << ">> 저장 완료" << endl;
}

void view_all(){
    ifstream fin(FILE_PATH);
    if(!fin){
        cout << "저장된 내역이 없습니다." << endl;
        return;
    }

    string line;
    int cnt = 0;

    cout << endl;
    cout << string(60, '-') << endl;
    cout << left << setw(14) << "날짜"
        << left << setw(11) << "분류"
        << left << setw(10) << "구분"
        << right << setw(15) << "금액"
        << "     " << "메모" << endl;
    cout << string(60, '-') << endl;

    while(getline(fin, line)){
        if(line.empty()) continue;
        string date, category, type, samount, memo;
        stringstream ss(line);

        getline(ss, date, ',');
        getline(ss, category, ',');
        getline(ss, type, ',');
        getline(ss, samount, ',');
        getline(ss, memo, ',');
        ll amount = stoll(samount);

        cout << left << setw(13) << date
        << left << setw(10) << category
        << left << setw(8) << type
        << right << setw(15) << amount
        << "     " << memo << endl;
        cnt++;
    }
    fin.close();
    cout << string(60, '-') << endl;
    cout << ">> 총 " << cnt << "건" << endl;
}

void view_stats(){
    ifstream fin(FILE_PATH);
    if(!fin){
        cout << "저장된 내역이 없습니다." << endl;
        return;
    }

    ll total_income = 0, total_outcome = 0;
    map<string, ll> by_category;

    string line;
    while(getline(fin, line)){
        if(line.empty()) continue;
        string date, category, type, samount, memo;
        stringstream ss(line);

        getline(ss, date, ',');
        getline(ss, category, ',');
        getline(ss, type, ',');
        getline(ss, samount, ',');
        getline(ss, memo, ',');
        ll amount = stoll(samount);

        if(type == "수입") total_income += amount;
        else total_outcome += amount;
        by_category[category] += amount;
    }
    fin.close();
    cout << "============== 통계 ==============" << endl;
    cout << "총수입: " << total_income << "원" << endl;
    cout << "총지출: " << total_outcome << "원" << endl;
    cout << "잔액  : " << (total_income - total_outcome) << "원" << endl;

    cout << endl << "=========== 분류별 합계 ===========" << endl;
    for(auto& p : by_category){
        cout << left << setw(12) << p.first
             << right << setw(12) << p.second << "원" << endl;
    }
}

int main(){
    int choice;

    while(true){
        show_mene();
        cin >> choice;

        if(choice == 1) add_entry();
        else if(choice == 2) view_all();
        else if(choice == 3) view_stats();
        else if(choice == 0){ cout << "종료합니다." << endl; break; }
        else cout << "잘못된 입력입니다." << endl;
    }
}