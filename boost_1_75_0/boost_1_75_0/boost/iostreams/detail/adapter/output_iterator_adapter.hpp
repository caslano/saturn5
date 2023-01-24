// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                      // copy.
#include <iosfwd>                         // streamsize.
#include <boost/iostreams/categories.hpp> // tags.
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Mode, typename Ch, typename OutIt>
class output_iterator_adapter {
public:
    BOOST_STATIC_ASSERT((is_convertible<Mode, output>::value));
    typedef Ch        char_type;
    typedef sink_tag  category;
    explicit output_iterator_adapter(OutIt out) : out_(out) { }
    std::streamsize write(const char_type* s, std::streamsize n) 
    { 
        std::copy(s, s + n, out_); 
        return n; 
    }
private:
    OutIt out_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_OUTPUT_ITERATOR_ADAPTER_HPP_INCLUDED //-----//

/* output_iterator_adapter.hpp
jPbUE2SeGcCHjy6vA3vvfTK+25XNujnQOFxYgfnkuwN75oiLL79N7aTdUvvJBmRzjedX1Im5qH2yMZl4IzxBX0LoLjrrGgg02yp7j32+gyl4OBu3CJyFjNzsQHouv2njEAxGNb08hxH53/lfKnBVAAe3A9ySfM9h5PyvbqmXz32Wb5WTLrL5cWEBwyRpGPKQnofuJI4Nv7b3726U8aZGzxsihNrkTc9RN1OGYdg/jg4wFFZkxV5NbFCOm2THTymy7kiLiT0P4T/5U9mh2THtGYxXSPlU9wXibr30f3UlvvdyXMTxeSW7T2oVVay/Td73p1gQmhHCxNFgLNg3+7QyC5IWlKn2lLACDZ95KnvG5cW8wueLehYtuRQfL82GVjmldsx6cSzhuC+HZ2dV3cVUW48iq4b2dR1dAq/v2OuP8ym5iT2kfCq3R3KSwxy02IVOFOsf9z0Diqb8tnwFmtV9NMZqngxHf8lfnFj3Pfg4iojbDiX3iD/UHAd9OcYlG1utDDTpEwcNiiPSn45Wjhy0buiPDsMBV6sTACSmU67baaPxuL5eamguzcmZLy414kv40Dd7ipN5zsCuDIpksWqvfrfH1RxWn/tLLJ41ru+mVFaz7FRjPHtE/WT6RwSQ1+V373+0imw9pRgqZOWEDaSLTdWrrAocj3du2fcJBhAzaL/EjD+WX/frm4FLyDWkTEs0bYqYJNdpc+NTMFbj
*/