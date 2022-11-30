#ifndef BOOST_SAFE_NUMERICS_INTERVAL_HPP
#define BOOST_SAFE_NUMERICS_INTERVAL_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <limits>
#include <cassert>
#include <type_traits>
#include <initializer_list>
#include <algorithm> // minmax, min, max

#include <boost/logic/tribool.hpp>

#include "utility.hpp" // log

// from stack overflow
// http://stackoverflow.com/questions/23815138/implementing-variadic-min-max-functions

namespace boost {
namespace safe_numerics {

template<typename R>
struct interval {
    const R l;
    const R u;

    template<typename T>
    constexpr interval(const T & lower, const T & upper) :
        l(lower),
        u(upper)
    {
        // assert(static_cast<bool>(l <= u));
    }
    template<typename T>
    constexpr interval(const std::pair<T, T> & p) :
        l(p.first),
        u(p.second)
    {}
    template<class T>
    constexpr interval(const interval<T> & rhs) :
        l(rhs.l),
        u(rhs.u)
    {}
    constexpr interval() :
        l(std::numeric_limits<R>::min()),
        u(std::numeric_limits<R>::max())
    {}
    // return true if this interval contains the given point
    constexpr tribool includes(const R & t) const {
        return l <= t && t <= u;
    }
    // if this interval contains every point found in some other inteval t
    //  return true
    // otherwise
    //  return false or indeterminate
    constexpr tribool includes(const interval<R> & t) const {
        return u >= t.u && l <= t.l;
    }

