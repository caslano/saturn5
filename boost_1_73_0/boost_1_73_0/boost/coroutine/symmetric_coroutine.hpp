
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_SYMMETRIC_COROUTINE_H
#define BOOST_COROUTINES_SYMMETRIC_COROUTINE_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/symmetric_coroutine_call.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_yield.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename T >
struct symmetric_coroutine
{
    typedef detail::symmetric_coroutine_call< T >   call_type;
    typedef detail::symmetric_coroutine_yield< T >  yield_type;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_SYMMETRIC_COROUTINE_H

/* symmetric_coroutine.hpp
VpZzIlFbFmVW7PFx4Lg9xL4zRXRHHqHGcDpcP3UBMpGV6MOyiB73ZhSMLsJ0Hl2GNFf9k6NlMSXN+lC/VVwCgbelsXKLz2tpyWVrzJsM4eAdrFyjaiwPHc2y23p8wGlgbaXGasd5Fxr/bkjg7cthBYYFMec59RJin+vcox4d2rbvj0YHOUna/lS0DclE6rYVB9w80uU2ZhnJBTt2tczOR3Dy8vQlJytqWrGuzBx5eUlablZmnSNHDd7CK/RusUYtGN3VziVodsbi+kfzaSu4DWuqUuxvCKqQvfC14tGa5U67dEhTZNa03CaFTBD0xOu7lwzyvhMrLJj3JH7FKd/R9QZ3tKyF3w3PebAYz71j6HfQ50fuYDqL5/EoHidewPcAScI/g8vpOHRz3k6tW0S/PZppAsD2aTRl0WfhEfzjwacjz4KHUafHAHr7Kw7vBQPgEx175Oir1p9ZFC/GZPzEukOuzcudDem6rbZiR9yvUNTNBp4Nn5h04r3Jv4eNE1wF0Th4F42j+Q1PXDvw7UZ2CrNwvphN4CoYL9rtG6bx+5YxgFrz7drQSNP/Bu3hYvJ+El9P0thtsbYzvSQMIRgnMS3ydzP47PRBj+aPEDxoRFNCIR5fhfsT7z9QSwMECgAAAAgALWdKUj96ukFi
*/