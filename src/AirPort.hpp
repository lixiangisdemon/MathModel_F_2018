#pragma once
#include "DataStructure.h"
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <random>
#include <functional>
#include <cassert>
#include <ctime>
using namespace std;

static int  string2int(const string &str) {
	int res = 0;
	char c = '0';
	for (int i = 0; i < str.size(); i++)
		res = res * 10 + str[i] - c;
	return res;
}
/*****************************************************************************************/
/*************************���������ķ�����װ��һ����AirPort��********************************/
/******************************************************************************************/
class AirPort{
public:
	
	/* first num means i, second it the column k that going to be changed, and the third is the new k */
	typedef pair<int, pair<int, int> > changedTerm;
	vector<pair<int, int> > tabulist;
	typedef float (AirPort::*Objective) ();
	typedef float (AirPort::*CObjective) (changedTerm &);
	typedef void  (AirPort::*UpdateFunc)(changedTerm &);

public:

	AirPort();
	~AirPort();
	/* ��ȡpucks��Ϣ */
	void readPucks();
	/* ��ȡtickets��Ϣ */
	void readTickets();
	/* ��ȡgates ��Ϣ*/
	void readGates();
	/* �������ɵ����� */
	bool checkResolut(string file1, string file2);
	bool checkResolut(string file);
	/* �����һ��ĺ��� */
	void solution1();
	/* ����ڶ���ĺ��� */
	void solution2();
	/* ���������ĺ��� */
	void solution3();

	void loadData() { readPucks(); readGates(); readTickets(); }
private:

	/* ͳ��������������ݽṹ */
	typedef struct Stat {
		float n_i;
		float e_i;
		float h_i;
		float h_i_p;
		float g_i;
		float g_i_p;
		float l_i;
		float l_i_p;
		float q_i;
		float q_i_p;
	} Stat;

	/* ͳ������2��3Ҫ�����ݽṹ */
	typedef struct stat_2 {
		float O;
		float B;
	} Stat2;

	/* ͳ��������Ҫ�����ݽṹ */
	typedef struct stat_3 {
		float O;
		float B;
		vector<float> v_t;
		vector<float> v_t_p;
	} Stat3;

	/* ģ���ж����Ŀ�꺯�������� */
	float primary_objective() const;
	float secondary_objective();
	float solution2_objective();
	float solution3_objective();

	float primary_objective(changedTerm &changedK) const;
	float secondary_objective(changedTerm &changedK);
	float solution2_objective(changedTerm &changedK);
	float solution3_objective(changedTerm &changedK);
	void updateVars_1(changedTerm &changedK) { ; }
	void updateVars_2(changedTerm &changedK);
	void updateVars_3(changedTerm &changedK);

	void clearParamVars1();
	void clearParamVars2();
	void clearParamVars3();

	// a_j + (1-Z_ijk) * M >= d_i; for all i,j, all k.
	bool checkY_i() const;
	bool constrain_4() const; 
	bool constrain_4(const set<int>& changedK) const;
	bool constrain_4(changedTerm &changedK) const;
	
	void calculateZij();
	void calculateZij(const set<int>& changedK);
	void calculateZij(changedTerm& changedK);
	/* ��ģ���˻��㷨����randomMove�����½� */
	void randomMove();
	void randomMove(set<int>& changedK);
	void randomMove(changedTerm& changedK);
	/* ͳ�����ɵĽ�� */
	void statistic(Stat &stat);
	void statistic(Stat2 &stat);
	void statistic(Stat3 &stat);

	void greedyAlg();

	float diffCost();
	float diffCost(changedTerm & changedK);
	void printY_i(string file);
	int findf_i(const Tickets &t);
	/* ��Ҫ���㷨ʵ�� */
	void masterAlgorithm(int n, int K, UpdateFunc update_func = NULL);
	/* ������н�� */
	void outputResolut(string dir = "", int solution = 1);

private:

	vector<Pucks> pucks;
	vector<Tickets> tickets;
	vector<Gates> gates;
	map<string, FLIGHT_SHAPE> map_flight_shape;
	/* ���弯��  */
	vector<int> N;						// ���������漰�ĺ��༯��
	vector<int> P;						// �漰���ÿͼ���
	map<int, float> procedureTime_p;	// ÿ�����ÿ͵�����ʱ��
	map<int, float> tension_p;			// ÿ���ÿ͵Ľ��Ŷ�

	int K; // ��С 0 to 68;
	map<int, vector<int> > K_i;			// һ�����ϴ洢�Ų��ܽ��ܺ��� i�ĵǻ��ں�
	map<int, vector<int> > NK_i;		// K_i�Ĳ���

	map<int, int> a_p;					// ӳ���ÿͺõ������
	map<int, int> d_p;
	map<int, set<int> > i_ap;			// map flight_id to passengers
	map<int, set<int> > i_dp;
	int m, n;
	/* ������� */
	vector<int> a_i;					// ���ൽ��ʱ���
	vector<int> d_i;					// �����뿪ʱ���
	int beta;							// ��һ�������뿪���¸����ൽ��֮��Ļ���ʱ��
	int M;								// һ���������
	int sum_people;
	/* ������� y_i �� z_ij �Ǹ�����ͨ�õı����� ʣ�µ�������2��3���õı��� */
	vector<int>    y_i;
	vector<int>    z_ij;
	vector<map<int, float> > a_sigmas;
	vector<map<int, float> > d_sigmas;
	vector<map<int, float> > gammas;
	/* ���ɽ����Ҫ�ŵ��ĵ�ַǰ׺ */
	string prefix;

	vector<Objective> secondary_objs;
	vector<CObjective> c_secondary_objs;
	vector<float> f_current;
	vector<float> f_next;
	/* D_T, D_S, I_T, I_S <-> 0, 1, 2, 3*/
	int tram_time_table[4][4];
	int procedure_time_table[4][4];
	/* {0, ..., 6} <-> {T-N, T-C, T-S, S-N, S-C, S-S, S-E} */
	int walk_time_table[7][7];

};

/**********************************************************************************************/
/***********************����ʱ������ÿ��������ʵ��*************************************************/
/**********************************************************************************************/

AirPort::AirPort() 
	: beta(9), M(5000), sum_people(0), a_sigmas(4), d_sigmas(4), gammas(7), prefix(".")
{
	/* init map_flight_shape */
	{
		map_flight_shape["332"] = WIDE;
		map_flight_shape["333"] = WIDE;
		map_flight_shape["33E"] = WIDE;
		map_flight_shape["33H"] = WIDE;
		map_flight_shape["33L"] = WIDE;
		map_flight_shape["773"] = WIDE;
		map_flight_shape["319"] = NARROW;
		map_flight_shape["320"] = NARROW;
		map_flight_shape["321"] = NARROW;
		map_flight_shape["323"] = NARROW;
		map_flight_shape["325"] = NARROW;
		map_flight_shape["738"] = NARROW;
		map_flight_shape["73A"] = NARROW;
		map_flight_shape["73E"] = NARROW;
		map_flight_shape["73H"] = NARROW;
		map_flight_shape["73L"] = NARROW;
		/* D_T, D_S, I_T, I_S <-> 0, 1, 2, 3*/
		int tmp1[4][4] = { {0,1,0,1},{1,0,1,0},{0,1,0,1},{1,2,1,0} };
		memcpy(tram_time_table, tmp1, 4 * 4 * sizeof(int));
		int tmp2[4][4] = { {3,4,7,8}, {4,3,8,7}, {7,8,4,6}, {8,9,6,4} };
		memcpy(procedure_time_table, tmp2, 4 * 4 * sizeof(int));
		/* {0, ..., 6} <-> {T-N, T-C, T-S, S-N, S-C, S-S, S-E} */
		int tmp3[7][7] = { {2, 3, 4, 5, 4, 5, 5},
							{3, 2, 3, 4, 3, 4, 4},
							{4, 3, 2, 5, 4, 5, 5},
							{5, 4, 5, 2, 3, 4, 4},
							{4, 3, 4, 3, 2, 3, 3},
							{5, 4, 5, 4, 3, 2, 4},
							{5, 4, 5, 4, 3, 4, 2} };
		memcpy(walk_time_table, tmp3, 7 * 7 * sizeof(int));
	}
}

AirPort::~AirPort()
{
	
}

