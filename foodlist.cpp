#include "foodlist.h"
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Product::Product()
{
    name = "";
    caloriesInFood = 0;
    proteins = 0;
    fats = 0;
    carbohydrates = 0;
    weight=0;
}

ostream& operator<<(ostream& stream, const Product& object)
{
    return (stream << "Product name: " << object.name << endl << "Calories: " << object.caloriesInFood << endl <<
            "Proteins: " << object.proteins << endl << "Fats: " << object.fats << endl << "Carbohydrates: " << object.
                                           carbohydrates << endl << "Weight: " << object.weight << endl);
}

istream& operator>>(istream& stream, Product& object)
{
    cout << "Enter product name: ";
    stream >> object.name;
    cout << "Enter calories in food: ";
    stream >> object.caloriesInFood;
    cout << "Enter proteins: ";
    stream >> object.proteins;
    cout << "Enter fats: ";
    stream >> object.fats;
    cout << "Enter carbohydrates: ";
    stream >> object.carbohydrates;
    cout << "Enter weight: ";
    stream >> object.weight;
    return stream;
}

string Product::ProductToString()
{
    stringstream st;
    st << this->name << " " << this->caloriesInFood << " " << this->proteins <<
        " " << this->fats << " " << this->carbohydrates;
    string product = st.str();
    return product;
}

//ще подумати над реалізацією
Product Product::StringToProduct(string info)
{
    char delimiter=' ';
    string token;
    istringstream stream(info);

    getline(stream,this->name,delimiter);

    getline(stream,token,delimiter);
    this->caloriesInFood = stoi(token);

    getline(stream,token,delimiter);
    this->proteins = stoi(token);

    getline(stream,token,delimiter);
    this->fats = stoi(token);

    getline(stream,token,delimiter);
    this->carbohydrates = stoi(token);

    getline(stream,token,delimiter);
    this->weight = stoi(token);

    return *this;
}

void FoodList::Add(string object)
{
    string token, name, temp;

    stringstream stream(object);
    getline(stream,name,' ');
    getline(stream,temp,'\n');

    //auto ip=catalogue_.begin();
    //auto& prod=catalogue_[name];
    for(const auto& [key,value]:catalogue_)
    {
        if(value==object)
            return;
    }
    /*for(ip;ip!=catalogue_.end();ip++)
    {
        temp=ip->second;
        if(temp.find(token)!=string::npos)
        {
            //cout<<"Продукт з такими характеристиками вже є в каталозі продуктів і страв:"<<endl;
            //cout<<temp<<endl;
            return;
        }
    }*/
    catalogue_.insert({name,object});
}

string FoodList::Read(string nameOfProduct)
{
    if(catalogue_.find(nameOfProduct)!=catalogue_.end())
    {
        return catalogue_.find(nameOfProduct)->second;
    }
}

void FoodList::Remove(string objectName)
{
    if(catalogue_.find(objectName)!=catalogue_.end())
    {
        catalogue_.erase(objectName);
    }
}

void FoodList::Change(string objectName, string newInfo)
{
    if(catalogue_.find(objectName)!=catalogue_.end())
    {
        catalogue_.find(objectName)->second=newInfo;
    }
}

bool FoodList::DownloadData()
{
    ifstream foodFile("Food.txt");
    if (!foodFile.is_open()) return false;
    string object;
    Product product;
    while (getline(foodFile, object))
    {
        product = product.StringToProduct(object);
        catalogue_.insert({product.name,object});
    }
    foodFile.close();
    return true;
}

//приблизне рішення
bool FoodList::UploadData()
{
    string object;

    ofstream foodFile("Food.txt");
    if (!foodFile.is_open()) return false;

    auto ip=catalogue_.begin();
    for(ip;ip!=catalogue_.end();ip++)
    {
        object=ip->second;
        foodFile << object <<'\n';
    }

    foodFile.close();
    return true;
}
