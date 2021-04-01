
#ifndef BOOST_CONTRACT_DETAIL_EXCEPTION_HPP_
#define BOOST_CONTRACT_DETAIL_EXCEPTION_HPP_

// Copyright (C) 2008-2019 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/config.hpp>
#include <exception>

namespace boost { namespace contract { namespace detail {

// Using this instead of std::uncaught_exception() because
// std::uncaught_exception will be removed in C++20.
inline bool uncaught_exception() BOOST_NOEXCEPT {
    // Alternatively, this could just return `boost::core::uncaught_exceptions()
    // > 0` but that emulates the exception count which is not needed by this
    // lib (the implementation below is simpler and could be faster).
    #ifdef __cpp_lib_uncaught_exceptions
        return std::uncaught_exceptions() > 0;
    #else
        return std::uncaught_exception();
    #endif
}

} } } // namespace

#endif // #include guard


/* exception.hpp
bAXBrHsWbn3n2o+E58xBZ9Ag8wCm6VpvtxZlocQP7EKM2XMrT+bNXqacnTG+hxs9aM9PvVkfZwdCdPnW0GUmIE1V2P1FamN8EWJAdgPfLkiqQWfIcXrrr6Y5xNkf71Ov8L1dkM3t6eO0Q+a18iKD630DWghNtdSKBzPj8Q++a3k3tkkZSEpcHwxfGVEPUVrb/IRMlCsA5/tA6r6WWoghZiAjdJl/f3MvdmKgktR72vb4fPRQJuQVNwWCNFltYe8LznMt+8269j1dvRtBAU66XwUmUHg+wk+Av1Wz6WxlYNjkci+ffy/DHfMPnvDycwmEXtkkLNlGB3jnskHgofCoeBWYXmoRW4YZQ0SMc5yeucoNLw02dCJUv8IaQc9bN5XPVDEJzpoIU04Xdc75IOrtvqy9x0ULWoAOd590IS0TDt8unHfcLPlgRolbb+xTNct09UHVQFdVJd17KGnbeL8VK2j/+oZoA6P5RDu4WqjMd81lK9Q4qxI9tgam7zCyfOx7VhjBM5MXMLuj0NdzEwsZY6ub8YPZPO4Ik2+X1ecT4mYmaEqDWtJ7dDzFiw==
*/