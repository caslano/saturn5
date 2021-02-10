
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONVERT_H
#define BOOST_FIBERS_DETAIL_CONVERT_H

#include <chrono>
#include <memory>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

inline
std::chrono::steady_clock::time_point convert(
        std::chrono::steady_clock::time_point const& timeout_time) noexcept {
    return timeout_time;
}

template< typename Clock, typename Duration >
std::chrono::steady_clock::time_point convert(
        std::chrono::time_point< Clock, Duration > const& timeout_time) {
    return std::chrono::steady_clock::now() + ( timeout_time - Clock::now() );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_CONVERT_H

/* convert.hpp
WWAVbpMI3YF97bjdUXvKIFsMZ7mDwoAFJbLZS0CyDSdtF7Jujdfz8thfThNnvpxO7QSCJuE4nMaOX1WQTGPSI0wT8sCoTFX6VUcMF47tczLzaYjC6ACHeEac4Sbr0IMP/iyaBo4nC6drJCsFb++0GZViD5tEFHs0OYR/Hfgy9fR4jQs0epbHb+9S+AhnbpYrLnGVDkx9cTPdlfct3C8fLX/R8zRx2+s4uDDYXWf8mqHEci9Tm9Fg+AhzW6U7ALahHm9J9T0NCOCSb72ab37AFO0iP47P8KYY6IOs4ebH/N4Rt197LQP8kWDuFRAvUWrvrnr30bOKM9nWu6X/HK8Qlhf+e38y9Q8n00mycvw8736s3L8pPPisF3Rbk7rg3vXWtlMvGm4vQM6tAJEo7hQI+ZtdcpnrjpKLIFku5vDeny4DZ8FRaFFZ6eRBGp6CKCzluaRfMbnbLyznp/PwbJ6GVr9pE7a3S8rUGy6TNDxOZ8EsXKxomW5lDle21TQ2vcjsPVVyVqN8sYx3sQziIAB/God49R0uHs4/yRgMsLuxhg8yY7f4dYibHf8DUEsDBAoAAAAIAC1nSlJ62Lt1xwQAAKsKAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9Q
*/