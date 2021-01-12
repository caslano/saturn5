#ifndef BOOST_METAPARSE_V1_SPACE_HPP
#define BOOST_METAPARSE_V1_SPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/whitespace_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_whitespace.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_whitespace<>, error::whitespace_expected>
        space;
    }
  }
}

#endif



/* space.hpp
RuKzrtRh6VlhnkXt6vVO6gv1+PhwYp6fH+rIayfLPMk58mf58UV5npaekOdtSvF8cGq/pOdbScNZRcO2EX8jDy2oWHuKhq1R/LyRuM2i7XN1wThGefFb/x6XFmrpRs9OwvgxqoWPH5NXuI3CuLFp8XFrwrjUcdG4+PMaZ+70SWF+P/nUL1hOyJOorcuLY8dS2KbRvMbE57U+jCtYgaL+RGXgVPl/ncz46IR4nrwUlpuXl1VU
*/