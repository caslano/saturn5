// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope.hpp>
#include <boost/geometry/strategies/spherical/envelope.hpp>
#include <boost/geometry/strategies/geographic/envelope.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linestring>
struct envelope<Linestring, linestring_tag>
    : detail::envelope::envelope_range
{};


template <typename MultiLinestring>
struct envelope<MultiLinestring, multi_linestring_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_range
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP

/* linear.hpp
cRrwKwAvVwjvbCWCPnP0y3EeMLV3gEk5ubBlEsbxEHTaXgAG79VZUlzCvFrkeN848sUk1NMZTuFW+nB0V4id4bSIZ0Et58errfr9jqOL6maFktP3xmm4bzMP3vpr7rNkXjnhzGaWyFwsCJ8zywJf6jUw4DQw4Svz0K/MR68GMOGyge8suJsVQy6EqeyuB1fnLqMNnP/ZwWUKjn6pMVZ6cP/+jntwT8+C80IS1nkBzzsvcNZ5AbfOC7h9XsDFvAp7jmod7q2rzaLHP/fpz3BNLtV1MlnzyUoCDZ6IzgVHgusW8OD9zWUunFXr9CtdOKvW4XEHLlftf4czlit3oSbSLSgKqEmvy3eP5UTrvt7R3bviPnFgX0/24Zi8+/0c4+S9ri9DRCWF7XXeGmu7C3iqdW5T3fH5JqJgnLKbjhPeT38WMYDr9O1XhdPv2E7X2gTrk8W6/wKv42bqPgpcgbqb5w7PeSNsZ8Ozx/nv8JSWB+tdBt4Xv80x2vvrXXMD+Kq+7swLfKCWt2ewfeC+5DyHj/45qP5/ZMFXae1LJa/zti+34KsK008uO9j08wqrfla6OsNhtXmXW+F0PVuotQnq2WJdz8DruGq5Nh9O7MVa4K9z3rflVtSF3O/AAfbDLULYNwVrAHbdAHg8QMGWAWuDbi+NbiWwr6GpGKhgEQd2lUbX6rSdocHagR0I3eX1CtbhjJsoUrA1TtsfOG336pd8ertiq8Tr1eQ/xbUAM0e63Sen+d+m31Qyk1hn04E7/f6EdRzlrGNHIbtvu461iS4z9rnbuv+Py9UuV9SyrTM8o5rioWdf/pUdhn7Fs+Xd6TQvha5MNHPo7OZFRzPX3IAkTc1Ei6R2XPhKZFLRLDfe0irOH+nQye/I9N6uPNmN5Ye6ePGcOilYt1yDq4+/dnhSBu2Sfu89+uOTT4stfMjKi5EeL5qZ6GqeiO7OyNp5AO+uIJJtF4+z6rWPk8c5NDIplWyLHJhs1sY5xUezNgrXOGpXNuc0Dy846g7CGoIykzOkd5Wjn+e1FbyUI5vr6+7SV+j168mJ6QT89vnjNJx7LmbItyXOjH32+0KvHUfp2V62Aq8oAD/VwIvxcmhWzReodkUFnWV8eCbmoPHzZB0nu2DZxIjGupidFhMd4bWDPLDek3Wc63OC7ShYoAhSAj49MvVZ58nFtOdOkhQFX90YPKO5JIBXV5ZUH5cGabgmqY9xmYHnmmS/n7Nw9w5SS9ueTXxlRD/ec8jI3osOCx6XXWG59/26ddwrPZ3fr5QKL5cv3FeKqbuPVxs0/ufLrjXxKBP1mg56yah3Y/7eTser7LvauP4GrTrzud5Oy6y0+28Gjf85tZtMfMY1GnQEnVqf4lxuk1JNc1/RmsnVFG+D5vwtQthdYqp+2tHmVv6LxFp5V5BFD/5ttaN3MU5ZpWxEvU30lLMJ0/s9XjxmvkvuI2u8dK8ciwbuSGrfvwEluGQqm+AlZKFCxrfcBf7UOv79zlqbY+b4D+ZwGEUr3KXvXx4m55XMI4evrHJ4aJxcvyaHfufBcrwMaZ8tbvnGWkd5RI4ntI528n7lo8CeQed+QazW6MQ4jzuw4zTYkzKm41fBnga2xZa81zGkYOsd2GIN9g+n7ZEDFewlYHtDF9L6e9Wh69XGfd2he1f01989keCXynhL2vo8/EibjfrXOPmuiNKKCur/lLRozgb13Yd8N0Djfsend2YSwAffA/lBAI8l4ZVizCFP/9QIktkkN/U1mg1BGvfrOrW6+7v5aOTb+eirDzqutuk596cajbTaygd/ruFcXtjaBb8/4ksdJ745RdyldFyRHlP8R6frjK7W5/W1hgveTfhGxxHstnt9K1k=
*/