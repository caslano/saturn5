#ifndef BOOST_NUMERIC_SAFE_BASE_HPP
#define BOOST_NUMERIC_SAFE_BASE_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <limits>
#include <type_traits> // is_integral, enable_if, conditional is_convertible
#include <boost/config.hpp> // BOOST_CLANG
#include "concept/exception_policy.hpp"
#include "concept/promotion_policy.hpp"

#include "safe_common.hpp"
#include "exception_policies.hpp"

#include "boost/concept/assert.hpp"

namespace boost {
namespace safe_numerics {

/////////////////////////////////////////////////////////////////
// forward declarations to support friend function declarations
// in safe_base

template<
    class Stored,
    Stored Min,
    Stored Max,
    class P, // promotion polic
    class E  // exception policy
>
class safe_base;

template<
    class T,
    T Min,
    T Max,
    class P,
    class E
>
struct is_safe<safe_base<T, Min, Max, P, E> > : public std::true_type
{};

template<
    class T,
    T Min,
    T Max,
    class P,
    class E
>
struct get_promotion_policy<safe_base<T, Min, Max, P, E> > {
    using type = P;
};

template<
    class T,
    T Min,
    T Max,
    class P,
    class E
>
struct get_exception_policy<safe_base<T, Min, Max, P, E> > {
    using type = E;
};

template<
    class T,
    T Min,
    T Max,
    class P,
    class E
>
struct base_type<safe_base<T, Min, Max, P, E> > {
    using type = T;
};

template<
    class T,
    T Min,
    T Max,
    class P,
    class E
>
constexpr T base_value(
    const safe_base<T, Min, Max, P, E>  & st
) {
    return static_cast<T>(st);
}

template<
    typename T,
    T N,
    class P, // promotion policy
    class E  // exception policy
>
class safe_literal_impl;

// works for both GCC and clang
#if BOOST_CLANG==1
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmismatched-tags"
#endif

/////////////////////////////////////////////////////////////////
// Main implementation

// note in the current version of the library, it is a requirement than type
// type "Stored" be a scalar type.  Problem is when violates this rule, the error message (on clang)
// is "A non-type template parameter cannot have type ... " where ... is some non-scalar type
// The example which triggered this investigation is safe<safe<int>> .  It was difficult to make
// the trip from the error message to the source of the problem, hence we're including this
// comment here.
template<
    class Stored,
    Stored Min,
    Stored Max,
    class P, // promotion polic
    class E  // exception policy
>
class safe_base {
private:
    BOOST_CONCEPT_ASSERT((PromotionPolicy<P>));
    BOOST_CONCEPT_ASSERT((ExceptionPolicy<E>));
    Stored m_t;

    template<class T>
    constexpr Stored validated_cast(const T & t) const;

    // stream support

    template<class CharT, class Traits>
    void output(std::basic_ostream<CharT, Traits> & os) const;

    // note usage of friend declaration to mark function as
    // a global function rather than a member function.  If
    // this is not done, the compiler will confuse this with
    // a member operator overload on the << operator.  Weird
    // I know.  But it's documented here
    // http://en.cppreference.com/w/cpp/language/friend
    // under the heading "Template friend operators"
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> &
    operator<<(
        std::basic_ostream<CharT, Traits> & os,
        const safe_base & t
    ){
        t.output(os);
        return os;
    }

    template<class CharT, class Traits>
    void input(std::basic_istream<CharT, Traits> & is);

    // see above
    template<class CharT, class Traits>
    friend inline std::basic_istream<CharT, Traits> &
    operator>>(
        std::basic_istream<CharT, Traits> & is,
        safe_base & t
    ){
        t.input(is);
        return is;
    }
    
public:
    ////////////////////////////////////////////////////////////
    // constructors

    constexpr safe_base();

    struct skip_validation{};

    constexpr explicit safe_base(const Stored & rhs, skip_validation);

    // construct an instance of a safe type from an instance of a convertible underlying type.
    template<
        class T,
        typename std::enable_if<
            std::is_convertible<T, Stored>::value,
            bool
        >::type = 0
    >
    constexpr /*explicit*/ safe_base(const T & t);

