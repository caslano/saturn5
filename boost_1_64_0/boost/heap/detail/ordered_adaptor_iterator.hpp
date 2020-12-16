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
#ifdef BOOST_NO_CXX11_ALLOCATOR
                        std::vector<size_t, typename Alloc::template rebind<size_t>::other >,
#else
                        std::vector<size_t, typename std::allocator_traits<Alloc>::template rebind_alloc<size_t> >,
#endif
                        compare_by_heap_value
                       > unvisited_nodes;
};


} /* namespace detail */
} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_DETAIL_ORDERED_ADAPTOR_ITERATOR_HPP */

/* ordered_adaptor_iterator.hpp
n9k9fH40fEH38EOi4bO7hx8ZDZ/bPfykaPjSzuAxPpNd6Xx1TUA/qU0WU1ThjCQJDEECheZO7rCN8a/cof20NsW2v3NF++uJ1z7PEPEz48VXifg58eLLRLwzXvtu6UBPuoDPiIcvVcSnxYt3iPjMePH5Ir4gXvwQEZ8dL36kiM+NFz9JxJfGxmsNXYw/1BWeOOYG8j45XmahA9J9sE84RbnSigl7kTIBYxO2KbAoE+1kPUEXx2a71JfPkQO1Yd6L5CjtbjFKy1miuwzFLV588716sUvzcFXpBoIUlzr/Gm6XWy1qv2oRpeL45hnexYyMB3wS3zs18k51QuitlYO+t68RIw4rWfq41EEXw+ShTkQWyrT3c9o0LS3utg2c1VzCM61AtYWM0yrU2htE/pOpo81wyxnZie7mZB7nnTSZ4zUUF9Lc8Vu+n4v1k5t7xaIkZBmbjjH+oBMT9ej3X1wb+37W5bHvz3Z4914T896Yzvffr+Br//O1m4xLleaUrdjWpjhM49/Df6iGU9mego1w26rX6H2+YxJUqQCC7OX/KsF2dYgCcaGdPxT27woPfH7gtpQWWz2tAE53l3swipqgPr7wcHjMDMeMRX1t19LCDO6ev3Y1JSOTl5dt61vMobcgjtqsRYn+LyfUOnL2KM2hA+acHbbfbPW3Z9gm7szZjSPq+M07uCipdnrevsXToPAzXPTPrZ5MhdhpWx9KDh1IZvcZTaCwDPOrCjcRYPSGAzg05X/VgEiHOmghNX55HyxKrWU/0nmhJX3FzjvdEEghFW4cjWpazpvuO8K29fuSlVDoneQsLN3SJV2nbh2Dnf9FJ9buADPsefMdqTEIEJb1fCNxUACC4nV5B2vvAp9nmt6gvXNla0ooUOXIrEmmzdCEnB05W/JCi4bVmvP2Lcn07Oe1CqogD9PTk0LJty6KOBbnfIB6Tk0feW8lB3nekUkr1NyVwmaA78wfAC4ErVnE1WSwwmFqMYXwm1pRSfYo6l8xrHfyIaay6K86l01eM/joMjCT4zoDXNXOs/WHiiyaXmtGNS+jyzgVMV9PU7bTf9uGZu0wo5O+yBM/c+gSTvUaPm6T4d9uhDTy5kMlWmqT8gC0aAvxjeDw9ajTBUWVFTote5fRNetMDZ/otk3eiRKkew7LIgMqu0L1zUOx+RJRu8aob7ca/9s+jXXs/7ku2j5lqbKKDyvjcWRFpQ3e1N3kz68UNTjfTDyyF9gpYCYeMujBQ6f88EKntucr83mATd2jB6zMJiebpA54n4t3O96d7A8EikZKg/cyIEGuN/PpQuUJzhzNRh2q21KuG7B/AuhIMmHB+xAFeVPVa01ci8dc0/OhUHJOSEGIqSWAgFCo13C60BFfU4uCUoRCfXJe59fnA2hkQjv6Ij4T6IcErWlIjLd0BV/C1CvnS358mRKFiAdBazKQZCMVI0lFJkhJeX4CFIhO4gy5KA7TS0iHl1SGRAAlCwWtZ4ps+Midaad2xD2TE4IX+JoQQVke5JcXKdluBm6hnF4PICd8y4JWExI6kJCJc+DrRCFASC5SyxwCYLqpBTgoE2ZNLvATzZI0QMzhoAgFCJprQhRzK4CEFMgcywUm/MwkjnFUKTGE2aTz4iAeqqgJD1ozowQApB6UhkljHiNgvgkRGl9GiNIBHb4LgGNp0HoKSyFoPZ0o+SRoHc/M8M935BtJyLb6JKwmkb/MgFCZoPgJCM0JQHMCUMJgaX7e1trvB2c4SvN2LjpZ+dvvqfPOalOs2UHMvkq/ZocArXkEsDmB0PgcM7N2ZbUFodX2AnIykACPA0fgYKAULwVtCEiSAW3+g8aa14LgBLkM2VLGJ/zXihP+mvmSpY4=
*/