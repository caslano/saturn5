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
Trp/FS7R4yfm9X4cFmW32hW1mCzvFlN4n9zeTYLp3nVf2gwGm8Ffw5bdj/4AbAcWZpMJJLfZDNvqcuHCad1AeHQ+isD3oDuV/VIY/AdQSwMECgAAAAAALWdKUgTGIN8ZAAAAGQAAACkACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9zdHJuZXF1YWwuM1VUBQABtkgkYC5zbyBtYW4zL2N1cmxfc3RyZXF1YWwuMwpQSwMECgAAAAgALWdKUrY2KwX6AwAAZQgAACgACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF91bmVzY2FwZS4zVVQFAAG2SCRgrVTvb9s2EP2uv+KmYUhSKHJ+dOuyBcXUxF2EOrZh2W0NGDAo6WSxoEmBpOxkyB+/oyTP8Tqs+VAZtmSK997d47sLFz68+m6XFzo4+Oa1bL5Luui+Cxpr9QUz+98By+UTtB8KXND9BVQ92Ec9LU/gRVFPcNxELTuua/e8XL6AbuGSdD89F7xYukdaaSO7+BtVPWq+Ki0c35zA+dXVr3AKF2cXZwHcMslRQGJRpqhXAVznzcofJXt4CA2+DQAtMBEeAE5LbsCowm6ZRqBnwTOUBnNgBnI0meYp/eESbIlQcIFwMxrP4+Gf
*/