void AirPort::readPucks()
{
	string file = prefix + "/" + "data1.txt";
	fstream f;
	f.open(file, ifstream::in);
	assert(f.is_open());
	while (!f.eof()) {
		Pucks p;
		string line;
		getline(f, line);
		vector<string> words;
		splitBySpace(words, line);
		p.plane_num = words[0];

		// arrival_date-departure_date
		p.arrival_date = string2int(words[1].substr(0, 2));
		p.departure_date = string2int(words[6].substr(0, 2));

		// arrival/departure-time
		vector<string> time; 
		splitByColon(time, words[2]);
		int hour, mins;
		hour = string2int(time[0]);
		mins = string2int(time[1]);
		p.arrival_time = hour * 12 + mins / 5;
		splitByColon(time, words[7]);
		hour = string2int(time[0]);
		mins = string2int(time[1]);
		p.departure_time = hour * 12 + mins / 5;

		p.arrival_flight = words[3];
		p.departure_flight = words[8];

		p.arrival_type = ( words[4] == "D" ? DEMOSTIC : (words[4] == "I" ? INTER : D_OR_I) );
		p.departure_type = ( words[9] == "D" ? DEMOSTIC : (words[9] == "I" ? INTER : D_OR_I) );
		
		p.flight_shape = map_flight_shape[words[5]];
		pucks.push_back(p);
	}
	auto cmp = [](const Pucks &a, const Pucks &b) -> bool {
		int exact_1 = (a.arrival_date - 18) * 228 + a.arrival_time;
		int exact_2 = (b.arrival_date - 18) * 228 + b.arrival_time;
		return exact_1 < exact_2;
	};
	sort(pucks.begin(), pucks.end(), cmp);
	for (int i = 0; i < pucks.size(); i++) {
		Pucks &p = pucks[i];
		p.flight_id = i; // flightId
		int exact_arrival_time = (p.arrival_date - 18) * 288 + p.arrival_time;
		int exact_departure_time = (p.departure_date - 18) * 288 + p.departure_time;
		a_i.push_back(exact_arrival_time);
		d_i.push_back(exact_departure_time);
	}
	
	for (int i = 0; i < pucks.size(); i++)
		assert(pucks[i].flight_id == i);
}

void AirPort::readTickets()
{
	string file = prefix + "/" + "data2.txt";
	fstream f;
	f.open(file, ifstream::in);
	assert(f.is_open());
	int i = 0;
	while (!f.eof()) {
		Tickets t;
		string line;
		getline(f, line);
		vector<string> words;
		splitBySpace(words, line);
		t.parssengerId = i++;
		t.num_parssengers = string2int(words[1]);
		t.arrival_flight = words[2];
		t.departure_flight = words[4];
		t.arrival_date = string2int(words[3].substr(0, 2));
		t.departure_date = string2int(words[5].substr(0, 2));
		tickets.push_back(t);
		sum_people += t.num_parssengers;
	}
}

void AirPort::readGates() 
{
	string file = prefix + "/" + "data3.txt";
	fstream f;
	f.open(file, ifstream::in);
	assert(f.is_open());
	int i = 0;
	while (!f.eof()) {
		Gates g;
		string line;
		getline(f, line);
		vector<string> words;
		splitBySpace(words, line);
		string num = words[0].substr(1, words[0].size() - 2);
		g.name = words[0];
		/*g.gates_id = string2int(num);
		g.gates_id += (words[0][0] == 'T' ? 21 : 0);*/
		g.gates_id = i++;
		g.gates_type = (words[1] == "T" ? T : S);
		g.area = (words[2] == "North" ? NORTH : 
					(words[2] == "Center" ? CENTER : 
						(words[2] == "South" ? SOUTH : EAST)));
		g.arrival_resive_type = (words[3] == "D" ? DEMOSTIC :
			(words[3] == "I" ? INTER : D_OR_I));
		g.departure_release_type = (words[4] == "D" ? DEMOSTIC :
			(words[4] == "I" ? INTER : D_OR_I));
		g.flight_resive_shape = (words[5] == "W" ? WIDE : NARROW);
		gates.push_back(g);
	}
	K = gates.size();
}

/* there requires two files, 
** one file is flight_names and the other is gates that the flight assigned to 
*/
bool AirPort::checkResolut(string file1, string file2)
{
	vector<pair<int, int> > flight;
	ifstream f1, f2;
	f1.open(file1, ifstream::in);
	f2.open(file2, ifstream::in);
	while (!f1.eof() && !f2.eof()) {
		string flight_name;
		string gate_name;
		getline(f1, flight_name);
		getline(f2, gate_name);
		vector<Gates>::iterator g = find(gates.begin(), gates.end(), gate_name);
		vector<Pucks>::iterator p = find(pucks.begin(), pucks.end(), flight_name);
		if (p == pucks.end())
			return false;
		if (g == gates.end())
			flight.push_back(pair<int, int>(p->flight_id, K));
		else
			flight.push_back(pair<int, int>(p->flight_id, g->gates_id));
	}
	assert (f1.eof() && f2.eof());
	f1.close();
	f2.close();
	/* is flight[i] fitting to gate[i] */
	for (int i = 0; i < flight.size(); i++) {
		int f_id = flight[i].first;
		int g_id = flight[i].second;
		if (g_id == K)
			continue;
		bool condition1 = (pucks[f_id].arrival_type == gates[g_id].arrival_resive_type || 
			gates[g_id].arrival_resive_type == D_OR_I);
		bool condition2 = (pucks[f_id].departure_type == gates[g_id].departure_release_type ||
			gates[g_id].departure_release_type == D_OR_I);
		bool condition3 = (pucks[f_id].flight_shape == gates[g_id].flight_resive_shape);
		if (!condition1 || !condition2 || !condition3)
			return false;
	}
	assert(K == gates.size());
	sort(flight.begin(), flight.end());
	m = K + 1;
	/* is the schedule right */
	bool res = true;
	for (int i = 0; i < flight.size(); i++) {
		if (flight[i].second == K)
			continue;
		for (int j = i + 1; j < flight.size(); j++) {
			if (flight[j].second == K)
				continue;
			if (flight[i].second == flight[j].second) {
				res = (res && a_i[flight[j].first] >= d_i[flight[i].first] + beta);
				if (!res)
					return false;
				i = j - 1;
				break;
			}
		}
	}
	return true;
}

/* the file requires two column,
** one column is flight_names and the other is gates that the flight assigned to
*/
bool AirPort::checkResolut(string file)
{
	vector<pair<int, int> > flight;
	ifstream f;
	f.open(file, ifstream::in);
	while (!f.eof()) {
		string line;
		getline(f, line);
		vector<string> words;
		splitBySpace(words, line);
		if (words.size() < 2)
			continue;
		vector<Pucks>::iterator p = find(pucks.begin(), pucks.end(), words[0]);
		vector<Gates>::iterator g = find(gates.begin(), gates.end(), words[1]);
		if (p == pucks.end())
			return false;
		if (g == gates.end())
			flight.push_back(pair<int, int>(p->flight_id, K));
		else
			flight.push_back(pair<int, int>(p->flight_id, g->gates_id));
	}
	f.close();
	/* is flight[i] fitting to gate[i] */
	for (int i = 0; i < flight.size(); i++) {
		int f_id = flight[i].first;
		int g_id = flight[i].second;
		if (g_id == K)
			continue;
		bool condition1 = (pucks[f_id].arrival_type == gates[g_id].arrival_resive_type ||
			gates[g_id].arrival_resive_type == D_OR_I);
		bool condition2 = (pucks[f_id].departure_type == gates[g_id].departure_release_type ||
			gates[g_id].departure_release_type == D_OR_I);
		bool condition3 = (pucks[f_id].flight_shape == gates[g_id].flight_resive_shape);
		if (!condition1 || !condition2 || !condition3)
			return false;
	}
	assert(K == gates.size());
	sort(flight.begin(), flight.end());
	m = K + 1;
	/* is the schedule right */
	bool res = true;
	for (int i = 0; i < flight.size(); i++) {
		if (flight[i].second == K)
			continue;
		for (int j = i + 1; j < flight.size(); j++) {
			if (flight[j].second == K)
				continue;
			if (flight[i].second == flight[j].second) {
				res = (res && a_i[flight[j].first] >= d_i[flight[i].first] + beta);
				if (!res)
					return false;
				i = j - 1;
				break;
			}
		}
	}
	return true;
}

