# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SELECTION_MIN_HPP
# define BOOST_PREPROCESSOR_SELECTION_MIN_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MIN */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MIN(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
# else
#    define BOOST_PP_MIN(x, y) BOOST_PP_MIN_I(x, y)
#    define BOOST_PP_MIN_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
# endif
#
# /* BOOST_PP_MIN_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
# else
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_MIN_D_I(d, x, y)
#    define BOOST_PP_MIN_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
# endif
#
# endif

/* min.hpp
S99nDTzunhwx7dvhN9MHarfE7SO+iQvGe2DuH2hGec3XfcI1mSC59y18AvD4pDYalzRt5CU/PtX/iA3P7ydc5sXu0EVpcU2sYY8Pv0kgB6HjodDkcGF/x6SGr356QvitsQ2/t1bBDPmux30oMCokmTz7kxhyY5q9u5p7XJ+hbmvdOs0dGeymlccRqhb8/pq8F0/c2MkeX4+b/QWPViuxe6wde4nm8o2tlUlh5svx4qKmUNXE/k2m6kpJTWacCfkQd9kKOf8oQg21C6yXM+2MKXCWAhNnueuV9Bt0REVVu5j4FzX60eKqowUen8k/zVrl6Kq+5FcxeK+HX9Jt+SbM9dv4/rapYs/GGR1X/LXgszh/W5szww/0dBNJHx3zpBIUYNjKjhXpjSPNnoeLuSzPDcARge9wi8zhTx5zQXJClhFJ8BcDdQ5H2qmyKasy1ZOs551xcUyeWkn3G5QLcdISxtqkJNi1/oBFrOqykYlBzHS+L7d0iHancmqxXSY7+SIfBXB38Vt8BPWSom6HWepiCzXfxLEFaCQ5xMpzu7/w8U6pf8qwITzF76QdpwyDLrICzBNvL0ETouWjZALiZAnsivvprXqA7WspMA4jUxsXx4Xbr7TcC5GjLXsJzanJ/pMGxjk2p98Zm1mq1V2iMT/L8/M0j7FhurKdhAxcDI0kL++xzXzuI/hMFLa31TuiVRIwfonNYgUG84467K47F51oE4dgXhW6XlWd1legyQCpPcH9bIfr69oGMZZRL/LrV679gTcmCpdcUnF4vNL0d68jLJbbfoyYSeicBqnqNA2WBFCksEnPTK6ucZe2lX//XMuqylTBeaiJGgyj7FjPyL44XOjz9K0tkR5nfip6MebM+7OYlfovU3/4cGcQyGCn47eEZFckfkeJWTasNbJlfzuW7Z6mUAwZY4fF9NF6r6pfoWjLNsZ7UaDf4CO145f26jm3w/olRk3CbMnnGBqahbylQVmVg6RhpguWHuFXHfD2ki/UI7edFHAU37wnNaDcKbBl5aDuUnjCrMDQZqR3GuH6nAimMuosWbm23MgOau0Ki2XXgA7SHh/bijEEZUf+cMVa0+2btKmQcnXtE8k8ahf1W17xKvGbOqynUhNZKI4bvkkQXwcZpnxjxvYS30m8psyF+NaCZoOQSIfkAiXnRP7xIAeXoqkoeUJ05EeLqLh76jeBS654QgeViB/1oXlG+Nqv9KtE477N+EB2ltPaGUGKyEd0DvU/FPKmSd4lqhb5TaBC1JjswQn7GvIxTNyQghQSlInTz7oY5LuI+AxZrme5unEu3X8gT/A+rDtRKeMP/eCv/uImcoVdyU0NNm33ZrReJ4Hi2m7C92DYAO3Lm1d2rQPRYk7pdWHhRyuvZWMgR6bA8xOts+QsXY/Sws0bV1PDN6g/ZBe07S80WAk814jztn4jhJ9/pwXnuiqnULV10s2yH6rb/5ooNEb/VRa6EeK2JXkjr7YOUl5wZ/6StDd4tXERcxN37HkuR6sVYiD3BiFUEhoTsZCeXvd+fwfOrF+LyWLWzdXHrtodRWGEjiZLHlmPKMUlyO88jQFvMw8s0U+rUksdzTubV6Ua5TED831PS4mv5eXEISezmeUv9CRiNSemnktN3nBC71bVtHExf/7u+vnt0+bDTF1c26ARNQ1oBp8VBCMdvlDzLrTg6pGJyO0Z4oxm861+Ntcwoz7NFthsKyzE4y3BgHS3OiKKJ8HukXMatNx9KLbRQXsugY3Q5NOi0SomxbJrp1ZSY5+fjbgFjU5azxuKVwfOVbBWWfY3dz+leenuMvtRO7wloEVBGBYzypwXA9LIpsyLikjn+rTlnW4ZDB6UqeyX4omeJoU=
*/