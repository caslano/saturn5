
#ifndef BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>

#include <boost/mpl/vector/aux_/iterator.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template< typename Dummy = na > struct vector0;

template<> struct vector0<na>
{
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef aux::vector_tag tag;
    typedef vector0         type;
    typedef long_<32768>    lower_bound_;
    typedef lower_bound_    upper_bound_;
    typedef long_<0>        size;

    static aux::type_wrapper<void_> item_(...);
#else
    typedef aux::vector_tag<0> tag;
    typedef vector0 type;
    typedef void_ item0;
    
    typedef v_iter<vector0<>,0> begin;
    typedef v_iter<vector0<>,0> end;
#endif
};

}}

#endif // BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

/* vector0.hpp
QQtNNRQ5sbaECNxqw+8vddj68tzsPMg+y2ZhyV+I+/RiKJuyxBferwE3v5o4JWNGKMkWM8wKnrtgyGtuBh6ITXItPIIlSXEK40Ui295CL5bV/PBNGGGhCGSgbuEUyDQfbPpS3QFKrB3vkcq9jOVxwz5CJTbM3Yh7LXSx0hO/kkEggEh9HWwCv13vfaSiFtBjcdT1OtTPPK0zw/aPVmHWr8vQ4dlQjlSw15X9OTLVo00KWnqF2jkbQeOimJb+jkeHb5+thj7EF6JreIB9tTps1Hn41p/N0yC3cpXcxysH5qaRI/C4kw1Rk2Zzo0rPw32/iLrhqdtrlfV3ApL6BO2zc8n16vdDI8xmL6uiJo10efAXqjEdAGN2dDK+6IDTosx9beOoUOkUwfNQCGA6jn2K4xYxDvZrwIj7hxiUx2Y8eD7D1E2G7L0hrsbiSrzIhxBSYfDT4oJ2s3v4pBzEzJDulCLjOUshpdc17f+V2mpkgU6C0WGoHMrIhXNV5EYUyZMkkwJmgvc05L7g9dOPiNfr1QhYGJckqIW/aiyfg++UOMdcMWNUJbkx7Mwnpw==
*/