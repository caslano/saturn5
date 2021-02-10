// Copyright Daniel Wallin 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FLATTEN_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FLATTEN_HPP

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_required required,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_optional optional,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_deduced deduced,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_IDENTITY(x) x
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0_DUMMY_ELEM(z, n, data) ~

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub)                            \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_, sub)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AS_DEDUCED(x)                    \
    BOOST_PP_CAT(deduced_, x)
/**/

#include <boost/preprocessor/detail/split.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(sub)                        \
    BOOST_PP_SPLIT(0, BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub))
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(sub)                             \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub))
/**/

#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_optional(arities)               \
    BOOST_PP_TUPLE_ELEM(3, 0, arities)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_required(arities)               \
    BOOST_PP_TUPLE_ELEM(3, 1, arities)
/**/

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0(r, n, elem, data)               \
    ((                                                                       \
        BOOST_PP_TUPLE_ELEM(3, 2, data)                                      \
      , BOOST_PP_TUPLE_REM(BOOST_PP_TUPLE_ELEM(3, 0, data)) elem             \
        BOOST_PP_ENUM_TRAILING(                                              \
            BOOST_PP_SUB(                                                    \
                BOOST_PP_TUPLE_ELEM(3, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(3, 0, data)                              \
            )                                                                \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0_DUMMY_ELEM                  \
          , ~                                                                \
        )                                                                    \
    ))
/**/

#include <boost/parameter/aux_/preprocessor/impl/for_each.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                             \
    r, arity, max_arity, spec, xform                                         \
)                                                                            \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_R(                                       \
        r                                                                    \
      , arity                                                                \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(spec)                            \
      , (                                                                    \
            arity                                                            \
          , max_arity                                                        \
          , xform(BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec))            \
        )                                                                    \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0                                 \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_optional(r, arities, spec)       \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                                 \
        r                                                                    \
      , BOOST_PP_CAT(                                                        \
            BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_                            \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                   \
        )(arities)                                                           \
      , BOOST_PP_TUPLE_ELEM(3, 2, arities)                                   \
      , spec                                                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_IDENTITY                              \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_required(r, arities, spec)       \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_optional(r, arities, spec)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced_M(r, arities, n, spec)   \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                                 \
        r                                                                    \
      , BOOST_PP_CAT(                                                        \
            BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_                            \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                   \
        )(arities)                                                           \
      , BOOST_PP_TUPLE_ELEM(3, 2, arities)                                   \
      , spec                                                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AS_DEDUCED                       \
    )
/**/

#include <boost/preprocessor/seq/for_each_i.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced(r, arities, spec)        \
    BOOST_PP_SEQ_FOR_EACH_I_R(                                               \
        r                                                                    \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced_M                        \
      , arities                                                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(spec)                            \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC(r, arities, spec)                \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                       \
    )(r, arities, spec)
/**/

#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN(                                      \
    opt_arity, req_arity, wanted_arity, specs                                \
)                                                                            \
    BOOST_PP_SEQ_FOR_EACH(                                                   \
        BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC                                  \
      , (opt_arity, req_arity, wanted_arity)                                 \
      , specs                                                                \
    )
/**/

#endif  // include guard


/* flatten.hpp
nMKrG7PtXYz6T4ZuIikYvy3g45GyijBcPobPJn+RETmPpESDsdjI9ijWgT6acBYJVpl4011i3ubU9kWaoEz4ZYaBKG3RkzmwGFmyNtol6H44X6xG0CVfsq3oIjeKoys1YqMvV3ys9embxjQJxR60Pe7wK4kpfAr4m2EV1VCJtgZSUeVPFA4m8pcJjHenj3hIucfCcIM7ocJNN4wI6+Qugk10/Hrx9tXr0/N3z1Zz8R9QSwMECgAAAAgALWdKUmL+W4XhmgAAEOwCAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy9ydW50ZXN0cy5wbFVUBQABtkgkYOy9fUPbRrY4/H8+xWBIsbt+AdJmu1DSJEASniXAD5N294bUlW0Za7ElryRDaML97M95mTdJI9sQ0k33hnu3saSZMzNnzpw5b3Nmeak1TeJWNwhbfngpJn48erD87f39PVgWc/869L8O/MG/WOE4jv7l91J34U7no+D/g0pn8O+cJlrC1PjYqYm5NT6KKtXoyDZ+xN+dzpxmzrBj+J8WVjzr4E9482AZ6u1Ek+s4OB+morpTE+t/+9sPoiE21jbW62LXCwN/JNqpH3b9+LwufuzTm6dD7/37ZuI/qQs/Fd6oSYBOh0EikmiQXnmxL+D3KOj5YeL3hZeI
*/