/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP
#define BOOST_CLBL_TRTS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP

#include <boost/callable_traits/detail/qualifier_flags.hpp>

#define BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(QUAL)              \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, false, false, Return, Args...> {    \
    using type = Return(Args...) QUAL;                             \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, true, false, Return, Args...> {     \
    using type = Return(Args...) QUAL                              \
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;                \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, false, true, Return, Args...> {     \
    using type = Return(Args...) QUAL                              \
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;                        \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, true, true, Return, Args...> {      \
    using type = Return(Args...) QUAL                              \
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER                 \
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;                        \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, false, false, Return, Args...> {    \
    using type = Return(Args..., ...) QUAL;                        \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, true, false, Return, Args...> {     \
    using type = Return(Args..., ...) QUAL                         \
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;                \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, false, true, Return, Args...> {     \
    using type = Return(Args..., ...) QUAL                         \
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;                        \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, true, true, Return, Args...> {      \
    using type = Return(Args..., ...) QUAL                         \
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER                 \
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;                        \
}                                                                  \
/**/

namespace boost { namespace callable_traits { namespace detail {

        template<qualifier_flags Applied, bool IsTransactionSafe,
            bool IsNoexcept, typename Return, typename... Args>
        struct set_function_qualifiers_t {
            using type = Return(Args...);
        };

        template<qualifier_flags Applied, bool IsTransactionSafe,
            bool IsNoexcept, typename Return, typename... Args>
        struct set_varargs_function_qualifiers_t {
            using type = Return(Args..., ...);
        };

#ifndef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(volatile);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const volatile);

#ifndef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(&);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(&&);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const &);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const &&);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(volatile &);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(volatile &&);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const volatile &);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const volatile &&);

#endif // #ifndef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
#endif // #ifndef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

        template<qualifier_flags Flags, bool IsTransactionSafe, bool IsNoexcept,
            typename... Ts>
        using set_function_qualifiers =
            typename set_function_qualifiers_t<Flags, IsTransactionSafe, IsNoexcept,
                Ts...>::type;

        template<qualifier_flags Flags, bool IsTransactionSafe, bool IsNoexcept,
            typename... Ts>
        using set_varargs_function_qualifiers =
            typename set_varargs_function_qualifiers_t<Flags, IsTransactionSafe,
                IsNoexcept, Ts...>::type;

}}} // namespace boost::callable_traits::detail

#endif //BOOST_CLBL_TRTS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP

/* set_function_qualifiers.hpp
HMxEzJBj65MC5yM+L/LOUPMRVT/F7Cn1rMg7XOcjxiLvE/c7Tf7gP+R8xLTJ2qeJTC6KzNsXdv5+P4n0XtGt6nMUX5oUOEfxqMhR8jxaj/CWdPv3zlHsaX9/0kb/A0wU5k3MReRd6WTNuyyaYP+z6qIsM19Bv/E78xB9fV7Sfv0PIt/EE0e82jEyPUXOsMFmuIah86/0GeX34mefVUT8VmIuw2iea/hxjjyeXgDEbyP4qri/ai3n/wsx12A0v9VvtMNvXoGZC2TcP3DkW6Fp31/W69rP3L4pOvaGTVf+pZF/75B3L57K90P/9+KZtVryvdhb+5Rw/os+NcLra4hNi4gaPBxG1K7trWs52vjcXGcb31nCXkQdSnTo5OQ4+4/2orNEZt+49UeF4l7L9EebRa5RpXcc8sXZ3iO7tUWkf4XndknXgPYpo6clv1l6oZmYS/zvQlOc5UuKllu5Ur0aZi7JRyJ3UZlRmqnaN6tf004bvxmm70uaqn2fyxjArCD9Waqv/WvIPEuZavpl8/xwXMLppDoB4WCHTqBdyLxuOdU8K5jn5c8l7DTXe9J65rRzLSNRUwPKiKaht9LfvEKUD5EbhXi/T+plyS9NA+yi/VTRVFMO5hcX509fJM/+rn2V6qaFfFeIhqtFp7kZy1skcif38WvNr1Wi06LS9+/WBx7R+8vQd4BTMXeQLjvN/eUvKcopzAsx11f1MsrbKMc4HarqnhQwphR6vUHSCLd3y5iA8SIJP6Cu9u5jye8qnQtxkd6DNS3wHshD53ujecduKnrFtJZmT0D12zTk/Cnctd/Q8TCRl1HqnXPQcsxege3E/SxqTYT0xx/3Iu17y1wdZoP6JpTN1Yl3nauzFb3DmLK5ShNMP2vrxsf9knn1uUHpKvdX1sdq2djVz5LfZOJfF46Fl/r72KB05QTrRfnFhTkF5jkpsH98TfQHeTry/5mYxzGazhpWTIV0jpV0tt2XMie0Ae9bLZzz+0xdGXuGvDcS91pm3CNH7PoxvhRp2uCtYkd7ot8oa56JbNxVRnKbJ3i9+C1Q2eg65w2aerlJdNeFnDe464zAeYM7zzj5vMFH0THzBo2fmSecN7j3DOe8QePHzBvMoN706GfPi8+QcmXbZ9r23tVr/fb2+bF8fxCTEOf/HlG1PWCd7wbDKpY70yZlo+z/9dI2Kc1uc8/Ucidz5rJCtUmq11jucTf30STDrjt15B7L69hJ14GPONm8/681ro3UQ5zGtdTEVY53d4un6jSq8jtMjL5PTpF194WzC3IDx9B39w9aY6bt4WETp3O1UXeNl+q1CNn2qXsl23SrEm26hP8v2WfQfd+9//39B5MvFfuhjz21eeMnURu+rffZhu2ntw21/2D1PoPO8xFXYCw94z4J/9dSRvbr3zdj/6X+/YGeH+v/+wd0BunfVhj5qH+/g/0R/fsqX9m4eg/+vt0rfbvY3+1vH/TvOugcl/mSukcFJNvELQx20Li94rNW+3kAxsDXYEv4Ojyu40TH1H+4+vdBdOT3tfr/KwyD36i/DEv3gwBj1J9zT7mn0KsDn4Ep8Fk4FO6Hw+GLjnCKNJy6LuF8qtf/HEbAL2AUPAZPgV86wik5QTjvazhHNJyjGs6HGs5HjnB2ajitXMLZpOFcBZPhZthc5ZYqmzMYNZwVHsIJOoPxHRrQWHgYJsP3YWv4AcyBR+F0GOFl70a1Xw4/hpfBT+Bv4KfwGvgZvE71d8EvkB+Fx+A++CV8Fx6HR+FX8M/wr/BT+C30R/Z7WA/+ABPgj7AF/Am2gn+DbeF3sCMM8xJfGA4LYQS0y6Wsg4YJLuWyDXp1YFsYDdvBhirb+XBY/bdwyYdk9d8=
*/