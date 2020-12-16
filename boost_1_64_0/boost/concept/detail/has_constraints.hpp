// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP

# include <boost/type_traits/integral_constant.hpp>
# include <boost/config/workaround.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts {

namespace detail
{ 

// Here we implement the metafunction that detects whether a
// constraints metafunction exists
  typedef char yes;
  typedef char (&no)[2];

  template <class Model, void (Model::*)()>
  struct wrap_constraints {};
    
#if BOOST_WORKAROUND(__SUNPRO_CC, <= 0x580) || defined(__CUDACC__)
  // Work around the following bogus error in Sun Studio 11, by
  // turning off the has_constraints function entirely:
  //    Error: complex expression not allowed in dependent template
  //    argument expression
  inline no has_constraints_(...);
#else
  template <class Model>
  inline yes has_constraints_(Model*, wrap_constraints<Model,&Model::constraints>* = 0);
  inline no has_constraints_(...);
#endif
}

// This would be called "detail::has_constraints," but it has a strong
// tendency to show up in error messages.
template <class Model>
struct not_satisfied
{
    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof( detail::has_constraints_((Model*)0) ) == sizeof(detail::yes) );
    typedef boost::integral_constant<bool, value> type;
};

}} // namespace boost::concepts::detail

#endif // BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP

/* has_constraints.hpp
7YR0Ai+NIwZmZiNDENp5IidihZBFVHCXXXDmPDq/OWnJSl03TgqlqwvOKkdlXWrnK4feGMSlrA3OB4tqfmPKil2WRZHnBoFkyof6nRO5T22770h4sGeHmDm62D2B0pWfdX9ykAgzfcX2P0/lJYmTR6EINiJvpyEPx6LP07cncKvAcVRl7g09Zfl2QRdcR3kgjGGf/AKVFedZJgs/q5eFc7BaWfO2rDhN0zhM6mVhRdTKOm3J8pPYV/Kcelk4+aqVddaS5aZhFGfuuvmabNfra/yLVFYkRZbFEV9X1nR9GWNLlp/J2MlEvJ6sqR1U95Wf+keYsqZ4KqK4UJp3lU+QXZWf+gr7eILNijRxnbAAbHvSxj6dYt28kDLLS+y0jX0uwUZOyJWmPcDCwE6xLyFYN4wd4WUcsDByU+yrCTYRIvXy1GG8rmxvJtiUp3GgMgHY0bK9i2Kj3OMiDgA7WrYPEmwQh2GQpBywo2X7BMH6XiwzOK3jdWX7AsHKMJM8yQImVdl2ty3s1616c8JA+gVgoRdR7Peoznic+5nPAQu9hGJ/SrGe4EUiAAoNt4QOsb8l2BBuA/i5C+CpdlU29Ntrte848KI0EP7F+q4B30+vuaWy8UdBHuwTwZyv48XO3nZHTTj4jgHm9QpzcrHCwOxQY1R18tYA8yaF6R+rx7ga81bALNVgVFVXct6uMGu9ekwl510Ks+3BNRjVDCo571WYc8v1mErO+yGt1QpTum3XINX+770DMf3jTZg2YrY9pAkzWWI+pDBn6jF33qXTWoO0HlqL2b3DwExc0oRpI+Z8E0bn5+NQ7yfqMGrSep9BWp+C/DyMYrBx3HuIkQ9vwrQRM/GIBozOz2cVZvyRtZg7t3V+vqAwrUfVYdQsVGO+DJhH12Kmqjx/VWHYyVrMrqrs34CyP6YOoyaDe3eU+7BnoU4fW2FgQtTZUfo4UbTvQhqPq2hqMqJ+75ia6iT+ZEn/AfDa9Gmg74T0S/7+4yv67PLMwlK/11uUar6xrBJBTOsJtZjVEqPTOVWH2d1eNjETT6zFoJwfQX5rMMpCLpuYU0+qxaCcn0J7efIoRlnPZROz7Sm1GJTzC2jjNRg1v1gmmKfWYlDOrwHztBrMdFkuxGx7Ri0G5fwOyvXMUYyaVyybmHPPqsWAnLJNnYd6fzZgBtvsi+raXEvT/gj52AP7/uXLQgCACyHs86deTOyd3JvkQUdVYktj/gJ5fEkNRlVQhfkbpPHSGszkNGL+CXl8WQ1GDVUtIz/bTtP+gxky7NS5Rswk2o7Tr6jDUBt08pV1GGqDDr6qAaPT+g/02VfXYqYqGz12K9VXXmOOlxqiVmTKLCDm0iZMe4DZBHJeW4dpTys5iFlrwmg5mxVGvq4Os2uC7xiOc+caMHsNzKnXN2DaQzvB3kAwWF1VWldU+TlHMdjGFAb79+k3EgyqWWHQtvbfRGzrdNUPNkMalLa7ov0I+N5MbXJbt8mrgM7fUjPXUctypQfEXNqE0XoYBzlvrcOUQwNi1howpO7eZvYjnDbgvKosK2BQDmIgz4jpX1orB+de14Qzw7fXydkNchCz1oRpD+eLJ99RN8+bLPOMc4J31mPcMo7WlqvfWKXVPVSat053cGcD/ZjdXvnJGxtrfvxn+hHbf2WN1eSFuTYYR6RvuQqhA00Bhv6gP6Pp5ZOQ2eMLykfIUmVZb1nFE7kaYOofEpL9iKN0Xg6H537gyIudlxs+IFXC9PGt+oJ+YU4umOf7YZZKN0wchu6jqoPsW1ZrThPfTrzIdcJUsKN6fRFVuFMEx9MgD6OwYEfbFu65BJc5YRzFbs6OTmrcLo17wQI9ey+kn8vQy5g2sUGx3yk=
*/