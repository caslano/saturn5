/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_ITERATOR_05062005_1219)
#define FUSION_IS_ITERATOR_05062005_1219

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_root;

    template <typename T>
    struct is_fusion_iterator : is_base_of<iterator_root, T> {};
}}

#endif

/* is_iterator.hpp
QS1braR4oP2pW3iVQkPKInYUVYc7yQKpy1BTBA04G1akCuXNqV1Sn9UUFVUQ1xQrtWWVOoDAJoHiDo7xQO6EyBm4dPSioqMR/r5bteVM40g5WdsbCBYY6ZPqTLU1V9GH4MhymXCUoQKdHH6IxEsWiCoT1d6F9hhuC/TeTz8clqOl/aK0ZmW9Qi0HQtas02Fwkdku7PW2s0xRMaUPGH5B3qPF/HXkMBkQLfJvMs2xkXJk1HbGq9jza8CsVllGKTtpAoUu9y7i84LWaFPsR1zs7h5Oj7KNDfrjTYKMjTQ+wKm1AWPKT9WKR5nXRuNV1nFfhlfo/fMV/L/xO+3HqLekNuMPprVbN/Z3ctLIg3W3qG7TZ1HttKTkqr6jyBijo3gJhva7xvAPDBv033RKB6rQtErn88x+lqaPISksKjoo59mlky36GPw55u9mJ23316B4copBr58c4mk1lOj78oecyrK/Np9vjgbzrTKfb+flGspS98UJnW06nmNMwCj+2bClfE3LcQNL3lj07lfJes2f+/Kp3Ojsusyjr7wi+R7VWCUcRaH9+wCXY8gQrYU1Evv7iJXO/gNQSwMECgAAAAgALWdKUnlE8bifGwAA7nQAABoACQBjdXJsLW1hc3Rlci9saWIvZm9ybWRhdGEu
*/