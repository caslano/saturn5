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
AAkAAAAAAAEAAAAAANIaPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NTZVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSVy2eBaIBAACZAgAAHgAJAAAAAAABAAAAAABYHD4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjU4VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqd+nQzSAQAA8wIAAB4ACQAAAAAAAQAAAAAAPx4+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY1OVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLw6SqXQAEAABMCAAAdAAkAAAAAAAEAAAAAAFYgPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKT/FfO+AAAAHUBAAAeAAkAAAAAAAEAAAAAANohPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NjBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSR/pKyWIBAAAKAwAAHgAJAAAAAAABAAAAAAAXIz4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjYxVVQFAAG2SCRgUEsBAgAACgAAAAgA
*/