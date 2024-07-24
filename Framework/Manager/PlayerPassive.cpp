#include "Framework.h"
#include "PlayerPassive.h"

PlayerPassive::PlayerPassive()
{
}

PlayerPassive::~PlayerPassive()
{
    // ���� �� �нú� �� ����
}

void PlayerPassive::Update()
{
	if (Keyboard::Get()->Press(VK_CONTROL))
	{
		if (Keyboard::Get()->Down('S'))
		{
			Path::CreateFolders(TilePath);
			PsvSave(TilePath + "PlayerPassive.data");
			PsvSave(TilePath + "PlayerPassive.txt");
		}
		if (Keyboard::Get()->Down('L'))
		{
			PsvLoad(TilePath + "PlayerPassive.data");
		}
	}
}

void PlayerPassive::PsvSave(string path)
{
    cout << "HP���  : " << hpIncreaseCount << endl;
    cout << "ATK��� : " << attackIncreaseCount << endl;
    cout << "DEF��� : " << defenceIncreaseCount << endl;
    cout << "SPD��� : " << speedIncreaseCount << endl;

    cout << "HP  : " << PsvHp << endl;
    cout << "ATK : " << PsvAtk << endl;
    cout << "DEF : " << PsvDef << endl;
    cout << "SPD : " << PsvSpd << endl;

	ofstream fout(path);

    fout << hpIncreaseCount << ",";
    fout << attackIncreaseCount << ",";
    fout << defenceIncreaseCount << ",";
    fout << speedIncreaseCount << ",";

    fout << PsvHp << ",";
    fout << PsvAtk << ",";
    fout << PsvDef << ",";
    fout << PsvSpd;

    /*for (UINT i = 0; i < 4; i++) {
        fout << PsvHp[i];
        if (i < PsvList.size() - 1) {
            fout << ",";
        }
    }*/
}

void PlayerPassive::PsvLoad(string path)
{
    ifstream fin(path);

    if (fin.fail())
        assert(false);

    vector<string> res;
    string temp;

    while (getline(fin, temp, ','))
    {
        res.push_back(temp);
    }

    hpIncreaseCount = stoi(res[0]);
    attackIncreaseCount = stoi(res[1]);
    defenceIncreaseCount = stoi(res[2]);
    speedIncreaseCount = stoi(res[3]);

    PsvHp = stoi(res[4]);
    PsvAtk = stoi(res[5]);
    PsvDef = stoi(res[6]);
    PsvSpd = stof(res[7]);

    //cout << "�нú� �ҷ����� : " << path << endl;
    cout << "HP���  : " << res[0] << endl;
    cout << "ATK��� : " << res[1] << endl;
    cout << "DEF��� : " << res[2] << endl;
    cout << "SPD��� : " << res[3] << endl;

    cout << "HP  : " << res[4] << endl;
    cout << "ATK : " << res[5] << endl;
    cout << "DEF : " << res[6] << endl;
    cout << "SPD : " << res[7] << endl;
}
