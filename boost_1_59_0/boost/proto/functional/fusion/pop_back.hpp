///////////////////////////////////////////////////////////////////////////////
/// \file pop_back.hpp
/// Proto callables Fusion pop_back
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_POP_BACK_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_POP_BACK_HPP_EAN_11_27_2010

#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/prior.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::pop_back() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::pop_back() algorithm on its argument.
    struct pop_back
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
          : fusion::result_of::pop_back<Seq>
        {};

        template<typename Seq>
        typename fusion::result_of::pop_back<Seq>::type
        operator ()(Seq &seq) const
        {
            // Work around a const-correctness issue in Fusion
            typedef typename fusion::result_of::pop_back<Seq>::type result_type;
            return result_type(fusion::begin(seq), fusion::prior(fusion::end(seq)));
        }

        template<typename Seq>
        typename fusion::result_of::pop_back<Seq const>::type
        operator ()(Seq const &seq) const
        {
            return fusion::pop_back(seq);
        }
    };
}}}

#endif

/* pop_back.hpp
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
*/