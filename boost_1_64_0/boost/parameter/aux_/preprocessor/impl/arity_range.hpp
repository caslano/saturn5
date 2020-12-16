// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARITY_RANGE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARITY_RANGE_HPP

// Helper macros for BOOST_PARAMETER_ARITY_RANGE.
#define BOOST_PARAMETER_ARITY_RANGE_M_optional(state) state
#define BOOST_PARAMETER_ARITY_RANGE_M_deduced_optional(state) state

#include <boost/preprocessor/arithmetic/inc.hpp>

#define BOOST_PARAMETER_ARITY_RANGE_M_required(state) BOOST_PP_INC(state)
#define BOOST_PARAMETER_ARITY_RANGE_M_deduced_required(state)                \
    BOOST_PP_INC(state)
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_ARITY_RANGE_M(s, state, x)                           \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_ARITY_RANGE_M_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(x)                                  \
    )(state)
/**/

#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/size.hpp>

// Calculates [begin, end) arity range.
#define BOOST_PARAMETER_ARITY_RANGE(args)                                    \
    (                                                                        \
        BOOST_PP_SEQ_FOLD_LEFT(BOOST_PARAMETER_ARITY_RANGE_M, 0, args)       \
      , BOOST_PP_INC(BOOST_PP_SEQ_SIZE(args))                                \
    )
/**/

#endif  // include guard


/* arity_range.hpp
BZfBNXAV/BL8MrwBfg1eI+H/CtwMvwrvgdfD++EG+Li4fwLWwqflWMqLfBsnrSzKyxcTtXxfCFvBRab+/I5J5vJiuj9K/6+l9A8vg+OkX5UD02Gu5MuVcIQcS3goZPHL78gkLTyjYDM4BurXtZHr+lpcd6VcNx72gRPkuoPGN1hVF2PagZlSXmfBTvLccSmsgV3hXHg5nAfz4Hyp/wF4lbibBRdJ/afuq/xcAqthCfwSLIdbYTX8vtw3n5Drn4QV8Bnoh3shfqj3JsvhH0TvTdMe4luMb6nqPWnMPh2dk7R4dYFt4aVwDOwG82FPuBL2gjfC3vABOBA+KsdPyPFrcDD8BxwCu+LxMNgLZsHeMAP2U8fh/sM2KXejJd3N/YfCRC18M2EnWATV8xvsBWfDUXCelMcB+nc72Ez8S8AY3yAk/9tCoz8q7v9sUX4/kPz9VNqjz6S9T6Cc3gebwR/C5vAATIYSL/kmRF5bxGuGW+IFk+FVUs9nSf9jDlwE55r6oWvFv+sswrlRnr82w37wVqlPd8E8eA+cD++FHvgwNPZOl31cWqn+VsP3Tt/TgD17+9yQ4MrDHL3Veu/eonXW+50k35bQtOeJjXuedCU9rfY9Sb8t4X9i75OmvXz/vb1P8slHq/1Pdh049x4oC29LaNQ+KIcPNGwvlOpQucI8itmPOYpJvj3B1QeTh6nGbMXsxhzGuLZQ3zHjMF7Mesz9mP2Y9zAdeKGajpmNWYt5GLMXcxSTeif7B2PyMQHMJswuzGHMGUybu7gWsxBzDWYrZjfm8F1Ne7U0/Zp+Tb+mX9Ov6df0a/o1/Zp+Tb+mX9Pv/D8n9/9jcyMPDG0A+G/t/9eFedAPduNZX+3/t8JXW1HlDYZ8rtb2/mt+icuY69TVHTvfa0hn3qkMVmOjcwtmepaGLnU1cJ5XrvhbIY/Z02Xs/TTMI6Ewhf1lBpVM+w8JsCxTZSXbFsn469S2ak587WrLtUzEH/4z7YnmM4/Vvkqdv9jYU96vjhNN7tE0zW+ZqM73N50naKa1jIaq81eqdcMuY7x/KL12tudbbjvyiEDdxN+vtcU0aH5Qs7bzlH8uX01NeFx3KicvkTib56M9lahdXCJpuQSznbRcG5mWRKhhaaeu4z/ZC8u8/6L1mp1x0jpN0uab6nyxSpvLxV2KKY3bSRp/V9KwPbGTNFTpVyFpNx8WtT/vHCvKmnWapZnnD5niZJ6PUysThdZLWn5DyqVriDktzQWyYWnK9ecsj5WcN5fHteo4yeQeOUnTTrCVOl+n0nQKJrQG6K5E6mUz0gLRxM7NkxLbh/Zcadc8ObFT8+TUlOZqbrpFmpKekeEyleu+Smch41ESLfOtAxyp3BS4upGSrZSdhJ9j85z4FpcobXSlPljkY6pFXagbcv66oM+9PSMNVSkmQerE98m/HUb+Sd6xxluQBXH8VZUev5fxZir+MkdG4v6SuuZSOSZ3hnJsPc9a/Heb/Fkq5Zp4qnOjmW+SYL1Ol6lsPNZN7Y2nFtzSy8YJdT5FjvVwJJrc14p72f9Tue8XE249H9a310zLSzTjb9+QNklLd+JGuteq42TjeGnEvKp3LpLvWVKHpst+MOlDzXlgzLozpVmpEYfhyu0Uq7TGn+j0Ko1Ir7nqfAsjvQLquLmx5sttEvcUzLXtGz4XS8WVMJrnQ29oId+e5YIRmO8Rpj2DVFxVWSsJBEqZQ6Qv/WKOr1X8uNZi7RfTHkgH1PmefItOsixP5uvv66bKYrXLeh1Gs1v8jm2X3lHnk6zqvjr/ijrfleMkc34EXSY/fqnctJB5cFrap2JK2zd87qSk/TnXUyGu2BFXaROGSh5RKtVvPx51FOY=
*/