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
oh67SwN7Vl6jCNNW0pMO4C4Ap7AG3bG5fNZjVEFBmxh/NSp/sOrkUN+HTdi9DMvl/KE/6VzqwxUn87mdPV34p3WSyvOUPB2rzNZbota/8Wx055sbnKlMc9DnwNvA1jA3EH6L/P3NiuxO7qJGuQd2t9T9dXaazlO4altl8oqLfHBsuUI5aedu8myGMF7e/Aygq7AfrbRWvh51uSrI34N0cT671P3YopC/OwTo8C7AtYKcP9db5cuOR0aY6VPGn86yeXRawIhFdw85VXKE+XqDfHq0APPN3FvVHvEq/u4ccOX7li7K7pzr7SlmoO5KvmlQLpLzx/2w5zbKFyMjWEi+/LzQt1/JqoLXc78Vc6xuymPVepPkZEtZnSFyfv4yyP+vR7xKVdJnw/atDtAsMCYt0iKFvsvXK2ILY/5gjLZnCd9/L/3ifl0YwkDVuYuhztarFH92wYTaLmZZ4iaoP9+k9820wjyiKZjDhHXIn5csVaGICqSv8T7kyHhevM0+6Ey1X0fX8bkeXJfwMTleNX/2Hubz2LVHoNO6ZGUqeat7Zj+YTWM+DXdkTGG+YZAInHUqo0WA1aMyBgtXvh4atjhyVWV0x/5WeqdoE/LjYF8GeUVwNFSX56Vy1OhEFIqG0feeb1XKkhgnUysu3xSX5vJhXV1BoEI1az9anWdPX4PZhymsu2LLOrNvYEX6tIbzYfD33WQ3x7CPTnawC6b2
*/