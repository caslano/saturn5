/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
AgHbAaokGyP/xXhRgylQvhnv3qlEL5up5xz+Cchp+RU+yBRXO7Oe3yjF5nbR1VvQcIt9hghvHwf826IDbCBkHCTuJ6RXKcqYAcJLRyGY6reMJ6EFSX0a7OU3I3ofZqpb3+tT2FDRTY85oBFXb3bQbL1EaSEuyOVzQup5HLv+e/9btuAYC1I0CcN6xfDgkozlAiJBSzb/tHyv/zQL5uREC7PZy+CGR4dMWCRAG523I3P8V1CgPvMfDek00TjqNZUJDBS13Dk+zSq5XqlAZEIeOFDqp0bws5ZjWxwjK+h2FSKysuAEadBAOaZSHZgLFZbvFwMXLzfEjO3Xt+tvkJ/9NMP2e/BI9Pi8THJmRQ9mxd7R84OLfwgsJwRvhOPkqCRmt0ldo0gMBkb/6FS2rkCsn7GAxgbz+rAvzHW2pi4y5+kiA2CsbbTa4J378SxKrdbSEDZJXSssolKc5HKNGrZ/tL1wrhVF4MwlAKQLZBvGj0GkdcUSa3frCYJzi4Xi/Q9edPd/Gwpsa0EsPHYpSDdPc5LtOjOkz2EVdCLVfIv3e9kvZ7fj/WFT6pZGcg==
*/