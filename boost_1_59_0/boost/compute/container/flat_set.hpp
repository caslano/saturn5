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
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
*/