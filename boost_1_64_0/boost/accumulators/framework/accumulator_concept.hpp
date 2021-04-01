///////////////////////////////////////////////////////////////////////////////
// accumulator_concept.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_CONCEPT_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_CONCEPT_HPP_EAN_28_10_2005

#include <boost/concept_check.hpp>

namespace boost { namespace accumulators
{

template<typename Stat>
struct accumulator_concept
{
    void constraints()
    {
        // TODO: define the stat concept
    }

    Stat stat;
};

}} // namespace boost::accumulators

#endif

/* accumulator_concept.hpp
sIOAbmHVMcfooMLv8NNTvAgysavS/DJCR3SlcK8HkEgf9ptqmsFeD/BnOYJJS6l+IHYx2KHffOsfCT4r+gt7SfTJpKKdmJSHYvKqsVDIOTpK6Oe9iN9zyzBxUmOxyed0G9BS2PzIPFtD8STUoay5sdiDxPiwZ7KRt4tx7ddhdHoX7ahkoIePMhWBoFNEoyRD8uMlcL7Hou+HefcZol+HWHNCwJB3dAcUK6lxGv/xij7M52aP5Zw6ob/4P99E49bBOsGeS+Dx05/a7HRhVKLtMNf5+i5HE2hxJQ0gtTPQ2Ta1HM38jqbpiqNPj2tONEU4UUnXV3PTEMGCdsCAJXtwfhGM1P7B0MqZX+HGCJWxbEA+9YGyc/sLeDDZR2VfwGxCj+/28TIlJ2REJulxNnpJkWzmU8emQ+isDi5ebJf5cYW5TZcPI3GnfpdNgVHQ8TEYimEj6/CUwhz77kdxvqNLQmoRVhSZqDwREbRWK19yUyZVevZEYcsBtm9KoQfcG+FBmDp1mIKfBK9/cW40o1Df/OAaqfQ/88yH9D+niESd8uQUuIpvlLuUwrozvg==
*/