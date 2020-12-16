#ifndef BOOST_METAPARSE_V1_ITERATE_C_HPP
#define BOOST_METAPARSE_V1_ITERATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl.hpp>

#include <boost/mpl/deque.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, int N>
      struct iterate_c : impl::iterate_impl<N, P, boost::mpl::deque<> > {};
    }
  }
}

#endif


/* iterate_c.hpp
Hrr4t3UCx9hbktv+po6jujDYvzA+ay+VSENG07gW7OT5wFd4Duc4jNMxXM/7uSx/ZYTpDr8kAp545i/oJz6XMPZjPl57RDl3G/bbA3WM1sVoF6G/Cw6Ff8Hxx8XwGM+b0J5t84H3F/hgfM5g8YuoE/5FMfUZYnivv05OhyDH3S8PvDAnvt/X8jq/b+A4dfmJAhl5TuQe2mCsRyE/OPEbjJ9ihN8O+3HVqfA94XPOAa22d2W0ainmAuKOujaijm/AW0XIxzw1UCKvItfw2gTkGa6C3lgDn/AG8MeNhBwCPnvxOsTaP8Df/gl1gt+eg55b0R35mhbwYzAH41gH/Y4cows8fsdhKOuhPgF04RGsrgsHsN/7XgfMX9B18MnebWOUnysGQq5Q1z9+R+4G84Tr0O+qb6APIGvqGYl5ZnYCG/HbXGL6cF8p8Pq6wHaMx7zeKviPuvnLV8t4Pqo76BWCLwlf5JkfdXkYPv+5nc9f3P5ATC4WNE10nNUVsvc38M+R0AOPwvc8m89bcd9g7WWY64M85kDv56KcH+067Dzknz5MgGwgZKcQuW4FrLgDMIgnhy2FTkDepsdQzBEgL/Y6cvFPq03L3lsnIL/fPoa+3Ed//Bf40zNpnhrxSG/MufUVeAYc1zTOWi9ydkeI58tymh6LU5Cj+xd06iDAdOoGPhgKnziBvetUB7k4TSJ1Zwm8fZCnugs5mfebmDv+4lPMt0H+J8K36HAl9Go7zJ8BxyvAkQ37c3PHDHIVckbjfoaNRqzQF/x6MuTk+RtYHZe+izkYL59nw9z8ZVOb7vMJ8xB7Qf/L7TLIhxMhty/AZ9X5Gy2ehk5DLmj5Tt2cfAfuQ+wC73+QGPcE8IcDc2GeP+HvPw75uyC+zKXIW9Y9b7wnD4KNfVhcZxwizj/Zgtj5FsgZ6L4E8cyl/UCXV+GTgB8fgK+g2f63oU/eMuJ8diB8V+jYXPjycnViOtz/EPxNXawfnsL6dU7f+P6NLk6wTuExPgf3Qjzu78Hbg+HTajnc93SyehtJ+fjqHIZv3lc8zviY2y/4Mo5Ogr8Wvsp+8wLI+/0NNITOkiFDPyAHkIu+Vj0NHBj73K91PjXii41Xxfe16mLYGMyX38zjqDGLiOljGNaLuBDzX8vtbI83kIvE2oQnoJ/bwUbNjMC+cblopyBfsQt9aiv6cTzyTRGTeb9bPkJME5NLuH45nw/5kOFw74Ju1+VcF16aGNcWjN8W2N2jB8BHXmKsv91Y9tt6RDzcrkr4kLo42M3nbAaX6mLAEOzMH+L68erE/TsXurbbJ833+TmdrO/9BbKgW/twG9agCBWM3HBLzN3ehhz6JOQlukD3QidNW4wcPvKSF7XPILfMRg4Pebfa85Ej+gW2djd0CXiq4TOMw8EZZALWBWTDJ86DHe2qiz9a8HmM00B//XE55/3Yo/xC9B+8Z5Cx1gLfURfARz+e+4rwyeb7kKdqBTr1FjBxOd5+4F2Zy8Zo1A2/5oHzMbczhN27F/6/W5cjvfVy+HENOv3+K9elb0J+4UcfOgyxdACxVRX88Img2cXs+bGCpiK+Rb7cDTnqNRx6YQRskA/nf8H2IHZ6sQbtfxK8gn5cAbr9vAa8NQC+0jto4zL4FM54fCO36OaA7oTv8x38702wnyj/Wz3Pv8P+vMH9qJ3oW9sgxqWGXSvng2cxbmtWI7ci9GnccR/6eM8N4vrKjRjD1qI9777EZfh60DEHuhFzhVVYS3Ey5PFcyNk3I9GXo3F+JHzzjZivDMMmc11ZCJu1Yj3ikSSi++Z2Pr+mm6/brMvbPjo2HuZMnbxcXa+z3w2Q99rEFV6XBZ23D7rmDS7D2cjjn8vjfF0=
*/