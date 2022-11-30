// boost heap: ordered iterator helper classes for container adaptors
//
// Copyright (C) 2011 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_DETAIL_ORDERED_ADAPTOR_ITERATOR_HPP
#define BOOST_HEAP_DETAIL_ORDERED_ADAPTOR_ITERATOR_HPP

#include <cassert>
#include <limits>

#include <boost/assert.hpp>
#include <boost/heap/detail/tree_iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/concept_check.hpp>

namespace boost  {
namespace heap   {
namespace detail {

/* ordered iterator helper classes for container adaptors
 *
 * Requirements for Dispatcher:
 *
 * * static size_type max_index(const ContainerType * heap); // return maximum index
 * * static bool is_leaf(const ContainerType * heap, size_type index); // return if index denotes a leaf
 * * static std::pair<size_type, size_type> get_child_nodes(const ContainerType * heap, size_type index); // get index range of child nodes
 * * static internal_type const & get_internal_value(const ContainerType * heap, size_type index); // get internal value at index
 * * static value_type const & get_value(internal_type const & arg) const; // get value_type from internal_type
 *
 * */
template <typename ValueType,
          typename InternalType,
          typename ContainerType,
          typename Alloc,
          typename ValueCompare,
          typename Dispatcher
         >
class ordered_adaptor_iterator:
    public boost::iterator_facade<ordered_adaptor_iterator<ValueType,
                                                           InternalType,
                                                           ContainerType,
                                                           Alloc,
                                                           ValueCompare,
                                                           Dispatcher>,
                                  ValueType,
                                  boost::forward_traversal_tag
                                 >,
    Dispatcher
{
    friend class boost::iterator_core_access;

    struct compare_by_heap_value:
        ValueCompare
    {
        const ContainerType * container;

        compare_by_heap_value (const ContainerType * container, ValueCompare const & cmp):
            ValueCompare(cmp), container(container)
        {}

        bool operator()(size_t lhs, size_t rhs)
        {
            BOOST_ASSERT(lhs <= Dispatcher::max_index(container));
            BOOST_ASSERT(rhs <= Dispatcher::max_index(container));
            return ValueCompare::operator()(Dispatcher::get_internal_value(container, lhs),
                                            Dispatcher::get_internal_value(container, rhs));
        }
    };

    const ContainerType * container;
    size_t current_index; // current index: special value -1 denotes `end' iterator

public:
    ordered_adaptor_iterator(void):
        container(NULL), current_index((std::numeric_limits<size_t>::max)()),
        unvisited_nodes(compare_by_heap_value(NULL, ValueCompare()))
    {}

    ordered_adaptor_iterator(const ContainerType * container, ValueCompare const & cmp):
        container(container), current_index(container->size()),
        unvisited_nodes(compare_by_heap_value(container, ValueCompare()))
    {}

    ordered_adaptor_iterator(size_t initial_index, const ContainerType * container, ValueCompare const & cmp):
        container(container), current_index(initial_index),
        unvisited_nodes(compare_by_heap_value(container, cmp))
    {
        discover_nodes(initial_index);
    }

private:
    bool equal (ordered_adaptor_iterator const & rhs) const
    {
        if (current_index != rhs.current_index)
            return false;

        if (container != rhs.container) // less likely than first check
            return false;

        return true;
    }

    void increment(void)
    {
        if (unvisited_nodes.empty())
            current_index = Dispatcher::max_index(container) + 1;
        else {
            current_index = unvisited_nodes.top();
            unvisited_nodes.pop();
            discover_nodes(current_index);
        }
    }

    ValueType const & dereference() const
    {
        BOOST_ASSERT(current_index <= Dispatcher::max_index(container));
        return Dispatcher::get_value(Dispatcher::get_internal_value(container, current_index));
    }

    void discover_nodes(size_t index)
    {
        if (Dispatcher::is_leaf(container, index))
            return;

        std::pair<size_t, size_t> child_range = Dispatcher::get_child_nodes(container, index);

        for (size_t i = child_range.first; i <= child_range.second; ++i)
            unvisited_nodes.push(i);
    }

    std::priority_queue<size_t,
                        std::vector<size_t, typename boost::allocator_rebind<Alloc, size_t>::type>,
                        compare_by_heap_value
                       > unvisited_nodes;
};


} /* namespace detail */
} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_DETAIL_ORDERED_ADAPTOR_ITERATOR_HPP */

/* ordered_adaptor_iterator.hpp
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
*/