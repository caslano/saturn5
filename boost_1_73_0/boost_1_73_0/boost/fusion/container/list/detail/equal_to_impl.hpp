/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_09172005_1120)
#define FUSION_EQUAL_TO_IMPL_09172005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<cons_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
FB4uIgQVEyDK2BG8hfI/mLHUbj7NWyEDMhpitoLUffz38APtVYfatW7I0H+ehbQshv5ZIrMIFAhz86BWkYB0KcHMoiigbpo85VVrqGs3tuah8AP8g1v1IApgBxgxYBzdZug61lGc7jperY7xkgjnEUwFMyS4NcjvGXpNlDhKYQl6Kv7tEusznt5xHubaLZmhREyklF2iRhP7tIB87hgpky+WThzypnuI1Q5W6T3BGIzzo5Drz8gNfi5y2jWp/wHTbbgRiqC2pWkd/XyrSHKLlVlDqNMG52ww6X0EhJyMTr/rT696g3EeRpR2rauZknEQcIUfHIyH/vHqpy4SK58wbKKVZJQoWaXOFMF1S0vk+wMMdmsjWLaxn7Sd3XyZ4nbQThykPlGWZ2WHkG/PDWwDlRgdVYw0e6gazdNl6CMHJvyW+xhgAAPp9a0b4FMMv4CoOQzTzQ6XA+uUJk38riKGjKqu3wGCg1Nu3goECuf2mxvW30llEyxugOBMBUZl/S/biaRGg0CjgI515G1ygysTkeDi4fPhBzCVFkmfSWakDamJ8y5d6kFurtAGPNjN2j7Q6vM1gLVWvgL21kqVP+82djAVxHiGxRuMCADROaZ+2rPZ5tDEMhHkA2j9mBSUhCvZOaBhkayXwDxNVFt8
*/