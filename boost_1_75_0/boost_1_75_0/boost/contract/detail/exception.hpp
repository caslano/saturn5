
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
fGUCk44H7do8O17M73LFYDtbyV3jqeijY2NP5Xc9zjXqQIuRMjqMC35yY7cbqJYVXBw+Oi2wgcWfoIvYCnNlU7f0+96kkaEwkZ32BcpMNJkE3VGEmDBLoiRtwmcqykb6LRqFHN18i2rHVDS4E6Ms2N4rn3p6rE+PyjxAMuERDVEeRejOCw2YdQFamiEE7TahcVnmJylVN3MkEqzFbidUJhjYzLifscSFR4h8cdzkbGho3JGtlTc3N9kkBMyPMN0NCZAUlpD7OD52nSOzaUDh9tVUYY2qyEWdt2f5yFh4aHnrb7Jc0R/h7Q2kyEohr66Mm7PVyVNRHRYkNePG0Bgt0yx/aN0qQNx52OZ5c7l6En2AU8Q562zsmignjptT6bMXBQjl9gkyq+3N2lPcwzY30bMOw3t9fHOGWqGzQzkMjgnBYp/gjenhKwuv7Jwsy0say82I5j+GHLklpB6hUxtaqkwi3KV5qIsCu09ai3TlzJi7KovGPtLzmWHOBmM5xxP36A4IVzkFaEuEBnS9MNxqSnggfFJSXaWgKtNE+TDRIYKrxE28xAYSgQwj615vzmcovLpttnNPity2fSTpHwxONR2IW5d6r/DFbMkzo4in00SkQ7TeWdjKK2tOUT/el98hc/xT64taeMdkOejRqlYscH702N3g1x9tDptXu+wymk5aR/VpbqCApju+io3nOXmmDgjlYQafETu8PPqx
*/