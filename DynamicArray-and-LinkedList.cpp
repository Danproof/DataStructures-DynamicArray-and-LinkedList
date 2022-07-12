#include<iostream>
#include<Windows.h>
#include<ctime>
using namespace std;

struct Candy {
	string producer;
	int weight;
	string type;
};

struct DynamicArray {
	int N = 1;
	Candy* DA = new Candy[N];
	int candies = 0;

	~DynamicArray() {
			delete[] DA;
	}

	int size() {
		return candies;
	}

	void capacity_x2() {
		Candy* DA2 = new Candy[N * 2];
		for (int i = 0; i < candies; i++)
			DA2[i] = DA[i];
		delete[] DA;
		DA = DA2;
		N *= 2;
	}

	void push_back(Candy c) {
		DA[candies] = c;
		candies++;
		if (candies == N)
			capacity_x2();
	}

	void push_front(Candy c) {
		for (int i = 0; i < candies; i++)
			DA[candies - i] = DA[candies - i - 1];
		DA[0] = c;
		candies++;
		if (candies == N)
			capacity_x2();
	}

	void pop_back() {
		if (candies) 
			candies--;
		else
			throw "Немає елементів, які можна видалити";
	}

	void pop_front() {
		if (N) {
			N--;
			for (int i = 0; i < size(); i++)
				DA[i] = DA[i + 1];
		}
		else
			throw "Немає елементів, які можна видалити";
	}

	Candy get(int i) {
		if(candies)
		return DA[i];
		else
			throw "Немає елементів";
	}

	void print(){
		if (candies) {
			for (int i = 0; i < candies; i++) {
				cout << "Параметри " << i + 1 << " цукерки:" << endl;
				cout << "Виробник - " << DA[i].producer << endl;
				cout << "Вага - " << DA[i].weight << endl;
				cout << "Смак - " << DA[i].type << endl;
			}
		}
		else
			throw "Немає елементів";
	}

};

struct Node {
	Candy c;
	Node* next;
	Node(Candy& new_c, Node* next_node = nullptr) {
		c = new_c;
		next = next_node;
	}
};

struct LinkedList {
	int N = 0;
	Node* head;

	~LinkedList() {
		while (N)
			pop_front();
	}

	int size() {
		return N;
	}

	void push_front(Candy& new_c) {
		if(N)
			head = new Node(new_c, head);
		else 
			head = new Node(new_c);
		N++;
	}

	void push_back(Candy& new_c) {
		if (N == 0)
			push_front(new_c);
		else {
			Node* temporary = head;
			while (temporary->next != nullptr)
				temporary = temporary->next;
			temporary->next = new Node(new_c);
			N++;
		}
	}

	Candy get(int n) {
		if (N) {
			Node* temporary = head;
			for (int i = 0; i < n; i++)
				temporary = temporary->next;
			return temporary->c;
		}
		else
			throw "Немає елементів";
	}

	void pop_front() {
		Node* temporary = head;
		head = head->next;
		delete temporary;
		N--;
	}

	void pop_back() {
		Node* temporary = head;
		for (int i = 0; i < N-2; i++)
			temporary = temporary->next;
		delete temporary->next;
		temporary->next = nullptr;
		N--;
	}

	void print() {
		if (N) {
			for (int i = 0; i < N; i++) {
				Candy c = get(i);
				cout << "Параметри " << i << " цукерки:" << endl;
				cout << "Виробник - " << c.producer << endl;
				cout << "Вага - " << c.weight << endl;
				cout << "Смак - " << c.type << endl;
			}
		}
		else
			throw "Немає елементів";
	}
};

void percentage(double DA_seconds, double LL_seconds, int sum = 0) {
	if (DA_seconds > LL_seconds) {
		double one_percent = DA_seconds / 100;
		double percent = (DA_seconds - LL_seconds) / one_percent;
		if(sum)
			cout << "В однозв'язному списку всі ці операції виконалися на " << percent << " % швидше" << endl;
		else
		cout << "В однозв'язному списку ця операція на " << percent << " % швидша" << endl;
	}
	else {
		double one_percent = LL_seconds / 100;
		double percent = (LL_seconds - DA_seconds) / one_percent;
		if(sum)
			cout << "В динамічному масиві всі ці операції виконалися на " << percent << " % швидше" << endl;
		else
			cout << "В динамічному масиві ця операція на " << percent << " % швидша" << endl;

	}
}

