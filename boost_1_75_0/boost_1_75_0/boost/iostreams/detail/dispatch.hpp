// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                   // BOOST_DEDUCED_TYPENAME. 
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/traits.hpp>         // category_of. 
#include <boost/mpl/void.hpp>          
#include <boost/type_traits/is_convertible.hpp>         

namespace boost { namespace iostreams {namespace detail {
    
template< typename T, typename Tag1, typename Tag2,
          typename Tag3 = mpl::void_, typename Tag4 = mpl::void_,
          typename Tag5 = mpl::void_, typename Tag6 = mpl::void_,
          typename Category = 
              BOOST_DEDUCED_TYPENAME category_of<T>::type >
struct dispatch 
    : iostreams::select<  // Disambiguation for Tru64.
          is_convertible<Category, Tag1>, Tag1,
          is_convertible<Category, Tag2>, Tag2,
          is_convertible<Category, Tag3>, Tag3,
          is_convertible<Category, Tag4>, Tag4,
          is_convertible<Category, Tag5>, Tag5,
          is_convertible<Category, Tag6>, Tag6
      >
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED

/* dispatch.hpp
jbw3xDCgeeN79YChoyxPkKgZo+EDayZULTlXW0HUuWSItG0oxq8MQqe9FjGG4psT0MuTGFC7Oj9fnErJSZ51hip56fNxsPWb93yjtJ8M+YZU03eaFwjbpLqauXfnLeGaHb2EvqrwB7tQq2gMnxl0xS3Y8NdtFvkXsNdKrHEN0I4vyohaKZYSkD1wR3oWn5VnJ0+7qAjmCVQcLvaNCxnZstpNgEe4xDeCdlI3h8l4MFmuOC/wBnviyVtE3C1XOcLbdoTCvRQIdydWV3cNyDcF9PARJzuCt2tC+6RR3RwfSVAvjuxZw7r2L7VQ9ff+PLx0Qi1e4kiZMiQIK+dbHzcM7vPi9Q7v03d0B2vAAgGcjwxTXUMUO4+pxNq8zvbuAmEYqB+ZfSBUv94dIWKa6tUY5M1hQ/owTUcZ3p8tGYZZS+uArKnS1asnqyc79Q0s37rn6QlkpY6Qpj7Dd+a94/MWD+/3C9r3exdxX6xisv1LKtSFjAv+LDf7b4M7URnKUFPKR2xRfcoeT/BhL3zekb+2pm7S+ZAV461Eitem7gCJR8pf7saOt1Z4qwj5EojRQMJOn7Yy11k01vlJ9Wvi36oEEGzk8Suy/0jUPG/YuxkZE8re4R65nh05ZnGjx6ryZK3e6jZI7zZoDu6J411HXyW07OD8jmj9F8LOsasWBoHC6dbt1sk2b7Zt2zfbtm27JtfNtv1m23XCZBsnnNGa
*/