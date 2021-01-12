/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_VALUE_OF_IMPL_05052005_0324)
#define BOOST_FUSION_SINGLE_VIEW_VALUE_OF_IMPL_05052005_0324

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<typename Iterator::position, mpl::int_<0> >));
                typedef typename Iterator::value_type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
/SlS9k4IkbtTyJAGqSlrpfO4k4FOzrw9KnIWcNrHmUyb0NoFtrXOry935iDQyTd4C+d7wxu4lWr8K0IerhzcvUA0TfBWrmK+Q83h9sFN5ptMvF+xbqfaPsxhX4itKl5+yunzyr6JJuAZh7vY5lxRGbkoo38gVJ/J8Q4B8ShkHSan4P6dOL/bPzqf2HShmRgb/auMLRt7xc8eGfZsu7ZsPmb24BAz+1S90Lo2eXj33kFXElxE
*/