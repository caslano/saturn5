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
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
*/