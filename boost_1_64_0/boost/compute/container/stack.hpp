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
R+KR6hxOvJlWeLfwgQgsJhBO+k21OyPVPXQCw03YjmpJivQnE7mzImib6/eWg54O/Tme+YVeowqJTiqb82TXuPuv0pW1q3/50uLNFPFnZWKgnEJYAnzfKCockH7t27/ArpI2MPX0uIyxFmm0Q+w4fe9s5lsZoc7fut/srYFQOG5FA2d8fHp4vztOMnDR2g+zZd3urhDXiWcH9kqVUirfF5I/1fepBjRGc/qEBIiJxXcs1RY4+as7wbjfY1V5yWP/l9xZqBY12LhvXO3yVLSeuf7/YxCa+zTPkrwKRF3T4JbNC5fdZmctv02jQfJuov/kyujBkr06RjQx3vB5ff2rCvNXcQti652PWyyP7ZBUVP6+8yuLnIwDXLnZzim3DarToTz015ihM+sdIK0zZDLQnTfaZiepuaQZyaSOBMynctTr9/ALjYA4IbQBXCEooutImxHdScCnSdt4f1jyQBAa6TJHaLHsI/xJNZQ5msw+N5gneTiur6cNsau9e0yiRqieRNtzKQpkX2kBzADWrZQBz0AWkA78a5/+tx53T6ZSu2o8V8XvMvWjWUZ+2Q==
*/