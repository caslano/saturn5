//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_RESIZE_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost { namespace numeric { namespace odeint {

template<typename T, typename S>
struct is_resizeable< nt2::container::table<T,S> >
{
  typedef boost::true_type type;
  static const bool value = type::value;
};

template<typename T, typename S>
struct same_size_impl< nt2::container::table<T,S>
                     , nt2::container::table<T,S>
                     >
{
  static bool same_size ( const nt2::container::table<T,S> &v1
                        , const nt2::container::table<T,S> &v2
                        )
  {
    return v1.extent() == v2.extent();
  }
};

template<typename T, typename S>
struct resize_impl< nt2::container::table<T,S>
                  , nt2::container::table<T,S>
                  >
{
  static void resize ( nt2::container::table<T,S> &v1
                     , const nt2::container::table<T,S> &v2
                     )
  {
    v1.resize( v2.extent() );
  }
};
} } }

#endif

/* nt2_resize.hpp
71NNNU37l8X1L22Or9wKzzMUlzNQdDmNEdZFKnlob/jmU8JfMgFElx+IgGrN8t2Csh0tD6dRwXkPnFFyuFB91v1IM2cLYAXQYGg9Ry4XPJHT9i1Kv5QLUva+jg2eCNTUuuQ/0KdzViU3v2FfjdZVdArAKnSvhegW/FF678RWOA/yvSdyP0UAdGKL8D5M7Q9OulncOp/370bL0SSDeBydtLEp+A2ayAaXkEdr+m7ZhyRQEeF7odcsLnCnYcDfFYW+GALaFQxJKMHxfzh2AwAaSy3DHE89wl+OmFyeOkgQdNFu1AYRLmphI1K9gpS+kymzMqZtT4VTA0o5yY6pgLTY8jWq87IQR4v/k+68TmDjjMh7xJFFG1XBeluhdlOTeimISj+r88hkJhhqNEFyWj8LAP7qz04agUqagPGMsjl7EJXoxXKJSPFqZB5tTT/DVyvLzIZpyQ5yQMPPOLqk76so4W9Anfc143pce22q45Km48lC9Pb1YZF/PxJpXJjsCPY4w26FMONc8K1eQ/OmsvSEx87+E07CMBZy8Yi3LXdfQwyFJIT6r+skcRiLbw==
*/