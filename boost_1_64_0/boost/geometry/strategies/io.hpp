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
O1F06TDo4vIDJa2XH5AAyNPMEpJQYErxhvx899ZuypmmNPHGaOycHD5KlSkDYiZlRNIa9YbzBa6O/QgtWWHr2YqxSy4bN1jQNnIlHYI6evtz1kJMDI2Htl4mhr6MZ1UIZfH15QmdwSBCax+yfkbjZVxrr3bUk22D73kaQsEEshcNr85PgoMklE74vtGQENgXO6UwdUzgRSd0762osZNmYw1a3Nf2uf6eT6jD+BL3mZ8qorlGAKOBRTI53YVeiXkzRTEyToH1iqswizeUurJPzWkPoErVyknCusECzJJ7xzP+NlCgk8ZD2xswQvA6zJbHYL0eScYibFVd5qZcaV1U+heSW9K/YFPESsLfVBE5sHavpJQnjncvakB9jERbyOCrDLeZ8VNdoDZrj+buQa/4w5ZYQFJb4a5skIlB9Uwl13Z6KvE6VsANt82SYYB0XYqvG9QE9/SrUNYLwspuoO7WpackmN1tQcj68t6rlUHRMQ7pxInFnlA0Zk560C6w0u43Y+0iWA72ay6iIRjadJ4rAVoF6FA677fslno5EefphbOmcY56HDFwQURybQ==
*/