//
// Created by bdten on 11/26/2023.
//

#ifndef PROJECT8_EXPRESSIONTREE_H
#include <iostream>
#include "UTString.h"
#include <vector>
#include "Project8.h"
#define PROJECT8_EXPRESSIONTREE_H
int flag =0;
using namespace std;
class ExpNode{
public:
    string val;
    ExpNode *left, *right;
    ExpNode(){
        this->left = NULL;
        this->right = NULL;
    }
    ExpNode(string val){
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }
};
class Stack{
public:
    ExpNode *treeNode;
    Stack *next;
    Stack(ExpNode *ExpNode){
        this->treeNode = ExpNode;
        next = NULL;
    }
};
class ExpressionTree{
private:
    Stack *top;
public:
    ExpressionTree(){
        top = NULL;
    }
    // function to push a node in stack
    void push(ExpNode *ptr){
        if (top == NULL)
            top = new Stack(ptr);
        else
        {
            Stack *nptr = new Stack(ptr);
            nptr->next = top;
            top = nptr;
        }
    }
    ExpNode *pop(){
        ExpNode *ptr = top->treeNode;
        top = top->next;
        return ptr;
    }
    ExpNode *peek(){
        return top->treeNode;
    }
    void insert(string val){
        if (isNum(val)){
            ExpNode *nptr = new ExpNode(val);
            push(nptr);
        }
        else if (isOper(val))
        {
            if(val == "~" || val == "!"){
                flag = 1;
            }
            ExpNode *nptr = new ExpNode(val);
            nptr->left = pop();
            if(flag == 0){
                nptr->right = pop();
            }
            push(nptr);
            flag =0;
        }
    }
    bool isNum(string oper){
        return oper >= "0" && oper <= "9" || oper>="A" && oper<="Z" || oper>="a" && oper<="z";
    }
    bool isOper(string oper){
        return oper == "+" || oper == "-" || oper == "*" || oper == "/" || oper== "<" || oper== ">" || oper== "!" || oper== "~"|| oper== "=="|| oper== "!="|| oper== "&&"|| oper== "||"|| oper== "<="|| oper== ">="|| oper== "%";
    }
    void construct(vector<UTString>& arr){
        for (auto i = arr.rbegin(); i != arr.rend(); ++i )  {
            string str;
            str.assign(i->ptr);
            insert(str);
        }
    }
    int inOrder(ExpNode *ptr){
        if (!ptr) {
            return 0;
        }
        if (!ptr->left && !ptr->right) {
            return stoi(ptr->val);
        }
        int l_val = inOrder(ptr->left);
        int r_val = inOrder(ptr->right);
        if (ptr->val=="+") {
            return l_val + r_val;
        }
        if (ptr->val=="-") {
            return l_val - r_val;
        }
        if (ptr->val=="*") {
            return l_val * r_val;
        }
        if (ptr->val=="<"){return l_val<r_val? 1:0;}
        if (ptr->val==">"){return l_val>r_val?1:0;}
        if (ptr->val=="=="){ return l_val == r_val? 1:0;}
        if (ptr->val=="!="){ return l_val != r_val?1:0;}
        if(ptr->val=="%"){return l_val%r_val;}
        if(ptr->val=="<="){return l_val<=r_val?1:0;}
        if(ptr->val==">="){return l_val>=r_val?1:0;}
        if(ptr->val=="&&"){return l_val&&r_val?1:0;}
        if(ptr->val=="||"){return l_val||r_val?1:0;}
        if (ptr->val=="~"){
            return -1*l_val;
        }
        if(ptr->val=="!"){
            return !l_val;
        }
        return l_val/r_val;
    }
};
#endif //PROJECT8_EXPRESSIONTREE_H
