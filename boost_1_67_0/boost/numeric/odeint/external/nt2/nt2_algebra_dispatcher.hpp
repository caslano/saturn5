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
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
*/