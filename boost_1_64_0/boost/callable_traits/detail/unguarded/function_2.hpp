/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::false_type
#include <boost/callable_traits/detail/unguarded/function_3.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC noexcept
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::true_type
#include <boost/callable_traits/detail/unguarded/function_3.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
/* function_2.hpp
mMsStQ62gF3efYMw4iy+4gzysA194iJYlyPpcZe5JmrV5wSAtSKsuyWasq9bE8oxzYQHBXMBWtqhzWfN0msCe9q9iw1+48XFRRROOlD4oDnGX6vmEh0PPtK2UsO7RVN8NdQk0qc5G2afTo+w/vx46bSJGJyIZs+aohT2LXqSr3u1Ur+nuxQHigfpp9QD0tK1/39Z3zlg+r6HYKcFU+eBjOSLjtfGyAOjoZibOcAKLyl0MCJcSVP5C4wIjk1LnlwIiCAZZp5riKfKZwK4G9RkHtgB4G4cuDqosnnQibw9VPahj+ZOpw2mMvF+aQatp3CX0eV4QMIgh2UuioRszin8iGdPCiXZpBjS+go30vX1zo6ESYMwzEi6kujis8DiX6ZD8eMutX26DTnS2OQiG4RBO5b7kCRFmdrhKMOUW0X+7l5AAxlM5gi66HYn3L/paZVUrIfleni3LylszkpRmTxFCmSqQcTY/l0NN3RpSCZvqUKRT9fYWQVCNLG1TT21e29gUhiFw/tFwemLXgVNYOhxpNwMUjDYdzgLXv5wg/DubgHK/+IJrnR8uQlhiw==
*/