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
eJdpgE7q+GRVu9X2aCw6k8cVBvSQ1Kb1/S5ICRPj+FS90EQTa6O1QLRdd+SpQ/Q5dkhRwXGO5r1M/t42Wbq9wQEpcRlf3vRzS8U3DRcmrRZam9Y920Z1dnVv2BeE9/6IXgbAn+RFMUBd+Rpsmlz9DmdlsJe8dATlStdO84/iuR7kyv4cytibOMy37U6D0J/4jhcw5yybXfdnclIi6eZD0p6he+XwDXQibI4C1OzkbniJRVu4fsxWHtWMqkC/WOK3Lm7sTChalc1qXwDNvUTvNxmq08ZszYI5jUqUA009Xe6MC+PbVy/yEHZ91wUbcb/vjIOem2nv4lJkWmgQYT2XLv7/hSsXRWJUTsT0P3+tXO9v7vLKs9gHKozwL3Le6+7N/K0cH3G1pqd0wEkO5ylRwHhOqlTu/dzrOCwzDUSC8OQDc/WDRj4mkH701otADNMMs8qxHL1R8E+FAdWgahSy1dxzsMkZEo5e+nhpbXy0X1uDUtveB/B6BdZ1cBIIgecDTHvcy/IFzB2H130BHRjdtzwEta8UQLwbqF8v9mBwU4uOCsLgfDyOvpbloA==
*/