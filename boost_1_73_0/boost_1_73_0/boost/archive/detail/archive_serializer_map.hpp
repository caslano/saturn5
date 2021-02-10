#ifndef BOOST_ARCHIVE_SERIALIZER_MAP_HPP
#define BOOST_ARCHIVE_SERIALIZER_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// archive_serializer_map.hpp: extenstion of type_info required for
// serialization.

// (C) Copyright 2009 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note: this is nothing more than the thinest of wrappers around
// basic_serializer_map so we can have a one map / archive type.

#include <boost/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {

namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_serializer;

template<class Archive>
class BOOST_SYMBOL_VISIBLE archive_serializer_map {
public:
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL bool insert(const basic_serializer * bs);
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL void erase(const basic_serializer * bs);
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL const basic_serializer * find(
        const boost::serialization::extended_type_info & type_
    );
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // must be the last header

#endif //BOOST_ARCHIVE_SERIALIZER_MAP_HPP

/* archive_serializer_map.hpp
9tS3IonDuAKzVTk2QiaqylnzNHS8gkKmqXZtFTnZjNRC1kkFEaYj9ug4WECtPmAjhNOOsxtVGlJHebZbNWwNostsDTKSpSNekIlb2Xt85Q4P9bUGHzWHCO7p0ORRTqaT9TFzk1vur6VxWuBKzFEJNNYebc0efw9YQID6dtJsn21qAwsq1DcrtuBI01VMts5bQ7K41FWP8WWeskir7FaMP5x9HV5dvhudfR0Prt8fdRcFYed9wLKgHtvjZ8vHD+NU6401HwaysWxDNUCBliG9C8KEdIbSOhxOdIicui7IOPaEulXENXm9XPH0VK6fOGRmIb2GEk6fOt+ncQcO33HO5CZVjLNRqiwgJEBAg7yNIpGk5jPW+t4KlgwGgZSb3uKQXrsImNud9uz85N354Gw6YxCz4Xhsfno437jMM3bhbrEi6WcN3R+DzTD/nioMhJhiPSMuzeaFXpEG8kjGLSHcEkc7/qjRkaBDP87CpI7UjrAoYcD5xgDsfWfDgm1QTq9kidOxWkRvHpjsGGlDEj5C7MKv4lR5RguwH0wqgDUTyJOKvbtVDCe31jVgwQGSYEndOeYFTBc+9X7DB2Tgb+PI7t/YMaLYMgwd4SUwLiOffJLICBlesDth8REGH0sxRw//c9LzJ5v6hYjyqHDB
*/