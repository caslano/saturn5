/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOINT_VIEW_ITERATOR_07162005_0140)
#define FUSION_JOINT_VIEW_ITERATOR_07162005_0140

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/view/joint_view/detail/deref_impl.hpp>
#include <boost/fusion/view/joint_view/detail/next_impl.hpp>
#include <boost/fusion/view/joint_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/joint_view/detail/deref_data_impl.hpp>
#include <boost/fusion/view/joint_view/detail/value_of_data_impl.hpp>
#include <boost/fusion/view/joint_view/detail/key_of_impl.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;
    struct forward_traversal_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator
        : iterator_base<joint_view_iterator<Category, First, Last, Concat> >
    {
        typedef convert_iterator<First> first_converter;
        typedef convert_iterator<Last> last_converter;
        typedef convert_iterator<Concat> concat_converter;

        typedef typename first_converter::type first_type;
        typedef typename last_converter::type last_type;
        typedef typename concat_converter::type concat_type;

        typedef joint_view_iterator_tag fusion_tag;
        typedef Category category;
        BOOST_STATIC_ASSERT((!result_of::equal_to<first_type, last_type>::value));

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        joint_view_iterator(First const& in_first, Concat const& in_concat)
            : first(first_converter::call(in_first))
            , concat(concat_converter::call(in_concat))
        {}

        first_type first;
        concat_type concat;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(joint_view_iterator& operator= (joint_view_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Category, typename First, typename Last, typename Concat>
    struct iterator_traits< ::boost::fusion::joint_view_iterator<Category, First, Last, Concat> >
    { };
}
#endif

#endif



/* joint_view_iterator.hpp
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
*/