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
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
*/