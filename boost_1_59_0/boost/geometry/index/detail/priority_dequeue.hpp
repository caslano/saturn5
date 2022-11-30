// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_PRIORITY_DEQUEUE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_PRIORITY_DEQUEUE_HPP

#include <vector>

#include <boost/geometry/index/detail/maxmin_heap.hpp>

namespace boost { namespace geometry { namespace index { namespace detail
{

template
<
    typename T,
    typename Container = std::vector<T>,
    typename Compare = std::less<typename Container::value_type>
>
class priority_dequeue
{
public:
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

    priority_dequeue()
        : c(), comp()
    {}

    explicit priority_dequeue(Compare const& compare)
        : c(), comp(compare)
    {}

    priority_dequeue(Compare const& compare, Container const& cont)
        : c(cont), comp(compare)
    {
        make_maxmin_heap(c.begin(), c.end(), comp);
    }

    priority_dequeue(Compare const& compare, Container&& cont)
        : c(std::move(cont)), comp(compare)
    {
        make_maxmin_heap(c.begin(), c.end(), comp);
    }

    template <typename It>
    priority_dequeue(It first, It last)
        : c(first, last), comp()
    {
        make_maxmin_heap(c.begin(), c.end(), comp);
    }

    template <typename It>
    priority_dequeue(It first, It last, Compare const& compare)
        : c(first, last), comp(compare)
    {
        make_maxmin_heap(c.begin(), c.end(), comp);
    }

    template <typename It>
    priority_dequeue(It first, It last, Compare const& compare, Container const& cont)
        : c(cont), comp(compare)
    {
        c.insert(first, last);
        make_maxmin_heap(c.begin(), c.end(), comp);
    }

    template <typename It>
    priority_dequeue(It first, It last, Compare const& compare, Container&& cont)
        : c(std::move(cont)), comp(compare)
    {
        c.insert(first, last);
        make_maxmin_heap(c.begin(), c.end(), comp);
    }

    const_reference top() const
    {
        return *c.begin();
    }

    const_reference bottom() const
    {
        return bottom_maxmin_heap(c.begin(), c.end(), comp);
    }

    void push(const value_type& value)
    {
        c.push_back(value);
        push_maxmin_heap(c.begin(), c.end(), comp);
    }

    void push(value_type&& value)
    {
        c.push_back(std::move(value));
        push_maxmin_heap(c.begin(), c.end(), comp);
    }

    template <typename ...Args>
    void emplace(Args&& ...args)
    {
        c.emplace_back(std::forward<Args>(args)...);
        push_maxmin_heap(c.begin(), c.end(), comp);
    }

    void pop_top()
    {
        pop_top_maxmin_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }

    void pop_bottom()
    {
        pop_bottom_maxmin_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }

    bool empty() const
    {
        return c.empty();
    }

    size_t size() const
    {
        return c.size();
    }

    void swap(priority_dequeue& other)
    {
        using std::swap;
        std::swap(c, other.c);
        std::swap(comp, other.comp);
    }

protected:
    Container c;
    Compare comp;
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_PRIORITY_DEQUEUE_HPP

/* priority_dequeue.hpp
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
*/