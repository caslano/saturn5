
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED
#define BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/function_types/is_callable_builtin.hpp>

namespace boost { namespace function_types { namespace detail {

// wrap first arguments in components, if callable builtin type
template<typename T>
struct to_sequence
{
  typedef typename
   mpl::eval_if
   < is_callable_builtin<T>
   , to_sequence< components<T> >
   , mpl::identity< T >
   >::type
  type;
};

// reduce template instantiations, if possible
template<typename T, typename U>
struct to_sequence< components<T,U> > 
{
  typedef typename components<T,U>::types type;
};

} } } // namespace ::boost::function_types::detail

#endif


/* to_sequence.hpp
5VWZjLtsq9vH4Kr8aQyuyk2DaFXW4n78E63KWsSruN94VeK7nzY6bOBwVc2rspqn6WKDVmU1rkoPxjiku8y0D2lVDpMs5fBoWJViMd6GP/bZy/OieXneHm3D6vfb6EoscxY2Rb+/5HUKLnnsq52j9hWZcvX53xNsqynlKtRyVLJf5fTT77zxhbYseyO3w6OMQmdrxcESGUMS4T20I19OC0SCD3fctIB0Ij8FZiSLo5BVBs0rWszQCUD6nL0MAeaewNV22CujhFmg/u03C9Q1JtQ1BPWdvRMtUNfoUNdYoOZ7aEe+bADqeIT6cFFX9DuXUG+hDMIA+FFgkDbYlH9+ng44JoM+XwDuIsjvgdZqTchrCfJtzwX5edbqoNdaQF9B9xXgLcEvXQx7c5cEPst3Cj0/R0jC/lCkIuj7LQT9en6BVklAyQos5sUON1k8ltNnVmrmY2rm8e2AdA51lYKa0WzgwERoW4WN16ODiTLcB5y9fuXDaCGz6VQM7eMHgf8ipiBmfhOSQgCPmJENaV13kiW+1l4l7ytQB+wri+S+Am3ivlJFo73jF9pXMoxednNfWRS8rwjSy6il1BkB582/JKBN1HmWftz6C1Bcu6AqYnroE1x3JgHoDiVCzJgVohTZ5XLWnF/3myT9p58T0IpI1s68fjBVB6oJVH3Em0jVgaxKrlFS9ScCdqbgD6tfperXePVrlPgF9HokXrca
*/