#ifndef BOOST_METAPARSE_V1_DIGIT_VAL_HPP
#define BOOST_METAPARSE_V1_DIGIT_VAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/metaparse/v1/util/digit_to_int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef transform<digit, util::digit_to_int<> > digit_val;
    }
  }
}

#endif


/* digit_val.hpp
TQvlewXfU/jreHF+0iGR4Cxl/KEDPkQZfxiNV+Hl1ve9BN/NcZm/51J8V8dl/p5c1wjXShn/OjQS/M15vmX+iWb4Asdl/0FzfJ6yvkoLfK6yvkoejzvPj8x/9BHeVnm+YvGIur55B1xb3zyF99PiW/GEFt+Kq+XH1fJ3o/9Gyb/TAb9WONe/+Px1wsc4Luen1OA1wuPDnPxAnuOv8Bz/Jc/xv/Acv647z2cj+36U84+vwxn/YP4t7szvbVE4/kR8T+EPb6IMZv4s3kL4DtzEX92BN3Zczu+tPZz6rxafiOdLfD+amPsH3+q4XH/qRnyLkl97Mr7ecZl//Bb8NSW/duaISPBBid+32rw/8Xr+OcA66wPY+UXL8WXCf8TN8/0M/pTwAZuc++tI3s9a/bAn/fva+j54L+X5qcVHOP1ncn3TofgZYv0Nd33TYfhgx+X6pmfjpzou1ze9E/89sC7XN4324v4NlV+/qhm+F15u/apWeAvhy3FTvtZ4M8dl/+ihuDv/T/aPpo7Wx6/SuBof59k+69m+3rN9zrN93rN9A66N3wW99e2juBof4vG48XLtW8/2tXhzxZP411r+VvxL5fm5Bd+gxH9m+kSCLlr7H68IlV9/ZRseOC7Hvz7Gf1L6N+OJSHCvlt8Vv0c5v3vxzsr5NXj2v92z/yHH6PvP4n2V/S/Be2vtv36Mn2jvR3yU1v7AZ2njt/j92vgtfo8WP3GsqZ+Wnn82HN/Vcbm+5nl4Y8fl+poX4r8H1uX6mnPw1cKvwYvjF8dFgj9o1x/voV3//tQPteuPJ5Tt6/AXlPlpw/HnlPlp7+D9tOt/PN9HbXwT76nUX7N4TOvfwm9U6ofb8JTr8vnGr9PyK59A/VHrH8Ev1+rPAyLBNK3+j6e1+Y/4wlD57bfht4WU9d9O8rw/8Ju0+Qc1nu+jx3O4Gj/p2b5Bdxr7uNZ/javfR8/2cc/2CXw/5fuTxLXxuTQ+UBkfn4qf5Lisf03DByjrK83A+ynj4w34Ptr43B8Z364oP3+mA14rnPdn8f3cET9Z+BrcXI3r8O9F/8DWGlu+ifg3wvsOdOqvtRGR30+M7+MblfxjPfGHhP85ast3FP6g8PfjtnzxQZFgptJ/2Q2/T+m/7I7P0OaXnxIJRoeU9enxix2X8QG34vnAuowPeAx/0nEZH/A4/oSWH/RU6k9afCv+W6DEt+Kbg/L9Sz/iG4W/PtKJ7xgcCY5x7y/ZfsH7Oi6/763wniXuz2L7BT/Ccfl9vxTfGrIuv+8NZ0SCHRxKxr/uWShf4yGR4EP+pdrx29bb63MhPlH4WtxcnwV4P+FtN9jydT+T90doZ5+AF/tXz9G/r3UeT+OLA/l+w8z7C1/kuFzfbBr+d8fl+mZ34Q84LvsX7sYXKvEryXP1708KV+df4dr3IePZPus5fr3Hc57j53G1famXjx9Y9yiuxZ/U4lco9YtB+BilfnEZHlPqX3n8ca3/Ev+Hsv/64WL8SPR/rcCfclz2f63E3fej7P9ahT8RlF9/fQ3+iPL+zJ7niQ/BO2j1I3xfLT70fL4PTv+lzN9zKH46fqTjS1+z/U9xvEb4D7h5P3bD+wk/IeeMb+HLKnb2RXjx+byQ+ovz/ZL9qxPxP5SIL9/b9I/jh5SIL29v1ufFOwpfhlcX/pqNB1p+oYvpv1Tuvz3xtVr9f1QkGKvFL+Cdtd8XTzm/n/x+dBsdCQ7DD3O8Zp2zPiX+WcXOfhtujjYa/0T427i5GhvxCcL7/Mvpf76c/j+t/8fjafxL5fo8hq91TNZvHsdfdEzOz34CX+WiXD8/6Ym/wo9UPDaG+F3FU/iWxvb+lv3b9+BP4gnHW79q6ycz8Cc=
*/