#include <cstdio>
#include <string.h>

using namespace std;

#define M 1000
#define N 100

int allocation[N][M], Max[N][M], need[N][M], available[M];
int n, m;
bool done[N] = {false};
int work[M];
int security[M];// safe sequeue

int isFinish() {
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < m; j++)
			if (done[i] == false && need[i][j] <= work[j])
				count ++;
		if (count == m) {
			done[i] = true;
			for (int k = 0; k < m; k++)
				work[k] += allocation[i][k];
			return i;
		}
	}
	return -1;
}

bool banker() {
	for (int i = 0; i < n; i++)
		done[i] = false;
	for (int i = 0; i < m; i++)
		work[i] = available[i];
	int tag = -1;
	for (int t = 0; t < n; t++) {
		int status = isFinish();
		if (status != -1)
			security[++tag] = status;
	}
	if (tag == n - 1)
		return true;
	return false;
}

void show() {
	printf("%d", security[0] + 1);
	for (int i = 1; i < n; i++)
		printf("->%d ", security[i] + 1);
	printf("\n");
}

int main() {
	scanf("%d%d", &n, &m);
	printf("please input allocation matrix:\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &allocation[i][j]);
	printf("please input max need matrix:\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &Max[i][j]);
	printf("please input available matrix:\n");
	for (int i = 0; i < m; i++)
		scanf("%d", &available[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			need[i][j] = Max[i][j] - allocation[i][j];

	if (banker())
		show();
	else {
		printf("can't allocate resource!'");
		return 0;
	}

	printf("please input which process you want to allocate:(0 end the program)");
	int id;
	scanf("%d", &id);
	id--;
	if (id == -1)
		return 0;
	printf("please input the allocation request:");
	int request[M];
	for (int i = 0; i < m; i++)
		scanf("%d", &request[i]);
	for (int j = 0; j < m; j++) {
		if (request[j] > need[id][j] || request[j] > available[j]) {
			printf("can't allocate'");
			return 0;
		} else {
			available[j] -= request[j];
			allocation[id][j] += request[j];
			need[id][j] -= request[j];
		}
	}
	if (banker()) {
		printf("allocate success!");
		show();
	} else {
		printf("can't allocate");
		return 0;
	}

	return 0;
}