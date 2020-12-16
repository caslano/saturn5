#ifndef BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_C_HPP
#define BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <int N>
        struct int_to_digit_c;

        template <> struct int_to_digit_c<0> : boost::mpl::char_<'0'> {};
        template <> struct int_to_digit_c<1> : boost::mpl::char_<'1'> {};
        template <> struct int_to_digit_c<2> : boost::mpl::char_<'2'> {};
        template <> struct int_to_digit_c<3> : boost::mpl::char_<'3'> {};
        template <> struct int_to_digit_c<4> : boost::mpl::char_<'4'> {};
        template <> struct int_to_digit_c<5> : boost::mpl::char_<'5'> {};
        template <> struct int_to_digit_c<6> : boost::mpl::char_<'6'> {};
        template <> struct int_to_digit_c<7> : boost::mpl::char_<'7'> {};
        template <> struct int_to_digit_c<8> : boost::mpl::char_<'8'> {};
        template <> struct int_to_digit_c<9> : boost::mpl::char_<'9'> {};
      }
    }
  }
}

#endif


/* int_to_digit_c.hpp
VGOsEImjtP/plMwvfjapSF/kl746wG+flP9UxG1iQHiNppsSisp/7wTwttZ8aQa48gA6X73BfT4cULk/Sud4Iftgg97r/Wbz5/lyfoD2Z2317x20H8iY/SqZ5+qQu2ip/bk3dV3z05PdGwOmx6JM+3g6x1HbzahW2l90wrbWq5zfvEBcFyvnTNmnTQFN+sFg9U6whvq6H9UBzPsg/1UvfS8puvY2em82VPcjF31PoknTU2/Aw0Oou34c3T5nheyDp5QVu2kMvzPQvVZof5qr4vGjSXXX/bzLK8UrJoF9ux2m57RM1y0EGCe7ML55dT+6Trs+it1t6czQPn0pe9ePNuImwznpA6l28rI7aNUeSDdCvlFkZ+dS//lA0iiKhu6vptroWL2PleEVVEvflwXpPB8I8VzJcnET4Exx6Ca1ANFdiC5RgNS1sp8V/ml+k9aKDKGs5zG4lFomf44+YJrzXN9Pz9X3tXMpC9Y7lDLa+UdK30enNf9i9X2tN4i1Ranxtg3ZGX6Kb+XT9xA6Tpa4k13YAM3bvKPuUh1o1XSpmaiAb2091+6s7aGQDOZ8V2EadQJE+3TApXSyL3ZomzPS+zAvymIvkspOIbXque4LOgMSikOSog/iX79UvNtX95mN+n7VH4ESFQgvrJ1hdhnFywbA4OQ1fV9xHvalarnrPT9cLpeUPbkNumqr4ZzxUveF2tR9NhJxe42Xv05nVIkdkOxpTZMrPoK9dUbvS7SjOw2lyfNX5Y9IIzVhneLxv/bnPuJnCriorzit5GdwdZa9qxob15lJPvkj5BvpKrpGZrr/DoSVbYAx+najLOdCK70HQYURK8gWzEfWXvtfUmHAPA13lqO+D3im702vUOY/h2yeSvLnyM4x1sM7PyEsFJ+eMEb+Id129nsC5obrPijPzrccGl+9c9uWrO/P9Y3242j5E/dR9mKO7Mkjsg8UePhxkJSHwnYV0kmVHkjjlpLvofxwcfpuu3Mx7c8ayzeWv+KrtHFVRtb2SWAXq40n+UCU1yFcSndsj6aKT+s+feGR1ltNEB9yIdURSX+jlO4fl7XfFwac7anvSRIVD3gGuNUdcDJD/vbW9oyHiNe3oMk5cul56Wbj6UB2rq3ec9XQ+93fYO9aU/33DlX7BeaQ/17vO8fr/CgE+FxE+6k4B4R7Kt6o/SC34oMCnZbpPaZSY+4ZIZ8OvkIfKBv4BbrnpxWv0HH8NlrfS4bTfwtki9531HuflvCzqKL4oI7ZO/qmcEOczkvZNPZLaTeXVCjUUvrKDE3sAxhaDwb+IYqn6LISUxXO8ZVJBSzXe0JzxWdya3/ZQNmICPljH5Fq2UbfO3uSvaKNYrm34qHqq8LrdD+yotoMWdzXToJwagw4ryhZUZndE0ap/2QEemosJ6ragLPwy3WeedouS/3nA+i3mux8WTJ11ur76Z7yR+gHHiJ76/3GCRfWh2ZsvSv26DtS71Um631dd8XjM2Rf3UW+NbMg9pU3tN9Q+E0OpSy/+uXgU71X9tL7bHkmbAN1n37PEvJpKH+xJEiQlz1FA7osQt/PnESMQrX0Xk9fx5VQvPaqZvt2d8AtOcnNuwLq3nRCX0dAY41MPW0PPyfKXxcJqB8C07vHHLU+3OHnoHhZiiX7n+ZQZT3XXhEJWKxHNTEzAOUDjRlfWRkWWsQ54/Xewk338+tgJ/70kL1hgb568j/vNWVGsPpTPHn+VTrnXguyiysBPmeQ3XEZqfw0jAubodsqe8UDvin+2w3pP0Rov5dGufTJ+xqdZWnb9R7ElbK1s/Te5yKcD/p5wC9S3/dIy3CJti9M8d89IGrNkz2kbW7wb/JHzCX7hyhS8/SDAq2ULTE=
*/