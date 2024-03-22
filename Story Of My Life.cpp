// Story Of My Life.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Weapon {
protected:
    string name;
    int ammo;

public:
    Weapon(const string& weaponName, int initialAmmo) : name(weaponName), ammo(initialAmmo) {}

    virtual void pickUp() {
        cout << "Picking up " << name << "..." << endl;
    }

    virtual void drop() {
        cout << "Dropping " << name << "..." << endl;
    }

    virtual void shoot() {
        if (ammo > 0) {
            cout << "Shooting with " << name << "..." << endl;
            ammo--;
        }
        else {
            cout << "Out of ammo for " << name << "!" << endl;
        }
    }

    virtual void reload() {
        cout << "Reloading " << name << "..." << endl;
        ammo = 30; 
    }

    int getAmmo() const {
        return ammo;
    }

    string getName() const {
        return name;
    }
};

class Pistol : public Weapon {
public:
    Pistol() : Weapon("Pistol", 12) {}
};


class Rifle : public Weapon {
public:
    Rifle() : Weapon("Rifle", 30) {} 
};

// Í³æ
class Knife : public Weapon {
public:
    Knife() : Weapon("Knife", 0) {}

    void pickUp() override {
        cout << "Cannot pick up Knife!" << endl;
    }

    void drop() override {
        cout << "Cannot drop Knife!" << endl;
    }

    void shoot() override {
        cout << "Cannot shoot with Knife!" << endl;
    }

    void reload() override {
        cout << "Cannot reload Knife!" << endl;
    }
};

class Player {
private:
    vector<Weapon*> inventory;

public:
    void pickUpWeapon(Weapon* weapon) {
        if (inventory.size() < 3) {
            inventory.push_back(weapon);
            weapon->pickUp();
        }
        else {
            cout << "Cannot pick up more than 3 weapons!" << endl;
        }
    }

    void dropWeapon(int index) {
        if (index >= 0 && index < inventory.size()) {
            inventory[index]->drop();
            delete inventory[index];
            inventory.erase(inventory.begin() + index);
        }
        else {
            cout << "Invalid weapon index!" << endl;
        }
    }

    void useWeapon(int index) {
        if (index >= 0 && index < inventory.size()) {
            inventory[index]->shoot();
        }
        else {
            cout << "Invalid weapon index!" << endl;
        }
    }

    void reloadWeapon(int index) {
        if (index >= 0 && index < inventory.size()) {
            inventory[index]->reload();
        }
        else {
            cout << "Invalid weapon index!" << endl;
        }
    }

    void displayInventory() const {
        cout << "Inventory:" << endl;
        for (size_t i = 0; i < inventory.size(); ++i) {
            cout << i << ". " << inventory[i]->getAmmo() << " rounds of " << inventory[i]->getName() << endl;
        }
    }

    ~Player() {
        for (auto weapon : inventory) {
            delete weapon;
        }
    }
};

int main() {
    Player player;

    Weapon* pistol = new Pistol();
    Weapon* rifle = new Rifle();
    Weapon* knife = new Knife();

    player.pickUpWeapon(pistol);
    player.pickUpWeapon(rifle);
    player.pickUpWeapon(knife);

    player.displayInventory();
    player.useWeapon(0);
    player.reloadWeapon(1);
    player.displayInventory();

    player.dropWeapon(0);
    player.displayInventory();

    return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
