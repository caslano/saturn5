/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_VIEW_07202005_0836)
#define FUSION_REVERSE_VIEW_07202005_0836

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/view/reverse_view/reverse_view_iterator.hpp>
#include <boost/fusion/view/reverse_view/detail/begin_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/end_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/at_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_at_impl.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_tag;
    struct fusion_sequence_tag;

    template <typename Sequence>
    struct reverse_view : sequence_base<reverse_view<Sequence> >
    {
        typedef reverse_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef Sequence seq_type;
        typedef typename traits::category_of<Sequence>::type category;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef typename result_of::size<Sequence>::type size;

        BOOST_STATIC_ASSERT((
            is_base_of<
                bidirectional_traversal_tag
              , typename traits::category_of<first_type>::type>::value));

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        reverse_view(Sequence& in_seq)
            : seq(in_seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(reverse_view& operator= (reverse_view const&))
    };
}}

#endif



/* reverse_view.hpp
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
*/