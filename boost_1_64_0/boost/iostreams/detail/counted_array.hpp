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
ntuVfasqIEsa4ab6HLE5LEGxPMAAkJZo74ofwDMPCygsDgvNRhwAOR40HAmnn+Tfc2UV/j/nPrkjE6ooLNnmcTf0O1Mv8pueZa4LJiCi1h2F9Yz76P8hUxxqpwzWL3s9ijeTZbFfzT/L1M2++8zs+VgQeaQG91mXG6H9z7+QFBpy1+EaGL24Bqoz9trCPh1hNU4i3S8kqejJvVGqnVd7Ey7AbGFNLuvv+35AlX8GiYOch7PLsbWzZYPjJNlZm1kssEfTtuOGc20MF+GU6LQejAqxPAcxSV/+bJ2UX0bqHyYrHJtt77TuSmxSHFD/9g1xrw22TrvL4vGwtgQrfgk1gJErb9e4+wSHb+N8omcmz6lAnpYxskuxIcflgwIGfssviqy0A31h5VtcVyT1rskji3hDppWFS+pyHcjJOe1WyfouKYsJQdoPrxxwIa7ZAx1X/pjpiaEn7KNFJSHSToiCcZDQpQkgnb5bRMX9N3XbgkQFX5jrqXKUv5/6iN8FHkD4AIzXytUoNwSS5VyFj0ISNLkmbIwBJGk6XiA/b8b6oMxB4+vH1ckaeBEE+g==
*/