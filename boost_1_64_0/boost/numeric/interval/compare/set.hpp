/* Boost interval/compare/set.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/utility.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace set {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(x, y);
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(x, y);
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(y, x);
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(y, x);
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return equal(y, x);
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return !equal(y, x);
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

} // namespace set
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP

/* set.hpp
ZqgvMN4uR1VGNTIM5sBsweuZ1aiGwKyZzTyZSmfFNjAds6idLWrTGhP64lLWJZ/2I5gdsz3rx/5De6rQ7sXurTQveYJNPD63KeU8zJbZ1fLscjqfwTTMyu4OprpUDDNn1mBWo1WU8zBLZtOfRYbQ2VRoF/1HaS59sxJs+/A2fSl+MDUz1abP/Sjugs042p/qhDoCNZmZ+8bsb+isCLNhNkS1Ygq9o8P4vNQftiKVYgtzZtbG+0EM7QEw3pfOoYtoD0+F8ZxoFnbcjPYHoZ3N5dVe9C4q9NNx7m6qu9kwnku1fnHqQeclmBOzGOv3Rym2wj3H1RobR7GFmTI7PdvpPO0rsHBmvT4fN4pqQW1zVSQzv1GT6b0qERbB7NjrVZNofLAoZieK1m2kuivY264+VJfKYTxfFp3bS3OtiqxqtjsWtqCcgPE43Hw8jO6pE+xlxXNTyhcYj9Gmzn3mUC2AWfK4r0yk+YyBWTHrMaP9X5RLwj1TrzccTnUC9gkz+wZbPqdzAYzH4Yrm179pP4LFMns2bn8SnYWj8H7EbFrvahupn7BY5czgh+uy3JS1VHui6HmV1qBl0zSqITBLZv69vqc82wvrptzTF9ca3jfO0vmsDtWlSvt2WL0KOp/BCpQ9zgfXkjvOp6leR1MdrDTrgBGvKX4wa2YTgy48ovjBrJj9+/sT3Sh+MFtmN5oU7qJ3NZgFswlD2tN6T4CZMavft/QD5bxgJk877KTYwtTMYkrO/pvOyTBTZl07l7ah+iKMb2jWnBpUX2A2zB7ON2tK8RPm7HRS4ULaO2BuzJYdG7CZzkswV2YLvtz1nmoIzJOZre7Ubarzwly/SLhFefYIZsmf12BTHzqjCFb7TqtCqvPCPXV/XjCjNR1TtZ/nNy8fQXkG43H4uvVYqmfBMGdmPy2J9qPYwuyZ/Zj9Yg/FCBbG7OX46R3p/AIzZxYUf9WV1q1g3910aEX7NMyS5+7O46kUB2EMg9/2mEt1HsbzxfOvMlp/W2E8z/rt3xdJaxPGc2mK2jmczlmwROUs9THBunidpTrYoR7dE4YYmb3Io/yEmTM79CCxPp1thHbjHveleRkN0zBrm2tP6yETpmX2ZcNVF2g+YU7Mlnw/tzGNHWbBbPrEVgH0vRxmxsz86qVPaF5gdswq2k36lt5XhH5Wn1Y3ns49MEtmb0+lHaL1AAtnNn9LAtU6t/pV262e+MMAqlkwD2Z1i/81hfYOmCezxdqZtBenwLZXWnyldT6qfku1Nbaqjd7b/wnt4Q3ozF5pju75/Wk9wOoyM4s6Tn3JgsUx6xyQSvv7aVg9ZkfSvyqj532CPY6ZT9iDMHpHgJkyS3lw5hatPxiP30SXsPqUg7AMZc/x/mju/2yjcyTd87+2pvaEelR7YGpmv6z7J4POEw1xjmS22KX1coofjN/zettDK+kdCBbBbJ/H4dU0PthopZ/Vcf0k4dYY+qbTkHIChnz5rYD28FLB7K0felJthdkz67elK5kqDuNj9m5S/X8oDjB+zzWjAhNoT4VZMUt6E9aE8lNoV3KjoBHVVpgFM5dbcy/T+Rpmzez4Tw3SaL8V+tmn/baztKfCHJn9kux/gnJeeJ7bL+Mu0t4otIs7HL+J6gvMgdm2WXueUX2BaZmt+7ZfLaq7MD7X402q0RnzgHBP+0WOlBPFwj3jrJddpdgK/bRt4PWC9j/hnmEb939F57pPUbOYNcu5kkIxgtkyi3ZNXk1xgPF7vvj12BRa7zANs/KLMUMod2E8J5JbpLylOMB4/M6anq1O35OFfm6p9bUdfQcT+llSraSU9lSh3dS0JMqXPKFd54xribQHwCKY1bym/12Bo7b0U0NN9sI=
*/