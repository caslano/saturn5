/*
@Copyright Barrett Adair 2016-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_SFINAE_ERRORS_HPP
#define BOOST_CLBL_TRTS_SFINAE_ERRORS_HPP

#include <boost/callable_traits/detail/config.hpp>

namespace boost { namespace callable_traits { namespace detail {

        struct sfinae_error{};

        template<typename T>
        struct success {
            static constexpr bool value = true;
            struct _ { using type = T; };
        };
    
        template<bool B, typename T>
        struct fail_if : T {
            static_assert(std::is_base_of<sfinae_error, T>::value,
                "incorrect usage of fail_if");

            static constexpr bool value = B;
        };

        template<typename T, typename... FailIfs>
        using sfinae_try = typename BOOST_CLBL_TRTS_DISJUNCTION(
                FailIfs..., success<T>)::_::type;

        template<typename FailMsg, typename ForceTwoPhaseLookup>
        struct fail {
            using type = typename std::conditional<std::is_same<ForceTwoPhaseLookup, std::false_type>::value,
            FailMsg, FailMsg>::type::_::type;
        };

}}} // namespace boost::callable_traits::detail

#define BOOST_CLBL_TRTS_PP_CAT_(x, y) x ## y
#define BOOST_CLBL_TRTS_PP_CAT(x, y) BOOST_CLBL_TRTS_PP_CAT_(x, y)

#define BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(origin) \
namespace error {                                          \
    template<typename ErrorMessage>                        \
    struct origin :                                        \
        ::boost::callable_traits::detail::sfinae_error     \
        { struct _ {}; };                                  \
}                                                          \
/**/

#define BOOST_CLBL_TRTS_SFINAE_MSG(origin, name) \
struct BOOST_CLBL_TRTS_PP_CAT(name, _ ){};       \
struct name : error::origin<                     \
    BOOST_CLBL_TRTS_PP_CAT(name, _ )>{};         \
/**/

namespace boost { namespace callable_traits {

    BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(parameters)
    BOOST_CLBL_TRTS_SFINAE_MSG(parameters, index_out_of_range_for_parameter_list)
    BOOST_CLBL_TRTS_SFINAE_MSG(parameters, cannot_determine_parameters_for_this_type)

    BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(varargs)
    BOOST_CLBL_TRTS_SFINAE_MSG(varargs, varargs_are_illegal_for_this_type)

    BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(member_qualifiers)
    BOOST_CLBL_TRTS_SFINAE_MSG(member_qualifiers, member_qualifiers_are_illegal_for_this_type)
    BOOST_CLBL_TRTS_SFINAE_MSG(member_qualifiers, this_compiler_doesnt_support_abominable_function_types)

    BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(transaction_safe_)
    BOOST_CLBL_TRTS_SFINAE_MSG(transaction_safe_, transaction_safe_is_not_supported_by_this_configuration)

    BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(expand_args)
    BOOST_CLBL_TRTS_SFINAE_MSG(expand_args, cannot_expand_the_parameter_list_of_first_template_argument)

    BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(member_pointer_required)
    BOOST_CLBL_TRTS_SFINAE_MSG(member_pointer_required, type_is_not_a_member_pointer)

    BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(reference_error)
    BOOST_CLBL_TRTS_SFINAE_MSG(reference_error, reference_type_not_supported_by_this_metafunction)

}} // namespace boost::callable_traits

#endif // #ifndef BOOST_CLBL_TRTS_SFINAE_ERRORS_HPP

