///////////////////////////////////////////////////////////////////////////////
/// \file begin.hpp
/// Proto callables for boost::begin()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_BEGIN_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_BEGIN_HPP_EAN_27_08_2012

#include <boost/range/begin.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::begin()
    struct begin
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::begin(rng);
        }

        template<typename Rng>
        typename boost::range_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::begin(rng);
        }
    };

}}}

#endif

/* begin.hpp
2RMntnJCMUnegAq3lodD8wDd6uKiXVSaJymAVPITxqBOSV6Pb+2pqORiZtCNnG7hdPO2b9tOeSinTJJ9ez6QNwo6glJpmmzDSfRv0Qd003UWrdllctFZ+kIIQqLmOum4rUSRtW6cdMt0fvfKsOd6A4FxqWiVRRMLjW+Ls+oyekCvjTd92SsDUAvSPxm5+r43ogmMTwXiWrB+yqHv1Fw/WyJGFMRt/REbEZ8Y5R66X16X4Tc+
*/