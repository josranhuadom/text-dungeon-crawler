#include <iostream>
#include <string>
#include "dungeon.cpp"
#include "Player.cpp"
#include "Room.cpp"
#include "Item.cpp"
#include "GameCharacter.cpp"

using namespace std;

int main()
{
    // 设置房间内物品
    Item sword("剑", 0, 5, 0);

    // 设置敌人
    GameCharacter enemyA("混混", 10, 3, 3);
    GameCharacter enemyB("混混头目", 13, 5, 3);

    // 设置房间1
    Room firstRoom(0, false, vector<Item>(), vector<GameCharacter>());
    // 设置房间2
    vector<Item> secondRoomInventory;
    secondRoomInventory.push_back(sword);
    Room secondRoom(1, false, secondRoomInventory, vector<GameCharacter>());
    // 设置房间3
    vector<GameCharacter> thirdRoomEnemy;
    thirdRoomEnemy.push_back(enemyA);
    Room thirdRoom(2, false, vector<Item>(), thirdRoomEnemy);
    // 设置房间4
    vector<GameCharacter> forthRoomEnemy;
    forthRoomEnemy.push_back(enemyB);
    Room forthRoom(3, true, vector<Item>(), forthRoomEnemy);

    // 玩家开始游玩
    cout << "欢迎来到老孔制作的地下城。勇士请输入你的名字：";
    string playerName;
    cin >> playerName;
    Player thePlayer(playerName, 15, 5, 5);

    Dungeon theGame(thePlayer);
    theGame.rooms[0] = firstRoom;
    theGame.rooms[1] = secondRoom;
    theGame.rooms[2] = thirdRoom;
    theGame.rooms[3] = forthRoom; 


    while(true)
    {
        int result = theGame.runDungeon();
        if(result == 0)
            break;

        cout << "Goodbye!";
    }








}