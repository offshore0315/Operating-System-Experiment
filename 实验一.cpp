#include <cstdio>
#include <algorithm>
#include<iostream> 
/*
�ó���ʵ�ֵ��Ƿ���ռʽ�ĸ���Ӧ�����ȵ�ģ��
*/

using namespace std;

struct Task {
	int tj, sj;//tjΪ����ʱ�䣬sjΪ����ʱ�� 
	int order;//���ȴ���
	int id;//��ҵ��
	int startTime;//��ʼʱ��
	int cyclingTime;//��תʱ��
	int weightedTurnaroundTime;//��Ȩ��תʱ��
	float weight;//��Ӧ��
	bool finished;//���жϳ����Ƿ���� 
};

Task t[100];

bool cmp1(Task A, Task B) {
	return A.tj < B.tj;
}//���ص���ʱ����� 

bool cmp2(Task A, Task B) {
	if (A.weight == B.weight) {
		return A.tj < B.tj;
	} else
		return A.weight > B.weight;
}//�Ƚ�A��B����Ӧ�� ����Ȱ��յ���ʱ�����򣬲�ͬ������Ӧ������ 

int start_Time(int x) {
	int h = x / 60;//Сʱ 
	int minute = x % 60;//���� 
	return h * 100 + minute;
}

int main() {
	int K;
	printf("��������ҵ��:");
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d%d", &t[i].tj, &t[i].sj);
		t[i].tj = (t[i].tj / 100) * 60 + t[i].tj % 100;
		t[i].id = i + 1;//���������±� 
		t[i].finished = false;
	}
	sort(t, t + K, cmp1);//����д�����ʱ������ 
	int time = t[0].tj;//����ʱ�丳��ֵ �����ӵ�һ�����򱻵��ȿ�ʼ 
	for (int i = 0; i < K; i++) {
		sort(t, t + K, cmp2);//�Ƚ���Ӧ�� ��������Ӧ�Ƚ������У� 
		if (t[0].startTime > time)
			time = t[0].startTime;//��ת����һ�������ʱ�� 
		t[0].order = i + 1;//���ȴ��� 
		t[0].startTime = time;// ��ʼ����ʱ�� 
		t[0].cyclingTime = t[0].startTime - t[0].tj + t[0].sj;//��תʱ�� ����ʼ-����+���� 
		t[0].weightedTurnaroundTime = t[0].cyclingTime / t[0].sj;// ��Ȩ��תʱ�� 
		t[0].finished = true;
		time += t[0].sj;//��ʱ��һֱ�ۼ� 
		for (int j = 0; j < K; j++) {
			if (t[j].finished) {
				t[j].weight = -0x7FFFFFFF;//�������Ӧ����Ϊ����С���Զ�������� 
				continue;
			}
			if (t[j].tj > time) {
				t[j].weight = 0;
				continue;//��δ��ʼ���ȸó��򣬲��μ�������Ӧ�ȱȽ� 
			}
			t[j].weight = 1 + (time - t[j].tj) / t[j].sj;// 
		}
	}
	printf("���ȴ���\t��ҵ��\t����ʱ��\t��תʱ��(min)\t��Ȩ��תʱ��\n");
	int runTime = 0;//����תʱ�� 
	int cycle = 0;//�ܴ�Ȩ��תʱ�� 
	for (int i = 0; i < K; i++) {
		printf("%d\t\t%d\t%d\t\t%d\t\t%d\n", t[i].order, t[i].id, start_Time(t[i].startTime), t[i].cyclingTime,
		       t[i].weightedTurnaroundTime);
		runTime += t[i].cyclingTime;
		cycle += t[i].weightedTurnaroundTime;
	}
	printf("ƽ����תʱ��%.2f(min) ƽ����Ȩ��תʱ��%.2f\n", float(runTime) / float(K), float(cycle) / float(K));
} 
