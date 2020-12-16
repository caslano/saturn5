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
NvDJIOEuwSiDwPH7JKZAXrthcJkpHj6kn80HeNk3NpLrD+u0zZ8Gz4fSOhciTGMkr/ZqHQnDJLgaT7VFbmxu7fUZRsX6L/HDU+gLfuBMDQsE9zBdTkpe9GOeAowvHbF/zjD5neLtNJIdZ6CcoS2zh1dliG6myLVdbuxvTNWVT5a90oe5Jju99jLe70QbG6iNQkaoRwjy6RcYmvUthH2zbKWs0D2+J3L6DyKeTkiwROwRKiJf5a8aib7l4JuvwdGAnVe98gpHs2TDo1XKxwESiT1JAnviyyQeZbL4CpaCvKqd4w6jQ5eEjcqGwKKdzhVQugIcF3nXqL/HLoan2q7BsebmLrp0ZUFylHSlXng+BOT3BisUcGr/LGNVdW6key/RLeAAenePOP4aBC1TqdmnPOAJEEKWplXh8Bfs75DopV1yqp7yMrFniHG+H6T+HoDEkNjiWsWQfiblZToXzXcHwNv+3Oy/Ee98j73YmPQ3ic3KCeORoj7GRl3kKRdzpG2HtpeRxy5+1k9HHt9vywhrXv3YgMIPYagM/CwvFqq088lrWfe08bQ9NRuqVMp+YVLAsfaEgfibkZm/CtBpThd1J0Ae2C7+Fu4UC4uKkCZPgyfJT5cNOtheXraYOTQ4wvxcKMVN6aDq5e7wqnRayS5ayeJsQsSc/Cy4li/H9ps+tPR1R/Pk2hv7oKKZgwm0jZI1LV7n5oBdBlI54JSBzGACd+q8fYq/74L2gJvjp7BzfD2drkcc6tW+fZhhv0Z51qe0419b9BqgGwvNo3xYcIP+YcxsEftMkh4XxHewQqQo8RKVjh/iSXB6UB2TsNEMSxe2/qzchblk/ft1ZoNI1blFgBlTpRNi+KaMXnH2vz1jw4NSY8OzQa2iw+E+sel/S4krH5ffG12/8b7FTrs8D5JFDK3xnBNBnIkJR8uF1ybFGgCR9FqNuaxMaB52oj7BUT0ThxjKRlztFGSMZIImHknPmKn2Z7AfIjaVHhL1jlLFvdJdNJbscRMv2cDOcFNfZIdG3Z98st6En3jd+XnniXrFv5ihuzDFsHe+0DuOa1C/iaq5kodlJTAmCjeR/YFLY2Ht8vRALSR92Ym0Pva/L40YUuDRqrt3ouyDv+m7yH6i3umovp9/2HyFcIm7Tr5C79G9D2fjSRQ+9zpJhsatlsryydx8Npqn/VUfRylqIhBq6zOC0hbtd/Cx91v4v3uXupBzohzRqWJkT8P+5y53uXilB3MnK0/p7fh6luP+Q0/j/sPrTddh4XtLdNA13+bFIWoldh63ONAECQPebag7yUUBZhriJLe4biBribjE1dRR2PhVh5FZvDwEjakPBVNIAzH9fSpHlNJJUs4mOg9hBui47aBInkFKab6F8DxDNIOuGVLB507Up1Oav6BMLMDGVwKGMglD8TBtdolDacwBgCXz9feuln1ZzkA7c+6YAbTmDG6DGmvu6x3GuXLC3lWc72Xk47llQfRNOHqq6bNNYFY/QHN0HY1EjGsyTL5uAHJXt+jyBi88rZF2M7Yr/R//SHnNJV3ZHtAjfJhm9gLTQ50DqOkI0UQmpoSzfPErRfUYSSrpfJvmmtk0z/DtGMhVHNWX4gdfF6T9BAbdIbKGc4luNl2SsL6HuiTSwKqmHlSuJXZ1glzwCr2sXDztJCMOJwkD3HhjolT8tButOi+QU6+NbduMZVdv0pfdPSa57BSvqdmqFZE1dznxHLgl9pa+FDDSmyNFk5tqaP3ZPMIPMQG8YIpxWJoese+g0VCRR9wEkZNahTIG8vsY+WvOEvLvSY9C/pncv0y6X9X7nxJxGuRZ28NqbGGKjVUXGrWyGoAqFpee5aapjt0H9Nz/wfM66+s=
*/