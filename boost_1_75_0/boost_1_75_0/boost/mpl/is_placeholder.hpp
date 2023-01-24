
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
tHQwnPrRJ4xWEGGMZtKJZG7r5OAUsnxZm1/h2xsKe5dflfDC+SNDzudnRv++yqFEa8AzYefe7eNETZ+9yOrvZc9IzL9QQx+v/lBH7YvtS+WLvoTqjOF7LPWKqs+6z9siUtvJimUa/YykqyV8CU0c5QwDiuPVQicdQOSA2RVM6IDyIs3+O/ZfZKH+vlRprN/R37M9LCtGaRbiHmGiShNho3Thgeb8jMdOFF7wrjh+x3tPkPubJmpF8GHwXDYMb+cwRDIPjHItsqWwJf67zHh+PJ6TeZCkog4AyxzTHIVEWrdVhZEBy3z+UcCKdvi3jOBoUCA3hebAr3H++pAwkLjgF5XMIl+OZBoRfhFXTL3ocSM+m3Ks6oc2ei3mTqxH4UxVgkERYkHgROaIzO2XNBphTv+bcE/7XTmow0BcYtzKeovLIBZfS5aktXmL/3hmXv04InUhyXEwlSnEl89OAzpIQq1MTavFPFG6vukSb/MrKUl9cGejyIqPrHVcRsxWAyrlpJkfs1yiPdiii1Pm0Tt5XxDcF5VFtfhY3KPZndCfMV32gmM36/1JPZ4re9QotC5S0Grl26YyEYfuaY/VifqaZqYmWMKd3UUsK0mEbuxNzLIFHqbq0TYlVsoFf7VAGH0ssxJfPfGtkbgLlm4GWn1TZdMRQwSdIKAxXr9HuHQ32WbUQ8vUjc9liCT60D8PpDM486Csq0o4OLcbvVSa
*/