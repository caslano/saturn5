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