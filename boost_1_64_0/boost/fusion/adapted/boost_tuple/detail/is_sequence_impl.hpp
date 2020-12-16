/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
4z44d4RXMvHw7V5ZRdLMScCXCjlrXO70yg0kiYfgarIbT8LWe7gbuH+MV06RqVrzf+irRmuG+WO9UouH7vfKW6Rc3xFeUcTZ6Rw48EGv1GidD7MvSeHGOO4PkZ+obbxXbp3Ae+EykXMp5l10PvyBZDJuTOIOP0r9umbYK0dJGx5+zCufkEY8BbOm8C5aT4lXNpIEnnzCK72f5L10Tbj0KfrMmoGnvdJA8vA0PP0M3zIeLOX9SAEehVXTeE88BQufJXgEfkYqdRwOeI6z0Gfhs6RGn4X7SAUuEe4AKdM5cAWpxhPwZ1Kqc6Z7pRcpwv1wNCnBw3AxKcbjcA8ZozXDhc975RguZfR5Jr36mdpggjQznoQXvcBZ6vvCatKi+8LsWV5p13E4iTThEbiKNOgc+Cepw41yr9xI6vEQnElq8SjcQAz2TULHi/QB98E7iA8Pw0WkLx6HR4gfl9nUTIbgQVhNAjoHnvMS3xQegG+SIJ6AvV7mG9O94ElSjBuveOUWUoKH4DxSquNRrwwlZbo+nEMq8BjcSSrxNOw6l71xP5xEavAIfJ/U6r7w3nn0QfeFJ0mjrl/J+iSp68M5ZLeuD3eSFJ6ClvncVdwHbyRprRO+Tk7o+8IDRNp53wXsu4h+4tHXvLKfZOKymL87qvk7CA++7pUlpA+egB1j9A2PwW1kOJ6C3ZfQN9wPHyAj8Qj8mkTwNLxmKd8sHoJrSBRPwt5vce+1HriWhHRN2FTDbyBuvM13QML/p9D+4+2e6wCOv7Fqy9TBdu+5957de2SYmjpqZTI6MllMDkbD1FGTydQpK5PJwarJcDCMVo4aJlMHk2FyMAyTg8kwdbAyGY4MG5Oenz9ej9erzz7n++Pz+Zxz+4Ou8BLM1C2eeK3f0jTO69HQmeuGx4Gop3G++QZnNM1fbE9v9Jusi/zpm5xVXbjZ/mCNbvA1S6xVGr/V2VtqrV7zzLf7vcKqdB3+7h3DY5jxGu94p/OtS3wHpug2b7XMGuoMlzFGV3nXu4bHoNddk5/AZuMd3v1uz6Nr/M2m50nNW97jN8H8Il+FhcabvN29zpgu8C+wTNf5v5ihM/cNj4sxNc3nD7A4jS93hjFPl/m3WK4b/Bpm6bjfbzXGpOfkSzBSN/h/WG9O/gG/gQ/aJ13ip5AzJ1YMjzMxTNd54KHhMVQXeRk2pPXhPR72e6hLfAUW6AZvwmydeWR4HIUlusK3Y7pu8c4rrW26Jv8YE9Pa8m2YlOZw/lHrpos8DyN1g7/6N/uoK/w8pqRnfsyZabmOrvMjGKfbPP5x19Rlvg/T0zhf8aS11ZlVw+MUzNE1/s7frX+aw++sds519Rnf6+fsXRrnHz7vXL2h+cp/OG/GW3xQ22+a8QZ//wXfR13n3rW+p7rJh/zb9/p1zT972fddN/hLrzjnus6H/sc511U+7FW/G7rG+673e6Ir/M5rfjd0+fXhse0bfk90m9/v+I67V+lNf9//6zdTF/hl5HX+reFx/Aa/q7rJP3rb762u8xOYoNt88Dt+E3SFn33X91EXN1rvTb6zusFj37c+us6jN/sd0B0++wPPn+bwC6imcc79zzqncR72oe+7LvACzNSlLbviTZR1fquuOB4VXR3cFS9gWhof2hUnoJPG+XFM1h1+4xNdsVHXP9kV/8S6NM59ma5YrQt8KFboMp+HVprP96CtW7wJTZ3Ztiv+NqwromOthvvcDl0xWLdGdsXuO3dFTtd4za5dUdCNT3fFzN26Yq4ufLYrjix0RV23+Q+7e5fU/NnPd8UyXeLeMd5L1/jpL/m8ruzRFceN7Yolus5/w7A3fZaP2bMrNhiv8oPYrNv8AQaZU/lyVxy8V1c=
*/