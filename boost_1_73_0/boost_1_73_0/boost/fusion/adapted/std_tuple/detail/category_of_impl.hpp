/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940)
#define BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
jWTB52nFDDAUat50NbAssHzEtcwy5BGpMDLifHSD2EwUMIU4t03QzdwmL0UNtVTdR/vEJiIH4f1nT/wm2O9xcMhjPptN3pEaP5znO+uykUZhumikddVlb+MWXX5dvbsup5y4TpcfUaSA2/g92evJbtXERMEG9zRTXG0cJ9uHLDXotP66fDPre2S5LA0gy8PFBuuysUYRs8FNlQKyXLYoLDYiOj+j0Az2l7eRfYAshbvG02SHkt1AlsJb4yBZ2kc=
*/