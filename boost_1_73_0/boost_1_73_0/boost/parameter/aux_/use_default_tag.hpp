// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_USE_DEFAULT_TAG_HPP
#define BOOST_PARAMETER_USE_DEFAULT_TAG_HPP

#include <boost/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct use_default_tag
    {
        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(use_default_tag(), {})

        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(
            use_default_tag(use_default_tag const&), {}
        )

        inline BOOST_CONSTEXPR use_default_tag operator()() const
        {
            return *this;
        }
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* use_default_tag.hpp
vnmkEnczqB9XLxsQVzUOakbOtOB3q1i/voLgm8jWeosQJvkPUEsDBAoAAAAIAC1nSlL/C7pzYgMAAFEHAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbWFucGFnZS1zeW50YXgucGxVVAUAAbZIJGCtVF1v2zYUfdevuHEMTG41K8nb4qSIl2ydMeQDsbcimDdBlq4trhKpkZQdo0l/ew8pu26QdnkpDYsUde855x5eaX8vboyOZ0LGLJdUsy6D/VffbwT79OJI/D/BwOwSbrT6lzP79eAkeaD2h6Qp5hcoYtplPCQ9ejHjgUKfkWw4Ttw6SV6gmTph7hK7xGniltgJ9pF3ruq1FovCUnjeo6ODw5/oR0xHBxFdpFJwSWPLcsZ6EdFJ7nfOivT+vm/4TURsKS37HmhSCENGze0q1UxYlyJjaTin1FDOJtNihhshyRZMc1EynV/f3I2u3ka0KkRWAGOtGjKFasqcinTJpDljsWwh6lRbUnNkAzsXxgKvsULJPqiZLOvKAMKRp6VRlC5TUaYz0KSWCmtrcxzHWaNLKI9zlZk425beL2y1qeIOCqp0Taq2ZBU1hiNycRFVKhdzN8MKbNbNrBSmiHZSQCTzWGkyXKJRXZpg00pmGm+ciVyU6+VKWDcZJY1jWhWq
*/