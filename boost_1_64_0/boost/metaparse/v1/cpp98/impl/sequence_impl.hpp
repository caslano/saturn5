#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/apply_parser.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/deque.hpp>
#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ps, class S, class Pos>
        struct sequence_impl :
          boost::mpl::fold<
            Ps,
            accept<boost::mpl::deque<>, S, Pos>,
            apply_parser
          >
        {};
      }
    }
  }
}

#endif


/* sequence_impl.hpp
HiCBGfkeDE18Ozk5MabRvEr1B/8FfRjCrjhRQb3h7eg3zb3V7BeDNzaDgPTkbHY7YCY3pdmO5TuGfxZ1gJ9BvaTO36kO7EHUQfuebgDfpfhbgdPXYBy/CZ8V4K+msjlUtsyUpZdJfSg3ovhjrlXtrXlrEp76O3f27OjcZYaYbd3FCZxv+/FhynARjcizwoKADumtTdF+ut15C4hw+Vs3hi0DLP6exs+psJLbiLcY/FFOdOfqgAeA7TGF7+TXiDVF9+JOPCrg3p1w1FA9/ThUt6tn3xvV9XUOtbs1Wx0qYgyLwo91vzWkG3dEQYSOn7QzqId9X8bbSLgBC1hP3FfrxgBCi7+PAYZEZudloZWtvSrzk+/y5gaUUzyiTd21OrIqaLL6vCqrPXKOmBESe80+l6dkS8OdenR/vZ/W1knAfS2tt34qO02UHULZrrsj3qwVZenHHvNK+0bqq+oaPMw80ydO4zmpN84HHIsSJOtZEG+R+gRzwj4PL77dzq7h8ngNxbDeeMxJMtKv/CDAELFhRJqsqSLKYBN5ywonG8FfTvAHtZDUHdHqemftCxnnLHZPMr9lCUezUo9UBcySZb1V09pmm49jDAQNOr9zjIGEoapv11zM40YBNrnJiVEoR5FL/uEBTvUs/y3kRyo4WEcGLRnTvJSx91b6o7m+bIHz9jPco848PJ5x3J7I843Uv+VokiawS7w1OZ5+zYxjM1fWzG9VHfB0tGfqMi+s45+X8EmfkgAq5f18hu/r7Mp2dw50BnF3LwhxHN/KS2O9Cq28p3tnJrsbaIK/VwLOtqX7VvOLXN5HKvUJw6I51CXj/SrgGJLSZo9hr4lhdESXdyGvJZifU+CKuNweNxJab5DtGCGkH7cjJe17UJgEmg32FrSHQ2e9iP0VqiwpvzIpN7Oby98my6X/P9jrea+W591VOh42HJxnxXi9I95jjW7MmFOIyIPPNOLtpG7GCm1MZ3eAYWt7xHgbVbyO4O2Hd7nvfNeB08Iw+T64hSW++wZ9Net4BvYLWtf25FMWaHvY1dw26kXz2pjEyrmZLoL5+83AnjbGuTGo054x0LY5VSpz8R7qXLyGeXbyKL2Xy82KSGvLmDmi8DBPldv7uS1joAVn62sBd/1frg/3ugDuxphez7aj8Ou1TOOr08fnQ2ukb5CUi+DzIw48UjLQTM3fT1vZof+qr7htgXZftLDRmcOuKP5ukPHgMIF8cHNSGIuu0qK5JveGT7q4EEVuLFqGQld8mvU3cMw65/H4/WqfJ3c8PpfYX6YqKE/WcyNFziu+tGGfTIt8Yor7NrcRPqk4qVe+JOwZP6fYu5kO1hD7IL7iyINUifzeDvDIkQopWOUrvnkDzLk/MnBz793X2y3nznc0PCHvjzk82MGNYV8M+Utgn3VhTtz3cxwbwWy/bC99T7MdvTug76s44f36DwgvnBIzWBtVTbedpeqVSxV9jKmeVpdhJDRddi+vTd2PYhp03gh0ztZ0wcxTIjVvdfWdlfsu+Cf8SeBJo3n/BZoN+kuWMQa137EPf+HC2L4MfUGdhwZ2m4kROSAZ7q9rgJvMH4Io5MHq0SPD46ou3an25U5ro7uPA+ftyY7iUr1YE7rhRIYNVQoXJbEMJ9vyIRytE9y7J2XmMoPLT0W5fdm66OR6OMl+14fSUjkDSEz7NOB3ezkTZjGNgvm4V8rzDvZbC+vJGMaLu5Wac0Z66BwBxy5jbz44PmuBbY+Mw4eNSB23SMIwcyXsLytB14PN9eLsEV7v8HI713F5DWjqvN4V/EDAMkV3UveL9DY/nMXRJ41DOMxJfpeiLqUKwhSxOjGW+ZmAGT2M+PBkHi6nsm5r+MYnDtc=
*/