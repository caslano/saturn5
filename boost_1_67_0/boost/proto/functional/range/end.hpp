///////////////////////////////////////////////////////////////////////////////
/// \file end.hpp
/// Proto callables for boost::end()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_END_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_END_HPP_EAN_27_08_2012

#include <boost/range/end.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::end()
    struct end
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
            return boost::end(rng);
        }

        template<typename Rng>
        typename boost::range_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::end(rng);
        }
    };

}}}

#endif

/* end.hpp
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
*/