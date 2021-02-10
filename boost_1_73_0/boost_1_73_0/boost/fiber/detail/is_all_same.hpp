
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_IS_ALL_SAME_H
#define BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename X, typename ... Y >
struct is_all_same;

template< typename X, typename Y0, typename ... Y >
struct is_all_same< X, Y0, Y ... > {
    static constexpr bool value =
        std::is_same< X, Y0 >::value && is_all_same< X, Y ... >::value;
};

template< typename X, typename Y0 >
struct is_all_same< X, Y0 > {
    static constexpr bool value = std::is_same< X, Y0 >::value;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

/* is_all_same.hpp
tM/x1NVL4AcHtIRTjTmqxFj3vrjTYOK1jDX8a1vo4z12anT6RCGe9bVwAP9ajxBNPw5p4xtWa8Edm2mxobcb2HjDaIigk4jNsDd4hnpb0XsGWu4YTR2AkzLFdPDUokQJqgAek+R2u8CSdvXI1GS9FZtSf4T9Uj43HE2wkTePTHPCr13H/ZiypqfdMfvQepBO10lnuH0km7vNsMvpuX5vB8qPxkyKgRuG53Qt9ORBUqMyJaCXPebQpacb19Bm33pSICubarf13+2Acj+744l7NJ6Mo6Xlpqn5cbE/2h1zx5lprhtYNlUlan2/rbdta3XDgzojucQy7Vpp7kWL+Qw+u5OFZ82RhhvNM52aF/tnwLO2mbDUPytSu9tYzM5m/vks9tuZqQ9RL9t0/1md4iKK/ZN46k39+VJv62uSRhjTY0VSh/OEY0ndj6yiUcUSNLH0Qs8DdxL6dBkdzW8BvhtW0KNxRQA/2NqJrf8BUEsDBAoAAAAIAC1nSlLlQtGgWwUAANgNAAA4AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9YWV9TU0xWRVJTSU9OLjNVVAUAAbZIJGCtVltvm0gUfudXHHlfnIri2Ol2e9tqaUI3qK6xDG5qyRLC
*/