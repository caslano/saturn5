
#ifndef BOOST_CONTRACT_DETAIL_CHECK_HPP_
#define BOOST_CONTRACT_DETAIL_CHECK_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/config.hpp> 
#ifndef BOOST_CONTRACT_NO_CHECKS
    #include <boost/contract/core/exception.hpp>

    /* PRIVATE */

    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
        #include <boost/contract/detail/checking.hpp>
        #include <boost/contract/detail/name.hpp>

        #define BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ \
            if(!boost::contract::detail::checking::already())
        #define BOOST_CONTRACT_CHECK_CHECKING_VAR_(guard) \
            /* this name somewhat unique to min var shadow warnings */ \
            boost::contract::detail::checking BOOST_CONTRACT_DETAIL_NAME2( \
                    guard, __LINE__);
    #else
        #define BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ /* nothing */
        #define BOOST_CONTRACT_CHECK_CHECKING_VAR_(guard) /* nothing */
    #endif
    
    /* PUBLIC */
    
    #define BOOST_CONTRACT_DETAIL_CHECK(assertion) \
        { \
            try { \
                BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ \
                { \
                    BOOST_CONTRACT_CHECK_CHECKING_VAR_(k) \
                    { assertion; } \
                } \
            } catch(...) { boost::contract::check_failure(); } \
        }
#else
    #define BOOST_CONTRACT_DETAIL_CHECK(assertion) {}
#endif

#endif // #include guard


/* check.hpp
716PrR/EX+5BQopiRZJPQDJkHwgoQUqZYfcO+YCLaIqdIk2ISNdEabVj3HDhB9PQCy2nzKzfWJkUdUrhVINpJJqfWVbBy1tI8rr8FNMyjXeJuhvOUuhXSvROLAMu4ej8ciNdPQP9HBVWoNC+vwnb+v6F8m12zKk3MBqHw5k31f7WlGC1CVSclZoB1CUeZfFETFaXiea0Pe67Q27YMEKtBFdcbStq4dQdym/FN6hYy8h05w23VEkTFDW62sKukkQrWWvWYHi8JyigoilZ410iYUVpae3qItC/q0/nJ1ZVNO1hohlVeKxgmXmaphccxcHVMpsCy4BuqNjiFYRl0cBYSVHk1jI7f83rwvUm2g/pUHgPGEiIWY8l1kfHk3xNAQEhGJ7gZoQ5KobdC3c+iSx/PpkYw3QWRMEwmIQW6slYxv+619PJ2AhIKqJYAkYv+rDHTMYpEllwktK0i0TU+FHb1SNOiSLQ1/896zMWn2VdPdg747WqatWDz0YRWVJwSZ9PnZiZr03wF+zf72v7F3xFQ+TrLJ5YXywLNYKVZ2W3yT3om2iQ8a8E0x/gzKuoH0eszLhO+o3qteGHan+Fod6bI43cyLXh92cwenpfTsZMWdyPWHb33Jt40cJy07T58B057w6cfbNgNo7mMx8+
*/