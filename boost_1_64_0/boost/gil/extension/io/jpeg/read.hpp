//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_READ_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_READ_HPP

#define BOOST_GIL_EXTENSION_IO_JPEG_READ_ENABLED // TODO: Document, explain, review

#include <boost/gil/extension/io/jpeg/tags.hpp>
#include <boost/gil/extension/io/jpeg/detail/read.hpp>
#include <boost/gil/extension/io/jpeg/detail/scanline_read.hpp>
#include <boost/gil/extension/io/jpeg/detail/supported_types.hpp>

#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/make_backend.hpp>
#include <boost/gil/io/make_dynamic_image_reader.hpp>
#include <boost/gil/io/make_reader.hpp>
#include <boost/gil/io/make_scanline_reader.hpp>
#include <boost/gil/io/read_and_convert_image.hpp>
#include <boost/gil/io/read_and_convert_view.hpp>
#include <boost/gil/io/read_image.hpp>
#include <boost/gil/io/read_image_info.hpp>
#include <boost/gil/io/read_view.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>

#endif

/* read.hpp
E/hZhtP7DtdVpa2mADjN0z81dr3Bed9Y7/L6acr7pgDcjFrHfJZwPxeAC3o+3C8Q7s2E6+2L3FDv3oHQdzo+Y9qlC8dtkWKf/nnAQ465Z+W/W3IL4GGCUwI+S7hVjjn2HvfGxa501kcGOnvbvQYZGAPZTeADsauvFaYQ6MV7s1Hj2sPSKhkLeuO8uZRNnCC5oXDJt3829EeiPb0DXW08eEoI3wMima/02RcPZnKFbNKT95esjGwfnsaQQGO4evOK7Fq/XF/O2TPdFeF7PziNi6d4zP2KpTHEvgfvrPf5Mezt7mo7+sgNrd3GbaRXtjHQkj7IWegd1o+6R0CBZb/7VTV3ulvqL+D3kP5+rX7Cd+pcNmM9ve1cKwou6ubeYr7mN8/lvqH4+Sbxc1+9y8/9xM+3RN97R/04tpEvQ++tfW+931dnXs0Pe0PCLh2uOeVcJ+TkCvaylxth4d8x7ZThUG/gez4d5gmfDg+4e6BbrDGj8HHRDJj1b0Fj7INCb5Y72xdb95BYpdqCFYNkO6blwrrdA731xMEAqR/fH3dvItLe1RfP5ndJMgpG8vyBR6fEfbqH6n08iTtf2eHB5S0tBui/8zXU02+Bsr3uXNLcTKpO8Btc3GTWvgu1i2n/0OaXGEoyr6gneZfNPOIZTeRgkziY6LJTP0z0s/K+XJ+XU7GtZxNbk2Y2nRjqapf0kuxnj/kZ9cXHl4JfQYf7C90P7Y9+6Edl9kMHlLiz9jD1Qd47XD/29UFrI3D+39rtGn9TnSoYaE9wF8TfZVkaJeJIP35C+vEmf9+Zhi+BXckh8jdo+Tbdqa0Ley/Xu3P3s4B+dGwfKvpPmQ+14/a08TLbZ/M0tL34Wq/dSgTUj9eH/yIg79h6eJfBhQGRv4CO04ez/Ps3rBmIRrgKFFi20cdUn/lL1Yc/Tn3mr8Zty1iE4c0/vOtXKF6VUjCyq/6N6K9/K+btT6j50O/q8al5+5PEy+/rx7Hvpv5M3rr3Qbw3OFW5n1Ll/hPl9efx93k39UQGYl08Kogw5fOMyudZlc9fKJ/niniGN5bR34SMnlcy+ns9PiWjfxC9Fwh3vm/+sjs9KvqqWjt3wb4p6eI/pS5OULaWEvs0dr7mJaGg1LeXAvnifQIsUGwfZpLxWVlFw3/WZ1Xa9AXus6Y0iHKC566h3qzim0Hj+m8ss78zdVrdUKzTmoZinU5t8NdpbYP7yTrdp4HuhDRM6Es9U8hm0jkuiIIRL9MEL/s2+Nee+yGcmD52P35/4iFE+Kf7ZE1ZyL0l9e5lrZj/TAeNEL176aX0xvUwvY3khefR/gC/lw6dzZLPqRU0n6kT9dlcphyC9VctC4tB1t+ZDdxO8VvcESE43wmhOqw3vAEeJvnNbhjnXs8k+n9Da47gZY7gZa7i5QDipYl4eQ3xMo/w3iTbopV/a869Zij7iow32eF2NF+2ozLnc4G6W2YbNDwfJMp8kCjzAlXm11GZD6YyL6Qyv16kf0z0s4eq9G+g9L+ktcMbKf2bFB7o+/rzZsJbJPJ5RuSzWLT9JartL23Ap9r+MqJ3WMOE468afgVInvMp/lco/t9K+R1OeBOsFVWlKbjoc1aKulolZLBayaC1AZ+SwRriqY1wO8afP8oO2HIVGEN8RQRfHYKvtYqvzgbzqTM74mtdQ9CYti3p21N3fTDzWNst204Z4+a7Q8JPlHgTsgd0tC+mKWSv1ou4YFm1trVhUzLWHulvi3b12WcgKeuAGO5vjhQ6faSQW7/SqQGSU5Ta3gaS00bGq8Q8kH7TPFCmP5rSb6L0x1D6t1N6nhdJH2oNXH62qz6W0sVEusWK1zjl9Sy18y2UZrCYBjpS1rsexWs=
*/