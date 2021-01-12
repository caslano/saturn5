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
mzWwM3Kh+1vndrb7JYs36ln+tu3nRTvmQauVqtM6FHx6aypeqPpaud5YQl/hIFvaUb8XcjWBsaZdm7vHfVG49WRjFN+IB/q3toX2iHXprm+Q/Zs1TZXoStv4BrLs0Lxw5Q45KTGi+jmZnyNzPt3VtqhJsc+q7EtAbvfI19JnAF/4HGx0s2rcPVmspUnXAI2dpJJ+YiO/g6DNgtjoLCzT2NMOe9bTK+urS3J+fjNoxZ4ljxW8
*/