
#ifndef BOOST_CONTRACT_DETAIL_DEBUG_HPP_
#define BOOST_CONTRACT_DETAIL_DEBUG_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Usually, never #defined (so "debug" assertions always in code).
#ifdef BOOST_CONTRACT_DETAIL_NDEBUG
    #define BOOST_CONTRACT_DETAIL_DEBUG(cond) /* nothing */
#else
    #include <boost/assert.hpp>
    // Extra parenthesis around BOOST_ASSERT to be safe because its is a macro.
    #define BOOST_CONTRACT_DETAIL_DEBUG(cond) (BOOST_ASSERT(cond))
#endif

#endif // #include guard


/* debug.hpp
oHPiR3RM+OiX8Nct0XLkz9cvcW+nX65jYmXTfEDTr+nX9Gv6Nf2afk2/pl/T71f+/abn/8tmlv9a5/+v8oz91+seoUqbV35YAZ136XV5nrE/17Z2sDc7F/mb4nc4e21LfMf9xGXG7IUNe5eJ0D3vu1nch9hi56/WBdj9dQCYuMy3AYz+XN2TLO4TbWdvbTTmn9z1YRdRLB5Xbu/wO9yZcIP4GWjnsXOpQWZrWvezc9CCqDrn
*/