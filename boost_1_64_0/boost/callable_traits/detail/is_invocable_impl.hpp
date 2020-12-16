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
MPXMukE3iz0j0Lq5Kptg8ni12HsE1CXJRr6ZKbOVYh/pX2amzizRc2uZafgGPuvfmvoifl1818+dVLze0Frxv1bXDPO9p5tFc49eZBkmQV0rVfONsvHbvy45wH07LED5ddG9yuaUt+SYqfOMJ8HN/Kg4Pkj5yXTjoGWo4RpbMbo+cQex93VWoQ27I+Z+6wZd26vk+sl9TPgGVozWgXZi7+esSnt7J8wWa6yE5zr8y9qs2ZsoYW6xIqxKVndvW7uJu55tbYBJCZamXeYMjdf+D037e2K/Qf0dVtIE0dP2vhkzp7kSXI8/4U2bf0sJn+mII8d7Yrx9NrVytc9G5Oj9yfXfYzvdkz2mrs6VeA+r3WENFvlaNvlJefbrWCjnLW/uozfEPlbWSZiH3K1iZ2aD4y37Old5lq3+bxKZ35i1QYdKGio7xN+kuYL6e+0h9jV8TL6skbjqmH6k30lcVU1+PCT+YaZf6aT4u7FresX+rW1+9jSzBkOI+HW0wqlbpg6Km8vohqVir65hWP1GzjeCFHS0laXsKWfWqB4lMtnUoHBTX3TPXhPvcyLznNq9eVDFXi6SqZG6VspaSce91N8IZHAzZRlmO0dha/4ZvfPJBLOeOHZv3swlVYn2MC0t2z14SvMkSuzeMDMsN24pVm17uFaW7d3pI5Frx7mw284VhpstTKJlexaeE5kmhMFuC1MFN+/6Zl11PTOoe3diVOf1voDOywug82YYt8DvKvZ3i40VLTkOYBpgNmCS0G8JE03/4eRMWSvH/ogKuLa7hmlh9EOq2JcEej6pbEfzjJgg9imB1nRX2fbmfs8W+5yAz7KBRr6Nub+zxD635LNM9eEo8Z9sX/uAOEqsd2eeXfb+44kil2V775Xl7cw9MFf8R2hZFz/b9mD2XcLzzfMO+puJtrXBfZ93/s86sSf7rQ0+LMCzL83n2ffzrGfw375uwWHpR3xqV+jML775/IEtsUNa3Djvo0+C9SMG6+8sXc9A+5Vlz0hVO/K9HSbzyYv6L/MsbeOBC60iv3CYqfI3Oor6B2+CcXABTIALYSu4AnaGN8MBcDFMh0thFrwFToXL4QyVPwvTLG1/gYP0vGVhip73NN4efgorqz0KnoG14BewITwLW8IvtR/1HOxr2ydymKXtI7CPnAcDkZHjXY33PRgDT8G68H3YFH4A28APYWf4EUyCH5v4tS0EFgSI/w/IVYB/0vj+AlvBt+FI+A4crfax8M9wosqZ/luN3+0kbr/+W/xlHYrvYXP4A6R8ZB5fN/iTzjMjAonfBZfDCLgJXgG3wPJwJ6wED8Au8BV4NTwFu8EPYS8YSxp6w7bwOtgD9oHXw35wMBwAM+AgOBcOhWvgFLgV5sMHYSE8CWfCM3AWPAtneyjrL+j3KXxU87cy3KHXv1r36VwH28HbYAe4Xq9/A7wGbtP6eQ9MgTs0P+6Fk+B9MB8+AGfBX8F5cDdcCvdovu2FK+E+uBruhxvhr+Fm+KDZj0y/0eAyTbd9P7JdOg5gj9bbvXAo3AfHwf1wMvw9lPvUfC+QV1oPmhTtFypHX60Hg2BjeL3WhxSpD9ovDrfDXnA4vEHt2XCUnu8GWADT4XKYAVfCMXA7zII74Vj4K5gNn9TznoQ58Bs4Abp0Xl9ZOBEmwDzYHU6F18Ab4Qy4BG6EK23z+k7AFfAtdT8JV8FT8Fb4MVwNP4Nr4Fm4Fn4F18Hv4W3QclIfYDS8HdaEG2FPuAX2g3fDwfAeOAlu13zP9r6bwANajuUkv4qOmlqOzWE32AL2gwl637WBWbCdlmt7OA12hqtgL7gB9oYnS+cl/uzjFR7eeXFjFtLml7vkcQujlpWz5mDuxBzCvI0=
*/