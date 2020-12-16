//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_FLAT_SET_HPP
#define BOOST_COMPUTE_CONTAINER_FLAT_SET_HPP

#include <cstddef>
#include <utility>

#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/algorithm/upper_bound.hpp>
#include <boost/compute/container/vector.hpp>

namespace boost {
namespace compute {

template<class T>
class flat_set
{
public:
    typedef T key_type;
    typedef typename vector<T>::value_type value_type;
    typedef typename vector<T>::size_type size_type;
    typedef typename vector<T>::difference_type difference_type;
    typedef typename vector<T>::reference reference;
    typedef typename vector<T>::const_reference const_reference;
    typedef typename vector<T>::pointer pointer;
    typedef typename vector<T>::const_pointer const_pointer;
    typedef typename vector<T>::iterator iterator;
    typedef typename vector<T>::const_iterator const_iterator;
    typedef typename vector<T>::reverse_iterator reverse_iterator;
    typedef typename vector<T>::const_reverse_iterator const_reverse_iterator;

    explicit flat_set(const context &context = system::default_context())
        : m_vector(context)
    {
    }

    flat_set(const flat_set<T> &other)
        : m_vector(other.m_vector)
    {
    }

    flat_set<T>& operator=(const flat_set<T> &other)
    {
        if(this != &other){
            m_vector = other.m_vector;
        }

        return *this;
    }

    ~flat_set()
    {
    }

    iterator begin()
    {
        return m_vector.begin();
    }

    const_iterator begin() const
    {
        return m_vector.begin();
    }

    const_iterator cbegin() const
    {
        return m_vector.cbegin();
    }

    iterator end()
    {
        return m_vector.end();
    }

    const_iterator end() const
    {
        return m_vector.end();
    }

    const_iterator cend() const
    {
        return m_vector.cend();
    }

    reverse_iterator rbegin()
    {
        return m_vector.rbegin();
    }

    const_reverse_iterator rbegin() const
    {
        return m_vector.rbegin();
    }

    const_reverse_iterator crbegin() const
    {
        return m_vector.crbegin();
    }

    reverse_iterator rend()
    {
        return m_vector.rend();
    }

    const_reverse_iterator rend() const
    {
        return m_vector.rend();
    }

    const_reverse_iterator crend() const
    {
        return m_vector.crend();
    }

    size_type size() const
    {
        return m_vector.size();
    }

    size_type max_size() const
    {
        return m_vector.max_size();
    }

    bool empty() const
    {
        return m_vector.empty();
    }

    size_type capacity() const
    {
        return m_vector.capacity();
    }

    void reserve(size_type size, command_queue &queue)
    {
        m_vector.reserve(size, queue);
    }

    void reserve(size_type size)
    {
        command_queue queue = m_vector.default_queue();
        reserve(size, queue);
        queue.finish();
    }

    void shrink_to_fit()
    {
        m_vector.shrink_to_fit();
    }

    void clear()
    {
        m_vector.clear();
    }

    std::pair<iterator, bool>
    insert(const value_type &value, command_queue &queue)
    {
        iterator location = upper_bound(value, queue);

        if(location != begin()){
            value_type current_value;
            ::boost::compute::copy_n(location - 1, 1, &current_value, queue);
            if(value == current_value){
                return std::make_pair(location - 1, false);
            }
        }

        m_vector.insert(location, value, queue);
        return std::make_pair(location, true);
    }

    std::pair<iterator, bool> insert(const value_type &value)
    {
        command_queue queue = m_vector.default_queue();
        std::pair<iterator, bool> result = insert(value, queue);
        queue.finish();
        return result;
    }

    iterator erase(const const_iterator &position, command_queue &queue)
    {
        return erase(position, position + 1, queue);
    }

    iterator erase(const const_iterator &position)
    {
        command_queue queue = m_vector.default_queue();
        iterator iter = erase(position, queue);
        queue.finish();
        return iter;
    }

    iterator erase(const const_iterator &first,
                   const const_iterator &last,
                   command_queue &queue)
    {
        return m_vector.erase(first, last, queue);
    }

    iterator erase(const const_iterator &first, const const_iterator &last)
    {
        command_queue queue = m_vector.default_queue();
        iterator iter = erase(first, last, queue);
        queue.finish();
        return iter;
    }

    size_type erase(const key_type &value, command_queue &queue)
    {
        iterator position = find(value, queue);

        if(position == end()){
            return 0;
        }
        else {
            erase(position, queue);
            return 1;
        }
    }

    size_type erase(const key_type &value)
    {
        command_queue queue = m_vector.default_queue();
        size_type result = erase(value, queue);
        queue.finish();
        return result;
    }

    iterator find(const key_type &value, command_queue &queue)
    {
        return ::boost::compute::find(begin(), end(), value, queue);
    }

    iterator find(const key_type &value)
    {
        command_queue queue = m_vector.default_queue();
        iterator iter = find(value, queue);
        queue.finish();
        return iter;
    }

    const_iterator find(const key_type &value, command_queue &queue) const
    {
        return ::boost::compute::find(begin(), end(), value, queue);
    }

    const_iterator find(const key_type &value) const
    {
        command_queue queue = m_vector.default_queue();
        const_iterator iter = find(value, queue);
        queue.finish();
        return iter;
    }

    size_type count(const key_type &value, command_queue &queue) const
    {
        return find(value, queue) != end() ? 1 : 0;
    }

    size_type count(const key_type &value) const
    {
        command_queue queue = m_vector.default_queue();
        size_type result = count(value, queue);
        queue.finish();
        return result;
    }

    iterator lower_bound(const key_type &value, command_queue &queue)
    {
        return ::boost::compute::lower_bound(begin(), end(), value, queue);
    }

