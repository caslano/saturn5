/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    apply.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_APPLY_H
#define BOOST_HOF_GUARD_APPLY_H

/// apply
/// =====
/// 
/// Description
/// -----------
/// 
/// The `apply` function calls the function given to it with its arguments.
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     constexpr auto apply(F&& f, Ts&&... xs);
/// 
/// Semantics
/// ---------
/// 
///     assert(apply(f)(xs...) == f(xs...));
///     assert(fold(apply, f)(x, y, z) == f(x)(y)(z));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [Invocable](Invocable)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         assert(boost::hof::apply(sum_f(), 1, 2) == 3);
///     }
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/static_const_var.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4003)
#endif

#define BOOST_HOF_DETAIL_FOREACH_QUAL(m, data) \
    m(, data) \
    m(const, data) \
    m(volatile, data) \
    m(const volatile, data)

namespace boost { namespace hof {

namespace detail {
#if BOOST_HOF_HAS_MANUAL_DEDUCTION || BOOST_HOF_NO_EXPRESSION_SFINAE
struct apply_mem_fn
{
    template<class...>
    struct convertible_args;

    template<class T, class U, class=void>
    struct is_convertible_args
    : std::false_type
    {};

    template<class... Ts, class... Us>
    struct is_convertible_args<
        convertible_args<Ts...>, 
        convertible_args<Us...>, 
        typename std::enable_if<(
            sizeof...(Ts) == sizeof...(Us)
        )>::type
    >
    : and_<std::is_convertible<Ts, Us>...>
    {};

    template<class From, class To>
    struct is_compatible
    : std::is_convertible<
        typename std::add_pointer<typename std::remove_reference<From>::type>::type,
        typename std::add_pointer<typename std::remove_reference<To>::type>::type
    >
    {};

#define BOOST_HOF_APPLY_MEM_FN_CALL(cv, data) \
    template <class R, class Base, class Derived, class... Ts, class... Us, class=typename std::enable_if<and_< \
        is_compatible<Derived, cv Base>, \
        is_convertible_args<convertible_args<Us...>, convertible_args<Ts...>> \
    >::value>::type> \
    constexpr R operator()(R (Base::*mf)(Ts...) cv, Derived&& ref, Us &&... xs) const \
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT((BOOST_HOF_FORWARD(Derived)(ref).*mf)(BOOST_HOF_FORWARD(Us)(xs)...)) \
    { \
        return (BOOST_HOF_FORWARD(Derived)(ref).*mf)(BOOST_HOF_FORWARD(Us)(xs)...); \
    }
    BOOST_HOF_DETAIL_FOREACH_QUAL(BOOST_HOF_APPLY_MEM_FN_CALL, ~)
};

struct apply_mem_data
{
    template<class T, class R>
    struct match_qualifier
    { typedef R type; };

#define BOOST_HOF_APPLY_MEM_DATA_MATCH(cv, ref) \
    template<class T, class R> \
    struct match_qualifier<cv T ref, R> \
    : match_qualifier<T, cv R ref> \
    {};

    BOOST_HOF_DETAIL_FOREACH_QUAL(BOOST_HOF_APPLY_MEM_DATA_MATCH,&)
    BOOST_HOF_DETAIL_FOREACH_QUAL(BOOST_HOF_APPLY_MEM_DATA_MATCH,&&)

    template <class Base, class R, class Derived, class=typename std::enable_if<(
        std::is_base_of<Base, typename std::decay<Derived>::type>::value
    )>::type>
    constexpr typename match_qualifier<Derived, R>::type 
    operator()(R Base::*pmd, Derived&& ref) const noexcept
    {
        return BOOST_HOF_FORWARD(Derived)(ref).*pmd;
    }
};

template<class T, class U=decltype(*std::declval<T>())>
struct apply_deref
{ typedef U type; };

#endif

struct apply_f
{
#if BOOST_HOF_HAS_MANUAL_DEDUCTION || BOOST_HOF_NO_EXPRESSION_SFINAE
    template<class F, class T, class... Ts, class=typename std::enable_if<(
        std::is_member_function_pointer<typename std::decay<F>::type>::value
    )>::type>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(apply_mem_fn, id_<F>, id_<T>, id_<Ts>...) 
    operator()(F&& f, T&& obj, Ts&&... xs) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        apply_mem_fn()(f, BOOST_HOF_FORWARD(T)(obj), BOOST_HOF_FORWARD(Ts)(xs)...)
    );

