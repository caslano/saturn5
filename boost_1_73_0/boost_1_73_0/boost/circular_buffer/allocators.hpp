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
197sdeEQ435r445GoIrCtywFzpbOkqcnOsgVA6kwk5ZmsT4QMiQ2CAGOENg0QFqL+NBV3bWK+7vz/3BPINVBsIWg4fFhGUcPy7ir2E5znG1377EAOE90aLcYyRzfUMnKO0wR8zvuc9alKgR9w8O1cfuXdxSlXRf7nZtYr8D7YTkMu7shAIe5G2VajM0K7RDwOGTVgxA94O9sujibzbL5cnyaz+bZMhtlE0abZDD+e/hpNhlHC8l3FQ0IJOSkYKkyjjybY1Y0LTju8Qq3oBq2LNTWiSsJ3XowOliMxzCcLDKajObw9fzhaYAfYJ3EMIAH11C/8s2xrvE9skox8xKu/AdQSwMECgAAAAgALWdKUvKaqtB9AwAAbgcAACoACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9lYXN5X3Jlc2V0LjNVVAUAAbZIJGCtVG1v2zYQ/q5fcdC+JIUi52XA2i4opjjeos2VDctpYcCAQIsniw1NCiJlx0V+/I6SjMTZgOZDZVgUj7zn7p57yHDpw7uf9nihg4MfPln7z+ih8eA0rfU3zO3/O2TZE3Q/clzS+IZQA3j2espO4U1eT3DSemV9rGv3nWVvCLd0SbrXwDkvM/dJls6z9x/qal+LdWnhZHgKFx8+
*/