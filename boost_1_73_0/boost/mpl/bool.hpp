
#ifndef BOOST_MPL_BOOL_HPP_INCLUDED
#define BOOST_MPL_BOOL_HPP_INCLUDED

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

#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_
{
    BOOST_STATIC_CONSTANT(bool, value = C_);
    typedef integral_c_tag tag;
    typedef bool_ type;
    typedef bool value_type;
    BOOST_CONSTEXPR operator bool() const { return this->value; }
};

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< bool C_ >
bool const bool_<C_>::value;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // BOOST_MPL_BOOL_HPP_INCLUDED

/* bool.hpp
cSca8COMx8/QiGcxCX/DZPw3TsCSrDcFy+AkSddWQqTOuf/WCoR1tkopybcZkm8zMQBnYUt8VtI1FxNwHi7DBbgOX8DtmIq7cJHk12LMxiV4Bl+R9C7D0qRjBVbAlVgT07AOrlbTLe+pEcdFujdJfm6W/EzHZvgGPo5vYU98G+fhdvwE/4Wf4/t4DHdhDn6ItZX7ShyBn6IOP8Mk/Bwn4X6chgfweTyIqZgp6ebeXd5hY/9L
*/