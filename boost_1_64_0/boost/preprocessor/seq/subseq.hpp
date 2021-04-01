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
# ifndef BOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_SUBSEQ */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_SUBSEQ(seq, i, len) BOOST_PP_SEQ_FIRST_N(len, BOOST_PP_SEQ_REST_N(i, seq))
# else
#    define BOOST_PP_SEQ_SUBSEQ(seq, i, len) BOOST_PP_SEQ_SUBSEQ_I(seq, i, len)
#    define BOOST_PP_SEQ_SUBSEQ_I(seq, i, len) BOOST_PP_SEQ_FIRST_N(len, BOOST_PP_SEQ_REST_N(i, seq))
# endif
#
# endif

/* subseq.hpp
dh341u1/76lxwaq7Ag85yFV3EuC5l3nb3FIef1xT9nor10biZ3GMy00OGgdBttWBHGyi2dlQHegPa3CE/gVnht/B22Y0Zv9fnct8tkqO11UgoJ3PuLmt9sj9PKDkeQ+VKhTgdCv67SIJwS1JYkWVpTDStLjMKQ4BmxKWjamVxWMJ3WTKiNyaqCILEn2Oq7lkmmVb1dvXo6F8hXqEWxGZMv/jymPc6VhRK0fK0In7+yZHkOx+/IIAUb0ORgapkn4/HIcCxgwIlGxdabHHBd9XBRoWZXYBClnIqQ8/PEvt0okF1qbE0qHVmEeZYqvgQMiH+S8lF4w9VeQEbMr4amu+gAYSUQbreoUA6n4vyVAEN1xDc0G2XTSnIQ6Ik5LtcAHUSUijWtR+R1MLxBaik0MwVqKI3uJo9nnKL5UUfb/ZZojHIZ1RxhqDXEzVgOrfL3uHSbSCXxebgZ3bJQc6QVxEfJ+h84Pm1B3IL6UesDzvpZw+bLymWvFIEWK689OHIvbincxCzRsp60+ZtC+n77dmRenOZAzj9/KgH51NyWp6vt2ugMs3TFf3Y7l37w==
*/