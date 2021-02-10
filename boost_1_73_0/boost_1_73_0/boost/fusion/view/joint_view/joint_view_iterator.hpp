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
GL/FrywOMSovD3S76o2mAx9daIPQWzGIfK5x44brmJKbo62EDtCRJiw8VvRigGsNwytp7BGTKgCF0swcUkomZO9Ng5mppikKOUjmjqQWvY26kjW1GejmrC1UvKvyXOqkpqPGl6MMussmraBjtkXA5cp04yJQhuIhvSOe+xbeO0WeK58fcJLJmwFPMxI3CYwGZY5rUnhHJYaWnVLAlNWVuNtZL43lOkcyT2qIPhXDsZBxzKHFRzj5qf8tZ8ZymJH+Lg0pOMPsi9QiwiEMIZI7EkU98hajStnbBTJOVYk+gx9if/4jY8g8L18y0XFtkIk1Tm8BqVqimtGtPIWWhQKxucfQRA0K9jhSo4Rg2XdXJ6fyYCNBPjaUelac9DpDstKfKjenjSDjnrdbd6SAnazIATzKb0HfaoLfM/TXHC7+bw6v/lcOVevr95iLTNZyw5hMu+3oe95CWvNgxCMzr/xtH4fQygcVd3dKPjuB14nFjJCQSiqVjgNvLerPnuimyZrfaVYh3qjWuXJ5yG+ptmpMCduR9bSn1UNV57w+jfLmx7zQ2Drz+ZWtzGmCLGdAQibJby7sxjq1aj/S4F2KhiEkCdwxEJttheHXmnOYhHKeY/wcPTeSeK2TOJJ5/OVXavjQ5ERvmS3psKZWnVsn
*/