    template<class F, class T, class... Ts, class U=typename apply_deref<T>::type, class=typename std::enable_if<(
        std::is_member_function_pointer<typename std::decay<F>::type>::value
    )>::type>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(apply_mem_fn, id_<F>, id_<U>, id_<Ts>...) 
    operator()(F&& f, T&& obj, Ts&&... xs) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        apply_mem_fn()(f, *BOOST_HOF_FORWARD(T)(obj), BOOST_HOF_FORWARD(Ts)(xs)...)
    );

    template<class F, class T, class... Ts, class=typename std::enable_if<(
        std::is_member_function_pointer<typename std::decay<F>::type>::value
    )>::type>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(apply_mem_fn, id_<F>, id_<T&>, id_<Ts>...) 
    operator()(F&& f, const std::reference_wrapper<T>& ref, Ts&&... xs) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        apply_mem_fn()(f, ref.get(), BOOST_HOF_FORWARD(Ts)(xs)...)
    );

    template<class F, class T, class=typename std::enable_if<(
        std::is_member_object_pointer<typename std::decay<F>::type>::value
    )>::type>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(apply_mem_data, id_<F>, id_<T>) 
    operator()(F&& f, T&& obj) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        apply_mem_data()(f, BOOST_HOF_FORWARD(T)(obj))
    );

    template<class F, class T, class U=typename apply_deref<T>::type, class=typename std::enable_if<(
        std::is_member_object_pointer<typename std::decay<F>::type>::value
    )>::type>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(apply_mem_data, id_<F>, id_<U>) 
    operator()(F&& f, T&& obj) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        apply_mem_data()(f, *BOOST_HOF_FORWARD(T)(obj))
    );
    
    template<class F, class T, class=typename std::enable_if<(
        std::is_member_object_pointer<typename std::decay<F>::type>::value
    )>::type>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(apply_mem_data, id_<F>, id_<T&>) 
    operator()(F&& f, const std::reference_wrapper<T>& ref) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        apply_mem_data()(f, ref.get())
    );

#else

    template <class Base, class T, class Derived>
    constexpr auto operator()(T Base::*pmd, Derived&& ref) const
    BOOST_HOF_RETURNS(BOOST_HOF_FORWARD(Derived)(ref).*pmd);
     
    template <class PMD, class Pointer>
    constexpr auto operator()(PMD&& pmd, Pointer&& ptr) const
    BOOST_HOF_RETURNS((*BOOST_HOF_FORWARD(Pointer)(ptr)).*BOOST_HOF_FORWARD(PMD)(pmd));

    template <class Base, class T, class Derived>
    constexpr auto operator()(T Base::*pmd, const std::reference_wrapper<Derived>& ref) const
    BOOST_HOF_RETURNS(ref.get().*pmd);
     
    template <class Base, class T, class Derived, class... Args>
    constexpr auto operator()(T Base::*pmf, Derived&& ref, Args&&... args) const
    BOOST_HOF_RETURNS((BOOST_HOF_FORWARD(Derived)(ref).*pmf)(BOOST_HOF_FORWARD(Args)(args)...));
     
    template <class PMF, class Pointer, class... Args>
    constexpr auto operator()(PMF&& pmf, Pointer&& ptr, Args&&... args) const
    BOOST_HOF_RETURNS(((*BOOST_HOF_FORWARD(Pointer)(ptr)).*BOOST_HOF_FORWARD(PMF)(pmf))(BOOST_HOF_FORWARD(Args)(args)...));

    template <class Base, class T, class Derived, class... Args>
    constexpr auto operator()(T Base::*pmf, const std::reference_wrapper<Derived>& ref, Args&&... args) const
    BOOST_HOF_RETURNS((ref.get().*pmf)(BOOST_HOF_FORWARD(Args)(args)...));

#endif
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(F, id_<Ts>...) 
    operator()(F&& f, Ts&&... xs) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        f(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

}

BOOST_HOF_DECLARE_STATIC_VAR(apply, detail::apply_f);

}} // namespace boost::hof

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* apply.hpp
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
*/