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
tfFqowTkpBSsck2VaQkK5b4R0K+mqmZI4LO3862tZjIju8zzks+fREOdcAF7noOiVLGrGMWHu8ahauUvqkydjwHcktCmjNrxn1D3BKZFEOKw2q6ED8tDEBZT6DjdNN14l8fjGOxpJfeUGkqvWSpEa1GhyuqW0LUFZcIQaYJW0IXPLRzP89CfDkJ+dg6q2cbnGrbKJUvdUCdFF75EkXQCUV0VJJ1t8/d0L76yFS/yFREnmk4otp9+c+fpif+Dv/HR7YaPS8XW8sJPXItZrcpVReXsfaAFDu/5RredJQ4d5IOaTYnXVh//DNjuG63F/BUO36oeTUotkugSN+nSn5fJq16IKu2NrnbbyWDHJR8lgChL+naE2b2yrlKFm1PJI1JJ1R5RyvoyHtd7PDXqu2U84CNCnLC2YHTBmGSCbFbRaKhfz2EOGKaylEp7Myx1fMwVDDc22DP1Xaw+LHSryraEm03VXK+MrRm3gn9mD4j+kkc1EsXyhnce5KeWydDTFq4aqKIEQRffXfcdyTh81icJg+Hj/naEyp1HpsUWYdHvhqUaT4jtXEBhPhctHt1v2yndHrXD+j7mOqEQJaOjHoM8+ZOEi3/5zg9RtwN/EmXefUV2PrHguG3N9XE+7831rSagO/4KDMnvB31x1kBActRmazF6xMeR+dUvgx0rAUlfPY0e5wfUj4inAYYjWzFy6q7xFDuMEc7oXUbbdOgp
*/