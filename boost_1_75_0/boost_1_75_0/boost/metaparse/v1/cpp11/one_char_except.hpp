#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Cs>
      struct one_char_except :
        accept_when<
          one_char,
          impl::is_none_c<Cs::type::value...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except.hpp
erQg9U45ZnovMCugIeGQd7Ktnx7bdGaXHlQavK9YWVjN0maRltJVGzLAf14KGphAsmlc3JUKiCPVllNSZaRh7CFkZrkb96wpNHPIQAcdbWR5WlmkTl8JDZcpyBRtAB4g0GmzaFsHkNcFrNDHlA/nLk58y/pqKyZTk9tWczQs5ofq5FGVat/AteV80SouVmiHnzuGJbBJU/8EqViihnJcBM+AAHElxfddhnIyJhIQGcBXUIeY611cqDEuFIgLjxoX8sSF5caFrDasdag0jbZY9JETLZY0S7gIR1Hpk1Y1kXmNdPMkg3P6townO2yW/F1rLP1R274a6T7qx3XX7DutRhp7+v3t7UBrxgNoxyLnBjcqfRjI4ArfnGLhQmmXZliMl3PMl+nOzZhXUGFrDuBUeDi8N5veY9W5tjcj/kCiJv5qNGkboy0hpSSqKBHT0CUPbWEKKxC4nqDQZrG1nqqjwyTROVK1nw+rHdmse/UHUDiPzTK1PVf+v+tj51LRx++KYy7vGqdHKKAok/Jl/7Cx4my5mFw/3bUCyYOBEQlO+3CrTtxKclTvC3hJ16/ldakwvfIqEhIdlZpXSw1fvRSgzglw7YctC8zWOT3+aqHJ2H+IOc0OlkRwP5HvWvecUnT+PW3u/DxRcnCDHDnFgmxCIFKG3FYnJilUDmkPoB87ukOUG8c5c429qgwniiIRNyecKACcG5AeqS73xBRK
*/