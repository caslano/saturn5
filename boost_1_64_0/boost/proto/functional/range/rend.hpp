///////////////////////////////////////////////////////////////////////////////
/// \file rend.hpp
/// Proto callables for boost::rend()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_REND_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_REND_HPP_EAN_27_08_2012

#include <boost/range/rend.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::rend()
    struct rend
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
            return boost::rend(rng);
        }

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::rend(rng);
        }
    };

}}}

#endif

/* rend.hpp
c1c5e1U/Q5N4ErI/it/fCN13gd5sioux02/kx2nkv/H8eoCJyy2Y/tspPRnek75cTxnCWiGY/sHO+NcsMG+1Mg5iDwGXPhN+gaARCnIN1AEhVz0OjFd9IpP0yJ4QaUCkP81ryjxJxPmz6gc4HKT4z583fatzcmQ7RgwZZQvPKiPjApWuG+7AbAOqy+ksnKDYkWxFBxo+Jqz71U3AW17mf3Sk5S5buSnrEOOcfY8SxoPrdsUIPjfy8QaPqchH6BZFIl3zW1bGmJAW4O3yhzqntFxOJzpnzDxmIeE62s3CmBDyQ++OeQV0IfhQ6aUEypHWNeCRxYLbJzR3CE7Xhe8YFCTcp16Rkz2ZgwDjRBDjuC6EhuJgaEiq4nBLEzGfX6v8XAfz6uwbMTkuzh5HWTJBfZoTUour3xvQuyjZwbWObNvTGJt8/tohsyugEXMFoSg2Coyl66GSiPawJNS8eUkPbV+Nl1ljld1VjxMIXzgZ1zkZ7/C6Ps0b4YWplea4pXL4JCi6nAurjwOotmZZBB3x60oUv/WuohuwVCKv0RFwDe6te3+wof3tRtT4Hw==
*/