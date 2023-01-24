# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP
# define BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP

# include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/preprocessor/punctuation/detail/is_begin_parens.hpp>

#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BOOST_PP_IS_BEGIN_PARENS(param) \
    BOOST_PP_DETAIL_IBP_SPLIT \
      ( \
      0, \
      BOOST_PP_DETAIL_IBP_CAT \
        ( \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_, \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_C param \
        ) \
      ) \
/**/

#else

#define BOOST_PP_IS_BEGIN_PARENS(...) \
    BOOST_PP_DETAIL_IBP_SPLIT \
      ( \
      0, \
      BOOST_PP_DETAIL_IBP_CAT \
        ( \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_, \
        BOOST_PP_DETAIL_IBP_IS_VARIADIC_C __VA_ARGS__ \
        ) \
      ) \
/**/

#endif /* BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_PREPROCESSOR_IS_BEGIN_PARENS_HPP */

/* is_begin_parens.hpp
6OyblxUaDiiavW8tsA25raLVQwSK4KgFFb44RTgf534dEW3pQr/JPX8xBGaDBU4XKKnaliBtAOuvbU8924igz7h3KCIhNAmQpdVBQBdk6WQ77AwRnk/1BmfD/d5R1akcUuL7+Pi5puBrX5P4+9kQ4dvBAv4NSkz0m3NhpB6fvt2TJm+/876vZWsUw4fIIf6gcyz3NrTHAeSPbwrdbtM33Wa2MQ5FaQKMy588gNZdwvO4+FKIYK3o1ZrNzrX+6RJf9AVf3clvXT5CuKZfkkZfOYSjpTon3WzKmPYWNF5WRYKMP97uTOO2D27eVG2cncz8SVxbDwk5zOIPnBWtkanXwEWhmdRsq+M8PZ9r8wmmyYbXNz8KpvlBdr5OiYHEEz+JUuaJgUg9I7qWdtvCPtOAp7Yx3vpsfDalNQmJn07UcgLcH3YXDgI4QV8CJOZXRQq2lsdI3uZ1nkTda8QC0UWA24HZegoNb6C44SIFf9WtbIvP7+Nit4cNkK5tv+1Iwxhi80DzLSEKsaM44V/OdXir55lrAQR69jRtbm5oQxaXz+r12E4oKNgmb1ViLBxw0G34mEVAfDqrx0czQMkCKRK/KoF1gh3yU4czyouHHJO6bEXXkJ/qc84hJaWlBb29NlYfqgWWBFo6eiR7OkrpTp9Cz09s06eiNrK40Q4+817RkHue2u+iBJsBKpsz2vS8ulCzVtfFQFSBG2jrISxT
*/