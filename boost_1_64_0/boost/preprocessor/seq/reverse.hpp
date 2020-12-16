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
# ifndef BOOST_PREPROCESSOR_SEQ_REVERSE_HPP
# define BOOST_PREPROCESSOR_SEQ_REVERSE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
#
# /* BOOST_PP_SEQ_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REVERSE(seq) BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# else
#    define BOOST_PP_SEQ_REVERSE(seq) BOOST_PP_SEQ_REVERSE_I(seq)
#    define BOOST_PP_SEQ_REVERSE_I(seq) BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# endif
#
# define BOOST_PP_SEQ_REVERSE_O(s, state, elem) (elem) state
#
# /* BOOST_PP_SEQ_REVERSE_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REVERSE_S(s, seq) BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# else
#    define BOOST_PP_SEQ_REVERSE_S(s, seq) BOOST_PP_SEQ_REVERSE_S_I(s, seq)
#    define BOOST_PP_SEQ_REVERSE_S_I(s, seq) BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# endif
#
# endif

/* reverse.hpp
dLe4O5GWvXFNtD69sXUF9HcSb9lnlhScLfk4PgW7sx8cHV98I7KKXKKyaKHbkBliu9gtzoiL6Pk+izQyExxtW+QFyVQk9L8HWHaZ+knth9o/UIV9Cl2fh3kc9U/Dg95FexAvMNAP/xCMD46gBwqR2KHTGEkWUpyUIevIbnIAfjKfUd9oB12eZqxCF/QOCWR2s5Rufw+ZJ8wItAUTrGnWZmuHfu+bGWxGKKUelbQojUSeVAEqG4VMqS5cYFMkuG1ob90e+XakXQ+sNtGebl+zc6AN7uEMc0Y505yD+o6RD3eK5tDG1N41/fVYATaIjQPKTqD5bKMb35nimigkt6lu2qekDTJjkwXcyaBg6Z9eMYdCRWOHjuOPAvDMY42JSOHDsVHROLWX4N5S+K8bQW/S+uDSz05st7D+CvOs63tlvCrIK1vqpPyyd9P7zxLBv/yebzPfgWSwpxgBdC8A1+WU+WUN5IHNZGukOsOB6v3yMFQzpaqoaqpW6gekI2/UF1UI3NUHrDUL+D0BL/banwxtC1WJrb9JToQzKkt+T9aTHWQvMHsTeM1s5DA4/H4zozV66Y3ILBaaa82d5jN493fmJ7ikOFYC/P5kyNvTIS2OgI8fbuWgDs6qJu1Me0B9ltDt9Ciahyf0F5rEToeeuord5h+8M1mn27/90KDr9n248wnOLucDnE4a/Y2H4yp9KxzjrnI3AON74Lrvuim8gvomWBU609cbjfkuhNM+4NVGpzkRk9qvHckL/TVQIrjj9ELCG1dCptpUv2hfIdaJq8B6bGhEM3jgIVCIJXKLeoXuZ6U/JZgV88asYWz9NjsnqUfaaZ0/TT6SlFYWYLUh3eilZ1mRK/v6tVMrtoKtQz58kBXlpXCCw3lykUZY+hu234nl8D13xEPhw+E0kYNwWhNivirX7xZvoBG5oZKi3auK5LYlvPCKYC9y/dihaHgOm/Qmo8hq/D+/JRkMxxgPPYgwLbDHCvM6OrfMVknwfEc4ggN4Rywx+SP0FH1Iq9u1ofLfOCmh5TWcOmh2pNvXnQqm/vX95SG0ZnW95vCEqVguVvH/nH4P5KP4eJ0tzdM38dVa4XfwPfwgP6Z1/ipalfv8MU70Lc40loin39elgc+M0N8MFhZUePABxfXrw2qipn572Ey0Fl3EQDEOznONuIC29xV67lQyu/acVH9FWEpWkDFvNuvLpvor4G76bd4wOQpnNE2/1lqmvwHajhzr4FdXelP/TQCv5Ad0WDH3pBT6G9mcKr++3UtVXJVBMh+lv5htDmfRSfXQKf0InVnO0N+MrED/sxneda86rE7GvPjT7PpMvdEv/xL4SfxUfoaY1wfazXq+r18hVAFG6uo3FO2QCfTSzeTImK+MdAK6BI3vBv0txn7NzhfR9N7Vb+beIVmKEySC74153Z5dv8SmMa/c9Vu6akEt/db9t/r7gD5wwsN0yzQtmBMsQpq6Blnqdrjig8Fx/dbhJjLUJ79+v9A/dqhh3F/vaeEkBUlHspCcJL92yVLzfyUSRb7VGUMb/Xdl9IUHGkHGkElkBplHonUfulmzz2FyEgx0Vbeiz8gb6GWYkcCI+dosAzxSbjhqEz7J19+dVdFfRjTWb2i6xLxv1I3pOOOP7Zx/SKN1HMfXnYWJlIWUhIXUKiuJZ8+ebc+2Z3OElISUXBIj+jFCDrkirEaNy2KEhJXEKIsVFiMkxnXUCKlREiuOGJeEHRJSFhISIywkrOy4otfz7uno5+Vd1y/o/unf1Of9/nw+7x/fIirhTGCPumhzhzeo93X/kcXX3GkyW+Rfu7t3N0kby4wpJzqgHfxG0ja7NJvHzPtR1h4xp7RtPce1+JJZ/eFi1JY=
*/