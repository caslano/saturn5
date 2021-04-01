///////////////////////////////////////////////////////////////////////////////
/// \file rbegin.hpp
/// Proto callables for boost::rbegin()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_RBEGIN_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_RBEGIN_HPP_EAN_27_08_2012

#include <boost/range/rbegin.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::rbegin()
    struct rbegin
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_reverse_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_reverse_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::rbegin(rng);
        }

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::rbegin(rng);
        }
    };

}}}

#endif

/* rbegin.hpp
nrFCAtz399mVVhqW/Ds+2x9TYsTY59IITNKuDFkGegihP2pFPhcQtPgPyx32hg/qgfH7LGhgwHeRPYs6kEHJqBDQ6VS5Lg2Y5ESprUIeFufUsndeV4HY3ltcp7oE083o33o8JbV8Bw4kHmFlXurhQ9S4FYgj9B+AhMhxHbKIQNR1iwv+bBj5OcB67EaaGeZ7D+dR284f1Wu5ktutx4yiLQAFVWpOGJZHp10LwjXfrZ1J8UE4bgVTqunou9psosZNIcNF2xJ6j1gKdbvhcAlqQkMu7RYL2UU5Pk24r0LBQ8az1IOIBrPoiGunBTDs09OMNzvAbu99GPacpxpN1AmIGYZ1lZpk+sv6UL3zeh4Yde1aW4qy4ZvjvRftmiaQJ6kcw8xDSm7mXAxrXI2Fwp49iqggJaFXbhalV3O+WqhSSKsQch+HiRkjpuj4Yx1TNyxE0w3T7sQCkscKFSvnEUujQfNaaaXP1YajY3vmu5Tde1dEKPfxHAph8pJ5797xRkAQ0GNBIfToEYUWcFCAydZyaoSTtM3LlLd2rzG+Lb1ojtRLT4VykY4+r1Re0Q==
*/