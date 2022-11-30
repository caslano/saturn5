#ifndef BOOST_NUMERIC_SAFE_BASE_OPERATIONS_HPP
#define BOOST_NUMERIC_SAFE_BASE_OPERATIONS_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <limits>
#include <type_traits> // is_base_of, is_same, is_floating_point, conditional
#include <algorithm>   // max
#include <istream>
#include <ostream>
#include <utility> // declval

#include <boost/config.hpp>

#include <boost/core/enable_if.hpp> // lazy_enable_if
#include <boost/integer.hpp>
#include <boost/logic/tribool.hpp>

#include "concept/numeric.hpp"

#include "checked_integer.hpp"
#include "checked_result.hpp"
#include "safe_base.hpp"

#include "interval.hpp"
#include "utility.hpp"

#include <boost/mp11/utility.hpp> // mp_valid
#include <boost/mp11/function.hpp> // mp_and, mp_or

namespace boost {
namespace safe_numerics {

////////////////////////////////////////////////////////////////////////////////
// compile time error dispatcher

// note slightly baroque implementation of a compile time switch statement
// which instatiates only those cases which are actually invoked.  This is
// motivated to implement the "trap" functionality which will generate a syntax
// error if and only a function which might fail is called.

namespace dispatch_switch {

    template<class EP, safe_numerics_actions>
    struct dispatch_case {};

    template<class EP>
    struct dispatch_case<EP, safe_numerics_actions::uninitialized_value> {
        constexpr static void invoke(const safe_numerics_error & e, const char * msg){
            EP::on_uninitialized_value(e, msg);
        }
    };
    template<class EP>
    struct dispatch_case<EP, safe_numerics_actions::arithmetic_error> {
        constexpr static void invoke(const safe_numerics_error & e, const char * msg){
            EP::on_arithmetic_error(e, msg);
        }
    };
    template<class EP>
    struct dispatch_case<EP, safe_numerics_actions::implementation_defined_behavior> {
        constexpr static void invoke(const safe_numerics_error & e, const char * msg){
            EP::on_implementation_defined_behavior(e, msg);
        }
    };
    template<class EP>
    struct dispatch_case<EP, safe_numerics_actions::undefined_behavior> {
        constexpr static void invoke(const safe_numerics_error & e, const char * msg){
            EP::on_undefined_behavior(e, msg);
        }
    };

} // dispatch_switch

template<class EP, safe_numerics_error E>
constexpr inline void
dispatch(const char * msg){
    constexpr safe_numerics_actions a = make_safe_numerics_action(E);
    dispatch_switch::dispatch_case<EP, a>::invoke(E, msg);
}

template<class EP, class R>
class dispatch_and_return {
public:
    template<safe_numerics_error E>
    constexpr static checked_result<R> invoke(
        char const * const & msg
    ) {
        dispatch<EP, E>(msg);
        return checked_result<R>(E, msg);
    }
};

/////////////////////////////////////////////////////////////////
// validation

template<typename R, R Min, R Max, typename E>
struct validate_detail {
    using r_type = checked_result<R>;

    struct exception_possible {
        template<typename T>
        constexpr static R return_value(
            const T & t
        ){
            // INT08-C
            const r_type rx = heterogeneous_checked_operation<
                R,
                Min,
                Max,
                typename base_type<T>::type,
                dispatch_and_return<E, R>
            >::cast(t);

            return rx;
        }
    };
    struct exception_not_possible {
        template<typename T>
        constexpr static R return_value(
            const T & t
        ){
            return static_cast<R>(base_value(t));
        }
    };

    template<typename T>
    constexpr static R return_value(const T & t){
        constexpr const interval<r_type> t_interval{
            checked::cast<R>(base_value(std::numeric_limits<T>::min())),
            checked::cast<R>(base_value(std::numeric_limits<T>::max()))
        };
        constexpr const interval<r_type> r_interval{r_type(Min), r_type(Max)};

        static_assert(
            true != static_cast<bool>(r_interval.excludes(t_interval)),
            "can't cast from ranges that don't overlap"
        );
        return std::conditional<
            static_cast<bool>(r_interval.includes(t_interval)),
            exception_not_possible,
            exception_possible
        >::type::return_value(t);
    }
};

template<class Stored, Stored Min, Stored Max, class P, class E>
template<class T>
constexpr inline Stored safe_base<Stored, Min, Max, P, E>::
validated_cast(const T & t) const {
    return validate_detail<Stored,Min,Max,E>::return_value(t);
}

/////////////////////////////////////////////////////////////////
// constructors

// default constructor
template<class Stored, Stored Min, Stored Max, class P, class E>
constexpr inline /*explicit*/ safe_base<Stored, Min, Max, P, E>::safe_base(){
    static_assert(
        std::is_arithmetic<Stored>(),
        "currently, safe numeric base types must currently be arithmetic types"
    );
    dispatch<E, safe_numerics_error::uninitialized_value>(
        "safe values must be initialized"
    );
}
// construct an instance of a safe type from an instance of a convertible underlying type.
template<class Stored, Stored Min, Stored Max, class P, class E>
constexpr inline /*explicit*/ safe_base<Stored, Min, Max, P, E>::safe_base(
    const Stored & rhs,
    skip_validation
) :
    m_t(rhs)
{
    static_assert(
        std::is_arithmetic<Stored>(),
        "currently, safe numeric base types must currently be arithmetic types"
    );
}

// construct an instance from an instance of a convertible underlying type.
template<class Stored, Stored Min, Stored Max, class P, class E>
    template<
        class T,
        typename std::enable_if<
            std::is_convertible<T, Stored>::value,
            bool
        >::type
    >
constexpr inline /*explicit*/ safe_base<Stored, Min, Max, P, E>::safe_base(const T &t) :
    m_t(validated_cast(t))
{
    static_assert(
        std::is_arithmetic<Stored>(),
        "currently, safe numeric base types must currently be arithmetic types"
    );
}

// construct an instance of a safe type from a literal value
template<class Stored, Stored Min, Stored Max, class P, class E>
template<typename T, T N, class Px, class Ex>
constexpr inline /*explicit*/ safe_base<Stored, Min, Max, P, E>::safe_base(
    const safe_literal_impl<T, N, Px, Ex> & t
) :
    m_t(validated_cast(t))
{    static_assert(
        std::is_arithmetic<Stored>(),
        "currently, safe numeric base types must currently be arithmetic types"
    );
}

/////////////////////////////////////////////////////////////////
// casting operators

// cast to a builtin type from a safe type
template< class Stored, Stored Min, Stored Max, class P, class E>
template<
    class R,
    typename std::enable_if<
        ! boost::safe_numerics::is_safe<R>::value,
        int
    >::type
>
constexpr inline safe_base<Stored, Min, Max, P, E>::
operator R () const {
    // if static values don't overlap, the program can never function
    constexpr const interval<R> r_interval;
    constexpr const interval<Stored> this_interval(Min, Max);
    static_assert(
        ! r_interval.excludes(this_interval),
        "safe type cannot be constructed with this type"
    );
    return validate_detail<
        R,
        std::numeric_limits<R>::min(),
        std::numeric_limits<R>::max(),
        E
    >::return_value(m_t);
}

/////////////////////////////////////////////////////////////////
// binary operators

template<class T, class U>
struct common_exception_policy {
    static_assert(is_safe<T>::value || is_safe<U>::value,
        "at least one type must be a safe type"
    );

