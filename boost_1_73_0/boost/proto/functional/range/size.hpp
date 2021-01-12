///////////////////////////////////////////////////////////////////////////////
/// \file size.hpp
/// Proto callables for boost::size()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012

#include <boost/range/size.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::size()
    struct size
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_size<Rng>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_size<Rng>
        {};

        template<typename Rng>
        typename boost::range_size<Rng>::type operator()(Rng const &rng) const
        {
            return boost::size(rng);
        }
    };

}}}

#endif

/* size.hpp
4NaF+il6sJ0rprxDSFq2/PoLNrCWDbGwsc1Pcf5JVs91vWEjWz2HmlxChVdcYQooW2nfRW/lMHnEYLMp/GnnezRn9LuMb5iVryOUjt1B0puf7op0sd4cLvhEZkKJrUiyit3y+eIXjke2E002vVmKq4ks/ikKvqTHPyMMpnhKRW08ys59b9Sf9Dc7951kYTo4Ud3WNfe8ylo10sLVqqmN+yLJqWjY0FP/OBaZTo4zHaQ41VP2
*/