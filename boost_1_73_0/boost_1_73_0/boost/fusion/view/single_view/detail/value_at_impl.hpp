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
fjYUuGPsIjf8BwJ307GTnBdmmRRxTeGAYxL0eGkgylFrR2w6PbsMtQfBnLJyexomZDwGZCMrX53jC9DbfOb56mBbn+WsWagU64AbIpGDUM80RpEc0S/bEYyxlim3aVLqDyX6lu8VGCK0lfp44LS7xZ4jIwTUaVImr5eUaTg7ygJ4qbIeKeXMy3cTBrt1TGHOfvLC8mvaKaXtsC4wlyJn/1Fl0jaCZqyQHcc6YWsykQlGB7M79iuvlWhgo5DjrD8OKOqUV3SHWjeoQG5UuYahyzBuTTMy5DB/Ck3KNQL9mqA0X0ymypGEKbGbk1r1nRWbtoBhoQHdq0EHDUvNVo9MFuGIXRrorpjBXig7FF2zvCciPOZWAV2GkTy5Sv3iFUXXcIgmLQyOHVPh0QqVJLR1uiS59NAoZI8XSmjoPYpilSXSOS6gDXpQO3S+dLCMEx10g2ZIFB2KgpENi+fN0U+0c/lyDw2PyScEE3gO8jHHa2SYKS1oFG5TyRIjpqxv5Hecq4PL8D1nfGKNnHAg/3B4fn56jtSGEdtdQRcfwGAztk2juWIah6K7ic1Pf+4ZVNV41+hxNjw5xItFoksTuM5CrS015gNOJEF11UALa4/ivsC0/uzAmEk+WtboqigyynG6PTx9sbTlAo1inaXl
*/