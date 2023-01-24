
#ifndef BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED
#define BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

// Copyright Peter Dimov and Multi Media Ltd 2001, 2002
// Copyright David Abrahams 2001
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/ref.hpp>
#include <boost/mpl/aux_/config/gpu.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F& unwrap(F& f, long)
{
    return f;
}

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F&
unwrap(reference_wrapper<F>& f, int)
{
    return f;
}

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F&
unwrap(reference_wrapper<F> const& f, int)
{
    return f;
}

}}}

#endif // BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

/* unwrap.hpp
I/LLoSjhXpx4Ts3pNb7REoogPxR8FPLDA0w214A6Iju3ug+o3ENfinNn2Q/SQI8zZAECdO8CsmYv0SAuv3udhjsLt+KpC31fIuQeSsDxV+XrH/Ajxmcv+1FPIY8Nou1GQ/TtA/HrBmVw41gdlQPPXSfy6k/Zuy91ubeZ7yPMh1CWvBZmH5enzVKiXwzKNSYYsAFLnCOTTyZM8JGkPyoESobTgYY24/x7RG9iaAeRnALL+jWzOv0fKbbS261RRoWkYmqDtIn9NOktC/p5mogotkVAIwy/0N1KnNqdWDF3W577ZMqdzOeWp53RDkCDL7e/a18C1I5aNwR3u/qj2TPprl/ePEf1Tb1Qnl12QZ291V+EN3kyXrq/+t7/lns8Zj3HVQ0ZulKJ9qclDoZQVPddznSnzlHEK7+4HENaTXL7AwLvX/g7FkqUAp+F1F+y1WD0gGsm/BCR2YlMBLjMX7jJ3HP/8t0nVkfViwB+dyZkP+O0WPQpE8mjbsa/gJM+HZRfRbeg6875uziOa68EMjAfO5oj0aeq6RubLWdzId4dRb2zU0Kf32Txoj/tE3Wo7f9Nbcu8DXYnxf5LJuj//MQQD+c/0EkZR3tzC+d/kpOehgNuoi6NiSx6fHWspN2dqd9ZNtPcWVeQ/vrCUG9qjA7fu01VY0XIVeJ8VRu2+Wb66toAzSeCLz3xDVA2+VMe7KZeNYVlVAncxPBX/IfI
*/