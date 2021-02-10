
#ifndef BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 245)
    {
        BOOST_STATIC_CONSTANT(bool, value = 
              ( sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
                    Set
                  , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*, 0)
                  ) ) == sizeof(aux::no_tag) )
            );

        typedef bool_<value> type;

#else // ISO98 C++
        : bool_< 
              ( sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
                    Set
                  , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*, 0)
                  ) ) == sizeof(aux::no_tag) )
            >
    {
#endif
    };
};

}}

#endif // BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
TcLwEQEAALYBAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODU5VVQFAAG2SCRgVZFBa8MwDIXvgvwH0VJYD8GH3ooJhFBYDiNp7YxdvUShYWkcbLdb//0cJ2vZxZbge08PiTuyrlaWEuDd0Gr/fdH9W5vGJlAW5Q6ynpRBST8OhEwlZJWQxdvpcKwOQgJnT5yz2QHWsEZB5kYmtl1DwA2N/X0CliIQWd/R4BaiDo1HbNAlMOpx5wV/LfJBXWiOhFMOfPkXZOsJNiPIa325qKGZTfaMbV4LIfNyv5nUZXGSGF/x6q33lmpDDuOP2TPO/ciH2pdLqpD3nUzX3rFRTqFqHRl0Z8Jpf3hWFj+JBlzZs3Yr4LfAeovRaKdr3SeQpWUaQSUOpzA6gjIVAucAUVhtBMcq9y9nTxVnDyv2PNUvUEsDBAoAAAAIAC1nSlJRi2XvYgIAAIIFAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODZVVAUAAbZIJGC1lE1vm0AQhu8r+T+MsHKJslnAbhojYilK0zhtEkcJzcXyYQ3Dh4J3Ebs45d93F3ASqZceXAkBC7PPzLzzQqhR6ZgrnJOwEKk0l1ds32SdqDlZRNFjd4Kb64hkpdxsCpGR
*/