void AirPort::solution1() {
	/* load data */
	readPucks();
	readGates();
	srand((int)time(NULL));
	/* construct Sets */
	int totalFlights = pucks.size();
	for (int i = 0; i < totalFlights; i++) {
		if (pucks[i].departure_date >= 20 && pucks[i].arrival_date <= 20) {
			N.push_back(i);
		}
	}
	m = K + 1;
	n = N.size();
	for (vector<int>::const_iterator it = N.begin(); it != N.end(); it++) {
		vector<int> k_i;
		vector<int> nk_i;
		for (int j = 0; j < K; j++) {
			bool condition_1 = ( gates[j].arrival_resive_type == D_OR_I ||
				(pucks[*it].arrival_type == gates[j].arrival_resive_type) );

			bool condition_2 = ( gates[j].departure_release_type == D_OR_I ||
				(pucks[*it].departure_type == gates[j].departure_release_type) );

			bool condition_3 = ( pucks[*it].flight_shape == gates[j].flight_resive_shape );

			if (condition_1 && condition_2 && condition_3)
				nk_i.push_back(j);
			else
				k_i.push_back(j);
		}
		nk_i.push_back(m-1);

		K_i[*it] = k_i;
		NK_i[*it] = nk_i;
	}

	y_i.resize(n);
	z_ij.resize(n*n);
	fill(y_i.begin(), y_i.end(), 0);
	fill(z_ij.begin(), z_ij.end(), -1);
	
	secondary_objs.push_back(&AirPort::secondary_objective);
	c_secondary_objs.push_back(&AirPort::secondary_objective);
	masterAlgorithm(n, K, NULL);
	outputResolut("����1��", 1);
	bool pass = checkY_i();
	clearParamVars1();
	if (pass)
		cout << "pass" << endl;
	else
		cout << "illed algorithm" << endl;
}

int AirPort::findf_i(const Tickets &t) {
	int totalFlights = pucks.size();
	int f_1 = -1;
	int f_2 = -1;
	if (t.departure_date >= 20 && t.arrival_date <= 20) {
		for (int i = 0; i < totalFlights; i++) {
			if (t.arrival_date == pucks[i].arrival_date && t.arrival_flight == pucks[i].arrival_flight) {
				f_1 = i;
			}
			if (t.departure_date == pucks[i].departure_date && t.departure_flight == pucks[i].departure_flight) {
				f_2 = i;
			}
		}

		if (f_1 > 0 && f_2 > 0) {
			a_p[t.parssengerId] = f_1;
			d_p[t.parssengerId] = f_2;
			return 1;
		}
	}
	return 0;
}

void AirPort::solution2()
{
	/* load data */
	readPucks();
	readTickets();
	readGates();
	//srand((int)time(NULL));
	/* construct Sets */
	int totalFlights = pucks.size();
	int totalPassengers = tickets.size();
	set<int> setN;
	for (int i = 0; i < totalPassengers; i++) {
		int f_i = findf_i(tickets[i]);
		if (f_i > 0) {
			P.push_back(i);
			setN.insert(a_p[i]);
			setN.insert(d_p[i]);
		}
	}
	for (int i = 0; i < totalFlights; i++) {
		if (pucks[i].departure_date >= 20 && pucks[i].arrival_date <= 20) {
			setN.insert(i);
		}
	}
	for (set<int>::const_iterator it = setN.begin(); it != setN.end(); it++) {
		N.push_back(*it);
	}
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int ap_id = a_p[*p];
		int dp_id = d_p[*p];
		i_ap[ap_id].insert(*p);
		i_dp[dp_id].insert(*p);
	}
	
	m = K + 1;
	n = N.size();

	for (vector<int>::const_iterator it = N.begin(); it != N.end(); it++) {
		vector<int> k_i;
		vector<int> nk_i;
		for (int j = 0; j < K; j++) {
			bool condition_1 = (gates[j].arrival_resive_type == D_OR_I ||
				(pucks[*it].arrival_type == gates[j].arrival_resive_type));

			bool condition_2 = (gates[j].departure_release_type == D_OR_I ||
				(pucks[*it].departure_type == gates[j].departure_release_type));

			bool condition_3 = (pucks[*it].flight_shape == gates[j].flight_resive_shape);

			if (condition_1 && condition_2 && condition_3)
				nk_i.push_back(j);
			else
				k_i.push_back(j);
		}
		nk_i.push_back(m - 1);

		K_i[*it] = k_i;
		NK_i[*it] = nk_i;
	}

	y_i.resize(n);
	z_ij.resize(n*n);
	fill(y_i.begin(), y_i.end(), 0);
	fill(z_ij.begin(), z_ij.end(), -1);

	secondary_objs.push_back(&AirPort::solution2_objective);
	secondary_objs.push_back(&AirPort::secondary_objective);
	c_secondary_objs.push_back(&AirPort::solution2_objective);
	c_secondary_objs.push_back(&AirPort::secondary_objective);
	masterAlgorithm(n, K, &AirPort::updateVars_2);
	outputResolut("����2��", 2);
	bool pass = checkY_i();
	clearParamVars2();
	if (pass)
		cout << "pass" << endl;
	else
		cout << "illed algorithm" << endl;
}

void AirPort::solution3()
{
	/* load data */
	readPucks();
	readTickets();
	readGates();
	srand((int)time(NULL));
	/* construct Sets */
	int totalFlights = pucks.size();
	int totalPassengers = tickets.size();
	set<int> setN;
	P.clear();
	N.clear();
	for (int i = 0; i < totalPassengers; i++) {
		int f_i = findf_i(tickets[i]);
		if (f_i > 0) {
			P.push_back(i);
			setN.insert(a_p[i]);
			setN.insert(d_p[i]);
		}
	}
	for (int i = 0; i < totalFlights; i++) {
		if (pucks[i].departure_date >= 20 && pucks[i].arrival_date <= 20) {
			setN.insert(i);
		}
	}
	for (set<int>::const_iterator it = setN.begin(); it != setN.end(); it++) {
		N.push_back(*it);
	}
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int ap_id = a_p[*p];
		int dp_id = d_p[*p];
		i_ap[ap_id].insert(*p);
		i_dp[dp_id].insert(*p);
	}
	m = K + 1;
	n = N.size();

	for (vector<int>::const_iterator it = N.begin(); it != N.end(); it++) {
		vector<int> k_i;
		vector<int> nk_i;
		for (int j = 0; j < K; j++) {
			bool condition_1 = (gates[j].arrival_resive_type == D_OR_I ||
				(pucks[*it].arrival_type == gates[j].arrival_resive_type));

			bool condition_2 = (gates[j].departure_release_type == D_OR_I ||
				(pucks[*it].departure_type == gates[j].departure_release_type));

			bool condition_3 = (pucks[*it].flight_shape == gates[j].flight_resive_shape);

			if (condition_1 && condition_2 && condition_3)
				nk_i.push_back(j);
			else
				k_i.push_back(j);
		}
		nk_i.push_back(m - 1);

		K_i[*it] = k_i;
		NK_i[*it] = nk_i;
	}

	y_i.resize(n);
	z_ij.resize(n*n);
	fill(y_i.begin(), y_i.end(), 0);
	fill(z_ij.begin(), z_ij.end(), -1);

	secondary_objs.push_back(&AirPort::solution3_objective);
	secondary_objs.push_back(&AirPort::secondary_objective);
	c_secondary_objs.push_back(&AirPort::solution3_objective);
	c_secondary_objs.push_back(&AirPort::secondary_objective);
	masterAlgorithm(n, K, &AirPort::updateVars_3);
	outputResolut("����3��", 3);
	bool pass = checkY_i();
	clearParamVars3();
	if (pass)
		cout << "pass" << endl;
	else
		cout << "illed algorithm" << endl;
}

void AirPort::updateVars_2(changedTerm &changedK)
{
	int c_i = changedK.first;
	int o_k = changedK.second.first;
	int n_k = changedK.second.second;

	if (o_k == n_k) { // stay put
		return ;
	}

	int n_i = N[c_i]; {
		a_sigmas[0][n_i] = (n_k < 28) * (pucks[n_i].arrival_type == DEMOSTIC);
		a_sigmas[1][n_i] = (n_k >= 28 && n_k < K) * (pucks[n_i].arrival_type == DEMOSTIC);
		a_sigmas[2][n_i] = (n_k < 28) * (pucks[n_i].arrival_type == INTER);
		a_sigmas[3][n_i] = (n_k >= 28 && n_k < K) * (pucks[n_i].arrival_type == INTER);

		d_sigmas[0][n_i] = (n_k < 28) * (pucks[n_i].departure_type == DEMOSTIC);
		d_sigmas[1][n_i] = (n_k >= 28 && n_k < K) * (pucks[n_i].departure_type == DEMOSTIC);
		d_sigmas[2][n_i] = (n_k < 28) * (pucks[n_i].departure_type == INTER);
		d_sigmas[3][n_i] = (n_k >= 28 && n_k < K) * (pucks[n_i].departure_type == INTER);
	}
}

