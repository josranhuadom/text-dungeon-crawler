#include "Dungeon.h"
#include <iostream>

using namespace std;

Dungeon::Dungeon(Player p)
{
    player = p;
}

/* ��ʾѡ�� */
void Dungeon::printActions(int numActions, string actions[])
{
    cout << "������Ҫ��ʲô�����������֣�\n";
    for(int i = 0; i < numActions; i++)
    {
        cout << actions[i] << "\n";
    }
}

/* �շ���Ĵ������ */
void Dungeon::handleEmptyRoom(Room *room)
{
    cout << "�����һ���շ��䡣\n";
    string actions[] = {"1���ƶ�����������"};
    while(true)
    {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input == "1")
            return;
        else
            cout << "��������?�أ�������һ��\n";
    }
}

/* ���ط���Ĵ������ */
void Dungeon::handleLootActions(Room * room)
{ 
    player.lootRoom(room);
    
    for(int i = 0; i < room->items.size(); i++)
    {
        cout << "����������ǡ���\n" << room -> items.front().name << "��\n";
        cout << 
        "��������ֵ��" << player.currentHealth << 
        "�㣬�������ǣ�" << player.attack <<
        "�㣬�������ǣ�" << player.defense << endl;
    }
    room->clearLoot();
}
void Dungeon::handleChestRoom(Room * room)
{
    cout << "���ǽ���һ�����䷿�䡣\n";
    string actions[] = {
        "1���ƶ�����������",
        "2���򿪱����ö��������ƶ�����������"
    };
    while(true)
    {
        printActions(2, actions);
        int input;
        cin >> input;
        if (input == 1)
            return;
        else if (input == 2)
        {
            handleLootActions(room);
            return;
        }
        else
            cout << "��ү������һ��\n";
            cout << endl;
        
    }
}

/* ���˷���Ĵ������ */
void Dungeon::handleFightActions(GameCharacter * enemy)
{
    string actions[] = {
        "1����ͨ����",
        "2�����ˡ���"
    };
    while(true)
    {
        printActions(2, actions);
        int input;
        cin >> input;
        // ��Ҷ���
        if (input == 1)
        {
            int damage = enemy->takeDamage(player.attack);
            cout << "�����" << enemy->name << damage << "���˺�!\n";
        }
        else if (input == 2)
        {
            player.changesRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
        else
            cout << "צ�ͣ���ѡ��\n";

        // �������ǲ�������
        if(enemy->checkIsDead())
        {
            cout << "ս��ʤ������" << enemy->name << "�����ܣ�" << endl;
            player.increaseStats(10, 5, 5);
            player.currentRoom->clearEnemies();
            return;
        }

        // û����֮�����ҵĹ���
        int damage = player.takeDamage(enemy->attack);
        cout << enemy->name <<"���������" << damage << "���˺���" << endl;
        cout << "Ŀǰʣ��Ѫ����" << player.currentHealth << endl;

        // ���������ˡ���
        if (player.checkIsDead())
            return;
    }
}

void Dungeon::handleEnemyRoom(Room * room)
{
    GameCharacter enemy = room->enemies.front();
    cout << "���ǽ���һ�����˷��䡣" << enemy.name<< "Ҫ�������ˣ�\n";
    string actions[] = {
        "1��ս����",
        "2���򲻹��������ȳ�����һ�䷿��ɡ���"
    };
    while(true)
    {
        printActions(2, actions);
        int input;
        cin >> input;
        if (input == 1)
            {handleFightActions(&enemy); return;}
        else if (input == 2)
        {
            player.changesRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
        else
            cout << "צ�ͣ���ѡ��\n";
    }
}


/* ���뷿�� */
void Dungeon::enterRoom(Room *room)
{
    if (room->enemies.size())
        handleEnemyRoom(room);
    else if (room->items.size())
        handleChestRoom(room);
    else
        handleEmptyRoom(room);
}

// �������ƶ�
void Dungeon::handleMovementActions(Room * room)
{
    while (true)
    {
        if(room->pos == 0)
        {
            string actions[] = {
                "1��������",
                "2��������"
            };
            printActions(2, actions);
            int input;
            cin >> input;
            if (input == 1)
                {player.changesRooms(&room[1]); return;}
            else if (input == 2)
                {player.changesRooms(&room[2]); return;}
            else
                cout << "��ѡ��?" << endl;
        }
        else if (room->pos == 1)
        {
            string actions[] = {"1��������"};
            printActions(1, actions);
            int input;
            cin >> input;
            if (input == 1)
                {player.changesRooms(&room[-1]); return;}
            else
                cout << "��ѡ��?" << endl;
        }
        else if (room->pos == 2)
        {
            string actions[] = {
                "1��������",
                "2��������"
            };
            printActions(2, actions);
            int input;
            cin >> input;
            if (input == 1)
                {player.changesRooms(&room[0]); return;}
            else if (input == 2)
                {player.changesRooms(&room[3]); return;}
            else
                cout << "��ѡ��?" << endl;
        }
        else
        {
            string actions[] = {"1��������"};
            printActions(1, actions);
            int input;
            cin >> input;
            if (input == 1)
                {player.changesRooms(&room[2]); return;}
            else
                cout << "��ѡ��?" << endl;
        }
    }
}

int Dungeon::performEndGameLogic()
{
    string actions[] = {"1����","2����"};
    while (true)
    {
        printActions(2, actions);
        int input;
        cin >> input;
        if (input == 1)
            return 1;
        else if(input == 2)
            return 0;
        else
            cout << "����ø�?�ú�����" << endl;
        
    }
    

}

/* �������η������ת */
 int Dungeon::runDungeon()
 {
    cout << "��ӭ�����õ��Σ�����\n";
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
    
    while(true)
    {
        enterRoom(player.currentRoom);
        if (player.checkIsDead())
        {
            cout << "�㱻ɱ�ˡ�������" << endl;
            return performEndGameLogic();
        }
        else
        {
            if (player.currentRoom->isExit)
            {
                if(player.currentRoom->enemies.size() == 0)
                {
                    cout << "��Ӯ�ˡ�����һ����" << endl;
                    return performEndGameLogic();
                }
            }
        }
        handleMovementActions(player.currentRoom);
    }
 }


