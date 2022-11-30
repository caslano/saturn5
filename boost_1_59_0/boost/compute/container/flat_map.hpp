//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_FLAT_MAP_HPP
#define BOOST_COMPUTE_CONTAINER_FLAT_MAP_HPP

#include <cstddef>
#include <utility>
#include <exception>

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>

#include <boost/compute/exception.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/algorithm/upper_bound.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/get.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/types/pair.hpp>
#include <boost/compute/detail/buffer_value.hpp>

namespace boost {
namespace compute {

template<class Key, class T>
class flat_map
{
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef typename ::boost::compute::vector<std::pair<Key, T> > vector_type;
    typedef typename vector_type::value_type value_type;
    typedef typename vector_type::size_type size_type;
    typedef typename vector_type::difference_type difference_type;
    typedef typename vector_type::reference reference;
    typedef typename vector_type::const_reference const_reference;
    typedef typename vector_type::pointer pointer;
    typedef typename vector_type::const_pointer const_pointer;
    typedef typename vector_type::iterator iterator;
    typedef typename vector_type::const_iterator const_iterator;
    typedef typename vector_type::reverse_iterator reverse_iterator;
    typedef typename vector_type::const_reverse_iterator const_reverse_iterator;

    explicit flat_map(const context &context = system::default_context())
        : m_vector(context)
    {
    }

    flat_map(const flat_map<Key, T> &other)
        : m_vector(other.m_vector)
    {
    }

    flat_map<Key, T>& operator=(const flat_map<Key, T> &other)
    {
        if(this != &other){
            m_vector = other.m_vector;
        }

        return *this;
    }

    ~flat_map()
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
        iterator location = upper_bound(value.first, queue);

        if(location != begin()){
            value_type current_value;
            ::boost::compute::copy_n(location - 1, 1, &current_value, queue);
            if(value.first == current_value.first){
                return std::make_pair(location - 1, false);
            }
        }

        m_vector.insert(location, value);
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

    iterator find(const key_type &value, command_queue &queue)
    {
        ::boost::compute::get<0> get_key;

        return ::boost::compute::find(
                   ::boost::compute::make_transform_iterator(begin(), get_key),
                   ::boost::compute::make_transform_iterator(end(), get_key),
                   value,
                   queue
               ).base();
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
        ::boost::compute::get<0> get_key;

        return ::boost::compute::find(
                   ::boost::compute::make_transform_iterator(begin(), get_key),
                   ::boost::compute::make_transform_iterator(end(), get_key),
                   value,
                   queue
               ).base();
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
        ::boost::compute::get<0> get_key;

        return ::boost::compute::lower_bound(
                   ::boost::compute::make_transform_iterator(begin(), get_key),
                   ::boost::compute::make_transform_iterator(end(), get_key),
                   value,
                   queue
               ).base();
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
        ::boost::compute::get<0> get_key;

        return ::boost::compute::lower_bound(
                   ::boost::compute::make_transform_iterator(begin(), get_key),
                   ::boost::compute::make_transform_iterator(end(), get_key),
                   value,
                   queue
               ).base();
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
        ::boost::compute::get<0> get_key;

        return ::boost::compute::upper_bound(
                   ::boost::compute::make_transform_iterator(begin(), get_key),
                   ::boost::compute::make_transform_iterator(end(), get_key),
                   value,
                   queue
               ).base();
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
        ::boost::compute::get<0> get_key;

        return ::boost::compute::upper_bound(
                   ::boost::compute::make_transform_iterator(begin(), get_key),
                   ::boost::compute::make_transform_iterator(end(), get_key),
                   value,
                   queue
               ).base();
    }

    const_iterator upper_bound(const key_type &value) const
    {
        command_queue queue = m_vector.default_queue();
        const_iterator iter = upper_bound(value, queue);
        queue.finish();
        return iter;
    }

    const mapped_type at(const key_type &key) const
    {
        const_iterator iter = find(key);
        if(iter == end()){
            BOOST_THROW_EXCEPTION(std::out_of_range("key not found"));
        }

        return value_type(*iter).second;
    }

    detail::buffer_value<mapped_type> operator[](const key_type &key)
    {
        iterator iter = find(key);
        if(iter == end()){
            iter = insert(std::make_pair(key, mapped_type())).first;
        }

        size_t index = iter.get_index() * sizeof(value_type) + sizeof(key_type);

        return detail::buffer_value<mapped_type>(m_vector.get_buffer(), index);
    }

private:
    ::boost::compute::vector<std::pair<Key, T> > m_vector;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_FLAT_MAP_HPP

/* flat_map.hpp
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
*/