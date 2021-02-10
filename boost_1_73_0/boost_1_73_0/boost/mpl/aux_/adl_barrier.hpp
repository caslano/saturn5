
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
mt95auwaHqsCis/lFh7zbxkMB+36cWLHNWuQ4oKT4pgKV3CFJU1vNF3bviGQE4169oBGOYWG647q/SqdyaZrCDFA/zmOG6IlAtcph0HYc++tf7CMDZPF3t15oZAUBE/EUfGL7sm4k2IdLx5iYx1raN0Iba/9kziHUBo1UOwPN1m1wZa15ndqcDdj7BWlOEJkzcOgTIM8up7NKjV83ZtaHxpKI/etEIuvT2WVF7cLz1c8bSrxablcYtD0j5prpTu2bhGIfxYvDz70SwTbA+zGfThf2UnF64U0DNqr9G9cEOTo1U5NEJY/hsjglxQhM1hzdiB6s6Wpb2eM/qvW0YSuIwys2CmLOyKDqe3YpSDfItZTnH/yGp7LbIPKsJkHPtgkTEOJvut7+lDDqOnGF+6jLw8JZEW5TaB6LTLMEyjzHxmGwhOIDh+P35/zKvElXgSkdQ0f3H9Nw7/MONNK8acrcRn131BLAwQKAAAACAAtZ0pSBkPp3bACAADZBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMDFVVAUAAbZIJGCdVFFP2zAQfreU/3AK6gtacBM6tkahG4IWugHt2lC0vUwmuTQRiV0lDpB/v3PSUsGkPSySk/p8vvvu++4aaKx0JCoc
*/