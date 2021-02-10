// Boost.Geometry

// Copyright (c) 2015-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP
#define BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP


namespace boost { namespace geometry { namespace formula
{

template <typename T>
struct result_inverse
{
    result_inverse()
        : distance(0)
        , azimuth(0)
        , reverse_azimuth(0)
        , reduced_length(0)
        , geodesic_scale(1)
    {}

    T distance;
    T azimuth;
    T reverse_azimuth;
    T reduced_length;
    T geodesic_scale;
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP

/* result_inverse.hpp
/oywupyQPBUJnuDUOeNJHTfkge76AEtvoxPtR7bpdoHLIsm3kTqWF+eKU9z0eNwo3NqnqteS1MX6OxYKzC1VGjHh1Em/0rXURslr1mEYVT6kPjE6iKCxD+hKfrwvcZKxpxJHv2q4FV5oxXkJYyWOftVwerLN6Iyg7jQF5HXMTrZntlwTgOfzUk0h50AezfaYc/E5OXnyIVv1UliNW0k+hz59L4aiUXkaqQ+XLTDsMclbsNzDFErpPmbtpVvBVBTTmhqQvN2YXirAJYZGyk5DQkHPwAqoOok0wyhvEBRpVN9HTYyxi5lD6api8Thh/OYCc5jX2qa5YghLVIE7DDFKf3UOhDZsYQr+Kqw5bPt09DkOFlSMyUK6lTUnHFWU6S5UUg1rDiV8DjjWSzo7kZK8CiqrbNe18tjotsRSXwaxVptbvTDVYDAY9Eb0xMaD7u/ynup21ZNcPKrrN3PDomm6B999B+23qVX0evDyojbxBXfavm51R2JwWfvt2Z1+n/fl+0SkguI036zK5nKTOCWoOttt7Q5qUNXONAjcZ0OYEzA7ekMaolq4dvFYeR6H3n11Ui+8UAfJxGnXhYOSVRzk5WvbfutsACfDTf8g9m0s9ZvUfmKWeMZTufR53G4sHmGpnRaB+Nvshfo5qzi5
*/