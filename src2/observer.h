#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const std::string& eventName) = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

protected:
    void notify(const std::string& eventName) {
        for (Observer* obs : observers) {
            if (obs) obs->onNotify(eventName);
        }
    }
};

#endif // OBSERVER_H