//  Copyright (C) 2011-2013, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_DETAIL_ATOMIC_HPP
#define BOOST_LOCKFREE_DETAIL_ATOMIC_HPP

#include <boost/config.hpp>

#ifndef BOOST_LOCKFREE_FORCE_STD_ATOMIC

#define BOOST_LOCKFREE_NO_HDR_ATOMIC

// MSVC supports atomic<> from version 2012 onwards.
#if defined(BOOST_MSVC) && (BOOST_MSVC >= 1700)
#undef BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif


// GCC supports atomic<> from version 4.8 onwards.
#if (BOOST_GCC >= 40800) && (__cplusplus >= 201103L)
#undef BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif


// Apple clang is 2 mayor versions ahead, but in fact 1 minor version behind
#ifdef BOOST_CLANG

#define BOOST_ATOMIC_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)

#if  defined(__apple_build_version__) && (BOOST_ATOMIC_CLANG_VERSION >= 60100) && (__cplusplus >= 201103L)
#undef BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif

#if !defined(__apple_build_version__) && (BOOST_ATOMIC_CLANG_VERSION >= 30600) && (__cplusplus >= 201103L)
#undef BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif

#undef BOOST_ATOMIC_CLANG_VERSION

#endif // BOOST_CLANG

// Stdlib should also be checked
#include <boost/config.hpp>
#if defined(BOOST_NO_CXX11_HDR_ATOMIC) && !defined(BOOST_LOCKFREE_NO_HDR_ATOMIC)
#  define BOOST_LOCKFREE_NO_HDR_ATOMIC
#endif

#endif // BOOST_LOCKFREE_FORCE_STD_ATOMIC


#if defined(BOOST_LOCKFREE_NO_HDR_ATOMIC) || defined(BOOST_LOCKFREE_FORCE_BOOST_ATOMIC)
#include <boost/atomic.hpp>
#else
#include <atomic>
#endif

namespace boost {
namespace lockfree {
namespace detail {

#if defined(BOOST_LOCKFREE_NO_HDR_ATOMIC) || defined(BOOST_LOCKFREE_FORCE_BOOST_ATOMIC)
using boost::atomic;
using boost::memory_order_acquire;
using boost::memory_order_consume;
using boost::memory_order_relaxed;
using boost::memory_order_release;
#else
using std::atomic;
using std::memory_order_acquire;
using std::memory_order_consume;
using std::memory_order_relaxed;
using std::memory_order_release;
#endif

}
using detail::atomic;
using detail::memory_order_acquire;
using detail::memory_order_consume;
using detail::memory_order_relaxed;
using detail::memory_order_release;

}}

#endif /* BOOST_LOCKFREE_DETAIL_ATOMIC_HPP */

/* atomic.hpp
VjKtf2S4l/sb/fPUvbKIqZe5E6973l6Pg6OVv9t4zx/Nd4e+4Ll2WashRcbjx9U9f2HZ/0di7sR0Y/wbZwXPWVfKmnIvYV7GcI4JzImefF0VuxyTpBxlDQpZJyUnaG0m0o2d5LGMa/U6Tq61mY7J+6YLMPGYDMxQZOronmCZWpC3XISqhkyZZIfrdTmoCHgkfw3ygV+jfJhkAb/hy0JQuIb1jDruxR1JaOJcLyjTn5d63RHK0cf5HHLr97L2n11eUc76pg7lRSSxIy/qUF7J2H2t17qROLrK8WvRM5gu5TgN0zCd8twbXI7qLulcH2Y5cr3Ow7mOsjGVo9PvQOU3v7i00KxboP1K3ntcZXOTlI2hXLnWLAOm93ni1/2c6/I1PNdav6VcXdvCCsjAK5T/HvXMnpoMzHWWt8jAQGWn8kvLgCpvyRd5F+WQC+xELkiXlimnTDwg6909Jt81P4IZab9LNsoET3iYMnGwDjJxsA4ycXBv+M+2029JVM01iBLVe6AS3vX4nO9ItXzNU+4+rf80Qp0Ptdra/nWYJcq/2lNKuY8JKUfV9iU4VOut9VPXjTW1H7qt+VClZSr55SUGXnOc9HvYpVrH6zx5p6/WbhT53C7yiaF9mqoEaVWhh4g6+xZ6XR25Rwe/PH/LNihceQ5Hdj+FX4Z8DxpaV6T9Yg/2c8Y9NSqr6tFX80c36fnZlSULQ+v2mN8vhtItOX3vR+u6x15d35vWVbfH/L421Hviuus+1XWPPf97XOnHSV83zfUet729rgDsAtvArrCDvL/tBLvB/vLedjDsCcfDXnA2TIOZ4j8L9oaFsA9cDfvCtaKzsw4OgJvgIFgJB8MqeC68W3R4fg6Hwocl3IOiy3MEjoQviv3HMEP3Teh3SfpilLs6lA5NPCyGneEy2A2WwqGwHE6CS2GG7S7hzgy0d3C6hBuLmSjhNpZwkyTc5vAs2NqxnsVg2BKeD1PhNNtdwt8dqHfhYxJ+E0ylhD9R1mk5H6bDqbAfnA8HwulwqugiYayZcCGcBYvEXwm8CJaJLtIyOBeuh9+TcsiU9/RZcBfMhQdgPnxEwhkr+/3lHoo96Z5/6N0oHZvdNjG2LsdYoy6OvHP/L9O/Ed2b2vRu6qRzo/RtviNdG9McgejX1NSt+ZZ6NW6dmnXITBXmEObtQ5G5hsgROSJH5IgckSNyRI7IETkiR+SIHJHjP/H4bub/C/PKF5z6/L89x/+aY++/jfK94GBMNGYQ5lN7gdm71JxNCV+4ZnL3eUSsaEmJf77m/TP1XIlxvoZr9VzJmHSLIxfP1XNtm5R7bz2P8DrxWdU0MI8Q/h5QxCNojjld0nRc1vfcj/Fg7sN8jN+KXcFpKi5Z4UhPblm5OT1yncfht6x0nnluGb/utJfZEdT7xD2i3NdY+WrviEmNNxFBe43XN8iD+p56Xl/TevEJ8bEJvvqW/o55V6Llzks9l3O7Cu8O60pb6x/jtSY3DswfHiXMNzFnNauZp7G15ankhcy3iB1pduXzTF4iB/RE4oUJLeGtwflcXrq4htwMkTmlDspvS99g3jL/jFB+jVbyME+sdYGnPh9YNmDN0MmsN9zUWuSNt7Zi9npTrWe89U3lJPf1uPdV0TooXWx3crm5tct6nPsYys8QBru4cKRIGBlV/v0O4iwf4cair9EZ45/buvw22+2X6iuTLrhfjNmCuQ1zP35Nc5DO+/mi1P2C9mJ4Tt2vkZ7fm638LzfOUTrD2ttVr+2gZe+Ecj+HeDcTO/aXU3Fuy3nDGjKWLzLWQ13X1LeL//tIx3FoeTzWEMxUzCLMBszTmHcxX2GSvHwRgumJGYaZgJmNyfXGWmvhJvgw/A0=
*/