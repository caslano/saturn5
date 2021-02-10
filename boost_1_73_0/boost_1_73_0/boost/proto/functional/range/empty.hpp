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
LWdKUmfwr9AOAgAAEwUAAB4ACQAAAAAAAQAAAAAAviQ+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY2MlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJa07R7cgIAAMoFAAAeAAkAAAAAAAEAAAAAABEnPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSHPblZ0UBAAAvAgAAHgAJAAAAAAABAAAAAADIKT4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjY0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtTXogRCAQAAKwIAAB4ACQAAAAAAAQAAAAAAUis+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY2NVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJK3of+PwMAADVHAAAeAAkAAAAAAAEAAAAAANksPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NjZVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSa2vlArICAADpBQAAHgAJAAAAAAABAAAAAABdMD4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjY3VVQF
*/