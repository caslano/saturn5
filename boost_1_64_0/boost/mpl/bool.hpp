
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
U5EOug8xkA2pG/syKhxZTNIWwDyVR4NagWOMK6EddnvEftakhie8GQP824V9B7NefcZu5IOpGDMbmrq9i5Os1t1ZRYaFUqXS3LyIT1BK78LFPxMTYDOzelZYqvqfBGRtRut1AzZPqUTt5KbPlV2NeXynvD7KHL4vvxO8MNfez8MkKrovjEywhqRzuK91caca61j+P1RqyxWIntvB2J/Zbo2q46uEhHYB1QzoxwlAMgEn22p7clEAD5rKoDLhdcopUWVL0grzEaMZBqGmFk4pXsbKdwWEIrSDlRCfyxBrE7mPLo/uuCXpiwH3CVJjXYJtsXmxz6GLKdKgug8LYvAc67Z/fqIvyIirFFCys+cGOIJkMCjILygiqwmlPELpi24oNDpg+B6JXZJwMLQdwLQV8l/FWtZFe9JnuCCU5AiZbq11gB2X1BZ3jQ2+y15loArK13gzHNA8pFSkR/sF7kjJYWC0jrZDczwhlg/2QNh6+mbqXHmC+jVzilUtqC+4iJ54jrJYXaizvHcchqcUfx8eEFaWsIOYYG+z4Xt7gyfMYoKlch2gjdOJPaMZFg==
*/