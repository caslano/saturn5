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
hiEZGE7tw9hYIYAFeakmCdagnxLiZRCKcLVKHSp7TLlBldTDb6W0e3lh2IZul7JySlmose0A7eONSVsjydHfG6I+018y7jXlS0lNwzmeYEt3QIZELfGK10xrEBJGREFMyYm7JuhRMhj6sguz8ydJpYr80f/Opr3CM29WV8F0DazYYbMhR6nWopnwYi08Y52S88FkqsuAsB0f+6ICovVADPMXDO9AqI7JznDdw1mzPhJkik+IOumBMd9DaoGNMERtzqZAJrNsqSgtt+KTPe8m0Wjqk+OojrdLfM2qfL4fvbaDMAsy6VPKmC5XeaR18xxqVAPf25z77AoOSicfWTZPnaQmUt5HKSkRp3dgZlsnRT+9jUjUETSYSXBnp7VhW4zosBi2fJu7I7u870/tVk4EUhFeBKTC4X/waWwM6Y1XRq3aDaMucfUQKCIo707tfxY0OlaSwjpYftKDE+CUGZRyVnHYmi4vBjex6HxHkVe8f2hafwFwGFYyavFKXEUKjnQ63EMOW84OdPv0b+tJnk6GTnmd0EWTEYQTxtnc3I956YjAR2CEBWBGzUcPpg==
*/