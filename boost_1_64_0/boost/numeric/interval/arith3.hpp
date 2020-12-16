/* Boost interval/arith3.hpp template implementation file
 *
 * This headers provides arithmetical functions
 * which compute an interval given some base
 * numbers. The resulting interval encloses the
 * real result of the arithmetic operation.
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_ARITH3_HPP
#define BOOST_NUMERIC_INTERVAL_ARITH3_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

template<class I> inline
I add(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.add_down(x, y), rnd.add_up(x, y), true);
}

template<class I> inline
I sub(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.sub_down(x, y), rnd.sub_up(x, y), true);
}

template<class I> inline
I mul(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.mul_down(x, y), rnd.mul_up(x, y), true);
}

template<class I> inline
I div(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y) || user::is_zero(y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.div_down(x, y), rnd.div_up(x, y), true);
}

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ARITH3_HPP

/* arith3.hpp
5xLtetWtpo/aSsZjNFvLJwF3WNGXN6M1tyEHyfgYvBa/00A9IzNjtndd6APUEGGT/X0foZ6RmTAb7lb1LOalXPV9xzp5Ij8dyHgu/afLoHDs4WR8DGaKTfOw3smMmW378qsl5oWM59mCieuH4E5JZspsa4dh97Dfknkya5f4BWM4QWbLbJXJ2p34BkHmxOzlqNXBGPsP1XaKBLt81HlhCS+dcFYMIuNxP7rbEDUknMyEx7bT9oVYD8KGbPszGHcZMh6HZ/d66OAcKSxmyQn0JV30ZYFRx2GokaJdVM1iT+QEmRuz8RcXVUct+Kka25SZQahLfmSOfK0sXfUFYydTMHvUcs9BjJ3MlZlGyZU5qAVkvJ9tDu9BzdovLMni3hR8RyHjMSo2L4EVkfG5jp/z0ABx/0V3dGYmtz7jbqEg4+2u2H2dhjMtGR/fsqKmJVgPwkbEzq+FOiHs076/krE/kJkxa+D66DjuHWTWzPpEKtfYKjJTZgEpfvWx95Px+Cn0D/XGnirG12vPql3Y30Vfkiaqow4Wk1kwO2K8BX+fUve3qnUpWlQF64jMidk+u5hQ7B2i3dqSOaitfch4X2zv13BGnRBm6BjdFvcx8czSc7b7ce4R7a7OfzYENYTMnFntlnWvoLaSGTL7cDBuBPYcMp5L16dWQYxKyBR8Tftv2Yo5+6Mao9i+26Yiz8h4X5rP2oUYNSHj8TOv3qoFvs0Is961ohR1V5iZ/7UOyDMyW2a1ar1CHVxHZsbfd8chCGuTzIpZq4Lim1ibZDw/V0f+Qe3JF9auYf+WmDPxzO4tDyPPFGoaKnM2qNkAnNm9yBTMLva6lI56Ldrd3P4sGnlGxsf+n7rOdXG3IOP99Bl9Tfn7DjLez7xmaU44v4j3hXx9MQHnF/HMz+cuuGGvIuNz7T507m7Mi3im/txiF8xLFQ2VfJlf+w9y3oOMP3PImJKnmBcylfzcaYe+hJHx932bOvgc7sxkPOfb/r2wAfYx8b6Ygi+2yCUya2aL5nphrzpEZsxs/ZRLjVCzxPj6WFrmYc7EGNQ9HyJfisUYXM10kPOG6hoq58hmQ4d0w5yROTJbPvoRxteejPczbewiY+QSGe9Lk05/YjFnZIbMfm8pN8CckfHxTRyrg/etI+N59lfM00GYMzKeuyWfnl9GzRKWn2rdCrkkxjC6qSIR900N1fjNyikfj/MgmR4z5ydB1TBnZDUrzYisw/cBtTAvZN7MDB57HsM+RlaL2dVbIRexVtgzDclGlC/GOvpJVp3ZlE+aVuiLpqoNL89ZhDMKWUnl/4+KAf2c8fn1K9QzbbyvwlzrbHqLOk+mzWzUx50xOGtoK8egT/Zp47UV2P90NNRqV961dcnG97R8h3lhpkO2auC6SMSdmTZZk+/7+iK2zLTIEhwPXEAt0FWaJlm5cbvZyF1mGmTfW47GXjWfrLjS1Mn2x+jH4zyhpxxfFbLVWj0R21w95TPVyMxGtGuGc6S+cj5/q1Eu7X3aBHsVWZsKC6qwFu9N9PA+svqsncHt0YvxfUJf2Zdf/8bl3M1w5KeBhloNZuczlrth7GQelfaTftYJOqKFOs/sB/2cs6VRBmo5s3L6GRCyaxXGTubMbOyHyBZYR4YaagbMkjMnKP9cEJkhs0H3LFB73ES7F0l2OKP4kXlWWhn9PFtexRXfOJl9p5+hhkNzcX8wVM7ZN/q5zzVLE3cEZl/p58lJecsxBiOlldBPo4iTKTjvknlV2pd/4+e1uznO+kbKvnxWoxyc1f5v3G/J3CvtE/389jb0HfpC9v9/a/zfXGww5U1HrFtjDXzD/dd6Rn7agzM0mQWzHZrN8nG2IfNidnd9ylysd7I=
*/