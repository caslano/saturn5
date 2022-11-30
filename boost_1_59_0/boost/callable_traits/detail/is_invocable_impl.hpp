 /*!
@file

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_INVOCABLE_IMPL_HPP
#define BOOST_CLBL_TRTS_IS_INVOCABLE_IMPL_HPP

#include <boost/callable_traits/detail/config.hpp>
#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/utility.hpp>
#include <type_traits>
#include <utility>

namespace boost { namespace callable_traits { namespace detail {

    template<typename T>
    struct can_dereference_t
    {
        template<typename>
        struct check {};

        template<typename U>
        static std::int8_t test(
            check<typename std::remove_reference<decltype(*std::declval<U>())>::type>*
        );

        template<typename>
        static std::int16_t test(...);

        static constexpr const bool value =
            sizeof(test<T>(nullptr)) == sizeof(std::int8_t);
    };

    //returns std::true_type for pointers and smart pointers
    template<typename T>
    using can_dereference = std::integral_constant<bool,
        can_dereference_t<T>::value>;


    template<typename T, typename = std::true_type>
    struct generalize_t {
        using type = T;
    };

    template<typename T>
    struct generalize_t<T, std::integral_constant<bool,
            can_dereference<T>::value && !is_reference_wrapper<T>::value
    >>{
        using type = decltype(*std::declval<T>());
    };

    template<typename T>
    struct generalize_t<T, is_reference_wrapper<T>> {
        using type = decltype(std::declval<T>().get());
    };

    // When T is a pointer, generalize<T> is the resulting type of the
    // pointer dereferenced. When T is an std::reference_wrapper, generalize<T>
    // is the underlying reference type. Otherwise, generalize<T> is T.
    template<typename T>
    using generalize = typename generalize_t<T>::type;

    // handles the member pointer rules of INVOKE
    template<typename Base, typename T,
             typename IsBaseOf = std::is_base_of<Base, shallow_decay<T>>,
             typename IsSame = std::is_same<Base, shallow_decay<T>>>
    using generalize_if_dissimilar = typename std::conditional<
        IsBaseOf::value || IsSame::value, T, generalize<T>>::type;

    template<typename Traits, bool = Traits::is_const_member::value
        || Traits::is_volatile_member::value
        || Traits::is_lvalue_reference_member::value
        || Traits::is_rvalue_reference_member::value>
    struct test_invoke {

        template<typename... Rgs,
            typename U = typename Traits::type>
        auto operator()(int, Rgs&&... rgs) const ->
            success<decltype(std::declval<U>()(static_cast<Rgs&&>(rgs)...))>;

        auto operator()(long, ...) const -> substitution_failure;
    };

    template<typename F>
    struct test_invoke<function<F>, true /*abominable*/> {
        auto operator()(...) const -> substitution_failure;
    };

    template<typename Pmf, bool Ignored>
    struct test_invoke<pmf<Pmf>, Ignored> {

        using class_t = typename pmf<Pmf>::class_type;

       template<typename U, typename... Rgs,
            typename Obj = generalize_if_dissimilar<class_t, U&&>>
        auto operator()(int, U&& u, Rgs&&... rgs) const ->
            success<decltype((std::declval<Obj>().*std::declval<Pmf>())(static_cast<Rgs&&>(rgs)...))>;

        auto operator()(long, ...) const -> substitution_failure;
    };

    template<typename Pmd, bool Ignored>
    struct test_invoke<pmd<Pmd>, Ignored> {

        using class_t = typename pmd<Pmd>::class_type;

        template<typename U,
            typename Obj = generalize_if_dissimilar<class_t, U&&>>
        auto operator()(int, U&& u) const ->
            success<decltype(std::declval<Obj>().*std::declval<Pmd>())>;

        auto operator()(long, ...) const -> substitution_failure;
    };

    template<typename T, typename... Args>
    struct is_invocable_impl {
        using traits = detail::traits<T>;
        using test = detail::test_invoke<traits>;
        using result = decltype(test{}(0, ::std::declval<Args>()...));
        using type = std::integral_constant<bool, result::value>;
    };

    template<typename... Args>
    struct is_invocable_impl<void, Args...> {
        using type = std::false_type;
    };

    template<typename IsInvocable, typename Ret, typename T, typename... Args>
    struct is_invocable_r_impl {
        using traits = detail::traits<T>;
        using test = detail::test_invoke<traits>;
        using result = decltype(test{}(0, ::std::declval<Args>()...));
        using type = std::integral_constant<bool,
            std::is_convertible<typename result::_::type, Ret>::value
                || std::is_same<Ret, void>::value>;
    };

    template<typename Ret, typename T, typename... Args>
    struct is_invocable_r_impl<std::false_type, Ret, T, Args...> {
        using type = std::false_type;
    };

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_IS_INVOCABLE_IMPL_HPP

/* is_invocable_impl.hpp
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
*/