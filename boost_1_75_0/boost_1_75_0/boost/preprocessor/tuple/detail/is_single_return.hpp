# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
# define BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_TUPLE_IS_SINGLE_RETURN */
#
# if BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# define BOOST_PP_TUPLE_IS_SINGLE_RETURN(sr,nsr,tuple)  \
    BOOST_PP_IIF(BOOST_PP_IS_1(BOOST_PP_TUPLE_SIZE(tuple)),sr,nsr) \
    /**/
# endif /* BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC */
#
# endif /* BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP */

/* is_single_return.hpp
15cCz74ciK3olgpO610NLlvtxFvhYmPR6PLvFGEFt8TBAZRQPff9KpR1nM4Z/1ag/0yEDb4RiE8KIAJ5Utuy5DdMc12Ht3QE/FWP2x6997R9AWfq4g3SDHJE2JS/ltcK8eIeboHgn32oQqz64PjXJoo/YjN+e8LjCu0KWie6n6AXajOGHubGn2c0Cof3joi8gU3BngGeQZndbWodeoCCax3UZOeDzAXibj96jADoX5CPfp/WSldIJP3evx60AyqbnKTJeWJP6PIlLdtFsLh7ishiMMlIidm/X1mZ8OHznAFGSZzHvMor4kTErrQgwzhS5Y/hxvymnp136ctQNAk0V6cha1eSUaFfTmgvJc4rx1/d6IwJO8Iq/Hs5TIO/cRbpmgr7cAVuhEntsFMd3DZqB0cYU4vTsL2IQtLQMlOnD/sqajZ4CU2l3Cz/ZuTTEGJUP1d37Aij+GoiLjXXVlysW7lzr3qkImT2Iv23DFg/Lk3ARkC5137RWKdxt/NnzDthrDsDMZ/yyXh9jxMqKqsTftHlC23jh8+p6O4YJzXdPwFWJFz2dJ9FWDoA6nKd5H+XeX3Fb3IJK14liY7w7y0Sxp4f7DvqvnSwZLZxOwIiTx7xQHfzCZrEHabczjg93T0ePE7Z25qIkTFu73keeH7bC3pjx5JymCymugt+Mmlr7Uce6/5Z6GrJyIJNZz/ohi1UzARYwWoKdd/GscJe
*/