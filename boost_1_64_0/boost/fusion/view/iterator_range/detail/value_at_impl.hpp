/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_VALUE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_VALUE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::value_of<pos>::type type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
iti+vibK1Xm5V1u1HPXGBsb8PgMx4WDI7iPKigSW64KHk5AFz800kykx56Tlkl4ZNQUhs74y4njjYhcJbYCxCWc0fGNtgEOhR6Mwenpe9sUowSfViA51MeLGXOPZuGKNKu9tAY3hAMvu+RJ4zGDZLGw3WWSEPDSxv5wNp/7nal9pEHdcDQr7Hby71SUE8/tkDWOGJwlhkGrbD3FsPvPNhSlsj+Lk7jHewSQrmE829SL6EHavUBYKLY1gOPVetnTb6k5dMflDa4pQWzNZcsiXOVmh0NiEUFyWy/W2jd105dAK6dU14aoNoqZahKdI+tw95VFkXsqGfIrD6fo0kvvN6p2Cq2auX+7B+OeIVBuon55fkZ9MfTcVS4FwvAbQMa8Kk4BLOHgGpfSUldWtTHsije2ElQBuDEgHzyal4IKWH8mMTeRmNnwECJKKt9/CPVEM7Q7cDsnR0l6W7YKFxD9Uwz31V9PqDgPJiF1HLfUljfCqa1hQGZEb3UHWozlsIVpzAjN0yxJuqVglG62nolmYxPxrpTo9zdlUviHmGKxYAY/Aj4OcwOGF6IaRuw==
*/