#include <iostream>
#include <string>

using namespace std;

struct grade {
	string name;
	int IDnum;
	int chinese;
	int math;
	int english;
	int total;
	int rank;
};

class GradeTable {
private:
	grade student[5];

public:
	GradeTable() {
		student[0].name = "李狗蛋";
		student[0].IDnum = 001;
		student[0].chinese = 19;
		student[0].math = 35;
		student[0].english = 98;
		student[1].name = "赵铁柱";
		student[1].IDnum = 002;
		student[1].chinese = 37;
		student[1].math = 54;
		student[1].english = 56;
		student[2].name = "王拉拉";
		student[2].IDnum = 003;
		student[2].chinese = 12;
		student[2].math = 68;
		student[2].english = 23;
		student[3].name = "张三";
		student[3].IDnum = 004;
		student[3].chinese = 69;
		student[3].math = 99;
		student[3].english = 0;
		student[4].name = "李四";
		student[4].IDnum = 005;
		student[4].chinese = 11;
		student[4].math = 75;
		student[4].english = 26;
	}

	void calTotal() {
		for (int i = 0; i < 5; i++) {
			student[i].total = student[i].chinese + student[i].math + student[i].english;
		}
	}

	void setRank() {
		grade tmp;
		for (int i = 0; i < 5; i++) {
			tmp = student[i];
			for (int j = 0; j < i; j++) {
				if (tmp.total < student[j].total) {
					for (int m = i; m > j; m--) {
						student[m] = student[m - 1];
					}
					student[j] = tmp;
					break;
				}
			}
		}
		tmp = student[0];
		student[0] = student[4];
		student[4] = tmp;
		tmp = student[1];
		student[1] = student[3];
		student[3] = tmp;
		for (int i = 0; i < 5; i++) {
			student[i].rank = i + 1;
		}
	}

	void printData() {
		cout << "姓名" << "\t" << "ID号" << "\t" << "语文" << "\t" << "数学" << "\t" << "英语" << "\t" << "总分" << "\t" << "排名" << endl;
		for (int i = 0; i < 5; i++) {
			cout << student[i].name << "\t" << student[i].IDnum << "\t" << student[i].chinese << "\t" << student[i].math << "\t" << student[i].english << "\t" << student[i].total << "\t" << student[i].rank << endl;
		}
	}

};

int main() {
	GradeTable gradeTable = GradeTable();
	gradeTable.calTotal();
	gradeTable.setRank();
	gradeTable.printData();

	while (true);
	return 0;
}
