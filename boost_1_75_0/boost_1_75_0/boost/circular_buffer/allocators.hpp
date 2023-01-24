// Copyright 2018 Glen Joseph Fernandes
// (glenjofe@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CIRCULAR_BUFFER_ALLOCATORS_HPP
#define BOOST_CIRCULAR_BUFFER_ALLOCATORS_HPP

#include <boost/config.hpp>
#if defined(BOOST_NO_CXX11_ALLOCATOR)
#define BOOST_CB_NO_CXX11_ALLOCATOR
#elif defined(BOOST_LIBSTDCXX_VERSION) && (BOOST_LIBSTDCXX_VERSION < 40800)
#define BOOST_CB_NO_CXX11_ALLOCATOR
#endif
#if !defined(BOOST_CB_NO_CXX11_ALLOCATOR)
#include <memory>
#else
#include <new>
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost {
namespace cb_details {

#if !defined(BOOST_CB_NO_CXX11_ALLOCATOR)
using std::allocator_traits;
#else
template<class A>
struct allocator_traits {
    typedef typename A::value_type value_type;
    typedef typename A::pointer pointer;
    typedef typename A::const_pointer const_pointer;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    static size_type max_size(const A& a) BOOST_NOEXCEPT {
        return a.max_size();
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class U, class... Args>
    static void construct(const A&, U* ptr, Args&&... args) {
        ::new((void*)ptr) U(std::forward<Args>(args)...);
    }
#else
    template<class U, class V>
    static void construct(const A&, U* ptr, V&& value) {
        ::new((void*)ptr) U(std::forward<V>(value));
    }
#endif
#else
    template<class U, class V>
    static void construct(const A&, U* ptr, const V& value) {
        ::new((void*)ptr) U(value);
    }

    template<class U, class V>
    static void construct(const A&, U* ptr, V& value) {
        ::new((void*)ptr) U(value);
    }
#endif

    template<class U>
    static void destroy(const A&, U* ptr) {
        (void)ptr;
        ptr->~U();
    }
};
#endif

} // cb_details
} // boost

#endif

/* allocators.hpp
F11l2mSiJmvMD0O0So5U9fzCHZorpntRVrT1I1i0nd0rkxY3hC5qLGAKoxXd+DuaJPIjzIn8HUZbj8LEHo345pLLfKBCovVEqYGKB3Eq+YJW6GgjWitKgQOEM3lA819KgZd6gFMEioKfVHSkTNDcC1Djc/iE+vD5HzU+37cZsK3xHn/4nIRpJ4oYkP5cVCc+Ly/xj8/iJqjlwyINPq+JVeNzy/6++Kzrr+Dz3/384rO1JFB8rtqjwecmtrrxWY13hePqx7uX99SBdzP3+ODdxP7Xg3e99gSCd3EJvnhXUK6CmTd/rxVmjo+tD2bOqWGmZwGs6JEifzDTDNM+3slg5qOddcLMvbv9w0zJRqjFuVMDM0/2UcNMRV9fmNnbV4GZwr5+YeZ/xYHCTF6xBmbKhwQOM0vH1A8zU4vrgJmBxT4w0++6YOZyUSAwYxzin1Yr53ULt4Jhv3BwGlgL82CqLZ/dLS/CIzo03+Z5DGRPE56iCbk0IUdJmEQTqM9TPk1JSKQJaTQhQUnoQRMSaEKMktCcJsTQhGgloWYXJkTThEgloYImRNIEs5RAPuE7M6HgBeUM8jNaQqCHkxU6pQS+SyXKVQnl6oT9qoT96oRiVYLatkp9ANpnl+oAlF+hJETQhBU0IVdVVa66qhxVgnJfkPOMTEuImx3taJyQMztatA7bpj0c3avWW6H2RdaJEmhguhEbR/7SyV8G57Zl
*/