
#ifndef BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/vector/aux_/vector0.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct clear_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct clear_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
VpsW+XNizjLX4dT6g2noymcvgFDrl3MYi/2wXtfF+lbJQMCK2qBFUft5WZohS+amgB/4z/0yjmdp2BUl0ko3OWn0pq0Xasefc0iDgZ/Rw9mIzcY8iKzhw4BDTGm83fVpHuZNvwcQayk6/q3djU6s6raS/CJ2rQtuQGD4//KDmmoEKAKpbA2PUh84T/lFikQJ5hp9RRYwD4r3TLDYZNJuW0cpXZFHuEvVpXz0p8cW25ArdGO7qhqELZT0WYtECihcg8XUmnT5CcbaLCeAvUuJrthqqGza28vQW/V/1UOY9NpPL65oKkwDKViFGHlkSWiOlRQvh5qQEqhxhrOuiXy7HywyXF4/pG9jGAyUgzyQsu1w6gWa5JwTTKUqiLDycMfEYDzLWRjsh32qnTL/WJHbxHuHkSmVak1A5lJ0kOKKn/qHhFkoLcvj5CgirCNAJgy2kHTMz0z4be7romcZX+lvaP/2lPWTNXTDpFZlm1uPsckz9bXKV+twl624a5Hxa/AmQwa3/S0RzVu2dLLC3zuJjNgh2mtjWv/gYc9CD1QC0aM8DConLz2yFnea5Q==
*/