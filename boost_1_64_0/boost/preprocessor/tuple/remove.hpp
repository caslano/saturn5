# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP
# define BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/remove.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/comparison/greater.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_REMOVE */
#
# define BOOST_PP_TUPLE_REMOVE(tuple, i) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_REMOVE_EXEC, \
        BOOST_PP_TUPLE_REMOVE_RETURN \
        ) \
    (tuple, i) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_EXEC(tuple, i) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REMOVE(BOOST_PP_TUPLE_TO_ARRAY(tuple), i)) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_RETURN(tuple, i) tuple
#
# /* BOOST_PP_TUPLE_REMOVE_D */
#
# define BOOST_PP_TUPLE_REMOVE_D(d, tuple, i) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER_D(d, BOOST_PP_TUPLE_SIZE(tuple), 1), \
        BOOST_PP_TUPLE_REMOVE_D_EXEC, \
        BOOST_PP_TUPLE_REMOVE_D_RETURN \
        ) \
    (d, tuple, i) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_D_EXEC(d, tuple, i) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REMOVE_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i)) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_D_RETURN(d, tuple, i) tuple
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP

/* remove.hpp
Q9xga9DngZPjHJWuXQeSpAZb6h7MCkhk4Lyvhse3suteTO1ibJIPvrUIuoXqM6NIZ8p6OfIDT9VGjB4a6s0c58fsX8mRsicHH+gbIA7o9//Rn0+iyscVLY48BE3Vn7kb8+uN7PaELH3trSLmJEPYHA9qOxNEGJ0kIpTnr3NdPnC8yp21RMU7ZTROSCJZQjXcgr1KYwH9CqCY2rYhTsPEcMI8csKKmgAMISI3uTF/kJ0CAGi6pvWQmbFuFHIdRc2ap2n6Gvm0rQNcQdpEhWj53LvpX/0p/0/4I3tss5RsOH4ESdowHDE57CWavKWyrc7mb93cjBNTwpUo7zGkJSm6bzyOl/rU7wwv3WpQhXpETIJk6sLpVSJJeVImV3TX0a5+rUfqY7G82OC5L428qU+r00NgUFc2hPi17z3b9oR8Sl3i/qoSB3bo0jNQiNhoJ+d/PqIOYnh/VGpZqS/9S8Qfe5bUp+o+lpne1mgmBRgqRrwz5HReM/miNnoXKzdoSa1jtjQLJidlQwUJsrmLvK2ZI56nmKRfV6aSEBraxhKojJjtp4ySl4JvMcKCHA==
*/