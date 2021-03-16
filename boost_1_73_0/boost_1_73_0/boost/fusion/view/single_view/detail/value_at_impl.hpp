/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_VALUE_AT_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_VALUE_AT_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion 
{
    struct single_view_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<single_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<N, mpl::int_<0> >));
                typedef typename Sequence::value_type type;
            };
        };
    }

}}

#endif

/* value_at_impl.hpp
lnvodd0MnpNfUlU1pUJIxj7w5f8uAvkwlY3i/8UbngZ8aTs6LGqvprynKac05RtN+a+m8F+9UpTmmtJRU/poylBNKdWUOZqyRlN2aMpbmnJCU77UlIua8oumhPpSpc+gbP5ZuarCP9ZaUYpqqsrUnMZKDnska0oXTRmgKaM0pUxT7tOUhZqyQSgdwJpRzwklA5U3hdIelU+E0gmVb4TSEZU/hNIWlTDzH+O1g6W0FcptqGQIpT8q/YXSDZURQsk=
*/