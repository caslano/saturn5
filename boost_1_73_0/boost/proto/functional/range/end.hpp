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
Pw94fhWUTLDMr5q57j+2MJr/Nr+KsWje8kZJr8UHXKLfOwezd1Pt0TSuWPiP+f43o6zL0LJm/DhYJ+xprJYimkgkOPBRL2PrNcy1g7FlmGwiVEk/W9PugZ8wtkyTTcRB6Wcrqfn6dcbWw2QTQZYi2wTKtudB3weD2HCxstnJDnyMlFCurd4nfxzIFnsrV1RT7cXxlGvGti0/n4BchxlcZuip1irJ84qsfX4Xe16HW5iCaRiL
*/