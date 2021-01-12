//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost { namespace numeric { namespace odeint {
template<typename T, typename S>
struct algebra_dispatcher<nt2::container::table<T,S> >
{
  typedef vector_space_algebra algebra_type;
};
} } }

#endif

/* nt2_algebra_dispatcher.hpp
W+ImIEM+U/Vmyee7VTDJW2hovzLyX5b39VdX9d/+P47XI1zXzyUAANYMW17r1OTsO7VVjHGsnfCwMWggW/I674sBIGGwVuUeyNd2Ml+7huatsFpAmZhKRT/M9/U5fRiB87fXNgzKD/Sat9pZWy2f0LLxGGHlmvCca9E8IQzTzXAZJvU6OLKBrA4XL9S+oJQm9rOVXtiUrwl6LFRqfmrociGupwbouUw+G4GbuEou7dC4UjKp
*/