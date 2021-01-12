//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_STACK_HPP
#define BOOST_COMPUTE_CONTAINER_STACK_HPP

#include <boost/compute/container/vector.hpp>

namespace boost {
namespace compute {

template<class T>
class stack
{
public:
    typedef vector<T> container_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::value_type value_type;

    stack()
    {
    }

    stack(const stack<T> &other)
        : m_vector(other.m_vector)
    {
    }

    stack<T>& operator=(const stack<T> &other)
    {
        if(this != &other){
            m_vector = other.m_vector;
        }

        return *this;
    }

    ~stack()
    {
    }

    bool empty() const
    {
        return m_vector.empty();
    }

    size_type size() const
    {
        return m_vector.size();
    }

    value_type top() const
    {
        return m_vector.back();
    }

    void push(const T &value)
    {
        m_vector.push_back(value);
    }

    void pop()
    {
        m_vector.pop_back();
    }

private:
    container_type m_vector;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_STACK_HPP

/* stack.hpp
OdmToGMzY84fL+NG7zRCuJV6fhDvEfI8sb/ZTfi2XPRPDb9XYBbUtS9z8DpWC/c7NG5/GSvjG9NM9ZA5TuZcfJmmjBGf3zxlXvbc7T2A/cg1NbR3Gs9VEva3vkfN0+YN2qKGxPNdTzenpe+QaavjzD2jRJfx082V5mPzW+4HzG+9fnOWb4snEPeMjpfC8aaVsWPJE8X/daatjiVbiC63BEZSAldTM9+NzQ9NqvnOmWF+4f3A
*/