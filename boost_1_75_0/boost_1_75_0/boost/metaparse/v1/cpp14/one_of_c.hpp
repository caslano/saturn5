#ifndef BOOST_METAPARSE_V1_CPP14_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/cpp14/impl/any_of_c.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_of_c :
        accept_when<
          one_char,
          impl::any_of_c<Cs...>,
          error::none_of_the_expected_cases_found
        >
      {};
    }
  }
}

#endif


/* one_of_c.hpp
78XBhM5jr/7EOxG+k5l47etDJPTXDbGZML3sqAGRvgzT8MnIp6CwdxkKe1u18h+NJ9rI2gvboeaiuzizrVBy1UxIs4SPEH9Vtw8WiSg/qT6bRTe3mkuXn2L0TT4wypMIfuD1RvacQoMK58BB6hGYdFT5eykMvq7dJ/kOU0ZcpfnNVMK+ohrdVXpSglZlWorQqlyZIrQqF6cIrcp4cwja5SY2/9lqXkzvMC7eY0WY3BUu6jHR8HifCIGOT7JewHJ+byxHWRuIt/hDp4n/iHLHUkL9ATOGCNyTav9k5dwpctuL0Ia4HLoYuCBtTCeuWWiSrJ7fQZtmME9W6U+T3YS2PdjRE5C8uA8u2INo/LqsXl7DMPzmCIb4IQSfwtZ249QO5lN2o/5YTts1XbJaDDIH61ZCu7GOToD9Uu1NmBShXarDKjqegvN/eMBmCbtlNeP8H1BrsmQAaxiHwo7OJ/cYEOzuxotR+1vwKJZcsr/6ACatew3+Wun30w+Qs0ANzRfd6DChLEeP6DticNi/0o+t6iu6yE3/aVoNHHBvGvDj/ZgXUJcLfmixSmzA890ZO3i3nN7FXfgO7MLYQMxjz5eMRIDP6a4ANBh76i1SVD0KT5xLTzDQ6pVtbXfC3FmntKXTVDo10FdSOv27k/xdUWnMmgtkzLRhW41T5tBEk1H0OC3CMcWvdHCWLKVTq29j7KiahQdZnhw9p6Yaln9K
*/