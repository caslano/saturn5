#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class A, class B>
        struct concat;

        template <char... As, char... Bs>
        struct concat<string<As...>, string<Bs...>> : string<As..., Bs...> {};
      }
    }
  }
}

#endif


/* concat.hpp
Wi5WKfcP4RmFC0Ldg3mtD5L2Yr+iqYoO+p2ThUPTC+tXBkpp4Q1RQWBL7QImdn0uQTRGO53pOmF+8qHRYUNH7F5bF8M/fEbshbQLrzfUnLasNTUfv96u1g+L5xG7zjJsyH3KT0dsRCSPLYTfLujXKyCF+GHHaPTDFvkMmkfwL4b8+Ef+BVBLAwQKAAAACAAtZ0pS7q34biACAACcAwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMTJVVAUAAbZIJGBtU+9v2jAQ/W6J/+FExZeKLISySQ0mUgWo0HUFQdp9nNLkIBbBjmwHxn+/c8IPadsXx3c+v7v3/MItGpsmBiPGhdwo+uzwdFQ6MxGbxfGyXuB5GjPvhXH/dsj9pp7dMa6xLE6UyhKbgFRpjulu1D6haTcgfvAlgH6vB4vvbJJYDCGusAu9R3hTBzoIehAMwsFjSCXPP2K2Rn1AHYIbzjN14G+SHbKxkhal9V5Rbm0ewjeXkZhaoWQIaaHMrSY+leggfls/t/vimp8IUyojmitCFkLiEDaiQJnscdR2a/AQ9IdHFDprMxb0HwZfia4j52ifyRLvOxgXwkEakSHjaR1ElLa5MKCRYgNKUoiQ4We1hQ0mttIIVkFSFOoIlXF7gxYy
*/