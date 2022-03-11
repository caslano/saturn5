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