/* boost random/vector_io.hpp header file
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_DETAIL_VECTOR_IO_HPP
#define BOOST_RANDOM_DETAIL_VECTOR_IO_HPP

#include <vector>
#include <iosfwd>
#include <istream>
#include <boost/io/ios_state.hpp>

namespace boost {
namespace random {
namespace detail {

template<class CharT, class Traits, class T>
void print_vector(std::basic_ostream<CharT, Traits>& os,
                  const std::vector<T>& vec)
{
    typename std::vector<T>::const_iterator
        iter = vec.begin(),
        end =  vec.end();
    os << os.widen('[');
    if(iter != end) {
        os << *iter;
        ++iter;
        for(; iter != end; ++iter)
        {
            os << os.widen(' ') << *iter;
        }
    }
    os << os.widen(']');
}

template<class CharT, class Traits, class T>
void read_vector(std::basic_istream<CharT, Traits>& is, std::vector<T>& vec)
{
    CharT ch;
    if(!(is >> ch)) {
        return;
    }
    if(ch != is.widen('[')) {
        is.putback(ch);
        is.setstate(std::ios_base::failbit);
        return;
    }
    boost::io::basic_ios_exception_saver<CharT, Traits> e(is, std::ios_base::goodbit);
    T val;
    while(is >> std::ws >> val) {
        vec.push_back(val);
    }
    if(is.fail()) {
        is.clear();
        e.restore();
        if(!(is >> ch)) {
            return;
        }
        if(ch != is.widen(']')) {
            is.putback(ch);
            is.setstate(std::ios_base::failbit);
        }
    }
}

}
}
}

#endif // BOOST_RANDOM_DETAIL_VECTOR_IO_HPP

/* vector_io.hpp
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
*/