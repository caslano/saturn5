
#ifndef BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED

// Copyright Eric Friedman 2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>

namespace boost { namespace mpl { 

namespace aux {

template< typename Pred, typename In1Op, typename In2Op >
struct partition_op
{
    template< typename State, typename T >
    struct apply
    {
        typedef typename State::first first_;
        typedef typename State::second second_;
        typedef typename apply1< Pred,T >::type pred_;

        typedef typename eval_if<
              pred_
            , apply2<In1Op,first_,T>
            , apply2<In2Op,second_,T>
            >::type result_;

        typedef typename if_<
              pred_
            , pair< result_,second_ >
            , pair< first_,result_ >
            >::type type;
    };
};

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, aux::partition_op)

}}

#endif // BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED

/* partition_op.hpp
ST1A+Jg5zrrqsHkumGkaGVkn1Rx+ibpMAdl8oopFXpVEvqPlyJgoYgVS48pQD7V+SdcW1/iYiznjRR40COeMFDztZqNTKolHjueM9fWboFSmjlDJyYnLj3SM4yPIzo5SRxRvo6gg9itcnas1EubLQsiMdQ3FMmpKIsN+z4lAeKTe3G8kwCcrFNrQEGaf/7DaFfukCk0apcAhGZMpFriSzrpIH7LPlEzTLOU6gVKz1glOMxvmZyf/AF+KOB8PbWLKeFWEzJCuFK2hS9wxQe3q7NLKIEp0b+moJjcZOkpl4fFRejlkTtrciYFJNrQSnIzYF2TJUJeuPsoIDas+TXl/Zs2MU+KUOAnRmTXZ2TWsGMTfzKW5upmds5u0L5Ex/crYOEzbMzyy3JEwWQ3k2KaIY4834mPFweDUxOt2J7vGau2tbrQ366g4VD+EPSids4AizpmIIUXTHjSrDMUibT4utL1zorODXj8AY1brsMFAhc3399Hy9TxDjiyer2FJYnghhqHL8GiWK11fYKaU9nxJqw9gU/pTcRIiOZ0Nt9uMO/6OuVEikZWF6Gw1yvS5/woWBl6GLl4VN1O9tAqID5Q0vjNLyC+lFPmVxv28/oktnFsnuLGagNwLjp0b5kZEDF2frt/L25Fcmhpfu2pTo2nXFnQ3SRJdPKWJnOwP8XJ8baRUeMAGjlPBOI6QYw7TxWxpU3w1gMGL5SpOFsGaC8RGxgFlJG4u1Y4ajv3n49/Dg67/z1x86lMlOt/Azv6BviH/5PxwDdIfuyGu0dWOLmKXkvMm64kkAceg7KsvoZCPfxT+8fnETyjFZ3h6HfgpCoCfgOhQAAmQKPjH6BKeTgYQBfxp0yB+nSNxtDxDeZj4RAY/Ux5QAH+QkbjgEb9OBEqByT7ZJTLokfIw5RBiMog8iVoKhj4l8sR/T1EKvCmUJ+HBLyJ8wgOFj8TR8ohUy/eEHH7C9SQSvYyko02bIiB8QMSkp9Uz8IgucbryEB7Rg9PpkjIaeCQOQNIw1AfQ50fyAHTlJjrk4JAnACgKv4cpwB9koPCADyYo/gDIKOiAwoM/APG0lGKlAcBPkSDiED7igEX8oMQRHhOPsOAlfl1+xANHdEgyrPIZykPy0fOIl2dcfkL05QYlfJKHUNc8ZAShufRNLiQ80s2gZK0Ej4wmUNKNAPyUoYkhg4MfeqQrCA+g4PRpgUfiCHXDgfjh0/ohNZSHKYe+c6FLvLo8DRKkZSgT8RMu4evzZeqkj8MMa3i1LUgLeEKa4gnhF8JPgU9kNHwA+PBDptUB4EApOPCIjDLE1cUBwCc8+MEnccEDSBoAkVMl5QcY8oUMjqRNePCTPIkfjl1+UMLTjkCmThT8gK5u8As9MSs8wSWOprV+/HnSmC3wgAJ0CmQUHCj0yaoAXfCIDuHRZBaSuIa0AFAEAOgwMgp8UMJj0iU8mikPKQNA4tHa8gC68sDPlI3IjMvGlAdh8KFLZIQHwE88fALMCsALAI/yAuDI7OMTIIJu9kIHfsID4AcFEBcNy6QFPfDhB4VfuwLoeBRZ/XUyT1BAmwdAZHqeIT4ckZEZDsCvm8WgxO9F/BRlKAugz5fwiJ9nKD9prBS0xhg6hfnSBn7S7KDgG1pxDAUdgFDSkNABdDx84CdxiIy4MQD8RAoZ0Sd6ANGj9GHSMfpyMPFJ+cCjmXKReJz8KEN5mXIC8BOeNg74Ogc/U+7/u/9chwM6Sn9Yjetmezu1g0GWd/7CxUuXr1zNv3b9xs2CW7fv3L13/0Hhw0ePnzx99vzFy1ev3xS9fff+w8dPn798/fad4vHNBGXKlhOaW5TXEcsKVhVF1pUqV6lqU616jZq1bGvXqUs=
*/