/*==============================================================================
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#define BOOST_PHOENIX_typename_A(N)                                             \
    BOOST_PP_ENUM_PARAMS(N, typename A)                                         \
/**/

#define BOOST_PHOENIX_typename_A_void(N)                                        \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(N, typename A, void)                    \
/**/

#define BOOST_PHOENIX_A(N)                                                      \
    BOOST_PP_ENUM_PARAMS(N, A)                                                  \
/**/

#define BOOST_PHOENIX_A_ref(N)                                                  \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, & BOOST_PP_INTERCEPT)                     \
/**/

#define BOOST_PHOENIX_A_const_ref(N)                                            \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& BOOST_PP_INTERCEPT)                \
/**/

#define BOOST_PHOENIX_A_a(N)                                                    \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, a)                                        \
/**/

#define BOOST_PHOENIX_A_ref_a(N)                                                \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, & a)                                      \
/**/

#define BOOST_PHOENIX_A_const_ref_a(N)                                          \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a)                                 \
/**/

#define BOOST_PHOENIX_a(N)                                                      \
    BOOST_PP_ENUM_PARAMS(N, a)                                                  \
/**/

#else

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PHOENIX_ITERATION                                                 \
    BOOST_PP_ITERATION()                                                        \
/**/

#define BOOST_PHOENIX_typename_A                                                \
    BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename A)                   \
/**/

#define BOOST_PHOENIX_typename_A_void                                           \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PHOENIX_ITERATION, typename A, void)
/**/

#define BOOST_PHOENIX_A                                                          \
    BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, A)                             \
/**/

#define BOOST_PHOENIX_A_ref                                                      \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, & BOOST_PP_INTERCEPT)\
/**/

#define BOOST_PHOENIX_A_const_ref                                                \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, const& BOOST_PP_INTERCEPT)\
/**/

#define BOOST_PHOENIX_A_a                                                        \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, a)                   \
/**/

#define BOOST_PHOENIX_A_ref_a                                                    \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, & a)                 \
/**/

#define BOOST_PHOENIX_A_const_ref_a                                              \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, const& a)            \
/**/

#define BOOST_PHOENIX_a                                                          \
    BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, a)                             \
/**/

    /////////////////////////////////////////////////////////////////////////////
    // Begin Perfect Forward argument permutation calculation
    /////////////////////////////////////////////////////////////////////////////
