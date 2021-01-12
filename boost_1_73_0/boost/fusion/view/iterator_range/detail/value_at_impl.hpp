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
haHbbxlGzb2eLMsR2DBj5YNtHRzqHVVejpMiDRcxLpGfZpDZMrATRS3PqU7ZMfindgJlsWNOPe3sbXk+2k0HvTA250LwzPjonGIXYVXN1J38qYLHs0o/T0MX87sDlWrOTUw3bAbGKOZ3v+Z8e1IfA0uZeeDKsD7l5686eSqzKsHh/1wje/z8UOsP2vF57g9ysPXkBpieiHjpK2iMbg8ZZr+lCwwsAvvkhfD3X5tj9yXYwU78
*/