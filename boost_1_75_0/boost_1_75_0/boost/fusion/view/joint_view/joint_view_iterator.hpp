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
ofY58nW96EqxPEgYJ0qAt3iMFT0/c1RO/8xYnLd5J9DzKceg/mmIf44ANN48oytsdJiOynQHz42duzKfQh8MLVxb7Bco+6VQFNszaNNn3lP4HmMU+XcK+Xco+TeL/OsvO0x5vv7qV4aHDk9ZPXrDol4X3XrL9XTx9WTZhs1Y/dD7LMcS9X3W0SXq+6ykeer7rHHPqu+zFi9S32etmCveZ11s+rnq+xwy/ur7HDye6vsc9FTf5+Dy6vscXF59n0MmoNFz6/iG6vsbMp4Kvr/R8X3V9zO43Pf7mYrX76skrrKPx9ev0u+pNa9RRKKj8Tqpvi/CkAIyuHb0CUfa7WJTxkJd3MX+SB8zAuD4jHJ2c1FfDh9Z/pBbJHtyoqRz2qfKileLo0+WNcuJOBMWsZlfAXPU+jagK2hn/O1kikvrJi1pRvpcQCMHy3lY05TRRHDE2jwUK34kCPb0m0n87PPJexiPXcyeSTMZiJmpq0p+Ad1K9TfwGmsefcstQHGcRsg3xxNmmXUpvFUZwTPRivH7S5W1VMwXZX3PJM90aCXvL+t46ua+9XHW/bPilBqm+rjitJ0YUx1nEFdHF8f5GOh+pXcZYuYi/L18UATkLAk4Gj4cQR5aGwfa6RhvWER0mSq4pVlX/v6t6PyF1qvMzkp5tVtJGYt0+YsY1LM9ffkGdxjBJRfRapdwoxVY+9E/cFf3Yj+fXoayvW/wtntf
*/