/* sfinae_errors.hpp
HMbAFuq/FUyELTWcEkvX38IXNZy6jvV1Z6p+NkxWuZ3KE2AOnAJz4VkwD2bBfM2XGXARnAnXwtnwCjgLXgvnaH4UwAfhPGj2KB1IvGA3jZdzL8XHPNwX3AsTYClMgU/AtvBJ2Bk+Be0zB7M1vGUanvPMwRe4rg++AmvAA7Am/AOMgq/BZvAgbAV/D3vCQ3p/b8Glqs/1KCy6PhNstrRNgujK7wFV2Q3jVG4GH4UpcA/sCh+DveDjMAeWwjz4BFyg8lL4JFwOn4IlcB88Drf6dTQe6zUe0XCT/e2Z+Pp5MQyHW/T+7oMd4K0wA94OB8BtcLC6D4F3wNPhnXAmvAsWwLthobovgffCZepvObwMrlP5uNyHveZO1g1KPP3ldRdGmlLaDVlTqO3KaNgGToYT4VS4GE6DER5kWB/65UtVvlnl1+BZ8GuYBWMJOAf2gNPhNJgPV8CZ8AY4G5bCufB9OA+GEc/5sDkshsclP3XdlK7RSgrac3Uu5TEeFsPmcBE8DV4NB8FlMBueB2fClXAuXAXnw9VwKVwDz4Nr4Rq4Ttu9C+DNcCO8E14E74eXwIfhlXAv3ASfhpvhfr3+cfl2rGuB4AKNf21YoPGfovXuDBgHz9T7mQWbwSy9n2zYF+bCMXA6nATz4FmqPx3OhHNV1nqja2+Ii0u9eVbrzX5YH74AY9U+XuWm8EU4EL4ER8CX4TT4BsxSOQ++CmfB12Gxutv9/gGNR4RLv/+29nPvwHD4LtT00/UnhOGSfgM0/gNhGBwEo+BoWAsOhvXgEBir9nFwKGwCh8Hmat8CDoedVTZ7C4/i+jBer+/cy/UZ0lnSEUbC/bA2fAnWgc/BuvB52FDtY+GLsJHK9hnNGXqd0/Q6zjOa39X29E/anr6v7enH2p5+oO3pUW1vPoI91F3TX9d1EH+X9N+h6X83jIT3OJ5Ptqq/OJd+cZv6uwPWh9thA5VjVbbDKdVwEl3CuUHDuREmwK2wscpNVbbDOabhpLqEc7OGcwuU9hZ2VLmzypoerD0InR7XaDjXanr8Vv1ZOv/e+Zzlj9/X6q+jl/uGXWBzmA5TYFeYC7vDPDgVFqv9CtgDroI94W9gH7gZ9oXXw35wq/rbDfvDvXAA3A8Hwj/BQfDPcDD8DA6Fx+Bw6I/0KBgNR8PGcAxsCU+HrWEmbAdHwE5wMsyBU2AhnGr6Y51jDS9yaVc+0fL6hZbXY1pe/67l9biW16+1vH4D28JvYWf4PUyDP8BM+BNcD/8GL9RwjkPcdH4ycdR41ICDNB68skk9/ACmwCNwMDwKh8K/wFHwIzheZX1eYh6x1keX56Wb9Mz0m2FDeJu2l3fAZnAbTFf5ODyEKdHwfFpuGkm7qmeOaTu2UtvhVdourdY9xNdovG+EQ+A6OE3lM+D5cA68AK5U+1VwI9yk8lXwcngjLIF3wCvg4+q+F14JD6r8BtwC34PXwK/U/mt4HfR6kE166fxgOMUlvT7TfPhc7+NLTf/jmv7HNP2Rtd/XubVwhku/f67Wz6VaP5fBunA5jIMrYCI8D7aGK6Hs+Q67wdWwN1wDB8G1+p54PhwDL4CZ8GI4Fm6AU+BGeBa8COaq+3S4HuarbNePAxr/nW7Pq/oesVvbi4dhI7gftoCPwgHwMTgUPg6zYSksgk9oe/EkXAufhpfAZ+F2uN+0+zp/FIa5tHNvajr+HvrgIWjnZ6n6S3DJT4/688Io6IPRMALGwHAYr7K+L+i8RtLS5X2htZb/FO2v28O2sCPEWF203KfDkfBUOAOeBufCPvAC2M/02zqnEOa69NsHPNQz+BqMU7mpyunwLdgXvgGHwDfhcHgITlb341K/dP6e4/nqFMdYzbU=
*/