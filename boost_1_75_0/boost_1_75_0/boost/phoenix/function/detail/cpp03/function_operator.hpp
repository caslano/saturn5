
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_FUNCTION_DETAIL_FUNCTION_OPERATOR_HPP
#define BOOST_PHOENIX_FUNCTION_DETAIL_FUNCTION_OPERATOR_HPP

#include <boost/phoenix/function/detail/cpp03/preprocessed/function_operator.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_FUNCTION_DETAIL_FUNCTION_OPERATOR_HPP
#define BOOST_PHOENIX_FUNCTION_DETAIL_FUNCTION_OPERATOR_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/function_operator_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                          \
    <boost/phoenix/function/detail/cpp03/function_operator.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
        template <typename This, BOOST_PHOENIX_typename_A>
        struct result<This(BOOST_PHOENIX_A_const_ref)>
            : detail::expression::function_eval<F, BOOST_PHOENIX_A>
        {};

        template <BOOST_PHOENIX_typename_A>
        typename detail::expression::function_eval<F, BOOST_PHOENIX_A>::type const
        operator()(BOOST_PHOENIX_A_const_ref_a) const
        {
            return detail::expression::function_eval<F, BOOST_PHOENIX_A>::make(f, BOOST_PHOENIX_a);
        }

#endif

#endif // PHOENIX_DONT_USE_PREPROCESSED_FILES

/* function_operator.hpp
FKv5fLtQ6BSL3Uq5nkyaDcSg3ye0OlKhMOt0jE5v0eqwtBYtBHCNRaW2qFQWpZJRyE0ymQnqPanEJBaZhALMi4+jN3Ko4fhEcwjJ961mH6VgxatXEJkjDhtUZYcvnksP9qMWxqZQoPgvlQBxSgCnDYr/cM5QvLO43fihqVGA6m9Y9/4i1v0/y3o5bi0mnb+G9cWfZg1vC9ZFuzioZGupRAVieDhcjoQrkUg1Fmskk81UuuDz01rtoNcjtFpgbQLWBr3FYLDqdRad3qrVWXXoy5NtGpS1bZC+lQpGLmfkMgbsKRFDyjaKRDQfYvIZsfG49vAQQIPTAbTi1cuI3cbS9Ntnv8qPDhMOu1OttisUuGyTMnDaiIUQ1eE4CYepX4gvusXtK99qAawHddDig7se0Sdxc6l/Xbl9wBrh3uoB7uED1k1gDbpjjdRC2uLeaIN7w/r8oa9X8w3r+QPWF1/EGr1X3dK8UwToF+3CRQsLVtrFebs4a+aNOm2v09FrNCQEbb3BQhisBGE1YOn0Nr3ehnDrrNr1N2ZblAoo0gAWEDfvBmRI5adQYB9DbQYpGKBDDFe+fhWyWpw63asnP5WiXni6ST0zqYHSnMZVpGk9c9HKPwoaNP/rWZf/NOvWX8b64q9k/WmZKbLb6ejUwFptNgBr0kqQNoK0IxkcBOkgCIcB/YysU29w6HQOrdYJ3NUqu1plUyotcqlZJgGP
*/