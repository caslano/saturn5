/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::pos_type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return *i.pos;
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
zCRwhIC8nActk67Hh9OO/wcLsrOPLAW/tHgj3AcPgggKLqr7apJAb5KZLXSAwvhBf+bdh50XwoT5dVbNpPNTC8ONH36wScYkCmugyFDQ7xco4651UvQY9i0IqVFeV3YYBIC3QSccFWg4RDqJKn9dynJsYSinwd1gkCrbXhgCkUICcE4vLb8FZCvhpH5oT0yj2MoBHP6JZRdLATv6LOhVkHyfcmRwtQmYnsxDSTWsQ/sfL+wCLqRyYYVa3m5bwR5UvmN76M6hxAflYQvn7kc+qsuyHLT2A0LNChyPdHB9qB4I+8NUvoQ1nfmNugtI9iZX2EfWuYOFpihGQvRYL4bD1KRZTDUZryeEf5rzoJ5DGtrpHwZKZelP7igjqmfMvxaPIiKwsXzSFCCe/6xb9EXonGpPt9qwcZHpQ9fl9w0cSFDqyJmy+5iIPvPwHOnsWrlx6TpdzIyTiWAUyQJ5vlNTNWofRzLVeseJxXkLvAduiLXuuRJNRdjRtBum8qVWRKhUdDaTYjGillBdap3ayRWXChBdyxVjhIR650okmLSxEzXOHDN9SCCJgvgryg==
*/