
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
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
*/