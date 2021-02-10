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
rNuuekbJ2NxnriVZZSkyVbjZNumdj7KNOd7dHHJBvlwYuyncArzpHI2ttsVp+AU8aXNrPIBLhj1ax6Dd7Z52b6suN+URdKLglY1nh1Wq21K5EG+v0Pfk3VE57r5sooAhsX4l1kpNLgfAluVOIThtRb4e0eEsPCxdFXTKEVpxvcvNHtBV4RcTcZZBLwssxAMT33z7+xEpbfI7EjNsv4pNWs0J1/3BW+lm4Jin68wp5YsMg1dwqdX8snL8lHNzt8sG354VnDAKbtI5S9xKUkYMcUllukwGzwqiCIujS2K5LrDHkCurENNO5QrlpizfxwBnEdFZ+sfu3SOJSz04PGz3eo5Pvb1d9WRMkLOHg20/sB2He/3pJ+9gn78wpz6KZiBauWdCwVLkF4F36G4AiC1/MAB6KskKNINVaO3EgEtcAQBOK9CyhVq8u/5oc7Me3eCNU1HYdSjYyHX4NrxZG35xK6CpAZWSnfOdfS3VOXtH/MMPeMXjXXxQR/23C/wnTPHhW/hPYFkfj2DrKkRVRL7ie10eaMHcTNmuuzqPYPx11YQqvtfpXxdMyCQZv+uETFrNunSbtVl17YHZCn374YGjqmJtpQiWez+Z/lPOnFiSGSFPqVXZp78rAjSk9Ft1FxfH1LwTMV3kqbggfqqi
*/