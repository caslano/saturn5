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