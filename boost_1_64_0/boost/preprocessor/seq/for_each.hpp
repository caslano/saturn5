# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_FOR_EACH_HPP
# define BOOST_PREPROCESSOR_SEQ_FOR_EACH_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/repetition/for.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/seq/size.hpp>
# include <boost/preprocessor/seq/detail/is_empty.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_SEQ_FOR_EACH */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FOR_EACH(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq)
# else
#    define BOOST_PP_SEQ_FOR_EACH(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_D(macro, data, seq)
#    define BOOST_PP_SEQ_FOR_EACH_D(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq)
# endif
#
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EXEC(macro, data, seq) BOOST_PP_FOR((macro, data, seq, BOOST_PP_SEQ_SIZE(seq)), BOOST_PP_SEQ_FOR_EACH_P, BOOST_PP_SEQ_FOR_EACH_O, BOOST_PP_SEQ_FOR_EACH_M)
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY(macro, data, seq)
#
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq), \
            BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EXEC, \
            BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY \
            ) \
        (macro, data, seq) \
/**/
#
# define BOOST_PP_SEQ_FOR_EACH_P(r, x) BOOST_PP_TUPLE_ELEM(4, 3, x)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FOR_EACH_O(r, x) BOOST_PP_SEQ_FOR_EACH_O_I x
# else
#    define BOOST_PP_SEQ_FOR_EACH_O(r, x) BOOST_PP_SEQ_FOR_EACH_O_I(BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_TUPLE_ELEM(4, 2, x), BOOST_PP_TUPLE_ELEM(4, 3, x))
# endif
#
# define BOOST_PP_SEQ_FOR_EACH_O_I(macro, data, seq, sz) \
    BOOST_PP_SEQ_FOR_EACH_O_I_DEC(macro, data, seq, BOOST_PP_DEC(sz)) \
/**/
# define BOOST_PP_SEQ_FOR_EACH_O_I_DEC(macro, data, seq, sz) \
    ( \
    macro, \
    data, \
    BOOST_PP_IF \
        ( \
        sz, \
        BOOST_PP_SEQ_FOR_EACH_O_I_TAIL, \
        BOOST_PP_SEQ_FOR_EACH_O_I_NIL \
        ) \
    (seq), \
    sz \
    ) \
/**/
# define BOOST_PP_SEQ_FOR_EACH_O_I_TAIL(seq) BOOST_PP_SEQ_TAIL(seq)
# define BOOST_PP_SEQ_FOR_EACH_O_I_NIL(seq) BOOST_PP_NIL
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FOR_EACH_M(r, x) BOOST_PP_SEQ_FOR_EACH_M_IM(r, BOOST_PP_TUPLE_REM_4 x)
#    define BOOST_PP_SEQ_FOR_EACH_M_IM(r, im) BOOST_PP_SEQ_FOR_EACH_M_I(r, im)
# else
#    define BOOST_PP_SEQ_FOR_EACH_M(r, x) BOOST_PP_SEQ_FOR_EACH_M_I(r, BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_TUPLE_ELEM(4, 2, x), BOOST_PP_TUPLE_ELEM(4, 3, x))
# endif
#
# define BOOST_PP_SEQ_FOR_EACH_M_I(r, macro, data, seq, sz) macro(r, data, BOOST_PP_SEQ_HEAD(seq))
#
# /* BOOST_PP_SEQ_FOR_EACH_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FOR_EACH_R(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq)
# else
#    define BOOST_PP_SEQ_FOR_EACH_R(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_R_I(r, macro, data, seq)
#    define BOOST_PP_SEQ_FOR_EACH_R_I(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq)
# endif
#
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EXEC_R(r, macro, data, seq) BOOST_PP_FOR_ ## r((macro, data, seq, BOOST_PP_SEQ_SIZE(seq)), BOOST_PP_SEQ_FOR_EACH_P, BOOST_PP_SEQ_FOR_EACH_O, BOOST_PP_SEQ_FOR_EACH_M)
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY_R(r, macro, data, seq)
#
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq), \
            BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EXEC_R, \
            BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY_R \
            ) \
        (r, macro, data, seq) \
/**/
#
# endif

