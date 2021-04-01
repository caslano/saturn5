
#ifndef BOOST_CONTRACT_DETAIL_CONFIG_HPP_
#define BOOST_CONTRACT_DETAIL_CONFIG_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/preprocessor/cat.hpp>

// Turn off BOOST_ASSERT(...) in lib's implementation (always on by default).
// BOOST_CONTRACT_DETAIL_NDEBUG

#ifndef BOOST_CONTRACT_DETAIL_NAME_INFIX
    // Do not use underscore "_" to avoid generating reserved names with "__".
    #define BOOST_CONTRACT_DETAIL_NAME_INFIX X
#endif

#ifndef BOOST_CONTRACT_DETAIL_NAME_PREFIX
    #define BOOST_CONTRACT_DETAIL_NAME_PREFIX \
        BOOST_PP_CAT(boost_contract_detail, BOOST_CONTRACT_DETAIL_NAME_INFIX)
#endif

#endif // #include guard


/* config.hpp
Sentk1PueBTkkSP59Vsr35fI7sxg3NAma/r913jxK0Ek+ALFb8Ig3cfpkrF5PNnlrNSMfVQDtb4zem7vEMj/H9YlWvqr19t7tI1xGVB6naeNxK29dF7MuTKWyZ+LPZgKzgPGlJxZrm+lbqM97seJF56uHBIr54w+Ef8jyYSlJgqvCFA/bAsnzlLy/asXhwARh+4fOPeW8CErr8X7CF30N+BcmSta5lxclcC7IuvHaTF42kS6wcXTLfliXhwGzN8j6P8g/J9VRjFS+2tBXZD7cuDquXuI8CkEy6OdKvXehRsMPK40OgbfzgchdFiP1wZP11ar4q05yN5PwuvJJTx3dp7OHBxTlcOHcB47tSYX1mgWhtRl3fVrY7VwRkoqi2YuzTymcy0fzptuB8ZSkHlF0GRcJLUtzLw6D1QNHQv6+qoNHD5QDWcUYBR3rr5VztTHOnLdvTkrum9QyJL7DzDzJB802tEOvaRXjw4Y8the9ArYbSMcKg1QkuaGuuJ4eLhImTxGIdlsQN2IDx7V6bEIwRq2lya+F7qk1Wwmib79N3jPGhGJUVcRwaHxQA==
*/