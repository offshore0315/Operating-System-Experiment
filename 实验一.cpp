#include <cstdio>
#include <algorithm>
#include<iostream> 
/*
该程序实现的是非抢占式的高响应度优先的模拟
*/

using namespace std;

struct Task {
	int tj, sj;//tj为调度时间，sj为运行时间 
	int order;//调度次序
	int id;//作业号
	int startTime;//开始时间
	int cyclingTime;//周转时间
	int weightedTurnaroundTime;//带权周转时间
	float weight;//响应比
	bool finished;//来判断程序是否完成 
};

Task t[100];

bool cmp1(Task A, Task B) {
	return A.tj < B.tj;
}//返回调度时间次序 

bool cmp2(Task A, Task B) {
	if (A.weight == B.weight) {
		return A.tj < B.tj;
	} else
		return A.weight > B.weight;
}//比较A和B的相应比 ，相等按照调度时间排序，不同则按照响应比排序 

int start_Time(int x) {
	int h = x / 60;//小时 
	int minute = x % 60;//分钟 
	return h * 100 + minute;
}

int main() {
	int K;
	printf("请输入作业数:");
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d%d", &t[i].tj, &t[i].sj);
		t[i].tj = (t[i].tj / 100) * 60 + t[i].tj % 100;
		t[i].id = i + 1;//考虑数组下标 
		t[i].finished = false;
	}
	sort(t, t + K, cmp1);//按照写入调度时间排序 
	int time = t[0].tj;//对总时间赋初值 ：即从第一个程序被调度开始 
	for (int i = 0; i < K; i++) {
		sort(t, t + K, cmp2);//比较响应比 （按照相应比降序排列） 
		if (t[0].startTime > time)
			time = t[0].startTime;//跳转到下一个任务的时间 
		t[0].order = i + 1;//调度次序 
		t[0].startTime = time;// 开始调度时间 
		t[0].cyclingTime = t[0].startTime - t[0].tj + t[0].sj;//周转时间 ：开始-调度+运行 
		t[0].weightedTurnaroundTime = t[0].cyclingTime / t[0].sj;// 带权周转时间 
		t[0].finished = true;
		time += t[0].sj;//总时间一直累加 
		for (int j = 0; j < K; j++) {
			if (t[j].finished) {
				t[j].weight = -0x7FFFFFFF;//完成了响应比设为无限小，自动排序到最后 
				continue;
			}
			if (t[j].tj > time) {
				t[j].weight = 0;
				continue;//还未开始调度该程序，不参加数组响应度比较 
			}
			t[j].weight = 1 + (time - t[j].tj) / t[j].sj;// 
		}
	}
	printf("调度次序\t作业号\t调度时间\t周转时间(min)\t带权周转时间\n");
	int runTime = 0;//总周转时间 
	int cycle = 0;//总带权周转时间 
	for (int i = 0; i < K; i++) {
		printf("%d\t\t%d\t%d\t\t%d\t\t%d\n", t[i].order, t[i].id, start_Time(t[i].startTime), t[i].cyclingTime,
		       t[i].weightedTurnaroundTime);
		runTime += t[i].cyclingTime;
		cycle += t[i].weightedTurnaroundTime;
	}
	printf("平均周转时间%.2f(min) 平均带权周转时间%.2f\n", float(runTime) / float(K), float(cycle) / float(K));
} 
