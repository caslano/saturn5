/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ITERATOR_RANGE_IS_SEGMENTED_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_IS_SEGMENTED_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    template <typename Context>
    struct segmented_iterator;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl;

        // An iterator_range of segmented_iterators is segmented
        template <>
        struct is_segmented_impl<iterator_range_tag>
        {
        private:
            template <typename Iterator>
            struct is_segmented_iterator
              : mpl::false_
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator &>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator const>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Context>
            struct is_segmented_iterator<segmented_iterator<Context> >
              : mpl::true_
            {};

        public:
            template <typename Sequence>
            struct apply
              : is_segmented_iterator<typename Sequence::begin_type>
            {
                BOOST_MPL_ASSERT_RELATION(
                    is_segmented_iterator<typename Sequence::begin_type>::value
                  , ==
                  , is_segmented_iterator<typename Sequence::end_type>::value);
            };
        };
    }
}}

#endif



/* is_segmented_impl.hpp
UsucUCfMQpUI/xRmMYI+b51zMXk6zTU1/VpYwhqIz+XNRXpMFsKgkgDxSHlxDC9str+iSy6RhOiOjwKkZXRgkN2mLGjlOkIA6XA6TJTwiT8FP4PtONkVEIX29z8DAmsvM4AxhZXMLdpaB8umd74gC5XdSD8d98016xrcBdwEKQyYn2ljlo1o+VbR/LAwNOGbsXaHOpvE228g8vk0+vnai6pWgmI6n6kt9ALP4Te5e2rC8Bc24u1MPjQtvAmFB/uSH3GnIuFaLLOuBzbeUKDZ8fbeVoFcLCxIaQg1if+K/o9N5QPYPxVHraWNop/sXDoe3cFI1n+RlOYXsLS/McAC5W7zhMYZLHQ9OvS0DuS2r0PwZ8xmkGv9/xoE3QHMV4aJV5BmSL8duHsRB0Hl+diEJ4TXvdj8CRJtHpg89M9/aiho1nRv7C/SzZWOyB/5hWa35OX1XLhyUIMeTRz/2b8pQcg7+p6ShFy33whWUhZFELkYvoOR3ZiSH5G2/xTZSRudymEJDrdEfo8A74Q99PU2nUOAeR12F/lAAgnT3//z3p1gWACL6YGRScFzSw==
*/