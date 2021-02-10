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
cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDcwVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUh+funXQAQAA8AIAAB4ACQAAAAAAAQAAAAAAbVY+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDcwMFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKsc7eE0AEAAPACAAAeAAkAAAAAAAEAAAAAAIJYPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3MDFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSTeAkx0sBAAA5AgAAHgAJAAAAAAABAAAAAACXWj4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NzAyVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUrYMU3pLAQAANwIAAB4ACQAAAAAAAQAAAAAAJ1w+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDcwM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIS3tuWJwEAAOgBAAAeAAkAAAAAAAEAAAAAALddPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3MDRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS3GrCaCcBAADoAQAAHgAJ
*/