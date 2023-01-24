
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_DETAIL_BASE_HPP_
#       define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_DETAIL_BASE_HPP_

#       include <boost/functional/overloaded_function/config.hpp>
#       include <boost/function.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/preprocessor/repetition/enum.hpp>
#       include <boost/preprocessor/cat.hpp>
#       include <boost/preprocessor/comma_if.hpp>

#define BOOST_FUNCTIONAL_DETAIL_arg_type(z, n, unused) \
    BOOST_PP_CAT(A, n)

#define BOOST_FUNCTIONAL_DETAIL_arg_name(z, n, unused) \
    BOOST_PP_CAT(a, n)

#define BOOST_FUNCTIONAL_DETAIL_arg_tparam(z, n, unused) \
    typename BOOST_FUNCTIONAL_DETAIL_arg_type(z, n, unused)

#define BOOST_FUNCTIONAL_DETAIL_arg(z, n, unused) \
    BOOST_FUNCTIONAL_DETAIL_arg_type(z, n, unused) \
    BOOST_FUNCTIONAL_DETAIL_arg_name(z, n, unused)

#define BOOST_FUNCTIONAL_DETAIL_f \
    R (BOOST_PP_ENUM(BOOST_FUNCTIONAL_DETAIL_arity, \
            BOOST_FUNCTIONAL_DETAIL_arg_type, ~))

// Do not use namespace ::detail because overloaded_function is already a class.
namespace boost { namespace overloaded_function_detail {

template<typename F>
class base {}; // Empty template cannot be used directly (only its spec).

#       define BOOST_PP_ITERATION_PARAMS_1 \
                (3, (0, BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX, \
                "boost/functional/overloaded_function/detail/base.hpp"))
#       include BOOST_PP_ITERATE() // Iterate over funciton arity.

} } // namespace

#undef BOOST_FUNCTIONAL_DETAIL_arg_type
#undef BOOST_FUNCTIONAL_DETAIL_arg_name
#undef BOOST_FUNCTIONAL_DETAIL_arg_tparam
#undef BOOST_FUNCTIONAL_DETAIL_arg
#undef BOOST_FUNCTIONAL_DETAIL_f

#   endif // #include guard

#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_FUNCTIONAL_DETAIL_arity BOOST_PP_FRAME_ITERATION(1)

template<
    typename R
    BOOST_PP_COMMA_IF(BOOST_FUNCTIONAL_DETAIL_arity)
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_DETAIL_arity,
            BOOST_FUNCTIONAL_DETAIL_arg_tparam, ~)
>
class base< BOOST_FUNCTIONAL_DETAIL_f > {
public:
    /* implicit */ inline base(
            // This requires specified type to be implicitly convertible to
            // a boost::function<> functor.
            boost::function< BOOST_FUNCTIONAL_DETAIL_f > const& f): f_(f)
    {}

    inline R operator()(BOOST_PP_ENUM(BOOST_FUNCTIONAL_DETAIL_arity,
            BOOST_FUNCTIONAL_DETAIL_arg, ~)) const {
        return f_(BOOST_PP_ENUM(BOOST_FUNCTIONAL_DETAIL_arity,
                BOOST_FUNCTIONAL_DETAIL_arg_name, ~));
    }

private:
    boost::function< BOOST_FUNCTIONAL_DETAIL_f > const f_;
};

#   undef BOOST_FUNCTIONAL_DETAIL_arity
#endif // iteration


/* base.hpp
i6EJidBz9wWcmoTje+l0yugicykIRiiLv0Iy6yxO2m8VehzgZJIYgQy/AAgkA/9MEaYqEywRUpBkTlLn0kGn/0G7LOj61RcFIUpSzbp86Wi3ETRpUNGnUbxhnPIdn4tVGvQ5HeYDPsfVSvmcYOHnXDhq9nsuqKQ1+kU6FxK1cyExZQyDxzs4fwaPdxEe8zg8zCWLTKRg08Pk71iCiXnOXBOp0JKEhUYawmWmCoKFLxiicPloyQyA8Tr3290b6IC5bqkATR/1r0uWEpDWliOQvinX7UsDjLZ08svvqDA69LwfGAHOYNg14CBf02BCiKOBpq6LAM2TBtDsVBhOA2hcKmimP//fg6YhJxBoLvxMACT6MwLI58sQIB8uE3Yp+v1TGWVAmCwGDBS9k1RxcN9zpB1JEuot9qc9ZUaOuXSewBm6B4DjFuOt5L93ilwzcbP/kCkNzpVNE8xAwwpB3SVtIE49Oxf9lx5Q6drDzyFE1GBT6lWygVxsUKHw693+d07spwIGUZ9yGHyJMHjvayMMVF398o6qYhFD/iElUWyvzOMKRRAW332GhMUCEBbNwSgsXnUBCotrQ1FY7HA21kQ+NBfMJWGxQLENnseFxQK5N3j7YggYoa6fPV+vrkfgOtJSZhSYSzsHcwJlQ1croVTj6i/M+lTEteVFrOuKXjpt+aEgWo8ChzSYXLjQ4dohHDRV4yvUzOXiXYJii5rP
*/