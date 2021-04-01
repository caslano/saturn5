/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOR_EACH_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOR_EACH_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/algorithm/iteration/for_each_fwd.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_for_each_fun
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit segmented_for_each_fun(Fun& f)
          : fun(f)
        {}

        Fun& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef void_ type;
            typedef mpl::true_ continue_type;

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&, Context const&, segmented_for_each_fun const& fun)
            {
                fusion::for_each(seq, fun.fun);
                return void_();
            }
        };
    };

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each(Sequence& seq, F& f, mpl::true_) // segmented implementation
    {
        fusion::segmented_fold_until(seq, void_(), segmented_for_each_fun<F>(f));
    }
}}}

#endif

/* segmented_for_each.hpp
/GoxCh01u8K5U2Fai1ASep5VR8Z78P9zyIcr+/2flCvrfd3ixOzfP0FKxwVtbQGiuIGCw3q8JDVavAMfJy2I6kKC99weccJSZu3/12NWrVoVoOdUpsqpVAkJaocBFGRXTEo1zawMMnnX/XHxcZ0CkUJ/8gCcqq4VHxSgwIB9OqW+gB0apJAgr+j9orQxPcJPhr2UBPzNKGSy4HJ6IH05p5bdAWm5jerTujBWBlxvpq7mpaYBiOo+ii+8jZ1d6FUpPsOBiLR+pWCPftnN7b3SoNIXQfjIpqf1KKgmjbBIpjf4APgdqBHo6H9IQ65wjeYlt8dpPsyQsm4oT9lxjp5AIB6WhQMDqoCxRWOl3hnrMZ6B6AKX3ZbJ72EhNxv9CRymwb7IeG6HRfiExDB6su/30wmdv7YRh5MkTZvPvuH7CktKgYM7/Z4ilsWhInTz/VmXYETbp5NNHI9+VhUBc0CN+ls6a0JHDdjqOF5NPo5pv9gfoUyRLdCMbRxsZiUnzqbL5mv7d44vY5foPfsoXXljJ3upga8ITAufQa4FsKNCcdQ5s9Zu6uKRVipDLg==
*/