
#ifndef BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        )

#   define BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES

#endif

#endif // BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

/* arrays.hpp
1B/tnv3N7taVN40/5XKVlKS7uAWFexoPy8x0P4p/xZ/bngAA8Of2P+0dsyG2K1/2+qnUNOqFTnOp2J/8QjLDXXC5m8nJ0nAxzikjEYovr3jZVsrmmov2fBl/p267/ipl4dHClYp5V9Pcuztbuzh3p9qt1qvYMjFurV6mFX/1fBuFsYeHx/Wm/jJvrGHMhd0h+0drdRf5hpyf+KtfnTcJLyvHFpaKlZ7RUaJvLjyMaef9b/wyOZpiJaNvm08bJkV/WnhO+cP2PM04llOHOrVOHZcUk0/jeOYj7LB57oN5+Yaxi0T2Kr7s69fXj3v31SdXqmMXEWp98W7y/bn74sbIs3QvmQtZW5vsBowXuGNA660f5/UEeJTUuWPNgfppJfLzCrbPNfvVL3cnZ95gKrc/m/Okq3d8uEtdcQL+N34J6Y8fWSJlqXdj4CFLY5JOIpcQGVcf5cP37Nb0lH1Ke6xSg/jzQx89AoPwmISyZ+u31LQb5w/r3XigY9S1k5e93S9YgYutQHCr6PX59ivtH7UG2HmdiE7jb+mx7f9l3sjd3SqZl8cfUVwzb62uxebvfs39vn/OL5vg3cEattfyYPPU84tyvC54hCAifuuGv3eu/Yv+sZ1lS59eXRHWkdlduNU1yrvAQpAtvXJL+ueV1YpKwo+NNW34avuaxVTXDRe0t5ldXN13gMXdS7xbNm4gXkH9aVRpxKYW1bd0xtGzQR3dGkemxPKKVsvq20gbVj/MXm21vHjzICLij3MWtI9cT+KLPdGfV1E6Zia0+cf9Nvm7oYMTxwVttLbbY+VistlFhNXxoPKNF0eWFJu2GFp6uhZdnxvw05OvRezwLVYF3g9NftwOovM51jsqRO807LDZ+qX0U9SVc21pPgtLEpQmTxlygW/jXBe/vmZhcu/HeVkBAIT147n/Mu8W3hLDifU/z2siXKo1vt+f8+png8mfxDY39XrtzupxHrujdfIJh2YiZ1Zn6M1m8/M1od5rrletHfSVWL6uqd/ujF3kstecaU9zn+w4Ej9+bo3m93kZ3/2dPOkvs3KVrFBzqlnmhohf8Qf88jzW6eJ2m+E2sOrpwmhFsQ+GdbxzhnQD/M6Kcy02PnJJbJf3o53lCrvSuqeWiCeEvuo5dBwRKQCAS+KkmSHy8dN/jDvju/9/sYLn6Sc56bH2lb4Dv9rRyCIQVZuZT4t3VJ4t/pLabPhhLNGzRkTgpZjF9vx9/rsP77301FBf5Hj7qExSVfft1cLZp/f6bVzxYT8b9TS6o6mm/G2HFcFCR7apWYkAAN/vP6Z/j8ffJv9rTvDvgh1WasmLtRyKD71IYl2llg0MvtrokQ9hp74slQ5+2WNTesx7C5/snU+Kmz78dVeQ3BHe1ykxFbzZmd/j8ld7GFuqWsWmNUa0u/psm863ZWX/sKz632yyo4j498gxmBVZNKZXeCjA4trwBa/6+uv3LEbUQSMiyypo0GnxWnNrP6s7AXlTH44dgwWXF2+Vtgp33/HyAQ/rgs3LD90blfnBxoHyL8KpdRUu8/UBAP7Wzryz0enRmQveCHNc/G7s5r8by79HOsDNZrm60R3dASn6whtYLTfuHGTxvQW6L9PlRFZwe8zZ1DtTakjgvLRa9T6gabSvRbov4s3+kUlfosRoUr2yxA8ZZunsDu8r/P3x8TZ/tRN++A74++f7H9i7Dqgmmi08AQREhSiKIIpBpKn0IqAivUiVJtYYSIBASEISOiJYsf1gF8XeEFGwotjABqLYO4qABbFhQRELvNlkF3YDKnnvnVfO+e9xzX63zNy502dD9t1oIBlJV/l8UCyZ1LBfp3CWVFpRk/mQnTcOvKphzdpgZBSdE6S3e54=
*/