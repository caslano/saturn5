///////////////////////////////////////////////////////////////////////////////
/// \file pop_front.hpp
/// Proto callables Fusion pop_front
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_POP_FRONT_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_POP_FRONT_HPP_EAN_11_27_2010

#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::pop_front() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::pop_front() algorithm on its argument. This is
    /// useful for defining a CallableTransform like \c pop_front(_)
    /// which removes the first child from a Proto expression node.
    /// Such a transform might be used as the first argument to the
    /// \c proto::fold\<\> transform; that is, fold all but
    /// the first child.
    struct pop_front
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
          : fusion::result_of::pop_front<Seq>
        {};

        template<typename Seq>
        typename fusion::result_of::pop_front<Seq>::type
        operator ()(Seq &seq) const
        {
            // Work around a const-correctness issue in Fusion
            typedef typename fusion::result_of::pop_front<Seq>::type result_type;
            return result_type(fusion::next(fusion::begin(seq)), fusion::end(seq));
        }

        template<typename Seq>
        typename fusion::result_of::pop_front<Seq const>::type
        operator ()(Seq const &seq) const
        {
            return fusion::pop_front(seq);
        }
    };
}}}

#endif

/* pop_front.hpp
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
*/