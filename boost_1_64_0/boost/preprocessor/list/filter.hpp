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
# ifndef BOOST_PREPROCESSOR_LIST_FILTER_HPP
# define BOOST_PREPROCESSOR_LIST_FILTER_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/list/fold_right.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FILTER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FILTER(pred, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_FILTER_O, (pred, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_FILTER(pred, data, list) BOOST_PP_LIST_FILTER_I(pred, data, list)
#    define BOOST_PP_LIST_FILTER_I(pred, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_FILTER_O, (pred, data, BOOST_PP_NIL), list))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FILTER_O(d, pdr, elem) BOOST_PP_LIST_FILTER_O_D(d, BOOST_PP_TUPLE_ELEM(3, 0, pdr), BOOST_PP_TUPLE_ELEM(3, 1, pdr), BOOST_PP_TUPLE_ELEM(3, 2, pdr), elem)
# else
#    define BOOST_PP_LIST_FILTER_O(d, pdr, elem) BOOST_PP_LIST_FILTER_O_I(d, BOOST_PP_TUPLE_REM_3 pdr, elem)
#    define BOOST_PP_LIST_FILTER_O_I(d, im, elem) BOOST_PP_LIST_FILTER_O_D(d, im, elem)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_LIST_FILTER_O_D(d, pred, data, res, elem) (pred, data, BOOST_PP_IF(pred(d, data, elem), (elem, res), res))
# else
#    define BOOST_PP_LIST_FILTER_O_D(d, pred, data, res, elem) (pred, data, BOOST_PP_IF(pred##(d, data, elem), (elem, res), res))
# endif
#
# /* BOOST_PP_LIST_FILTER_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FILTER_D(d, pred, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_FILTER_O, (pred, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_FILTER_D(d, pred, data, list) BOOST_PP_LIST_FILTER_D_I(d, pred, data, list)
#    define BOOST_PP_LIST_FILTER_D_I(d, pred, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_FILTER_O, (pred, data, BOOST_PP_NIL), list))
# endif
#
# endif

/* filter.hpp
QI+4uU2nx4TLGqTHln5Ej6jlOj16HfSjx8f9LgA9tl2q0eOiz4LTY1kAPSa/3hR6LAygx6n2jabHmHrocfK1AHqUvd50evx6SYP0uLEvTwc+0+lRfsCPHpf0vQD0SL9Eo8eTi4PTY0wAPY682hR6xN3hTw9T478PZz30eOjVAHqYXms6PbLjGqTHx9cRPcYY8+2on/3o8ex1F4Aei7pq9Dj2aXB6OAPoMXJOU+hhC6CHpfH0yKtv/fOfwPXPnKbTY3WXBulxybVEj7hPjfXPfv/1z7UXgB7xXfT1zyfB6ZEXuP55pSn0KAigR0Tj6ZFfDz1ufiWAHvteaTo9ruvcID2eTeb57ic6PWr2+tFjbPIFoMesWI0eWxcGp0d+AD2uf7kp9FgYQI/4xtNjdj30WDo7gB62l5tOj/kXN0gPcxLRY9RCnR6j9vjRY3/vC0APy8UaPQZ+FJweswPo8eFLTaGHKdOfHgmNp8eceuhxxUsB9Kh8qen06NCpQXqMvYbosdCgx+ZdfvTIvOYC0MPZUaPHJx8Ep8ecAHp0ebEp9OgVQI/ExtOjvB56vPxCAD16vdh0ekyLaZAe+3vy/tnHOj3SdvrRo6rnBaDHgQ4aPS5dEJwe5QH0eGZWU+gxKoAeQxtPj8p66NF8VgA9ymc1nR5/tm+QHplXEz1sBj0W/uBHj2uuvgD0GNZeo8dz7wWnR2UAPc481xR67AtYf9gaT4+v6qHH488F0CPq+abT48F2DdKjKpHllUGPuB1+9JibeAHo8VW0Ro+Qd4PT46sAejzybFPoEWX3p8ewxtNjTT308JQF0KPg2abTY3vbBulxTQ9enxvzq7Lv/ejRpscFoEdyW40ej80PTo81AfTYM7Mp+4lpAfQYLunRPEQzvDV5QOlyXPhG9wz7PgeeHyTPd8WftH8YqRTsTcczq+HiCILY8lc3kL1m1zYmqlS7bWi/eEN98m9moPyb2XT6/tmmQfpmXsHrS4O+C7f5y78rLgB9h7XR5d9bwem7IVD+lTaFvmPs59z+T/Dd/k99I+j2fy/JFicoASqFpvHxdX3mAUClDJTX7F+XsjKCVD/iP0l8KtELeiBLzUFJP68e0rcuDSD9W6VNJ/0pa4Okd1x+Gia5Am9GdKags9/Uv+UVW/dtEaXQ6Ao1qXYU/G/ZZmaKEeWs9ztIv2KrXz840Z2VZP4/1ulo1Vgn+83grDMvgHWq3U1hnTJtKpMqRUNyB/0okB9RqHOCCd4JYILhbo0JkutlgmXBmeCd+r5/d+D37/ZjAlZhLr6/NTSGs7MN+meXMHkDv/9W0EqihKA8cGe3RvNAuiUoDwx/LRgPHIu/ADzQrpXGA/a5wXngnQAe+LKkKTxQCR4gYjMf9JV8kCL54DdfWbAggA0yS1Q2kLnxZwwEVGEvItvHBi/0pV4YrLCgHlY4M52IrDPCSyUBjCBJ7s8Ggee/LRtigMzLGs0AI8KCMkD2nGAMcPTSC8AA0S01Brjz9eAMsCCAAVZMawoD1GhC4CbVYhMYIFIywBFfBigIYADbNI0BIgMZwHRu2hfUQ/uQaX60/8+086f9X80bon3WJY2m/TBzUNovfiUY7f+IuwC0j2mu0d7xanDaFwTQfmVxU2i/D3tvRHJJf/nxR+mDgEH7ogDaDyvWaB8VSPsCBLShYEnwoaCovu+/KFD/rbjp84FD4Q3OB4Z0Dc4O16ns0JPYAYq0wXhhtj8vrNV5wdPlAvBCZLjGC7f8JzgvFAXwwpLCpvBClE2VAzdIPoiubzIwPYARbi3UGCH6fCcD0+vhgFNPBnDA84X1TAYczRo1GfhvWEPyYHDnRsuDxJCg8uD5F4PJg19iLwAPRIQ=
*/