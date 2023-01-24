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
SWCSx/ZZqSVneMJ+kOr6c9iytWGP9GieDF6kdqqC1FxG1voGraxz1a7pqjpOqV3zBnM4H3af6uK8133BYCq8VW3zJWqr3kiNPFP19iZvjurthP354dUB1Y6d067UEGUQoC6mZbgELPkTon0n0PXCVeD6GrspMyLgk1vndIBGiCdl7nqRPqT++A0S+fA+ghJ7OG/9N/Hj6vCAj6+A8nI3hLHyUHbGVqsJZ6023/9waWetU6wlXbDRrGllc9poXZNdsgQS+G0l/XmzjyhZzF1DStZwV4o381qtxEFzuoml1vaIbVQE9VkHf5uSTaw/nFGyJTy4P2zgwkvOTMXV5b4od53R9GgK4rTcHEZ3NC//HHvGBx3SRXVQF/kMzgfdddAppyBdCT5+Cly9bHZiSTJ3mtz4KndJrObtgGzH6i7L9BWHETuuyksiPMrlCOhV1MO9AsLGSZOpeLm1+nQkNFq1yS1BWt8yzKkwnOe0Yg56V3PvbDN8+W/40mratjxq0O+Rgg/tkkveUeM7lrwajiLx0Pi8tOo8m8m23XcTZLAFBwlgUZaXVA7t1sH0aDyitarsXPUGqOSVWG4bLAibg9VAMQQkwIFQEs/j/J+XoGkFlXd3CcrSTdVP0OuXzOu37E3MJpl/62prLbkfWteHXVtSwENNhSvIQt/yqG8hhp9TU7eGsJd992PY+cCwKl+WgfbGnliPzbJ5eVTZH5EQ
*/