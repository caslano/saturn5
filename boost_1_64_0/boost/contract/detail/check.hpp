
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
Sp1n1CyIE7uTpsqEfcg6n3AOuvdOF4OqXOa9+al8+i7qw4n3nt6o3m/kpz40AO/w3YqQtPPq1uwLk5C4T64mGpIzlh9BHDtDuf9U7IPzOYvd3qvoulavhfiPmGepdoC/gJie6jJLYPRSshQKcDj3VEYWAGA565GM6Hf+OrNJpzoUU/DB/Cvv31fLTluIPC6D61qPT1MeD6j/ahKnxe4O29zA6oMJVIXROjJmX+NZWhfQYZLHmUChAI2FsFgSzyOa44ITqZ6r3sMeYHX+X32WZOHPM/6jVCqgbQ1ivwqh2exfqlzYlW4jDI1kpZcfhzWdwNVkDyY0DYxG6UsdQNfLV80k0xKVk0rPx8H+dd4qjKlX/xHp4AHL9RP8k82iwfV/3xnoLOU5yVl/8pP5/S71XYXWpa6lbL58pt8BTaL4No+0jlkpndGCwUlH8rFnIfktMXsU2o6g7+qwD4BLLQRAhrFkknhhaU1wIAIL9hU2eV3x8VftcfJ2aXdlCGxd2yVwCFMXgIeIGbcmaYVObQV+BmVWNCZGtMHmxiGN7uMxY9/o6uQpQ70YaLlOPA==
*/