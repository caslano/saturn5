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
CLulaIX7p2l9kpN5TAodbW3lvc2vX20LD+UEqhbH5vfeS3/vS7amDQDvBBRj1/P/LT3v/W1X/70EuOYpjN1yjwAqiG9ASOkO3Sz11Zph0bOHn5lsxWFgl2kNVb+DRNZmtlff+imo3n/6mEX0m27JMI9Y0wS0BfSu/nXdVj4iQPuDusE9t8xFv/WaATKjUCeuWjFPea5eoGe7NqlpScT9t0o4TQfq6DqwHyYg+ahewvxtZVSNaWYBFGhHYHON3I1hmaoQkxhersCWiiruYiL4qys3kf/aIhx76/mdngicNFFs+xFWpZFVdQ4q2L+vRedXXVQfdZROocxQRl303chO704oG2peux6wTGmlZyHsgI9bFfJdQj2o1fcw2K+77rDpqr5E1htKGj46iHJ+BrkV0Gc8mjb26oxcCRBsRfzsXtBeUhSXyhUrsNSq9W6+TPE37lX0kyCs1g2NchuqgYLeiJ5eiYYo/DOPtyqHhzRQcB2fm0BbMPGLATh7dgc64HomGUNA9WM38G8OT0FqrKKYGv/9lJO9Rwe09mzdjvfD4FIWnZ8ZJ9lrrCoRAQ==
*/