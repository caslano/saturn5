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
XCvgGy5zvkJ33EBmTKl/HQziusoxk0GiYj2Iu1K4mVl/ltUCo1nzJ1ClAaOg1sIB0ndgrRKZ0oolQmFZr3KpM2cXFjoskoGqQIs8b+HQVArdpCAgbKvlkCaUGL00tGhVaPK2zdT6QBHL2gKldVWgOywL6iUKC+9AXSSisvq2EJ2Xtsq25N+5sl3sCagCo4KeF8Io7MGKa6kduB/NboP5DO696dTzZwsI3oPnL1q8u5F/g9yQ6LUC8VhWQmMUFch1mUuRHDj/oZ3O3NktXM+n42Ayi2idwxn03p5DgF2MpD7vQS+XK7p1+MX9+cw9RQF9RYLrp0gLQ/eLL1JJI1p4C773ccgOIZcneJUGcA9bzBEa6bFVDxd+MAlHIftJFnFeJwIuCb8hWvaOWahYofxzt306geMMKZAjEw5cOrBRMoHjUskC7/ToN+vrZhheT0eT2Sjw2YRjibGnOLQ6xAe69WU6QoRlOrFEUtXfNuamT7CN+FqQcttoK+Qqa9NxIRTGyOKBIA6i6Z8dEd5W5jndLva3NDm2xkZUlUwE29PHpdF22VfFxIpvwC/Tq3WtDW0xLCr4SqSKupmZihc6xbCJtgZnAXGKdRdr48IGbaZDU0/bWNJobDwsToGbSvDkRBUYNx1Zm0IZiFH/QbB9
*/