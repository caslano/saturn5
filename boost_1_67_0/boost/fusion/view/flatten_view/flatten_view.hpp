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