    // construct an instance of a safe type from a literal value
    template<typename T, T N, class Px, class Ex>
    constexpr /*explicit*/ safe_base(const safe_literal_impl<T, N, Px, Ex> & t);

    // note: Rule of Five. Supply all or none of the following
    // a) user-defined destructor
    ~safe_base() = default;
    // b) copy-constructor
    constexpr safe_base(const safe_base &) = default;
    // c) copy-assignment
    constexpr safe_base & operator=(const safe_base &) = default;
    // d) move constructor
    constexpr safe_base(safe_base &&) = default;
    // e) move assignment operator
    constexpr safe_base & operator=(safe_base &&) = default;

    /////////////////////////////////////////////////////////////////
    // casting operators for intrinsic integers
    // convert to any type which is not safe.  safe types need to be
    // excluded to prevent ambiguous function selection which
    // would otherwise occur.  validity of safe types is checked in
    // the constructor of safe types
    template<
        class R,
        typename std::enable_if<
            ! boost::safe_numerics::is_safe<R>::value,
            int
        >::type = 0
    >
    constexpr /*explicit*/ operator R () const;

    /////////////////////////////////////////////////////////////////
    // modification binary operators
    template<class T>
    constexpr safe_base &
    operator=(const T & rhs){
        m_t = validated_cast(rhs);
        return *this;
    }

    // mutating unary operators
    constexpr safe_base & operator++(){      // pre increment
        return *this = *this + 1;
    }
    constexpr safe_base & operator--(){      // pre decrement
        return *this = *this - 1;
    }
    constexpr safe_base operator++(int){   // post increment
        safe_base old_t = *this;
        ++(*this);
        return old_t;
    }
    constexpr safe_base operator--(int){ // post decrement
        safe_base old_t = *this;
        --(*this);
        return old_t;
    }
    // non mutating unary operators
    constexpr auto operator+() const { // unary plus
        return *this;
    }
    // after much consideration, I've permited the resulting value of a unary
    // - to change the type.  The C++ standard does invoke integral promotions
    // so it's changing the type as well.

    /*  section 5.3.1 &8 of the C++ standard
    The operand of the unary - operator shall have arithmetic or unscoped
    enumeration type and the result is the negation of its operand. Integral
    promotion is performed on integral or enumeration operands. The negative
    of an unsigned quantity is computed by subtracting its value from 2n,
    where n is the number of bits in the promoted operand. The type of the
    result is the type of the promoted operand.
    */
    constexpr auto operator-() const { // unary minus
        // if this is a unsigned type and the promotion policy is native
        // the result will be unsigned. But then the operation will fail
        // according to the requirements of arithmetic correctness.
        // if this is an unsigned type and the promotion policy is automatic.
        // the result will be signed.
        return 0 - *this;
    }
    /*   section 5.3.1 &10 of the C++ standard
    The operand of ~ shall have integral or unscoped enumeration type; 
    the result is the ones’ complement of its operand. Integral promotions 
    are performed. The type of the result is the type of the promoted operand.
    */
    constexpr auto operator~() const { // complement
        return ~Stored(0u) ^ *this;
    }
};

} // safe_numerics
} // boost

/////////////////////////////////////////////////////////////////
// numeric limits for safe<int> etc.

#include <limits>

namespace std {

template<
    class T,
    T Min,
    T Max,
    class P,
    class E
>
class numeric_limits<boost::safe_numerics::safe_base<T, Min, Max, P, E> >
    : public std::numeric_limits<T>
{
    using SB = boost::safe_numerics::safe_base<T, Min, Max, P, E>;
public:
    constexpr static SB lowest() noexcept {
        return SB(Min, typename SB::skip_validation());
    }
    constexpr static SB min() noexcept {
        return SB(Min, typename SB::skip_validation());
    }
    constexpr static SB max() noexcept {
        return SB(Max, typename SB::skip_validation());
    }
};

} // std

#if BOOST_CLANG==1
#pragma GCC diagnostic pop
#endif

#endif // BOOST_NUMERIC_SAFE_BASE_HPP

/* safe_base.hpp
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
*/