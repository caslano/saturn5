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
fLvta/w7ADTAy35LlRRCg5a5eeAKgdalSLHSmAHXkKFOlVjTjajAFAi5KBFGi+XNdH4ZwEMh0sKS7GQDupBNmUHB7xEUpiju9xw1VwZkTnAiz4Q2RNgYIas+aSMYVBttOaw8L7UEfs9FydckxA0UxtR6EIZpo8p++wphJlMdpocc9Auz+f46N+Rkw3cgawNGQqMxABsZwEZmIrczZYU262ZdCl0ER0ukV2WhVKCxLC0X4QTqvXeEVZujwIZBTbaFsZOWlbZSD4Xc/CeQkmlZ8kZVJETJoKBMUq4DaKoMlQt2r3+QaBPrsvxsfY5+M5AVmYFOtILpqgNrroUO4HqafFhcJXAdxXE0T25g8R6i+Y0l+zidj6n+gsQU4LZWqElcgdjUpcCs1fx9I/T+EFVaNhlCx6CmUnW8J1sb3GS4bu7ctqioYhTjpwVX0LuKZ13vXw9gRCvo2foP27tUZrbFNJxDMlklbBLH7FP0zyJmF9HYBlGCGvrkLYZpqrKBnruew/xqNht6FCJy3z2+K+Wal0xUwviWm13OFhfRjEWzWRdenDu9CVt87IL1ApDXiozmvjZUQRVA5weWLuTUv5jdVp3u0GEUGuqBZ7x+tW4sCblzXMj1rmUa7o2+sPs/N/AE9IP8U4dpibxqav+X
*/