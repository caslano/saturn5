/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEGMENTED_03202006_0015)
#define FUSION_IS_SEGMENTED_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion 
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::false_
            {};
        };

        template <>
        struct is_segmented_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_segmented {};
        };

        template <>
        struct is_segmented_impl<iterator_range_tag>;
    }

    namespace traits
    {
        template <typename Sequence>
        struct is_segmented
          : mpl::bool_<
                (bool)extension::is_segmented_impl<typename traits::tag_of<Sequence>::type>::
                    template apply<Sequence>::type::value
            >
        {
        };
    }
}}

#endif

/* is_segmented.hpp
YZHQhp3Q/fV+6paUDlkj7dWGNumt4nWk4XtElL93Z3T8JHkcZnF5w/tFXGcbGbMXSLovyRwzQDq9YOqNwY/ueV4aI+7EAHCuLEanVQU+irt5zZ4DKQ5aFSzRVtZftIFgxF6c/i9YMxkCFt8B7Yk1kyK+oaHYxkXf8rqu/Apitvchxp5dlmjbPHg/xZA83fkecQvdMN+B1/EagnaIu6lr65iKLOB5kLD+5dN0Z/98R9ee95FhEEd5wmutnaa2vK92031UVNQyKfCWqYUGHfZ1LnY+LmXJtQumFcdwNMAYgKuufWxdyKyMqiZCHc3/MMGFhUzjrCjY2vaEePdvSqmuX6oykqlMWe/g07UF+tRy+UqmgjCpy0qwZnSdPLG5PcE/0hdTquuFlUo74O54dmF0uja2mNe1tHd3ItIorxTh6/sY+wvNq+YiLZXgHc94Zbw2Ma+pjN4jVCosgxjvdWEknvZsgA9nNMZ9HaRFLLIuLxA91OcyfI+Q0Ri3GUhTXCPPeBW5aPkWaPkqUSZpILHdXbllaP+cuXLOwySoQll0LJgL6m7P0LJxHgkVq6h3pUxlbj0jMs8zpXLBiHPBEO9hs34s4SSUmeA0A2zoafTLRfhCFmYqzJJEdHzBkxdTzWsYp+9m7BZvCjWfAfViA7IIaVbYO5Ce140d6NUGp5dttARF28hv3R/WGJMOSglahFob17fFfQy1sdT5HOYao7txQl7G7nSuwdDGMtmhraYSPgbrbvL6zQTM6Qm2snMJ4mwjI7D16fppKJdTM2v3CevJRwY+rxvX5Q0GQ9rOjSs4Q+km8CDSdz06fSv6N49ObQbTfYZOZIDGUbw8EUPtV+f2T8LQvC4hhra5e46cPYAY0r/kHDIB07fp/PsEjGvTuX7Qp5viWt/fDsakj/ZbJ2YtDdK17+Od7/30/qVpjq6e6C4PIc32lRub+BZIp23svnVGDK0X8f96S8Cgzp+W4duE5pdB3grpe5bhKmL8MmCMxZCee2QRiryWN3yv455vP2zaHI9sY1hEXB3/wGL8C0eqT0IctcexdUQMvZhzZXR1xmB8oy/7hn0fYnzrH0xL61YIjuSI+n6KoTk6bb9A2j5nZZlHScJvvu5veIHEl75J/xmc1TL3lMJcMOEYHCANg4i6bfTSaZ/ev6O6jhgMNOrMfZRm2FHH9Tekr2jlM35/9v7uO8Slct9aH2i+Q/SPpfUmzp4bw+ugprVxsiHAFdAh0WUnhtasR9eJu+c7oK8MoaKgPHtBG4jbyXvllg19s23GzRUgIm3h1g5tdbgMqWBd1G0MDarjpnfitva7aVMsy+7hjgZV7RJ02md0O0NfO07eor/p9va7SRN51u+gaUDQhXT6j93J+W6YMPbunZHm9T/GmkXM5D6Weo/TxOGAPju7gWX9hft95YUQb8sp6xFNaz3hQCciz/Zd8XuTmFv32bshrUsQ03urpTWdjvZ6T+y9UU2zSGr/z4unnnx6kUOkzYifWsxEFgWL5skS0eV8qPH/o+tgXg8/+Qy23TMGhA5N4mNmpztMWzYEOPPi6yiGJOTafV18ND0biCzn+gmeX4OpGfeu6oO0Dli/MwNCg2wpHTIDOi27O3dcpHRMwF1npsJe/IY6VpzfwAN2nOtsfT7Q5HkaXji2XjswFtjApWUb7psYNu3S0K06+omf2rkr+ImH3Ewc/vEOhHB14vA/mPXODGkcZXnGguppEKf1VPYU3fjzcMvY85H7bEb6LCmCqq5z5nJ4dlCM9XzHSqFkEefMGJrzeGKW1s9LQNucizAs4+KG27wbQ9fc9BSLec55Eiqm4w6PJxflBPrmZsR+sAzzuK6DkNnQtvTcfD2gPtM=
*/