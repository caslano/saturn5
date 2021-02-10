/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_MAIN_10262014_0447
#define FUSION_LIST_MAIN_10262014_0447

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_to_cons.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/support/detail/access.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename ...T>
    struct list_to_cons;

    template <>
    struct list_to_cons<>
    {
        typedef nil_ type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call() { return type(); }
    };

    template <typename Head, typename ...Tail>
    struct list_to_cons<Head, Tail...>
    {
        typedef Head head_type;
        typedef list_to_cons<Tail...> tail_list_to_cons;
        typedef typename tail_list_to_cons::type tail_type;

        typedef cons<head_type, tail_type> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(typename detail::call_param<Head>::type _h,
             typename detail::call_param<Tail>::type ..._t)
        {
            return type(_h, tail_list_to_cons::call(_t...));
        }
    };
}}}

#endif
#endif

/* list_to_cons.hpp
DF6ihZDsBnfuQyJXMwUyhUcqt6V5jixecys9+Ym9eC+ZkUw4H3tnWtaJDGo2hiihGiMD553wFPu12bGJ2WgbjQYNNiPUHZUIjYkcySMKpI17qyuo9CLbBuzkYLb6lsZ/tlg4CgkC3v3UJ4MjjdwuTkQS3JAUx6UEH/QdiYQW7T7Qe8NaKalDzP+VgbFQLRWVLQsh2pDVP+XHIMiCcORBpodY7gPX9sC4GwcPWpslOi54qiZZx5B/wPNcvYgOevaenWxD7bP+x+tPvcmkP542tQNWw+krjD8wSI7lBx2llfBdDwJDhyErmTUoednO1iQMee/3bHh9cSEtfhGBJwU/5PB7kZKELZSh2M+Ck50QgHko+4K5t5lLcNg7dy5Gpz0IjiGHB7tH78+T8GUqa4FYUZ1EgRuDaWubPc1dLM7UhCmuh4Mf2gxXdSbTcb93SaqyXzLV459a7B071va88ZRtmH63quNJbceS5AqokE9CLl5P0Zt8HZ46k+tTrJmRsI/kSQLl0jq0wQozfJ9xz80QRWOxECGk5BDiEmRK6AfAmz0osNNgSfrsZzQclBVnnD3QnPyee5kKoG2NNYu+x2UhMGpaHkLmmUW/UaM0yqWe4Bf94K3k75IqN4wUVILc3BWYVhEVtR5SumAz87Gd
*/