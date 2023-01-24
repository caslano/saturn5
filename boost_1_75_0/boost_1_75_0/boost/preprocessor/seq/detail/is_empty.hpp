# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2015.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
# define BOOST_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
/* An empty seq is one that is just BOOST_PP_SEQ_NIL */
#
# define BOOST_PP_SEQ_DETAIL_IS_EMPTY(seq) \
    BOOST_PP_COMPL \
        ( \
        BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq) \
        ) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_EMPTY_SIZE(size) \
    BOOST_PP_COMPL \
        ( \
        BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
        ) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq) \
    BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq)) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
    BOOST_PP_BOOL(size) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq) \
    BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq (nil))) \
/**/
#
# endif

/* is_empty.hpp
NlJpkIXZHZTxz4VcTjJn9uXt4gvhn/wgIs6M0He5sKMhjh71nYS6mgatnSxIR6l1KMY62BCMMLTJvGkoJCvnGj8YtgtOXop1bLet6zZ1TR7WeOhkvLZvMFdfWCdM3k3Web+Wc12VaZE22fGQ7pd8trxUIwyp5Z7M3d6LkyneI9+2+0iGdo9f27I5xbSyPjXJ5F1r2FFv1esp3EuIybpmQj2UkIGkW7ODYC7tZWKGxt5YNm2y7TAMJg7w6sWPO+G13rlyNW024xKLsW5TAlaQ/Q5fOugqkliyEhyEBosR47YEWZL64TL/JS5FmtZPUi4lrNwtkyoj4SHRbjnd8jo/qoiPuM+PHC/z6sioT+clqbZDTcB2vUdLKYsmlkG5WwzcHRUQFxVS53u+J+JesQb8H0++sIR1fhem+4FCxw50RbkS/Oe0q+NLElyqO0g3Vlm1RdRL75S4CAyMFomY8Hmqkea5gingMea6kJ3Fjm1jByfWU1H7Kyf4F8KenjRAGeePc6O1uOtN3OJ9QRtbCXS9qkywVhre52cOFefmq08h5Q5Hh9eTmHx4VcJlYb4BbYCkg6RqM0uaXRSSsACzok+KlKX0amLythoJi5cmEGh5t6wPMgWOc4SIEo2KdjMO7SVDdpa6b/Z5ixsff/syLxlOHl3VhZ5JtVB9T9CegbmE8cKjVl2OBsuj1m/Ay5WheNfbNpp4yPvZ12uTt/v1
*/