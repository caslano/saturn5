#ifndef BOOST_METAPARSE_V1_LETTER_HPP
#define BOOST_METAPARSE_V1_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/letter_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_letter<>, error::letter_expected>
        letter;
    }
  }
}

#endif


/* letter.hpp
Y0Jh/rjCcsYlsXcpf0EuuC7A4coWtlO7bqw3zK5z6XURdFoLDNMsTR95ax1lUwpLKypKHAUVleXFpeMdrojPN1dTb0091GTy2IS8TT/Oroa1BrPTRpvo5TwYtbu+TGE/qIbwc74N8HIjE+JXGhxOrrai9Rhuifpmx9QXiqlP5fWFebnE/fEpvmg99JTj7wK6C7pG6O7krqgfgroy5hjs0ISoNXU4NES6a2BLbKejo51fme8YV1xeWFBZVn66Bp3wCfBQWZ6byWR5EWTZ3UIvy5M1SabXfakc43pWIFTi8dcpIW6morzSl/orZLLHn+C50KsVnnlKmbsgxl9rze8X+z1hD7UzimucHJaJ8OfY86l+T0wJjkOT63yXC0KjlrkL/eHQ3CkBuIziOWR6rKwmqLsbv0/RiftUdouhxhT6kLeD2rMKtq1wPv0ehI96Fo3lB8BGehXxIErDgYxmZUElBOvpr6mYC5fEJ2x8tNyxlHYmyh3H8GmN408b6xqi4Uj8LIvBVWDPTIFZ9zyHwiZ6zvuXR6Z7/Lk5/PY02RsRdBnOx0erWEfzUfz+BEV2AY6Xp7qqgG4iXRHxCf05jjRWzdtEfVH4KAW1ckh2wvmGL+dxqvoxmsDxV4QhxOWKqoTqDWNbon9eEPD5PMLGTxFtCzJQ0Z9K3TMO1ojzNPibtDfM6xN1VZHSiK9aCZW5y+vlfL+LYog+nwf5OotQDhvnCYGDsKu/5i/1gUjN18n8R1x+oT6ph55fEqvI4x9peuVog/9IP3vB7GUHTVezD3lQulDfJAN1LhB1QvYKy8sdrIyDbpQa1Vvxt5n+5nWxxbLheoeqOPV2qjW958dNlB3C61so6oOc0u2K1aDi1GqJXmi4E/t3alintaMXWvmxzenAouKSwhj6iduCdhMT4bA5DhMN41ABVSCHIyHGV+fSsdB0BJOGKM0Wa/51mbYntOwVz0bz2GSJjna/RNtVWsmrreBNirmL1mg2i8em3bjNWqrz56Cvud6M+nPiuj/vxwVa3WPnhhXG/xdq19MDIRfZHY1xltG42kSM047jvIjiQLwwhNu85XreaMaXj/quXTPxF+O7ruD9u6T5GBb+Jd/hXIG/r2UUVK2ihE+4T72S4xyWEGcNDbQcumSB/kajT/F3jgM0EzioDzW5cLLBbxI3NNiOnGZXaDRiBYdxul2p9xWAS1ZrIRYUgdYO/Y2mZasRTsA0+iqgd0vKE/zPwXwEEbuj1qs53Vfz/k1MnjuwEANmZK6J5jia8j3jXc/Ez3hM6c0UMeVaXXy0LiY+Wp+Jvxge28D7ej0ve65B1ov5VvBE+DqN9yZ4amqJztcpc7tVJWzIV/F7tKSI02lZ6sVQ1tLH7rWF9Yq/MX91MBr3D33+KkmcGOfHUz3PaUWdQwMxEz/k/KTDY4KXKf2pjonS/xZOx5mcjhu1PjQKofadKn0c0rLxma/a4YyEaLAXfR6hdG187nU6nHDygswXKeV69FYdjdoadAEzb8FItdfDbFJTD7V+JIzNk+YMMzJvF3EFYgxBhzt1fHhXDB/enYm/GD68h/PhvbxsD0Ms55jilZ1KbcBLrQhsNdMV9xt0hcMTqI64tWayU25LdbrJpoxF9dWDOn01kbdhU0J9FYNJqKH4Z4x3RRtT4N1oOzfr2lnK27klYTtjkfGGJn7YqPfXxsSSj/Cx9Gl14G0WPpaP6XIud8bAPMFhQhzmSQ7zFC9noEkKcXmUJs8koMmzzY9dQXODxx9y2UnkDzqiPuCwPA2F7hpQo5PbciqiiQWXy94LJvwCH518qJ4bjkEX+6BxbLdynFF/+EWtT6ibZnK4vn5J042+6ui9It7/l/X+tw0=
*/