void AirPort::updateVars_3(changedTerm &changedK)
{
	int c_i = changedK.first;
	int o_k = changedK.second.first;
	int n_k = changedK.second.second;

	if (o_k == n_k) { // stay put
		return ;
	}

	int n_i = N[c_i];
	{
		a_sigmas[0][n_i] = (n_k < 28) * (pucks[n_i].arrival_type == DEMOSTIC);
		a_sigmas[1][n_i] = (n_k >= 28 && n_k < K) * (pucks[n_i].arrival_type == DEMOSTIC);
		a_sigmas[2][n_i] = (n_k < 28) * (pucks[n_i].arrival_type == INTER);
		a_sigmas[3][n_i] = (n_k >= 28 && n_k < K) * (pucks[n_i].arrival_type == INTER);

		d_sigmas[0][n_i] = (n_k < 28) * (pucks[n_i].departure_type == DEMOSTIC);
		d_sigmas[1][n_i] = (n_k >= 28 && n_k < K) * (pucks[n_i].departure_type == DEMOSTIC);
		d_sigmas[2][n_i] = (n_k < 28) * (pucks[n_i].departure_type == INTER);
		d_sigmas[3][n_i] = (n_k >= 28 && n_k < K) * (pucks[n_i].departure_type == INTER);

		gammas[0][n_i] = (n_k >= 0 && n_k < 9);
		gammas[1][n_i] = (n_k >= 9 && n_k < 19);
		gammas[2][n_i] = (n_k >= 19 && n_k < 28);
		gammas[3][n_i] = (n_k >= 28 && n_k < 38);
		gammas[4][n_i] = (n_k >= 38 && n_k < 48);
		gammas[5][n_i] = (n_k >= 48 && n_k < 58);
		gammas[6][n_i] = (n_k >= 58 && n_k < 69);
	}
}

float AirPort::primary_objective() const
{
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (y_i[i] == K);
	}
	return (float)sum;
}

float AirPort::secondary_objective()
{
	int sum = 0;
	for (int k = 0; k < m-1; k++) {
		int sgn = 0;
		for (int i = 0; i < n; i++) {
			sgn += (y_i[i] == k);
		}
		sum += SGN(sgn);
	}
	return (float)sum;
}

float AirPort::solution2_objective() {
	
	a_sigmas.clear();
	d_sigmas.clear();
	a_sigmas.resize(4);
	d_sigmas.resize(4);
	for (int i = 0; i < n; i++) {
		int n_i = N[i];
		a_sigmas[0][n_i]  = (y_i[i] < 28) * (pucks[N[i]].arrival_type == DEMOSTIC);
		a_sigmas[1][n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].arrival_type == DEMOSTIC);
		a_sigmas[2][n_i] = (y_i[i] < 28) * (pucks[N[i]].arrival_type == INTER);
		a_sigmas[3][n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].arrival_type == INTER);
		
		d_sigmas[0][n_i] = (y_i[i] < 28) * (pucks[N[i]].departure_type == DEMOSTIC);
		d_sigmas[1][n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].departure_type == DEMOSTIC);
		d_sigmas[2][n_i] = (y_i[i] < 28) * (pucks[N[i]].departure_type == INTER);
		d_sigmas[3][n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].departure_type == INTER);
	}

	float sum = 0;
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];
		float tmp_tp = 0.0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp_tp += a_sigmas[i][I] * d_sigmas[j][J] * procedure_time_table[i][j];
			}
		}
		int S_p = (a_i[I] + tmp_tp <= d_i[J]);
		float tmp = (tmp_tp * S_p + 72 * (1 - S_p)) * tickets[*p].num_parssengers;
		sum += tmp;
	}

	return sum;
}

float AirPort::solution3_objective() {

	a_sigmas.clear();
	d_sigmas.clear();
	gammas.clear();
	a_sigmas.resize(4);
	d_sigmas.resize(4);
	gammas.resize(7);
	for (int i = 0; i < n; i++) {
		int n_i = N[i];
		a_sigmas[0][n_i] = (y_i[i] < 28) * (pucks[N[i]].arrival_type == DEMOSTIC);
		a_sigmas[1][n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].arrival_type == DEMOSTIC);
		a_sigmas[2][n_i] = (y_i[i] < 28) * (pucks[N[i]].arrival_type == INTER);
		a_sigmas[3][n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].arrival_type == INTER);

		d_sigmas[0][n_i] = (y_i[i] < 28) * (pucks[N[i]].departure_type == DEMOSTIC);
		d_sigmas[1][n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].departure_type == DEMOSTIC);
		d_sigmas[2][n_i] = (y_i[i] < 28) * (pucks[N[i]].departure_type == INTER);
		d_sigmas[3][n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].departure_type == INTER);

		gammas[0][n_i] = (y_i[i] >= 0 && y_i[i] < 9);
		gammas[1][n_i] = (y_i[i] >= 9 && y_i[i] < 19);
		gammas[2][n_i] = (y_i[i] >= 19 && y_i[i] < 28);
		gammas[3][n_i] = (y_i[i] >= 28 && y_i[i] < 38);
		gammas[4][n_i] = (y_i[i] >= 38 && y_i[i] < 48);
		gammas[5][n_i] = (y_i[i] >= 48 && y_i[i] < 58);
		gammas[6][n_i] = (y_i[i] >= 58 && y_i[i] < 69);
	}

	float sum = 0.;
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];

		float tmp_tp = 0.0;
		float tmp_tpp = 0.0;
		float tmp_wp = 0.0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp_tp += a_sigmas[i][I] * d_sigmas[j][J] * procedure_time_table[i][j];
				tmp_tpp += a_sigmas[i][I] * d_sigmas[j][J] * tram_time_table[i][j] * 1.6;
			}
		}
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				tmp_wp += gammas[i][I] * gammas[j][J] * walk_time_table[i][j];
			}
		}
		float r_p = (tmp_tp + tmp_tpp + tmp_wp);
		int S_pp = (a_i[I] + r_p <= d_i[J]);
		float tmp = (float)(r_p * S_pp + 72 * (1 - S_pp)) / (d_i[J] - a_i[I]) * tickets[*p].num_parssengers;
		sum += tmp;
	}
	
	return sum;
}

float AirPort::primary_objective(changedTerm & changedK) const
{
	int oldk = changedK.second.first;
	int newk = changedK.second.second;

	/* if k -> k don't change */
	if (oldk == newk)
		return f_current[0];
	/* if k -> K return +1*/
	if (newk == K)
		return f_current[0] + 1;
	/* if K -> k return -1 */
	if (oldk == K)
		return f_current[0] - 1;
	/* esle don't change */
	return f_current[0];
}

float AirPort::secondary_objective(changedTerm & changedK) 
{
	int oldk = changedK.second.first;
	int newk = changedK.second.second;
	int size = f_current.size();

	if (oldk == newk) // stay put
		return f_current[size - 1];

	int sgn_k1 = 0, sgn_k2 = 0;
	int o_sgn_k1, o_sgn_k2;
	for (int i = 0; i < n; i++) {
		sgn_k1 += (oldk == K ? 0 : (y_i[i] == oldk));
		sgn_k2 += (newk == K ? 0 : (y_i[i] == newk));
	}
	o_sgn_k1 = (oldk == K ? 0 : sgn_k1 + 1);
	o_sgn_k2 = (newk == K ? 0 : sgn_k2 - 1);

	int diff = SGN(sgn_k1) + SGN(sgn_k2) - SGN(o_sgn_k1) - SGN(o_sgn_k2);
	
	return f_current[size - 1] + diff;
}

