/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09272006_0719)
#define BOOST_FUSION_BEGIN_IMPL_09272006_0719

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef boost_tuple_iterator<Sequence> type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
vBxlDC7L58cAg+4F3srl3S+VHEXUiAVlVGYZKzMFy8xEDgXntWUyAlt5ZpVZeKnxjEXLKBsIdSh1oLlbVhkNZolsrluwmrWEzgw7COADKCDPjtBIq2UdCOKvaBFYi4mX88Q/R9MIzqCzNzmhTXPRjTC4YUvD1wWJBIjttIP+LNwQe51WFpzM/mT2l5PpXZDB/nJZ9JozMDoVkheysIJM7yd4Cux15rm8n5ShwPiEDIb2SCUnMGpGIstlBQ2uFcbgmkitVs+mhhWsyfLuQZvcMnXhEDTfjGdNWS8rbNGD1z6ZaJlZxkXzmr+tFmfp0eJ7WFg9hM3xb//RRdyLOHwDhf2KABiT7Uwm2sFKJIHSh8vK57TUZquiABks5tPJSSImqV0McF0S58d1mBOV2h3oN6wvV3DDVqgsOkbcySpkVafsOA7NvJJjYfsmr0RhcuKqOJaRcyVO01KFsxYuxmCqXg1+v1Kzlc0u0BnJwk2IVY1pOM6mzmg4GCpO2ZmlryouRlydLhAuQ/gOHn420blSJiSfxSfA5/eslRbMbNrGVsBOE16NdW/GUIvV/IsJ9MVqS+DUupxfusxabtFrbzhEza4kWdCdhq1onSocK/ZIGudN2yM4jN62CMHyK3DfxpgENm3U2v+OQiZZia2L/bCSs88kgBxRkJ1zeT2lkoWRYtwCJyxnnLB2td/oXy5G/3LT6F8Ooz8XAmn0j6Fc
*/