
#ifndef BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/arg_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T >
struct is_placeholder
    : bool_<false>
{
};

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct is_placeholder< arg<N> >
    : bool_<true>
{
};

#else

namespace aux {

aux::no_tag is_placeholder_helper(...);

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
aux::yes_tag is_placeholder_helper(aux::type_wrapper< arg<N> >*);

} // namespace aux

template< typename T >
struct is_placeholder
{
    static aux::type_wrapper<T>* get();
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(aux::is_placeholder_helper(get())) == sizeof(aux::yes_tag)
        );
    
    typedef bool_<value> type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED

/* is_placeholder.hpp
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
*/