#define BOOST_PHOENIX_M0_R(_, N, __)                                            \
    (((A ## N)(&))((A ## N)(const&)))                                           \
/**/

#define BOOST_PHOENIX_M0                                                        \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_M0_R, _)             \
/**/

#define BOOST_PHOENIX_M1_R_R(_, N, SEQ)                                         \
    BOOST_PP_SEQ_ELEM(N, SEQ)                                                   \
/**/

#define BOOST_PHOENIX_M1_R(R, __, ___, ELEM)                                    \
    (BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(ELEM), BOOST_PHOENIX_M1_R_R, ELEM))      \
/**/

#define BOOST_PHOENIX_M1(R, PRODUCT)                                            \
    ((BOOST_PP_SEQ_ENUM                                                         \
        (BOOST_PP_SEQ_FOR_EACH_I_R                                              \
            (R, BOOST_PHOENIX_M1_R, _, PRODUCT))))                              \
/**/

#define BOOST_PHOENIX_PERM_SEQ                                                  \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_PHOENIX_M1, BOOST_PHOENIX_M0)           \
/**/
    ////////////////////////////////////////////////////////////////////////////
    // End
    ////////////////////////////////////////////////////////////////////////////

#define BOOST_PHOENIX_PERM_SIZE                                                 \
    BOOST_PP_SEQ_SIZE(BOOST_PHOENIX_PERM_SEQ)                                   \
/**/

#define BOOST_PHOENIX_M2(_, N, TUPLE)                                           \
    BOOST_PP_COMMA_IF(N) BOOST_PP_TUPLE_ELEM(BOOST_PHOENIX_ITERATION, N, TUPLE) \
/**/
    
#define BOOST_PHOENIX_M3(_, N, TUPLE)                                           \
    BOOST_PP_COMMA_IF(N) BOOST_PP_TUPLE_ELEM(BOOST_PHOENIX_ITERATION, N, TUPLE) a ## N\
/**/

#define BOOST_PHOENIX_PERM_ELEM(N)                                              \
    BOOST_PP_SEQ_ELEM(N, BOOST_PHOENIX_PERM_SEQ)                                \
/**/

#define BOOST_PHOENIX_PERM_A(N)                                                 \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_M2, BOOST_PHOENIX_PERM_ELEM(N))\
/**/

#define BOOST_PHOENIX_PERM_A_a(N)                                               \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_M3, BOOST_PHOENIX_PERM_ELEM(N))\
/**/

#endif

/* iterate_define.hpp
Z+AWzMC70Ip3Yy5uxVtwG27E7bgJC/Eg3ovP4w58BYvwVXwAP8FiVDK9Gy/GB9Ef92Ar3IshuA+7434cgA/jQDyI6v16eVf+Ep3rpixZfossfzZGoBX7oQ1jcQmmYC5m4QrMxjw1HXnvPG7USecJSedJSadUyvNpnIjPYBI+h8vxeVyHR/FWfAkd7VPyDng8otM+NU3SmS7pxMv6nIE9cCb2x1k4BP+A8Thb1udcXIjzMA8TcSVej1swCe/GZNyBBrwfU3A3mnA/pmIpLsRnMA3V4+8a7/uPD9vJ/Tr0x4/Ref0YI9MV6Vw/fibLfQoH4r9wClbj9fgFZuBXaMXTUs5fy3J+g9vxWyzEGnTc35X3o+NUnfu7mX6kizdge8zGzpiDPXAJ9sdcnIDLMBFXYBrm4Qq8EW/Hlbgbb8KH8WZ8Htfh97gef8BbsQ35+SP2xtvwctyIg/B2vBI34TjcjJPwDpTrfHn/Of/Wuc6/i/Ga4t2yPPdgJG7Dq3A7TsQ/4TSkzGQ9yXvOMVdnPe2R+T6EnXAvdsP9OAQfxqvxEZlvCSbgo7gAD2I6PoZL8JCkW0WUSbqrZT2FKefLku5xWU9/l+U5gSPwfYzBKpyJH+N8/ARvwk9xLX6GRXgK9+DnWILVWIlf4Dv4JX6NX8l6+hovIj812APPYBR+hyPwe1lPP8h6qsOZ+AsuQxaIfosAv1HSv8j5TnPlGUXHcs61X2fL89byHHwgBmN7DMeO2ANDcAx2wkkYjnOwM+ZgF8zDS3EtRuBO7IZ7MRIfw574Bl6Gx7EPVuHlWIN98Ufsh6Fktj9eigNxKA7CWTgY5+EQNOBQvAmH4TociTvxSnwaR+ELeDW+hjH4Lo7BKrwG63AsNlfuC2J7HI/9cAJGYyxOwUk4C+MwGadiKk7DDJyONrwWN+FMfAL/gC/gbDyJc/BfeB3+hHOxhXKfD3tiIvbDJByFyRiLBpyK6bgGM3EHZuE+tOBf8QZ8Bq34LC7BaszFWlyGyvNCy7ErrsbL8GYciGvxKtyK03EbZuB2vBkLcTPei3fifXg/7sCdWIQH8X48hA/gEdyJz2MxVuMu/Bp347f4INbiQ9ihOds7Xor7cCTux6vxAM7GEpyHj6Kzv1pLQf31yym3/mpZd+p4BTJex7OMV+Lj/Cp9nN9pzXjUQZfxOPao4wVuVo977AddxxuhjkdslvydZbwYH8dL3iz5O8t4+T6OV6RJN9dtvG8045U1MB51Xx2vysfxuIks5dfweIF3+Da/KBmv41nGi/dxPItmvAK38WZqyqVAzZ/neFM045Woy9vweGU+zq/KPX/64znetwthDY5H3Onb/GLu9L4cBs148TJe+7OMZ/FIV3+8Ah/HK/FxvEpNufi5jTdYM95p5/I2PB4XT7K8DY5HbJH8nWW8GB/GG04ky3jdde7zNpPfoTXHS/BijMAWqD5vJtPP1DlvfFzuczyBnbAUL8enMBafwTh8Dq/FIyjz5aRT2sd15rtInj9ZjO0xHUMxAy/DTOyLWdgfLaiWi8y3v7f+ziX9fBlvmE76Nkk/BzviEuyCS3EA5uJgXIZDcDk679NUyny36dynuV/K+wFshzuxGxbjANyNI/FBjMM9eB3uw8W4H3PxYfwjHsB7sATVfnjv9v4cVVFbSR9b404Mw2LsjrvQ2X5SJvMZ2cSz/eQJOb9+GvvjMzgMn8VYfA7n4hHMxnLMxxdwA76ID+JRPICv4BGswPfxVfwOK7Ev6b+BV+CbOBDfwqF4DB3LLe+FxAE6y10q7dBl2AGfxc54BC/HcnS2sxfIfJJ02tmbSHtTUwzAZtgWL8Ye2ALHoT/OxJY4H1uhc/6B27w/17U=
*/