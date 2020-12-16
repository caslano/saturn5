// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Revision History:

// 27 Feb 2001   Jeremy Siek
//      Initial checkin.

#ifndef BOOST_ITERATOR_FUNCTION_OUTPUT_ITERATOR_HPP
#define BOOST_ITERATOR_FUNCTION_OUTPUT_ITERATOR_HPP

#include <iterator>

namespace boost {
namespace iterators {

  template <class UnaryFunction>
  class function_output_iterator {
    typedef function_output_iterator self;
  public:
    typedef std::output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    explicit function_output_iterator() {}

    explicit function_output_iterator(const UnaryFunction& f)
      : m_f(f) {}

    struct output_proxy {
      output_proxy(UnaryFunction& f) : m_f(f) { }
      template <class T> output_proxy& operator=(const T& value) {
        m_f(value);
        return *this;
      }
      UnaryFunction& m_f;
    };
    output_proxy operator*() { return output_proxy(m_f); }
    self& operator++() { return *this; }
    self& operator++(int) { return *this; }
  private:
    UnaryFunction m_f;
  };

  template <class UnaryFunction>
  inline function_output_iterator<UnaryFunction>
  make_function_output_iterator(const UnaryFunction& f = UnaryFunction()) {
    return function_output_iterator<UnaryFunction>(f);
  }

} // namespace iterators

using iterators::function_output_iterator;
using iterators::make_function_output_iterator;

} // namespace boost

#endif // BOOST_ITERATOR_FUNCTION_OUTPUT_ITERATOR_HPP

/* function_output_iterator.hpp
kHxVQfJVB8GXBqoh3xib9ulNufahnp4FHM7waIY913MdZD7242rdjiXkm2XTjrfzenewHX/B/bvuAnYC3k2/8tXAEcB7gJOB9/K99pe8zjz9HQO6YawdnOMZlzvc10kFRqp6AqNVfYDtVP35vtQf2Bk4EHgZcBDwcoavYli33yHK236+QMu7inxDbeTdk/XvBexP//oDGB7CsOd6dTof+3mHBNygM86PtEpAK0HVoM0gzx5g2/G77vzI/8m9wI6hXnb7gTmnRwa9J1jS9MgG7QuWNj3y/2ZvsKzpkSfdH6wSPNWgLaC9oOOgdhdA/qAZoCtA60FPgmpBB0FRM6CfoDTQHFAFaB2oBrQddAAUNTPS6gFKB80DXQvaCNoGOghyzoq0UkFzQOWg9aDNoFrQMZBrdqQVOkJH6AgdoSN0hI7QETpCx7/j+Ff5/5e1dmWnxv//xxiMThP//JJpprLk7UB//gfP8saXLynJyxT3Vu7zdUg3Q6eTTQPLsKlfds58734Ac+S8Wh0gycWff3mi5fWPF8H5Cwf9+QGPqMHx9miL60gnjZg4Rq3p8Po1lesFsOvb7utbVi6r/ZPsk/On2dqMMa1xHfF0aOsn1eQ92otrvwz/CDHvqPNXWZPRKiwLjuyC/OwyhOk/R/KINfIoLiox/KzukPPPoWwOay3tfHtAPo+EYT4TMoxuAk82Z2JdeYxTr7FZlCjk9jeMiI2gxbL2xWW7N4Anz93gq5C9AcqdjVo5wzGi8tsfIJ68aFBrieJtXHmXMzxK8x120W6WfNPAd5nic1Zu8vB8CR5v2+TnVhj+1rqJzFoxjNW8EnbVy7MCeV4u9sOV+z15XpHI63KN8+319imYKnrqigRnYz891W2RKNdqetI10fX8v1IPW5rrYEXffP2/ih6J783Rch18h+1V357aya0CV3rnb60pmCCrA795H9Co2le/tc+hz4V/CebVHTb3B/PDX0u9ZlGvKtC62+hdxZMN3Q0TPUpFwsOgK5XcW/X0s6WOJ09CI9g5ii11W2ejpl79KfDhSwPf1YrP0dzZKNLLV0k+zzVzPfk1X+Sbl+ZZCZ6lUq4JmielRX2eR8BzjeKJ9rc5Vz4AP9b6ofs/rRefiLzig9YLUwfM9i3hFMUgUFPaxLXB5F/Vu/XbN7c4UxaN+bSvbVsire6D/tRL9goosrWH9eENR2K0b+kl9j63NW9T8B7oJToifEfof8uldBX1WaZkGuu1v7+WbSP+c4Owq9WyMu4h1ANxUg99D6nyxrG8sD2Wchww1tMMo4xr6Vf/fX7TeIcyrrOVcWZZcWk5LPr9ZK3XNh6VdGX295G97PUa3kXviQ9me9tk+7bQPh0ul7SJtm1TZ7TNIaNtDtTbb6ZI12Ge5DVa+wJ55D2vXXQ52nA7CnSd9OXRzkYx3ntxOduyM/lSm6BPEj9iadHO6NGNm4S7opMbN3Y2Qno7PVH51+JcShPqiSvD2aid5acrivjs0v220h/IQR/OIO61huiPktUh6o/qk7NEJnj+JFsSXskw8qrn82IXF+9uALn4rbAL9Osw+E39gpNk33cV7Svie+Fda0VDi1aAbHQL+dm/w2ifebXUD3/dQlr795J4pp0gaUcgdSz6okb+/r+pN2HCtwYckdZSvsPcyXcUTx9zGHL0ebfRz5Chkv48fDuKEl3bBT0YAvmtlGf3ec5Wp1n6naUuzs9PorzfBOqbW/J9IVauMdBqwue2KwidCea5reql6hrHupr9eC4zTmPmw7n+eGttfR1QC5FFB1H33ah3qtPzHhbv9x5W790tiLUlph/53c3dJ87y7LsN7A6ddL1frzziPDcfHq3wviXP/s+lz1I=
*/