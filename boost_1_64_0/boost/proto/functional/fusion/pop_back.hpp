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
vGHLMw7tCm2oAPXUrOSyCufXnIWibCbHqXUml3q4hh/f6+S3YWYMdS/+OFXjgrCOha10DqoS7+xIQRXC1XxTKktvgNbsWcJjM24/aeVjDm7t20zBkL5GgIX0RHPtbHDOzJ8jLUyw50k050Ag2KOx3Q3fcL9WS4HasT8De4npzBuDxqv+/MTewPmf8ts46CBaWGqFo+9w+oLg8sbSmFP6I9K341rCL8RGEMgP264CcZ7oWr+sBwnV6vohB9Ry6qSGzqahFSqFLZ6qb3Akd1IKc5P3ZG6YYvtzg0ATXKVLW5cE4jIleayTkc7LNHhSKLcvMbNvw+IiSg1Pv4tKkl9vzB19dvJTvL8GE0/1IAffA0f5CwR5ofBep1TEowUo4THaAXcXWVtQ11xGLK0ZyQmWyy1ixUkgbtt4k6X30qB026QiDuhPgPFIX3hiUYo5m41XvRHtB/nDUzc4Q3Us7e70yWQl6m3oqqIyLyrT38P64RsxWMob0Fj0qwrQftjkKAvYHV/qrQAXS1aPIIZOJbZ6n+gNQDKI2ApEOH9JKDN1NY0VKWHndIi78eJEfg==
*/