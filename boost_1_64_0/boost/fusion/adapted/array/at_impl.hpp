/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct at_impl;

    template<>
    struct at_impl<po_array_tag>
    {
        template<typename Seq, typename N>
        struct apply
        {
            typedef typename
                add_reference<typename remove_extent<Seq>::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return seq[N::value];
            }
        };
    };
}}}

#endif

/* at_impl.hpp
zvEqHloY2cHn+XCskhp8Ds5h4BEI/EFR6YDdg0EZ/6OwAq2t9wZ+JQud1uAPfBTrwnSux+qoOx68lr4BB3nJZIy1YflLEDqJR2CDLKlBsJINATzREHYny9NwzK5Ss9Yl/PSQsOpqqbSlqQrbUWnbURW2AzzVC9QFtx+i2D6B2w3MSGQ7H0HhwtDn0iwrhhEZsiUY8MMJ2LjggIHWCBC1pTwqLY+qkkel5VGhPOUKoCQb9a6bznhDksed6VsITq8Mw+WZoKtzb4ZPGPwXDjEjhYvA458IY9Ierg9rQ7AmADAxu3c52MbxZPdm/QSFccKsIMQU3r8tSWrMuDs7jCATvF85hYxcclx3Q4ddz8JwQz6B0dGhTxjBiEbGhg56LYGxGlWlGlVKjSpWI6Aojt/cAOK8U+0P2DR/NVqrr69j7YeawI9h2MbE1kSk+ZzbK3E1bqdZjodmcYwpIRF4a6zwNYTQ6E8YRn+HQEcgqrnWcYgRxfOzKKS5E96CwCU+eMbl1aD0lhQxrmXhaf+PSE5GeGcpqBt8C9yCSyucIygvqTrt4fC5hXkTOL6DxBRKIA18BI0cjaBDEAEbDSUqSLwiEyIw7xBCfUIIGRKk/l8Nq/9Hw+r/0DDi2ONYmEyEmf2fEYMMh724QVRS+cqouvRD7ebUeD7sIKCmAAPRs8NRuzNsm4ZFx5mdx6R+9ajdlvIRDEMurZtyYd/8gr7AkoLFoTBzGKmE4R3bZRx0nyZMCq4D6+LikjXLwFrQDY9jhrTZqzew2TawFKQuw6gh9pxcCksjl5ybcanl6YVZj3Yi26sBYsTsPsUM5UGQG46164OokX0uaxnkgiF9EoVgMYzaxGhZqxin2rn3gaSkMceEY8TUPGZQJWl8cCDTZKmywBpQUTQkEwAr8ih0i2RGnbqXT7ExUAwyGDRsgigCBpYqPkZ1r6q448EroI+ExShbuMBqjtHaFhHQEtVcFbKSxW1ZUpwN3hRzaWzeYNQrj8gn9QshccK/Ufx4JRTd2W81tFGpqULLpdsx8imX588DCDdDfgiHopY8ck2O+mB2TUe5mB1swB+iB6ObhRD6WIihg4VQ0btiMJEWBydQTBpOR0dxKThdJBhVxZbeKM3DGNTBgjDFpM4c8wKjrI6TZlfJVClPlSwXKEdKhs3eCVsABli0i0uhOVwSrUBUqXyivchBtQDFjh9g2vG7c+8Y8qT0x4IY9qSOx4IYT2VCtYlZtjliVtAilVEqucHwrqoHJ/BiSeIRR1WPOCocYJQ3wKiqAUZd0ICithxQiH+Brlb5Iw/oLTSc1GzaJ4+6sfcDmPB/QGMPCDDwgTEc5RB3fHAqejg4F9DHEaO6l9vF3/LyeEKq70EqrCKATpSYXuZpdAK0DhljjIAaGgjQuLXiiBgGNehTxQ18CciKVU4riLk2qA9Ol6xyrAUFTlSstqfyDliAykVxCWkM416mBLiQwA7tjUG80JIA8T5JCl1IZGAOFcb4aoTBSGMMNpoCEznOJSpf9o8IRyAGDydqddZsolJ4IygBzqwk0i/NHUyAuFJuciqNnxHBRedLoCnNrCaa69B8jB3Zue3Mw9vTeIR6QL/VMveUEUl2brHQ9omBSXvZdUIszgWMdDfCBXVYNGOFPDiuaUhoYqoIwDm7GMPWGjA4b0cac4Nb1O/MhML0TgLMBWAODlccOiJAVk44NF+juN93fCFCDXf1Yh/Jpc0ylwA94QU9v7JyaG4ZX5tYnse5TSSL0SJxDNssVnB9A8626KyRQwQWGUSoTo9+suc0tjFWe3h7vyBn5pf2oxAcIdXH0IvHlBFntI67joq7YgKWGTEilPajIxa24yIME64AK8/2Qdc=
*/