#ifndef BOOST_METAPARSE_V1_FOLDR_HPP
#define BOOST_METAPARSE_V1_FOLDR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr : foldr_start_with_parser<P, return_<State>, BackwardOp> {};
    }
  }
}

#endif


/* foldr.hpp
lHKR1qcEtw/d2YMFH8TSpmjnlEgz2iuSMg/UtoQ1579zYpF0MpNsMfUJDSfrdSkz1hFbFku06lXJjlQsbqTtft43AtuGwSUH6nODs7+YF0ob4UwykZFJG1zyfbe7ODDdxCFX/UtWD8+f/B6onVGXP/cdR62PGOE56t2+c5T7IHl/bdMcf0NF0F+t4YD5gSJPCfPPD/prGwN1tRpOs39rgrReFVRCnap1VUF/MGQfQz9e7pw4TDWnbs7014rYGus=
*/