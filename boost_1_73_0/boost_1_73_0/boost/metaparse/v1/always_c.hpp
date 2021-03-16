#ifndef BOOST_METAPARSE_V1_ALWAYS_C_HPP
#define BOOST_METAPARSE_V1_ALWAYS_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/always.hpp>
#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C, class Result>
      struct always_c : always<lit_c<C>, Result> {};
    }
  }
}

#endif


/* always_c.hpp
SQrH2ZLjbMlR9XCodaQlR1pyXFyTIyM5MpLjcioNRNajmaxbM5Vdz4b7Qm38Dt+cxIaGQ2sI5BTWtLO1a3fC/9o7eV34HH5tPntXur7ujTewlq6xXLqytrX1qjpW5RD1DTao8Ll1c5n5o77tYw7R4PtrFvvRkGHOJZq9phimvrWmnmhaPDRyUnJoJHW9BsEQ0qBB2pgT6hwIRoDFGmRQcLoQnHGO0CCYUa2UEPWNKBhp5tbRO3Sg9KHTT72L60w=
*/