float AirPort::solution2_objective(changedTerm & changedK) 
{
	int c_i = changedK.first;
	int o_k = changedK.second.first;
	int n_k = changedK.second.second;
	
	if (o_k == n_k) { // stay put
		return f_current[1];
	}

	vector<float> changed_a_sigma(4), changed_d_sigma(4);
	int n_i = N[c_i]; {
		changed_a_sigma[0] = (n_k < 28) * (pucks[n_i].arrival_type == DEMOSTIC);
		changed_a_sigma[1] = (n_k >= 28 && n_k < K) * (pucks[n_i].arrival_type == DEMOSTIC);
		changed_a_sigma[2] = (n_k < 28) * (pucks[n_i].arrival_type == INTER);
		changed_a_sigma[3] = (n_k >= 28 && n_k < K) * (pucks[n_i].arrival_type == INTER);

		changed_d_sigma[0] = (n_k < 28) * (pucks[n_i].departure_type == DEMOSTIC);
		changed_d_sigma[1] = (n_k >= 28 && n_k < K) * (pucks[n_i].departure_type == DEMOSTIC);
		changed_d_sigma[2] = (n_k < 28) * (pucks[n_i].departure_type == INTER);
		changed_d_sigma[3] = (n_k >= 28 && n_k < K) * (pucks[n_i].departure_type == INTER);
	}
	set<int> changedP;
	for (set<int>::const_iterator p = i_ap[n_i].begin(); p != i_ap[n_i].end(); p++) {
		changedP.insert(*p);
	}
	for (set<int>::const_iterator p = i_dp[n_i].begin(); p != i_dp[n_i].end(); p++) {
		changedP.insert(*p);
	}
	float diff = 0;
	for (set<int>::const_iterator p = changedP.begin(); p != changedP.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];
		float tmp_tp = 0.0, pre_tp = 0.0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float A, D;
				if (I == n_i)
					A = changed_a_sigma[i];
				else
					A = a_sigmas[i][I];
				if (J == n_i)
					D = changed_d_sigma[j];
				else
					D = d_sigmas[j][J];
				tmp_tp += A * D * procedure_time_table[i][j];
				pre_tp += a_sigmas[i][I] * d_sigmas[j][J] * procedure_time_table[i][j];
			}
		}
		int S_p = (a_i[I] + tmp_tp <= d_i[J]);
		float tmp = (tmp_tp * S_p + 72 * (1 - S_p)) * tickets[*p].num_parssengers;
		int pre_Sp = (a_i[I] + pre_tp <= d_i[J]);
		float pre_tmp = (pre_tp * pre_Sp + 72 * (1 - pre_Sp)) * tickets[*p].num_parssengers;
		diff +=  tmp - pre_tmp;
	}
	
	return f_current[1] + diff;
}

float AirPort::solution3_objective(changedTerm & changedK) 
{
	int c_i = changedK.first;
	int o_k = changedK.second.first;
	int n_k = changedK.second.second;

	if (o_k == n_k) { // stay put
		return f_current[1];
	}

	vector<float> changed_a_sigma(4), changed_d_sigma(4), changed_gamma(7);
	int n_i = N[c_i]; {
		changed_a_sigma[0] = (n_k < 28) * (pucks[n_i].arrival_type == DEMOSTIC);
		changed_a_sigma[1] = (n_k >= 28 && n_k < K) * (pucks[n_i].arrival_type == DEMOSTIC);
		changed_a_sigma[2] = (n_k < 28) * (pucks[n_i].arrival_type == INTER);
		changed_a_sigma[3] = (n_k >= 28 && n_k < K) * (pucks[n_i].arrival_type == INTER);

		changed_d_sigma[0] = (n_k < 28) * (pucks[n_i].departure_type == DEMOSTIC);
		changed_d_sigma[1] = (n_k >= 28 && n_k < K) * (pucks[n_i].departure_type == DEMOSTIC);
		changed_d_sigma[2] = (n_k < 28) * (pucks[n_i].departure_type == INTER);
		changed_d_sigma[3] = (n_k >= 28 && n_k < K) * (pucks[n_i].departure_type == INTER);

		changed_gamma[0] = (n_k >= 0 && n_k < 9);
		changed_gamma[1] = (n_k >= 9 && n_k < 19);
		changed_gamma[2] = (n_k >= 19 && n_k < 28);
		changed_gamma[3] = (n_k >= 28 && n_k < 38);
		changed_gamma[4] = (n_k >= 38 && n_k < 48);
		changed_gamma[5] = (n_k >= 48 && n_k < 58);
		changed_gamma[6] = (n_k >= 58 && n_k < 69);
	}
	set<int> changedP;
	for (set<int>::const_iterator p = i_ap[n_i].begin(); p != i_ap[n_i].end(); p++) {
		changedP.insert(*p);
	}
	for (set<int>::const_iterator p = i_dp[n_i].begin(); p != i_dp[n_i].end(); p++) {
		changedP.insert(*p);
	}
	float diff = 0.;
	for (set<int>::const_iterator p = changedP.begin(); p != changedP.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];
		float tmp_tp = 0.0, pre_tp = 0.0;
		float tmp_tpp = 0.0, pre_tpp = 0.0;
		float tmp_wp = 0.0, pre_wp = 0.0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float A, D;
				if (I == n_i)
					A = changed_a_sigma[i];
				else
					A = a_sigmas[i][I];
				if (J == n_i)
					D = changed_d_sigma[j];
				else
					D = d_sigmas[j][J];
				tmp_tp += A * D * procedure_time_table[i][j];
				tmp_tpp += A * D * tram_time_table[i][j] * 1.6;

				pre_tp += a_sigmas[i][I] * d_sigmas[j][J] * procedure_time_table[i][j];
				pre_tpp += a_sigmas[i][I] * d_sigmas[j][J] * tram_time_table[i][j] * 1.6;
			}
		}
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				float G1, G2;
				if (I == n_i)
					G1 = changed_gamma[i];
				else
					G1 = gammas[i][I];
				if (J == n_i)
					G2 = changed_gamma[j];
				else
					G2 = gammas[j][J];
				tmp_wp += G1 * G2 * walk_time_table[i][j];
				pre_wp += gammas[i][I] * gammas[j][J] * walk_time_table[i][j];
			}
		}
		float r_p = (tmp_tp + tmp_tpp + tmp_wp);
		int S_pp = (a_i[I] + r_p <= d_i[J]);
		float tmp = (float)(r_p * S_pp + 72 * (1 - S_pp)) / (d_i[J] - a_i[I]) * tickets[*p].num_parssengers;
		float pre_rp = (pre_tp + pre_tpp + pre_wp);
		int pre_Spp = (a_i[I] + pre_rp <= d_i[J]);
		float pre_tmp = (float)(pre_rp * pre_Spp + 72 * (1 - pre_Spp)) / (d_i[J] - a_i[I]) * tickets[*p].num_parssengers;
		diff += tmp - pre_tmp;
	}
	
	return f_current[1] + diff;
}

void AirPort::clearParamVars1()
{
	y_i.clear();
	z_ij.clear();
	secondary_objs.clear();
	c_secondary_objs.clear();
	f_current.clear();
	f_next.clear();
	N.clear();
	K_i.clear();
	NK_i.clear();
	pucks.clear();
	gates.clear();
}

void AirPort::clearParamVars2()
{
	y_i.clear();
	z_ij.clear();
	secondary_objs.clear();
	c_secondary_objs.clear();
	f_current.clear();
	f_next.clear();
	a_p.clear();
	d_p.clear();
	N.clear();
	P.clear();
	K_i.clear();
	NK_i.clear();
	a_sigmas.clear();
	d_sigmas.clear();
	pucks.clear();
	tickets.clear();
	gates.clear();
}

void AirPort::clearParamVars3()
{
	y_i.clear();
	z_ij.clear();
	secondary_objs.clear();
	c_secondary_objs.clear();
	f_current.clear();
	f_next.clear();
	a_p.clear();
	d_p.clear();
	N.clear();
	P.clear();
	K_i.clear();
	NK_i.clear();
	a_sigmas.clear();
	d_sigmas.clear();
	gammas.clear();
	pucks.clear();
	tickets.clear();
	gates.clear();
}
	
bool AirPort::constrain_4() const
{
	bool res = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < K; k++)
				res = (res && 
						(a_i[N[j]] + (z_ij[i*n + j] != k) * M >= d_i[N[i]] + beta));
			if (!res)
				return false;
		}
	}
	return res;
}

/* �����ƺ���constrain_4��һ������ */
bool AirPort::constrain_4(const set<int> &changedK) const
{
	bool res = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (set<int>::const_iterator it = changedK.begin(); it != changedK.end(); it++)
				res = ( res && (a_i[N[j]] + (z_ij[i*n + j] != *it) * M >= d_i[N[i]] + beta) );
			if (!res)
				return false;
		}
	}
	return res;
}

