/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_NOT_POINTER_HPP
#define BOOST_ALIGN_DETAIL_NOT_POINTER_HPP

namespace boost {
namespace alignment {
namespace detail {

template<class T, class U>
struct not_pointer {
    typedef U type;
};

template<class T, class U>
struct not_pointer<T*, U> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* not_pointer.hpp
o8BcogvlgEQCpgc4RpHmwQXH9TezaeOsVhzNh72TDo5lvNtkr4jXXh/hjNqPZMBsSQ7QmH/twWqYjIZtq6y1Fv3mSMElear09q5GglncgHBvCs3qzYkDP5lIRImbqIIGP167pkjQ6FquNFbFke44isjsaseQKInpi9jST9fVxo+1pv89gtnt3OPIl8NWWr1y78hwCF1lp87ZA56CwbSiAzA6SPRFZzToPJvOI9iRyfJF+wLhvJNG6QOiWIMWLj8jC+aIiuzSI+lnAxnzoLFNUsgVxr2opXJE2pguiSFNuhjJ51wD+xy9l/DAaEWmkpxWowMuu1favx2c15K9AdhE6d4RsDNYOcpq5gubJJDT9w5YWtt2Rt8CGfH/6EwEoaYjJ0mgM3BnwlAyOjreMy5Bb31i6qa/Czf04GI9ymyrxF886gncoX1Yq72oPU5hgWSkZBISY5coL/NG0eVY9uC/rXje6NIuafS4E6xw2gJ9PmbJ3NhCdCMTOzIQo0RzECIyDrPXduMAqn6UvVckfp6Z72AEJlq8ayfYIvMJHmdyUK0D+73mOcn6vfOj/A==
*/