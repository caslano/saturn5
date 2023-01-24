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
aDUWDTWDBXyOZ98FGVxP65hPGArdayHumYug15nLJBNqmWEa3d7vaJq6/gJShy4oXj/yqgaxRY5LfRjnNPXhISBEE1EE56UtdMeRg3G0sCKl6GieK4uOv8R6BTXDYWZzgLrkw3rUw3sW1eMHVo8CC4821IIplPa30kZfSn6CYviDU0SvBWaI+kHqQdmNuTCwBMrxPM4XLPRboR/jU6V+rAnQjwr81SAOMvyiGXkEtBBNZR2jVio+ixdxZTxxF+Me7z/Gqg9kuIE1vVd8kpTYhIbBfAn0HhcTuxDDWGNR2cyrVg/mPb4R1DVC9gquTQP3wi20wXbhAWiDdU+ZSXF7D5GK22MI58DKwVnGFrqsy6G7S+9jta7gGx/fh6c+791HP9++D4v/eRfHKdxnzXcD5lnvLFTnWWYiejNEYcUNHERvzbMSk+8R2v0Ott1xvRidmcnrRC+ewdKZJI8MRAfOWQGb55YrKXnbuuAsAV1MPc+YDre33vD/7nC7ILShGVvNnbJN95t/fX8nNUzBvdhOD99rzuEGDTaNYCUZwQkVphEks7iHAQtdGMCYrxz2Tu1tHva69fQdeNhL1hA3/UEl/GEUi0QepWvzXJRAmfL4MT68zzG2UjbanjCSbAKDt0FoeZYrjbZbVodxLmLnUjSEQbDwUqxNQ1bIhozEdScZspD2ZMgiQkxDlmoaspZkyD7vFauRHXvQUqxmipZ2
*/