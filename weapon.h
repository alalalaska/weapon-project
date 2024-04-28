#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "WeaponPattern.h"


enum class WeaponType: int
{
    Pistol, //пистолет
    Rifle, //винтовка
    ShotGun, //дробовик
    MachineGun, // автомат
    UnknownType = -1
};

enum class WeaponCaliber: int
{
    Cal_9mm = 0,
    Cal_7_62mm = 1,
    Cal_5_45mm = 2,
    Cal_5_56mm = 3,
    Cal_12mm = 4,
    UnknownCaliber = -1
};

enum class WeaponCountry: int
{
    Russia = 0,
    USA = 1,
    Austria = 2,
    Germany = 3,
    UnknownCountry = -1
};

class Weapon
{
protected:
    WeaponCaliber Caliber; // калибр
    WeaponCountry Country; // страна производства
    //double Weight; // масса оружия
    //double BulletSpeed; //начальная скорость пули
    //int MagazineCapacity; //патронов в магазине
    bool WeaponIsGood; //оружие исправно

    Weapon()
    {
        WeaponIsGood = bool (rand() % 2);

        Country = WeaponCountry::UnknownCountry;
        Caliber = WeaponCaliber::UnknownCaliber;
        //Weight = double (rand() % 3.5);
        //BulletSpeed = double (rand() % 801);
        //MagazineCapacity = int (rand() % 31);
    };

public:
    bool IsGood() const { return WeaponIsGood; }
    //int MagCap() const { return MagazineCapacity; }
    //double WeaponWeight() const { return Weight; }
    //double Speed() const { return BulletSpeed; }
    WeaponCaliber GetCaliber() const { return Caliber; }
    WeaponCountry GetCountry() const { return Country; }

    virtual WeaponType GetType() const = 0;

    virtual void Shoot() = 0; //выстрелить
    virtual void EquipMag() = 0; //снарядить магазин
    virtual void Cleaning() = 0; //чистка оружия
    virtual void Buy() = 0; //покупка оружия
    virtual void Sell() = 0; //продажа оружия

    static Weapon *Create(WeaponType type);
};

typedef Weapon *WeaponPtr;

class Pistol : public Weapon
{
public:
    Pistol(WeaponCaliber caliber, WeaponCountry country) : Weapon() { Caliber = caliber; Country = country; }

    WeaponType GetType() const { return WeaponType::Pistol; }

    void Shoot() { wcout<< L"Вы выстрелили из пистолета"; }
    void EquipMag() { wcout<< L"Вы снарядили магазин пистолета"; }
    void Cleaning() { wcout<< L"Вы почистили пистолет"; }
    void Sell() { wcout<< L"Вы продали пистолет"; }
    void Buy() { wcout<< L"Вы купили пистолет"; }

};

class Rifle : public Weapon
{
public:
    Rifle(WeaponCaliber caliber, WeaponCountry country) : Weapon() { Caliber = caliber; Country = country; }
    WeaponType GetType() const { return WeaponType::Rifle; }

    void Shoot() { wcout<< L"Вы выстрелили из винтовки"; }
    void EquipMag() { wcout<< L"Вы снарядили магазин винтовки"; }
    void Cleaning() { wcout<< L"Вы почистили винтовку"; }
    void Sell() { wcout<< L"Вы продали винтовку"; }
    void Buy() { wcout<< L"Вы купили винтовку"; }

};

class ShotGun : public Weapon
{
public:
    ShotGun(WeaponCaliber caliber, WeaponCountry country) : Weapon() { Caliber = caliber; Country = country; }

    WeaponType GetType() const { return WeaponType::ShotGun; }

    void Shoot() { wcout<< L"Вы выстрелили из дробовика"; }
    void EquipMag() { wcout<< L"Вы снарядили дробовик"; }
    void Cleaning() { wcout<< L"Вы почистили дробовик"; }
    void Sell() { wcout<< L"Вы продали дробовик"; }
    void Buy() { wcout<< L"Вы купили дробовик"; }

};

class MachineGun : public Weapon
{
public:
    MachineGun(WeaponCaliber caliber, WeaponCountry country) : Weapon() { Caliber = caliber; Country = country; }

