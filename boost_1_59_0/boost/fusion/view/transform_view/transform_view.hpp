/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TRANSFORM_VIEW_07162005_1037)
#define FUSION_TRANSFORM_VIEW_07162005_1037

#include <boost/fusion/support/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/view/transform_view/transform_view_iterator.hpp>
#include <boost/fusion/view/transform_view/transform_view_fwd.hpp>
#include <boost/fusion/view/transform_view/detail/begin_impl.hpp>
#include <boost/fusion/view/transform_view/detail/end_impl.hpp>
#include <boost/fusion/view/transform_view/detail/at_impl.hpp>
#include <boost/fusion/view/transform_view/detail/value_at_impl.hpp>
#include <boost/fusion/view/detail/strictest_traversal.hpp>
#include <boost/fusion/container/vector/vector10.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct void_;
    struct transform_view_tag;
    struct transform_view2_tag;
    struct fusion_sequence_tag;

    // Binary Version
    template <typename Sequence1, typename Sequence2, typename F>
    struct transform_view : sequence_base<transform_view<Sequence1, Sequence2, F> >
    {
        BOOST_STATIC_ASSERT(result_of::size<Sequence1>::value == result_of::size<Sequence2>::value);
        typedef transform_view2_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef typename traits::category_of<Sequence1>::type category1;
        typedef typename traits::category_of<Sequence2>::type category2;
        typedef typename detail::strictest_traversal<
            fusion::vector2<Sequence1, Sequence2> >::type category;
        typedef typename result_of::begin<Sequence1>::type first1_type;
        typedef typename result_of::begin<Sequence2>::type first2_type;
        typedef typename result_of::end<Sequence1>::type last1_type;
        typedef typename result_of::end<Sequence2>::type last2_type;
        typedef typename result_of::size<Sequence1>::type size;
        typedef Sequence1 sequence1_type;
        typedef Sequence2 sequence2_type;
        typedef F transform_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        transform_view(Sequence1& in_seq1, Sequence2& in_seq2, F const& binop)
            : f(binop)
            , seq1(in_seq1)
            , seq2(in_seq2)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first1_type first1() const { return fusion::begin(seq1); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first2_type first2() const { return fusion::begin(seq2); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last1_type last1() const { return fusion::end(seq1); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last2_type last2() const { return fusion::end(seq2); }

        transform_type f;
        typename mpl::if_<traits::is_view<Sequence1>, Sequence1, Sequence1&>::type seq1;
        typename mpl::if_<traits::is_view<Sequence2>, Sequence2, Sequence2&>::type seq2;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(transform_view& operator= (transform_view const&))
    };

    // Unary Version
    template <typename Sequence, typename F>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
    struct transform_view<Sequence, F, void_> : sequence_base<transform_view<Sequence, F, void_> >
#else
    struct transform_view<Sequence, F> : sequence_base<transform_view<Sequence, F> >
#endif
    {
        typedef transform_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef typename traits::category_of<Sequence>::type category;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef typename result_of::size<Sequence>::type size;
        typedef Sequence sequence_type;
        typedef F transform_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        transform_view(Sequence& in_seq, F const& in_f)
            : seq(in_seq)
            , f(in_f)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;
        transform_type f;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(transform_view& operator= (transform_view const&))
    };
}}

#endif



/* transform_view.hpp
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
*/