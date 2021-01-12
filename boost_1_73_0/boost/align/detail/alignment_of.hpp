/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    char value;
    T object;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - sizeof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of.hpp
7j9lYfcXYdkFJEl0xpH9RPBMTfcqBGN63VoTwcM3/mSLjNKAcWFimieI8e9StIjkr/bCFQqwQPuQljTnefUq7e/ym732NQjpE0ckVaSA4D9jsE8/JGjQZaCARbdMYEkvCRUCoMH46ZcsBLkk+auFLpl3+ZJbya2C/z5u0TuDgoeTqmfEkeSAB3lZlT7DqvSpoRqm+SWalZTDYdWV8EAf0C0bnHUEGKmv3StDGu0IOoMEl0uw
*/