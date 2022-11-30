/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ZIP_VIEW_23012006_0813)
#define FUSION_ZIP_VIEW_23012006_0813

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/view/detail/strictest_traversal.hpp>
#include <boost/fusion/view/zip_view/detail/begin_impl.hpp>
#include <boost/fusion/view/zip_view/detail/end_impl.hpp>
#include <boost/fusion/view/zip_view/detail/size_impl.hpp>
#include <boost/fusion/view/zip_view/detail/at_impl.hpp>
#include <boost/fusion/view/zip_view/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/algorithm/transformation/remove.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>

#include <boost/config.hpp>

namespace boost { namespace fusion {

    namespace detail
    {
        template<typename Sequences>
        struct all_references
            : fusion::result_of::equal_to<typename fusion::result_of::find_if<Sequences, mpl::not_<is_reference<mpl::_> > >::type, typename fusion::result_of::end<Sequences>::type>
        {};

        struct seq_ref_size
        {
            template<typename Params>
            struct result;

            template<typename Seq>
            struct result<seq_ref_size(Seq)>
            {
                static int const high_int = static_cast<int>(
                    (static_cast<unsigned>(~0) >> 1) - 1);

                typedef typename remove_reference<Seq>::type SeqClass;

                typedef typename mpl::eval_if<
                    traits::is_forward<SeqClass>,
                    result_of::size<SeqClass>,
                    mpl::int_<high_int> >::type type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename Seq>
            BOOST_FUSION_GPU_ENABLED
            typename result<seq_ref_size(Seq)>::type
            operator()(Seq&&) const;
#endif
        };

        struct poly_min
        {
            template<typename T>
            struct result;

            template<typename Lhs, typename Rhs>
            struct result<poly_min(Lhs, Rhs)>
            {
                typedef typename remove_reference<Lhs>::type lhs;
                typedef typename remove_reference<Rhs>::type rhs;
                typedef typename mpl::min<lhs, rhs>::type type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename Lhs, typename Rhs>
            BOOST_FUSION_GPU_ENABLED
            typename result<poly_min(Lhs, Rhs)>::type
            operator()(Lhs&&, Rhs&&) const;
#endif
        };

        template<typename Sequences>
        struct min_size
        {
            typedef typename result_of::transform<Sequences, detail::seq_ref_size>::type sizes;
            typedef typename result_of::fold<sizes, typename result_of::front<sizes>::type, detail::poly_min>::type type;
        };
    }

    struct zip_view_tag;
    struct fusion_sequence_tag;

    template<typename Sequences>
    struct zip_view : sequence_base< zip_view<Sequences> >
    {
        typedef typename result_of::remove<Sequences, unused_type const&>::type real_sequences;
        BOOST_MPL_ASSERT((detail::all_references<Sequences>));
        typedef typename detail::strictest_traversal<real_sequences>::type category;
        typedef zip_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;
        typedef typename fusion::result_of::as_vector<Sequences>::type sequences;
        typedef typename detail::min_size<real_sequences>::type size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        zip_view(
            const Sequences& seqs)
            : sequences_(seqs)
        {}

        sequences sequences_;
    };
}}

#endif

/* zip_view.hpp
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
*/