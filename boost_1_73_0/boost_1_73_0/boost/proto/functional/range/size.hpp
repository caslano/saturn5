///////////////////////////////////////////////////////////////////////////////
/// \file size.hpp
/// Proto callables for boost::size()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012

#include <boost/range/size.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::size()
    struct size
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_size<Rng>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_size<Rng>
        {};

        template<typename Rng>
        typename boost::range_size<Rng>::type operator()(Rng const &rng) const
        {
            return boost::size(rng);
        }
    };

}}}

#endif

/* size.hpp
AAAAAAABAAAAAAAjXz4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NzA1VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqluZmY+AgAAvwQAAB4ACQAAAAAAAQAAAAAAj2A+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDcwNlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJwFFnbPgIAAL8EAAAeAAkAAAAAAAEAAAAAABJjPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3MDdVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSJ3g4Dd8BAAANAwAAHgAJAAAAAAABAAAAAACVZT4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NzA4VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUr03NurvAQAALwMAAB4ACQAAAAAAAQAAAAAAuWc+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDcwOVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKGGl5yXwIAAFYFAAAdAAkAAAAAAAEAAAAAAO1pPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3MVVUBQABtkgkYFBLAQIAAAoAAAAIAC1n
*/