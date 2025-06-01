#ifndef FOODLIST_H
#define FOODLIST_H
#include <iostream>
#include <unordered_map>
using namespace std;

struct Product
{
    string name;
    int caloriesInFood;
    int proteins;
    int fats;
    int carbohydrates;
    int weight;

    friend ostream& operator<<(ostream& stream, const Product& object);
    friend istream& operator>>(istream& stream, Product& object);
    Product();
    string ProductToString();
    Product StringToProduct(string info);
};

class FoodList
{
public:
    void Add(string object);
    void Remove(string objectName);
    void Change(string objectName, string newInfo);
    string Read(string nameOfProduct);
    unordered_map<string, string> catalogue_;
    bool DownloadData();
    bool UploadData();
};

#endif //FOODLIST_H
