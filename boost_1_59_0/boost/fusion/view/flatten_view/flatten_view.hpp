/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_FLATTEN_VIEW_HPP_INCLUDED
#define BOOST_FUSION_FLATTEN_VIEW_HPP_INCLUDED


#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/flatten_view/flatten_view_iterator.hpp>


namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct flatten_view_tag;

    template <typename Sequence>
    struct flatten_view
      : sequence_base<flatten_view<Sequence> >
    {
        typedef flatten_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;
        typedef forward_traversal_tag category;

        typedef Sequence sequence_type;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit flatten_view(Sequence& seq)
          : seq(seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }

        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;
    };
}}

namespace boost { namespace fusion { namespace extension
{
    template<>
    struct begin_impl<flatten_view_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef typename Sequence::first_type first_type;

            typedef typename
                    result_of::begin<
                        mpl::single_view<
                            typename Sequence::sequence_type> >::type
            root_iterator;

            typedef
                detail::seek_descent<root_iterator, first_type>
            seek_descent;

            typedef typename seek_descent::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline
            type call(Sequence& seq)
            {
                return seek_descent::apply(root_iterator(), seq.first());
            }
        };
    };

    template<>
    struct end_impl<flatten_view_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef typename Sequence::last_type last_type;

            typedef typename
                    result_of::end<
                        mpl::single_view<
                            typename Sequence::sequence_type> >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline
            type call(Sequence&)
            {
                return type();
            }
        };
    };

    template<>
    struct size_impl<flatten_view_tag>
    {
        template <typename Sequence>
        struct apply
          : result_of::distance
            <
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
            >
        {};
    };

    template<>
    struct empty_impl<flatten_view_tag>
    {
        template <typename Sequence>
        struct apply
          : result_of::empty<typename Sequence::sequence_type>
        {};
    };
}}}


#endif

/* flatten_view.hpp
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
*/