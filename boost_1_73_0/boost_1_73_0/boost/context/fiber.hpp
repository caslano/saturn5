
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/fiber_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/fiber_winfib.hpp>
#else
#include <boost/context/fiber_fcontext.hpp>
#endif

/* fiber.hpp
wfGPUrDJHFMAw+DCIRdizNMXYmADbU5zVNfaGuhuRRPzjY1NPLPWEcHDzxdmbAUcA3iXU6wj2iHH0HiMSW1zinVFdwBWy/O18rhRHqOrd6fU28vMBwb3xM8PBLeEuOuIW03c48Q9RdzLxB0nrrRpfxazDReP+LHBg4qvztjaMFhZgGMgOc7YHFtwCBf3LgGnFecVrOW+Sw7HMvM2QEdlHVMr/wGGnpW+QAy79XL416tV/qo1od72qI5gKpcrYj4=
*/