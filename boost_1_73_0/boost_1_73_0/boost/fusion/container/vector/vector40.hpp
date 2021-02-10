/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR40_11052014_2316
#define FUSION_VECTOR40_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector40.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector40.hpp
xqHu5L9Anj9gUOrysYMWxxHfDOr3MH5pLNaLcncc1HDVy8b0YdqyKNIJlvo0pXISBpJoAYDvX92c9jfGIIvsjOLwxE4Xcj14HrE9ZSasqwio/U6mguuWz+Y5ihysk+YYMarV2mcj8joIm6ZpXHOOcpOm9L6Kq4a3xFUkZnXf1Rkch4JZY+9A5oqt29Rm5IYA2S/npxdHT18evD07WohEayaYrOKb+XCn7blGwrFYIXO/wKJWwdWIhR5V9jGrfMYDJzRpp7gmfPMhD+S5ZYt36/iaGTVr6hgG9Xa5oe1mc5mZdDIZBEKTx5jdVZmMqSuZzSsqyGLEBN5ress+CNbit7BR2HlUJgRBDo978oRRHbO4EVksFzaJBJKSmAcPNKXKmSzL8Jns5a6c+IJaVNWDWljYTvQ7PVA1OJe6jDEoqYsfd4ajJUUu9lrWP/Uoc693221lc5Sj2thiwwX7kXC8c9uJkJCaGNbtMshBcPWhh6K72Z2oc2KnAmTV1eRs+NwH0MaSjEiahb71ClqM8nO/WuOvUnS9FK40dWoF4jt5PCVonbjcwxaezgU93noe1HS1M2B3G2JBAZt1w96dmd21i1um8CKMxggnOGbV8ABz92xCR+bVaMPaUJXv2RALX1qNfDlUSQSsY5VZOwjD
*/