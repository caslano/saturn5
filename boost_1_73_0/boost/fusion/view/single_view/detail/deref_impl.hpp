/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_DEREF_IMPL_05052005_0258)
#define BOOST_FUSION_SINGLE_VIEW_DEREF_IMPL_05052005_0258

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
        struct deref_impl;

        template <>
        struct deref_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<typename Iterator::position, mpl::int_<0> >));
                typedef typename Iterator::value_type type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.view.val;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
sMrA0d5igFb2rTzVZQettD0zWlxA8+SNRjnsTOVZc7tcuR5+eL+DSzeiP5M5esDDpfuTxZz+6RYWh7toMZYc7MStHGxPdybJ+U/C4+5kz+ezt3bwPd2nxOf3t3F40qVMsVe3JTi5pIkedzABH7uDCf6TIwRnLmffXj+4kuDSFUw421d5HOmWZTgvuBvhSNc1cNzZzeF7eJzBm9QJxc+Sfn9Pi0MHAnbfzOF/fbCAuw5i9854
*/