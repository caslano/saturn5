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
Z9MZuykm2sP1afC2rbxhzjJS4fWPMV7eH2z75Jv81mzPHQm7C5Jq35j+ZQyY6rqL/SDXTJxrvnU6jqkv2MYPsuy7nmgK+Hh4e9tFPnAJsPtTcXe9G97+mywy0TH9l+DDd1WJ6ky/kMnrFbmD93b+pQ+y4nQdE39wa+Ba8rntM/nWIBM/Kp5ekpa88tMMMUlzfdL9aJK9Jb9nBuo+1jjxa+Y0ro+YmI4APpVs9pLZ80oZiU22tpeHSLxgfLYnd4D/B+dVK9uc873OaacmRau9TpjxNGbqGsIcdIVuSpXs6xStNNRVPnLoaAFO7Kv8Um+Gfx4D/hVkJB50JNykv6OHg15BtGOV3gyZ6EHRQC6f2dR9f4cYwv0ahfzJLajmwmVAR2mh2LrN9HMboAlB9GHB4CZxfI49auVf4T3ASw5iekq37pQP7dkmm9BJI5Vxj+98U34u5geMAbaH/C5YGOPljcdEJ1bSBPB2rMn/ny/nj+wMiIAmjOJ/ld/xzfQzKM1R1pQOyzqK4364X604LDG5STqGYVedLv5uLl/3bPno1akDpP0W8AWN0n+edDUql0D+Cl+DflNOx5zJB5oVv7wLZ9nv/fs37V8twlyzMHbf5Ae6/rbo/laKRIzLoA7XyQ5Ur5Gvf7Z8dBuQxadjBOZV81+RySL/VwfZLfQ8/cy17vPT8g3Plo/ctWeh0CE9RI6v8/3w9BysJRxhoHP6
*/