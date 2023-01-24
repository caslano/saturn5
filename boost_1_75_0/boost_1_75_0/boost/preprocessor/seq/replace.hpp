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
# ifndef BOOST_PREPROCESSOR_SEQ_REPLACE_HPP
# define BOOST_PREPROCESSOR_SEQ_REPLACE_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/comparison/equal.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_REPLACE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REPLACE(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i)
# else
#    define BOOST_PP_SEQ_REPLACE(seq, i, elem) BOOST_PP_SEQ_REPLACE_I(seq, i, elem)
#    define BOOST_PP_SEQ_REPLACE_I(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i)
# endif
#
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST_EMPTY(seq, i)
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST_VALID(seq, i) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_EQUAL(i,BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq))), \
            BOOST_PP_SEQ_REPLACE_DETAIL_REST_EMPTY, \
            BOOST_PP_SEQ_REPLACE_DETAIL_REST_VALID \
            ) \
        (seq, i) \
/**/
#
# endif

/* replace.hpp
TpbQ7wmNCXbss7IjFczrQmn4mbWSo9lXj5fnupHX96RT6w7GkKnYRjPdAMoeF4q4vK896T6JdfFJZ4T6v3kpEp4tV5rO3ouM5n4Br7TSlLQVPQPMm/zaHC2gjXVmBuMmElmIYDjJk+Odoix2PaRoYVqX2hxOuBwa5f9jc9982/Ch85R8omHYqZaPwtjNaMJycNVJeZLPTF91H5tvInWhulNq34Yjr2nnOc5IYFBouaX3fes40cO84gn9b0uivaHfBv5R/or0RFO3+4YCT421Wd3D7Ki3rFELaIo5fMsD5UnsWpuvdnmyzVYy2XMspxvU7sYyc1mZ1aXi/lQTKfPPFhayvvyTVDVGM0QzSjO8OD90bXW8jDaThEk/n8YnH1u5n6eeJLZvfitUTRCL4PJj9yv2erLT1q+T/roIVDxXfNP7Pu0VHNw+hnqKu0D03lf+eMGDH14ybet54Yx8wbQILEENYgxDtFBqtmG8ZFGasfmKa/tS/EcxygyW+JDzENmQ4FF8PW5reAFR7kuizm28l3ghEfgvb9mUDa2ZDKWZa02wmJnBLwy2jNtpqINHtzCcJEkoXwJe93FF9FkL4qqlf7cuD39nFUZ1SXsWPFqAcjeosRXygTKU4MPrw60/Db+T3gg/97hVZk57Up01yz5vSxQMtbYxfHf1vvml7femB0Vg28iLojdMM7xLbvd3w5W3WlMz/4rtQqIfiHM9
*/