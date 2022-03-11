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