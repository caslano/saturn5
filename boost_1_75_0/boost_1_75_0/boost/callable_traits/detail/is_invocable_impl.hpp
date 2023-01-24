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
1TiuHSDG8dKqNsfxRPc/NY7MGzo0Ds9X0eN4pkdb4ziy+1TjuM0jxvHNyjbHsbzbnxrHlIIOjWPa2uhxbOre1jguOeU45rvFOLq3PY59zj81jsUjOzSO976MHkfn7pFxu4UeO094mh+U5AtARrDTiDJUPP6Q5K/DA+m3JEspeXJvX78NOY6lVlQDdMvtt8JQA4RygZx34m/cznDXWqABzJYDM2NxZ5b28S91Z/6zT0mqTx6SgjEm+tU5ltqhoji7p18dVlQdg9rEn8u/mDZeqprE/8V7swbZ/ffweTmqmZle2tbysXhQgqq2Kjf5QEAJ9JMCd0Ln73ROCkxPdjih00RiUzC2DKqXKPcWxcRpcGPOu17uivvtqD0Eov6kRtSFfK3sO9PSyv/s3cl/3mcr9ruT0cZvr2+TNv5qjaKNb1/fEdq4tC6aNnZzRtBG1AM6Ne+Y279NNHnHoOIs2OXVa+ItgMqKBZMIHwHEVgiPhywXeNyd8VjsMqdyjTm/TnONkTHOaKS/U0Rfvt3Zui9Zbffl88//VF+eqe1oX65roy/PXd1mXy79c31xnKwvrc6aVuw41VnTE/knPWu6ufVZEx5cKFW1/6fOmq6paOusKfBCHV8auFTRndrJU80d+snTv+7QT56kO/STpzPvMJ88Lb/dfPIUHNjhk6f7h2onT5OH/i8nTxcN78jJU+aa9k+e2pnbH7efam4/GXbS
*/