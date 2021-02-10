//==============================================================================
//         Copyright 2014          LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_COPY_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_COPY_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

namespace boost { namespace numeric { namespace odeint {

template<typename T, typename S>
struct copy_impl< nt2::container::table<T,S>
                , nt2::container::table<T,S>
                >
{
  static void copy ( const nt2::container::table<T,S> &v1
                   , nt2::container::table<T,S> &v2
                   )
  {
    v2 = v1;
  }
};
} } }

#endif

/* nt2_copy.hpp
NJ8SCeEIeWRdOA15BN9BWKvy1q4ZOyV0a73ZS2iRt8wuaYdgFjmS9U6Ju8KAP+rC2Zs3f8FLeP3q9VkAY14JLGFlsFqjugvgbeZ23hV8u+1r/DsANMDLfkuVFEKDlrl54AqB1qVIsdKYAdeQoU6VWNONqMAUCLkoEUaL5c10fhnAQyHSwpLsZAO6kE2ZQcHvERSmKO73HDVXBmROcCLPhDZE2Bghqz5pIxhUG205rDwvtQR+z0XJ1yTEDRTG1HoQhmmjyn77CmEmUx2mhxz0C7P5/jo35GTDdyBrA0ZCozEAGxnARmYitzNlhTbrZl0KXQRHS6RXZaFUoLEsLRfhBOq9d4RVm6PAhkFNtoWxk5aVtlIPhdz8J5CSaVnyRlUkRMmgoExSrgNoqgyVC3avf5BoE+uy/Gx9jn4zkBWZgU60gumqA2uuhQ7gepp8WFwlcB3FcTRPbmDxHqL5jSX7OJ2Pqf6CxBTgtlaoSVyB2NSlwKzV/H0j9P4QVVo2GULHoKZSdbwnWxvcZLhu7ty2qKhiFOOnBVfQu4pnXe9fD2BEK+jZ+g/bu1RmtsU0nEMyWSVsEsfsU/TPImYX0dgGUYIa+uQthmmqsoGeu57D/Go2G3oUInLfPb4r5ZqXTFTC+JabXc4WF9GMRbNZ
*/