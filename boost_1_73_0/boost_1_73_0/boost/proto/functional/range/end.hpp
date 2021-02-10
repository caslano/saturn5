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
AAG2SCRgUEsBAgAACgAAAAgALWdKUgl8Xl/VAgAA5gYAAB4ACQAAAAAAAQAAAAAAVDM+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY2OFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLma94kFwIAAKAEAAAeAAkAAAAAAAEAAAAAAG42PgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NjlVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSJKt07B4EAAB1CgAAHQAJAAAAAAABAAAAAADKOD4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjdVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSc/gFOhACAAC+BAAAHgAJAAAAAAABAAAAAAAsPT4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjcwVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUh3ZJowQAgAAvQQAAB4ACQAAAAAAAQAAAAAAgT8+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY3MVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKUc7fwDwIAAL4EAAAeAAkAAAAAAAEAAAAAANZBPgBjdXJsLW1hc3Rlci90ZXN0
*/