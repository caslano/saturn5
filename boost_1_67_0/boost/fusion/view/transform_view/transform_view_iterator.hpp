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