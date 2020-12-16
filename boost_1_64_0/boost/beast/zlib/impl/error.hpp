//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

// This is a derivative work based on Zlib, copyright below:
/*
    Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Jean-loup Gailly        Mark Adler
    jloup@gzip.org          madler@alumni.caltech.edu

    The data format used by the zlib library is described by RFCs (Request for
    Comments) 1950 to 1952 in the files http://tools.ietf.org/html/rfc1950
    (zlib format), rfc1951 (deflate format) and rfc1952 (gzip format).
*/

#ifndef BOOST_BEAST_ZLIB_IMPL_ERROR_HPP
#define BOOST_BEAST_ZLIB_IMPL_ERROR_HPP

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::zlib::error>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace zlib {

BOOST_BEAST_DECL
error_code
make_error_code(error ev);

} // zlib
} // beast
} // boost

#endif

/* error.hpp
GSlHNiA7kX1IiyeID5KPrEU2IjuRfU/UzLWtuWqumqvmqrlqrpqr5qq5aq6a6z9z/TTz/4tWVM7+P7r5/8F5+w+45u1nqj+rreLSBnk9eD5nbfcY39yCxZpsET4fXmN50m97xGOOrrngIePzHyg8p6o/qETh2RAangW4DCaJX3ikX/Sjzr91hc2M5/3D+EUfVvhZa5HGLXeq5uL0QieljjusOv26pGD+Uv/z4eWmtut8eONC58M79pFHnL7h45Y40pnvxt+Q84cyolWOiU8T+BXh6U08MkPjwZwmG36d3WzDj27oWO1JxvxexB8jIlx5tLTMzl+2buLtWRhTjfmdiPsjatuz4wPOmLDGkfcEdXBxAvnaUGO5oynPDZDbkIcQ9j+25/N+QsSnxVMzmgXH+at3JgHxDD8fmrIRej70ShMe8kdrEH4XZr4optKcKnOgrjWH5EELTeSaobH2E5E0dHajb/PAnIpMWFxl3lQCW44c/XibD28bc1agb/h8CdfY/H6jkxbo4Drf+GHS8UGkReLhx8q1RkNpY8MUEr8UVZLHkObiaPI3s54rflp8Uc+WsTKb7zOM3s2Kp+OulczMYKkfNEe4zncuxm6YCdcSo/tbxghmmLrxXZPKcpNDmfie/xuozDRpethz5d3nOat8lMns1K9ik88/rxdaDu6w5tB3yN7aB58jPjKYLvVD5/IsLior0KxVm49h7zy5mfmj3nn4F/LOK65v5zCEhLe8zsHzDhuhsy0svOUpmuzoP/cIN9WbT2jnHoXNG2wQc3CYjiNMuw8Kk5loqXT0D9fuYxSu6zzCFduJPPcIl5nkaYLlH669RxkuJw8z6h48f6wx4doXHi7e+YuX581bUrbIL0y4OTbzx3Z5hKkzYQo0CA9T0eK5+pr6hAk3Rxcmpy0yq15YmNQWiQ0P02HCE3uMwrOtvpT1rhiENCGNkkLCg7u0Ocvm+Zcj6beTmTeGMdcx+meaeVgmy+35+L2NfS/GVmupPeL40ci4WYkS6x14qD3XRvbDmO9Vz/dcIengc0P7zspJPPJ3liud7PeZ8HNP4dfaRcLHPYUv/LygsO9UhwZaM6I0boS0Cg4uu9NYiyMUZr6Vh1wDOKZx+PolTXAu1be+CEkPzu8Pf0benBWVR/TmLS5YVORqGy4uLlR+xkHc2fOhguG+x5hnUG78v/kPGZ2x5CnffM7v7EK89yL1EoPVp5k7buYsTudcp55H2CaIC/kmEl61l74xz2WcPey8nc1a83C5zq45H0kg3VMautNkydzyNPLbsx2tc/yM/hyVbcd9V6MfHRvUpxg4bVBr3wmz5pkac7nrLKYSuw5sAvaTjP0iY86x7l3nY4edN5Nj7JcZ80SrnxRQepp26szE6rZJQ8s88eKeiZfKvLNe1oTdr8zbtD+gtQQzVeYnI691DEYiPO2Dn0/f9of0R9n3ynhjPs4v7aWfLbPV90z7HKufIrPVP+r2zpGmY7D8TjfP5Pdz2Jlvu2MPPn8pA53V7jQMOduIubz+vwflrrFnuRpr7TvZuD+eeOTrkD3mtPqWjcvitOcZ0lJsSiQ3hcaLcmE+Oj6/x6VPasarnj1vzI8FRvLduR8J/44onnKXZNxNxbzbmHcGcvj7CFK1bh5nrvfbhEaVZ6alKw3JRy7y0bU2v8Do9ONXRAtbX3uYe321Zi0isKqR+zcqzzPmFYR4XiCZ9+YL5HsX0mhH8L0Z3bJ+vfrja0c2SG5QO6ZBfeYSucumeY86v6/yYoNuqneebvj6+VGh3zZTPjuZ8DFvJuz9+lqTg+v4K8HzwdAPy0cqum8+oh9ax3vG2jpLPoTXcenbOi59/zqOfkgdR79adXw=
*/