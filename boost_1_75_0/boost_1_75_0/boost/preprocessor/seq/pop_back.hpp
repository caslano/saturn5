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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_BACK_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_BACK_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_POP_BACK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_BACK(seq) BOOST_PP_SEQ_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
# else
#    define BOOST_PP_SEQ_POP_BACK(seq) BOOST_PP_SEQ_POP_BACK_I(seq)
#    define BOOST_PP_SEQ_POP_BACK_I(seq) BOOST_PP_SEQ_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
# endif
#
# endif

/* pop_back.hpp
KlSZhd/QUg1THLsKUwOVRsDWZGZA+ZF5SklAVM8JvWg41fHpDTbM90yQ01T2MShaDVLc9u31ONehXAPeKCQWYwgyffxgcPSQtXuJLgdv81Eadchb5pptEuYgZ0GkF+7ixqK3nXp9S4tlMBOO9dMczWJy635MjhVA/06ObNw9iWJo2u08+3ha0eqypzsfy8Lmrs81EJfipnS88TiDNW8ClIkmLjugWCZbpriO6RiRMMto+ERZLF34AmoM8CdxPhJtpnQ/Nw1tiNUm79l7s5w/wpsZg7YrXjQ1NkpxEtiw3J6B5rqBwCj6KchveirXEXIjv4t8QjT0AtohT2rTu7nwmDQKmvvOd5fYA+6CNUTWBpfIn7vHGoonoADlu3vcz6MUy7zV1vrzeFexeV3PCNMBCGBD6WT95TCw9/AwBmLr5xkM8detePW7yeQSRsmJbOlz5we+Rd6ETWCreL2bAnJDQHZFZ1CVi/veWS8fdQjCKfPXvex73xjSERD/jtHSB7XTCajJS2jZ+2mvR54oYfJxZFSLraij0g7FewQiEhSXIfYHArv4zncY2JiqY52JQLBb/vmcsUqZhUwt5YBm3Kb1VJErK08hpf74fPZUJ7xVG9lEzvd5ARmwemxzgAT+LUbo/pAYdP1fy+6s/zZG4Pp72d3d1c3RXtLK3MyW6x9RgpGTwaj7JgoCOVbIqJ9Ktdpbav6jmT2y/YU0a7PU
*/