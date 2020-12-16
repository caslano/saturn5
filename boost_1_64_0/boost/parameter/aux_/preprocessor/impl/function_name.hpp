// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_NAME_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_NAME_HPP

#define BOOST_PARAMETER_MEMBER_FUNCTION_CHECK_STATIC_static ()
/**/

#include <boost/parameter/aux_/preprocessor/is_nullary.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(name)                      \
    BOOST_PARAMETER_IS_NULLARY(                                              \
        BOOST_PP_CAT(BOOST_PARAMETER_MEMBER_FUNCTION_CHECK_STATIC_, name)    \
    )
/**/

#include <boost/preprocessor/seq/seq.hpp>
#include <boost/config.hpp>

#if defined(BOOST_MSVC)

// Workaround for MSVC preprocessor.
//
// When stripping static from "static f", msvc will produce " f".  The leading
// whitespace doesn't go away when pasting the token with something else, so
// this thing is a hack to strip the whitespace.
#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_static (
/**/

#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_AUX(name)               \
    BOOST_PP_CAT(BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_, name))
/**/

#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC(name)                   \
    BOOST_PP_SEQ_HEAD(                                                       \
        BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_AUX(name)               \
    )
/**/

#else

#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_static
/**/

#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC(name)                   \
    BOOST_PP_CAT(BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_, name)
/**/

#endif  // MSVC workarounds needed

#include <boost/preprocessor/control/expr_if.hpp>

#define BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(name)                         \
    BOOST_PP_EXPR_IF(                                                        \
        BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(name), static              \
    )
/**/

#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_PARAMETER_MEMBER_FUNCTION_NAME(name)                           \
    BOOST_PP_IF(                                                             \
        BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(name)                      \
      , BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC                         \
      , name BOOST_PP_TUPLE_EAT(1)                                           \
    )(name)
/**/

// Produces a name for a parameter specification for the function named base.
#define BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(base, is_const)          \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_parameters_const_                                \
              , boost_param_parameters_                                      \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

// Produces a name for a result type metafunction for the no-spec function
// named base.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(base, is_const)         \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_no_spec_result_const_                            \
              , boost_param_no_spec_result_                                  \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

// Produces a name for a result type metafunction for the function named base.
#define BOOST_PARAMETER_FUNCTION_RESULT_NAME(base, is_const)                 \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_result_const_                                    \
              , boost_param_result_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

// Produces a name for the implementation function to which the no-spec
// function named base forwards its result type and argument pack.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(base, is_const)           \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_no_spec_impl_const                               \
              , boost_param_no_spec_impl                                     \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

// Can't do boost_param_impl_ ## basee
// because base might start with an underscore.
// daniel: what? how is that relevant? the reason for using CAT()
// is to make sure base is expanded. i'm not sure we need to here,
// but it's more stable to do it.
#define BOOST_PARAMETER_FUNCTION_IMPL_NAME(base, is_const)                   \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(is_const, boost_param_impl_const, boost_param_impl)  \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

#endif  // include guard


/* function_name.hpp
OKdiyiwAv5chGS/tBLtzNbwoC8rKjiwoPMZRXD6ptKqiHNXFaLIs4+BtIxzpUd09NdqmW1IwcgXeAHwH53/1ZWRceo4DzlBOh7PF6fE6a72UVWMH4/CMEDsL6n2LiRnJcHOzPxAy3ZHvKMiIfHHJV5Hzt8b2kRn9v/76aznbLkwZhnN3HWFACiuPLy2KpDBAnYoyunDMdvhsObihCbgCOdDlo0vwsu/oxefFX0e+owx9cWJGCvYfgnYM43VJdTjqnC1YAAr7UIcRwOcY57HGZsYQYztxXLRJpg/tQYWHUX2d7Lv3wvYQ9OGw9NGW6z2UENKWbRj4ri1YfdEOSyvYflZPtMHaAjaG78fnDah09WUY86e8fcY7L//6zaz+qZfsvP1DM0/CEP98tj+8Wd7WJzzp7rqho2PygudqkdP+abZ/vysPffLTYxZ9tf0vm93x3fsX7YUw5Usj+1dek597wtTdP3h85NAVz2x9YaFhfM2Ob7zig/OcK8f8Musb85ayNQcgXv4gdnxb6dsP9Gyz/a2vbbr/9s+NvAGN2W1WZP+4U7PvcZdfNyfrxWf3f/3kh9FRFWz/gWcV9H+46vvD541cuP6N7FuGIH6U7b/j2rqqhWlrP3ry9t1/vX52O3zv72f7rzx/4obHR868POcRx61bNB72Nnwj2f69Oj7rzP5k4+9erDz9vdN3soeRw+TyyP6M6hW3nLR75Ujfzs9VFOR/Dq/qF1k9n3tv/n2zLnEUnfbxLUct/ylzNa41O769fFjn+fsdUp5Ze+LWKZNPbMAcA9s/ody1w2c1/ftu1jzqk7MP2AB7Xy/6e8OnqcaIz1KNcSg1KK0oHQWwoQMXoSxH6UUZvTLVWIz96ei/Mvzfjv6aMQF2j6Ngc0FZgDK6BPdBKb4T5c2j4SMObc5dhrmOY6Ej45e1EmVIBXR0lBCKF9/TUAkfdmDXcagPypwq2K1Q+lBGT0TdUdpQ5uGYsmrYFo6H/Q5lxCTYl7DvpRropcBxJ8J2ijIT5f2TUC876ocyFyV0Mhr6eaqhRYsWLVq0aNGiRYsWNSJf/4+o1UHMNg3o/ymK9P/I57tnGkaSjx2T8qL2gSnQq8eSfQA6K5N9UFJR9kaZvw30z7Q06MttjqrqQkcpau9xetla4ptDz87F96NnmC1ge/x3Ezs2m+nVxuB6NY4/KGMhOxZ6zk5Mbxb16BukHq9a6lGN3se1gMqdvB5v/4V69FjrQfr7JymD6eOD67NdV0b2Ly0766B1hxxc/u1Du2Quydh8Hq7tVZH9Hx3x08wjZ1x3dn3t0tJcW9GDf11P72Tf/8qZm9RvcuucNZOvWzBj/oLXa+BvyPYv/P4r19RdNvaNL7p3/zVvrf1pMPvD4Pr+OFbPa5Zkdq9csuPlU3a66oBx477YMLgdILm+P7h9oJF9/wlZl7zvPrv/yTNml27TlfnL94PbAZLbPQa3AyS3qwxuJ4HdgNkIrHaBDdCv01elGnuijEepQYm3FTRjX6y94O/ZCmasSrQXzF6V+oc2A24vmLsqub1gIfZbbQZLsb1ylbYbaNGiRYsWLVq0aNFiGP+0/h80G/CRtz5/DHYx/R/+pBbPz62S6v/HOrGVVRAMmk210P3ZkfONwzIM1+nuSMXcblELVAH/M+/4cLO9Nuzxuu1Nbqoc1tMP+Exvns0wW006kZ0mTi8yW3LzIw21t+bZWI2bvGMiBwcDrt9lwud2s8HuyYtppDOIaOIBG0Mb6fbbGoSk20/amOngDsfE4hKHCfuGv57nVRDnLqZzJxiEdG669VzQWs/tB45AuYHpnp/XPrHpoe133j51VM+PXe7Vd0E3w2f21ZgvXq31Iy1atGg=
*/