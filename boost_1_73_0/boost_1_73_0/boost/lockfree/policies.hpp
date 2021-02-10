// boost lockfree
//
// Copyright (C) 2011 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_POLICIES_HPP_INCLUDED
#define BOOST_LOCKFREE_POLICIES_HPP_INCLUDED

#include <boost/parameter/template_keyword.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost {
namespace lockfree {

#ifndef BOOST_DOXYGEN_INVOKED
namespace tag { struct allocator ; }
namespace tag { struct fixed_sized; }
namespace tag { struct capacity; }

#endif

/** Configures a data structure as \b fixed-sized.
 *
 *  The internal nodes are stored inside an array and they are addressed by array indexing. This limits the possible size of the
 *  queue to the number of elements that can be addressed by the index type (usually 2**16-2), but on platforms that lack
 *  double-width compare-and-exchange instructions, this is the best way to achieve lock-freedom.
 *  This implies that a data structure is bounded.
 * */
template <bool IsFixedSized>
struct fixed_sized:
    boost::parameter::template_keyword<tag::fixed_sized, boost::mpl::bool_<IsFixedSized> >
{};

/** Sets the \b capacity of a data structure at compile-time.
 *
 * This implies that a data structure is bounded and fixed-sized.
 * */
template <size_t Size>
struct capacity:
    boost::parameter::template_keyword<tag::capacity, boost::mpl::size_t<Size> >
{};

/** Defines the \b allocator type of a data structure.
 * */
template <class Alloc>
struct allocator:
    boost::parameter::template_keyword<tag::allocator, Alloc>
{};

}
}

#endif /* BOOST_LOCKFREE_POLICIES_HPP_INCLUDED */

/* policies.hpp
JJCIc14pc6w/cRYISi8+JkpBc0PFmKhEIvQSl07h+GRtz6ppbKJ+tGaA7kkNngxRw6F9R/K5FOH7j6efWwAHvTpl4EZgMq57FKFMH7lCULjiVpJQDYopByjwGil70CFxmOr9OGZqDlffWgTTAD/Zu1RMsIyWiUxJvCh+rzk3q22spvTaC3qb8rjyVnzfq2RYeXUGvbS6Ccv8zO7ZTzJ8IlTaphehZ0HHGRjfF+8/epbqs4PHBYVtqmVx0lyEw3ka2hUKhtbyhPJwLVfW8gKtLwHrJ6dsk5KChXNVYBg8Q8xIKDgkOWCDbmfQYOCvggbeSNsUBFDoUR+pHNyIFlRVUi8v5oLSK02zAiOrWEVXZQ4qSq6gIFAVP3brfoo9kQYobGGue5AQKrT4JalaCB+mFsY7OBRo5I26DddVZt51TpnWx6wEouOwlQL521s5cWkfnEAwwKxAG5hGCq1iqlLb2kj2tRqqIrjHGClT7CBsTyzgmX5suGWRqbD2Y6SlbNOK1yKsVZ3hdR9lt5tx5J0gybYivJsT42qds1F8d3LSgdY4mxV3J6ersGvMG1V3t2Yy77rqZr1tLdkJ/RALT2V9V8w4bimtrTswsLRMhP7EHaHO4UqqCMP2VyX+MKfXzlpckXTromYdQDz0deCP
*/