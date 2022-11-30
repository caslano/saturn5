/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOINT_VIEW_07162005_0140)
#define FUSION_JOINT_VIEW_07162005_0140

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/joint_view/joint_view_fwd.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/view/joint_view/joint_view_iterator.hpp>
#include <boost/fusion/view/joint_view/detail/begin_impl.hpp>
#include <boost/fusion/view/joint_view/detail/end_impl.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    template <typename Sequence1, typename Sequence2>
    struct joint_view : sequence_base<joint_view<Sequence1, Sequence2> >
    {
        typedef joint_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef typename
            mpl::eval_if<
                mpl::and_<
                    traits::is_associative<Sequence1>
                  , traits::is_associative<Sequence2>
                >
              , mpl::inherit2<forward_traversal_tag,associative_tag>
              , mpl::identity<forward_traversal_tag>
            >::type
        category;
        typedef mpl::true_ is_view;

        typedef typename result_of::begin<Sequence1>::type first_type;
        typedef typename result_of::end<Sequence1>::type last_type;
        typedef typename result_of::begin<Sequence2>::type concat_type;
        typedef typename result_of::end<Sequence2>::type concat_last_type;
        typedef typename mpl::int_<
            result_of::size<Sequence1>::value + result_of::size<Sequence2>::value>
        size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        joint_view(Sequence1& in_seq1, Sequence2& in_seq2)
            : seq1(in_seq1)
            , seq2(in_seq2)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq1); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        concat_type concat() const { return fusion::begin(seq2); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        concat_last_type concat_last() const { return fusion::end(seq2); }

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(joint_view& operator= (joint_view const&))

    private:
        typename mpl::if_<traits::is_view<Sequence1>, Sequence1, Sequence1&>::type seq1;
        typename mpl::if_<traits::is_view<Sequence2>, Sequence2, Sequence2&>::type seq2;
    };
}}

#endif



/* joint_view.hpp
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
*/