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
# ifndef BOOST_PREPROCESSOR_SLOT_SLOT_HPP
# define BOOST_PREPROCESSOR_SLOT_SLOT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/slot/detail/def.hpp>
#
# /* BOOST_PP_ASSIGN_SLOT */
#
# define BOOST_PP_ASSIGN_SLOT(i) BOOST_PP_CAT(BOOST_PP_ASSIGN_SLOT_, i)
#
# define BOOST_PP_ASSIGN_SLOT_1 <boost/preprocessor/slot/detail/slot1.hpp>
# define BOOST_PP_ASSIGN_SLOT_2 <boost/preprocessor/slot/detail/slot2.hpp>
# define BOOST_PP_ASSIGN_SLOT_3 <boost/preprocessor/slot/detail/slot3.hpp>
# define BOOST_PP_ASSIGN_SLOT_4 <boost/preprocessor/slot/detail/slot4.hpp>
# define BOOST_PP_ASSIGN_SLOT_5 <boost/preprocessor/slot/detail/slot5.hpp>
#
# /* BOOST_PP_SLOT */
#
# define BOOST_PP_SLOT(i) BOOST_PP_CAT(BOOST_PP_SLOT_, i)()
#
# endif

/* slot.hpp
Bpt6KpvzVflcv4cjtbvn8yalf3r2hgZFB254/7z097Mqm4NW+VyzHySefmErPn3+mtqPtWybduexxmlfVT7nzn2u4unPeaxsjmGzKO1e1iyzedfYyN19Zu/OeqDgT284fifX1MdZsDWSuUEq8AwizybiVw31MvYxepgjbAjrwMawKYyD3WATOACeCXV88Z7APbo8S0h8LVA7HPR2vgmfBDvCIfACOBT2N+6DYSpMg2lwrNnPgelwIsyABfA6eCW8CF4DR8JFMBMuhxfDCjgK3g8vgavhGLgGjoWvwWy4A06Gu+AUeBQWw34eyg4OhXp/uNmfBOfAmfBSeCm8HF4Br4BL4ZVwLbwaboXXwD1wAfwaLoQ8a8l5BObaRZh2lmX2nXPtzsZOszWsB9ua/GwPO8PzYDyMhz1gF5gAu+v0G/dk455p3Mdqd3P8XR5zrTf3FrPET8aYy3Y9do3gUlN+t8ORcDnMgneZ8rlX5wO8Dy42c4DugQ+YfF8Fn4IP6XyBT5r8x03y/WlYg2P+BKPhGzAGvgWbwrdhG/gOPA/ugmPgJ7AI7oGz4F44B34Kb4dfwDvhX+AD8Fv4ODwE18Pv4AtQp2MHlLky8De4H/4VHod6TgwXMuWFPuiDjWF1eCasBTvCcNgDRsLeMAqOhDGwCMbCafBh4i2DOn/KYWPcr4Fx8FbYBK6AZ8Fn4HnwNdgM7oRnw32wJfwFtoa/wXNg9VDqCQwj3Yklvz8WrwIVY/Mg2oR2oWj8D0FVKmPLZJxY2XB7vJdXN8ZQGYclY61aZ8pYKRkPteQS6BjDdBjFEU871AtVhHIsGW/kH0801zFeaHSpfwzQulz/GJ4C9sPMGJu5/L0cmfEz0nDXlXKMUP/Yl8MF/nEt48zYlO347UOqjOOXqaqtaqvaqraqrWqr2qq2qq1qq9qqtqrtH9z+rd//Z+SVlOYXFcrHf6X+qe//Uap6JHMK9VN8alpGVsLw4cp2U+KUOkjZbh5xS0xITtPvwsLEDZek1JSsAYmpSQMSzLd+5rlavze5z6tk08/xdQx/wqfDAPnuZc5GfnIy+JuX27ctCefy25Gu38dtW/u36Mry7Pf+SeI/MSTM41Vnoq4h1Rzv9IuKy0hZqVLWN5qLxX5kSNBvMVq/cV8k/v30e3uTh0XWu+wy8btb1VaXqZbme+v8gdrtiKpFDC3QAN7EPQa3oS+QnRaTTcr+3ccREt8lIT9T8hGe6qplSA3neeaXlM0W2wbsDRXbvBCvp5pqjDqGhDniziuciLm85zbfdHLEfliIbZOjl/QrDdgcwCZdbMY4bIoLsmVhPn8aY3C5RGxGhPyofLz74btTSPUT06iU9c0jS2wvDLmGbwVNlVnL2ag5GdgCnY3MGslmP4hGLQ1bGbY2bGN4jmVbaTzyHSH6d38DOVxDzU+w16ndPcBaV7arMm5v225dAm7bbLfOAbf1tlungNtq261jwO0u262DlAdut1puPWR/sbUfL/sjBgb2u8t+R2u/m+zPSTj9dSj/H9YpfDpau18eGbrcV/uh1nXfSel/qPv30VXrFFatUxi8TqHdP7TiD/0tZJ5ZL3Cdx1yHzLVvF+yCVmsH/bf5lnS++fbTy3zr6Q3HwMEwFybCCeYb0RTzjWgqHAbnwBQ413wjuhZeCK8z34iWmW9Ed5hvQ/eYb0P3mW9CD8NR5lvQaLjVpONdOA5+AHPgxzAXfgbz4HE4AXo4l74w1ny7OQsugmfDAbCTcY837r3gRJgBp8BMWACnwqlwGiyE18AiuBgWw9vgNLgKzoDPwNnwVTgXvme+NX2p8x8ehlfBX+F8GBHi//bUAF4D28E/wM5wAUyEOp0pkHTKelo=
*/