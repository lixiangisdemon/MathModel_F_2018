#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <forward_list>
#include <cassert>
using namespace std;


/******************************************************************************************/
/*****************************һЩ��Ҫ�����ݽṹ*********************************************/
/*****************************************************************************************/

enum FLIGHT_SHAPE {
	NARROW,
	WIDE,
};

enum A_D_TYPE {
	DEMOSTIC = 5,
	INTER,
	D_OR_I,
};

enum TERMINAL {
	T = 10,
	S,
};

enum AREA {
	NORTH = 20,
	CENTER,
	SOUTH,
	EAST,
	WEST,
};

/* D_T, D_S, I_T, I_S <-> 0, 1, 2, 3*/
inline int map_DIST(TERMINAL TS, A_D_TYPE DI) {
	return TS - T + (DI - DEMOSTIC) * 2;
}

/* {0, ..., 6} <-> {T-N, T-C, T-S, S-N, S-C, S-S, S-E} */
inline int map_TSNCE(TERMINAL TS, AREA NCE) {
	return (TS - T) * 3 + NCE - NORTH;
}

/* ����洢tickets �����ݽṹ */
typedef struct Tickets {
	int parssengerId;
	int num_parssengers;
	string arrival_flight;
	string departure_flight;
	int arrival_date;
	int departure_date;
} Tickets;

/* ����洢Gates �����ݽṹ */
typedef struct Gates {
	string name;
	int gates_id;
	TERMINAL gates_type;
	int area;

	A_D_TYPE arrival_resive_type; // D, I, D_OR_I
	A_D_TYPE departure_release_type;

	FLIGHT_SHAPE flight_resive_shape; // W, N
	bool operator == (const string &str) const {
		return name == str;
	}
} Gates;

/* ����洢Pucks �����ݽṹ */
typedef struct Pucks {
	int flight_id;
	int arrival_date;   // range at {20}
	int departure_date; // range at {20}

	int arrival_time; // range at [0, 288], set every 5 minitues a unit.
	int departure_time;

	string arrival_flight;
	string departure_flight;
	string plane_num;

	A_D_TYPE arrival_type; // D, I
	A_D_TYPE departure_type;
	FLIGHT_SHAPE flight_shape; // W, N
	bool operator == (const string &str) const {
		return plane_num == str;
	}
} Pucks;

/*****************************************************************************************/
/******************************����һЩ���õĺ���*******************************************/
/****************************************************************************************/
inline float MAX(float x, float y) { return ((x) > (y) ? (x) : (y)); }
inline float MIN(float x, float y) { return ((x) < (y) ? (x) : (y)); }
inline int   SGN(float x) { return (int)(x > 0 ? 1 : (x == 0 ? 0 : -1)); }
inline int   SGN(int x) { return (int)(x > 0 ? 1 : (x == 0 ? 0 : -1)); }
inline double myrandom() {
	long long a = rand();
	double r = ((a * 9973 + 1234567) % 99991) / 99991.0;
	return r;
}
void splitBySpace(vector<string> &result, const string &line) {
	result.clear();
	string str = line + " ";
	int start = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ' || str[i] == '\t') {
			if (i != start) {
				string token = str.substr(start, i - start);
				result.push_back(token);
				start = i;
			}

			start++;
		}
	}
}
void splitByColon(vector<string> &result, const string &line) {
	result.clear();
	string str = line + ":";
	int start = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ':') {
			if (i != start) {
				string token = str.substr(start, i - start);
				result.push_back(token);
				start = i;
			}

			start++;
		}
	}
}


inline std::ostream & operator << (std::ostream &out, std::pair<int, int> x) {
	std::cout << "(" << x.first << "," << x.second << ")";
	return out;
}

template <class T>
inline std::ostream & operator << (std::ostream &out, std::vector<T> &vec) {
	if (vec.empty()) {
		out << "" << std::endl;
		return out;
	}
	int size_ = vec.size();
	for (int i = 0; i < size_; i++) {
		out << vec[i];
		if (i < size_ - 1)
			out << ",  ";
	}
	return out;
}