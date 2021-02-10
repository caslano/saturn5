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
yYE62pyw6n8SG6tCORmns/YXowC/dEVUb/Fj80Uv5GIWUTjFpdNp/Y7gcyyMg8voj9K67d1TFytWZmvH3CykQ4cNtQtMdoXIq+1A65HHKnXJl1lji1Ud3dyqoNrBtk474AUbO0etPzZOenPZ7ziZtQcc2v1QirhsQMnYb/lGwG9R667LfXtQJAn34fCoYwGrCtgfwhFsDgduWR02q/P37Abr7tm8Mxa7mWY720/rbN+ORan/YjTofrcf59mfuUa3dne9C9b/mX9KK+f9sAHXm7cLwke2EOgNl8PhbaDPKs8fAMK85Qqzvm1OUSbOW4KgEsvhAO6YBN0egSvyIyxx+CdntO+vAF5Qm26sDXCOds3ZL0odh+1tpQajbujbL+kFKuPGoi+xSosCNvEd0lY4enBEio5vdBOsffddx9seTKV9ZgiOe6LwxRLi2DlqbWrEr+LixEjX5oXIS47fTmM8MEs9e4nFxwn8enrxajw5jehg+DiByVn/4tTr8AF9nNC7C3j88+VowD5Hm1Z4Sxj9F9FaeOmOp7e60oZHGfRnXCieqU2BJJdCl8tKwG/Olxic3ByJwUSJHrs3DQ39yXa8wucPes87URMBo4+X/6O17XrMV080zuVCKH0HQUEllf7WuHE+NpJ/B/lu0AX/
*/