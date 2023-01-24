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
# ifndef BOOST_PREPROCESSOR_LOGICAL_OR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_OR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitor.hpp>
#
# /* BOOST_PP_OR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_OR(p, q) BOOST_PP_BITOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_OR(p, q) BOOST_PP_OR_I(p, q)
#    define BOOST_PP_OR_I(p, q) BOOST_PP_BITOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* or.hpp
6j2i94kT9WuV9mPBjsQoVJ/NfR+V7lZAG3/NX8w0LTS7bDD1DkPtBG1CKgN4Rn1L2lK69Toz9gxm5ejJhj9AS/LovAV+1kT5CnRldoMwebzl3CNHhStoGKElsj+6E4R+7r0QgT74l90ipNxrTXGtwGUSumMcHvoGwqf8n7g0c4xqzDuYyRPoVRgNAjabv2waXT5VDM6Y/448AnqwvFM+lATQp5P+0SLrjLW76Q2iASwn3jxvKhJdWz+1J/G645+RlNNTgoXXqCnr340OYejh0lcnhcbufO854arW7FxZ4Lj2y9GcjcyUp5Ov5CjcPH+hIhr176KYabuM7I2Tu3EQKXRijT9UVXw00B/5/Caf1hVB9iq9+E0Qmrq8MFfsFmbQTCCmX2mYrPrIo0bvfrqq6KRCrl+JqpRmeDwohaeN3UjjcSjP38Mo2rFUw9fjWcGXIIODcwrcnVPiui5c/e7Akn3RlHJRTnTRSvTZ61yVt99sOaJtnEQ8Y9dcT1Jry14PlWKmgqwdJ894jB5ujqySF2fdgOHRRSZmFVG4Jpl7Ie0RPMVXX7vhxn4WtNTYsJXNO3hwGUjL6wQ9EGrebxij8fGWVz382JP12D8SqDTSoN75IVeeyfnqry/TYXNMlY9dqAcqJDga768YrFFE5+fs8ok4iO7LkiWy1S8KVAqLMV5io2c242eXZm18KB/tEJR5emEZyBXRfCuRr+su
*/