int main() {
	SetConsoleOutputCP(1251);
	DynamicArray DA;
	LinkedList LL;
	Candy c;

	//додати в кінець 50000 елементів

	clock_t start = clock();
	for (int i = 0; i < 50000; i++) 
		DA.push_back(c);
	clock_t end = clock();
	double DA_push_back_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час додання 50000 елементів в кінець динамічного масиву - " << DA_push_back_seconds << endl;
	
	start = clock();
	for (int i = 0; i < 50000; i++)
		LL.push_back(c);
	end = clock();
	double LL_push_back_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час додання 50000 елементів в кінець однозв'язного списку - " << LL_push_back_seconds << endl;

	percentage(DA_push_back_seconds, LL_push_back_seconds);

	//додати в початок 10000 елементів

	start = clock();
	for (int i = 0; i < 10000; i++) 
		DA.push_front(c);
	end = clock();
	double DA_push_front_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час додання 10000 елементів в початок динамічного масиву - " << DA_push_front_seconds << endl;

	start = clock();
	for (int i = 0; i < 10000; i++)
		LL.push_front(c);
	end = clock();
	double LL_push_front_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час додання 10000 елементів в початок однозв'язного списку - " << LL_push_front_seconds << endl;

	percentage(DA_push_front_seconds, LL_push_front_seconds);
	
	//зчитати 20000 елементів під випадковими індексами

	start = clock();
	for (int i = 0; i < 20000; i++) 
		DA.get(rand() % 60000);
	end = clock();
	double DA_get_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час зчитування 20000 елементів під випадковими індексами в динамічному масиві - " << DA_get_seconds << endl;

	start = clock();
	for (int i = 0; i < 20000; i++)
		LL.get(rand() % 60000);
	end = clock();
	double LL_get_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час зчитування 20000 елементів під випадковими індексами в однозв'язному списку - " << LL_get_seconds << endl;

	percentage(DA_get_seconds, LL_get_seconds);

	//видалити 5000 елементів з початку

	start = clock();
	for (int i = 0; i < 5000; i++) {
		try {
			DA.pop_front();
		}
		catch(string ex){
			cout << ex << endl;
		}
	}
	end = clock();
	double DA_pop_front_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час видалення 5000 елементів з початку динамічного масиву - " << DA_pop_front_seconds << endl;

	start = clock();
	for (int i = 0; i < 5000; i++) {
		try {
			LL.pop_front();
		}
		catch (string ex) {
			cout << ex << endl;
		}
	}
	end = clock();
	double LL_pop_front_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час видалення 5000 елементів з початку однозв'язного списку - " << LL_pop_front_seconds << endl;

	percentage(DA_pop_front_seconds, LL_pop_front_seconds);

	//видалити 5000 елементів з кінця
	
	start = clock();
	for (int i = 0; i < 5000; i++) {
		try {
			DA.pop_back();
		}
		catch (string ex) {
			cout << ex << endl;
		}
	}
	end = clock();
	double DA_pop_back_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час видалення 5000 елементів з кінця динамічного масиву - " << DA_pop_back_seconds << endl;
	
	start = clock();
	for (int i = 0; i < 5000; i++) {
		try {
			LL.pop_back();
		}
		catch (string ex) {
			cout << ex << endl;
		}
	}
	end = clock();
	double LL_pop_back_seconds = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "Час видалення 5000 елементів з кінця однозв'язного списку - " << LL_pop_back_seconds << endl;

	percentage(DA_pop_back_seconds, LL_pop_back_seconds);

	double DA_sum_seconds = DA_push_back_seconds + DA_push_front_seconds + DA_get_seconds + DA_pop_front_seconds + DA_pop_back_seconds;
	double LL_sum_seconds = LL_push_back_seconds + LL_push_front_seconds + LL_get_seconds + LL_pop_front_seconds + LL_pop_back_seconds;

	percentage(DA_sum_seconds, LL_sum_seconds, 1);
}