# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_TO_LIST_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_LIST_HPP
#
# include <boost/preprocessor/punctuation/comma.hpp>
# include <boost/preprocessor/punctuation/paren.hpp>
# include <boost/preprocessor/seq/detail/binary_transform.hpp>
#
# /* BOOST_PP_SEQ_TO_LIST */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
# include <boost/preprocessor/seq/size.hpp>
# include <boost/preprocessor/seq/detail/to_list_msvc.hpp>
# define BOOST_PP_SEQ_TO_LIST(seq) \
    BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC \
        ( \
        BOOST_PP_SEQ_TO_LIST_I(BOOST_PP_SEQ_BINARY_TRANSFORM(seq)), \
        BOOST_PP_SEQ_SIZE(seq) \
        ) \
/**/
# else
# define BOOST_PP_SEQ_TO_LIST(seq) BOOST_PP_SEQ_TO_LIST_I(BOOST_PP_SEQ_BINARY_TRANSFORM(seq))
# endif
# define BOOST_PP_SEQ_TO_LIST_I(bseq) BOOST_PP_SEQ_TO_LIST_A bseq BOOST_PP_NIL BOOST_PP_SEQ_TO_LIST_B bseq
# define BOOST_PP_SEQ_TO_LIST_A(m, e) m(BOOST_PP_LPAREN() e BOOST_PP_COMMA() BOOST_PP_SEQ_TO_LIST_A_ID)
# define BOOST_PP_SEQ_TO_LIST_A_ID() BOOST_PP_SEQ_TO_LIST_A
# define BOOST_PP_SEQ_TO_LIST_B(m, e) m(BOOST_PP_RPAREN() BOOST_PP_SEQ_TO_LIST_B_ID)
# define BOOST_PP_SEQ_TO_LIST_B_ID() BOOST_PP_SEQ_TO_LIST_B
#
# endif

/* to_list.hpp
abxbhenF/dJjUsKcx2zZvVO1gjfYysjTGRpKmBl+D2fFDDS0iCW6mUMjz3qMV3g/6opjaYR9eUlzy3X1V0peXqaj9RfoFiXLrzhi7EZfrp5Y6VXqZrO3UxAqQVCWN1y7Ne188DfKUcqplx/gtH8B7BdKaRo+myi7ovYTGC3aF9tEcMaxFGn/pArTTkZ62v2A3k2eed+Z2yk+8ljNmzQgzZDTAeeVf9zRKcAj9tWWRNo5Pp6h3HAAog4KSURJdGMnZVxrVo+qDyXEKP56taklmw9m5azQ4y+zWBRi1XF9zKY6BG51UE56c9xYNGjV9uVlaFgmAKpomVJNjnPOcwgqrGoFDjs2sm4ND9hrmct1Mkr4dU9qO/Ckc+xqf6sT5s1SDi7ZXTD6xmM3rKfeaIo30HdSRbS6rPVX5CTh4IZgLMrxybXIucth6luxGTwQSl3vyGDdiAvYBQ06AezCRZ04H76+ih1k/vgy7hNW9Uinu64rSioQc8hQasW9nnhp8LMThV2Y/VaIiiSn1JYYaaDk5YuPrwY/4CT1cQd/eiOJzMStNEANJnxn1VAfwxdMK61OcvOJ1PmF82uuP9EYc0LOta1Cu8RDlVew6YYChtT+imxxQzKBj39DNiYz8/wL2y2fdnyHIJEtjksJ9LNg2ptBsYh+fEEM8uj+lwuSBLyDaO1k/P05M2gi29SvPhHeDYiTfidwwlSWpPQxRBgL
*/