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
25SpscVdKZzqqR2NscoQY/6+99hDO4NGOhnkFfujecXfoLdu4K7N3SFere2d9gvVjZjdnxWdx0918mF9B2LxMtQ3MW9WAH+BrAMPFdjjCLZKYN0K1pmt6rXAVs+3+nXUX4Tc6Fx9wSHy23/K6r5axC/Oj+Y1q5el9jsdjRDc6hhJc6nCrIdrQaMYM02ZeJxsedigcHrtLI7zp4Q0VlK7d+/Tt73UX+qCQsxmLz12/reKdm7q+K0iIxd/BeN+YTQeXHmk/W5pql7dx7nrY2ALbHBz6eYWU0j9zWvH44BHW2B0Ib71/ng2bdruO/EFPKAzM1POm38EfXl11H4blkGuNMltLKXcNsj3CSfOR5MbxcuZbh1gI9MO4YlqOATwcXlDlfnlgSaUp+f4MOhehzm+Em1e0aafWTvNovSIJ8IDO10StdMI6cQvi3c+PqncybDG99ao3B0sF836+tcb0S1pDEVrPobLodmtEc6Vd0T1H2W5aBbTf3yZ8f2U4v/TLfZ+/RVR3Z5CuvEr9uzPpxPNvPhiSfDt/V6Oq/dsOSnE4t57o+v001iuvAZ/aL5Yjfji+6P2OpNlVl1fVPPxGcB/8/76PcbXtLmuFXA/b1fB/PiB/wZ+tO8lpcfA2Lj36wcmPk8JvtP3+EUXeEJsHK6L6lIWWb7/+LrANw5Jl0rUJz4R1WVPJgvx6RD7Xo2Pw/VRebMiT7fq7LcWRF4S/82+z0bX3ZrIY39XflcH/G4P6IIPogbYbsyYzuN/8lf0tyW+GNWhoXSYzuN//b0qWq3upzMo4BRDjcN3de3Ogdl8AX/kMLUa0+F9gKgeF6LGqNopO/i/H/jMZfr7MvXThv7vB56j9N82MGguclBu8tyMJ07KOtW9FtX9xqju/7RypiqFhnMv+Dmin+wS7b7Ea6OKy7y+PW8Zf+9nP5vgPPXcgEY+78lNVliHm9JvAzOk3cefJ7rJ7tbk0HeAvqbGQSloXsSz/f0N43XV3OB+xbi0UxZ3Po2Vf0Z3AeE0S4u720Li6b2V+lJpl+7caS7fM2ijMmlbF3iZ2E4ddGFLO12q6+e2Obe7kP0OeikO/an4OWhQQklpSJc/ODaRHJLPaJhHPlEeka4/FwP+GMSBI0Dz5jb3fOK/+XD+3+7HvHD+yFCzDRYu1LoNDu944tCootIPpDjvlS5jGjuCmZ/efFyATz8ZzuZlRvda1kXNcxmZnDenXp/JS7F2Tr1R4JJiK49QGzaTh18S6imRNzeDS78N/lbhLaBN38DaUzG1kUsz/WCBJlxFjdEVgM1gjL6k2she/SqBHbfAwt4jsA8S3dUCW0907xfYCNFdI7BVRHedwEpE9wmBfZ1gXxXY+QS7UWD3J37fFtjtRHeTwM4m2M0Ceyy1vU1gfya62wV2PcHuENjvCPZngQ0R7N4naNirCPZAgS0luUcKbCfRLRHYPYjuYQK7iuhOBOzNgO0mulVC9w+iWyOwtxBsSGCzBNsssCbBhgV2C8G2Cew6gp0psNUESwT2YwVre+1K1H8IIZW+MOc5+rhYDvyRhcqnx3IDDdQZJpqoqubGEH9yKm6vbE3zFJRWJg+ACvMypGs2pksV3HXBolLciM/UW9AN4svK8mRKNjhdLRfA166BTCdvCFhmiD0BDSrCFcz5ySrKpxNdc+HBIGi/sTxVSkjdEz08Ykq+ljRnVJc8Xn6/JP6EhCuidK6NQpq9pRkMN9P4ug0nSbNUH6gUxzAq+ZkR/RxwnN+WoS3DRegEu89FM6rqvGXSfZVPUzowMIV0yxIyV8TceenB2PbHpx1HbTyJ0fp6bK+Xp5BZ4dUHq8D2Ojhw3+L0whR+2ZJmRxNfdxfALdqn7XA=
*/