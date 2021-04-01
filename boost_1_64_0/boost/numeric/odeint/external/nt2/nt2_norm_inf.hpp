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
1R2pLLtwyomdVtLXLSsH50a2HolKe297zwgwodPzJyHmlm2qluBzU3U1rxL5Uyod2opflZiF53wow+hpLG8hanvavOOtfKhfKe7ZXaoGR4F+xahFLFCIGO/HrCR+6eOH5RtO03yxmcM2sl1mJzktj+VXeGnY9bWQgPtocJ5upRZ3hyC527gWEOIzYLXneP87G7I9hkTp04oBvNnsKz9zwLvbNEvN7AccywO21XXN7NebsALebuY77t9TUvzG0u4upGAkhnW1w3StMJCJzsOgW6RpKrrSMbQ5X593eNZrO+A6JjJBEL7H8GPF2z/cuYhu49k2VLL2UhP40Gj12JzZreN/DYkHgTxTnAr+MR7ucUzSEFhIMT0ISRDDL6TywjNLSvuIXRABBuom8ZT43QipkCqys6QrU4WTXEDyFGd3G3jcrLNtADoKl5fsWnRm7l5PEp5gB1qYMs/Zyj8pOdf2YBod1eakplw9o3MmIjMjxCchRnZhy6gaTAfjD9rbIuPm63gy7m88w/kgcaP75yUkPQ1viWY1W4f+CXRQD6ZED1Hsg8ttzjuVAmK6hQ==
*/