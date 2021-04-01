# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2015.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
# define BOOST_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
/* An empty seq is one that is just BOOST_PP_SEQ_NIL */
#
# define BOOST_PP_SEQ_DETAIL_IS_EMPTY(seq) \
    BOOST_PP_COMPL \
        ( \
        BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq) \
        ) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_EMPTY_SIZE(size) \
    BOOST_PP_COMPL \
        ( \
        BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
        ) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq) \
    BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq)) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
    BOOST_PP_BOOL(size) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq) \
    BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq (nil))) \
/**/
#
# endif

/* is_empty.hpp
1d3mrtzvQF/RCFkD2nmTQTFj4ue4WIEvjecarmqkPPanOYROPMDBrO65fhDBxcCiea88oyYmOqJccs53ZZXWMqbydiAwmz9JwEEuqUMfs5UURmSbd8vvHS9WaAuLS6m648NNi2fQvd5JGcMjDsJZPmQlYKrs83truwfVhKcr/XNk1dLtkKwY5Q+utGZ8POAXtsHUzGJfqSmbjUxb80evsn/iQeM8cKydJiQBgKnGTyuIJKA7ppCDAc2rwBxBjdYkXYfMiTS0Ctrr1sxcsR99Wl7HJRXDAIz1vfu+UcssZ1b7mijUJek9qOI+Vz0qoXL5idg5xlOs0e3geUYH8dnY0BR3ztkb0nveRkXls+K+s9nCkf3Av2xBNTXG2xSGzOmOb0OwobZK2nMWx8ws1Eu93WuwCJAuB/oHcPeR7zmKBTVjGF4Zl+Dso3/7VyOu0Cd0c4F8dxukyMNXbT14N6e/kZfzFF9awL3hrZkW5Q29yV5OvlmvPbxry8fbhsx3X+WeY3QvrRYSlioYSrtUyXSOCT0R4L6YGEK3snwqfYXgejWcDaXS/NbXPktGQw==
*/