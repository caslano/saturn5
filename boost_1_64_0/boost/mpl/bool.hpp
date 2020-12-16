
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
ArECuOh4LVWCOy/78zHiasgeWZTbt16s5Q9KBFWJ06iEkhs2xL+sMaGY7306NjdOkQDS6F+KWqnMLyZDnU8377ololkC1sxS/bob+wZO/p0+DTD7EVGsFS5hj0h1AHuKl6KsirtK30ylAX7rXe4gCEXpADlBum8jOo7nKGme1mLTceMIAg4x3/cjPViWUw+if0c9aHrwGB/TNX3xMo+usoU4K20qLdmkxt0h6rLoEVJfair6E9ScTYX2CVLROhkqb682Fam1Mro7FxICyqS1SXJudQzwqbj5NdI7Lu8uyXuPK++FgFojObElYO2VnLNcOYcgZ7XkxBaOtU9yjnblbIece33F/bE86sH5YV7J3EcuL0yCoKuEYiGRqVTGX9wPZbpjlxtK2OoKKsLd895NpsjPVZFeyNxNkTXMloy2lZRb8wQnty+yAEEMjhFMKgutSsF8qSvbOcr4YLLtLrRqJNt0V7Y8DKVu4kVCMSMnWp6eenCoDTHJ2FJHHkD8ss6WYoPWCIIIp+m7mRM/zy5LsGR1/6nRszrgma0bbfkZOqmXn7EVsmWOft75f13sX/Iz/t+kZ9uf0h+ybXPQA3NLXWf0ebildY9e/98hm9PDaMQoZSoMjfsIyOSgSHJ8+2gDOIA4u5x5bzOc+aL8/+8j/CYAP38sfsMZvxxrOePX08HvxCj8fnSvxi/AmwRfzxTbDt8ZuqJ5uEXh15bwA5J0h96TMfj1Ffye0ff/356YfntWxNNv+JVR9EtvJo4Kv+XQf1a6/eNg29EnDOd7eXN6AYWbyVJMfgHNejwo1SycU16uQpUW2iuPh6lL6bnliF7KPG3EDGHxym9ugGLdqrxHhwyxsl/Tesiula6M2LPcgRimKiedmEAQU+VXhweOXEoxAdNLNylIyHnCnufS6eXLA0v2FJ+lHes8ryxOVci0JnWeIqIUhnOQsGW/p3xxJrC09+cBcWRILSy/W31lFr7wIkHJrw6HODgMn5BRrMPXtVjbKSjh66Yolepu9aS04hTgRJ6ThdbGvZ2YydriQwWA3at6UI6w1+hi6e4K5Sp/eLoF7/+XeLqZ+z9p7gLFzFUyehE0pUB1D0LDh5oS8Nqcf7vX8b+OvubX7eReQP7+PFlQQ4GTECq0/8CcQqrGGFXXX2ddgg0jeLRm4ZsaTtnKibNutdv3br828DrT3bPG2I1g0a/tCUvDizwrP7uFTRyPKPRvnGO2nhDqHaAwBa8i5TgE+/3MK014mmuIWmozrLDAnFJS/rbjQrrdCSM5fINGZohhaCDc9Asm2h14RxC364EqSAjRbfIrTAKoApPcY/jK4nX2LDyjxXs2HCaz8rf+0XiQnh67IUlP19wT09MgzaHz8LVp9yUp+B8+ngT+Iz9NBH/k+mbCX5IM/vg4+OLN/eID7usnl8o16wWeokH296kU7lZQwR3UN/igX0plVW04ZFEQsq//ASCw1oYbzEO0NYVbx0N0i/uVqBlgQgAT8lBGfddcJ8H814/FYH5CE60Nye+fwG1jv3Im0RVWqY7/XOZc5IEJg2ZEre/tdY9qc1Cj8F9zwV/M8Ce44WcY+EEDf1yT4f/eBf9Ghv/pUoHfKRo+rzKvmaUvOmwSfSpc8Jcw/PKG4T+xqInwQwp+xAX/DYbfz4GfwyyDaeJZbo5cJL+zRvQZgohEfpdL7CeVhSY5I/uDlQCY/L6RQ3fGnP8Q/j3lAjBp4k9u/n2klzmsvYXFD6jxmzlKnZo4TXBPB9ub5M3wBKvWyWJ1FzL1M5kwzCd1yaRMpWKReBCZ0pxMAci2Sfcf6QlGpqOuq5Djo6kmB+p6TeU4GRV1Ro5tJgdXdJfK0ZmcgzN6k4nqJtU=
*/