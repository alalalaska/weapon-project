#include <iostream>
#include<vector>
#include<list>
#include<ctime>
#include<string>
using namespace std;

#include "weapon.h"


WeaponContainer::WeaponContainer(int maxSize)
{
    WeaponBox = new WeaponPtr[maxSize];
    for(int i=0; i<maxSize; i++)
    {
        WeaponBox[i] = NULL;
    }
    WeaponCount = 0;
    MaxSize = maxSize;
}

WeaponContainer::~WeaponContainer()
{
	for(int i =0 ; i <MaxSize; i++)
	{
		if(WeaponBox[i] != NULL)
		{
			delete WeaponBox[i];
			WeaponBox[i] = NULL;
		}
	}

	delete[] WeaponBox;
}

void WeaponContainer::AddWeapon(WeaponPtr newWeapon)
{
    WeaponBox[WeaponCount] = newWeapon;
    WeaponCount++;
}

wstring PrintWeaponType(const WeaponType type)
{
    switch(type)
    {
        case WeaponType::Pistol: return L"Пистолет";
        case WeaponType::Rifle: return L"Винтовка";
        case WeaponType::ShotGun: return L"Дробовик";
        case WeaponType::MachineGun: return L"Автомат";
        default: return L"Неизвестный";
    }
}

wstring PrintWeaponCaliber(const WeaponCaliber caliber)
{
    switch(caliber)
    {
        case WeaponCaliber::Cal_9mm: return L"9 мм";
        case WeaponCaliber::Cal_7_62mm: return L"7.62 мм";
        case WeaponCaliber::Cal_5_45mm: return L"5.45 мм";
        case WeaponCaliber::Cal_5_56mm: return L"5.56 мм";
        case WeaponCaliber::Cal_12mm: return L"12 мм";
        default: return L"Неизвестный";
    }
}

wstring PrintWeaponCountry (const WeaponCountry country)
{
    switch(country)
    {
    case WeaponCountry::Russia: return  L"Страна производства: Россия";
    case WeaponCountry::USA: return  L"Страна производства: США";
    case WeaponCountry::Austria: return  L"Страна производства: Австрия";
    case WeaponCountry::Germany: return  L"Страна производства: Германия";
    default: return L"Страна производства: Неизвестна";
    }
}

Weapon *CreateWeapon(WeaponType type)
{
    switch(type)
    {
        case WeaponType::Pistol: return new Pistol(static_cast<WeaponCaliber>(rand() % 5), static_cast<WeaponCountry>(rand() % 4));
        case WeaponType::Rifle: return new Rifle(static_cast<WeaponCaliber>(rand() % 5), static_cast<WeaponCountry>(rand() % 4));
        case WeaponType::ShotGun: return new ShotGun(static_cast<WeaponCaliber>(rand() % 5), static_cast<WeaponCountry>(rand() % 4));
        case WeaponType::MachineGun: return new MachineGun(static_cast<WeaponCaliber>(rand() % 5), static_cast<WeaponCountry>(rand() % 4));
        default: return NULL;
    }
}

Weapon *Weapon::Create(WeaponType type)
{
    return CreateWeapon(type);
}

void TaskWeaponIsGood(Iterator<WeaponPtr> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        const WeaponPtr currentWeapon = it->GetCurrent();
        wcout << PrintWeaponType(currentWeapon->GetType()) << L", " << PrintWeaponCaliber(currentWeapon->GetCaliber()) << L", " << PrintWeaponCountry(currentWeapon->GetCountry()) << L", " << (currentWeapon->IsGood() ? L"Хорошее" : L"Плохое") << endl;
    }
}

int main()
{
    setlocale (LC_ALL, "Russian");
    wcout<<L"Стрелковое оружие"<<endl;
    srand(time(0));

    int boxSize = rand() % 299 + 1;

    WeaponContainer weaponBox(boxSize);
    MegaWeaponContainer megaWeaponBox;

    for(int i = 0; i < boxSize; i++)
    {
        weaponBox.AddWeapon(CreateWeapon(static_cast<WeaponType>(rand() % 4)));
    }

    for(int i = 0; i < rand() % 299 + 1; i++)
    {
        megaWeaponBox.AddWeapon(CreateWeapon (static_cast<WeaponType>(rand() % 4)));
    }

    Iterator<WeaponPtr> *it = new WeaponIsGoodDecorator(weaponBox.GetIterator(), true);
	TaskWeaponIsGood(it);
};
