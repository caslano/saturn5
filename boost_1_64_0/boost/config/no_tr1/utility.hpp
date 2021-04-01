//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <utility> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/utility is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_UTILITY
#  define BOOST_CONFIG_UTILITY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#  include <utility>

#  ifdef BOOST_CONFIG_NO_UTILITY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#endif

/* utility.hpp
Et690V7hmYXKyW8rUL0fXr0o/GmhH/riq7GRadF4mWWppqXe03ZB583KE3JurQQ4zHn2eosJ+ugzAk0W134UQLhm30WCCGh41zYtG8G6ehK6dViDJrcU4l6nJXywJulpfHepwYR8FwnLvYWM9wSdQZ4fOrDxgShKgMy4p3ijhq+vVjxjc/F/COK/Dwluynuzl3a7dwL+G3wwulzoSWI7vPo/j7twdX3UM4QDaqfwmNx4qtqUVWpyDkKg+zyImjzh4slvocLLwOTgwjQqTpR+6B9RnSmqQNnp0tV+knlzdQetOO1a7+gPCK/AxYImf6xQmb6PpNQ5PHAkWJKQf0Kexw9OzIn4cTvbNbo6froy62Ppz3Tu2vhnKqRkBYAjAVbt8fa+oPdsuhpNooR6Gy/v+niQudErsxdabORj+zIb2/Z02eUrPt5zYa0glIv1X05mMC7xBTiO8qv62loLBO2dxWMVQvQIkkWL7IO8BAMHsgl9sGq+JYVa2WqEESkO8FfbLGxCn5DT//ijdtTgwkyRGNBQFYDSCmKZ6LIi/lGfflSMnhQeAnZ/zANM5A==
*/