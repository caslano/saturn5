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
mk+TbOfFW9aGwa/u57U/V9LPP8sM+sG1Ml1Z6DvUX+IS0PqHzQYuyVkDltHJi09ga81DcLF8z/pnQHQwdvHZVm7sYWk+Q719YRyAhv+Omq22fq/aLCUwl3xB4+rmVOjJ8S2gBGbgkYEJLl44PMUVTem2YEpcgrFTnRgHut2At7j4BJxGgy3heCazwlJ2EqYA5TCDJWj+fPEJuA93J/MkLl/USy8jPR+xh6A6S8qsBy0X/O58+O7RxSfgNkQq1eHT8tMwbVFfR+WyaJoC7eopJ7maAL3w5svUeffHUURJVZHNUelj6dQ9PAkAX4OnGy8EbuaBX+Mw4b67qaqzYxFpxYoCcZdWXqZXCPDam46yIbT4BBzCuQeYql2pp4LDoqZ6TPUW1gCR4IyUtTxl8d1Nb/LhGGK/7/sicL8Pd2AX0Doj/wKcgm/gr1PpNYceWTzUQa+X0yPlAsGNC4aY7/KD+Pni5whDlwgd64Eu5aBL2Sd7s1eB62/w8JXN/qLuPRvazLYIH3Fzbf0t6vTLqYUvQysONznoQ09xh7WcJIjpDzFp7sNSSQ9K08c3Psblc/bxTQnTbL26J8BSn32IjmkAor9rd/TdcyBTOeVIuydRWhYH2tfKL2x/Zs1SevWSfdmvq9deCjMHuk3CAtHBkjLjdeRt1Nn+D04lm8DHEttdu4Zt5fvhgHu+oqgmN+5aJr+Oar6+a3GqQ39mu9Xu
*/