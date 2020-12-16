//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_LJUNG_BOX_HPP
#define BOOST_MATH_STATISTICS_LJUNG_BOX_HPP

#include <cmath>
#include <iterator>
#include <utility>
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>

namespace boost::math::statistics {

template<class RandomAccessIterator>
auto ljung_box(RandomAccessIterator begin, RandomAccessIterator end, int64_t lags = -1, int64_t fit_dof = 0) {
    using Real = typename std::iterator_traits<RandomAccessIterator>::value_type;
    int64_t n = std::distance(begin, end);
    if (lags >= n) {
      throw std::domain_error("Number of lags must be < number of elements in array.");
    }

    if (lags == -1) {
      // This is the same default as Mathematica; it seems sensible enough . . .
      lags = static_cast<int64_t>(std::ceil(std::log(Real(n))));
    }

    if (lags <= 0) {
      throw std::domain_error("Must have at least one lag.");
    }

    auto mu = boost::math::statistics::mean(begin, end);

    std::vector<Real> r(lags + 1, Real(0));
    for (size_t i = 0; i < r.size(); ++i) {
      for (auto it = begin + i; it != end; ++it) {
        Real ak = *(it) - mu;
        Real akml = *(it-i) - mu;
        r[i] += ak*akml;
      }
    }

    Real Q = 0;

    for (size_t k = 1; k < r.size(); ++k) {
      Q += r[k]*r[k]/(r[0]*r[0]*(n-k));
    }
    Q *= n*(n+2);

    typedef boost::math::policies::policy<
          boost::math::policies::promote_float<false>,
          boost::math::policies::promote_double<false> >
          no_promote_policy;

    auto chi = boost::math::chi_squared_distribution<Real, no_promote_policy>(Real(lags - fit_dof));

    Real pvalue = 1 - boost::math::cdf(chi, Q);
    return std::make_pair(Q, pvalue);
}


template<class RandomAccessContainer>
auto ljung_box(RandomAccessContainer const & v, int64_t lags = -1, int64_t fit_dof = 0) {
    return ljung_box(v.begin(), v.end(), lags, fit_dof);
}

}
#endif

/* ljung_box.hpp
sdKttw/C2ek+e4eGFT4awIh75UVKnV/bNQDTVLiCndgzAIsVrmJn7jMIixU+pIyD+2pY9MIis0p98oCOEwA0wG4wl+6vY6BFrDJ//aCNgYuzzsWWMo8cGoClMpOO6oNsbA/ewVCsxG053I5DkWR7+jCOs9/JsYLIJvtIOw4yyu2IyEfNwwln6wYoNuyPIJz9Pk/+ku7aJOyxL6JRCxhYzi0Aeac6X44ZbxpkE0b1dm6djaP3RsINrbdx9M5IuHfbODLkUfrTnzeYOHkPTWN32MTIuCQ0djdaGMq+gvuhjaPsq3u0TQbOtkMiG43NBpbmaXoz0jCiqVrr9/oWC9dav1/fquNknYglRNmbb9NxlDda47+8XcfA5S7Zwd6m0eAlANwWKvW04x6Sju1m9jG6U7o6AKu/nxO+3tmOV21DASbxv7fxUF5TPOX9dvi18Zp4WY/5bsBK2yusDsP+Kr4Xx6x9P/97C2Pfp1/Z04IxbN3vHBtS3vD9PPYS148ZvhPq7/3+fYYJOxoEZeXnrsuWnzfdlQFsZbyrp61TdQmiyHfjomLdBZhWxAgw7LvO4v4D8Unh107kFQy2G2DSPNdZNGPv6vjCj8uyzGqBh4qHvmnE5zb2N1kZlmF+68rT/C39rQdh/doN8uSbfW/q/HxH0N4GtJuX+Hu+MGdACt2j34S/O4ZgZZg83wVD7elZRDxC6sQA3das5WuudMYi33c3DMaiWLo/2jgQe2xydqnbU9fUTe1YYVo+eWF+6jldOX98fHM7lvzm4Dy4pRWHFiqU9rmtg3E4JclxOrxtDexyp7Ni4N8/GC/cjKFDGsrL9oF43KkQdmzHYOxMZ7k3q57FB2OxdhV/O7cNxoLXZYmXe5x7DMTjkk5tcqMdKz1Vy7X6nq04fGWmvL5ldzuOB1aj9lDWlHu149E/BPqNa8WgmwQq93vvPRiHkckk9vd7B2NxLMj0j+5bAzu3THeu910TB+Fpp2m9uN9grNnHRw6sgSX/RtTHDw7Ct/fxqw8YhLf77RsPDcLa/fbyAwdiRRWb+IsPGoRv7+czDx6MX15dWV7qdgh7eACWxgSdix4yGCscaCh5jh/ajhVTr5gtF/nwID91HC90wMQ2WywQ0v8IYr5+xMbISusqOhWP5DhB5q/tkn/5dvg+2PcG6S+04Myzw+VHAea/8M/xykebONsP2/JjTIztf+/cUcRUNWhKjOege30ani6hH3aWxculkrcrx1qxmDWSWR9vx1GVUB4/04I1fcX1HmtjBvmKWx5pxWLVUB6fPYo4uyvh6ZBk5icGYYXCiMSxk4hrn14l7s+DcVBsyuN7xwbhZNEp/tkdg7FQdPJP/biBOOwZ1N9f/3iB7a2IjkDfjzwBv2PtS9824juORGV83PlE7fukOx44p7140ivqybBU+v6TOO4ivWviUHxxZwXvZFHnW7XZE7PJiRH4vLPxc3Z0ns7VwnuvuOIUQLk3vXxPfW+alklUp0l8q3vTxhfJXao8P2GJm3hVVra7IoFWVn2RHBOBhiLxNzrdE/aMjdzh3br/OjeP4shP3LUFVxCESBU61/8KcdrSxu5xt1F+J87ixMnb5cLrcz/0DiQAblNhUoZMRqcb/SBDlp/nuZvG6X9VeBLNZfp8P/+TgyBT1CfESuCWx7ixPgi0f+2CuU/QyjOFiM/Xd+E8jnbn5/ar9mTc2ptvw4QC3oVFtDn7OcjnU4PvlMEQ8lU2Hy4mwIeYXwMfjJyZqcVOb74Lh8nppZUZUjsRmElLDnZBzMEjKC0bQ6ddDhXyftuaJlkG7gXM7wCjA/q8f2zlJUu/9nLj2BM5gLEJmLOD8ituLWYACbg1yoVnKIG7B+A=
*/