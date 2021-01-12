/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    T first;
    char value;
    T second;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - (sizeof(T) << 1)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_msvc.hpp
+5K9UD+PEJAojZUXwxABUWEROSCTR0PQeGIkUR3zkunk0G6UptkY08oa58mF+G2HzWwzS3sGFqDguKEYuBJv81wZbmS+r3PIfi2V71WIFwymcitCblcjN06QODASOfmtFDHLYxK12bj7FmtYjZcsI1402/W+M3bF2YZxtqC0X7XVfpPNEtiNOOtzJ27EXJaKjdgL9QVSM6H2FqHWNWIgyObXL+FmNovn8ddedFqNe6uKVCPX
*/