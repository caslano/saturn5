
#ifndef BOOST_MPL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_MPL_VALUE_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct value_type
    : apply_wrap2<
          value_type_impl< typename sequence_tag<AssociativeSequence>::type >
        , AssociativeSequence, T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,value_type,(AssociativeSequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, value_type)
    
}}

#endif // BOOST_MPL_VALUE_TYPE_HPP_INCLUDED

/* value_type.hpp
55Capi0zsV7mb5+QPxYFzG+uIGLbkde+sT04iqB3urF6a1ksT1RKDlZMeLINujgQTCpGRCaq2I3STIByusUUGDyGjlzAxNVVRJ9inP/PYC3tsQRtDIbAHvJgAspQ22pXJspCytnLqti85osZ2+er9UZe388ZPk7xdYjHsT/QN1UPpY56oMca4W/LUOsAW0QH01BTnAq1S7NsgN6TN1Qy/faO/U5q1XmKZMhm4r1YrkE7cn1L32Ei0nY54gP+6LazeMmJJqw+KpQcEfL40b9QSwMECgAAAAgALWdKUgWPz01PAQAAMQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxOTZVVAUAAbZIJGCNUl9rwjAQfw/4HQ6Hb3OZbCiTUDa02wTR0upgTxLbK5a1SZdEt357z+jUx70kucvv34UIh9al0mLARKFyTdsXNj/aZDZgr4uIGXSmYYJfuoIfgewGEjQ7NF1bZMiEwbps6Nr6ZlplAYvDaPoJ0UuSwOPDPTisam2kKcoGlHYgd7Io5bokMr9iCX6SIodRWaByJ4fUF2eLgOWuPlMDBkLJCn1scEYqe0ADGqPNLfg5aP3e0sCgVYqE50cCiFRXlVSZVxxy3nmfJ4tJNOyQVDSPF7z31Idu96jR
*/