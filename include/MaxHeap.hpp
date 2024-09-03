#ifndef MAX_HEAP_
#define MAX_HEAP_

#include <stdexcept> // std::runtime_error

template <typename T>
class maxheap {
private:
    T *heap;
    int capacity;
    int tamanho;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    maxheap(int capacity);
    ~maxheap();

    T top();
    int getSize() const { return tamanho; }
    bool isEmpty() const { return tamanho == 0; }
    void enqueue(const T &obj);
    T dequeue();
    void clear();
};



template <typename T>
maxheap<T>::maxheap(int capacity) : capacity(capacity), size(0) {
    heap = new T[capacity];
}

template <typename T>
maxheap<T>::~maxheap() {
    delete[] heap;
}

template <typename T>
void maxheap<T>::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}



template <typename T>
void maxheap<T>::enqueue(const T &obj) {
    if (size >= capacity) {
        throw std::runtime_error("Error: Heap is full.");
    }

    heap[size++] = obj;
    heapifyUp(size - 1);
}

template <typename T>
T maxheap<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Error: Heap is empty.");
    }

    T max = heap[0];
    heap[0] = heap[--size];
    heapifyDown(0);

    return max;
}
template <typename T>
void maxheap<T>::heapifyDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            index = largest;
        } else {
            break;
        }
    }
}
template <typename T>
void maxheap<T>::clear() {
    size = 0;
}

template <typename T>
T maxheap<T>::top() {
    return heap[0];
}

#endif 
