//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_NORM_INF_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_NORM_INF_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/abs.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

namespace boost { namespace numeric { namespace odeint
{
  template<typename T, typename S>
  struct vector_space_norm_inf<nt2::container::table<T,S> >
  {
    typedef T result_type;
    result_type operator()(const nt2::container::table<T,S> &v1) const
    {
      return nt2::globalmax(nt2::abs(v1));
    }
  };
} } }

#endif

/* nt2_norm_inf.hpp
XRYt4f49rsllscbLkz5ZLA2550vk/YaYc3Edy7hs/D2bzGVRbJrONL6mqT2qz/h4Fm0tD7n3KSqeV3B7z8YpL8pUsgwrQ7L8Ki7/3EHqV+VV/Wu4/PNcvgXJ866qfnFWRe17lfrYgF5kmpeY5jfS3wYQPfW/DyDS3PtHxR2iTajMOZ96V3Px+4hNF7mQ6cSZlZCkE9sW7LQn0F4qFfcu4zLivYjOVNZbtfV0SNwnU9Zb3d+/MmTf/++UX43vacg=
*/