#ifndef BOOST_METAPARSE_V1_GET_REMAINING_HPP
#define BOOST_METAPARSE_V1_GET_REMAINING_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_remaining_impl;

      template <class T>
      struct get_remaining : get_remaining_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_remaining.hpp
FDGRq3goz1Q223gbMLGIJAlehID5zA5lez7h30+SlqU0hxMsvJwYlQuJ3DuUa/cfTv3R1yBYZtPvthzf35DqM/Hltkdpn6r3Y709SeoDhOd3h7ppu99I29Ie9XluXcwyxOif08oFuBGeXGWtoPx2bHSdM5IE3SeZLh6OYOFnmC59JjcRSwc3CQpMEtRnDBEs9D1oiOaB8VWh065feK66D7pWD9ULtVTTNltrgl6eFlaRq6gWixjNuwTjiOu0B4KFFx2hT/Tz4bXaUfMhS/Y4t24MX6QTzpXZ4EkTtr5GH8FCX+i9sM7cShLUV4kgWHhBEd3d+3XgrkmKdfA01n0tzpB7BI1DzSEWVoVXptn1xlnUFJPw/eWNYyYT54SewdWaO4OzdNsec4pehOaDImCiHBTVqXZ1U7eOZigeZrdZJVl4eRM2qyDbl0oj26sxn0faCAsvHKLy0s6HyzfSepT+6fpFmiXunnaeHqnTwT09j/HQEU57WabeiF2drlA6xbhJ9Si0UDjq3S9VFV3lEebw07mjjjH7gmScxeoAM5BL3ILBbWIYJUmF5NsJ9CSeDE/+R8LkGkHWYFbGXiXDoMwJ6u/oBAv3SYYkt9+Ov7TysnvS/0Dj3yHI8U/GT+hbmBAswijBvRvfN6t20/8GTMQRJc1GGBDOebE6S+3db/X6+fzeLlzQz5oeKLPgtzv0ZmnPgHBwn2RE3QQnWP8DxDR4xMb9Ej4OuGemLZ36z12MRuk+eRTqEON+UMmIleles60baQMJ/+jzFqlzHhBIAfYeAlRGDwCkYnsPAWqpb3arqvsFbBMXDL54p2Y/txSm+T06pxHMwKohuzYhJeLjBkF7YAQko/pHO2E4LlE7fYL0zjDrZG32JpgVgGk+fSzUap5bVyDOhGoonRt5shadNUH3Saa78BMszNJH7ASVJOi/6czv7FmYBDY1H8fn1v2bqV+U2RRmu/IRKEuFCkjGLUwZU4dyiRslfRoGN4tSc83v6KW0i0xAMsZz0lOF4xIVcSyNwS+K7liar/nGFQvm+MiIjmW9fLDqW/FFxdVGImQNQcqP5rRdSzX2DoIUQQmAZkUUZcx0lpkBPhoKi1iJuwTj+FtUWYFYRAsIPsXKw1HcRdIDyHShcFvQ5Vp1/CUNwa6er8UOCPe8/0H6JHcsnrpChDkulTt92wqTOp9fkOyni1EFWYyLn8tQw7krIZPVHsN70QbkKT5+e3pbEpD0olK2Hua4xGHDMt78GPnweanx0j+/K/+R5v72j7tT56OR2uQCZLNa4JNG2dvGpm9N/wW6rpjSmpgdBOmi3AO8GwoEPJGSzXWn4wAfSVbnTEgSNIgfYXiMyijBe2U3PuB4Si2j4YwkS9opK9A5+FSQpN7TfYWXZr5LRmCQjg24xgDZlwOCGoiQi0YrABE/jY6jb7QCkn4KKBMKOS7uo8wk7VBd7Mm+3cg1ybRi9z1c4paI+e76VYEkjvcI9F7hEdWe8LveOFIyXQT4iJ4wz3d+Dn7wCL9rJ9d9dailoQodoPx0broS0ZAaZ41oiI6o6W71ys4AMAMvelbQpe+u7T07oLbggZC2UJ4g7bIpD+/YaIL6blN69y4EcMF3BT5fpE7URW4WI5E/GDerSBLUlzAiWJCJsWEwoUtqU1ablfuTZ6W2v+s3VFqAWES5clFo1apNhqBcSdIBknEvt0x2zfv7VhqCEhgFEDtSXMNOnWon2BbohjBTob68H/5Zb9sNJNQXaXhT//iqaX0ATX/EtG4BPf2iwku7rwV0epFPheIhG27suhUlrjMGDd3oW9Xb1ya9gEaAynuDwCtl5Qr/QedvB0iqztNQNN8eD5h97uny8IYvZ0k=
*/