/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_31122005_1209)
#define BOOST_FUSION_BEGIN_IMPL_31122005_1209

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {
    
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef typename mpl::begin<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
tfo/jTL5crhMg02t8f7DvUR4QuXpWfxU15u8bBfYDYBHOQjA1YgtJeOSDuOCzUJjBCGK6sjf55xyVCi7FjUYRZoEZzV+NgPgU3EK8TPqIVFEzuaFXBe7Nd0qBF2HpRPOgt/tRv9OEWTOZKHiv6pb7rkeIP06dNar82YhHnfVYVZneEH7VeiFgV99UQqxw+D5BSXpLoPmcU2UL2v2fJ5I+E+7Cnfesou20EcNHY6OSg1/e+91szrIrrgks1BesMRoWGDNMhG+UVADhENQCbcn51H5Smk6v9cQhRkC7mFlnssGpFsyMlIoAexrN4nVQnkFMx+5rq+SEqW/yPwk/WUYb8gb5K6ml8MZuvJhf9+Li6ogDD0RHAyMVdCMYpS2TU1lT8A6oOfCfhWgVNnU6eaB8Y/MVo0dXVZ/Wwl9CaggetpSn4H65G8FHMFXUhVE7l6llwrLQftL3uGwEhGu+Rdg2Owns8RD8d2Rt/W99Jtgiyk4eqMKAJf0u7uqBDYV/6pBn+0anyaZKlo1AnDgY3cBkomT1dfHCm/6crFqRjfhZ0+WZyK8muWtfWjT+Q==
*/