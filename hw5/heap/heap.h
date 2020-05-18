#include <vector>
#include <utility>
#include <stdexcept>
//#include <iostream>

template <typename T>
class MinHeap {
public:
    MinHeap(int d_in);
    ~MinHeap();

    int add (T item, int priority_in);
    const T & peek () const;
    void remove ();
    void update (int nth, int priority_in);
    bool isEmpty ();

    //void iterate();

private:
    // d-ary
    int d;
    // vector representing heap structure
    // index => index in heap
    // value => first -> element, second -> nth element
    std::vector<std::pair<T, int>> heap;
    // vector with priorities
    // index => index of heap
    // value => priority of element at heap index
    std::vector<int> priority;
    // vector representing map
    // index => nth element
    // value => index of element in heap
    std::vector<int> map;

    void bubbleUp(int pos);
    void trickleDown(int pos);
    void swap(int pos1, int pos2);
};

/*template <typename T>
void MinHeap<T>::iterate() {
    for (int i=0; i < (int)heap.size(); ++i) {
        std::cout << heap[i].first.getWord() << " " << heap[i].second << std::endl;
    }
}*/

template <typename T>
void MinHeap<T>::swap(int pos1, int pos2) {
    // when location switches, priorities at location switches
    std::pair<T, int> tempheap = heap[pos1];
    heap[pos1] = heap[pos2];
    heap[pos2] = tempheap;

    int tempprior = priority[pos1];
    priority[pos1] = priority[pos2];
    priority[pos2] = tempprior;

    // update map
    int tempmap = map[heap[pos1].second];
    map[heap[pos1].second] = map[heap[pos2].second];
    map[heap[pos2].second] = tempmap;
}

template <typename T>
void MinHeap<T>::bubbleUp(int pos) {
    int parent = (pos-1)/d;
    if (pos > 0) {
        bool shouldSwap = ((priority[pos] == priority[parent]) && (heap[pos].first < heap[parent].first));
        if (priority[pos] < priority[parent] || shouldSwap) {
            this->swap(pos, parent);
            bubbleUp(parent);
        }
    }
}

template <typename T>
void MinHeap<T>::trickleDown(int pos) {
    int child = d*pos + 1;
    int minpos;
    // make sure it exists
    if (child < (int)heap.size()) {
        minpos = child;
    }
    else {
        return;
    }
    // make sure children exist
    // then compare to find child w smallest priority
    for (int i=1; i < d; ++i) {
        if (child+i < (int)heap.size()) {
            if (priority[child+i] < priority[minpos]) {
                minpos = child+i;
            }
        }
        else {
            break;
        }
    }
    // compare priorities to determine swap
    bool shouldSwap = ((priority[pos] == priority[minpos]) && (heap[pos].first > heap[minpos].first));
    if (priority[pos] > priority[minpos] || shouldSwap) {
        this->swap(pos, minpos);
        trickleDown(minpos);
    }
}

template <typename T>
MinHeap<T>::MinHeap(int d_in) {
    if (d_in >= 2) {
        this->d = d_in;
    }
    else {
        throw std::runtime_error("Expected d >= 2");
    }
}

template <typename T>
MinHeap<T>::~MinHeap() {

}

template <typename T>
int MinHeap<T>::add(T item, int priority_in) {
    // add to the vector
    this->priority.push_back(priority_in);
    heap.push_back(std::make_pair(item, this->map.size()));
    // added item at the map.size()-1 index in map
    // has value of heap.size()-1 => last index in heap
    map.push_back((int)heap.size()-1);

    // bubble up
    // always the last element when adding
    bubbleUp((int)heap.size()-1);

    // number of adds prior to the current call
    return (int)map.size() - 1;
}

template <typename T>
const T& MinHeap<T>::peek() const {
    if (heap.size() == 0) {
        throw std::runtime_error("Heap empty!");
    }
    return heap[0].first;
}

template <typename T>
void MinHeap<T>::remove() {
    if (heap.size() > 0) {
        this->swap(0, (int)heap.size()-1);
        // remove
        map[heap[heap.size()-1].second] = -1;
        heap.pop_back();
        priority.pop_back();

        // trickle down
        trickleDown(0);
    }
}

template <typename T>
void MinHeap<T>::update (int nth, int priority_in) {
    if (map[nth] == -1) {
        return;
    }
    int pos = map[nth];
    // check priority at pos
    if (this->priority[pos] < priority_in) {
        this->priority[pos] = priority_in;
        trickleDown(pos);
    }
    else {
        this->priority[pos] = priority_in;
        bubbleUp(pos);
    }
}

template <typename T>
bool MinHeap<T>::isEmpty() {
    if ((int)heap.size() == 0) {
        return true;
    }
    else {
        return false;
    }
}