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
520DUmCqu1oT5OvY/sVTLp81xkc60gk/MbX0R5R3Vx5uoLg0MDHI/GvBp5LmvpEWofEsqma3RM6JqWOAe5wqw2EddmxTLh3cnqPGfcM3kG+HXrZ+YGqaXAWRagyrxuBVG4Z+sv+jyrf802frbXbSNmgr7FAYKIXxFEnNRtpHgLOmDbAW65DSxfqMasQacwD8BgvxD6sMdfypA4TzrXADOhiX+zzv68cMvZC/h/gmWv4EkYsvaT5IG+39hogakpicfHdoAfTAlC+0IUaoal2ITwb7TIJlZBIwazAPQqMUXJ+7ZOw3N+wjA84Vo/jS4wgI0EOBnlAdPE+pNGSOJqLu2VcczRe8pxS+bMaGgKeOg5EKP8wNYVKbxr+ieD/NiX4SvIMfHP/ACbNJjb1L6+N3ue6Wm29ojYZgMI6hNmQ6tIa4Me7N5YREockT8L/Xpow2/pD8JDGPpoD7ghZEtNQjVuub9+OY13SD/y2dzCM/n625ZBKvfSjnG1x1QjB0rQDcxM8hAoDXo/g4y/NnyNTEUwiB0hBE8+fTTSoKOrzZpF3LhvG31POjJVv8BA==
*/