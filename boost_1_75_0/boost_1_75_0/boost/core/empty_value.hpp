/*
Copyright 2018 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_EMPTY_VALUE_HPP
#define BOOST_CORE_EMPTY_VALUE_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

#if defined(BOOST_GCC_VERSION) && (BOOST_GCC_VERSION >= 40700)
#define BOOST_DETAIL_EMPTY_VALUE_BASE
#elif defined(BOOST_INTEL) && defined(_MSC_VER) && (_MSC_VER >= 1800)
#define BOOST_DETAIL_EMPTY_VALUE_BASE
#elif defined(BOOST_MSVC) && (BOOST_MSVC >= 1800)
#define BOOST_DETAIL_EMPTY_VALUE_BASE
#elif defined(BOOST_CLANG) && !defined(__CUDACC__)
#if __has_feature(is_empty) && __has_feature(is_final)
#define BOOST_DETAIL_EMPTY_VALUE_BASE
#endif
#endif

namespace boost {

template<class T>
struct use_empty_value_base {
    enum {
#if defined(BOOST_DETAIL_EMPTY_VALUE_BASE)
        value = __is_empty(T) && !__is_final(T)
#else
        value = false
#endif
    };
};

struct empty_init_t { };

namespace empty_ {

template<class T, unsigned N = 0,
    bool E = boost::use_empty_value_base<T>::value>
class empty_value {
public:
    typedef T type;

#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    empty_value() = default;
#else
    empty_value() { }
#endif

    empty_value(boost::empty_init_t)
        : value_() { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class... Args>
    explicit empty_value(boost::empty_init_t, Args&&... args)
        : value_(std::forward<Args>(args)...) { }
#else
    template<class U>
    empty_value(boost::empty_init_t, U&& value)
        : value_(std::forward<U>(value)) { }
#endif
#else
    template<class U>
    empty_value(boost::empty_init_t, const U& value)
        : value_(value) { }

    template<class U>
    empty_value(boost::empty_init_t, U& value)
        : value_(value) { }
#endif

    const T& get() const BOOST_NOEXCEPT {
        return value_;
    }

    T& get() BOOST_NOEXCEPT {
        return value_;
    }

private:
    T value_;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template<class T, unsigned N>
class empty_value<T, N, true>
    : T {
public:
    typedef T type;

#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    empty_value() = default;
#else
    empty_value() { }
#endif

    empty_value(boost::empty_init_t)
        : T() { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class... Args>
    explicit empty_value(boost::empty_init_t, Args&&... args)
        : T(std::forward<Args>(args)...) { }
#else
    template<class U>
    empty_value(boost::empty_init_t, U&& value)
        : T(std::forward<U>(value)) { }
#endif
#else
    template<class U>
    empty_value(boost::empty_init_t, const U& value)
        : T(value) { }

    template<class U>
    empty_value(boost::empty_init_t, U& value)
        : T(value) { }
#endif

    const T& get() const BOOST_NOEXCEPT {
        return *this;
    }

    T& get() BOOST_NOEXCEPT {
        return *this;
    }
};
#endif

} /* empty_ */

using empty_::empty_value;

BOOST_INLINE_CONSTEXPR empty_init_t empty_init = empty_init_t();

} /* boost */

#endif

/* empty_value.hpp
KNu9SG6e5wTk9RAbBeJvjeLmGnDt60wUN8cfAH9DIa4J8j4PaZfB++BB3HxzwWhu3mAUlK8W8rwVxc2tFozh5tsOQp67Ic5BzAPeA4CXsxBM8O4FdZYG9MOgE6yE/PzhPSCCm9/ygjQS+KuHOpgzgJuDdB/DzaniOmk2dOTdkRZd50WMm7KMyjRDWZqiaKqiRJWkLkSZQVwH6e3fEwEZq9JrdNMVhRpVhqpcr1GYVHK54EO2kz77jHUcuVzwI72lYZubpJ+uF+EdSXpHhCTGyuUCPw7k+C19lkIjxHEjb5yPVRuB6vQURbnKnNaFfP92ksJQokos0mnlchH8N09ZuUKjaQJ3JkedElQafbxao7LQX+yOMKQv+Li+0qeeRJ5jdBqNqsik1mllFYVGlUnAO5DPahJNqnLBN2pDduycoJpu5t+RfDjSoDJVKjRy+TI+jZf0fB/Mk8sJODCpDALOiZQ7JitMRaUqoyiPt/qlFpYBeQtfjmTVDC69XBTvxZFcbpZ4bsTxIfCTWsxnIMDbEklljK5CC8nlgn/eTjqrDfI1TmVKUVXFaSvKLThnUh2Vz0MFek7kZJkQ0VIf0w4CPaMwljuR5GD4ZnGEenYil4rTNBUliVqjWW4c8EQVtL2Qd1vSb6ceG17OyRZ2K1dye2a6TmeK12mUWEalOb8xqXFKtUln4PI7ZIdj7WDnuEqV1mTk4uEcjSPZezVN
*/