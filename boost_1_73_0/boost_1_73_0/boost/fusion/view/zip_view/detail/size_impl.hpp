/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_20060124_0800)
#define FUSION_SIZE_IMPL_20060124_0800

namespace boost { namespace fusion {
    
    struct zip_view_tag;

    namespace extension
    {
        template<typename Sequence>
        struct size;

        template<typename Tag>
        struct size_impl;

        template<>
        struct size_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::size type;
            };
        };
    }
}}

#endif

/* size_impl.hpp
eWZL5GRkozkYScU2xGP5YbZC0MxuSRPLRTNmPjLEugX6ES3R10cS8Zi5JhEZyrEzgWKfdwbxtHYC/QJ3ZivcXB6EjyTSKcNcn06MJA3YB47o+BmRRdNZvDckF0+nYJ5rsdULbjGv44dp2yGwgMgZOUKJ5FI9UAVsMxsNdjwweX4+OlemssOqjUAtkxzdWZxqTrHTAfQcgfIZqBwTicFIdJ2ZycbT2Xh+kxlP0XwhvLR1fB32XOIazxtJ09iYgU0=
*/