
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
QMpm5XYRBm5GLpcmnmsJcQoEMupGyY8JR9mOY/YU0UQGztPcJRNcM+F2O4VY5FwJESfB8aFbdUK89Ix7Tm+mPiQSZEeEmVYxDw7dl06kR11urr9zskxn9+VzMevetY1XMPJuSx7TLSSQNilSvaz53GzDtb4k7EbRNqZHHw5X0xKrGEnsD2RcMy3Qd0Vt58LQe2WfmoVij/ejQYxeXZ2drOXTtzOX39TU1GDeL9yUXlI+o9pWvn5Z/xgAKyzU0+Wzz5EnMJgK/5jl8eflM4F9fXYTiyPlh45dyVy0Y9mTMO7E9bzcJU2buJ0vuKZCWTib2KaEzPhu5ai48BHSOhHzNfe4zSUrL6ytISfuw7qeZLIiJksK2zCr3BeK9Tyhv4ZZQKjSajcrQQ42i34EQxkwLeqcxsq0r4pIXFPGqQC7e7eo5Ujj51jLvBjfUK/6tQO0JYR8nuMP1TFCV0aTj4zFkITprpVs8Jrqp6jh86knTNTRvHvloRXJpGBUfPr4TCS9SQ0BIQf2NGX5mtGkxd3+uvT3pakeEdIL6lkfz+g0fSxaQ+PCeDppfMmFquDZRiIhQccZlYGwgN0jUXulFSynh5+Eln/+mOmY7HaihXSqYAMma9NrE2mhTtcTqnxUFdKMKFmdknV4fwqGq8sdR16NNZdqrJWPF1DSl5Pda1Llwyc3/dhDL/XIucSZj5ihY1O5J/VviRy84Kko0sAW
*/