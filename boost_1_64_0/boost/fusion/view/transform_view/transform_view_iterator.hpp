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
PHFNdB4XnEdJwdY6Bvqt5GqSnbyCcy0PnpVbxJUIPbdkEHFD0uCRzlJvrU2DL5s/hWva7NHDGHNmTmpGTiuqy1ezm0zswYRp02bh6B+869/H5RiPbK7u/MCbFnYY2t85sHfi1Z7iKjKJvn8tKU5bifKHr5SjyhS0BlOjZuImWCuNQHBY1Rj445OddO7Sam0a4eIYJEARqrnTsttapkzqCZafzL7HBMK31URSZG/5W8HyqJWtEcezP8CoQqxNO19iGU9UobcZUunGTSZtjLPk5k7/KjJRg27b57ETDAArr1/LccUaBoZTbC6fi7H/YaCLYsYGLye+KS+qR397W77T69U1JkeuCmd8nMUOsMsry/oRNI8/pqi3MStmT+MpJKjqZwBBQxATLI09bTLMkEI/w04DxBO1CJgYZELFi16BMfNuN/RJ/cli08oLV4FdmyWS1temb+SyEHBs/0ZH6llaryhpbW1fDGbjVnxLTEFbx42yxSBY4eL7RzJ5cdb/Kj5aEBFV01yKEirDTsLEcWjuhSfef4t2wSQcAfOilS60dJYsDcBJSsG35z30ng==
*/