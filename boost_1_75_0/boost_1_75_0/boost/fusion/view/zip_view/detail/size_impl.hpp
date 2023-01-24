/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_20060124_0800)
#define FUSION_SIZE_IMPL_20060124_0800

namespace boost { namespace fusion {
    
    struct zip_view_tag;

    namespace extension
    {
        template<typename Sequence>
        struct size;

        template<typename Tag>
        struct size_impl;

        template<>
        struct size_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::size type;
            };
        };
    }
}}

#endif

/* size_impl.hpp
+Xw69ovqOSdslxXn7VWSjxzKFs1xuirp+nw+CV1YYDHpgqVnbLzsLz26k+QDj+HpVm3c86OThRqUYe7DXRAn3/8sD+1kBh3kR8EK1Wbyketirhf6oArXG4vjFDszhncBO6Fz23m/hpnL4Agxl3cVxu8WinHcXd0FnGtYZDpL1kyfghSAZ4b71uop8ngGRtjpuHltVIrGYB8/839VgKiHIbvUDhoPQt6XKIE7s8gvhndpCKY75edvDvovzTVZ6CRc7+8aZnM++V7J4F75pOEi3nQul0MDG0u8hTEO1DR35VPI8zK7cb3ol1kRSCv/vjh8i3v5ljeQj8lgIDUr7YetJPVGT1Efla2AgQH2GeZjFhf9fMqHvnqefIX8yLOqD+LT57nSeXZMXAdItln2Gqbp5SIfue9B96OLkx8dpkRHWfi7TFEYpcFGRffnevAXNro9xEfGOy6H/2JONvIDZZTy4xd55k/LNzxbPuaiDGHWwZvete1lo/xVH57kSK8SNquTdh5eI9/4Gci3yBcbZCv6IxNDRaKV1nOkCbPZJPvK5PLuNfJNz5aPDBU+MLrOs20cbzXSiWZuAUsNN2+jSHZ6jXzzs+XbwtwGZNiINZzP2cL15E03j8wPP0sWvE3rPy3f8mz5zFrtWWTcBduPJtw1feZ35zhZQcApDa+9H+tncP565QvqMF7gnLQ2yUrShct0WzLk4OFhe87xwIW8
*/