/* �����ƺ���constrain_4��һ������ */
bool AirPort::constrain_4(changedTerm & changedK) const
{
	int changedI = changedK.first;
	int oldk = changedK.second.first;
	int newk = changedK.second.second;

	int I = N[changedI];
	bool res = true;
	for (int j = 0; j < n; j++) {
		int J = N[j];
		if (oldk < K) {
			res = (res && (a_i[J] + (z_ij[changedI*n + j] != oldk) * M >= d_i[I] + beta));
			res = (res && (a_i[I] + (z_ij[j*n + changedI] != oldk) * M >= d_i[J] + beta));
		}
			
		if (newk < K) {
			res = (res && (a_i[J] + (z_ij[changedI*n + j] != newk) * M >= d_i[I] + beta));
			res = (res && (a_i[I] + (z_ij[j*n + changedI] != newk) * M >= d_i[J] + beta));
		}
			
		if (!res)
			return false;
	}
	return res;
}

void AirPort::masterAlgorithm(int n, int K, UpdateFunc updateVars)
{
	float tConst = 2.0;
	float factor_1 = 2;
	float factor_2 = 2.25;
	float coolRate = 0.9999;
	float reheatFactor = 1.0555;
	float terminateT = 1e-2;
	int maxUnimproved = 700;
	int maxUnaccepted = 500;
	int unimproved = 0;
	int unaccepted = 0;
	int verbose = 5000;
	double annealingTemp = tConst * n;

	/* Heuristics Algorithm */
	fill(y_i.begin(), y_i.end(), m - 1);
	//greedyAlg();
	calculateZij();

	/* best record */
	vector<float> bestF(1 + secondary_objs.size());
	vector<int> gateFlightMap(n);
	std::copy(y_i.begin(), y_i.end(), gateFlightMap.begin());
	
	vector<int> current(n);
	vector<int> current_zij(n*n);

	f_current.resize(1 + secondary_objs.size());
	f_next.resize(1 + secondary_objs.size());
	f_current[0] = primary_objective();
	for (int i = 0; i < secondary_objs.size(); i++)
		f_current[i+1] = (this->*secondary_objs[i])();

	long long iterations = 0;
	/* Simulated Annealing */
	do {
		copy(y_i.begin(), y_i.end(), current.begin());
		copy(z_ij.begin(), z_ij.end(), current_zij.begin());
		changedTerm changedK(0,pair<int, int>(0,0));
		randomMove(changedK);
		calculateZij(changedK);
		bool condition = constrain_4(changedK);
		if (condition) {

			float diff = diffCost(changedK);
			if (diff < 0) {
				copy(y_i.begin(), y_i.end(), gateFlightMap.begin());
				copy(f_next.begin(), f_next.end(), bestF.begin());

				copy(f_next.begin(), f_next.end(), f_current.begin());
				if (updateVars != NULL)
					(this->*updateVars)(changedK);
			}
			else {
				//float r = distribution(engine);
				double r = myrandom();
				double probs = factor_1 * exp(-diff / (factor_2 * annealingTemp));
				if (r < probs) {
					unimproved += 1;
					copy(f_next.begin(), f_next.end(), f_current.begin());
					if (updateVars != NULL)
						(this->*updateVars)(changedK);
				}
				else {
					unaccepted += 1;
					copy(current.begin(), current.end(), y_i.begin());
					copy(current_zij.begin(), current_zij.end(), z_ij.begin());
				}
			}
		}
		else {
			unaccepted += 1;
			//cout << "don't satisfy conditions " << endl;
			copy(current.begin(), current.end(), y_i.begin());
			copy(current_zij.begin(), current_zij.end(), z_ij.begin());
		}

		if (unimproved > maxUnimproved || unaccepted > maxUnaccepted) {
			annealingTemp *= reheatFactor;
			unimproved = 0;
			unaccepted = 0;
		}
		annealingTemp *= coolRate;
		if (iterations % verbose == 0){
			cout << endl;
			cout << "iterations: " << iterations << endl;
			cout << "tempature: " << annealingTemp << "\t";
			for (int i = 0; i < f_current.size(); i++)
				cout << "cost" << i + 1 << ": " << f_current[i] << "\t";
			cout << endl;
		}
		iterations++;
	} while (annealingTemp > terminateT);
	copy(gateFlightMap.begin(), gateFlightMap.end(), y_i.begin());
	copy(bestF.begin(), bestF.end(), f_current.begin());
}

void AirPort::outputResolut(string dir, int solution) {
	printY_i(dir + "��������.txt");
	ofstream f;
	f.open(prefix + "/" + dir + "����ͳ��.txt", ofstream::out);
	assert(f.is_open());
	string name[3] = { "һ��Ŀ��ֵ:", "����Ŀ��ֵ:", "����Ŀ��ֵ:"};
	for (int i = 0; i < f_current.size(); i++) {
		f << name[i] << endl;
		f << "\t\t" << f_current[i] << endl;
	}
	f << endl;
	Stat stat;
	Stat2 stat2;
	Stat3 stat3;
	switch (solution) {
	case 1:
		statistic(stat);

		f << "���䵽��������        :   " << stat.n_i << endl;
		f << "�ǻ���ʹ�ñ���        :   " << stat.e_i << endl;
		f << "���䵽�ǻ���խ������� :   " << stat.h_i << endl;
		f << "���䵽�ǻ��ڿ�������� :   " << stat.h_i_p << endl;
		f << "���䵽�ǻ���խ������� :   " << stat.g_i << endl;
		f << "���䵽�ǻ��ڿ�������� :   " << stat.g_i_p << endl;
		f << "T�ǻ���ʹ����Ŀ       :   " << stat.l_i << endl;
		f << "S�ǻ���ʹ����Ŀ       :   " << stat.l_i_p << endl;
		f << "T�ǻ���ʹ����         :   " << stat.q_i << endl;
		f << "S�ǻ���ʹ����         :   " << stat.q_i_p << endl;
		break;
	case 2:
		statistic(stat);
		f << "���䵽��������        :   " << stat.n_i << endl;
		f << "�ǻ���ʹ�ñ���        :   " << stat.e_i << endl;
		f << "���䵽�ǻ���խ������� :   " << stat.h_i << endl;
		f << "���䵽�ǻ��ڿ�������� :   " << stat.h_i_p << endl;
		f << "���䵽�ǻ���խ������� :   " << stat.g_i << endl;
		f << "���䵽�ǻ��ڿ�������� :   " << stat.g_i_p << endl;
		f << "T�ǻ���ʹ����Ŀ       :   " << stat.l_i << endl;
		f << "S�ǻ���ʹ����Ŀ       :   " << stat.l_i_p << endl;
		f << "T�ǻ���ʹ����         :   " << stat.q_i << endl;
		f << "S�ǻ���ʹ����         :   " << stat.q_i_p << endl;
		statistic(stat2);
		f << "����ʧ���ÿ���Ŀ       :   " << stat2.B << endl;
		f << "����ʧ���ÿͱ���       :   " << stat2.O << endl;
		break;

	case 3:
		statistic(stat);
		f << "���䵽��������        :   " << stat.n_i << endl;
		f << "�ǻ���ʹ�ñ���        :   " << stat.e_i << endl;
		f << "���䵽�ǻ���խ������� :   " << stat.h_i << endl;
		f << "���䵽�ǻ��ڿ�������� :   " << stat.h_i_p << endl;
		f << "���䵽�ǻ���խ������� :   " << stat.g_i << endl;
		f << "���䵽�ǻ��ڿ�������� :   " << stat.g_i_p << endl;
		f << "T�ǻ���ʹ����Ŀ       :   " << stat.l_i << endl;
		f << "S�ǻ���ʹ����Ŀ       :   " << stat.l_i_p << endl;
		f << "T�ǻ���ʹ����         :   " << stat.q_i << endl;
		f << "S�ǻ���ʹ����         :   " << stat.q_i_p << endl;
		statistic(stat3);
		f << "����ʧ���ÿ���Ŀ       :       " << stat3.B << endl;
		f << "����ʧ���ÿͱ���       :       " << stat3.O << endl;
		f << "�����ÿͻ���ʱ��ֲ�    :    " << stat3.v_t << endl;
		f << "�����ÿͻ��˽��Ŷȷֲ�  :  " << stat3.v_t_p << endl;
		break;

	default:
		break;
	};
	f.close();
}

