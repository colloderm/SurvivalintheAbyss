#include "Framework.h"
#include "PlayerPassive.h"

PlayerPassive::PlayerPassive()
{
}

PlayerPassive::~PlayerPassive()
{
    // 종료 후 패시브 값 저장
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
	ofstream fout(path);

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

    PsvHp = stoi(res[0]);
    PsvAtk = stoi(res[1]);
    PsvDef = stoi(res[2]);
    PsvSpd = stof(res[3]);

    //cout << "패시브 불러오기 : " << path << endl;
    cout << "HP  : " << res[0] << endl;
    cout << "ATK : " << res[1] << endl;
    cout << "DEF : " << res[2] << endl;
    cout << "SPD : " << res[3] << endl;
}