/* for_each.hpp
c4kRYFYC5PJ0SD/RfS4pnEodS6IV01Zti/5sPFjcja+cJf7i+gH/YjkXX8PDh0Fc/JJxqpCsHMWruL7bycCXB4G9NRF70lUVy+i3Vjy5WB5Rj9U7XDk/jlsqF+uXlpJkpkvnYOQpe4LYCSECk3m6kP5NWLKqdmBR3xIowYs2JERtr5W96fL9vmM6vwAzOfByy6QxPmWqLZ4O8qfd1xp0bPuoiJ4y6b6SNhJu/9N5DuHbgm2JFOTNhlfeS+aNyNl3N5rvCrLhPD92Juh/O1+v4UHeq087gHembmEziUoXv2zJ62KasFDC0UFAoWd1syArFj5iWpJcoR5x7YWJc1d8rQVhgddoJ5a2vAFKLyzJCrrgWPqcaEb66s3CYrShnutcMin363URFIx36tE3B521tRXHMC3D4b9Bt8FS+AccpjXZ6kmnUGdkMCduvWwwoud6ZHzd6WX80KSdWWnTWRtLp5jOQDIz/HblPdZ1pmlyMJ3TkJAwGu3Hr311+nBxB5lV3PBdtlDXBDVGyXBrA0PLdsYh1gZLTkTWli7kzIaLyp57+598C+i1Q4C/p7oeK7ZJessANwHjdJbYV2GvoOW308SFiltVD3ng4V9gPkjUslo3tGoLKaVkmklAIRJD78FjvKWfvFRzbOgQY/Uu1A+tGoY+GcNhLygG3jRhKi2DTVISaEDqQKi56+M+Ouc0/E32+LMWo140rQ0cx1Th2JW8Lhi2kvF6D+fblzUfJ9J2ZdKI3MhbRr+NgcV/Qd6LNWvUu9SDPeEpsQRfaN1bgnLjpq7ak7qHE+HzyqfXdW+6O7PZtSq3uYLACOPU8VPzPFCG5n/p39qIYPkd+A7JrfKhQrVgDJNaoLLbVih5itStXeQnAvMIqvkTOvR3eIEXeN+v8E5wlePEYUYMFFheQ/AqgSBDea71Rl/CyLvLNBYKpt4nrHGwNL16M/0GXdDks5Mnkx9/8HrXR4chHitwqa9VPRkIO6LR66DC2VYtvTq06Y91EY63w7TEu/n0Kor1aEuZQ4wDLy2jnJc+m+UpYXyG/ESqMvPUDw0YwYHRChj/lIEPjH/KAgdGKGCMAkZoYEwDRhhgzAdGWGCsBkY4YGx76sc18NSPa+apH9faUz+uo6d+XHdP/bjgZn/vx4UJjGhgv348yeaaDLAk2GFNMbbCCgkHOTH0cS9hmfZvrGAgJwNCCIvTjDcVTIxteeXSfvuA3U65W+xiGIUZFnpmJsL76sBYwTMtMixEcQqdLrmMOCqxZjyPlHLqQQRiMtrzS9h8b0A2u+SlWeHbiktoM+5sgXE84DMYN+fbwzMshF0YqA/KsEjN/a/85vlHaXKzmFZMbxSWUmH9vOgRO14o6K+XtLDXJ8oJem75ITe//iJgE/BVyILW8yhDAg8UlQJPNGfBQtzFF5hQhbWizBC5ounrEMX/nilZwk3pNmBtNs+dM9UsxD81qJu4xivwtbKW5rCdMV6wzZBJqWUw++0ezcK36dymdXouqtdzKe9w4zni0dQoLrD2G6F0l7jk7+tESGpyjG0HvdHX3sVrKQxKyS7LQOZFh5zj2SqIUyavm9mCfpr/WK/SSWqiCZS8W0qGEtALRkpzeIlMqtPwW4oAbgL1mkFQu7ujgfKdPnW+WzT8p9pj2TQVVA2YAylH2CFVL4oh7Iu+hTf64F69djWyFwustEFmF7qksVXz52vwVkI48TG74DUOuRZeM8z7KBD1zKYxF52rq1uZoZZiSCFO5QfD0V8SN1lkx+P4EecNHLuz4Bbxst/jEOBE5qP7x+z5SfRYlMeUvSHlyDZyHRvhG1zRDw4mG3DUGZJRlDjq0pbxdSuzL2lYUT5xqTuqkfwQwo0=
*/