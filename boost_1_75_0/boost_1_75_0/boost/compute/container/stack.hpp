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
CdfP7NZQPZmQaP/FOnp8YuUVthr/kuHAS5ZNTMBTgig8lK8ucMmqLZ/Wk8nnQuqJOVc9/4qqxy7thu8qCslYbMn0o7U436L4Ld5itBdbc+uWjrJIAWm7KLzbiIUUDJc1HE3EQ6xeS0qBNAk4uK9FuZ3aMjEDMfUqN8bzdZ0ribIgEyFFJdVBuXpIFFHRDLIdO3C1isOBCo14dS2uEc+yji8obWVbJpjiYpj86o9s9PZqxqNkPH+nab5vgfRDQWbQJi1kJucXyBvMcpyIb8ksiOLwFb/gAQyhIPfH8pEF3v5XER5y+hB1KRyyFJRajou5dfOusWPMuyb5y8HwNMsBT+HODi+S6MU+ectg1f41GO1fg7GKy8n+NRg7iyyqArOj1scadMEsIDXj/q8GaWfNNmGmDnnXoEibl3Y+dw5zh36BOao+cXn0GcwaDPaJ8cU2m8hNuIuOUVDeBVDjgpg/rC9trl0Uiwdc/ytUG+lCEapP08HcpLj1Ojp2Vog/xfgj4k9egedmxfzQGrLTojUpntaDQUr0jGmVUSYzl/ak1/+BaxejF/5giDCaIOVxR1ispIVXi257eqoC2sK/aD3XCDNqVS2CL79ppBUSzJyjnwc6Gt1n9C4zCekDz1NIkg5hhWCg/YiDPIC3HlM50pq3A+cLRGQ+kSbp3iogDYaExy0MYGI9slgOYOhaj3BRxgZ5rIEtmRdeGk7N/E6M
*/