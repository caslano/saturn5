// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP

/* io.hpp
SW+QVNcNlnsIAhpk8zAxmv6TyYZ2kbXOJXWxLHvfykoJX5aJ3EipMqOptsjx/eokrwaYNEOBwhFUe6V8HG7lfcU+0tAUJ2ONyUNYOOtIsTr6addym2CZ1hH7pn6iUt3l8/I7slc8pnvxGrHTFU9qoiZCg4eXP4U9os/z3lUV6GsrC42W1kR7C32uvOIYdBzNVSlRA5J5zb72rw1TTlLCm5W8DW5sIVqplMwsqZ+OjAPxulXhB+/E4j/Axf3fdsI/wj4FoXENyxxZeMZSyhiIKOeEnOmr3cvB3sp/L9O2bcmKqa12FLCabPW0iL3sSmaVwvEYoS6l0iQ1QPUHG+eSHGXdst6uOa+gqrjtQ+zQ9lIPp/DjTNht2d+YihNbP0k9C4oHIHVLAoKrPuQ7LH9gQNtx22jJtpei8pjaLxOBMQJSfw1+P8KYPrXKW5XyDw9GzzLJ1zmC3GLDaF8ig422rGoKumG2XcE+T60UnlzDGDtXxvEBmz28xvgny0q5dyhFbucCHhDhnLUI5pIxj2QDbCxUEy+TYMv7mG6KTMeXnd27Rq85neBxk18Owtdr4TWkcYmAJCjaCFd6iRx4H6ByDYC00Ex5rqQDxo6srwH0w3sCsRN7erh0om7gG4YkCD8kPRnxNgkirsLlR3f7OgkiAbS8Pi28O0pdgJj4JRANurh6unVH8Qe4xORoXNo8G9oYtnDaq/9YeX8aUKum
*/