    using t_exception_policy = typename get_exception_policy<T>::type;
    using u_exception_policy = typename get_exception_policy<U>::type;

    static_assert(
        std::is_same<t_exception_policy, u_exception_policy>::value
        || std::is_same<t_exception_policy, void>::value
        || std::is_same<void, u_exception_policy>::value,
        "if the exception policies are different, one must be void!"
    );

    static_assert(
        ! (std::is_same<t_exception_policy, void>::value
        && std::is_same<void, u_exception_policy>::value),
        "at least one exception policy must not be void"
    );

    using type =
        typename std::conditional<
            !std::is_same<void, u_exception_policy>::value,
            u_exception_policy,
        typename std::conditional<
            !std::is_same<void, t_exception_policy>::value,
            t_exception_policy,
        //
            void
        >::type >::type;

    static_assert(
        !std::is_same<void, type>::value,
        "exception_policy is void"
    );
};

template<class T, class U>
struct common_promotion_policy {
    static_assert(is_safe<T>::value || is_safe<U>::value,
        "at least one type must be a safe type"
    );
    using t_promotion_policy = typename get_promotion_policy<T>::type;
    using u_promotion_policy = typename get_promotion_policy<U>::type;
    static_assert(
        std::is_same<t_promotion_policy, u_promotion_policy>::value
        ||std::is_same<t_promotion_policy, void>::value
        ||std::is_same<void, u_promotion_policy>::value,
        "if the promotion policies are different, one must be void!"
    );
    static_assert(
        ! (std::is_same<t_promotion_policy, void>::value
        && std::is_same<void, u_promotion_policy>::value),
        "at least one promotion policy must not be void"
    );

    using type =
        typename std::conditional<
            ! std::is_same<void, u_promotion_policy>::value,
            u_promotion_policy,
        typename std::conditional<
            ! std::is_same<void, t_promotion_policy>::value,
            t_promotion_policy,
        //
            void
        >::type >::type;

    static_assert(
        ! std::is_same<void, type>::value,
        "promotion_policy is void"
    );

};

// give the resultant base type, figure out what the final result
// type will be.  Note we currently need this because we support
// return of only safe integer types. Someday ..., we'll support
// all other safe types including float and user defined ones.

// helper - cast arguments to binary operators to a specified
// result type

template<class EP, class R, class T, class U>
constexpr inline static std::pair<R, R> casting_helper(const T & t, const U & u){
    using r_type = checked_result<R>;
    const r_type tx = heterogeneous_checked_operation<
        R,
        std::numeric_limits<R>::min(),
        std::numeric_limits<R>::max(),
        typename base_type<T>::type,
        dispatch_and_return<EP, R>
    >::cast(base_value(t));
    const R tr = tx.exception()
        ? static_cast<R>(t)
        : tx.m_contents.m_r;

    const r_type ux = heterogeneous_checked_operation<
        R,
        std::numeric_limits<R>::min(),
        std::numeric_limits<R>::max(),
        typename base_type<U>::type,
        dispatch_and_return<EP, R>
    >::cast(base_value(u));
    const R ur = ux.exception()
        ? static_cast<R>(u)
        : ux.m_contents.m_r;
    return std::pair<R, R>(tr, ur);
}

// Note: the following global operators will be found via
// argument dependent lookup.
namespace {
template<template<class...> class F, class T, class U >
using legal_overload =
    boost::mp11::mp_and<
        boost::mp11::mp_or< is_safe<T>, is_safe<U> >,
        boost::mp11::mp_valid<
            F,
            typename base_type<T>::type,
            typename base_type<U>::type
        >
    >;
} // anon

/////////////////////////////////////////////////////////////////
// addition

template<class T, class U>
struct addition_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template addition_result<T,U>::type;

    // if exception not possible
    constexpr static result_base_type
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            + static_cast<result_base_type>(base_value(u));
    }

