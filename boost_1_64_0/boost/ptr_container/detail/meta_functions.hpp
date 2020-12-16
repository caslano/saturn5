//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_DETAIL_META_FUNCTIONS
#define BOOST_PTR_CONTAINER_DETAIL_META_FUNCTIONS

#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
namespace ptr_container_detail
{
    template< class T >
    struct select_value_compare
    {
        typedef typename T::value_compare type;
    };

    template< class T >
    struct select_key_compare
    {
        typedef typename T::key_compare type;
    };

    template< class T >
    struct select_hasher
    {
        typedef typename T::hasher type;
    };

    template< class T >
    struct select_key_equal
    {
        typedef typename T::key_equal type;
    };

    template< class T >
    struct select_iterator
    {
        typedef typename T::iterator type;
    };
    
    template< class T >
    struct select_local_iterator
    {
        typedef typename T::local_iterator type;
    };

    template< class T >
    struct select_const_local_iterator
    {
        typedef typename T::const_local_iterator type;
    };
}
}

#endif

/* meta_functions.hpp
Hmois58hPdbV4YaZKZpM6Nw/2eWT/I6nEfzu1nwFI6DO7lIfvnncfMXl5OcfOtLebyLzvfcrTVggvBCIsJt7mzBdvGhf2NXEKf1TcAf7zmYs3EKOq8B2HR1h9xL/IrBfbRBhexq698oibKXBdpgUYbeRx7Ngk0Qed4D96jLuyBPYXQZbKrDHegfp/WJGhH3TE38PuvucCHuYuEmwISLunB4B3aOGbmfTHgsnVNfXVy/jREFLk7/PrZ2/zRU+1fotjuql/C+1jBAcj7bmZNPIAvVp9+Kn2uqqmY6sq24cOW5MdV1rB0OP8E6X2ig+yrymDT1fXdqMsCxN1jeiFsIkTd7DmxmNLEtiBhcn8vNHjBw5ZnxBQTWjzrbqFaRtiHwlRmMOb63XY2XXCfIYVpc3rFRkNJwoXOxUPSdYQiDwp3AhNhrf8pEF1Yu6Cky1s4W59Uco6rqmYItDXUVVFkVTTXNDTWtjdWNzXVOHvqPmI8NnkHgmwPS2mllUVV/SPWlWaSqd2k+MU73sp0arrmlvWrqwzq4WoRFWsgIhYd+Tjl6ebJ88r3rZqOGjodFy9U9T33j62c2scybriyqqfPru01g16TTAVCDkfzqDoBrM4tQ3Lus857kMUluWp6rzR1Sn6pesDR1fEK7WNzK/1jGrg0u5fjTeXBNvydJ40jmVRS1Ll7Y0y+LT8oaitREx1jNonVVPhlcXJ5flj0pUjhuRqOCYTLK1utC3EOX+lgTi/ojuUF8YWeieEkkXJhhmVbfULKku/Td6wIKxecOaW5jNgadzR/HNyxs2s4AvxbdyWN6w4sSMwsSMSbMY7FZwrasPIHSFZcVBUFGl/1tRVeT/FJeV8UMwfxjCxJSymYWTynBKWIxIlFbOLJvk38pFnw/r7ccoYpLAX9YKbuyqnFVSNDE/wIs5QDlvnv6vxBw/vcCV5f/LqyaK/9AB82ZBRlZl3aCaVFY2c25iRmWRfz9gYkZp5YxJVUVTo5CK2eV6xaOstLBiUsX8GIrSKuaK8LUSxSWFs6ckykrmlJRJMp0t8KTyhG/GZ/CH3/c/iupdzrWRFXNKi0oC6mLUtalmmEU5eZSzYmlwSjRroi5B9Dd18EMoReX0qpl+3SbPmhkwDBhuFPsPz1YUllb59YABxSWaw6WTS1kNhay4ZE7+iLC8frR548YkdAK+RdR/wLjZs/hLE5cFiUsWj1gxYsyIgggtLfGh8SNG0M5RXy/WxCZB6lZJRP5mQrq4VDf8VPhUxtpmkEGicHZpWTGv4k71ffTExDlFVTNnllUW54+uqJqh0yguLvVbr5K4E4P/IodxWgamls7ySXTT+ABPFSUqi6frlGdOnlxaVIpQ6gx0GQpLqibpPybP81PU19gjsJrAX3CdWFyMyI8cPcaX89la/kvK5yQmV5SWUOT5EyuS7QzZgvjIS3nR1ETl/PIibpCa7TdhcInURBXqfXKaspTOVTI15f8f/XBGMVAl/bFuwnIuJW5LtOu/GXFV1uGHElgxjP+rzxu2vH7UiNGj9W/+6AL9WzAiP/jNH6V/xxYE4ePHjDC/QfiYESOD34Kx+nfcyHH6d9ToMeYXXP+G+Pggv/HEn1xaX19bw5099cMX8V9FAcUYUlzQxNdKlCmT+VZSGXjPgHCR73zrK6XbUWl1KX/+eZ0+61P/ws2Ze8fXK+K3mK+EbzLfFL6pfKV80/hWwa/p/JJX/qiCMaOD31EFwe/oUcHvuLHB7/gx+nckkqh/x43Tv6NHjde/Y/KD3/EjRptf6Bs6atrqSaemrW7RhNJJfgfwddm8cG/ULuS+HiXdld9JfGWbyzN7j/q+eGpWMO3R0jY5qY86zDLXMGf75rs=
*/