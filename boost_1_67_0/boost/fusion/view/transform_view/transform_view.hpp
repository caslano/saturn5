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