    iterator lower_bound(const key_type &value)
    {
        command_queue queue = m_vector.default_queue();
        iterator iter = lower_bound(value, queue);
        queue.finish();
        return iter;
    }

    const_iterator lower_bound(const key_type &value, command_queue &queue) const
    {
        return ::boost::compute::lower_bound(begin(), end(), value, queue);
    }

    const_iterator lower_bound(const key_type &value) const
    {
        command_queue queue = m_vector.default_queue();
        const_iterator iter = lower_bound(value, queue);
        queue.finish();
        return iter;
    }

    iterator upper_bound(const key_type &value, command_queue &queue)
    {
        return ::boost::compute::upper_bound(begin(), end(), value, queue);
    }

    iterator upper_bound(const key_type &value)
    {
        command_queue queue = m_vector.default_queue();
        iterator iter = upper_bound(value, queue);
        queue.finish();
        return iter;
    }

    const_iterator upper_bound(const key_type &value, command_queue &queue) const
    {
        return ::boost::compute::upper_bound(begin(), end(), value, queue);
    }

    const_iterator upper_bound(const key_type &value) const
    {
        command_queue queue = m_vector.default_queue();
        const_iterator iter = upper_bound(value, queue);
        queue.finish();
        return iter;
    }

private:
    vector<T> m_vector;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_FLAT_SET_HPP

/* flat_set.hpp
kS/Rr0OcGsrzGNx90SM5n/1z0fl+pa+rj/0WxFUDP3G8Z/H3ZjP7a6n/uBKP2ZCHUB8OuckOvZD63DC62l8cJ5Hn9bH/2xl77LkYv3cPeV4gOu1O8qmf8MuMWzfPRU9ln2HgbdzHPNbJNOreK7GnHNc8yL4oe/ofmJ+r+NO/CR3jXuLhbuLsGOYLeoHpMeYF/rGYfYkbTxvvTyJf+574aBH+o4t1fRfrLoi4g3y57Tvi4vuY9zbUZbI4jjN24kfsFHUtmzn0/bxjyTgQvy/D31yE3ZzB1+jnLY6MM32pw2XEodPp+8Ofj20h/mikbpFOXFpAXE0eHdHAfEvCfrQTj3xFnMG86nuGeP0T4oO3sBM8d82V8QsgPrPBDwasop+jBn3AxP2i7jHgZTNxfb+S91GnGDP2IRcxDwfxE8HEdYZe+DbPe+W+Rc2l33MjX2fzPKWnuN85nDd55yrGu+BadIrbJlHfwr+RR6dWEseuoY8VvWXvy/gJdCvfZMb5Lvr+viWfWE58je6U9BHj/DZ595X45Tuwd/ze8KXETfjTYlvWRTj5BP0z3YnED+gRPjdh174hX3qaeJ3ncdik8/yHr9ABrkeXuR8/fI66jC/67zT6Hjay//AJG/aron80E5e0oENk0bf6Bvruh+RnzCuvMfS2f3JdTuTD5M0n38F/3GJNXEcchd8NIB44+ST36TbWwQe814S4xPc+5hX1AN+t5D1cR5+NJf6R9eqNvT2JnaGvMIA+najrWD9nqadwPlFfoNe2ox9tY3yoM+T00RfCPEu6mX7lreQ7Q8TtN3I9icxT8sosP+zlP9BFmb+7HyZfeZc8hrgobz7zYzp9d9HEgf+jnlxAX1EKdv0T8syT/JwHccUG+h2way1VxAGX0P/yOPHBS1x3I/og+Ye7H/eFvvPYn8nryD/60DMaiWNa3mO+Lpr4unEp/q2EdePMc2OPE88yPnv/QXz4Ms/TXG7opPhFB35uC/UxdNp49g16E8dnGbov59dSwLwhjrb5Cvs9hu56EzryYvwE8Uef8Txm4kmv2eiXW1jPrBv/GfS5EydExHH/tlsQj05GN0I/cWO93sI8qkO/m42dY9+JTSLzzou4/jl+/jLqQvfQr9SGDk0+Ev8Nn/M6434365Q8su4D1q8L++2f430kQdh56iyrNjPPHPGbxPOV6Ayl7ozHVOJ76t/Nr2LHYuj7XYqO1og9IL7PYH9owF/oBlE8h8ifekoN9/N99q8RN5vd0a0DGTf0lMRQxrWbetli6vXjxGFT2Q/lzf0nnzBFkW8NUzctpO+RPnQ/6rIha3meSgn3GTuQRT/sMLpKDvXAkFfwa5ejz9CP14y9if2Nuv0VxGcZ3NeLrOhzIA9dgD9GJ3AsJ79bQnxBn+8+3kMVUMW6RH/wu5V4bpA+x2HjORj4uwT8cwC6YSh68U3sb5hO/pFPvnKA+Y1fzkGX3OKN/m6HLrSXPKYDfa+UOOhN9nkNoI84YoeJYwJ7OV9v/K6J+/mHLXEL63oP9UI+d+dN+JXjtrzvgPteSdxwhvnM55SSrw1MIX9Zy/49xtXzOLptPXHCdxxvHToi5+n1GbrcFYyLH3WeDuqID/Hzj/Gcrnr6I9LJRzlOwF4T9TX6e19HHyjGPtmxnj8kbjpNff9L6g3r0aWNfjd0Pz/6wQroEyjtoE5PH3gz8VJUK352FfWgEfYttzAvyZfabuc4l6MX/cF1t9Pvcw36z8vMo2biJOpwOeTlUfNYD1/Tp3ZkMn2Z1C+IGw5h1yIuQXebSn9yPHrQPuO5s9RpeB+ft1EPP8T9OEdcOYN+d+rta59Hz2B9tWzBnl5C/Pc29p5+UDN5+kbsSfc=
*/