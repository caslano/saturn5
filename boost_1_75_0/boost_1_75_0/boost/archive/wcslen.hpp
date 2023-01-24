#ifndef BOOST_ARCHIVE_WCSLEN_HPP
#define BOOST_ARCHIVE_WCSLEN_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// wcslen.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#ifndef BOOST_NO_CWCHAR

// a couple of libraries which include wchar_t don't include
// wcslen

#if defined(BOOST_DINKUMWARE_STDLIB) && BOOST_DINKUMWARE_STDLIB < 306 \
|| defined(__LIBCOMO__)

namespace std {
inline std::size_t wcslen(const wchar_t * ws)
{
    const wchar_t * eows = ws;
    while(* eows != 0)
        ++eows;
    return eows - ws;
}
} // namespace std

#else

#ifndef BOOST_NO_CWCHAR
#include <cwchar>
#endif
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::wcslen; }
#endif

#endif // wcslen

#endif //BOOST_NO_CWCHAR

#endif //BOOST_ARCHIVE_WCSLEN_HPP

/* wcslen.hpp
Bsq9HWqo3N2hSgVBDrV9QRgzZuqyGDFCyOiJHfQRKGrWgmVgdh4shKUdGgvjyFnGL0IG9Nnxt4wGryEdUYMtSEax2rkn7teWumj6+lftPB4IGYqJU3+iBHq7aucT6EYk10QnX/ZYGqKTG6Kr4o7bW+2b+kPCP7xhrmP2EKUstP0Eg6GsOqxtlTu0Oi0k7Mbn7tATS2FAXfahXLz4IL4yOctHfUT+1yMf4bdN80GJuh7NkVxd2oEk/ARc5yGQih3eD3SjPIQFrTEZwKPurwyPSMVH33IPDCQld6YDoBjdValT2uFaMuO7gNJ5mRnlSnBCYKX3P+zbuTqLGofTxfIvHxIL7UH4ZZ/M9YUJOg+l/D/DG1QQ1yPww3bM1Z+5vQBJJYp/iaW9+YnhPmE+DW0QVfpwJBZpk8ewnSB+r++AEbFLO1AXrW3Nuo7y0d/vDvqlx/zob2rboNPvMa0Bu8t7lfXQaYxDGrMtjfRcKAp+eVUAaJk+mXwGZARNYzWaTowHZVU9BwjPCKk09EHBrT0FzG5in83BCEfpbjO/eApVSXAWrpUrkM6Ks5jlDlnuwMCvA69OlL8QZXaW5RgNovRPqBF4lb94qsWUjWsDvBpZAFMW26ZFweMhUHAvFmSEtCiwYYEZC+ZDKi3bFGbA7+U/nmFl/+quX3AndQZdF7rwlhqT8TM4Q11wNZzxJF8pMTpL5XukPdNUaU+p11xh
*/