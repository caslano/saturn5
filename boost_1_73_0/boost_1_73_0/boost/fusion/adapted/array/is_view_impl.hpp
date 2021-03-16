/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::false_
        {};
    };
}}}

#endif

/* is_view_impl.hpp
2kBnsG4cgFl1T+eAqz2MhN4oZduoy6dKsLBgKwW7RrDfC/amYFS2iGMgZbubfqFWyra+HWVb0VAXXtyG+01Qn2N+2PAjy/iEOO+bBrG5F7guS1a+p5jyzTfl28uU71op37W6jK4QrEawtYJdK9ibgr0jWLz6uuqZvU6L6uuDceMbfq2pr3cnVkTbTk8nuhY0Yaf6eMbRXv11Ze4P1V/tnCGzFjy5BQU20akimQq7P4s1h1ezWIX9XRarsK+aCb0=
*/