# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2005.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_BINARY_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_BINARY_PARAMS_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(count, p1, p2) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(count, p1, p2) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_I(count, p1, p2)
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_I(count, p1, p2) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M, (p1, p2))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_IM(z, n, BOOST_PP_TUPLE_REM_2 pp)
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_IM(z, n, im) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I(z, n, im)
# else
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, pp), BOOST_PP_TUPLE_ELEM(2, 1, pp))
# endif
#
# define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I(z, n, p1, p2) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(p1, BOOST_PP_INC(n)) BOOST_PP_CAT(p2, BOOST_PP_INC(n))
#
# /* BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z_I(z, count, p1, p2)
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z_I(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M, (p1, p2))
# endif
#
# endif

/* enum_shifted_binary_params.hpp
KwDNpXoVQF0Qn7VkNMoOAS+1Zy+CW8n+etJdbW7ooz7jx2MyG2J8ZD+Bn3UKztzlhs+YpR9DWWdntOwxa1Vl57PMJJKZFFM3J3NgzYv13rs7NG8PMZhBjz6uz3qedaWLJ7t67QzUpkRiZzyeq3l7vsZaU7cmLjuBOtfVY13c8fIw9Z4fpewUzuTLcTg7U/McfqHPwVFO4Ro01222cExlvTatderDBQ1VjXbqx6SqTAvI2sF9mMvQ/4cFDfUyWWTeGMsuni23HDQGY329svoyEw9+5U68zhVtMwPym115UeoDPkXs20zWXE00cjl7vVSfO8FEV2Ut6m6Td3b8aOP+XiOxtYB+44/5/NTchT+p+BMdB3vCi5ve7K8PGNk1zP7YOZ7ved61Tt/1EuMJFZ1xg70lid7rjoVduRiTlrUuWNrecbMaG0ptlE13/pyU3N4YsqirQ52ZlktBU2el5DYGLzcyGRW/z6epCf7mQA8ZPRjOXrOAPmjOztyaev1N1m6S8q1+f09qV2TpQDt3EtPPuJ4ugU7dK/FDK3c7IA8GnLYqe9++ZuVuz+RPHSf7Er9u+WgP4h4nlZrwK46X2u4bqX2Zxkx9Ldy9aUXq4Xx3rC9pNq/U5Sd5C/fXupRxGF/3PH4VrKKxbh3MBjCDF+wPlgmD0wOZnzA4bn/Xkt5J/GeRBr//o8hSv/9cMK/l64btkdTqyQOR1BbOl7oZi2mqylGLSnk70dBcSEiBnnpZibo1VZuTsIu1i58KVl3j9d/7wx0MqTNzn/F7DVr0fsll+uSkOTdXjwk7bURobF+vZbRgVmte4TjRh9fYtjKYcpN1mknaxI7IksOaD+i+VbQWcwf2xPU3QHu3X5jn/b0c2ptMsybJHpDned6ebylomFExlZU//TV7vb6oqedPJWVHmzVSu9p+gvme62ZX2XnP3jazlvxnK7O3ZizLiVj90cmvrZjZ6HP6d5HU5vTvYyl5YKY2W/Wbmn8VX3to/HPmSjH1lJPRADCJtKRrofqwmb8S1d9suM5FC4NeyH1GJnvdvfxjRt5jl/0YSdt3K5u55aUicHEUnLElPzRJV2Ck4lSe4ULHRxgJxSyRrBtShb51MIElXpKPXpYK2TuG81yx6jXtvE/DbsP71LvZ8klpXG55Vw5vspwpgew0GHHtjJn1tXVz5tSqCwrqq6Yl8Ss2nATpfM2p8/i3NJGdY7gwgK8ZPjNTXeHrm9sNHycSvUIjT8ft4wUN1dUZnwZbDJ+2c8agyhpvowAubV6ExPveO7iqoqHR2+80fPoXV0rLv3jRUk4zmAStjWQ4wJxAVSRdgFJfFcncg3vq9fGZO/XZ/ifNCIQ9afaFyMwfXKJGj8xsX2ZXJLVl/PORVMfloG775aSpfdaU6v7HRhpO9C/mVpNN/nSr+e2LZR7ZdOX/Gu07ZcdSPIOsTgSzL1Y3nzOiscGfeRsnnN2JaWozJMmY8G7TXoeSM/UvZjVckZ05S5+FlBWmSGrdu0pLk2WxK4SzhuqQa1N7u/CA/xvdjMseHwrsak/fakIRSq7FLXKzonFug/mVDUVDJLUevQJp4rzzewqy/iPa6+LfYyqLgxPlF3LVZ/tSt4J1Vhx3ew3b4i51dmQiv2WfdOCa3JXSrtuYQC5rvM8VmVwya1aZLxWpCYXNm1mSwkHA7chgdsqE5XArVjMT+WIt51wiPRQvS9ktE3lS0T0/lLiULU/J8M11qmTne2XKPA7n1NDUdOLc860uDNViLiVI1iXVHDFxbao3uTo2sdFUr0Yu60ASo1dFMhunWyIp4XJraSsjk57kPNttA5iIytzez0yuRl4emkBKlveoEslvikvq16pW4heoQi4=
*/