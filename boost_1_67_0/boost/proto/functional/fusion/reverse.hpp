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