    // if exception possible
    using exception_policy = typename common_exception_policy<T, U>::type;

    using r_type = checked_result<result_base_type>;

    constexpr static result_base_type
    return_value(const T & t, const U & u, std::true_type){
        const std::pair<result_base_type, result_base_type> r = casting_helper<
            exception_policy,
            result_base_type
        >(t, u);

        const r_type rx = checked_operation<
            result_base_type,
            dispatch_and_return<exception_policy, result_base_type>
        >::add(r.first, r.second);

        return
            rx.exception()
            ? r.first + r.second
            : rx.m_contents.m_r;
    }

    using r_type_interval_t = interval<r_type>;

    constexpr static const r_type_interval_t get_r_type_interval(){
        constexpr const r_type_interval_t t_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        };
        constexpr const r_type_interval_t u_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        };
        return t_interval + u_interval;
    }
    constexpr static const r_type_interval_t r_type_interval = get_r_type_interval();

    constexpr static const interval<result_base_type> return_interval{
        r_type_interval.l.exception()
            ? std::numeric_limits<result_base_type>::min()
            : static_cast<result_base_type>(r_type_interval.l),
        r_type_interval.u.exception()
            ? std::numeric_limits<result_base_type>::max()
            : static_cast<result_base_type>(r_type_interval.u)
    };

    constexpr static bool exception_possible(){
        if(r_type_interval.l.exception())
            return true;
        if(r_type_interval.u.exception())
            return true;
        if(! return_interval.includes(r_type_interval))
            return true;
        return false;
    }

    constexpr static auto rl = return_interval.l;
    constexpr static auto ru = return_interval.u;

