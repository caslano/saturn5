#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>
#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/fail_at_first_char_expected.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete :
        foldr_start_with_parser<
          P,
          first_of<return_<State>, fail_at_first_char_expected<P> >,
          BackwardOp
        >
      {};
    }
  }
}

#endif


/* foldr_reject_incomplete.hpp
0k2OIrY/Kumymo8FX+aeVwGs4qmYkEuMxY9iV5i2L6r7jKeJngzCcewNffhML4uUMvb40PJuBC85m8pCJGt3ToT5Zg0nMI8NlGbPjugspPAkLPtGxVJNNftuxo9EGNAlJgvfUONahbgmtKV+kfSBteEjtRZHCvlrp0jJXznaBIJBperOr1fYCRNkraBnwtPA3EMO5Y7sVmXjmxZMtVGYFhbBeGivqSYxP5uoPfMtFhDbwEvfbeAl7kRV23vQbL8Ie+Io+tgum1uK30LB9u4I6gzXbvDlZP6Bq54I8g8WH7LRbfgBxoEcxtc4Z+KvENdKzddkqoshyBjJgeZSypyqiJYmrrALMgOBm2re2aWmfMS4DKQWnNbZrX5qKq+3ewUinhpvYJddG84ywxu9Z7zCq9bAdXHlbys4lAubt/7LTfNG5Z8dBh3I7leYu19hvVZpvlZpvVZtvlZtuhZqKBNdtSIrNS83rzjjGltyu0TDjYAo9oky+Qm4hAV9GHcuibdLmYcknjs3y9YRDs4yQXycJ4CdE6ps8NnNCieueNvpiEsRzudXMdd0kRiY9r61F37TdDz/Eu/V/39adBRNPKHrJnps9LHf+dMaJ58UtonsPrRflibSPrq6P/1e2R/LsbxEh+f52af48Uk6/QQd8unwEB2m02ESv/XO/ob8DOF2cWLz6MgU9dtL5ObtZfW6M37DLjRNEUXRsEAi1rHW
*/