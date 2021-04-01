#ifndef BOOST_METAPARSE_V1_ITERATE_HPP
#define BOOST_METAPARSE_V1_ITERATE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/iterate_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class N>
      struct iterate : iterate_c<P, N::type::value> {};
    }
  }
}

#endif


/* iterate.hpp
G5JZbh8F1kcQlieiLudF9bLansv4punxuktCPP5n7zXQggRyINcxTeB7SnsiaZc6nkYhjyJ/2qAGz42Z0oN7cj4LUyRefUCUn3rT7MNSzTBkSfW+RCGGH9uUlwWWfHWPsNlmsBfrkflJN5cqx1EEq+SUJOWD3KARgNDFcKLZOMI1PSdpD8a77FACBcLJMrDJ2d0wSQwK1dwdP7dixcRiLNM8/oU45IcmhdHh3nmpCPeaurOEvzQBU13OLWvyZzRQUjCsRzZ5jrzNbITQXA8LYZoliwzHah8e+4dLnEmqxFO1Cx4BgERKED3SqzRVW4YmA9XCiVZcB0qyJoXGqQcBgx606zP8aYatuVjQbnddpC0AxEkXBe8ZCGdiwHTDfHYcKDksJPii87NUMUw8Xg05GxnF5OckASRHaICjSN25kTa5VY/nIKgH4OCuraWtpfn4h+nsfIOhe1Vrvv3SRcaDneAuHw0mAe6N/4HKzXZptIKgadutVxOIZ3OlP+JvUUj+4d/9e8kjRtspAVif9ssuCRhKDChX1M0aIVnqSVkxdhjsRaiDPpdT+P61QA==
*/