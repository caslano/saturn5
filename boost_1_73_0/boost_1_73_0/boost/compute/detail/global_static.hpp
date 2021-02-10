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
Wm0oLyqqcqqt7hKv79I6T8ySPxEi3CzqRWrsqrs1Cwqz5Dgvyeo09eKw1WjrXNAU+Wh1eSUVsN5U/GHzzLK2+1W+3luIsHpBy7rMoA5hwbokR+C7VGeJLmW9BKLR4qMsIf9Gyra2J5RnsIo6YUSDqEMLZY3t0vvB9GI0m9L7cDIJh9NrGp1TOLz28n4dDM+ADQOtJemPRaktrCjJrIvU6GRP+Q+s9OkFcT7n/GeBzGfUeUFhfQM4P3nZoU5qFvx8e0VXKqtV2gl60QUNw6t+sLf/iPi/otnkUhAny6Lr4WgcDaKg95b+bLI4rRNNb3ifA9PqlyA4xY5ZnOPBrrwDuU2P8bUbfKViZcmY0c0Kv7osBjAqileqpMe4RoF+fW2dWXOTScVVtEzVjT0Meksjzpz1o9PJYDwdjIbBOxSXq8kPywFs/LAco/CyBAUDAAECKi21SjZsGVczLO26AlzWWczFR6muLEsIUB4M9+q4LhKFAjBZYu5MglgTcB875JuqFwRTp4+9ZYWqvKnX8KapfJPgC8pL7OJFJq5TeN2khA6s1mAYWwULneb3h1wGnDWgDeHJuCLvgUPW4QPFaoocwTDZDa9WlNVpesSlYjIYmwSMfTyTfaw30/fkN8PZnEsLFNKY4Cinfe4NX2jP
*/