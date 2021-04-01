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
Y7rJTZ7QjrHi9V2EtfUsZjdvyRu2MFnLAS8OwuTRg5bZ10Vjmzt4DFGNhvSB/z+TJhV7oGleQZwhIx2KYmHG4YuAWK8q5VPIXOKdC9hF0KRu/lnGA88lrvlq/04sawaGecq5TIxMoz3qG2FQuNxad8v8NFx/s3psa5EoHHk1EhUlZv/SvjI2rRzt+EkCTYbtivCsWcmtcgC151yqwzRuwJck5dCvowV+Jju8jytnPwG6oxdUfb0A0oTvABge7trpCu0GNG0n6dPoN4hJ8eRKZjR9JSbJWD0Ek/H+sseVMO281w8eb2/ktRxZWF92jxmLMraET96/FDqCWHBNr4gJOl2d8j3BRy5pWJBV6nzzK0S8L9/ZUWQ5+uOdXOJtaFXd3AL756MdAYCIWnZNriX1Vf4GiPItjQGBwFjaJQVCaBFbdhsFHJPMnd/juqUh5TWrncVZMZO1+eY/wmYWxXdUfgl+L1qMXfVjIHWTH/1HF3fNsXMud0V6uMJ6ZFk4klMpwvgr2OWbAPdovUrQq22HlpR5PJ+AYUMpfmXG1F3p1M7fZbQr3pkrLUDYrw==
*/