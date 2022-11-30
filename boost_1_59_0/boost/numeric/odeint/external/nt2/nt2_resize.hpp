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
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
*/