/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_27122005_1251)
#define BOOST_FUSION_SIZE_IMPL_27122005_1251

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::int_<Sequence::static_size> {};
        };
    }
}}

#endif

/* size_impl.hpp
ErACYDcBuxnY28AagMXbwxSMLGgn7dTDZiPTyVAw4tO7hUozs/3V/mDd2HbH0psm9lE5LW5u15SfTlvHB5dnkl08JjNYd13msTR5nkF7m0ZkBOuuyVRbitTeoKGyqtf2INO2FDvMOfb5uWDzskr+lnm0bfyk0tFAsuMcrd1PtfYnylVFNzu6x77qnIzSvup8JoZOnK3RiHcfhcyRtTqo3vYz0laihIPR3mAJtWuRwiKm6LfJv4IjJpAq7Kkuzm4=
*/