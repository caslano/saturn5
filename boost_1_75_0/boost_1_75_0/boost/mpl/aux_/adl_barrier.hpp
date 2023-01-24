
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
cJoiXy45jaqYU98TGp/xBDXFbM85kfUlObLzBMeYvzEIwG7+YW27k/Vl7Vpk26K/7AGzjjXgzqCfugc7/M5rbIOb7c4LiENzvsdoXH7RxeHzwMgYUQUMKHrjefEIa3sEt+snPyz40yAcE71WqFF9IuFYvzsv2UO68BBiv4WvyFK8tpT+vACH/nnR06m24Zcn7aMSiLQHf/RIgTkXdKkEAfZynq3VNqq4k3HT9lJL5nmb29Is/atvXt+PlPbFXH545FDsldkkM4wkn8LukWhsTYTxXnI+Gm1TBrPDx8gPp7avrXhBGtp0xN3EiwnS27cSrA6/xDc6b7p98wAqZGbdjElv9dTWreMjiiz8UavG8gJ8IZv1guay/uA6nQl/BL/poJLRmrpVPR0V9MlLL7TBRsSXs8CvqGG6vEtHE16dp7uGkeVKiyvf8+HO8zUomIK0Tkjn+51/iS7knyXPr+Qxe24nKy8IvrUC9CPKwEVQrb1dviBuH394tD4XJeKTGedUwMsg4O7bs3Y/6dSWRFwBnofsNlR0OVkccPHfqkO6L44FF8tcFRLInSPjlow/JSw2rs9PjSN4gwMUTmMarxqvBr4kmamBrfmXqUaRd5yuqUG/RO/pfWvp/AIGN+yConx1ZuKNJTupiacCwwjVpOcjsChiakco0iI5wkK9cUN3kyA7TP7fPWtv+bsMeFbiWL13Qwy9/aMFfCa6EI07
*/