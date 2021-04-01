
#ifndef BOOST_CONTRACT_DETAIL_NAME_HPP_
#define BOOST_CONTRACT_DETAIL_NAME_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/config.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

// NOTE: Explicitly list number of names to concatenate using ..._NAME-n
// (instead of using ..._SEQ_CAT or similar) for optimal speed and reentrancy.

#define BOOST_CONTRACT_DETAIL_NAME1(name1) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_PREFIX, name1)

#define BOOST_CONTRACT_DETAIL_NAME2(name1, name2) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_PREFIX, BOOST_PP_CAT(name1, \
            BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_INFIX, name2)))
       
#endif // #include guard


/* name.hpp
BFS8S90Gd01FYIvUopkptuM1jnjSyUIvNEFYBqKDmh3qog87eDFftzZvUm8TmhE9HBNwQhnaPpdPbW0HxewHHk2h3EjUIckY/9rGytL9rHL9BMj5Lk3cLFfwZAef3iSt2xaUUK1VGSvtEBbqB+7EaD+RFDc0O+/+AHgIL69Txgxi6qcB/1QCfq8Pw4XKVWgS2Guhk4a/dvZYLeh7E6kebFkYN4xZ9eXJkC89hvC9Hr8xdDtT5N6JbtvrDQce2hJehRhmcqC3VHdqtKfD5ED3nwibzAMeK3Mbdr5ImXtoGyDloZDkcZ4WDMe4dcnfXEopnU4zHHiJo0nZa01ijZ1LKoevGw1Y81tvsDN/pQ1Z/ESmkYBBpegSD3Eg8sFGwpv+sP3fCtMDjbGLmKz3qRqFX39+NYDiuqfZDCiwPZ7GDeXch9BVmQbSs7bNM8AMAm3f/KBw11EWBB8J+U7quLjR2gvWh2fAKjMvMIERsPzUol1urEOjpxc2a8jpoNlH8aguT3XKFWSznK/XNlQgq5P9q1fB49cBLQcVRt4VVOf7SjVkNRXc/0XMy3zyDw==
*/