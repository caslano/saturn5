/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TRANSFORM_VIEW_ITERATOR_07162005_1033)
#define FUSION_TRANSFORM_VIEW_ITERATOR_07162005_1033

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/view/transform_view/detail/deref_impl.hpp>
#include <boost/fusion/view/transform_view/detail/next_impl.hpp>
#include <boost/fusion/view/transform_view/detail/prior_impl.hpp>
#include <boost/fusion/view/transform_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/transform_view/detail/advance_impl.hpp>
#include <boost/fusion/view/transform_view/detail/distance_impl.hpp>
#include <boost/fusion/view/transform_view/detail/equal_to_impl.hpp>

namespace boost { namespace fusion
{
    // Unary Version
    struct transform_view_iterator_tag;

    template <typename First, typename F>
    struct transform_view_iterator
        : iterator_base<transform_view_iterator<First, F> >
    {
        typedef transform_view_iterator_tag fusion_tag;
        typedef convert_iterator<First> converter;
        typedef typename converter::type first_type;
        typedef typename traits::category_of<first_type>::type category;
        typedef F transform_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        transform_view_iterator(First const& in_first, F const& in_f)
            : first(converter::call(in_first)), f(in_f) {}

        first_type first;
        transform_type f;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(transform_view_iterator& operator= (transform_view_iterator const&))
    };

    // Binary Version
    struct transform_view_iterator2_tag;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2
        : iterator_base<transform_view_iterator2<First1, First2, F> >
    {
        typedef transform_view_iterator2_tag fusion_tag;
        typedef convert_iterator<First1> converter1;
        typedef convert_iterator<First2> converter2;
        typedef typename converter1::type first1_type;
        typedef typename converter2::type first2_type;
        typedef typename traits::category_of<first1_type>::type category;
        typedef F transform_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        transform_view_iterator2(First1 const& in_first1, First2 const& in_first2, F const& in_f)
            : first1(converter1::call(in_first1)), first2(converter2::call(in_first2)), f(in_f) {}

        first1_type first1;
        first2_type first2;
        transform_type f;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(transform_view_iterator2& operator= (transform_view_iterator2 const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename First, typename F>
    struct iterator_traits< ::boost::fusion::transform_view_iterator<First, F> >
    { };
    template <typename First1, typename First2, typename F>
    struct iterator_traits< ::boost::fusion::transform_view_iterator2<First1, First2, F> >
    { };
}
#endif

#endif


/* transform_view_iterator.hpp
W2yQQPygnQEwLulzuckIV2RuWJR3ya6NkewsUVUanti8CJmfmsmPiHdx5QXNK5GFarZLtWY0w1VLsdciyPFsVC/73Nnpnjg+BfPt5f5fA/Fn811siy6eR2AaGo+6vlmrVzgPdlP7BoV0bpk8oNSMQoWNvA8LPEfEt5v96GFR4fKgcWpwZk83Nzcb3n7CFLzKoMUrpbwqVlpRoPIaveQkRBhNZiypKrAujP3pXPMmuz5T9+9wPKl741WkGTA+oyVrlAFDzThWUJdW8RXDojqsOKYW/1G6PcoSljcTyo2yxaRu0kioOmKqNk/HjmUvPt+Hlaxpa08XeWlQ9aAIOwzSx2WY+5lerZueUHkeRs4SjFjryWXJaTNKu40YMvTWURYDPXbEbHDAg9BawAYd88VIZG5a3xXdSkqr3QZuDz/xmirEoY59zeW29G2k1qQ1BTqYqNAKBKqFia7MJW6LEvMgrhAeN1GZIq2py5eo4+mcbB7G3ntK85vivWyorV1TRQxVnY5mcZ1gYFKgAEZcYbCpTzuYrRV5UNJJ1iMkIx+6rDkR30JeqQ5jHglFh45WXeYkiYi4q28xtcdP6RXwxULwLfLZVKOTY3JvfFW1SgYnXjurm3YSThvVYCopIjBNPfHEDjqu6qDLsVWkk7MB
*/