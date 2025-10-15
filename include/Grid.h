#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

#include <SDL3/SDL.h>


template<class T>
class Grid {
    private:
        int m_rows, m_cols;
        std::vector<std::shared_ptr<T>> m_data;

    public:
        Grid(int rows, int cols);
        ~Grid();
        const std::shared_ptr<T>& operator()(int x, int y) const;
        std::shared_ptr<T>& operator()(int x, int y);
        Grid<T>& operator=(const Grid<T>& obj);
        Grid<T> (const Grid<T> &obj);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& ofo, Grid<U>& obj);
};  

//Destructor
template<class T>
Grid<T>::~Grid() {
    // SDL_Log("Deleting Grid object");

}

//Constructor
template<class T>
Grid<T>::Grid(int rows, int cols)
    : m_rows(rows), m_cols(cols), m_data(rows * cols) {
    // SDL_Log("Creating Grid object");
}

//() operator overload
template<class T>
const std::shared_ptr<T>& Grid<T>::operator()(int x, int y) const {
    assert(x<m_cols and x>= 0 and y<m_rows and y>= 0); 
    return m_data[m_cols * y + x];
};

template<class T>
std::shared_ptr<T>& Grid<T>::operator()(int x, int y) { 
    assert(x<m_cols and x>= 0 and y<m_rows and y>= 0); 
    return m_data[m_cols * y + x];
};

//Copy constructor
template<class T>
Grid<T>::Grid(const Grid<T>& obj):
    m_rows(obj.m_rows), m_cols(obj.m_cols){

    m_data.reserve(m_rows*m_cols);
    for (const auto& val: obj.m_data) {
        if (val)
        {
            m_data.emplace_back(std::make_shared<T>(*val));
        } else {
            m_data.emplace_back(nullptr);
        }
    }

}

//= assignment operator
template<class T>
Grid<T>& Grid<T>::operator=(const Grid<T>& obj){
    if (this == &obj)
    {
        return *this;
    }

    m_cols = obj.m_cols;
    m_rows = obj.m_rows;
    m_data = obj.m_data;

    return *this;

    
}

template<class U>
std::ostream& operator<<(std::ostream& ofo, Grid<U>& obj){
    for (int i = 0; i < obj.m_rows; i++) {
        for (int j = 0; j < obj.m_cols; j++) {

            if (obj(j, i))//Values isnt null
            {
                const U& val = *obj(j, i);
                    if (j != obj.m_rows - 1)
                        ofo << val << ", ";
                    else
                        ofo << val;

            } else {


                const char* val = "NULL";
                    if (j != obj.m_cols - 1)
                        ofo << val << ", ";
                    else
                        ofo << val;
            }
            

        }
        ofo << "\n";
    }
    ofo << std::endl;
    return ofo;
}




#endif