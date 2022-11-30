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
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
*/