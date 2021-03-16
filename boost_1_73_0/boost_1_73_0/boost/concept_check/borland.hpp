// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

namespace boost {

template <class ModelFn>
struct concept_check;

template <class Model>
struct concept_check<void(*)(Model)>
{
    enum { instantiate = sizeof((((Model*)0)->~Model()), 3) };
};

#  define BOOST_CONCEPT_ASSERT( ModelInParens )                     \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =               \
         boost::concept_check<void(*)ModelInParens>::instantiate    \
  }

} // namespace boost::concept_checking

#endif // BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

/* borland.hpp
aS3Ie4BTAB/30gLedV7qv54AxGdvvZdcEGI6HHA8CYgPwUbAtYB1XlJEYjwOZbd4yVPNNi8ZBTzjpbUfz3rJkSymuwFwOyAK0s8DorajHjAB+ALmD7gDcDngTkBs5F2AaOq1G/AA4B7A9wH3e8kI4FVAnGRpAMSxDl4HRfnXAfsCvgGIS6kPemmB7yHAa1U67Kf/buh+GkO0UJe4XzO3hLmHmNvM3BbmdjK3i7lvmPuOuXPMoZBD3AWG5nowl8c=
*/