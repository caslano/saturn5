// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ALGORITHM_SUM_HPP
#define BOOST_HISTOGRAM_ALGORITHM_SUM_HPP

#include <boost/histogram/accumulators/sum.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/indexed.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace algorithm {

/** Compute the sum over all histogram cells (underflow/overflow included by default).

  The implementation favors accuracy and protection against overflow over speed. If the
  value type of the histogram is an integral or floating point type,
  accumulators::sum<double> is used to compute the sum, else the original value type is
  used. Compilation fails, if the value type does not support operator+=. The return type
  is double if the value type of the histogram is integral or floating point, and the
  original value type otherwise.

  If you need a different trade-off, you can write your own loop or use `std::accumulate`:
  ```
  // iterate over all bins
  auto sum_all = std::accumulate(hist.begin(), hist.end(), 0.0);

  // skip underflow/overflow bins
  double sum = 0;
  for (auto&& x : indexed(hist))
    sum += *x; // dereference accessor

  // or:
  // auto ind = boost::histogram::indexed(hist);
  // auto sum = std::accumulate(ind.begin(), ind.end(), 0.0);
  ```

  @returns accumulator type or double

  @param hist Const reference to the histogram.
  @param cov  Iterate over all or only inner bins (optional, default: all).
*/
template <class A, class S>
auto sum(const histogram<A, S>& hist, const coverage cov = coverage::all) {
  using T = typename histogram<A, S>::value_type;
  using sum_type = mp11::mp_if<std::is_arithmetic<T>, accumulators::sum<double>, T>;
  sum_type sum;
  if (cov == coverage::all)
    for (auto&& x : hist) sum += x;
  else
    // sum += x also works if sum_type::operator+=(const sum_type&) exists
    for (auto&& x : indexed(hist)) sum += *x;
  using R = mp11::mp_if<std::is_arithmetic<T>, double, T>;
  return static_cast<R>(sum);
}

} // namespace algorithm
} // namespace histogram
} // namespace boost

#endif

/* sum.hpp
Bf9KACmhtjoP6JrkA+tthAPDNluqKKD8XF3wuxkJ3fzPrdAvo/jo84SExgDI/B8SOiqPB5mqXT1RS7qTcSFtQeZPo1DVU/ZoGIy7pyPzdJ8UQ80TdnXPYbtbOHqo3n320TH3aNJZa4Cv+sUYeDYbDJDwjyjV7/moj4e7ca09cuezwWw2mWnvaqCq47zPN93B9jin6ajy8o7Ltr9PftsF9+jYPqsEsffmINM+bjw7aOlht00P1DqH84Mtj+kHO2DOXo/ZjO42WZIO3pIV0MGrxrO3IlhJ0yxHaLIWmqzpscf6TchB67B9rGuAp62SdFSRpD4FmlOBKaRI1I8GO026XKE5g1LV0RsmqdlD9gvm8DXqV65+iDuWlaLj5hYGAtwrwIFlIER7Qq9Z6Ji9O+GZoW1ONWJRDbtP26vb2Zo+qimool41OPOqgyfPw2OwbgA1gZ+F9JhjHcKasGSaK+dHO2w3ngXfZPonEvJZiqmEliKx05h4aEx9DCSvCX15rwONBnDXmw2mo26Pzz/8dsgS1FRvr1r2j1ftK97+t1fJwUNKXDlXh5ra3AcspXS9KN8e7PxaNmvt4CnpHXRiBbuE5bdt1+cFFt75re1/S/oBxli29mvZLI8tSAR+JaXfiJm3QM21j9M+Dpy19wWm
*/