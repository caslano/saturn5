# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
# define BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_TUPLE_IS_SINGLE_RETURN */
#
# if BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# define BOOST_PP_TUPLE_IS_SINGLE_RETURN(sr,nsr,tuple)  \
    BOOST_PP_IIF(BOOST_PP_IS_1(BOOST_PP_TUPLE_SIZE(tuple)),sr,nsr) \
    /**/
# endif /* BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC */
#
# endif /* BOOST_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP */

/* is_single_return.hpp
W4ya0SnmtoVUVCLHMOYGY7cRzslqAwwGK/GtkWjceICxEKjGOBecsHhbsVJmTJF2iymqcrlpzDFcYi+y9fVTdBAu+z0lU3yQTis+LvR7sspUg7C/7XRv1nG937NNXWuDcUZI7XSmlX0xmAXTBN4Eizm8SSL6Yni7jN7NV/AuwQXqMBvnk4g6FBczFM8/JAlEy+hh18WwSuII4vPX9MXYJTQjxWS+COcJJIg7+N2AXDCHXiJ/
*/