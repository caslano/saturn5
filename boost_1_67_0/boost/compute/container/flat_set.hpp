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