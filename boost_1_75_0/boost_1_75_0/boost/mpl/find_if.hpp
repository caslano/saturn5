
#ifndef BOOST_MPL_FIND_IF_HPP_INCLUDED
#define BOOST_MPL_FIND_IF_HPP_INCLUDED

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

#include <boost/mpl/aux_/find_if_pred.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/iter_fold_if.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(find_if)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct find_if
{
    typedef typename iter_fold_if<
          Sequence
        , void
        , mpl::arg<1> // ignore
        , protect< aux::find_if_pred<Predicate> >
        >::type result_;

    typedef typename second<result_>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2,find_if)

}}

#endif // BOOST_MPL_FIND_IF_HPP_INCLUDED

/* find_if.hpp
hR22Gnz9/kJd2LehBrcHiMWhFtd7p4h61fZbvOJGrTBu3D/a0ZqU8gJegPkGlS9IhffvSk1q+zVm483babec1+bbGL0+PQeOKvSjrOIgevidWCVemyUDuIuhl38Lev8UsVxOH/iwV3ZXffVKHAbn+3Kcz/2yuOhiZO3u4ycwL/i+1mCw5q/V154c7arX71dxJsdB3HDJR78dUONa46UMCr2P2RrzSBDaEUtdEAKhc1ir617S2Tyv1aAVn3/pybKwheJfcXuTHJW+EAANBW8pnD2N9tPFWRoX+3v2Y0P2Ns31Ue6wsUv/ggHhQdkvZP9kcaNxb1Xe/7sI8r+vR/5lwnUszWSdHSws3f5rwV00l4CvU5bEInhtb1aEJyE0DQNoIvgf85LuqTm4cDNTZRxM96Lvaeq6z7QuNlHfDurxMihb1Qz6xGRb9TSrjJTkRvKy2c5dt0QyHnfIr7Yowxs0+G1PS0qmSxo3eFrJds8vhR7O7HRqCOXPqa6Vpvi3RA7zlh4EtgS3vKcv+Psbj+5UjU2ujbJS7ueEffl1ZG6jT8IkM+3eifQ8eLt3GvYBHkDQPAUxFDvddno7CsQY8A9LcOoAsymvC1IDWgeeD9mV10K/wEJq5ZMlfFglYhyto0Qj4/0YBWmmP6FS9gVd0Lfp5lhhYwPa0/493gfChwDIwlLb8ydY1JXrU65xbn5RShH4jdTcJjq7yndaucUO
*/