// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_USAGE_DWA2006919_HPP
# define BOOST_CONCEPT_USAGE_DWA2006919_HPP

# include <boost/concept/assert.hpp>
# include <boost/config/workaround.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts { 

template <class Model>
struct usage_requirements
{
    ~usage_requirements() { ((Model*)0)->~Model(); }
};

#  if BOOST_WORKAROUND(__GNUC__, <= 3)

#   define BOOST_CONCEPT_USAGE(model)                                    \
      model(); /* at least 2.96 and 3.4.3 both need this :( */           \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  else

#   define BOOST_CONCEPT_USAGE(model)                                    \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  endif

}} // namespace boost::concepts

#endif // BOOST_CONCEPT_USAGE_DWA2006919_HPP

/* usage.hpp
j/tcen2lf6f1eoa0u2TdK9U28WjrbFNzWqgxVppHsc1n4l9XW2c483a4NZVVWyc4Urd1fN131f6/575rHLLuu98evPY8fIXN+zx8gc37PHyKzfs8HMXmfR4OYPM+D7sPep6Hd9Hdz8Nb6O7nYSO6+3lYh+5+Hlaie58Hys3neTBkLdc4w+LHnIfoQ9Z5yEpJyEz2Og9DClnnoaq0+euZ+6hVTGnLISWQckgVpBZS3/DZVuJY
*/