    // return true if this interval contains the given point
    constexpr tribool excludes(const R & t) const {
        return t < l || t > u;
    }
    // if this interval excludes every point found in some other inteval t
    //  return true
    // otherwise
    //  return false or indeterminate
    constexpr tribool excludes(const interval<R> & t) const {
        return t.u < l || u < t.l;
    }

};

template<class R>
constexpr inline interval<R> make_interval(){
    return interval<R>();
}
template<class R>
constexpr  inline interval<R> make_interval(const R &){
    return interval<R>();
}

// account for the fact that for floats and doubles
// the most negative value is called "lowest" rather
// than min
template<>
constexpr inline interval<float>::interval() :
    l(std::numeric_limits<float>::lowest()),
    u(std::numeric_limits<float>::max())
{}
template<>
constexpr inline interval<double>::interval() :
    l(std::numeric_limits<double>::lowest()),
    u(std::numeric_limits<double>::max())
{}

template<typename T>
constexpr inline interval<T> operator+(const interval<T> & t, const interval<T> & u){
    // adapted from https://en.wikipedia.org/wiki/Interval_arithmetic
    return {t.l + u.l, t.u + u.u};
}

template<typename T>
constexpr inline interval<T> operator-(const interval<T> & t, const interval<T> & u){
    // adapted from https://en.wikipedia.org/wiki/Interval_arithmetic
    return {t.l - u.u, t.u - u.l};
}

template<typename T>
constexpr inline interval<T> operator*(const interval<T> & t, const interval<T> & u){
    // adapted from https://en.wikipedia.org/wiki/Interval_arithmetic
    return utility::minmax<T>(
        std::initializer_list<T> {
            t.l * u.l,
            t.l * u.u,
            t.u * u.l,
            t.u * u.u
        }
    );
}

// interval division
// note: presumes 0 is not included in the range of the denominator
template<typename T>
constexpr inline interval<T> operator/(const interval<T> & t, const interval<T> & u){
    assert(static_cast<bool>(u.excludes(T(0))));
    return utility::minmax<T>(
        std::initializer_list<T> {
            t.l / u.l,
            t.l / u.u,
            t.u / u.l,
            t.u / u.u
        }
    );
}

// modulus of two intervals.  This will give a new range of for the modulus.
// note: presumes 0 is not included in the range of the denominator
template<typename T>
constexpr inline interval<T> operator%(const interval<T> & t, const interval<T> & u){
    assert(static_cast<bool>(u.excludes(T(0))));
    return utility::minmax<T>(
        std::initializer_list<T> {
            t.l % u.l,
            t.l % u.u,
            t.u % u.l,
            t.u % u.u
        }
    );
}

template<typename T>
constexpr inline interval<T> operator<<(const interval<T> & t, const interval<T> & u){
    //return interval<T>{t.l << u.l, t.u << u.u};
    return utility::minmax<T>(
        std::initializer_list<T> {
            t.l << u.l,
            t.l << u.u,
            t.u << u.l,
            t.u << u.u
        }
    );
}

template<typename T>
constexpr inline interval<T> operator>>(const interval<T> & t, const interval<T> & u){
    //return interval<T>{t.l >> u.u, t.u >> u.l};
    return utility::minmax<T>(
        std::initializer_list<T> {
            t.l >> u.l,
            t.l >> u.u,
            t.u >> u.l,
            t.u >> u.u
        }
    );
}

// union of two intervals
template<typename T>
constexpr interval<T> operator|(const interval<T> & t, const interval<T> & u){
    const T & rl = std::min(t.l, u.l);
    const T & ru = std::max(t.u, u.u);
    return interval<T>(rl, ru);
}

// intersection of two intervals
template<typename T>
constexpr inline interval<T> operator&(const interval<T> & t, const interval<T> & u){
    const T & rl = std::max(t.l, u.l);
    const T & ru = std::min(t.u, u.u);
    return interval<T>(rl, ru);
}

// determine whether two intervals intersect
template<typename T>
constexpr inline boost::logic::tribool intersect(const interval<T> & t, const interval<T> & u){
    return t.u >= u.l || t.l <= u.u;
}

template<typename T>
constexpr inline boost::logic::tribool operator<(
    const interval<T> & t,
    const interval<T> & u
){
    return
        // if every element in t is less than every element in u
        t.u < u.l ? boost::logic::tribool(true):
        // if every element in t is greater than every element in u
        t.l > u.u ? boost::logic::tribool(false):
        // otherwise some element(s) in t are greater than some element in u
        boost::logic::indeterminate
    ;
}

template<typename T>
constexpr inline boost::logic::tribool operator>(
    const interval<T> & t,
    const interval<T> & u
){
    return
        // if every element in t is greater than every element in u
        t.l > u.u ? boost::logic::tribool(true) :
        // if every element in t is less than every element in u
        t.u < u.l ? boost::logic::tribool(false) :
        // otherwise some element(s) in t are greater than some element in u
        boost::logic::indeterminate
    ;
}

template<typename T>
constexpr inline bool operator==(
    const interval<T> & t,
    const interval<T> & u
){
    // intervals have the same limits
    return t.l == u.l && t.u == u.u;
}

template<typename T>
constexpr inline bool operator!=(
    const interval<T> & t,
    const interval<T> & u
){
    return ! (t == u);
}

template<typename T>
constexpr inline boost::logic::tribool operator<=(
    const interval<T> & t,
    const interval<T> & u
){
    return ! (t > u);
}

template<typename T>
constexpr inline boost::logic::tribool operator>=(
    const interval<T> & t,
    const interval<T> & u
){
    return ! (t < u);
}

} // safe_numerics
} // boost

#include <iosfwd>

namespace std {

template<typename CharT, typename Traits, typename T>
inline std::basic_ostream<CharT, Traits> &
operator<<(
    std::basic_ostream<CharT, Traits> & os,
    const boost::safe_numerics::interval<T> & i
){
    return os << '[' << i.l << ',' << i.u << ']';
}
template<typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits> &
operator<<(
    std::basic_ostream<CharT, Traits> & os,
    const boost::safe_numerics::interval<unsigned char> & i
){
    os << "[" << (unsigned)i.l << "," << (unsigned)i.u << "]";
    return os;
}

template<typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits> &
operator<<(
    std::basic_ostream<CharT, Traits> & os,
    const boost::safe_numerics::interval<signed char> & i
){
    os << "[" << (int)i.l << "," << (int)i.u << "]";
    return os;
}

} // std

#endif // BOOST_SAFE_NUMERICS_INTERVAL_HPP

/* interval.hpp
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
*/