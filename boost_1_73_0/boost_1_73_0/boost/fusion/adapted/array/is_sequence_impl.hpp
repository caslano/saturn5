/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };
}}}

#endif

/* is_sequence_impl.hpp
kcG4YBKkyNWWVBRwX7KUckkzIBIyKtOKLfGBcVAFhZyVFIbhZO4Hv9uwLVhatHZ2ogZZiLrMoCA3FCqaUnbTmNmQSoHI0QLaz5hUaLNWTHAH4SkoWq1la0Y7QUopgNwQVpIlwhEFhVIb+Uu/n9ZViZH0M5HKfnqfCqdQ6ydRzdGbNdmB2ChQAmpJbdDyNqxFxnK9YorwcFMvSyYL++AWAvKsLyqQtCxbc6jKqGxCoBC12bK1JGzQe6b0IgWXGm1biPUjQUxrayivK45wmBaUywQm3oaaZ7Qy8iYR9yhtlk3KXyjZwfcMBEevoONG4EcdWBLJpA1f/PgqnMXwxZ1O3SCeQzgCN5i39j75wSVygyFqBfR2U1GJXlTA1puS0ewR+HftdMuJr2A4m47DSZzE/rU3DINLP/bDAM6gc3IOH2uuyf1jBzolW+rqw7lzdu4M8EA/JZTIXSKp0nXGP1JKotXoCgL32rOeN7041qXVgyIVPGNaCXIMl4Bia03cv2oqlbESzYNwEvmR9QPjaVlnFC40bMPD4r1lEFKB50+96eo3cFQgQ0okyrOe2FAKvjJe9N4ZvEsvGk79iX5pTQhWgTQiTQ+RNUWGOE39M5ozjpwsxNbQZZH7D0E+u+OZ1z3rLfKJCcu6IWVtyKIq
*/