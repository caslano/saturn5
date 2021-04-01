/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_09172005_1127)
#define FUSION_CLEAR_09172005_1127

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector10.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct clear
        {
            typedef vector0<> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::clear<Sequence const>::type
    clear(Sequence const& /*seq*/)
    {
        return vector0<>();
    }
}}

#endif


/* clear.hpp
V2RJNHzzeT/u/B0ML+Rc09NgBtXbiHimgOTPhXi0Z6jPaihpzp/Zq/fDW3VmhEEMwLAtFfWb7mgLbw/EL3fd0B5Zz65lEnVkMx5YmSdIQHGP1baOuwFpqh69K56dkUCE2Z0QUZKa1QcEEJzXOU/07c4g+gSYIJTXI0Qxp4X0Wl9hVSIf5w0g0eiOxCWqZo4Z8bsnpo79VTDxe1rfdKs+CDGt1rASu3dwHgf5I6BBZhhZLu2oUmHw0ExuTjXLZRZptEYFpHf+ZSWcl/LfUDXeAbMbwQLQtontqUdlMzmo941ndQbeTByWvl/EG9LmY2sokD712Y9DjAsDI2wVr/u+4w/Trk8dtVIky3FElWvFvnWmubzxvWGRp7aJ+ERMe52YsYcTOR9mbOiDBTtjZv0RVZaYC6mJoCNC8eKp0lajgKIwVWKr2isdLM2cshhPvIQ+uBxXTgicIV5waKZkQs7tvaw3I0JNP2EZjUpVCUPl4Bt5EAtqpGpOtQHXjd5C6RuQ/hczx2PgaBGMtuOpOk27pgg1vPb8aSu2S/LNa75P5zqcBw8eOftsMxm98A==
*/