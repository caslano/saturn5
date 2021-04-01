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
LwJdlKI2FIMOj7ftDn+JLYl+RBtdASFM6Kuqtic2yEMY1zPFG1Emx4NiBQ9ivhyo/zU5+Aj+0jZfyXGEWVZHyOtGZOtsaH1dvZ1AUgmr4zml1x8bLBaOSkjLU3e5AA5+S1K8aXWRc87COch8ymeuuu0w5oCQDeOzw9Mt3NgUTzLn0hSLUcw6jGeUFcm5kNyp4NMLvrWysRHS+5sg3Lx0jibUPuTVOidTjwP9wmPqCW5sbdkxRBXosHOQueY6u0XWBmyT06LssR50tEaeq9IV1FB2ToNqYDH+Bd8sBhbAzLD+8orF8he/DTTPOYEjjQf/yZfFXXLo9XFfjBRVc0hcx5218NpbQHssRT9Lm0/++BK7HESXtLmwHlJ08IOiW6O3ZGnD6Eosfz4Co6vvw/fhqxdlYHj7lcKKKJ7E1WHi7fpIjwTirlbJEtPtv/IBZSw4tuzUvSLMhRwpl8LazttAMhuSiKH4kGrJQvB70iiES2rTUc+g0p8D58aX/bwO/0sUG8DmQNxFmljScXsZgmwDcprorZH1lTUQXKTOUR1DY9/j+v1F+9x+iqgSSg==
*/