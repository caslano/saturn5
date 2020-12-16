#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/text_wiarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_wiarchive :
    public detail::polymorphic_iarchive_route<text_wiarchive>
{
public:
    polymorphic_text_wiarchive(std::wistream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<text_wiarchive>(is, flags)
    {}
    ~polymorphic_text_wiarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_wiarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_WIARCHIVE_HPP


/* polymorphic_text_wiarchive.hpp
jFHWsUgfYghQPOyd6LzLotlB2lhGU69tK5vaRo4EYiBPM46EhNz0G51hfdQ3ntfiIDsga0LVaUcTbe3wrxf+dcU/F/7Nt/xLN/+e2nhW/++f4/kXJcB6qaK5bioQrJkMHPc8bvfkPs7CozwSiKy4lEQfn1CxaVNMgcjVlCrKpoVIdZV9KgKR0Uins5I55UBjCS/jPVQRXcILDN3V7x6Is0Z0ET3528ujoOXs7MDx9RNggI74+s0CUMFjQ8cjkd5/kDbrA8ygTzFlbi7UvPZSkbnlMhNnriFxeyhdDD6kkjVqSTZoPTNaoptM0J4hSDbE7sE9PKe1m/WqBpwDe3iOc0E0DmBfkt+BXHpeC7HEIo0aQ5BwiZukEARSUiVkTDqAgn5bMpTwho4g40qwrsnIvS/r54kBDCp3t5kizjYT+DaPJE2MvmzVyso+/RjKxRuxWmhW/pYwzq7uhktKqQVslTeHZGhzhd19zWRidz+jP/o7QSH6g0CprgFxRAD127b48f1vrdes9F9GqN0f7tCaM9b0p3YHAsfzX799uBFzSZ/ao5b7+usnyaZ3502fZWz6n/rXcTxPqzmWoOQyOrglrPooYZLOGFOnqAbYWRJ+wsGSwBIYN7m2PcGeSfXiswb9cR/NUysRk8uG4+RgLgVppKiOicUWGg7hHqa9dNvpcBEldg3oOPY6WKP3bsU0yRK2YOJIrZQBCvLG8cyBICW2BH1dG/aCUX6uqYW60fA3wEGR9HZn0gUfJhfcO1ku+PiJYj9CXe7vIF2C3Hu1JbtCvFMFcEW/pt9RM172SZEz6tOAf5A33aZr602UOZaOQ0pLXoIR09aILOS2cTxzdlo0K0FPGSpv3GCXb3OAn758YrbuYBkQ0oeJyERPZJHJOprQWGPnLU48ypfYghbvFIdsEl2vRyFNitKH9jXDbP1Lbj+U/ss5pj3NJUb8u9iG4t+dY9rTGOUngoH7S/Ry3UM4T6ojehZ7OfyGA9YfZvb4vXYVVvNWfCkg1PcGfCFOexJtQYUrvTXMm48GzZurctJTvV85y7/v4DuatbRL+VK1ZspQuO1EWrNHeM3i09h2bTbOLKEeAwB8wWKGPQ3moN9/URDbfovPFsUW3pkrXkFfRkpeyRClopvaSfY30+ztIentz5cYvUXrD/SRG46+eIPrHFb0m3ox+u12EZvOMx1F0+xCfji3pbf3tGJ5bHCqlYEquJKQqTLJgQODS1fVi49UO/LOnIffyV35d9O8khS+I9WLAK7Ncb4g44wyx1mlHwLPke77RdFse+9owj8jMDaa6mEHLuHGaBu1lGJtSXmiXIdy0tKX+p97s+1K/H9SzKJ69/lIjgKA35Iq9ma6zcsGS0iR1NLCJcZ1owOD6X2EVQF0199JpanVvaDQ22Z/yDuwY3Xyqh8d3qg4ISH9fY+WoZ4rQ3Vp3wJQA02BK+K/ZJuh2zqy8EZPFQFvixxtG3kTFMvR7ujcf3b5MrVXi2WvEmgywx/G1NbrYZgQUx+AQfUcygmYxTROXB1a8T+yTXvp8Ub836jG+V9OYv5HdlCIeYD8BED6XJ7AMLcHHXQIMDteIO6MCXo4dO9QXoWulAnIemMCQ9Z3MbNQ2vNkcer/fGtjPlZ84LWhMio6N/rwgcEYkeVFaqErZKH/iEkzTjA0XL87pS5OIDETv2hnimX3tTgQOOGH/5fOdxsZJPMk9etdJsPkd6LNZHfxQp3lFjX7acFRTMAoQj1Cy9XctsvctoyjQ/Qg5lahv9JTSPekFqfmMQryv1ymvfxYdX4Co0+Jv13F/8sy7DvbGu33Pq8h+3ez/OIxqry9ofK3G+Uj1xnlywobsv8yy7c1yq9qqHw=
*/