public:
    using type =
        safe_base<
            result_base_type,
            rl,
            ru,
            promotion_policy,
            exception_policy
        >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            return_value(
                t,
                u,
                std::integral_constant<bool, exception_possible()>()
            ),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using addition_operator
    = decltype( std::declval<T const&>() + std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    legal_overload<addition_operator, T, U>::value,
    addition_result<T, U>
>::type
constexpr inline operator+(const T & t, const U & u){
    return addition_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<addition_operator, T, U>::value,
    T
>::type
constexpr inline operator+=(T & t, const U & u){
    t = static_cast<T>(t + u);
    return t;
}

/////////////////////////////////////////////////////////////////
// subtraction

template<class T, class U>
struct subtraction_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template subtraction_result<T, U>::type;

    // if exception not possible
    constexpr static result_base_type
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            - static_cast<result_base_type>(base_value(u));
    }

    // if exception possible
    using exception_policy = typename common_exception_policy<T, U>::type;

    using r_type = checked_result<result_base_type>;

    constexpr static result_base_type
    return_value(const T & t, const U & u, std::true_type){
        const std::pair<result_base_type, result_base_type> r = casting_helper<
            exception_policy,
            result_base_type
        >(t, u);

        const r_type rx = checked_operation<
            result_base_type,
            dispatch_and_return<exception_policy, result_base_type>
        >::subtract(r.first, r.second);

        return
            rx.exception()
            ? r.first + r.second
            : rx.m_contents.m_r;
    }
    using r_type_interval_t = interval<r_type>;

    constexpr static const r_type_interval_t get_r_type_interval(){
        constexpr const r_type_interval_t t_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr const r_type_interval_t u_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        return t_interval - u_interval;
    }
    constexpr static const r_type_interval_t r_type_interval = get_r_type_interval();

    constexpr static const interval<result_base_type> return_interval{
        r_type_interval.l.exception()
            ? std::numeric_limits<result_base_type>::min()
            : static_cast<result_base_type>(r_type_interval.l),
        r_type_interval.u.exception()
            ? std::numeric_limits<result_base_type>::max()
            : static_cast<result_base_type>(r_type_interval.u)
    };

    constexpr static bool exception_possible(){
        if(r_type_interval.l.exception())
            return true;
        if(r_type_interval.u.exception())
            return true;
        if(! return_interval.includes(r_type_interval))
            return true;
        return false;
    }

public:
    constexpr static auto rl = return_interval.l;
    constexpr static auto ru = return_interval.u;

    using type =
        safe_base<
            result_base_type,
            rl,
            ru,
            promotion_policy,
            exception_policy
        >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            return_value(
                t,
                u,
                std::integral_constant<bool, exception_possible()>()
            ),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using subtraction_operator
    = decltype( std::declval<T const&>() - std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    legal_overload<subtraction_operator, T, U>::value,
    subtraction_result<T, U>
>::type
constexpr inline operator-(const T & t, const U & u){
    return subtraction_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<subtraction_operator, T, U>::value,
    T
>::type
constexpr inline operator-=(T & t, const U & u){
    t = static_cast<T>(t - u);
    return t;
}

/////////////////////////////////////////////////////////////////
// multiplication

template<class T, class U>
struct multiplication_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template multiplication_result<T, U>::type;

    // if exception not possible
    constexpr static result_base_type
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            * static_cast<result_base_type>(base_value(u));
    }

    // if exception possible
    using exception_policy = typename common_exception_policy<T, U>::type;

    using r_type = checked_result<result_base_type>;
    
    constexpr static result_base_type
    return_value(const T & t, const U & u, std::true_type){
        const std::pair<result_base_type, result_base_type> r = casting_helper<
            exception_policy,
            result_base_type
        >(t, u);

        const r_type rx = checked_operation<
            result_base_type,
            dispatch_and_return<exception_policy, result_base_type>
        >::multiply(r.first, r.second);

        return
            rx.exception()
            ? r.first * r.second
            : rx.m_contents.m_r;
    }

    using r_type_interval_t = interval<r_type>;

    constexpr static r_type_interval_t get_r_type_interval(){
        constexpr const r_type_interval_t t_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr const r_type_interval_t u_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        return t_interval * u_interval;
    }

    constexpr static const r_type_interval_t r_type_interval = get_r_type_interval();

    constexpr static const interval<result_base_type> return_interval{
        r_type_interval.l.exception()
            ? std::numeric_limits<result_base_type>::min()
            : static_cast<result_base_type>(r_type_interval.l),
        r_type_interval.u.exception()
            ? std::numeric_limits<result_base_type>::max()
            : static_cast<result_base_type>(r_type_interval.u)
    };

    constexpr static bool exception_possible(){
        if(r_type_interval.l.exception())
            return true;
        if(r_type_interval.u.exception())
            return true;
        if(! return_interval.includes(r_type_interval))
            return true;
        return false;
    }

    constexpr static auto rl = return_interval.l;
    constexpr static auto ru = return_interval.u;

public:
    using type =
        safe_base<
            result_base_type,
            rl,
            ru,
            promotion_policy,
            exception_policy
        >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            return_value(
                t,
                u,
                std::integral_constant<bool, exception_possible()>()
            ),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using multiplication_operator
    = decltype( std::declval<T const&>() * std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    legal_overload<multiplication_operator, T, U>::value,
    multiplication_result<T, U>
>::type
constexpr inline operator*(const T & t, const U & u){
    return multiplication_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<multiplication_operator, T, U>::value,
    T
>::type
constexpr inline operator*=(T & t, const U & u){
    t = static_cast<T>(t * u);
    return t;
}

/////////////////////////////////////////////////////////////////
// division

// key idea here - result will never be larger than T
template<class T, class U>
struct division_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template division_result<T, U>::type;

    // if exception not possible
    constexpr static result_base_type
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            / static_cast<result_base_type>(base_value(u));
    }

    // if exception possible
    using exception_policy = typename common_exception_policy<T, U>::type;

    constexpr static const int bits = std::min(
        std::numeric_limits<std::uintmax_t>::digits,
        std::max(std::initializer_list<int>{
            std::numeric_limits<result_base_type>::digits,
            std::numeric_limits<typename base_type<T>::type>::digits,
            std::numeric_limits<typename base_type<U>::type>::digits
        }) + (std::numeric_limits<result_base_type>::is_signed ? 1 : 0)
    );

    using r_type = checked_result<result_base_type>;

    constexpr static result_base_type
    return_value(const T & t, const U & u, std::true_type){
        using temp_base = typename std::conditional<
            std::numeric_limits<result_base_type>::is_signed,
            typename boost::int_t<bits>::least,
            typename boost::uint_t<bits>::least
        >::type;
        using t_type = checked_result<temp_base>;

        const std::pair<t_type, t_type> r = casting_helper<
            exception_policy,
            temp_base
        >(t, u);

        const t_type rx = checked_operation<
            temp_base,
            dispatch_and_return<exception_policy, temp_base>
        >::divide(r.first, r.second);

        return
            rx.exception()
            ? r.first / r.second
            : rx;
    }
    using r_type_interval_t = interval<r_type>;

    constexpr static r_type_interval_t t_interval(){
        return r_type_interval_t{
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        };
    };

    constexpr static r_type_interval_t u_interval(){
        return r_type_interval_t{
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        };
    };

    constexpr static r_type_interval_t get_r_type_interval(){
        constexpr const r_type_interval_t t = t_interval();
        constexpr const r_type_interval_t u = u_interval();

        if(u.u < r_type(0) || u.l > r_type(0))
            return t / u;
        return utility::minmax(
            std::initializer_list<r_type> {
                t.l / u.l,
                t.l / r_type(-1),
                t.l / r_type(1),
                t.l / u.u,
                t.u / u.l,
                t.u / r_type(-1),
                t.u / r_type(1),
                t.u / u.u,
            }
        );
    }

    constexpr static const r_type_interval_t r_type_interval = get_r_type_interval();

    constexpr static const interval<result_base_type> return_interval{
        r_type_interval.l.exception()
            ? std::numeric_limits<result_base_type>::min()
            : static_cast<result_base_type>(r_type_interval.l),
        r_type_interval.u.exception()
            ? std::numeric_limits<result_base_type>::max()
            : static_cast<result_base_type>(r_type_interval.u)
    };

    constexpr static bool exception_possible(){
        constexpr const r_type_interval_t ri = get_r_type_interval();
        constexpr const r_type_interval_t ui = u_interval();
        return
            static_cast<bool>(ui.includes(r_type(0)))
            || ri.l.exception()
            || ri.u.exception();
    }

    constexpr static auto rl = return_interval.l;
    constexpr static auto ru = return_interval.u;

public:
    using type =
        safe_base<
            result_base_type,
            rl,
            ru,
            promotion_policy,
            exception_policy
        >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            return_value(
                t,
                u,
                std::integral_constant<bool, exception_possible()>()
            ),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using division_operator
    = decltype( std::declval<T const&>() / std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    legal_overload<division_operator, T, U>::value,
    division_result<T, U>
>::type
constexpr inline operator/(const T & t, const U & u){
    return division_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<division_operator, T, U>::value,
    T
>::type
constexpr inline operator/=(T & t, const U & u){
    t = static_cast<T>(t / u);
    return t;
}

/////////////////////////////////////////////////////////////////
// modulus

template<class T, class U>
struct modulus_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type = typename promotion_policy::template modulus_result<T, U>::type;

    // if exception not possible
    constexpr static result_base_type
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            % static_cast<result_base_type>(base_value(u));
    }

    // if exception possible
    using exception_policy = typename common_exception_policy<T, U>::type;

    constexpr static const int bits = std::min(
        std::numeric_limits<std::uintmax_t>::digits,
        std::max(std::initializer_list<int>{
            std::numeric_limits<result_base_type>::digits,
            std::numeric_limits<typename base_type<T>::type>::digits,
            std::numeric_limits<typename base_type<U>::type>::digits
        }) + (std::numeric_limits<result_base_type>::is_signed ? 1 : 0)
    );

    using r_type = checked_result<result_base_type>;

    constexpr static result_base_type
    return_value(const T & t, const U & u, std::true_type){
        using temp_base = typename std::conditional<
            std::numeric_limits<result_base_type>::is_signed,
            typename boost::int_t<bits>::least,
            typename boost::uint_t<bits>::least
        >::type;
        using t_type = checked_result<temp_base>;
        
        const std::pair<t_type, t_type> r = casting_helper<
            exception_policy,
            temp_base
        >(t, u);

        const t_type rx = checked_operation<
            temp_base,
            dispatch_and_return<exception_policy, temp_base>
        >::modulus(r.first, r.second);

        return
            rx.exception()
            ? r.first % r.second
            : rx;
    }

    using r_type_interval_t = interval<r_type>;

    constexpr static const r_type_interval_t t_interval(){
        return r_type_interval_t{
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        };
    };

    constexpr static const r_type_interval_t u_interval(){
        return r_type_interval_t{
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        };
    };

    constexpr static const r_type_interval_t get_r_type_interval(){
        constexpr const r_type_interval_t t = t_interval();
        constexpr const r_type_interval_t u = u_interval();

        if(u.u < r_type(0)
        || u.l > r_type(0))
            return t % u;
        return utility::minmax(
            std::initializer_list<r_type> {
                t.l % u.l,
                t.l % r_type(-1),
                t.l % r_type(1),
                t.l % u.u,
                t.u % u.l,
                t.u % r_type(-1),
                t.u % r_type(1),
                t.u % u.u,
            }
        );
    }

    constexpr static const r_type_interval_t r_type_interval = get_r_type_interval();

    constexpr static const interval<result_base_type> return_interval{
        r_type_interval.l.exception()
            ? std::numeric_limits<result_base_type>::min()
            : static_cast<result_base_type>(r_type_interval.l),
        r_type_interval.u.exception()
            ? std::numeric_limits<result_base_type>::max()
            : static_cast<result_base_type>(r_type_interval.u)
    };

    constexpr static bool exception_possible(){
        constexpr const r_type_interval_t ri = get_r_type_interval();
        constexpr const r_type_interval_t ui = u_interval();
        return
            static_cast<bool>(ui.includes(r_type(0)))
            || ri.l.exception()
            || ri.u.exception();
    }

    constexpr static auto rl = return_interval.l;
    constexpr static auto ru = return_interval.u;

public:
    using type =
        safe_base<
            result_base_type,
            rl,
            ru,
            promotion_policy,
            exception_policy
        >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            return_value(
                t,
                u,
                std::integral_constant<bool, exception_possible()>()
            ),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using modulus_operator
    = decltype( std::declval<T const&>() % std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    legal_overload<modulus_operator, T, U>::value,
    modulus_result<T, U>
>::type
constexpr inline operator%(const T & t, const U & u){
    // see https://en.wikipedia.org/wiki/Modulo_operation
    return modulus_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<modulus_operator, T, U>::value,
    T
>::type
constexpr inline operator%=(T & t, const U & u){
    t = static_cast<T>(t % u);
    return t;
}

/////////////////////////////////////////////////////////////////
// comparison

// less than

template<class T, class U>
struct less_than_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;

    using result_base_type =
        typename promotion_policy::template comparison_result<T, U>::type;

    // if exception not possible
    constexpr static bool
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            < static_cast<result_base_type>(base_value(u));
    }

    using exception_policy = typename common_exception_policy<T, U>::type;

    using r_type = checked_result<result_base_type>;

    // if exception possible
    constexpr static bool
    return_value(const T & t, const U & u, std::true_type){
        const std::pair<result_base_type, result_base_type> r = casting_helper<
            exception_policy,
            result_base_type
        >(t, u);

        return safe_compare::less_than(r.first, r.second);
    }

    using r_type_interval_t = interval<r_type>;

    constexpr static bool interval_open(const r_type_interval_t & t){
        return t.l.exception() || t.u.exception();
    }

public:
    constexpr static bool
    return_value(const T & t, const U & u){
        constexpr const r_type_interval_t t_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        };
        constexpr const r_type_interval_t u_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        if(t_interval < u_interval)
            return true;
        if(t_interval > u_interval)
            return false;

        constexpr bool exception_possible
            = interval_open(t_interval) || interval_open(u_interval);

        return return_value(
            t,
            u,
            std::integral_constant<bool, exception_possible>()
        );
    }
};

template<class T, class U> using less_than_operator
    = decltype( std::declval<T const&>() < std::declval<U const&>() );
template<class T, class U> using greater_than_operator
    = decltype( std::declval<T const&>() > std::declval<U const&>() );
template<class T, class U> using less_than_or_equal_operator
    = decltype( std::declval<T const&>() <= std::declval<U const&>() );
template<class T, class U> using greater_than_or_equal_operator
    = decltype( std::declval<T const&>() >= std::declval<U const&>() );

template<class T, class U>
typename std::enable_if<
    legal_overload<less_than_operator, T, U>::value,
    bool
>::type
constexpr inline operator<(const T & lhs, const U & rhs) {
    return less_than_result<T, U>::return_value(lhs, rhs);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<greater_than_operator, T, U>::value,
    bool
>::type
constexpr inline operator>(const T & lhs, const U & rhs) {
    return rhs < lhs;
}

template<class T, class U>
typename std::enable_if<
    legal_overload<greater_than_or_equal_operator, T, U>::value,
    bool
>::type
constexpr inline operator>=(const T & lhs, const U & rhs) {
    return ! ( lhs < rhs );
}

template<class T, class U>
typename std::enable_if<
    legal_overload<less_than_or_equal_operator, T, U>::value,
    bool
>::type
constexpr inline operator<=(const T & lhs, const U & rhs) {
    return ! ( lhs > rhs );
}

// equal

template<class T, class U>
struct equal_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;

    using result_base_type =
        typename promotion_policy::template comparison_result<T, U>::type;

    // if exception not possible
    constexpr static bool
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            == static_cast<result_base_type>(base_value(u));
    }

    using exception_policy = typename common_exception_policy<T, U>::type;

    using r_type = checked_result<result_base_type>;

    // exception possible
    constexpr static bool
    return_value(const T & t, const U & u, std::true_type){
        const std::pair<result_base_type, result_base_type> r = casting_helper<
            exception_policy,
            result_base_type
        >(t, u);

        return safe_compare::equal(r.first, r.second);
    }

    using r_type_interval = interval<r_type>;

    constexpr static bool interval_open(const r_type_interval & t){
        return t.l.exception() || t.u.exception();
    }

public:
    constexpr static bool
    return_value(const T & t, const U & u){
        constexpr const r_type_interval t_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr const r_type_interval u_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        if(! intersect(t_interval, u_interval))
            return false;

        constexpr bool exception_possible
            = interval_open(t_interval) || interval_open(u_interval);

        return return_value(
            t,
            u,
            std::integral_constant<bool, exception_possible>()
        );
    }
};

template<class T, class U> using equal_to_operator
    = decltype( std::declval<T const&>() == std::declval<U const&>() );
template<class T, class U> using not_equal_to_operator
    = decltype( std::declval<T const&>() != std::declval<U const&>() );

template<class T, class U>
typename std::enable_if<
    legal_overload<equal_to_operator, T, U>::value,
    bool
>::type
constexpr inline operator==(const T & lhs, const U & rhs) {
    return equal_result<T, U>::return_value(lhs, rhs);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<not_equal_to_operator, T, U>::value,
    bool
>::type
constexpr inline operator!=(const T & lhs, const U & rhs) {
    return ! (lhs == rhs);
}

/////////////////////////////////////////////////////////////////////////
// The following operators only make sense when applied to integet types

/////////////////////////////////////////////////////////////////////////
// shift operators

// left shift
template<class T, class U>
struct left_shift_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template left_shift_result<T, U>::type;

    // if exception not possible
    constexpr static result_base_type
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            << static_cast<result_base_type>(base_value(u));
    }

    // exception possible
    using exception_policy = typename common_exception_policy<T, U>::type;
    
    using r_type = checked_result<result_base_type>;

    constexpr static result_base_type
    return_value(const T & t, const U & u, std::true_type){
        const std::pair<result_base_type, result_base_type> r = casting_helper<
            exception_policy,
            result_base_type
        >(t, u);

        const r_type rx = checked_operation<
            result_base_type,
            dispatch_and_return<exception_policy, result_base_type>
        >::left_shift(r.first, r.second);

        return
            rx.exception()
            ? r.first << r.second
            : rx.m_contents.m_r;
    }

    using r_type_interval_t = interval<r_type>;

    constexpr static r_type_interval_t get_r_type_interval(){
        constexpr const r_type_interval_t t_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr const r_type_interval_t u_interval{
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        };
        return (t_interval << u_interval);
    }

    constexpr static const r_type_interval_t r_type_interval = get_r_type_interval();

    constexpr static const interval<result_base_type> return_interval{
        r_type_interval.l.exception()
            ? std::numeric_limits<result_base_type>::min()
            : static_cast<result_base_type>(r_type_interval.l),
        r_type_interval.u.exception()
            ? std::numeric_limits<result_base_type>::max()
            : static_cast<result_base_type>(r_type_interval.u)
    };

    constexpr static bool exception_possible(){
        if(r_type_interval.l.exception())
            return true;
        if(r_type_interval.u.exception())
            return true;
        if(! return_interval.includes(r_type_interval))
            return true;
        return false;
    }

    constexpr static const auto rl = return_interval.l;
    constexpr static const auto ru = return_interval.u;

public:
    using type =
        safe_base<
            result_base_type,
            rl,
            ru,
            promotion_policy,
            exception_policy
        >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            return_value(
                t,
                u,
                std::integral_constant<bool, exception_possible()>()
            ),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using left_shift_operator
    = decltype( std::declval<T const&>() << std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    // exclude usage of << for file input here
    boost::safe_numerics::Numeric<T>()
    && legal_overload<left_shift_operator, T, U>::value,
    left_shift_result<T, U>
>::type
constexpr inline operator<<(const T & t, const U & u){
    // INT13-CPP
    // C++ standards document N4618 & 5.8.2
    return left_shift_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    // exclude usage of << for file output here
    boost::safe_numerics::Numeric<T>()
    && legal_overload<left_shift_operator, T, U>::value,
    T
>::type
constexpr inline operator<<=(T & t, const U & u){
    t = static_cast<T>(t << u);
    return t;
}

template<class T, class CharT, class Traits> using stream_output_operator
    = decltype( std::declval<std::basic_ostream<CharT, Traits> &>() >> std::declval<T const&>() );

template<class T, class CharT, class Traits>
typename boost::lazy_enable_if_c<
    boost::mp11::mp_valid< stream_output_operator, T, CharT, Traits>::value,
    std::basic_ostream<CharT, Traits> &
>::type
constexpr inline operator>>(
    std::basic_ostream<CharT, Traits> & os,
    const T & t
){
    // INT13-CPP
    // C++ standards document N4618 & 5.8.2
    t.output(os);
    return os;
}

/////////////////////////////////////////////////////////////////
// right shift
template<class T, class U>
struct right_shift_result {
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template right_shift_result<T, U>::type;

    // if exception not possible
    constexpr static result_base_type
    return_value(const T & t, const U & u, std::false_type){
        return
            static_cast<result_base_type>(base_value(t))
            >> static_cast<result_base_type>(base_value(u));
    }

    // exception possible
    using exception_policy = typename common_exception_policy<T, U>::type;

    using r_type = checked_result<result_base_type>;

    constexpr static result_base_type
    return_value(const T & t, const U & u, std::true_type){
        const std::pair<result_base_type, result_base_type> r = casting_helper<
            exception_policy,
            result_base_type
        >(t, u);

        const r_type rx = checked_operation<
            result_base_type,
            dispatch_and_return<exception_policy, result_base_type>
        >::right_shift(r.first, r.second);

        return
            rx.exception()
            ? r.first >> r.second
            : rx.m_contents.m_r;
    }

    using r_type_interval_t = interval<r_type>;

    constexpr static r_type_interval_t t_interval(){
        return r_type_interval_t(
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<T>::max()))
        );
    };

    constexpr static r_type_interval_t u_interval(){
        return r_type_interval_t(
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<result_base_type>(base_value(std::numeric_limits<U>::max()))
        );
    }
    constexpr static r_type_interval_t get_r_type_interval(){;
        return (t_interval() >> u_interval());
    }

    constexpr static const r_type_interval_t r_type_interval = get_r_type_interval();

    constexpr static const interval<result_base_type> return_interval{
        r_type_interval.l.exception()
            ? std::numeric_limits<result_base_type>::min()
            : static_cast<result_base_type>(r_type_interval.l),
        r_type_interval.u.exception()
            ? std::numeric_limits<result_base_type>::max()
            : static_cast<result_base_type>(r_type_interval.u)
    };

    constexpr static bool exception_possible(){
        constexpr const r_type_interval_t ri = r_type_interval;
        constexpr const r_type_interval_t ti = t_interval();
        constexpr const r_type_interval_t ui = u_interval();
        return static_cast<bool>(
            // note undesirable coupling with checked::shift right here !
            ui.u > checked_result<result_base_type>(
                std::numeric_limits<result_base_type>::digits
            )
            || ti.l < checked_result<result_base_type>(0)
            || ui.l < checked_result<result_base_type>(0)
            || ri.l.exception()
            || ri.u.exception()
        );
    }

    constexpr static auto rl = return_interval.l;
    constexpr static auto ru = return_interval.u;

public:
    using type =
        safe_base<
            result_base_type,
            rl,
            ru,
            promotion_policy,
            exception_policy
        >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            return_value(
                t,
                u,
                std::integral_constant<bool, exception_possible()>()
            ),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using right_shift_operator
    = decltype( std::declval<T const&>() >> std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    // exclude usage of >> for file input here
    boost::safe_numerics::Numeric<T>()
    && legal_overload<right_shift_operator, T, U>::value,
    right_shift_result<T, U>
>::type
constexpr inline operator>>(const T & t, const U & u){
    // INT13-CPP
    // C++ standards document N4618 & 5.8.2
    return right_shift_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    // exclude usage of << for file output here
    boost::safe_numerics::Numeric<T>()
    && legal_overload<right_shift_operator, T, U>::value,
    T
>::type
constexpr inline operator>>=(T & t, const U & u){
    t = static_cast<T>(t >> u);
    return t;
}

template<class T, class CharT, class Traits> using stream_input_operator
    = decltype( std::declval<std::basic_istream<CharT, Traits> &>() >> std::declval<T const&>() );

template<class T, class CharT, class Traits>
typename boost::lazy_enable_if_c<
    boost::mp11::mp_valid< stream_input_operator, T, CharT, Traits>::value,
    std::basic_istream<CharT, Traits> &
>::type
constexpr inline operator>>(
    std::basic_istream<CharT, Traits> & is,
    const T & t
){
    // INT13-CPP
    // C++ standards document N4618 & 5.8.2
    t.input(is);
    return is;
}

/////////////////////////////////////////////////////////////////
// bitwise operators

// operator |
template<class T, class U>
struct bitwise_or_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template bitwise_or_result<T, U>::type;

    // according to the C++ standard, the bitwise operators are executed as if
    // the operands are consider a logical array of bits.  That is, there is no
    // sense that these are signed numbers.

    using r_type = typename std::make_unsigned<result_base_type>::type;
    using r_type_interval_t = interval<r_type>;
    using exception_policy = typename common_exception_policy<T, U>::type;

public:
    // lazy_enable_if_c depends on this
    using type = safe_base<
        result_base_type,
        //r_interval.l,
        r_type(0),
        //r_interval.u,
        utility::round_out(
            std::max(
                static_cast<r_type>(base_value(std::numeric_limits<T>::max())),
                static_cast<r_type>(base_value(std::numeric_limits<U>::max()))
            )
        ),
        promotion_policy,
        exception_policy
    >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            static_cast<result_base_type>(base_value(t))
            | static_cast<result_base_type>(base_value(u)),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using bitwise_or_operator
    = decltype( std::declval<T const&>() | std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    legal_overload<bitwise_or_operator, T, U>::value,
    bitwise_or_result<T, U>
>::type
constexpr inline operator|(const T & t, const U & u){
    return bitwise_or_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<bitwise_or_operator, T, U>::value,
    T
>::type
constexpr inline operator|=(T & t, const U & u){
    t = static_cast<T>(t | u);
    return t;
}

// operator &
template<class T, class U>
struct bitwise_and_result {
private:
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template bitwise_and_result<T, U>::type;

    // according to the C++ standard, the bitwise operators are executed as if
    // the operands are consider a logical array of bits.  That is, there is no
    // sense that these are signed numbers.

    using r_type = typename std::make_unsigned<result_base_type>::type;
    using r_type_interval_t = interval<r_type>;
    using exception_policy = typename common_exception_policy<T, U>::type;

public:
    // lazy_enable_if_c depends on this
    using type = safe_base<
        result_base_type,
        //r_interval.l,
        r_type(0),
        //r_interval.u,
        utility::round_out(
            std::min(
                static_cast<r_type>(base_value(std::numeric_limits<T>::max())),
                static_cast<r_type>(base_value(std::numeric_limits<U>::max()))
            )
        ),
        promotion_policy,
        exception_policy
    >;
    
    constexpr static type return_value(const T & t, const U & u){
        return type(
            static_cast<result_base_type>(base_value(t))
            & static_cast<result_base_type>(base_value(u)),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using bitwise_and_operator
    = decltype( std::declval<T const&>() & std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    legal_overload<bitwise_and_operator, T, U>::value,
    bitwise_and_result<T, U>
>::type
constexpr inline operator&(const T & t, const U & u){
    return bitwise_and_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<bitwise_and_operator, T, U>::value,
    T
>::type
constexpr inline operator&=(T & t, const U & u){
    t = static_cast<T>(t & u);
    return t;
}

// operator ^
template<class T, class U>
struct bitwise_xor_result {
    using promotion_policy = typename common_promotion_policy<T, U>::type;
    using result_base_type =
        typename promotion_policy::template bitwise_xor_result<T, U>::type;

    // according to the C++ standard, the bitwise operators are executed as if
    // the operands are consider a logical array of bits.  That is, there is no
    // sense that these are signed numbers.

    using r_type = typename std::make_unsigned<result_base_type>::type;
    using r_type_interval_t = interval<r_type>;
    using exception_policy = typename common_exception_policy<T, U>::type;

public:
    // lazy_enable_if_c depends on this
    using type = safe_base<
        result_base_type,
        //r_interval.l,
        r_type(0),
        //r_interval.u,
        utility::round_out(
            std::max(
                static_cast<r_type>(base_value(std::numeric_limits<T>::max())),
                static_cast<r_type>(base_value(std::numeric_limits<U>::max()))
            )
        ),
        promotion_policy,
        exception_policy
    >;

    constexpr static type return_value(const T & t, const U & u){
        return type(
            static_cast<result_base_type>(base_value(t))
            ^ static_cast<result_base_type>(base_value(u)),
            typename type::skip_validation()
        );
    }
};

template<class T, class U> using bitwise_xor_operator
    = decltype( std::declval<T const&>() ^ std::declval<U const&>() );

template<class T, class U>
typename boost::lazy_enable_if_c<
    legal_overload<bitwise_xor_operator, T, U>::value,
    bitwise_xor_result<T, U>
>::type
constexpr inline operator^(const T & t, const U & u){
    return bitwise_xor_result<T, U>::return_value(t, u);
}

template<class T, class U>
typename std::enable_if<
    legal_overload<bitwise_xor_operator, T, U>::value,
    T
>::type
constexpr inline operator^=(T & t, const U & u){
    t = static_cast<T>(t ^ u);
    return t;
}

/////////////////////////////////////////////////////////////////
// stream helpers

template<
    class T,
    T Min,
    T Max,
    class P, // promotion polic
    class E  // exception policy
>
template<
    class CharT,
    class Traits
>
inline void safe_base<T, Min, Max, P, E>::output(
    std::basic_ostream<CharT, Traits> & os
) const {
    os << (
        (std::is_same<T, signed char>::value
        || std::is_same<T, unsigned char>::value
        || std::is_same<T, wchar_t>::value
        ) ?
            static_cast<int>(m_t)
        :
            m_t
    );
}

template<
    class T,
    T Min,
    T Max,
    class P, // promotion polic
    class E  // exception policy
>
template<
    class CharT,
    class Traits
>
inline void safe_base<T, Min, Max, P, E>::input(
    std::basic_istream<CharT, Traits> & is
){
    if(std::is_same<T, signed char>::value
    || std::is_same<T, unsigned char>::value
    || std::is_same<T, wchar_t>::value
    ){
        int x;
        is >> x;
        m_t = validated_cast(x);
    }
    else{
        if(std::is_unsigned<T>::value){
            // reading a negative number into an unsigned variable cannot result in
            // a correct result.  But, C++ reads the absolute value, multiplies
            // it by -1 and stores the resulting value.  This is crazy - but there
            // it is!  Oh, and it doesn't set the failbit. We fix this behavior here
            is >> std::ws;
            int x = is.peek();
            // if the input string starts with a '-', we know its an error
            if(x == '-'){
                // set fail bit
                is.setstate(std::ios_base::failbit);
            }
        }
        is >> m_t;
        if(is.fail()){
            boost::safe_numerics::dispatch<
                E,
                boost::safe_numerics::safe_numerics_error::domain_error
            >(
                "error in file input"
            );
        }
        else
            validated_cast(m_t);
    }
}

} // safe_numerics
} // boost

#endif // BOOST_NUMERIC_SAFE_BASE_OPERATIONS_HPP

/* safe_base_operations.hpp
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
*/