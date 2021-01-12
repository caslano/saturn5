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
SBM5Ypp4UqwRu0TK7vzvdxqxo8gQ40V5dZ/6rPdxRQfTE206/mvP6s29tnWimCWWBNdbtq+l7GKcmCuCayRd22haor8YJ6aK1WK7yL32sJ5Ivj6z1VmmW+e3r8+MX5u5TETXY8qdFb8m81evxwyuxUy+BvO3r7/c22svf37d5e+75rLwesvCV+Gr8FX4KnwVvgpfha/CV+Gr8FX4KnwVvv6/X//Z5/9npPf5Nz3/v0HSs/Wf
*/