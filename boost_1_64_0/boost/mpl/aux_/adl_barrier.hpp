
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
nC8q38fIfTHbB5gv86IZ8Jvc6tbhWBFCO7XCRZMbHgZOmxecoeOvYV7CMGoBBOJx3ILxG6psLF9IT8JBxjJ+ErZlxbGjQcAe5Y9+H2x9DPSwDARTB95NfxCL7bIwa4rTCt+j54ERf7E3OmcIKD/W1weftLtWI8fWkVfU5jxsIDG5LtImh516Sg/4LXH04zMJ/sAEnne/ue6pCGaCKzzKdBGfh+V+wkbMo0QO5g+0jrAOqEdYHoSXgsihsF4bm7AzGH6IDA9cxb0MN57m1R14P1YXe+M4Vo4yg8xFCFyDsth9y6sA05FtAk0fdVgRab9KIE9Q1qpKNevF63mLdiZFEHlaemYwLrgNcIEvRq+9dAYtUGpB+9U87eDAeQgOyXA/ZAsBDhgBWGwgocDTdhvxdPDK4/gTXhCJP1mHuxL8jxWx7pMf7tT8j+Wx8neLfPPGl+O9jzfE6C+wBPKfmP2dvUTLf2L1J7XOtzKvRg64J85CC5CO8KdIZp0eGBJmclANETjIJ10Mob34618XCa/5xoN4/6+NNz4/3v9EIq47m771yPfRdhcsazy0+83HOtv96Fc5gbKz3nARUs01/u6U+Axn/o8sH+WX4WVcUtHQ9QgSWp/1Rsvy704OhRQliyS/s/y74aWXRKVdML0QaR/u0UlDgiN1kq55ok7SFf2SoE6rLKE0d0Z53ZBgBvc/56PQBQRPj/wajh1iBb3ODAB+CuVNLIebdHwHagLjDR4bcBnBJ9qz69Q9V6FweZ2LCp9JuvrsgKkynwp7yKGSK9zW9oSoZZua6m/p3Wkc67LP2ooKa9bo1umgMgNNAyEyJvhmITCI0VFXQij4iqOAMI7wo++HZx6y2weDPVuE+0J4KOgBntGutRHuEtpI+7JvJyFZYVEQJ4frLsFm/0LwqNAr22agh67ndid+QFftnfDgFLsP0J1O5b/uN/SXTQm9bErIMk+q8QCfd8uKuYG9RjvlI1RejlhtXHGwzp32M7F71rq6CsZJiCxn6UdL8sk1iV28I5qZ9RKthRFibfgdqpSG8GFo4xdyMwvOiXgdcmOnvILUD2molOr1FUe0SkWxIev03gu/yBiG0nSw/po8wbJ6l74zZDP3UdPCszkM9+9sOdenqTf9otbmwNUVaIPqeSL6zqe+33XlJqjJldg1ecjPM1RkayK0JdxHT5XBqXRW5jp16HPbpNXwKa3uzSErqdseI3iZ/sMYPAIf917U+D0yNZG+rzlkdpT8P2H539wbIf9/Ptn7ZXe5vXzvZOX5vnj9QSkfqZGkejQjT+BU89cOzcg7gxl5NaTb7lBxlAJktGieSL5VwVauEtzCZpOB7PjGAdVYF25B5yINEYDCyw/Jflbd14JQi/PeBfmDQic7laVrtP+TR5K/l3/2cPR7GfyPx6L9m41Nob1+jyZ+3183N3H+Y8vjv/+9k+P2b360IhreRx9ODm/5I4nhWX9HcnvOa6mfePE2fveQrh/Nr+9FRLa8KSI3JHHtG+gjYx4a/TW1wsZGZvdZ6BH+uRD8Vl5LrgYVFdaPPJ/l4PQ++mseT7e4oorSqydRko4JRjgViKlG+g15mYpySLCsqt8xzi2SWTnoBRHM6L8Cui33B4ebN6Ft5drBAyqqllVQvv9BRY9tCTPFHtx29We4qg4i/Np+c8fDWrWKGtgE3H5Q9Jf2oKVdJUiTQSL/CcB0kKnyesRUX1OnuklH3CTIZggG9Kee0zfIKa5uTqMIsOjgk+/lgPaUl+1xlLnChfBss4dc/xoXqblXIYg3sK6g9I5LLeYCeZsVI7wiYCSonDu5QVo/KcQlk7Lb9dOayad366Vft12pY4Z/zUf7O6haFKn/Bs8=
*/