void AirPort::calculateZij() {
	
	for (int k = 0; k < K; k++) {
		for (int i = 0; i < n; i++) {
			if (y_i[i] != k)
				continue;
			for (int j = i + 1; j < n; j++) {
				if (y_i[j] != k)
					continue;
				else {
					z_ij[i*n + j] = k;
					
					i = j - 1;
					break;
				}

			}
		}
	}
}

/* �Ժ��� calculateZij��һ������ */
void AirPort::calculateZij(const set<int> &changedK) {

	for (set<int>::const_iterator it = changedK.begin(); it != changedK.end(); it++) {
		//int k = *it;
		for (int i = 0; i < n; i++) {
			if (y_i[i] != *it)
				continue;
			for (int j = i + 1; j < n; j++) {
				if (y_i[j] != *it)
					continue;
				else {
					z_ij[i*n + j] = *it;

					i = j - 1;
					break;
				}

			}
		}
	}
}

void AirPort::calculateZij(changedTerm & changedK)
{
	int oldK = changedK.second.first;
	int newK = changedK.second.second;

	if (oldK == newK) { // stay put
		return;
	}

	if (oldK < K) {
		for (int i = 0; i < n; i++) {
			if (y_i[i] != oldK)
				continue;
			for (int j = i + 1; j < n; j++) {
				if (y_i[j] != oldK)
					continue;
				else {
					z_ij[i*n + j] = oldK;
					i = j - 1;
					break;
				}
			}
		}
	}
	if (newK < K) {
		for (int i = 0; i < n; i++) {
			if (y_i[i] != newK)
				continue;
			for (int j = i + 1; j < n; j++) {
				if (y_i[j] != newK)
					continue;
				else {
					z_ij[i*n + j] = newK;
					i = j - 1;
					break;
				}
			}
		}
	}
}

void AirPort::randomMove() {
	
	int i_1 = rand() % n;
	
	int k_1 = rand() % (NK_i[N[i_1]].size());
	
	y_i[i_1] = NK_i[N[i_1]][k_1];
}

/* �Ժ���randomMove��һ������ */
void AirPort::randomMove(set<int> &changedK) {
	int i_1 = rand() % n;
	int k_1 = rand() % (NK_i[N[i_1]].size());

	if (y_i[i_1] < K)
		changedK.insert(y_i[i_1]);

	y_i[i_1] = NK_i[N[i_1]][k_1];

	if (y_i[i_1] < K)
		changedK.insert(y_i[i_1]);
}

inline void AirPort::randomMove(AirPort::changedTerm & changedK)
{
	int i_1 = rand() % n;
	int k_1 = rand() % (NK_i[N[i_1]].size());
	changedK.first = i_1;

	changedK.second.first = y_i[i_1];
	y_i[i_1] = NK_i[N[i_1]][k_1];
	changedK.second.second = y_i[i_1];
}

/*  ����Ŀ��ֵ���� */
float AirPort::diffCost() {
	f_next[0] = primary_objective();
	for (int i = 0; i < secondary_objs.size(); i++)
		f_next[i+1] = (this->*secondary_objs[i])();

	vector<float> df;
	for (int i = 0; i < f_current.size(); i++) {
		df.push_back(f_next[i] - f_current[i]);
	}
	float factor = 300;
	
	for (int i = 0; i < df.size(); i++) {
		if (df[i] != 0.)
			return df[i] / f_current[i] *  factor;
	}
	return 0;
}

/*  ����Ŀ��ֵ���� */
float AirPort::diffCost(changedTerm &changedK) {
	f_next[0] = primary_objective(changedK);
	for (int i = 0; i < secondary_objs.size(); i++)
		f_next[i + 1] = (this->*c_secondary_objs[i])(changedK);

	vector<float> df;
	for (int i = 0; i < f_current.size(); i++) {
		df.push_back(f_next[i] - f_current[i]);
	}
	float factor = 300;

	for (int i = 0; i < df.size(); i++) {
		if (df[i] != 0.)
			return df[i] / f_current[i] * factor;
	}
	return 0;
}

void AirPort::printY_i(string file)
{
	ofstream f;
	f.open(prefix + "/" + file, ofstream::out);
	assert(f.is_open());

	for (int i = 0; i < n; i++) {
		int k = y_i[i];
		f << pucks[N[i]].plane_num << "    ";
		if (k < K)
			f << gates[k].name << endl;
		else
			f << "��ʱ��" << endl;
	}
	f.close();
}

void AirPort::statistic(Stat & stat)
{
	set<int> N_i;
	set<int> W_i;
	
	memset(&stat, 0, sizeof(stat));
	for (int i = 0; i < N.size(); i++) {
		stat.n_i += 2 * (y_i[i] != m-1);
		if (pucks[N[i]].flight_shape == NARROW) {
			N_i.insert(i);
		}
		else {
			W_i.insert(i);
		}
			
	}
	stat.e_i = (float)stat.n_i / (2 * N.size());

	for (set<int>::const_iterator it = N_i.begin(); it != N_i.end(); it++) {
		stat.h_i += 2 * (y_i[*it] != m - 1);
	}
	for (set<int>::const_iterator it = W_i.begin(); it != W_i.end(); it++) {
		stat.h_i_p += 2 * (y_i[*it] != m - 1);
	}
	stat.g_i = stat.h_i / (2 * N_i.size());
	stat.g_i_p = stat.h_i_p / (2 * W_i.size());

	stat.l_i = 0;
	for (int k = 0; k < 28; k++) {
		int sgn = 0;
		for (int i = 0; i < n; i++) {
			sgn += (y_i[i] == k);
		}
		stat.l_i += SGN(sgn);
	}
	stat.l_i_p = 0;
	for (int k = 28; k < 69; k++) {
		int sgn = 0;
		for (int i = 0; i < n; i++) {
			sgn += (y_i[i] == k);
		}
		stat.l_i_p += SGN(sgn);
	}

	vector<set<int> > A_k(K);
	for (int k = 0; k < K; k++) {
		for (int i = 0; i < N.size(); i++) {
			if (y_i[i] == k)
				A_k[k].insert(i);
		}
	}
	
	stat.q_i = 0;
	stat.q_i_p = 0;
	float sum_1 = 0., sum_2 = 0.;

		float tmp = 0.0;
		for (int k = 0; k < 28; k++) {
			if (A_k[k].empty())
				continue;
			for (set<int>::const_iterator it = A_k[k].begin(); it != A_k[k].end(); it++) {
				int I = N[*it];
				int exact_time1 = 3 * 288;
				int exact_time2 = 2 * 288;
				tmp += MIN(d_i[I], exact_time1) - MAX(a_i[I], exact_time2);
				sum_1 += 1;
			}
		}
		stat.q_i += tmp / 288.;

		float tmp_1 = 0.;
		for (int k = 28; k < K; k++) {
			if (A_k[k].empty())
				continue;
			for (set<int>::const_iterator it = A_k[k].begin(); it != A_k[k].end(); it++) {
					int I = N[*it];
					int exact_time1 = 3 * 288;
					int exact_time2 = 2 * 288;
					tmp_1 += MIN(d_i[I], exact_time1) - MAX(a_i[I], exact_time2);
					sum_2 += 1.;
			}
		}
		stat.q_i_p += tmp_1 / 288;
	

	stat.q_i /= sum_1;
	stat.q_i_p /= sum_2;
}

