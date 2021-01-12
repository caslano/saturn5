///////////////////////////////////////////////////////////////////////////////
/// \file empty.hpp
/// Proto callables for boost::empty()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012

#include <boost/range/empty.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::empty()
    struct empty
    {
        BOOST_PROTO_CALLABLE()

        typedef bool result_type;

        template<typename Rng>
        bool operator()(Rng const &rng) const
        {
            return boost::empty(rng);
        }
    };

}}}

#endif

/* empty.hpp
7tcb8Y/hJ34vpysT/2bDEXq5V0KjToZ+fQ/Xf49/+qAadUUke5bfEw3Hwr72nFMaR+XU1dTXguTT27jwcL10iP6tL/57qP4tgQXKPeFgBO/1ikhGxj//xOkOMX4nU0e8yajk6rfbBomN68EQtxQxH0j0KRYW9slJuMtM/d+JFksj/vufhC/HgZJ1oCOloDgvYaRkQuHPI354it1cNyPF6zxSChNHyt3EL+/gjIBUnutg/Nep
*/