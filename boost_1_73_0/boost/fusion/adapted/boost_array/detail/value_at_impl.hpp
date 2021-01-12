/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_27122005_1256)
#define BOOST_FUSION_VALUE_AT_IMPL_27122005_1256

namespace boost { namespace fusion {
    
    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_array_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename Sequence::value_type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
h2o9T4uj173sE2dWSYRfG+e6iQe47sLR+rzUuu6Z/ixaZXVd+yJxk6z96PrcmGs/GDk+0lEuW9c1h+o1s39xzRR/V3/7Ou95rMc9n90pet1FNfccOvg919fr5/7i+q/7fvS1tg4UhsbqVr7zq2E4isXkp+Fxsu+S+5N9KRFnVhAlGl995vlrGhriD0RGoUqKHEVxMoMnsTODHUeRNXIpnkchI5w6KYV1EfaDzjwMTB2x0yoU
*/