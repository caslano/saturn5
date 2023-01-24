// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_LEXICAL_CAST_HPP
#define BOOST_CONVERT_LEXICAL_CAST_HPP

#include <boost/lexical_cast.hpp>

namespace boost { namespace cnv
{
    struct lexical_cast;
}}

/// @brief boost::lexical_cast-based converter
/// @details The purpose of the converter is to
/// * Make use of the boost::lexical_cast functionality and performance that many people have become
/// accustomed to and comfortable with;
/// * Demonstrate how existing independent conversion/transformation-related facilities might be
//  incorporated in to the Boost.Convert framework.
///
/// The converter can easily replace boost::lexical_cast, adding flexibility and convenience.

struct boost::cnv::lexical_cast
{
    template<typename TypeOut, typename TypeIn>
    void
    operator()(TypeIn const& value_in, boost::optional<TypeOut>& result_out) const
    {
        try
        {
            result_out = boost::lexical_cast<TypeOut>(value_in);
        }
        catch (boost::bad_lexical_cast const&)
        {
        }
    }
};

#endif // BOOST_CONVERT_LEXICAL_CAST_HPP

/* lexical_cast.hpp
uJk2bt1BG7ftoJv+IgF5QZ42NG7CNXq8q39WM/7r63dt2NhIa0ryqCYthuoyE/9SYWpqFK3VlUIZNgP/9c835R/KtXnj5q20MHoAHd+Z0NQQN5ra3f2vEYCXxI6ElqdGQztspyhLtvhv3LKNliZK6cRQd5oV0YHK/yIBeUkLcaX6zAQmS4/iX504nGYA/5P6dvwLhQ40vbsbndYK/svGD6eZPdxpTr+Of6HQgcpC3ahB/mj+NwL/U4H/LOB/MqT764QOIBNu1PgY/huAf834YTS7hxudAmn+o9DXj4VcDP0gRPjSnAgfmtPHmw8+DJbLx2HxH5uvH80OdaUm4H/jY/gvB/4n9XSjef07tDpg/lP6+dLJvdtD27lRWXBbmtbVjqYGEJrezYFmAe3sXh40O6wdlQM+PQjwAXZ0YmAbiOsIOHcokw/LJ6+/nw0afnRSD1dakQ38b300/1rgfzLwXwDpHhmAVn5fqNswT5oBPE4EfvIj/Khh3AA6ryiVrn9CS/eunE/feH4j/eC1A/TjY4dY+ODQi/TwC5voHsDVz9TQp6eMp5rIcCoPdaHpUJ6cXu1oPtQF5m+h50cnt5J//Xgpze3pShWQxlYo6I95+0B9AD2oX9WQLrROOZHuXbWAnv/gbfrd1Sv09o3r9F83b9Af4O+tb74G2GX67Zdf0OuXL8Lfi/TGV1/Q776+Qm9e+wreL9OvPjtL39q7
*/