
#ifndef BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/vector/aux_/O1_size.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct size_impl< aux::vector_tag >
    : O1_size_impl< aux::vector_tag >
{
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct size_impl< aux::vector_tag<N> >
    : O1_size_impl< aux::vector_tag<N> >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

/* size.hpp
bBgdXjdO0ebviOuMUw4vpK7rg8GUDM7Q0GtsTNRPtqvvyJfORyBhcQ5EhEl8s2qPbLKWCLTMi3Ad0kNPtM6XV5CpqTXNEmXhyWoCGnhl78E75KADWbfvvAhx+SyawsmOiKnE7ywtm68RzCYItcyU+CQAZbJE4e+UJDQo+fnX6DmnOMnY61t+LUJcQNcJNcwQ21fivSYYeCYw5uVPsoVDXLgO7Ph27ywvZ3f6BU8Xn/NaT7AZi4noEtvEaInSm7A8BV6giSIaPi5YqViTox37J/jIxq+oIM5byS/+z9y+TZ5n5oT1ccSUhBJr18TxML1zSaS0NnKyytKFzk83wOcEs3qixRrXruL5MxJc0uhGcJrnmUJ2+Y7020rXHsigBPUVwPrDZOrn/x2M8d6OgoV6sxY5+pFmJEeAk95dXoUXsKWwsqZoAnxpjxWWAqJj8FMQrtPVhQvnCn3WD79e15oMY8Ker4NvSxuku6/v+wTw2WkUWwQnVvfbjPC43GO838ioaePyBQkrTk8L3I4guCLu8UQHG5Q8QEaxyOb6+CejVupcB+tVGUbqzXnoqA==
*/