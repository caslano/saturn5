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
rCwXHr4HDz1Wc7kA4TB7AVTlrYCdc9UIcH8A5w5izOqssDut7GK4fSQfJoO4pT3QSMv8sYAxi8/hqoAuLo8VhKFP7n8jrlh2JLIotBTRwRn3AbDG5akUQw8B0JEqSQ4ZIkFbHADrTixsErEUArMB2FTCmK3KbMHgnqZ+G0cEgZHryhFTW6wen99daZ1P856+nLF5JYUzBX4jAXQTqM7YIj9B7c45LoplGtqag5wlBtFTd6XFOz3xZDA8ycpjzOw=
*/