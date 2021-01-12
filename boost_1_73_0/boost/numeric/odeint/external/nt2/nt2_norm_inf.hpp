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
zEy7bAaI3EC152ONp4tdlKmyEsIaD5EVUD4VUQEDtn1qWrYxesYqFrVOmy3wY71GBPDzr9bAuVzmNYnvMl+rNFvt1bNtr99M4H6ZeCH2Gy8eyCN4fNxYj3NYvEM+b8pGP3r8nC4Gy8O1Lmk38++bjmtdCeue1L9a/7eH0+zlNLv1fDByTn0toK0Z753Ipyym/FoPsL1wvyr7mB3bEonHtkewNpsiXb7UaPnHYyRoUXb2/hGF
*/