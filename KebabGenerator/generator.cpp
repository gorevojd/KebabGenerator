#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

enum generation_type {
	GenType_PrePrim,
	GenType_PrimSec,
	GenType_PrimPrim,
	GenType_PrimPrimSec,
	GenType_PrePrimSec,

	GenType_Count,
};

struct generator_state {
	vector<string> Pre;
	vector<string> Primary;
	vector<string> Secondary;
};

string GenerateKebabName(generator_state* State, int Type) {
	unordered_set<string> UsedPrim;

	string ResPre;
	string ResPrim;
	string ResSec;

	string TempPre;
	string TempPrim;
	string TempSec;

	int RandPre = rand() % State->Pre.size();
	int RandSec = rand() % State->Secondary.size();
	int RandPrim = rand() % State->Primary.size();

	TempPre = State->Pre[RandPre];
	TempSec = State->Secondary[RandSec];
	
	TempPrim = State->Primary[RandPrim];
	UsedPrim.insert(TempPrim);

	switch (Type) {
		case GenType_PrePrim: {
			ResPre = TempPre;
			ResPrim = TempPrim;
		}break;

		case GenType_PrimSec: {
			ResPrim = TempPrim;
			ResSec = TempSec;
		}break;

		case GenType_PrimPrim: {
			ResPrim = TempPrim;

			int CountLeft = 1;
			while (CountLeft > 0) {
				int Rand = rand() % State->Primary.size();

				string RandPrimTry = State->Primary[Rand];

				if (UsedPrim.find(RandPrimTry) != UsedPrim.end()) {

				}
				else {
					ResPrim = ResPrim + " " + RandPrimTry;
					UsedPrim.insert(RandPrimTry);
					--CountLeft;
				}
			}
		}break;

		case GenType_PrimPrimSec: {
			ResSec = TempSec;
			ResPrim = TempPrim;
			
			int CountLeft = 1;
			while (CountLeft > 0) {
				int Rand = rand() % State->Primary.size();

				string RandPrimTry = State->Primary[Rand];

				if (UsedPrim.find(RandPrimTry) != UsedPrim.end()) {

				}
				else {
					ResPrim = ResPrim + " " + RandPrimTry;
					UsedPrim.insert(RandPrimTry);
					--CountLeft;
				}
			}
		}break;

		case GenType_PrePrimSec: {
			ResPrim = TempPrim;
			ResSec = TempSec;
			ResPre = TempPre;
		}break;
	}

	string Result;
	if (ResPre.length()) {
		Result += ResPre + " ";
	}

	if (ResPrim.length()) {
		Result += ResPrim + " ";
	}

	if (ResSec.length()) {
		Result += ResSec;
	}

	return(Result);
}

int main(int ArgsCount, char** Args) {

	vector<string> Pre{
		"Papa",
		"Happy"
		"Smart",
		"Econom",
		"Super",
		"Super Puper",
		"Super Duper",
		"Express",
	};

	vector<string> Prim{
		"Kebab",
		"Doner",
		"Grill",
		"Shawarma"
		"Hot Dog",
		"Chicken",
		"Texas",
		"Gruzin",
		"Pizza",
		"Food",
	};

	vector<string> Secondary{
		"24/7",
		"Delicious",
		"King",
		"House",
		"Cha-Cha-Cha",
	};

	generator_state Gen = {};
	Gen.Primary = Prim;
	Gen.Secondary = Secondary;
	Gen.Pre = Pre;

	int ToGenerateCount = 100;
	int CountGenerated = 0;
	unordered_set<string> Generated;
	while (CountGenerated < ToGenerateCount) {

		int RandType = rand() % GenType_Count;

		string RandName = GenerateKebabName(&Gen, RandType);

		if (Generated.find(RandName) == Generated.end()) {
			Generated.insert(RandName);
			
			cout << RandName << endl;

			CountGenerated++;
		}
	}

	system("pause");
	return(0);
}