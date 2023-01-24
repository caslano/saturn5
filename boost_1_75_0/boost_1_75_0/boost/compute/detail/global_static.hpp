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
VUGBkNV3PSf7RN9SfjXWt5ZfZXsLr9ZavKV8iFhruQShNcVSn/UPxfveZ/3hNMl5huj+sKLuIjWCZt4SCJrcXUbh6WyEqdocQzGWq3dhzwShQwapF9RFQb3zUXcXdAoap30lsTQt+Odn+LL4peDG7Iy+ZO22P27hWtz+wuDGGFoKNJZlEhwBORZ6FVahJjcsdL8WhI3VltVH44FoLYJbgrLB5VhTjYHX9FQ53j7Lb+eb4ctdy39WLMLH1aaT38frguhD7Pub+n6A7zVM9OQdn1qW21JmFaxbgzdBBZtwkAAU/rJM1Pz6C09jKmDLSn9Hy1uAZD9sNx4bQnIwDBR9RAEcCL5U/g6mQEwARO3N8qHttjf8MpZr+LW3M/yWv4nVZPFvXQkW34NA3SB2ra+CPxVqniJv+ryng5X4vEMt3Ree/SH4ID47EfmsMVikJ5+tjcuQLB9Um6p+jIfXBn8Qj+JZ3J0W0PTY1d0LlrLRig0tJ0H3pXr79EV4u1+9rUaxHSq0eKuaT+IIGwE0zQKCTtwa/B+xxDCh2qfjTPI7uohx5rqDBucVy7pQ5Ao1m0n3q/pKh99fKjz9jo7xRGrwT+zNpIP0BmoeFHrdVzKc03S07wp+6QIVvAmPI7h8V0c8ehhBu8+XqT6abvEhTKEpvrlqHVZsKDk01oLed96kl6t+VpA0G44iaTL9oXTetc7BvjXD2DcLEgGkkkMI
*/