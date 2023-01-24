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
# ifndef BOOST_PREPROCESSOR_SEQ_FILTER_HPP
# define BOOST_PREPROCESSOR_SEQ_FILTER_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_SEQ_FILTER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FILTER(pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_FILTER(pred, data, seq) BOOST_PP_SEQ_FILTER_I(pred, data, seq)
#    define BOOST_PP_SEQ_FILTER_I(pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FILTER_O(s, st, elem) BOOST_PP_SEQ_FILTER_O_IM(s, BOOST_PP_TUPLE_REM_3 st, elem)
#    define BOOST_PP_SEQ_FILTER_O_IM(s, im, elem) BOOST_PP_SEQ_FILTER_O_I(s, im, elem)
# else
#    define BOOST_PP_SEQ_FILTER_O(s, st, elem) BOOST_PP_SEQ_FILTER_O_I(s, BOOST_PP_TUPLE_ELEM(3, 0, st), BOOST_PP_TUPLE_ELEM(3, 1, st), BOOST_PP_TUPLE_ELEM(3, 2, st), elem)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#   define BOOST_PP_SEQ_FILTER_O_I(s, pred, data, res, elem) (pred, data, res BOOST_PP_EXPR_IF(pred(s, data, elem), (elem)))
# else
#   define BOOST_PP_SEQ_FILTER_O_I(s, pred, data, res, elem) (pred, data, res BOOST_PP_EXPR_IF(pred##(s, data, elem), (elem)))
# endif
#
# /* BOOST_PP_SEQ_FILTER_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FILTER_S(s, pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_FILTER_S(s, pred, data, seq) BOOST_PP_SEQ_FILTER_S_I(s, pred, data, seq)
#    define BOOST_PP_SEQ_FILTER_S_I(s, pred, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_FILTER_O, (pred, data, (nil)), seq)))
# endif
#
# endif

/* filter.hpp
6St1Ix4V5lHNa72/jvrooNB6hdaiwsPrTgH0YfTTDsYxfH8QPeZudDTOw4rQf2JMBpH0GI4eqS6Fm0OSmoiKLDMBVCWJaxZUk/d/xW2SekLhcKwf5V1/kuc1iXAzR+qIi5OlC7Aa0oSXWloRZn+K5+OL6DYr/NtLs6X8VK2OcRaq0A9OLqLtlGOoLiKj+OCVkJ21rLUROxd7E8hyVkBbNf/iCdCxRbRKpt3OnOl5bEr/ujbxp1P9hnmE7im4rhThxvz8Fu2w0BOX5VdvsZp5AU0p8bW+iGy8Of9TgD+R4zzkGleniAuie5hbvxOIDhj1qdN5TjMZirrglWnvzTONo8JxfbYCvAvylxv6ZxvjLiGqMO5vbYx8y28sXkYXWppuc0Y0BNWQywTDIelVz8BmpSENQhp5mvnLBWmRDZHi3WqN/EcJx6eX6EL33Yw1ntXybvtnPQCVFv/RnNAkQ6KnsjWs7bzdXiLQSJmkNJmqMRYQ6zdIOohmWc9tSp0XVkAUUJtqIkPtjckhbxxvx7cwo2gZmTFgXVYfMxH+q23x8ONovfSZoDNvTWE9UWvv1CFPXMyqiMkRSvfm/SZMIh1Jp+yR5SXq1NsXy5VRcoXEYdn/uynlWJOo9XiOVVr+jAyzXL47gLsQCJMDV6jpbc2fT4b/EL3zpTVhQzoqVKO2P0tAehYQKyQI9N/I3u12E00U5HxwCTuyPK5LkXRr
*/