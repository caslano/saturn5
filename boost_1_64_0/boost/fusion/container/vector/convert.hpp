/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09222005_1104)
#define FUSION_CONVERT_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/detail/convert_impl.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_vector
        {
            typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_vector<Sequence>::type
    as_vector(Sequence& seq)
    {
        typedef typename result_of::as_vector<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_vector<Sequence const>::type
    as_vector(Sequence const& seq)
    {
        typedef typename result_of::as_vector<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
8wi9Wba0tJ6kxZYG3suZmplkLrceWOp9JX8kDVLvm2KbRwWq1Psa1KnKOeUyvRclvV3knOpA6MuyBT/q0mvOIL0Vb/+hzzOpE5D0OqdhQw1Hm5BWhEhCR9Yv1qXBdjsp/5yWNGjuH5IG53Tpxi5Iy0gyZzjVYbVvKP3T6/IsxF7Pf53U85PIYSy78KwjvUQQPzUnK91UifFO9Mc4X1MPZ09XgVoHSM1aqPTJr9a3MS/MNkZJEXm6vaatb+qvlHTJ+pGOuv6MtCTmOY0nkco8x/7HkB62mW6PJ047j3jIEzWuTuTJk/z74+cccUUZxBVhEFesQVwJBnFpj0GJ1J/v4Bj44VYMVe5FvzqOATd2ucxsx2DdpY4B30E+Jtt3UFJmBmvY5tWReWyQrybbvK9+Iw7msW2ZR5/6Bsdvi3Jd2c63CO15pR87NsKgTcVY/feYnA81vdX6VxmnQG1XIcdIXW8GtwA5Z9RluJM68reXLb10r2N0n9C1n2G/7NtT0j3Uti4Hx3Ed9bTNI9vJAt01s0uKYH6R746z2I24SslfzfGS20zFxurdcl3ZsXq76vI7z+Caj3GkVeo59edrksW+r7Ga/WIDuvZDSUSpu/9LPXy03Mv6yb2s4Cen89J2K6vA9/OVupep7V4kvcPk/j9IflMU1nQcF34I8bui/LRW5LeEPZ/GSj10R7l+A7EFy3lfqKeJVy5fyaf8cs6H5r/UczofCnTXpH1cKP+G8vvOOlfy2OB6SzW43vJ011uMwfVmMbjeYg2utwjd9dbU+Tqytj+I16RxhP5a1N4n5VrU5nEqlXbWdSWPb8BA4iv+RZvHcslVcHzsVy8657HFkZ/Tja852X/H2CHEJ/uv7itZIuuG646Dpj2KrMueq9erNv/01za7xiWmvz4bexlfnyE/afPEdnlWpP3Dlbo+7b+5l3oZP1sUO54tss1Tc7PScuYoDxkVarNh9BtNm0dH6tkWHi3PdiMxWonztJpHNBSUPKrgeXP6jO680eWZr9P3CptXzmbNb6Ne9vmybL6LvCxQ89JCZso47GpbREm63KuiNNey8jumgLw+zL4/xfxblPSil/aZUNq3xqqfs/XPl7PkfHO6x8Z4lz2GQ0ijyfasTC7Gk7DKta/W3te0cW32Nj5fLNWc4mLooIrH5ep5NLW+i2cd27WUmZ4Ur/sdVn671yv1vGNPc2l9F887p8ukWW6Ml3c9uXrmOcO8xtWqrh1UZds7DbRuJ/J8cLux5+bfvWHIxMYnay25jXHaqivzc5rec3bRzQ9PvLPD+Ee9wz2PV74dVGXHStozRJk/NPrlQfE9/p3f6IlOc7/M6Z1rbSvO/Lf3x323Pr3Zid/uL4z+OPCFn/j9aJ1fdGxCq4cSnqlz5/V7PXzPPf1K5dtZxVq3c+SOpHuf8jv94olGU77YtXhbh8q3v8qx7u/ip1cf+nJnSMiinWPy0pY9dfJ/t12WN2kl/bGPDDrxTHp4Qafi9374dVk7fvdmKvMXRWf+fH7Uwceebf7F3r8evGPw5bXXauwh5YhSvlgsz9l1pcxxkDJmBQ7G9jgEw3AY9sThOBRH4mi8CSdgLKbhaMzCsTgHx+Hd+Ce8F8fjGpyA6/DPWISTcBfegu9iPF7ABPwVp2Jr0piE7dCMIzAZb8YUnIupOB/T8Emchk/jdCzGdNyPM/BjzMTP0IK2dj1Stij3+WJdux4TyzVQwAC8TtaLMklZIRbIejUwXFbrzHJ+GIILMQzvwnBcgt1kO0UmKfPDtnJ8Girlk7KdhrIdXwxEPwzFxtgHm2A0+uNUbI7TsAXOx5ZyHFrhs9gaN2Igvo1BeAjb4hlsJ8chGOuQnvbojx0=
*/