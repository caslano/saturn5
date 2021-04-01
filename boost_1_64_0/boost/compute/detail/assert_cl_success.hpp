//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP
#define BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

#include <boost/assert.hpp>

#if defined(BOOST_DISABLE_ASSERTS) || defined(NDEBUG)
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    function
#else
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    BOOST_ASSERT(function == CL_SUCCESS)
#endif

#endif // BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

/* assert_cl_success.hpp
Za0lZpQmF3M2aXURlLIPDVectDDYXSr2FGFX+ys4Ah93t3Gu2CeBXBlbeXaPKu1F4P+i9iW7ENC6WEhMPaYJPfsJE7nDhVFVzWRl4O6L/5lASNjN1ccZqn77PmwCKvXWTy+q4jrgClgYUVL3fjbRegoQF/hZj7jTN8j4NPClhmiiWKOYgxKjgg+jaq5h7rkeodHcaaI3BkHHJ0gNOwcg8+BmdlIEpwEyeuf93laVIGnJ8onfQ1vfpQj8TfCzpVW6pxRTy/gFtJvM/K5msOxNE1Y8JgrmWlLgLk/EWk7fiJOnEDFu5eFcdBuNC79z/Jz8uZNy3aMxubIMYCwQlI1n+0Xf96m6xjKaE2unViuhif8MOUox3HQA4pdeb625iBxvOUZdV44yXFyagoiSw5Nh9DT8tT+ue/m5OAPvo+vOresVMCXF/tlBHqYYGVy8sy9UkgIuy/ugUHpoD9T+rrePBKnoib2Y9/aT3MrSy1wOVFxh/PY5IsXKQSp/hOOF8K1ApVwC0xOe6SU7le8Tv1f+L0lxzBX2qyuaTf6uv00C2Y7H/arStd8lTDAoeg==
*/