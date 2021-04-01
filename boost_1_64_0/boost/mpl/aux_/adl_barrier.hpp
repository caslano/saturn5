
#ifndef BOOST_MPL_AUX_ADL_BARRIER_HPP_INCLUDED
#define BOOST_MPL_AUX_ADL_BARRIER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/adl.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE)

#   define BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE mpl_
#   define BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN namespace mpl_ {
#   define BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE }
#   define BOOST_MPL_AUX_ADL_BARRIER_DECL(type) \
    namespace boost { namespace mpl { \
    using ::BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::type; \
    } } \
/**/

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
namespace BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE { namespace aux {} }
namespace boost { namespace mpl { using namespace BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE; 
namespace aux { using namespace BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::aux; }
}}
#endif

#else // BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE

#   define BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE boost::mpl
#   define BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN namespace boost { namespace mpl {
#   define BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE }}
#   define BOOST_MPL_AUX_ADL_BARRIER_DECL(type) /**/

#endif

#endif // BOOST_MPL_AUX_ADL_BARRIER_HPP_INCLUDED

/* adl_barrier.hpp
x8jZ6N7msxNeI3OorMjmGTX8iA/bqTafQ5pLdyrfOz0b/RFzwdiNej9+CiR9HKXl+ZonTmhACGusenxTw/PiQxRxBrn6/Q2z+jKA1C9v4/Kz3dNg3AtTrg8bhtPb6vyLICzZbuIosg+yd0yDA1hCLAuJ0HmDohZmLOksi4vlwHJ9yVJV29+xdAh0naUOTajYgU+yMhEBjn2UAQ4atBkBNuFtDozbDGRxyw7cae6Vy95d5jvA16KmC58jl958UB4yzJJ/WnuBosgBQgn8sc7Mh3HVunWleZy/NeG1ZFCsovUnQMqrpWLpuIpSmEJ+Jxnqk6etBVOr5O8Jxf4wDOW6/XJngWuQAJ0jLaxjj5UGNkfsbTemtqRxM2H8G2/Tbj1ccl9khptOhZex+G6QFBwctvl7MZHrE8532EEIH7wrdWC4zC71FmfERbLKG6objg/8UHx+LoDISRNBSZ4J0vJK1/IJN6i+ZkVxXM7ke8yYtRdYoe/WhK3VhLfeEUP5/LDdzAou4TkbCLNCrw3IHXHFYOHxSzgBb2fJ6EHzpl3ZXNgE6NnFfYrNeMtIiw==
*/