    WeaponType GetType() const { return WeaponType::MachineGun; }

    void Shoot() { wcout<< L"Вы выстрелили из автомата"; }
    void EquipMag() { wcout<< L"Вы снарядили магазин автомата"; }
    void Cleaning() { wcout<< L"Вы почистили автомат"; }
    void Sell() { wcout<< L"Вы продали автомат"; }
    void Buy() { wcout<< L"Вы купили автомат"; }

};

class WeaponContainerIterator : public Iterator<WeaponPtr>
{
private:
    const WeaponPtr *WeaponBox;
    int Position;
    int Count;
public:
    WeaponContainerIterator(const WeaponPtr *weaponBox, int count)
    {
        WeaponBox = weaponBox;
        Count = count;
        Position = 0;
    }

    void First() {Position = 0;}
    void Next() {Position++;}
    bool IsDone() const {return Position >= Count;}
    WeaponPtr GetCurrent() const {return WeaponBox[Position];}
};

class WeaponContainer
{
private:
    WeaponPtr *WeaponBox;
    int WeaponCount;
    int MaxSize;
public:
    WeaponContainer(int maxSize);
    virtual ~WeaponContainer();
    void AddWeapon(WeaponPtr newWeapon);
    int GetCount() const {return WeaponCount;}
    WeaponPtr GetByIndex(int index) const {return WeaponBox[index];}

    Iterator<WeaponPtr> * GetIterator()
    {
        return new WeaponContainerIterator(WeaponBox, WeaponCount);
    }
};

class MegaWeaponContainerIterator : public Iterator<WeaponPtr>
{
private:
	const std::list<WeaponPtr> *WeaponBox;
	std::list<WeaponPtr>::const_iterator it;

public:
	MegaWeaponContainerIterator(const std::list<WeaponPtr> *weaponBox)
	{
		WeaponBox = weaponBox;
		it = WeaponBox->begin();
	}
	void First(){it = WeaponBox->begin();}
	void Next() {it++;}
	bool IsDone() const {return it == WeaponBox->end();}
	WeaponPtr GetCurrent() const { return *it; }
};

class MegaWeaponContainer
{
private:
    std::list<WeaponPtr> WeaponBox;
public:
    void AddWeapon (WeaponPtr newWeapon) {WeaponBox.push_back(newWeapon);}
    int GetCount() const {return WeaponBox.size();}

    Iterator<WeaponPtr> *GetIterator()
    {
        return new MegaWeaponContainerIterator( &WeaponBox);
    }

};

///Декораторы для итератора контейнера WeaponContainer

class WeaponTypeIteratorDecorator : public IteratorDecorator<WeaponPtr>
{
private:
    WeaponType TargetType;

public:
    WeaponTypeIteratorDecorator(Iterator<WeaponPtr> *it, WeaponType targetType): IteratorDecorator(it)
    {
        TargetType = targetType;
    }
    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetType() != TargetType)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetType() != TargetType);
    }
};

class WeaponCountryIteratorDecorator : public IteratorDecorator<WeaponPtr>
{
private:
    WeaponCountry targetCountry;

public:
    WeaponCountryIteratorDecorator(Iterator<WeaponPtr> *it, WeaponCountry country)
        : IteratorDecorator(it), targetCountry(country) {}

    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetCountry() != targetCountry)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetCountry() != targetCountry);
    }
};

class WeaponCaliberIteratorDecorator : public IteratorDecorator<WeaponPtr>
{
private:
    WeaponCaliber targetCaliber;

public:
    WeaponCaliberIteratorDecorator(Iterator<WeaponPtr> *it, WeaponCaliber caliber)
        : IteratorDecorator(it), targetCaliber(caliber) {}

    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetCaliber() != targetCaliber)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetCaliber() != targetCaliber);
    }
};

class WeaponIsGoodDecorator : public IteratorDecorator<WeaponPtr>
{
private:
    bool TargetGood;

public:
    WeaponIsGoodDecorator(Iterator<WeaponPtr> *it, bool targetGood) : IteratorDecorator(it)
    {
        TargetGood = targetGood;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->IsGood() != TargetGood)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->IsGood() != TargetGood);
    }
};


#endif // WEAPON_H_INCLUDED
