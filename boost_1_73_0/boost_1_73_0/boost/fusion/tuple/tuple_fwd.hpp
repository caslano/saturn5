/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_FORWARD_14122014_0051
#define FUSION_TUPLE_FORWARD_14122014_0051

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if  !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   undef BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   define BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct tuple;
}}

#endif
#endif


/* tuple_fwd.hpp
5hkJykbTV8cjV2/DYmu0Yu2/i2vGxQ3KrPPrTrfXr2WbyVa5Gr9dKUtCswfcjvRdW/id9bJtG8RXWbqazQgtwKHAds8nxbM6bEo9iSUwwVus2okNkfCY3j2HnXLudRVq1/fP5R4RvPDUmY2xOVLFOcJttTp/DsjYYApApaFGoNdhrpEP/A2QC1z3BcBSgE/lvjpM8YHIatJBOoTDQiJ4fYUBCR4dXsYol+nPN0H7r4l1Z+QPCJWwKf5FdBduFE3VXAWLe+ZZww7MZgCG+N6ARBHA7Pob58OHnY9ArzYebVibdORd2yH5lSL/DHhcX1rcrElUbORqZbJhznH11azLFxgvK02HNw/n75+k4qjpVr6JCti1rjTXpAyPr8WACwC3ZK9tsYTwLkK3opJy52jbG/qytswVbPkCbAtgS5HqPIoUoa5WD2gyFymBIwfOaHjV4Fnw/qNjMVCGfZIViMGWXYXPvNmjOLK6qBTaXGgsX5RlEGl2iaazs0/D95w+lOpP3+2bSF+ZC1joJxJ3Jmk6429BzA9hlfuaB5e9f8B7ethrH7cPMchiz/DlDiR1afOMvqREW8oiJP7YyIcFKcWiCxOxYCo1MzkE0KCRkWXmeZR3XE/PnswdoFlNgJWB8N327s4O3NhHigtZfoxV
*/