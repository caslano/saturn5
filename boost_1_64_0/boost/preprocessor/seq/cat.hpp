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
# ifndef BOOST_PREPROCESSOR_SEQ_CAT_HPP
# define BOOST_PREPROCESSOR_SEQ_CAT_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/seq/size.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_SEQ_CAT */
#
# define BOOST_PP_SEQ_CAT(seq) \
    BOOST_PP_IF( \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), \
        BOOST_PP_SEQ_CAT_I, \
        BOOST_PP_SEQ_HEAD \
    )(seq) \
    /**/
# define BOOST_PP_SEQ_CAT_I(seq) BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_CAT_O, BOOST_PP_SEQ_HEAD(seq), BOOST_PP_SEQ_TAIL(seq))
#
# define BOOST_PP_SEQ_CAT_O(s, st, elem) BOOST_PP_SEQ_CAT_O_I(st, elem)
# define BOOST_PP_SEQ_CAT_O_I(a, b) a ## b
#
# /* BOOST_PP_SEQ_CAT_S */
#
# define BOOST_PP_SEQ_CAT_S(s, seq) \
    BOOST_PP_IF( \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), \
        BOOST_PP_SEQ_CAT_S_I_A, \
        BOOST_PP_SEQ_CAT_S_I_B \
    )(s, seq) \
    /**/
# define BOOST_PP_SEQ_CAT_S_I_A(s, seq) BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_CAT_O, BOOST_PP_SEQ_HEAD(seq), BOOST_PP_SEQ_TAIL(seq))
# define BOOST_PP_SEQ_CAT_S_I_B(s, seq) BOOST_PP_SEQ_HEAD(seq)
#
# endif

/* cat.hpp
THxp99yXZwSvlVQls7VTtH4GpY7On+QJBNrn1D8U8obNy6+77eaZObqR9KFmbQpFN3tHlNzjlTFwaUjhtkwFm7M5s7ArFRxzn44EozUXz1U9rbacQzmdxQzjGgiJmqMcsN6NkH2O2Eu1zQwIphoxUL3ewfFrkueZQygeIEspC8a8oGAZTQx89xmH1/BOTgtSy7qYjiNHaXh6l6bX1M7Q/+agO7DZf//5benUWMOHbMdNz6qZij0Cz8SJZGvXWJ0dRn3vkrwmL+b03JZreEuGomzsLhdJqiAd9vqAAjUSjMhwCK/QixmWxgTCT872QZDxK/BwIQ6Ds5SRL/e1E6jqNgcdDlhqs9ZxYQ5UbskRcMIvlkqp0V+FxhEqStTl969f9mSoxcR9sF6NoUA9GvxCWX4SkZhnmgiNSbodeLHMVy/DGaRYB/OMa9qBGhWhsM1CsIIJ5xh3ZhmHnSf6uV6LntUQkUeL8lTl8rOuRWFMd5j+frsaVSYPfZlbtqUhFLmEmMWzo6tET+NJ7E7eOnlDcudVfPMv88LaoVcyDpQRWG18WckdXgRZ+hO4NAd4wLThuetuNpjT/PO5ywlBh10CsSe2hI12pzZ2kDbUAd5m0Uy1EAdoLsapCujuOtrPCquuxEykLUyN0rAduDao1WE935Ey0jpuJAtEIfabEWttGQ5dAoW8KMh2dEIX/SlmbPobjsfZDEd62XPwYVom3hblqCdfckjmppjRY/DppF4ZrtYcbmHQZRpjWDpHGLLt2KnZ2z2R1tDonqelOX197Ul4XMYGfgOu6epll2oF2ydh2vnkljon2ahfYoWNGxqWC1oypTW8WcFWb2sNKUmkO7bv0B6GVc2RspbCNXxdNDODHeMHHJGkC5KPa5xLs6/XdpEAe8f86+1IOnvoboQK5UPKOZJTCMF3jVRI+lz0tPLrHxLcppaKyTkKC0JqggnP1bCOkRX73U7bLNsOlm8MSXILCqbs6ccQuCdbapeUVymfnfuboAgRhA5ifJKyto8iX4kxf6fYkbnBfv5hjsDq4zQ78dyV6Njoz1LXzF0Bl9tAP7G8nWNXzMJMHwhffDEESWfYKfm7YtNxuqBbhiK9pIBErzIbWbN6rbZiz09dJcukOx0YuHABEWRxTWWvGduEgl5MKn2Mt1uOXqKf9EtnW4GZXIsyxF+iKVk+QtB1DiHEZHv+xekP4zrR3koQz76vb5uYF970q72qgwzYvPrDfO+FleZ8L7xacLpklkcY9h0hclA7ATmb7i6iKb/NbrT0/s6BU5uLBQx8YdGZXP+Vh2zgbH7yyNvYQHhiVrE0xl5wYlk+qB2Uinn4ErqHBzkdAtN1qCDYNQO6Qdy67HxllHPfnmds8RMqAXX+eVvOjsYFMn2NEWQoBepGQibGLdW+AW16HoW5ZVGYO31IacjP3jFEF8KgXm3X0NnNsDnOdJi3Rhjbki4LPoxBDmmuOyVrgWxXH2J6DpmSX2v9EIM/Dl3rahn4sDHTJU8ztuc4wMkqtQ9G+DZJKIf+G2xR4mf6jesChfpSRqUbTpn1eGf+ipcTxAoKW/MZQ+3EFSOqJJfNlWa4VdN9NPidnJu0IyuOvLNDDt1VFk1+9BLDYhRqEx1DE/ac5vlXJfotRq2aQfDeCIhbHFHl+6pKIqVTe01pB4gZbs1C354vSk+ijTEPHLhNQs/De4Qays2ERPV71piXDFTgWpzDIbtNKyLADpXa8ZvKiqtJDSzhwmLMq+zvyzGIusN7cT2dlbAuZyrKQNIs5RxJftZKvH37Feob8YYAjtHu6ebCH9k7y6A4ujQK4+7BXYJ9EBjc3QnuBAvuECQ4BIfg7kGCBHe3QLDg7hqCu7s=
*/