void AirPort::statistic(Stat2 & stat)
{
	map<int, float> a_sigma_1, a_sigma_2, a_sigma_3, a_sigma_4;
	map<int, float> d_sigma_1, d_sigma_2, d_sigma_3, d_sigma_4;
	memset(&stat, 0, sizeof(stat));
	for (int i = 0; i < n; i++) {
		int n_i = N[i];
		a_sigma_1[n_i] = (y_i[i] < 28) * (pucks[N[i]].arrival_type == DEMOSTIC);
		a_sigma_2[n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].arrival_type == DEMOSTIC);
		a_sigma_3[n_i] = (y_i[i] < 28) * (pucks[N[i]].arrival_type == INTER);
		a_sigma_4[n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].arrival_type == INTER);

		d_sigma_1[n_i] = (y_i[i] < 28) * (pucks[N[i]].departure_type == DEMOSTIC);
		d_sigma_2[n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].departure_type == DEMOSTIC);
		d_sigma_3[n_i] = (y_i[i] < 28) * (pucks[N[i]].departure_type == INTER);
		d_sigma_4[n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].departure_type == INTER);
	}
	vector<map<int, float> > a_sigmas;
	vector<map<int, float> > d_sigmas;
	a_sigmas.push_back(a_sigma_1);
	a_sigmas.push_back(a_sigma_2);
	a_sigmas.push_back(a_sigma_3);
	a_sigmas.push_back(a_sigma_4);
	d_sigmas.push_back(d_sigma_1);
	d_sigmas.push_back(d_sigma_2);
	d_sigmas.push_back(d_sigma_3);
	d_sigmas.push_back(d_sigma_4);

	map<int, float> t_p;
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];
		float tmp = 0.0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp += a_sigmas[i][I] * d_sigmas[j][J] * procedure_time_table[i][j];
			}
		}
		t_p[*p] = tmp;
	}

	stat.O = 0;
	float num_p = 0;
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];
		int S_p = (a_i[I] + t_p[*p] <= d_i[J]);
		stat.O += (1 - S_p) * tickets[*p].num_parssengers;
		num_p += tickets[*p].num_parssengers;
	}
	stat.B = stat.O / num_p;
}

void AirPort::statistic(Stat3 & stat)
{
	map<int, float> gamma_1, gamma_2, gamma_3, gamma_4, gamma_5, gamma_6, gamma_7;
	vector<map<int, float> > gammas;
	for (int i = 0; i < n; i++) {
		int n_i = N[i];
		gamma_1[n_i] = (y_i[i] >= 0 && y_i[i] < 9);
		gamma_2[n_i] = (y_i[i] >= 9 && y_i[i] < 19);
		gamma_3[n_i] = (y_i[i] >= 19 && y_i[i] < 28);
		gamma_4[n_i] = (y_i[i] >= 28 && y_i[i] < 38);
		gamma_5[n_i] = (y_i[i] >= 38 && y_i[i] < 48);
		gamma_6[n_i] = (y_i[i] >= 48 && y_i[i] < 58);
		gamma_7[n_i] = (y_i[i] >= 58 && y_i[i] < 69);
	}
	gammas.push_back(gamma_1);
	gammas.push_back(gamma_2);
	gammas.push_back(gamma_3);
	gammas.push_back(gamma_4);
	gammas.push_back(gamma_5);
	gammas.push_back(gamma_6);
	gammas.push_back(gamma_7);
	map<int, float> w_p;
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		float tmp = 0.;
		int I = a_p[*p];
		int J = d_p[*p];
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				tmp += gammas[i][I] * gammas[j][J] * walk_time_table[i][j];
			}
		}
		w_p[*p] = tmp;
	}
	map<int, float> a_sigma_1, a_sigma_2, a_sigma_3, a_sigma_4;
	map<int, float> d_sigma_1, d_sigma_2, d_sigma_3, d_sigma_4;

	for (int i = 0; i < n; i++) {
		int n_i = N[i];
		a_sigma_1[n_i] = (y_i[i] < 28) * (pucks[N[i]].arrival_type == DEMOSTIC);
		a_sigma_2[n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].arrival_type == DEMOSTIC);
		a_sigma_3[n_i] = (y_i[i] < 28) * (pucks[N[i]].arrival_type == INTER);
		a_sigma_4[n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].arrival_type == INTER);

		d_sigma_1[n_i] = (y_i[i] < 28) * (pucks[N[i]].departure_type == DEMOSTIC);
		d_sigma_2[n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].departure_type == DEMOSTIC);
		d_sigma_3[n_i] = (y_i[i] < 28) * (pucks[N[i]].departure_type == INTER);
		d_sigma_4[n_i] = (y_i[i] >= 28 && y_i[i] < K) * (pucks[N[i]].departure_type == INTER);
	}
	vector<map<int, float> > a_sigmas;
	vector<map<int, float> > d_sigmas;
	a_sigmas.push_back(a_sigma_1);
	a_sigmas.push_back(a_sigma_2);
	a_sigmas.push_back(a_sigma_3);
	a_sigmas.push_back(a_sigma_4);
	d_sigmas.push_back(d_sigma_1);
	d_sigmas.push_back(d_sigma_2);
	d_sigmas.push_back(d_sigma_3);
	d_sigmas.push_back(d_sigma_4);

	map<int, float> t_pp;
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];
		float tmp = 0.0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp += a_sigmas[i][I] * d_sigmas[j][J] * tram_time_table[i][j] * 1.6;
			}
		}
		t_pp[*p] = tmp;
	}

	map<int, float> t_p;
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];
		float tmp = 0.0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp += a_sigmas[i][I] * d_sigmas[j][J] * procedure_time_table[i][j];
			}
		}
		t_p[*p] = tmp;
	}

	float sum_p = 0.;
	stat.O = 0;
	for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
		int I = a_p[*p];
		int J = d_p[*p];
		float r_p = (t_p[*p] + t_pp[*p] + w_p[*p]);
		int S_pp = (a_i[I] + r_p <= d_i[J]);
		sum_p += tickets[*p].num_parssengers;
		stat.O += (1 - S_pp) * tickets[*p].num_parssengers;
	}
	stat.B = stat.O / sum_p;

	float alpha[14] = { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 };
	vector<map<int, int> > mu_pt(14);
	for (int i = 0; i < mu_pt.size(); i++) {
		for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
			float r_p = (t_p[*p] + t_pp[*p] + w_p[*p]);
			mu_pt[i][*p] = (r_p <= alpha[i]);
		}
	}
	stat.v_t.resize(mu_pt.size());
	fill(stat.v_t.begin(), stat.v_t.end(), 0);
	for (int i = 0; i < mu_pt.size(); i++) {
		for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
			stat.v_t[i] += mu_pt[i][*p] * tickets[*p].num_parssengers;
		}
		stat.v_t[i] /= sum_p;
	}

	float mu_t[10] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
	vector<map<int, int> > mu_ptp(10);
	for (int i = 0; i < mu_ptp.size(); i++) {
		for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
			int I = a_p[*p];
			int J = d_p[*p];
			float r_p = (t_p[*p] + t_pp[*p] + w_p[*p]);
			int s_pp = (a_i[I] + r_p <= d_i[J]);
			float c_p = (r_p * s_pp + 72 * (1 - s_pp)) / (d_i[J] - a_i[I]);
			mu_ptp[i][*p] = (c_p <= mu_t[i]);
		}
	}
	stat.v_t_p.resize(mu_ptp.size());
	fill(stat.v_t_p.begin(), stat.v_t_p.end(), 0);
	for (int i = 0; i < mu_ptp.size(); i++) {
		for (vector<int>::const_iterator p = P.begin(); p != P.end(); p++) {
			stat.v_t_p[i] += mu_ptp[i][*p] * tickets[*p].num_parssengers;
		}
		stat.v_t_p[i] /= sum_p;
	}
}

void AirPort::greedyAlg() {

	vector<pair<int, int> > d_pairs; // (flight_id, d_i);
	vector<int> gks(K);  // gk(0<=k<K) represent the earliest available time of gate k.
	std::fill(gks.begin(), gks.end(), -1);
	
	for (int i = 0; i < n; i++) {
		int n_i = N[i];
		vector<int>::const_iterator it;
		for (it = NK_i[i].begin(); it != NK_i[i].end(); it++) {
			if (*it == m - 1)
				continue;
			if (a_i[n_i] >= gks[*it]) {
				y_i[i] = *it;
				gks[*it] = d_i[n_i] + beta;
				break;
			}
		}
		if (it == NK_i[i].end()) {
			y_i[i] = m - 1;
		}
	}
}

bool AirPort::checkY_i() const {
	/* constrain_2*/
	for (int i = 0; i < n; i++) {
		int n_i = N[i];
		map<int, vector<int> >::const_iterator nk_it = NK_i.find(n_i);
		vector<int>::const_iterator it = find(nk_it->second.begin(), nk_it->second.end(), y_i[i]);
		if (it == nk_it->second.end())
			return false;
	}
	/* constrain4 */
	bool res = true;
	for (int i = 0; i < n; i++) {
		if (y_i[i] == K)
			continue;
		for (int j = i + 1; j < n; j++) {
			if (y_i[j] == K)
				continue;
			if (y_i[i] == y_i[j]) {
				res = (res && a_i[N[j]] >= d_i[N[i]] + beta);
				if (!res) {
					cout << "bad" << endl;
				}
				i = j - 1;
				break;
			}

		}
	}

	return res;
}