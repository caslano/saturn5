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
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
*/