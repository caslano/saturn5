// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED

#include <algorithm>                               // min.
#include <cstddef>                                 // size_t
#include <string>                                  // char_traits
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>          // streamsize.

namespace boost { namespace iostreams { namespace detail {

template<typename Ch>
class counted_array_source {
public:
    typedef Ch          char_type;
    typedef source_tag  category;
    counted_array_source(const Ch* buf, std::streamsize size) 
        : buf_(buf), ptr_(0), end_(size)
        { }
    std::streamsize read(Ch* s, std::streamsize n)
    {
        using namespace std;
        streamsize result = (std::min)(n, end_ - ptr_);
        char_traits<char_type>::copy(
            s,
            buf_ + ptr_,
            static_cast<size_t>(result)
        );
        ptr_ += result;
        return result;
    }
    std::streamsize count() const { return ptr_; }
private:
    const Ch*        buf_;
    std::streamsize  ptr_, end_;
};

template<typename Ch>
struct counted_array_sink {
public:
    typedef Ch        char_type;
    typedef sink_tag  category;
    counted_array_sink(Ch* buf, std::streamsize size) 
        : buf_(buf), ptr_(0), end_(size)
        { }
        std::streamsize write(const Ch* s, std::streamsize n)
    {
        using namespace std;
        std::streamsize result = (std::min)(n, end_ - ptr_);
        char_traits<char_type>::copy(
            buf_ + ptr_,
            s,
            static_cast<size_t>(result)
        );
        ptr_ += result;
        return result;
    }
    std::streamsize count() const { return ptr_; }
private:
    Ch*              buf_;
    std::streamsize  ptr_, end_;
};

} } } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED

/* counted_array.hpp
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
*/