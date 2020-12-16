/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_INTERVAL_HPP_JOFA_100331
#define BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_INTERVAL_HPP_JOFA_100331

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_continuous_interval
{ 
    typedef is_continuous_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_continuous_interval.hpp
apgErfMxj5IlG4bbL7bKdwi5aDOWZZIsl4YO91XJr+wp8AAak1Dyje5mFgkzUORab/JX+3B6+1yOCC9Ng6XIjyyfpWSTLpRglPj3oyXVF1cpZFHr+ZRmX7T6Ao+twlAXVjn+yaUW2qkOPsvmJZVHUTAnnyjS0UOGeemwf33mZAKYKkI/Blkr+Bt47SBHoYoW1FqV5TufxjfR6/rqfsPN9ViSXgrdKzWyPq3CsunLeablfljmEja3q20W+Eyf3L+RfPxIf2hzYvNM+w5NPE36BQ3QFTjH46fsnwqpr7ZzHkyLNpY2xQYD3lml8ZwzdI+OUY9T6WI2XU8vuXs8+pxHDzePSr+nji3fWpbVE3yYVQoeG1WcLvgwi2R5gCJ9oR9upo8JfVWlR/q8LxOL4OHRa+mX8zkFDy8ppc++GOGV81bIg/DIpkugiZfzgr2dUGe7x4e8sH+J4Aq9lhf3nFh6RPxRoBcLp9Rtw2mvTUPe2THhGUc3EUe91IXQp5geKQs9dB19C9RqOYXeOZ5cEp+AbBNKIxI4AOOg4riCGad9N6bJkQqQvjVtD9ACnM8ByPUNYie1vqbv/TEz/2hDXwSolll8bkNJ2eWCvmzqDTfvi7GejI/ZcABSYEmmeGewwd8dYj8CzokkRkGvHbenU03tNsWZyuHE5lpuVmkP0PJ+byq9lj2n3B4aH7oT65jsz3l86EqsZ97+HPPxokzyhplxSN2bc2Xw4kn53l27JYjl8SKK9c9HnranFyMmno97uukrX+bdeJX60eXr825Vf31lIhPCijYkqXTsVWzAWiFFO0LKcNaskfxCzb7MoMKGXFt/OfaNhg7aR0nyqSh9LaPTNIhGhaEWmA+XcZnlPGh0PHg43/D4JRODcZ0GO0G6DMmkTieyYmupTrW8oPZETo41VMcr/NBSDd8RaXf5WVN1vJp+r86PLTOXnzVWxyv8w9P4sXXm8rOG6njmf+JAv82cTCUTsf7e/gTfzvW0UnHU4E1X8fTUtF1O08cY5Qsp+oLXdu3hxqx8vM9WqV35sZCVK5ja3MbfHM0sB+2mS8IPlwhtn5kHbaXxsP3dVZuRB/Xrw2PZywqaOsyWR9StD296IGU83hyVpUm06b4mvzLnqlh2YZHiW4Fsf0pF/iL+ovy+FafmK2bLuuR8+VcufnTLQMrxNc8qw7+y2Q5DhsFCLiLDv9LFp08XF5o5KRHkUGuFwODQJEJEZKhUQiepuMR0OZV3D5X/OCJ7zNqlVb5jidCWLSotlqY+YwnL1Pw3tIydLOYnsFbXKkofV/zTwiKW0wL8ImmBlj52Ks6cFnhmSgsqBnLSiUYG5oRm/Rkr17C0NJwbp2gB4YlnPUgbSfCpC+JY2gqw/NSmmCobz2qRb/VQ5UvP2wT+PPvhZpSfZBGSRqI3peUfOcRQqKfBwx0S6IW7RK7jnKUcIkb8HVIWr5JUn4B/EUR2bHoF8fqMHXRPxaEuC74PUnEAxAbHicSePaqeEZ1ePUvDP7CMmFlUlEaLczb6vJTovEtudHrfMzniH5pEunmkDOe/Dy/VV79LYzCRRqOdK0ptR43yfW7u/UU8hqfoVoRxjEt0CyMctkzm3WuEsVzzw3YSAiDptyxL98OCqKfYALnaP33k8aJJ6Zv+8jrbWZzaB6fL68BugHZ+kpd2mrwO2opPY95UMrVzZ7JQkQVwk/yIj/yYn/zI3ORjkaj7uQlOMElDFocz1zF7vHX5vGjU5XN9a/JhDAGbsd4lCV0+OxrYP4ZrHVS5vKznfemuVAGXGtEEiglVWbzYFz+J4FVZUs9YMwLdzMv1yPfeAK3zcv1Z2THT9kFipeibB64vvheGO5Euy6urEu8=
*/