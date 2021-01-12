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
c9JegmClt3Vl68lPBK8a61KdtLqpe1m2O1mQIKyr2M7GuJakZ3Of4XxUl8+21a1mfMZ16qRB6jHoQkC5ZjmfNojaJsNeNfRDfW1l69xsmfILzANfnJHWTdymTRzkvjB5nk8N6nlMBY84KOoqNmEVB9aGdXN2gcLtlskZXE7v2fmB4FEGpbZTWpVRn7gxdg5n8V7DaM59uaCHiz438FRGruKuwS5xl/1m0fY233MSwT9fUBsQ
*/