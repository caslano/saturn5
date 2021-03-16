// Boost.Signals library

// Copyright Douglas Gregor 2001-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org/libs/signals

#ifndef BOOST_VISIT_EACH_HPP
#define BOOST_VISIT_EACH_HPP

namespace boost {
  template<typename Visitor, typename T>
  inline void visit_each(Visitor& visitor, const T& t, long)
  {
    visitor(t);
  }

  template<typename Visitor, typename T>
  inline void visit_each(Visitor& visitor, const T& t)
  {
    visit_each(visitor, t, 0);
  }
}

#endif // BOOST_VISIT_EACH_HPP

/* visit_each.hpp
nadV50nNIM2WeQ/YzLdZXbKDybQEP4QAyZU4E/4y3d8c+9XzSLJkF++TWuabuNgDeZHMd8m+S1H11KeopNOZWq1kFNHQJdgPrPsp2ekMdi9BNT/1kOuHbsQsF8GGJ7t9mmfTyTJO18li+ng6mb6N7eTVNpnvk8VsnQCuzcuZCIUg0f15YRazeLGoxHGTrNe5ntEq36dKCMmrfUNTLnicBiRRJHf2VFLd1le1nseEYc/yXQ9dXFrTty2rWeljGjo=
*/