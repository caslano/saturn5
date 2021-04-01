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
z5x2M7CDQCZWfOLZyOa+XOviYFJqAdGexcpobbMwgRHgwSKwml/yL+TKH6cFgqTTEFmLffd+0W0SKMVmNswi9c2ElUjonj9u5T5u7CWQ1wB77F88iqdFKRp2QEP/KJ1FTuwRgxS6LjO02A7k6orJ12mNR3gsIrq0xeRdPAUlKQTXKlVTE2sLeQCVESr1CZ0fFDxqGJOrqWRnizxAS/FZA7ZQJ1sMksRhjYHoIfh7b44s2TDOW1YxyiLYsVjTfAVlEHmmrqqGrJxtruLJbYoGryxpyxGYW7HftVCv1VKzwG2bm6hmY6hsqK5OwBSE/qC/qUQUP+RJKRKC+vk33Apw/ylmFQKflokST3MsQ4lDeHDR/H+sNDJeRxnXGbJx4bT4DihfTOoop40LVNMs9pIjoTuLwXP4d6Gc9gQndJ+t3NMfnYcpNtpgU3v20OrmB8uQNYQFOqpFEBlDiPabYciZne3hGxXGglgAhOXE8fUpWdS3m/3OvLCAEsBMHzLO/DwCC0EHxNr0KbU8ta6r+hRWb2PwgromW0BfwKUrtd32/2mLfZDgu6VBdZUCkg==
*/