#ifndef STATE_HISTORY_H
#define STATE_HISTORY_H

#include <vector>
#include <functional>

template<typename T>
class StateHistory {
public:
    StateHistory(size_t maxSize = 20) : maxSize(maxSize) {}
    
    void push(const T& state) {
        if (history.size() >= maxSize) {
            history.erase(history.begin());
        }
        history.push_back(state);
    }
    
    T pop() {
        if (!history.empty()) {
            T state = history.back();
            history.pop_back();
            return state;
        }
        return T();
    }
    
    void clear() {
        history.clear();
    }
    
    bool isEmpty() const {
        return history.empty();
    }
    
    size_t size() const {
        return history.size();
    }
    
    void setMaxSize(size_t size) {
        maxSize = size;
        if (history.size() > maxSize) {
            history.erase(history.begin(), history.begin() + (history.size() - maxSize));
        }
    }
    
private:
    std::vector<T> history;
    size_t maxSize;
};

#endif 