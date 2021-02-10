
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
XIPgtwqNtLBBVDCzjXYzJl4mbESsomktVBqtOnFgUVXwuEoKQpdysAi6hmelXxVshj9zgs+uzq4hNdhLNxhSN1LZmkp54magSig714xQauWM7qBspFLYUcmt0U6XuovYKo8zkEqrsdeDDbyBOdDE3/Gv7LcdntGAlP35I2Bxmq8DVvxKY0gClie/Y6AdBJPxu5fgB2Fy48sfgW8QknNojDalrryX3shPseDv2xD88AffAFBLAwQKAAAACAAtZ0pSkopTt38AAADMAAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE2MTBVVAUAAbZIJGBNj8EKwjAMhu95isLOIyDoKRTEi3efoGwZFDWFplP29qYWV0/hz/fBn1BhLVNQ9kBRlmTjzts75Vk9rBJL5XC7ng/HExB2Rth0GGBwl0dkKaPGmYGmbzBDOb84e5AktsZfpIVDWTP/FxD2pSMJT7unlbrquCqpEWyIcC/B/sAHUEsDBAoAAAAIAC1nSlJbjeNOegAAAMYAAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTYxMVVUBQABtkgkYE2OsQrDMAxEd32FIXPR0lF4add8hEkUMEllsJSU/n3lhtadxL07dEfGalNSjkBZ
*/