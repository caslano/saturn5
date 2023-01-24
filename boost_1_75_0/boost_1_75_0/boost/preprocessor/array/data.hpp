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
# ifndef BOOST_PREPROCESSOR_ARRAY_DATA_HPP
# define BOOST_PREPROCESSOR_ARRAY_DATA_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_DATA */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_DATA(array) BOOST_PP_TUPLE_ELEM(2, 1, array)
# else
#    define BOOST_PP_ARRAY_DATA(array) BOOST_PP_ARRAY_DATA_I(array)
#    define BOOST_PP_ARRAY_DATA_I(array) BOOST_PP_ARRAY_DATA_II array
#    define BOOST_PP_ARRAY_DATA_II(size, data) data
# endif
#
# endif

/* data.hpp
U3ZWV9dR1HF3dlRmb52qulV1H53OA3Ucbz5jc7tu1alTp87jP6du6l5/u6hs4pc//cmb++5cdf26g787+PKht3dcDO2cs+/QzG+8DzUNLx4S/bBj44yr1n/4zIH6OcfviR0+/avsuOBnKQ+ce+Sj/44/1H/tjfE9y+K/zK/6+dKbJhfeuOc/D34598hbz22pDE372pF3+Q1Hexx48pUFn5btypqx4OOHuuU//NCbf3lk3JqxV1a5L14x7Wxwcbp/x1nHN5+Pbswp/OWjw/cX9FgQf3brywv2vr/zhH/V5G3PP/KX6PW/n+t8YNYLDeMaH5+bMODrD7Zu+cNX9RNslXOemHUx+vTui/vv//Po7NXuqv8b8/6Z+c2/Gv3c0D+mTnrpsO3MzJiM5pJ5+z6+p+9/TK14fmF1Q1Lzr59/c1R5/MVND687ey796U+yN99zbtfrab899WT0h5uPnt7Tp+8rww4WpCWfWR1XUHHv4QkfDHeftG0ZNfyF48fTP9l1+vLF17383P2bXlhkv7H39mnnppxMTzg08Mm0j06dikm8781n/ufzw6Hrb/5i/PmRub/aOjjmvWmtm7x3zPmkNfrX+/vc+cvZ53vfvujYmpvHb0r8a8uB0D2v7TqVctnJCaM+Gt/9ywMbEnN2PHnDgKSVrqpQaMUVDz445Lfbejmz+70Ta0/P33ag/2u2p25Ne/G1KefS007u2t3j
*/