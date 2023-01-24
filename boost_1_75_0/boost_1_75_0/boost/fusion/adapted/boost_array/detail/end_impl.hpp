/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_27122005_1120)
#define BOOST_FUSION_END_IMPL_27122005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, Sequence::static_size> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
G+x2c8bcF0PPGU+fG2TOSGEyWKxQOzNt/I3TxmuL+KCbOylg5ugy8Z/OHK/9s5njZM7/MHOUDA6cOYoH+/XkjYM7M3M0HzzNzLFexm6rkE02iX42k1teCGn3eXBQR3YJwIOyVIF25PneaEj830Gd2Z2OOEi7Uz/LSRTgt2QEYlH74d3AVJdoECwzDtGNsOsZyfWIAz3IvFVIVU6wVGjGn+9Mb0X2qaKV44dkkWIwyQPIJNs0XPdl8G7N4EzCKuVY/zoyyQ4X9a3MmQT3B48hk0wflOG+in2/3py3X0a4pgzIg/HHdOKIc/UZMf8csWfIMM+I7UCdVVXSXY0EgYxhnb9uDPLAmjEd8cBn/wnJA7+cfToeeNDggffO7gwPpKgd8cCsqzrBA73+cxoeSDk7CA88GIwHHvzHPLCy0zzw4P/OA/86qzM88NMvp+OBDzORB1ZldsQD1c+Gtv+2h+KBMcoSANAiDlhl7wwHXPRLRxxw0xUmGjvo/2dN/a8Edv8l9vbdr6wHAkXnw4qX9f1D7fp+8Wn7/o2O+/5Rve+vZF3/0P/e9TcP7EzXN/10uq7/aBTdU40KjSUG7frx06Hb9bsBge1aHtiu5f+4Xd/qbLuW/+/tKg3oTLs+sv907XqTg3xfOoKfIRcuN9v80dXYkXZnyA+d2f4MOcs3ni1Iv1bHsAnbD+s6BoyVTUMpy3t/TpbvQ6prPCS9gJ8w
*/