/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED)
#define BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/deduce.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/config.hpp>


namespace boost { namespace fusion { namespace traits
{
    template <class Sequence> struct deduce_sequence;

    namespace detail
    {
        struct deducer
        {
            template <typename Sig>
            struct result;

            template <class Self, typename T>
            struct result< Self(T) >
                : fusion::traits::deduce<T>
            { };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template <typename T>
            BOOST_FUSION_GPU_ENABLED
            typename result< deducer(T) >::type
            operator()(T&&) const;
#endif
        };
    }

    template <class Sequence>
    struct deduce_sequence
        : result_of::as_vector<
            fusion::transform_view<Sequence, detail::deducer> >
    { };

}}}

#endif


/* deduce_sequence.hpp
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
*/