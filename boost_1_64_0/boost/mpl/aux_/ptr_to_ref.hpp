
#ifndef BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED
#define BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    ||  ( BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        && !(defined(__STD_STRICT_ANSI) \
            || defined(__STD_STRICT_ANSI_ERRORS)) )

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    *BOOST_MPL_AUX_STATIC_CAST(X*, 0) \
/**/

#else

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    aux::ptr_to_ref(BOOST_MPL_AUX_STATIC_CAST(X*, 0)) \
/**/

#endif


namespace boost { namespace mpl { namespace aux {

template< typename T > static T const& ptr_to_ref(T*);

}}}

#endif // BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

/* ptr_to_ref.hpp
K/2Gy6hkn/LbRQwEV7XcanOG519DuL31YAm6Z77ENeynBPhqJhb47ymC6U5bn0G95DqMtwVz+Z0BMD+GvN0kF5sAAXVxMXzgru8vd7qY5Yp/y/gtj/djjEYu+iO78S92/N5LCvlJOHVqnWabRsmJVYs7LMTefZeNIWdmGmvIG9FrjKk4D2LllF6qGT/Z4x797vOw5LZClDcI1khx2cAUk0aerIFVzKQUQJ0pQt4gX+wIaJx+Tgp2mh1y7F0+ymb8osso818UPH1BE9w0HyU7rDSVxhY68M3au5zfUaTH7v3BLpNmR++FYW1q0Cc31xAYSd7IxT26Q93cgN/qIq3/yma2YXEnac13LmV83DsYNRrWFNzogJfmDhsifUbcogpirNGaJe7Ab0h+XT1tmu2No+q2dMJ63o1qfFc1P/8nEINM4qAqKPqXA/GxoU/Pja3ForGqtfI7iYIO5tAs3Fw2x22/fUXNiOCjCGXA+eKCTPMWKL4Vs0M8waq+PTwjk8gkdCXBDEZR4AEtlyYqJXI4FadS1g2wGTyz+J44V1J39LAyhviMnEidbej+0Q==
*/