/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_09272006_0726)
#define BOOST_FUSION_CATEGORY_OF_IMPL_09272006_0726

namespace boost { namespace fusion 
{ 
    struct boost_tuple_tag;
    struct forward_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef forward_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
lYKPO7b6YBZYpFHpB12w3X/qA46nSJlPXMyX/MMfDvX3Qk8YDWzeigpq1X4qf4OvA1JydDgFjIQU7etwl/oy0f+R4XKUPRiNnX/I2aZ93O2rtGBSmYulBebvbdPUDIVlFQ/IVC7dx49TKwgsAB2CUzlfmQx/YCFTFHihLO0wYfwkSe3a1ozejZX0dnLl4vijiWzDa1/0JumG0jQWH+nA9oCWRKdI9R851D3tCCtKtyWof4F+fD/vpiqsVefPTYmeWu56hgIDjf5jVzbFoW6C4LX579PUURh/v86XDCmAYZIdZLHvaSt/wmhbxEgU+svIiRd5zUCamQTOpT5a60MCi76mMqqwr6Fyl7t0AI5D8Lfi8G81fVo6nRewClrEOkdWZzhBVlE0PhKkklHwKE/VVcMdfZmDUGQfQNiu2a1Z70p8WtVU+lwk2vJMRWEu2tGtZN9Ul+sh2uZe6rN5XBQrI5qMniIBtyUEnsPH1tSY8vsyT32u/aCnDoUjpb2AhYKBvlVk3k+UdxdE9ZxJnRdI/j2tn2/MDoggNOrg7gq3340oEbiI9BQ7DPDhLw==
*/