//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_GLOBAL_STATIC_HPP
#define BOOST_COMPUTE_DETAIL_GLOBAL_STATIC_HPP

#include <boost/compute/config.hpp>

#ifdef BOOST_COMPUTE_THREAD_SAFE
#  ifdef BOOST_COMPUTE_HAVE_THREAD_LOCAL
     // use c++11 thread local storage
#    define BOOST_COMPUTE_DETAIL_GLOBAL_STATIC(type, name, ctor) \
       thread_local type name ctor;
#  else
      // use thread_specific_ptr from boost.thread
#     include <boost/thread/tss.hpp>
#     define BOOST_COMPUTE_DETAIL_GLOBAL_STATIC(type, name, ctor) \
        static ::boost::thread_specific_ptr< type > BOOST_PP_CAT(name, _tls_ptr_); \
        if(!BOOST_PP_CAT(name, _tls_ptr_).get()){ \
            BOOST_PP_CAT(name, _tls_ptr_).reset(new type ctor); \
        } \
        static type &name = *BOOST_PP_CAT(name, _tls_ptr_);
#  endif
#else
   // no thread-safety, just use static
#  define BOOST_COMPUTE_DETAIL_GLOBAL_STATIC(type, name, ctor) \
     static type name ctor;
#endif

#endif // BOOST_COMPUTE_DETAIL_GLOBAL_STATIC_HPP

/* global_static.hpp
FW6H18EdcBN8DF4Pn4Sb4bNwK/wDvAm+ArfB19T8HXgr/BDeAQMe2nPYFN4FW8K74fHwHniCJxjPAfBeOEyvp8MRMAeOhLPgKFgER8NlcAy8G54Od6r5LjjBzS/150U4BR6GZ8B34ZnwU3g2/AbmwATK6ExYF+bBNjAfZsNZbnxhMewCz4Ej9PpMWAoLYTlcCCvg5fA8eAdcAO+DC+EeuAgehhfCTJ6T1a4e4FrY0x+M9yh4
*/