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