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
VySrLjs+xqPOBEHpcaeOzA7HljXUnLicWrsl/t9r4VF4ThV3atJUtjQOJpyQOjM7EbBC5YloBRI2AVGA7MDfMUeKP4+2q/BeNkphIoa0yXLQ8LPYTfyGe0xxYMJaSIrAkBg/+a/IptQjILx90HdvH7Q9/jl8KT4T87MAWdN3a9oevg9fsnd9FXCR/V7evfFAe6SLix3lQ5ZugY7qQg2s6YYNb+/Bl5Yz8uGyy8GKX1w8EDyO08aDePysKE4jijRi4JjZUgZwMenyNm108Z5sUxFMpIRVSRaFEPAFBkZKHiboGTvUnT6JBUjImUMIjmiLvm9afJxqpmV+nVuLwDi+XqZ6A3w1GJ69LAr+pKJffBw+hVAmrmQTYbxXevSrPAo1juUUQIPwLZYquknfDr7HhAWhOaEjGVsBTqJWKagVKzS/eS1LLMXYORSWVcw/iJK9+65swbx983QgvD1512K76+GM45qGbVMvq21ZjaogXCIWSLvtwHo22oZFWjuv2+1Y68UaroMkywQh+YJ9TxwLC7jsDpQeRxmUKj1b2XWE+Zxx4N7f3zdSBi9Uil0tQz/Jp0Wc1WrKqXaoZPXkNZVyNytv06/IkJd2KortDC6DcmWE6g03CatqV0XefItswcV34VjFILFf2xhtipRq
*/