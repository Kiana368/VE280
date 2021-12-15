#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "Dlist.h"
#include "Instr.h"
using namespace std;

// For this stack, we let bottom of the stack be "front", top be "back".
// We deal with the elements from "back" to "front".
class Stack:Dlist<int32_t>{
public:
    Dlist<int32_t> list;        // a Dlist list with variable type "int32_t"
    void push_back(const int32_t *ob)
    // MODIFIES: this
    // EFFECTS: inserts ob at the back of the stack
    {
        auto *nob= new int32_t(*ob);
        list.insertBack(nob);
    }
    void pop()
    // MODIFIES: this
    // EFFECTS: removes the last object from non-empty stack
    {
        int32_t *top_ob=list.removeBack();
        delete top_ob;
    }
    int back_first()
    // EFFECTS: returns the last object of non-empty stack
    {
        int32_t *bf_ob_ptr=list.removeBack();
        int32_t bf_ob=*bf_ob_ptr;
        list.insertBack(bf_ob_ptr);
        return bf_ob;
    }
};

// for this quene, we let bottom of the quene be "back", top be "front".
// We deal with the instructions from "front" to "back".
class Quene:Dlist<Instr>{
public:
    Dlist<Instr> list;        // a Dlist list with variable type "int32_t"
    void push_back(Instr *ob)
    // MODIFIES: this
    // EFFECTS: inserts ob at the back of the quene
    {
        auto *nob= new Instr(*ob);
        list.insertBack(nob);
    }
    void pop()
    // MODIFIES: this
    // EFFECTS: removes the first object from non-empty quene
    {
        Instr *top_ob=list.removeFront();
        delete top_ob;
    }
    Instr top()
    // EFFECTS: returns the first object of non-empty quene
    {
        Instr *top_ob_ptr=list.removeFront();
        Instr top_ob=*top_ob_ptr;
        list.insertFront(top_ob_ptr);
        return top_ob;
    }
};

void func_add(Stack &stack_td)
// MODIFIES: stack_td
// EFFECTS: removes the two elements at the back of the stack_td,
// then insert a new element which is the sum of the two elements.
{
    int32_t a=stack_td.back_first();
    stack_td.pop();
    int32_t b=stack_td.back_first();
    stack_td.pop();
    int32_t result=a+b;
    int32_t *result_ptr=&result;
    stack_td.push_back(result_ptr);
}

void func_nor(Stack &stack_td)
// MODIFIES: stack_td
// EFFECTS: removes the two elements at the back of the stack_td,
// then insert a new element which is the nor-result of the two elements.
{
    int32_t a=stack_td.back_first();
    stack_td.pop();
    int32_t b=stack_td.back_first();
    stack_td.pop();
    int32_t result=~(a|b);
    int32_t *result_ptr=&result;
    stack_td.push_back(result_ptr);
}

void func_ifz(Stack &stack_td, Instr &cur_ins, Quene &quene_td)
// MODIFIES: stack_td, quene_td
// EFFECTS: if the element at the back of stack is 0, pop up
// the following n instructions. Otherwise, do nothing.
{
    int32_t a=stack_td.back_first();
    stack_td.pop();
    if (a==0){
        for (int i = 0; i <cur_ins.parameter ; ++i) {
            quene_td.pop();
        }
    }
}

void func_load(Stack &stack_td, const int32_t *mem)
// MODIFIES: stack_td, mem[]
// EFFECTS: get the value stored in mem[] by letting the element at the
// back of the stack be address. Then, add the value to the back of the stack.
{
    int32_t address=stack_td.back_first();
    stack_td.pop();
    int32_t value=mem[address];
    int32_t *value_ptr=&value;
    stack_td.push_back(value_ptr);
}

void func_store(Stack &stack_td, int32_t *mem)
// MODIFIES: stack_td, mem[]
// EFFECTS: get the address and the new value by getting the two
// elements at the back of the stack. Then, update mem[].
{
    int32_t address=stack_td.back_first();
    stack_td.pop();
    int32_t value=stack_td.back_first();
    stack_td.pop();
    mem[address]=value;
}

void func_push(Stack &stack_td, Instr &cur_ins)
// MODIFIES: stack_td
// EFFECTS: push back an element cur_ins.parameter to the back of the stack
{
    int32_t *n_ptr;
    n_ptr=&cur_ins.parameter;
    stack_td.push_back(n_ptr);
}

void stack_machine(int &simple_mode, Instr &cur_ins, Stack &stack_td, Quene &quene_td, int *mem)
// EFFECTS: print the machine status
{
    if (simple_mode==0) cout<<cur_ins<<endl;
    cout<<stack_td.list<<endl;
    if(simple_mode==0) cout<<quene_td.list<<endl;
    for (int j = 0; j <16 ; ++j) {
        cout<<mem[j]<<' ';
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    //Todo: load the stack, the instruction list, and the memory array.
    int32_t simple_mode=0, end_flag=0;
    if (argc==2) simple_mode=1;
    int stack_num, quene_num;
    cin>>stack_num>>quene_num;
    //load stack
    Stack stack_td;
    Quene quene_td;
    int32_t val;
    int32_t *val_ptr=&val;
    for (int l = 0; l <stack_num ; ++l) {
        cin>>val;
        stack_td.push_back(val_ptr);
    }
    //load instruction list
    Instr cur_ins{};
    Instr *cur_ins_ptr=&cur_ins;
    for (int i = 0; i <quene_num ; ++i) {
        cin >> cur_ins;
        quene_td.push_back(cur_ins_ptr);
    }
    // load memory array
    int32_t mem[16];
    for (int & j : mem) cin>>j;

    // Todo: execute the instructions: ADD, NOR, IFZ, HALT, LOAD, STORE, POP, PUSHI, NOOP
    for (int k = 0; k <quene_num ; ++k) {
        cur_ins=quene_td.top();
        quene_td.pop();
        switch (cur_ins.name) {
            case InstrName::ADD :{
                func_add(stack_td);
                break;
            }
            case InstrName::NOR :{
                func_nor(stack_td);
                break;
            }
            case InstrName::IFZ :{
                func_ifz(stack_td,cur_ins,quene_td);
                break;
            }
            case InstrName::HALT :{
                end_flag=1;
                break;
            }
            case InstrName::LOAD :{
                func_load(stack_td,mem);
                break;
            }
            case InstrName::STORE :{
                func_store(stack_td,mem);
                break;
            }
            case InstrName::POP :{
                stack_td.pop();
                break;
            }
            case InstrName::PUSHI :{
                func_push(stack_td,cur_ins);
                break;
            }
            case InstrName::NOOP : {
                break;
            }
        }
        // print the machine status
        if (simple_mode==1){
            if (end_flag==1) {
                stack_machine(simple_mode,cur_ins,stack_td,quene_td,mem);
                return 0;
            }
        }else {
            stack_machine(simple_mode, cur_ins, stack_td, quene_td, mem);
            if (end_flag == 1) return 0;
        }
    }
    return 0;
}