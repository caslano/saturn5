#ifndef BOOST_METAPARSE_SEQUENCE_APPLY_HPP
#define BOOST_METAPARSE_SEQUENCE_APPLY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/sequence_apply.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
#ifdef BOOST_METAPARSE_USING
#  error BOOST_METAPARSE_USING already defined
#endif
#define BOOST_METAPARSE_USING(z, n, unused) \
    using BOOST_PP_CAT(v1::sequence_apply, n);

    BOOST_PP_REPEAT_FROM_TO(
      1,
      BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
      BOOST_METAPARSE_USING,
      ~
    )

#undef BOOST_METAPARSE_USING
  }
}

#endif


/* sequence_apply.hpp
NkytLzb4/TnEr4076Hof2KHeWr1VZ5fc2DD2dTGeR5L4itOMPV0fN7Tz2WUa7jPTIeUgDtVfgGy1rmiuLc26a/s+Sda5LRuDj3i1s9bMe5RG64fxymafXTsrG0rcV/+Dcb/DjLtnYl780/m8+A2bVdx1EY9WjuCNVn5KDxWnpk/LuIe7FLfxnC6FXeqPuvYLHm0c0Cq/ddmvMvNZG4O0rD8faL5iskCEhzyar0j2Zuh+bxXEYe5Jq+G3c3A9hcsKY7kTTaiNZcNUTjnU5zRUP0nFn/GMduVnz0Ecl00k9FJp+CRs719MveZq/nN6mbK2+Bdl/dflUPaQH91svze7k3tWIEPJNNd87myOfc2Hukf+q384fXq65h7qPF2PEfYv67K2HBr7XEo7GQcTZNw8xJPTKt8+/xfzbc7d2qcpOz1CpuqjIX4xdt1yN4VDfxHefF6oikudWy7zz9wndshu7fvQkNvyjALzGfXmevGtIm59DkXtjVfr5Eifqkf6nqEviHoh/dI2aON4iux5hk3ZIv5M+VdOTpNv7ifdZljFBxlCFuJVcZnzqyI+M44jhhXXDI+4NBuQepo2cOcwLa+lDUDW6Hagr61+o9I2mm4qLYhTpod4r8MCu3dej6n39my3+9jrrxG/sjVlf5q8I3bv/HkbFL+kt1V37N69tuqxiWkyvyLIpMijyJp/j/ayqOmjyNu+i/KSPTZHIk7jDGHzvgLF1+8bM/cc3Y54EJ/cz99+bpez92i0/RNf7NF53cm+t1P5MCVrrj35vuDTaUdr11s/D3eLPbu3rt0q/kO6GH/mM+BaytHP3aDZKPJvlLIHtmf3yh5lqdotU87se7U/y3qUc6yh/+hy9XWoTfdSWKs2TD0z2lxfO3Av/XwNNS4Hl/bch5v26jwPW+z919sb8JH+vdrfi2BNQr8fQb9vB2Wl5Ooy59r7n3l+hvF8diFrq73b1yetTwe9EbcaQ6r6JZ91xK9nh+099vLLiv/27PiRNpoMxKHsRF9D+2pv+jPqYtuitxnJ/M98+7Sf/zHuD1b+v1UbvN0+nbXBxjPuzDoEeS3Ohdin1Ro27zn2ukzoDd3anxFxzz5jt6tWZz582zI9+tikfXq0tCB8+/HxAvt2Ly0ybvX7dvu232Nw8xA9Pa3a7CP2be9jqG02ftfse2Tbd+e+/PuXYLd6Xw860+z66327a9fQQfVJW+XhvPt1Lw8zn+mw39htLSv+wwnxt5m/QnmM3j+841/Kp6/26067kiVj7v3b59WSxHqv1/mt9++uD8ts37uQBtTBlum4Zf+x18G0/rVPy+ddSEtmeR/QHZvS7y3e+oDu7lM6DPHdasSpz2Xpsj/vsuw5DxxVrvq8+YHie+a6zEEIcyOuj3DNfBDmiXEdiutmXJ/gmulgy1oTVxXXebgex/U7rp5DEB+uE3GBg98gB5+/PCTlzXWoZW2GC3GLOPY7NI7ncRnXdYfG8UAe4oF8Kfdd/D7zYRhHHdaZXgccFsXXGfdmyf1Yyp/zcOy7Ojz9vL/2+Wbt81fa5wWPSD/vJD+fdISZHshReSV1UHp1pvsjR0Rxtpfx8xFjk7PwkTQ52x+ZxNE+LDXcMVqc9+PzH7gQXrc5ZY/LHIV9Hrg021P2ePFRKl3K/l7DbxMcjfqBC/kg7NPH5/sMGz/9aJqNP4ZwuWMybR2/ja7/csfw9Jc6Q8eseDuPc7T46mPQ8/xjRo/3lTHEu/aK/fWGVwvqTd/x4o9BZfFCs1xxF+/t6e1Zsrj4UNC3ZO9yChteftnFg5Lte+7ivlfx7MBLQlTKBcffvRHWN167x/eCfyxu1ytazor9Db8+4NvVuYrlihfMtRC4C/c=
*/