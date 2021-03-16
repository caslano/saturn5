
#ifndef BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/set/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : s_iter_get<Set,typename Set::item_>
    {
    };
};

template<>
struct end_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef s_iter< Set,set0<> > type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
BXltu5jlU03eaqA7X9DOJ0/7hPLCQLffJg8cDpt+Cv7wey7TrKYFi///3var3JIXQYqSpc78ZZfDinxnCzuA90faWCM7lmLyGM6OF/Ol/ETZvSl+gTtagJwr+xnI9N0+yF9g9BVFnW8+F3cRG1peasUmJWEl4g2Fhry+UT0WD0bjweR+PRjZ4w0F/WwLkL3Wih6xOzqkR4d2a76kHtGSetyb1HRfNJKMR0O6FvEOhTTWI4gXzEuMXw8Y8kb8e4M=
*/