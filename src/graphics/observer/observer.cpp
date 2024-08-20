#include "observer.h"

namespace acGraphics{

bool Publisher::_debug = false;
int Publisher::_static_number = 0;
bool Subscriber::_debug = false;
int Subscriber::_static_number = 0;

//removes item at index i from a vector 
template <class T>
void remove(std::vector<T>& v, int idx) {
    v.erase(v.begin() + idx);
    if (v.size() == 1) {
        v.pop_back();
    }
}

//===========================================
//	PUBLISHER
//===========================================
    Publisher::Publisher(){
        _id = _static_number++;
    }

    Publisher::~Publisher(){
    Node<Subscriber>* here;
        while (_head != nullptr){
            detach(_head->_data);
        }
    }

    //added new subscribers 
    void Publisher::attach(Subscriber *subscriber) {
        ++_total_sub;
        if (_debug) {
            subscriber->attach_msg();
        }
        Node<Subscriber>* new_n = new Node<Subscriber>(subscriber, _head);
        _head = new_n;
        subscriber->add_pub(*this);
    }
  
    //remove subscriber
    void Publisher::detach(Subscriber *subscriber) {
        if (_head == nullptr) {
            return;
        }

        if(_head->_data == subscriber) {
            Node<Subscriber>* here = _head;
            if (_debug) {
                subscriber->detach_msg();
            }
            --_total_sub;
            _head = _head->_next;
            delete here;
            return;
        }

        Node<Subscriber>* last = _head, 
        *current = _head->_next;

        while (current != nullptr) { 
            if ( current->_data == subscriber ){
                if (_debug)
                    subscriber->detach_msg();
                --_total_sub;
                last->_next = current->_next;
                delete current;
                return;
            }
            last = current;
            current = last->_next;
        }
  }
  
    void Publisher::print_sub() {
        std::cout << "There are " << _total_sub << " subscribers in the list\n";
    }

    //return total_subs 
    int Publisher::count_sub() {
        return _total_sub;
    }

    int Publisher::get_id() {
        return _id;
    }

//===========================================
//	SUBSCRIBER
//===========================================
    Subscriber::Subscriber(){
        _id = _static_number++;
    }
  
    Subscriber::~Subscriber(){}
  
  // Action happens : 
  // virtual void onNotify() {assert(false);};
 
    void Subscriber::detach_msg(){
        std::cout << "Subscriber " << _id << " is Detaching from Publisher\n";
    }

    void Subscriber::attach_msg(){
        std::cout << "Subscriber " << _id << " is Attaching to Publisher\n";
    }

    void Subscriber::add_pub(Publisher& pub){
        _subscribed.push_back(&pub);
    }

    void Subscriber::remove_pub(int i) {
        if (i < 0) {
            std::cout << "No such Publisher subscribed to\n";
        } else {
            _subscribed[i]->detach(this);
            remove(_subscribed, i);
        }
    }

    int Subscriber::find_pub(int _id) {
        for (int i=0; i<_subscribed.size()-1; i++) {
            if (_subscribed[i]->get_id() == _id) {
                return i;
            }
        }
        return -1;
    }

    int Subscriber::count_subscriptions() {
        return _subscribed.size();
    }

};