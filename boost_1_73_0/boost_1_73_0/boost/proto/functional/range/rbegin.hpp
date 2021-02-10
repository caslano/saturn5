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
cy9kYXRhL3Rlc3Q2NzJVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSzKXZTg8CAAC9BAAAHgAJAAAAAAABAAAAAAAqRD4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjczVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUi8QfxKwAQAA5wIAAB4ACQAAAAAAAQAAAAAAfkY+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY3NFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIBQHjEAwQAAHoKAAAdAAkAAAAAAAEAAAAAAHNIPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2OFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ/PXV0WQQAAKsMAAAdAAkAAAAAAAEAAAAAALpMPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2OVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKF2xKg+AEAAIIEAAAcAAkAAAAAAAEAAAAAAFdRPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmUZhuGXAgAAwgYAAB0ACQAAAAAAAQAAAAAAklM+AGN1
*/