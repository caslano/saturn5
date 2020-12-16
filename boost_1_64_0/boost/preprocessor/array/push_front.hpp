# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_PUSH_FRONT_HPP
# define BOOST_PREPROCESSOR_ARRAY_PUSH_FRONT_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/array/detail/get_data.hpp>
#
# /* BOOST_PP_ARRAY_PUSH_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_PUSH_FRONT(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# else
#    define BOOST_PP_ARRAY_PUSH_FRONT(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_D(array, elem)
#    define BOOST_PP_ARRAY_PUSH_FRONT_D(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# endif
#
# define BOOST_PP_ARRAY_PUSH_FRONT_I(size, data, elem) (BOOST_PP_INC(size), (elem BOOST_PP_COMMA_IF(size) BOOST_PP_ARRAY_DETAIL_GET_DATA(size,data)))
#
# endif

/* push_front.hpp
Oi5zu6t5RlXGel2Ms0V842bJj0aq5/jk7TLrPVy53Pq3eoavrNt3TcnmVQGyGeKTzYC/e1nOoq3QrO9TFDvL86e4Ci1r1XVohQVlVXXPC4JWJf6/Gxt/u8sKrWVCzTL57tIi63lB1O+qMDMn1rJh5nNnBdLpC8LlqX1OuPG35bltjGd4asqt97SD5rKU6WCWqf27E3+XleTT2lpaF2iVMyoqrXsod4PGsn9/2/saZYrLXdZzjforGobXey4J/B/gvS/KrEu9BzTK+0yCdDnoO4d8gUXux/rWqidmOCzz9jn1qMoOmntsqHfJy71vMvgWUzk9pa4SY06qwljLpvRhUffAtWDHuFetTzv+8rX6g5yh87Xv4C02++gscbm9c8eKZtjrsnxI6m/DPvPWZO3anuvqYulKlr27qp1mDKtekw+gHXWfcsXBdLX4wffmXSBV2d8lymYFrasBY2See6PqerbO+0pp+YWlxIBW/VLvUmaUqPdjPMd8d0f5afWyRXalY3Z5QWVZwHsVYf46vZc9lueFm+8HZZRkmP4uv0wtlLPoVALLKPMLqd3l4b0d4954tf/+cqtPV/wwz8IKYEgA2fSnEVY84nu/Rr1ZasUgIer9JZ8fX2n14+qZ6qAC35salscGXOHJQWOIP1CPYTdv6l57pmeJrc64mlbTfy6C992qVFfFtGK39T0fdd1mvGMVeN3KAzVG5ou8Vnym6Cm13tvE/f5xV9fZeDWghPVdb8X0jBI77+nPNiWpzrvfwOcgz+6k6EZ1dd/HSsFlFBsXpfbdKyXL/iVN1v1dklxlxbUXfDwc4OVZhhkqgVQcsz2ck6iYY5HfgQbvjqPcad76zMb5rvquRZh1BL8W6b3PUVPgMWsOvB7lvTfwur/v0TLRVTE0SpFzjdW2/msj1PiYD7bwfJSie3XR4y8/VsyXsRw15bX6mSj+R/vblCTs4ROottZ3u1T9WJHCaeoVM+v1VOt178t1/jZk1ratSt3qv5ZtuaZus7y7lVpp9MZ8ecvS1zy/bcqakR9XUWTU4Lu+qrtxNrkhYYkut7lnw2wzDu2BSt1ssQM7fPqbYb4+HZcaaH8CL/nelw1uC/ADhK3mzeq3suG3dq97dtmQuu+Umy/l1a5zNLnn1QNFC/XSUl1wxrrvUpgxhl7BzXYViJ8ejm7AGqtOQ7PItirHHk3uAlc1sejsHEZEOQNvPbeZuUL2vCghj6bOWVxtzQ8G72/wNZMNtPFBcwZ/cKzqvlvtqBO/3mFgCNOOKO+leHun2XeLZ1PXxvjWmlr48GMDsMHUOvt/qRIOe4LRalUscK+jNJen0L/hUiB9bNAqvDhqoBePq7M9yAqo8wTupu3BHkFZ81qoGH9bMMDRfKwFA2Tlz6wja+1qcYXvUq39t1wrVm/NWrFKt9rr+LXiClPJLbi7p1/vLbdb7HVv/3XL7dZ3doPgkiS1R9g9lnEdEDg+geIWeKXe2aKZpbM9rkIf48w2BOIWg33QkQvjHI3G9xny+C+Wi6A45g/01bBra5RdU5i9zr4RD6qY0ovdNXnIEtMaZ8zu4WM9i/5hFdP2lLr7sT7SnfKq7APdvWXXqbJLLfPaa9Rvhb+tbfHHz5Hibcvj6v47VbmjzA9l25Vx44d/LfdTqs9GfU8b7VF5ZlW/+ludiRmQe5mlfid1q3vO+LOWWHxOQFs3Bvy9SZ1DHBZet4/Gdev+Fi9Y+B1puR6p+P2S5Zm3qvbzbd67xXLNGFdrHuFVa3vUc3oHnbvwTV14Zy6irLphZryP/x2N7XWwe5DpP0Wy5FKDzx0e573meS9qnHsHqyegb74cqVeWq7xHBrhq88lvmnpt5j/NPr5l2tk=
*/