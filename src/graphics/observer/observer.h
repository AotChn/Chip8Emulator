#pragma once

#include <iostream>
#include <assert.h>
#include <vector>

namespace acGraphics{
template<class T>
struct Node
{
  Node(T* data, Node* next): _data(data), _next(next){}
  T* _data;
  Node* _next;
};

class Publisher;
class Subscriber;

class Publisher {
public:
    Publisher();

    virtual ~Publisher();

    //added new subscribers 
    virtual void attach(Subscriber *subscriber);
    //remove subscriber
    virtual void detach(Subscriber *subscriber);
  
  // Action happens : 
  // virtual void Notify() = 0;

/* ========================================================================= *
 * DEBUG 
 * ========================================================================= */

    //prints the number of subscribers
    void print_sub();
    //return total amount of subscribers
    int count_sub();
    //returns the id of this publisher
    int get_id();

protected:
    static bool _debug;
    static int _static_number;
    Node<Subscriber>* _head = nullptr;
    int _total_sub = 0;
    int _id;
  
};

class Subscriber{
public:

    Subscriber();
  
    virtual ~Subscriber();
  
  // Action happens : 
  // virtual void onNotify() {assert(false);};
 
    //debug detach message
    virtual void detach_msg();
    //debug attach message
    virtual void attach_msg();

    //adds publisher to list of subscriptions
    void add_pub(Publisher& pub);
    //removes subscription to publisher stored at index i
    void remove_pub(int i);
    //finds index pub is stored
    int find_pub(int _id);
    //counts the amount of subscriptions 
    int count_subscriptions();

protected:
    int _id;
    static int _static_number;
    static bool _debug;
    std::vector<Publisher*> _subscribed;
};

};