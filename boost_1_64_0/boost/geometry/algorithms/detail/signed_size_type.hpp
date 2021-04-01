// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP


#include <cstddef>
#include <boost/type_traits/make_signed.hpp>


namespace boost { namespace geometry
{


typedef boost::make_signed<std::size_t>::type signed_size_type;


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP

/* signed_size_type.hpp
1Dio4Q7kJmDuwT0RQwDo1b6oZ5DpPkTV6dIO9qPPiIZI6T/4bU44hYtcdH3TsMPKcjd9jZVoFrqbLHTuV3BC7sMT19t/RMYqiFubV32a9mwXgv6z28BWbH4SBV4V+cIIrt0mbdS+Zw/m5HXZm3MfX9i7ly4T/5iZTFgRLgRm4c7L+JjG6p84pk2r/9rSYcoEmZ2gtsKwMuMncebeGJrXXdH0z5X5KhoStDZBWkFzNCuhR/0TW9iaCJOZqspgSMYyivvYTf9eB45s7xn6bKe+fxy+AA8fgDHfrr/Qou7uvjB/vAWdRe0WJ5UN7+oLhlbsqB2j5Y0YzUtMzrSZBH2UEoUlEVA9WjSjDb2XrqtdlpLQS13q8VD8yKLsDtIdxprCvlQrbOYqVhg/vx2CW9TsBWd7CkELRSk5YEJQJOB32CeWb1pWvYix1LT+hD/podGaQMFZY9JBLwOZHZ/Ze5zYyCltl08bttSkYF9yYFOe7zFW6r2UIU6uFv1jKr1Cw5VYw7KEq2iYVOmlLamVFSzfvUe0xNbEVpqgCdZUNTce/adx/n7x6kuBGBn1WA==
*/