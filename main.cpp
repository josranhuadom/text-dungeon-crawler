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
    // ���÷�������Ʒ
    Item sword("��", 0, 5, 0);

    // ���õ���
    GameCharacter enemyA("���", 10, 3, 3);
    GameCharacter enemyB("���ͷĿ", 13, 5, 3);

    // ���÷���1
    Room firstRoom(0, false, vector<Item>(), vector<GameCharacter>());
    // ���÷���2
    vector<Item> secondRoomInventory;
    secondRoomInventory.push_back(sword);
    Room secondRoom(1, false, secondRoomInventory, vector<GameCharacter>());
    // ���÷���3
    vector<GameCharacter> thirdRoomEnemy;
    thirdRoomEnemy.push_back(enemyA);
    Room thirdRoom(2, false, vector<Item>(), thirdRoomEnemy);
    // ���÷���4
    vector<GameCharacter> forthRoomEnemy;
    forthRoomEnemy.push_back(enemyB);
    Room forthRoom(3, true, vector<Item>(), forthRoomEnemy);

    // ��ҿ�ʼ����
    cout << "��ӭ�����Ͽ������ĵ��³ǡ���ʿ������������֣�";
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