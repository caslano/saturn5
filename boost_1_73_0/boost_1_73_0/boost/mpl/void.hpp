
#ifndef BOOST_MPL_VOID_HPP_INCLUDED
#define BOOST_MPL_VOID_HPP_INCLUDED

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

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

//  [JDG Feb-4-2003] made void_ a complete type to allow it to be
//  instantiated so that it can be passed in as an object that can be
//  used to select an overloaded function. Possible use includes signaling
//  a zero arity functor evaluation call.
struct void_ { typedef void_ type; };

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace boost { namespace mpl {

template< typename T >
struct is_void_
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_void_<void_>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template< typename T >
struct is_not_void_
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template<>
struct is_not_void_<void_>
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

BOOST_MPL_AUX_NA_SPEC(1, is_void_)
BOOST_MPL_AUX_NA_SPEC(1, is_not_void_)

}}

#endif // BOOST_MPL_VOID_HPP_INCLUDED

/* void.hpp
eQPTCRa1BqV0rY5ZZu2WNhxNCLTaYCclvOY2Ax4PgE9B6Rje3ikuugQIIrPZkHfMeAwO1b/ZGPOB1s3WGAecBlgK0Z/NV+H9QvYbxMV8GYo3z/cHtN4dwqXSJxz6PbBreT9jmSc1NC2BSiyWYDNs5wSZqmCNqMGpMmMdFuzbXILYlsaayBRjRocJBJX5+hc1OJ6SHpuZykr4h2GP/SI5+G1KXGgYu7IQ/efJcnU/f+odxinhUlz2WO8/VQnEua9AnJoV52v1B1BLAwQKAAAACAAtZ0pSYA3v27UBAADGAgAAHAAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDJVVAUAAbZIJGBlkk1vnDAQhu+W+A+jRHuJSr2scomFkNI0yUZVs6ss2UOqHlwzFCtgI2x2S399x7AflSIhGDPvvH7G49Sj80o6zFiqTWnp847D3naFy9gyz9fjCx7v8yn4Ip1WIHtfsZSflSmfii/ZJWyw22EXO10gSzts64HyhfRyMuTJ5wQW8zmsvrGv0qOAvMdPML+BZ7ujRDKH5Fpc3wiSPH7P2WQnIIDGblzwUr4juL1TtXXI7qzxaHycDy0G3R/PK9/U7KE3ZogrlIWAAR09jEAnkpQfyEbku1oHgwlZjQuSTJtlrPK+
*/