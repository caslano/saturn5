
#ifndef BOOST_MPL_SWITCH_HPP_INCLUDED
#define BOOST_MPL_SWITCH_HPP_INCLUDED

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

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template< 
      typename BOOST_MPL_AUX_NA_PARAM(Body)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct switch_
{
    typedef typename find_if<
          Body
        , apply1< lambda< first<_1> >, T >
        >::type iter_;
        
    typedef typename deref<iter_>::type pair_;
    typedef typename lambda< typename second<pair_>::type >::type f_;
    typedef typename apply1<f_,T>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,switch_,(Body,T))
};

BOOST_MPL_AUX_NA_SPEC(2, switch_)

}}

#endif // BOOST_MPL_SWITCH_HPP_INCLUDED

/* switch.hpp
s39iQFmWgGXde+HTgcYgRj/SURg378RfMCCKF97GoleL+uOhM9EXjntFbfQacN78lC62BfTDUkiYX+gm/rdaybPiQ2SWmhadPBbKjJt1xgOzJx0JNtdveqpQtk9TBwvtgir73/N0HHd2wF72Q3/IJkXwstVkvDk8WBDYm2IZjtj3QD5APpBm1iJi9LTH3BNp8ooS+sOJ5kEpenKrjX2/KkNGdRd+H+BXd82nDLEhI5OCszILEU3V9sBs5Hy7THen1Qn5MMVvEghqtGq4atzxgQSrgwRiSDPtzTNoQdMo+tv87R+Ett+1o8IRhXD/EYNwW/Mo+JNOE4UNr+lTivi4dKLIh9NvCMLIKj0Ey3D+j1wfxPGMAk34kUu28YmC5OUQxtDg5T9AbahLL6ixCv8ooRhC/gsdkSn+XlJMCksWqwQL7Y/drOS2KpKEtij43iZiwdhh2AzY89V4Tvvrlxq5v/0FcnMNWH6FyG599YTPDjnsQRGpwZT8I2IYFQbDFpnVH+HUp+HPp+Eytpw8kbOD7JcROMSxTB2xYntRM0NuHOHipyHXDydlyKLgiZoWnh1MMGNK4tn5H2olsUXq3udIAeGbtkU8CTtD5qPb5NZ6a6+8vt7U8y7rz8f7AqnAmrl3P84PO2p4vHIx7ChkfHL2Gjvhl7YEfdGraJ7SqK57V184FmnvaY3biVnmrzbwXVxqW3baA/cHMga8DKAe
*/