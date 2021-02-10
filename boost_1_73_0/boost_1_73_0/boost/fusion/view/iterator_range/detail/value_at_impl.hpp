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
CMuF+pDlykJ4LvQqS7SKS5lf79M5Onqm0ygpYiWOM50uMpMu2stjWvZAwjhxOZz2fhoNCC+O1AeYJIXtU+sEblogbfvwe7iE2ROo3fwRzl3WZWbE6246CKfT0X/PwnaPnqkU4XF0RPpEBurymZ+Vg04TZaG3VSdNXkrajTiLpZMtYa3+U4VOnKW5knHr6ItJrVMchFCScloJFp2zR6YQZL6vCZ4cT8S4SPX7QiHOXZF9ZX+7TabIFyotVuIvWIJqwDS4HbcYOc8oA1IDGEgXcI10SCfrTGY5/nkB6RstqZKAmyd/2xsGFxcvWkS+ltoR7dz4/NEpfstEYB+A4/2EcF6pWINXshFyjmDY4xFJ8ZFSUajl9O6CN63yGbE0qZ7Hvem0eu71+0G9/tP0t/p5cluv9/v9evntZfU4vZ/WJ25614Or6/rnr3e3weDR9eT2QkAO0ne1IuixChEEKJbifWFgL8BY4xKTQTCBNgPPc+uAx4vj22mws9CHsuyjCLmxUECafMv3+pdyU3usos1Yx+lzByDZ0eD6Mrjmy0DruV4UgC1TOE8En8DJq2x7OrgfD6rTCEhBAQQsVSkihSwhxRI5dZ7od1RRELZNUaPhNNhy2CWXM5bKmCtZ3T2GeoqWDoGaK15NydZ8ipIO
*/