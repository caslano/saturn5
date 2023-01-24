# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ARRAY_ENUM */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_ARRAY_ENUM_I(BOOST_PP_TUPLE_REM_CTOR, array)
#    define BOOST_PP_ARRAY_ENUM_I(m, args) BOOST_PP_ARRAY_ENUM_II(m, args)
#    define BOOST_PP_ARRAY_ENUM_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_ARRAY_ENUM_I(array)
#    define BOOST_PP_ARRAY_ENUM_I(array) BOOST_PP_TUPLE_REM_CTOR ## array
# else
#    define BOOST_PP_ARRAY_ENUM(array) BOOST_PP_TUPLE_REM_CTOR array
# endif
#
# endif

/* enum.hpp
XtSwPalxRVTK4ua9S99tjIqOybuwdcINtn/5/faGy+yZ6zOyy/tUNCrPxpxeH9swekoIZa1tOdhSknLnV+Uoavt7DXcVp9uXHJ6d0lRuf+FwetzN5YnZ447NK96d0bR5X0zm/tiirAuHW5vscclo3l0Zv8h1dIu56oq3o6asXzA3xVZ8uii0u1/M0cYjiw+sKl9eag89kZpyvPurWxr9d+VN2FdWE3/k7kWfFa6YumpF4orC+Dvi1x2s/tvhtQ+2/jl6XM4IX3zLW/E5F1y3t5xXNivPNp9S0uNr1jU1JMaNLT+vPLV07NpyJe4u+0u21PXJ4zLjjrweH/cn+0slmTEpfTbv2Xhrad5LDTNTmjYmHL4wKLMpKj4ubl3m2vJxqfbjT6Dk8rxq1FK0eX6hcnzUCJvj2OZxb81zZITGHNx2oXnCm5+njtiRsvryE9tDHzdl7hmT/ceoyf+6qPvqtFOPFQ8a+/aEvAWOnfZ9e2LSBipPry+8cO2aEbfYRt53d1FWIDWu24Wi6qO3xLccX3t73CfHBxx46oV+nthDPavjW9amDMh/908Nb32wddHHz2z0bEturhs8dltcg8/3swMNxccqtpaUtuxv/Wvf5F61t/V8dd+Z2i/vn/Ne0uWhdUm9ZsQm9Mq5K7P7gIX7lcuLQ+Ut0eti4kKxSb1saQmX5Sxcenisd3/5zui3nm1pXJfkuiH2fyct/Hzz
*/