/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_FILTER_VIEW_HPP)
#define FUSION_SEQUENCE_FILTER_VIEW_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/view/filter_view/filter_view_iterator.hpp>
#include <boost/fusion/view/filter_view/detail/begin_impl.hpp>
#include <boost/fusion/view/filter_view/detail/end_impl.hpp>
#include <boost/fusion/view/filter_view/detail/size_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct filter_view_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    template <typename Sequence, typename Pred>
    struct filter_view : sequence_base<filter_view<Sequence, Pred> >
    {
        typedef filter_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef typename
            mpl::eval_if<
                traits::is_associative<Sequence>
              , mpl::inherit2<forward_traversal_tag,associative_tag>
              , mpl::identity<forward_traversal_tag>
            >::type
        category;
        typedef mpl::true_ is_view;

        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef Pred pred_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        filter_view(Sequence& in_seq)
            : seq(in_seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        filter_view(filter_view const& rhs)
            : seq(rhs.seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(filter_view& operator= (filter_view const&))
    };
}}

#endif



/* filter_view.hpp
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
*/