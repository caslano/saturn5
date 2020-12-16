#ifndef BOOST_METAPARSE_V1_FAIL_HPP
#define BOOST_METAPARSE_V1_FAIL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/reject.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg>
      struct fail
      {
        typedef fail type;
        
        template <class S, class Pos>
        struct apply : reject<Msg, Pos> {};
      };
    }
  }
}

#endif


/* fail.hpp
77hdP3UOPttxu37q+fh5rtv2xeuJ4GnR/z8DXxHY/Knx83kG/nhQOX/qmfjyoHL+1CX4nKBy/tTsG/r9VY+vrbLOT1Dya/Dn8ZTjAzrE8Uk34s8YPw2P4pPuxJcZ/+ud8dFW4vXG+97lzs/T7+/grURwsuN2/KMKn1qmfz5qH7fAJzpun4+u+Iig8vuxHv+V67b/Az/Fddv/gdeJ8YEr8cPF+MBV+GFqfODtRDBN1H/a4VNct+s342Mct9enJz7KcXt9GnD1fcjhO5S5/3Yp+bP4t4G9/+L8Pi/g642fhreO2nf4Z8afwKP3zyp8jfGajs71+wf9A+r64Wp98Sx+n8hvdREe5R+KvP8dcf/2pfglxk/Fo/7jBnye8cfx6GzW4AOMp+50vn/v6uerEQ9aVu6fWIxvKMVvRX7aDvH7dwm+3vgSvEXUv4d/YXwzHr1/78XXOm7jw+oKjG+q9hG+RM0PWJ0IFpYZ3xle+jdOx6fiD3eIfent8fjIdHyy8a/w9qXSnosfa/yQRXF85lz8cOM5vPn3+Yjnt8z3b2wUn4f3xwvbxb7XbTyjpfL9De9u/Gy8U6l8q/B2xl/Eq0vlW41vZXzPPzvt408Swd7i+o/F9xTXvxH/rsz2O5X+fgTP88/ntov9/j/H7+9H8ZeNf41Hd8vX+FXGR97uxE9/mgheVfNb8FdE/P6X+JOO2/z36/HHjb8QOvml8OXG+7Vzvn//jNoX5ef/bsDnOW7rzxvx2Y7b+vMmfKbID/4jfpb4vjR+RvyR+P0X4oeL3z/8nO+ris/DVfxOA36E6zZ+CT9MjB8HaxPkx6tc/0nh95fuH7x0/8Xtt13xuxy3919qHfGxKj4YP0/l/8bPEfffifivxP13En6KuP/q8Cnq/sNVfvTgC/39CHG1fSrySvHVkVfKf+vZf8ZTvjrP9llP+eo95Wvw7L/RU76cZ/smT/nynvIVPPsv6vLxAtQe4ktV/Qm/z3UbP4IvEPl7T8UPMz7qKuf9io+tqnx9tlufCAaL9T92xUPHbf38UPwzsf7HGPxj0f/QWEwEHzlu54cswd8q077vE33/8BXGl+Odo/Vv8UfKlK996a/X8UWifE0bqN+5buMf8fWi/+EVvOC4jR8e/BXxr8ZnXhn/NQQ/1/hbePP7CT9Mrc+EjxbxTW2+Jn7DcRs/lMT7OG7jhzJ4ufbndtH7G5/quM0POA7ncKb9GY9fjMcniPZnHp8pnq9X8bPE8/UBPlU8X9lvdPutweM5vFbl/8AHiPpBEX9K3H8b8Cbxfd/x20RwsYiPL+Iqv024kfkh6v2FH6nmDzvbB+XWH3a2D8qdP55U5fuO+G3hafwI8XwMx8eK+sUo/BAxP3UsvpPxF0Y589Nxlb8wj+8u6m+r8F3E7xt+z/FV/gV8mJo/gu8nfr9ReI3In1CPq/t7Lq7u7yZcPT8FvLvw8IdEsKu6P/He4vgZfI54vsbis8T1L+Id1P35r4TOD4Kr+TlpvK2q3+E7qvEHvKca/8NTqn2Kp8XzuxDfXz2/eKiuzybaP2r+OD5cfL+yuFwfD5f5mTyex7uK+I3gR/37hR5PebwWHyWO3+DZvtHjOVzmT/N4EU+o89+st6/1eAZX+896tm/weA6X6yd5jl/A3xLP12p8lfq+/9vz/f1Jey0u88t5ts96vMGz/5xn+7zHi7i6/tRA5fFTuNp/2uN1uJwf6Tl+g2f/OY/nPfsverYPq7TX4vL7gqvj1+E7qfa/xxs93uTxgseDFsmgi/q+erwOl+fn2T7n8QIuy9/SU36P1+Gy/B5v9Ow/r53/Scr8jimPpz1e5/F6jzd6vMnjBY8HrbSnPJ72eJ3H6z3e6PE=
*/