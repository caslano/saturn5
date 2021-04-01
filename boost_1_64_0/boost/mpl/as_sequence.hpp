
#ifndef BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct as_sequence
    : if_< is_sequence<T>, T, single_view<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,as_sequence,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, as_sequence)

}}

#endif // BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

/* as_sequence.hpp
djEtkH5dr9DY1JmHlZ8U7RfeWhtsU/bxQ/Dg58etN/UWyz48h9gstcv2ECwt+dIoM8WmwMQt1MzfOAJXNCDue1EWWWdmH/1XHKS0PkIv2RTOOee0U0IY8qLOVq0T0kKkjmzqOJhhkPDgD4P2dRnyQ21eQltIBAQtfH0lEGy9YJknYzYFNYUM6sbVetgxa3tTDaS/AJb+OinwI2YL+Z9UmjJGcKK4GE/unVyCnNGl7Ghv1Vu9+UH0557HwvFkbV3F5scsX9srDy15EuguYLYkOfAXZMy8Yj6AKwHjWGBOR+ayy3ao6ZvKKK8KzS56eq8WJ+o5DoxJlBlPhJaLqYlnwQG+Fwwv9SmLQfRl6LUKUqeBEdN5KH9xgrY47tf4rG/AlwqjLYToupwEjLQPF1kawy2bnS33QCSSmfkWpTQAjzVJb6q0s24Zzj/g66kGjYSnbay5Y3z00C8FaPGS1JCOQzv+aG1bsdl3ZuznO5srN7D+zYkrUocucoIFi4qAtxn4t3d2ZuawekwMwgQfRPDzER5svwaJyHtKyu/ht7hBrY77y09Ngzzxz4TYpw==
*/