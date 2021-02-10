/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_10022005_1617)
#define FUSION_HAS_KEY_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct has_key_impl;

    template <>
    struct has_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply : fusion::result_of::has_key<Sequence, Key> {};
    };
}}

#endif


/* has_key.hpp
Hp1I6AbkyoCRkGrmgUV6kMiAh/aNAUHhKl3EXEfeizdoSgQNqUCzOLZcqMeZztxmMM3D41kYrNBjbuxLS6GtqYdIJiUgxtGyhKkSaAjjgKBAYpg9SLGHlAO7nRcm8pi6AB9MzYu/AUiBzsCH9hT60w+woJprD771Zzej+Qy+tSeT9nB2D6MraA/vLdmX/rCLqedoTAF7XCmm0bgCnqxizoLc5s97GpXKUT4wLuf9QRc3Rwb9SzsYcB5k1aCYoAmG2VVWKnxbFXbHKMDUuxhJGWMyAgY+7hZT6qQatZy0gi3ygFuSqYElM4aLJehNsnBKMSbZEaIvxXjqYBmRYCMIF9wcU29RBVtZj2XZLpwGwTa6EO0FC7vk+Vv4QrpXJSxjw13Qegu13g8LFWPH9LXpXLILXRlVRmaCXWC6g0wPQWMmyshMsAvECmSmDC1Eu2CDM2E7A8+yZ/jz2iINIX9hsYUy6zjsnhTPAFt0riiYwLlQqeTiHP83FpUfUQU1/KYu3LivwUpy4cYKBZHG8UfbvFxQ24k0jqXvPqFCiN2F1ACa/2DEAG5+eZFRiDTBiWwbfrExWPW13l1nMLeNUXPe/WBKQsEryzRow89prKSYGrhf7CFTuIDVXtLC7llwNF9oxdwOriIaL95io9o+
*/