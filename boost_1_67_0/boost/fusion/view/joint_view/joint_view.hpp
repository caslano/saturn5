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