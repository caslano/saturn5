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
5fJVsznlE+UY0x+frfQF/et0g1Dno/R5NKok8V6F7dlEV+K9FCGUvNK/61LYfXCD3p86LoXlf7ws6Q0TUjhmSX4K64EpKbyFZaosZ8iyIIXNwWkpHNRshl4Auw28uy3ZjO0Ymw7sZ8DKgdUBWwnsfmAPAtsM7GVgjcAOAvsG2PfAKDMNY9daBhsHbCKwMmAVwDwnJKhDSzghQcakM1QmST9pYnJrPe3m8tC8isLZJa2ZgTisLL/ZTtb+d8xAHFY=
*/