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
25k96cql9utTD24sgsOOZkf0+dLSUFcNz9cwbuPlRc9dNcK6k1OslxcPt7OvejpxjfrQ/Mn4u33QarrQx8J90v08xT4thcn2wa1yvdPwiROMw1a4ZnwEv6Db0l9jrqUfi3OVl9A189SP75ef97P3pc6/SaarT4q07zpe3xF/ly8KX4WX+MX8n+nWx4rfN6r3qgsnf+o58ZfcO+WT9+if+ppqzvdef1tnc5g6RKU4cAvc2hsO7y4ffM9+6S4ZM/V/NBjnreqB/1G3zhN/rqAHfStvOWe2fqH+F/E+baLPzfD6Bvt5phivo/Rx5Ltfbng+BX6PFxUPC8ff82fSOba1M+/Wc7+gLsD/Rp4on6ynd/4Ep84wrt3sP0qXKNiNz31GL1+lHiYe5bTYH+dKeWcg3cnfL9pCp5+q7nsVXvmuvPSFOka4D4u4lg9/Zg1X53mH/vFnpP4Zfvk3HWGwePQEXC1ftDmneu0rxjuCvWTYn+knOO1Y432b+ESHahsuH9xLx2wnXp8Nrw7285XWLfQTryfQYfhTcRuc+xHdYga8pA6S9bjxW2N/Lby1pQAvTRLHxIdZkXSnPvZJLhfv1ls33tV7HGp9+KvsdZ1xDPfRX6dumSRO/yjv5Kq/OE9w9j568lfG9yF6UY76zT/3C/Rg/pXCf31/5hXw7jny3mp5aKb3+UM+gOuKj9dHkE+3Gx5tn3S441/G92K4ll6ZabxTGrzXU3j3X+wYL8ke733i2P0a/VTq5BnL5VF5c7R+662d8Qj8M3M0vaoCj5+MHx6RgIcbj3HWl4if9frD6iLUl8axo4HyXyG7pPc0zqcHnmH8NuBZ++X3Huqts40LvTPjVPPTLH+mw7GLrMumr1TQBZv/R9P5AOJV7nHca94NoyiKoqZNbW3W1P6pWVNTU1tNs6LmZkXRrOhS1DQrNmqKLrUVjbJGUVZW3KzZvVbU3CjaNGLNijaNYghzv5vP6d5Pi3Hec57zPL8/39/vOYf6oeMC+uSmc3+Y1/bkw6uII13J+6Ia6BM+a0kfLXp9HHH1e8Q/keQrM4jn0fUKPsKv8X37e7E3K6m7/oP9aVGsy27sbCv9aLwXtvJB7BN98gH4le5c9Cfs4SrsTRv2xjOA+HSTBX6HfUsm4kz6Nha4MJ4/Yk+6qXd1oZuE0r9NH73zdhP3A/+Gvay04HN4H4Yv/nrWA8RJJy3JK7Df1ClC+7HPheiEh/h9dJ8k5kfPMvZDkK+lv824rUWvvA9d3Rb7WkO95Z+cH/H58XuYB/70iReiL1qSJ3+KH6De0YddXNDPekTvXsB+Kxt0SecwdLmXeL6NEde3kQcSJ9ZH8DyJGtYLfmOLFfYE++K/Hr0mgXX+MXXA2zk/7LqjN33GD1KH76EPfZS8OQ67S/58nPvpenYq+iH7gsjn207xeddjB9DhE+PQPamvRQWSr9ZO4XlG5Atz8OeetsRt9Eu6EQdcxnxzZp4Sz9j/wXNPsDeJ9FGZ0q3RBcknvuD7XdxHF/oQ83iexMBU8h9+jrgpKRv7cDV9AnewvvAfY8TDjnHEfYfQxW3JY+lD63sUu0CfcukP+BfsnrmT+419z0NXnVVkvBfclvfI4w9OUV+jjlufwv16hPyf51LXkbeX4l+jHiQ/GkP/pf7qxf6mNmt04Gr0HSP+dCe+GyH/m0c9guvfiB6QeBS9aj3xC/lzsQmdi/g5PpF4b8VUdBj6eqywPxdx305grxzo019NXaoJv/YL8a83/aH3MX+tee4e/tDreeoyvOfYMwi/jz06mES/x7f0M58mn32cPLaYeOUH8tI16HcPEG++Sb5IXS7idtYpz/HKuhF//izrZAh9KYl1bMRrjug=
*/