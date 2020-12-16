
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
kyde0q+IM2HLov+RZaF9azGI7VfCSrvC1bXy+lkFu8a28dIoIquhvCiJxlZ3nQT/GSX2cGK79HK2JEHoLnGad+WeXtbt/bz1ax5nUSx6rWsc51K2rHy0P1e5+DXaojFae4vPwAC4ysMuRmOUpgHk4xEL4f2kZHzlZe04Y+jctiD1S1QPb7nQr1KsWL5DdJJFp3Pm8/CjnuWGyBoBg9keb9AnYNprf0bKqNQvuKmI924HojEc4eaS+2d+PKWkuvy9p45oernW17O/BKEu/pAeHi2SokvRawW6Z1FCeZ3Rj6VrvNsTzR+psVqHmixab4UgP7V9Ub3pPORhP56ZsY1T0KBorMHYhdOlWPT8d/NQJx1L9dLPtKh8nROzOiBWYzU2bZzwNufLnPm0b/k7pK58OBbf6vdEhXzpnr/vqtWyTl/F6iwWtCpPv8ZqDBadRpvJOpZLgmvx5EvWWFmjicWu12u90dPpIkgmh57hY/VGvQ0nPb2V2ouIRcZn1lg0eAryzTmwvqwWPW0iDhaDQKV4gz4eACR+Vu+2czZVb8WpIyFZQsd62dhEk92oBSnehkYqzeJJp5mF5SbVK1c+97KXsuVaHu00F5OnXK9tTek2i7g5aJr+tC9O1XRs6KjRuFlozCbpbDa9MYl1ejvWddLSTXfYh4OeihXUJOmckyirkfl1gd/Kl4cFecW7vZle5lZAb0zHTtey7vnIUQZr0BmTbMle+ChV557YBPuR8nmWkqrFHzo2USuTNGIuNWSHWkzGJJkenvyeXKnWJOxJSnYJ8sTTztQ7lyzuzvLk86aEUYdNZDLqqL2I5jWHCWlcRmRxL+jFdKGNqZUJePSkYj7adhrHxJJKvYMEb3MsEMwmixhPva8ojdcIyOGQk4g2YEvWW51Zxf4f/YrTBYjS4pUOprW6RI3dYGNpYwjy+DTaFuLA6Z9cMYvyHB4KxHLoUEYr5DN64AXrBO/53GtfKV3cVWK8mZ8G3Wk6bepEg4PiJYMP065ew1i4fkM839P83C8qjNWadFbqO6imbIK3CxtXoegHTFqdh/8Q1hkyEj+HiN29zGUKfHKfTPGp+HPirA0vuqQEK650dJ7DEPL2qwKdIiVp2v4enpPSczN6DG/yz7hfEm/ACphYWjv9MB21T6yPi55iNA01ioxYinc5FLpSSk71oNMZlaaF0SLac2E17iWWJ5947gAvdBzPeeSX+FBPUZ78wvigEr3S3c5dohTlG2rRmJ19LaRlTg9DHi6RBppLPM8l6xJSYt0ug673cO2jjkWLlaTdyscK4887XTRuPfiayjZXPOlCOaiBF7rMX+O6RcCjk4nG4SKX67IHnl+23xabgLM0Heq50B2DLBYnPQDpOgrLNWe6ms4Dz09wnaVujepDB4gs3cUxOkTpUBTqovNrD5ClY9FzN5X2hifd3Ru50rEAWb06S6/1Y3HkamMTbBmQN5+7obzz8a2pNcVSTyDWh9Jj08V7gfx6Hn2ty2IEfn7Mufg8ruM9FfGy3+tqhdzoKCVPuqT1pfvPnmZF9RTonmZF6W4XSi2AMiBFQqfXVNgXkn0b2p4iPlyV4vgVZpzYBPmuGs1H+bzZL8XreEKs0xHJ6YKyMrzFvYkkFuuZ37nEkuBxIYBbQU5roYNaqq/MdfANrHbn5+kSQ/K8fnX3ey50Wb9juTK649pZxJRrOZSPVhUnhnzx4TBKiqUTWv7KtehSrHnz8UXi6E01gzPkWi+6D+BqnTfyyRsA5Xvlo4rqtW/k43XMiw8vKahVU8Y89LOJqpEnXz770SbqR2t++JxTFK11HvIdq/1YKj3v/kY/o6Z+Jg+628u/oRzq7T3swKr1cCsUTz2cXmM=
*/