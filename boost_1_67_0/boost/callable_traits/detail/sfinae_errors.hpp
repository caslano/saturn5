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