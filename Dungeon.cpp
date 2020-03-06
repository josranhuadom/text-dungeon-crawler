#include "Dungeon.h"
#include <iostream>

using namespace std;

Dungeon::Dungeon(Player p)
{
    player = p;
}

/* 显示选项 */
void Dungeon::printActions(int numActions, string actions[])
{
    cout << "接下来要做什么？（输入数字）\n";
    for(int i = 0; i < numActions; i++)
    {
        cout << actions[i] << "\n";
    }
}

/* 空房间的处理代码 */
void Dungeon::handleEmptyRoom(Room *room)
{
    cout << "你进了一个空房间。\n";
    string actions[] = {"1、移动到其他房间"};
    while(true)
    {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input == "1")
            return;
        else
            cout << "你输入你🐎呢，再输入一遍\n";
    }
}

/* 宝藏房间的处理代码 */
void Dungeon::handleLootActions(Room * room)
{ 
    player.lootRoom(room);
    
    for(int i = 0; i < room->items.size(); i++);
    {
        cout << "箱子里面是……\n" << room -> items.front().name << "！" << endl;
        cout << 
        "现在生命值是" << player.currentHealth << 
        "点，攻击力是：" << player.attack <<
        "点，防御力是：" << player.defense << endl;
    }
    room->clearLoot();
}
void Dungeon::handleChestRoom(Room * room)
{
    cout << "你们进了一个宝箱房间。\n";
    string actions[] = {
        "1、移动到其他房间",
        "2、打开宝箱拿东西——移动到其他房间"
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
            cout << "给👴再输入一遍\n";
        
    }
}

/* 敌人房间的处理代码 */
void Dungeon::handleFightActions(GameCharacter * enemy)
{
    string actions[] = {
        "1、普通攻击",
        "2、撤退……"
    };
    while(true)
    {
        printActions(2, actions);
        int input;
        cin >> input;
        // 玩家动作
        if (input == 1)
        {
            int damage = enemy->takeDamage(player.attack);
            cout << "你给了" << enemy->name << damage << "点伤害!\n";
        }
        else if (input == 2)
        {
            player.changesRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
        else
            cout << "爪巴，再选！\n";

        // 检测敌人是不是死掉
        if(enemy->checkIsDead())
        {
            cout << "战斗胜利！！" << enemy->name << "被击败！" << endl;
            player.increaseStats(10, 5, 5);
            player.currentRoom->clearEnemies();
            return;
        }

        // 没死掉之后对玩家的攻击
        int damage = player.takeDamage(enemy->attack);
        cout << enemy->name <<"给你造成了" << damage << "点伤害！" << endl;
        cout << "目前剩余血量：" << player.currentHealth << endl;

        // 如果玩家死了……
        if (player.checkIsDead())
            return;
        
    }
}

void Dungeon::handleEnemyRoom(Room * room)
{
    GameCharacter enemy = room->enemies.front();
    cout << "你们进了一个敌人房间。" << enemy.name<< "要攻过来了！\n";
    string actions[] = {
        "1、战斗！",
        "2、打不过，还是先撤回上一间房间吧……"
    };
    while(true)
    {
        printActions(2, actions);
        int input;
        cin >> input;
        if (input == 1)
            handleFightActions(&enemy);
        else if (input == 2)
        {
            player.changesRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
        else
            cout << "爪巴，再选！\n";
    }
}


/* 进入房间 */
void Dungeon::enterRoom(Room *room)
{
    if (room->enemies.size())
        handleEnemyRoom(room);
    else if (room->items.size())
        handleChestRoom(room);
    else
        handleEmptyRoom(room);
}

void Dungeon::handleMovementActions(Room * room)
{
    while (true)
    {
        if(room->pos == 0)
        {
            string actions[] = {
                "1、向右走",
                "2、向下走"
            };
            printActions(2, actions);
            int input;
            cin >> input;
            if (input == 1)
                {player.changesRooms(&room[1]); return;}
            else if (input == 2)
                {player.changesRooms(&room[2]); return;}
            else
                cout << "再选！😡" << endl;
        }
        else if (room->pos == 1)
        {
            string actions[] = {"1、向左走"};
            printActions(1, actions);
            int input;
            cin >> input;
            if (input == 1)
                {player.changesRooms(&room[0]); return;}
            else
                cout << "再选！😡" << endl;
        }
        else if (room->pos == 2)
        {
            string actions[] = {
                "1、向上走",
                "2、向右走"
            };
            printActions(2, actions);
            int input;
            cin >> input;
            if (input == 1)
                {player.changesRooms(&room[0]); return;}
            else if (input == 2)
                {player.changesRooms(&room[3]); return;}
            else
                cout << "再选！😡" << endl;
        }
        else
        {
            string actions[] = {"1、向左走"};
            printActions(1, actions);
            int input;
            cin >> input;
            if (input == 1)
                {player.changesRooms(&room[2]); return;}
            else
                cout << "再选！😡" << endl;
        }
    }
}

int Dungeon::performEndGameLogic()
{
    string actions[] = {"1、是","2、否"};
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
            cout << "你最好好好输入" << endl;
        
    }
    

}

/* 整个地牢房间的运转 */
 int Dungeon::runDungeon()
 {
    cout << "欢迎来到该地牢，嘻嘻\n";
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
    
    while(true)
    {
        enterRoom(player.currentRoom);
        if (player.checkIsDead)
        {
            cout << "你被杀了。重来吗？" << endl;
            return performEndGameLogic();
        }
        else
        {
            if (player.currentRoom->isExit)
            {
                if(player.currentRoom->enemies.size == 0)
                {
                    cout << "你赢了。再来一局吗？" << endl;
                    return performEndGameLogic();
                }
            }
        }
        handleMovementActions(player.currentRoom);
    }
 }


