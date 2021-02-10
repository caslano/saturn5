///////////////////////////////////////////////////////////////////////////////
/// \file reverse.hpp
/// Proto callables Fusion reverse
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_REVERSE_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_REVERSE_HPP_EAN_11_27_2010

#include <boost/fusion/include/reverse.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::reverse() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::reverse() algorithm on its argument. This is
    /// useful for defining a CallableTransform like \c reverse(_)
    /// which reverses the order of the children of a Proto
    /// expression node.
    struct reverse
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq>
        struct result<This(Seq)>
          : result<This(Seq const &)>
        {};

        template<typename This, typename Seq>
        struct result<This(Seq &)>
          : fusion::result_of::reverse<Seq>
        {};

        template<typename Seq>
        typename fusion::result_of::reverse<Seq>::type
        operator ()(Seq &seq) const
        {
            // Work around a const-correctness issue in Fusion
            typedef typename fusion::result_of::reverse<Seq>::type result_type;
            return result_type(seq);
        }

        template<typename Seq>
        typename fusion::result_of::reverse<Seq const>::type
        operator ()(Seq const &seq) const
        {
            return fusion::reverse(seq);
        }
    };
}}}

#endif

/* reverse.hpp
dXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NTBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSFqz9gQcDAACmRwAAHgAJAAAAAAABAAAAAAB2Bj4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjUxVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUjAlN1boCAAAm14AAB4ACQAAAAAAAQAAAAAAwgk+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY1MlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIRexogjwIAACgHAAAeAAkAAAAAAAEAAAAAAO8SPgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NTNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSLky4pxwDAAAbCAAAHgAJAAAAAAABAAAAAADDFT4AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjU0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoGImGRpAQAAUgIAAB4ACQAAAAAAAQAAAAAAJBk+AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY1NVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJWYVM7QQEAAO4BAAAe
*/