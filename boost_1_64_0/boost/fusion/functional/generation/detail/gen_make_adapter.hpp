/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

// No include guard - this file is included multiple times intentionally.

#include <boost/preprocessor/cat.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_CLASS_TPL_NAME)
#   error "BOOST_FUSION_CLASS_TPL_NAME undefined"
#endif

#define BOOST_FUSION_FUNC_NAME BOOST_PP_CAT(make_,BOOST_FUSION_CLASS_TPL_NAME)

namespace boost { namespace fusion
{

    namespace result_of
    {
        template <typename F>
        struct BOOST_FUSION_FUNC_NAME
        {
            typedef fusion::BOOST_FUSION_CLASS_TPL_NAME< 
                typename fusion::detail::as_fusion_element<F>::type > type;
        };
    }

    template <typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::BOOST_FUSION_FUNC_NAME<F>::type
    BOOST_FUSION_FUNC_NAME(F const & f)
    {
        return typename result_of::BOOST_FUSION_FUNC_NAME<F>::type(f);
    }

}}

#undef BOOST_FUSION_CLASS_TPL_NAME
#undef BOOST_FUSION_FUNC_NAME


/* gen_make_adapter.hpp
xuMSHINLcSEuk3xajkdwBV7ClXgTV+HPuBof4Rp8huvQmnStx1K4ASvhJqyKmyVfU/Lr626p083cj65KPQCy6NrJO+NH6IlTMBCnYhROw2E4HSfiTJyLs3AdzsZ0TMbLOAfv41x8g0jnYT2cjz64AINxIY7CRbgIU/AALsYruAStSONSrIHLsDOuwGBciRGYiuNwFS7A1bga1+BBXIsXcR3+jOuxiBX5hdUwDZvjRuyGmzASN+M43IILcStuw214Cj/B73A7Pscd+JY19wXogLvQC3djAO7BRNyLU3EfrsJ0PID78Ss8gA/wIBYuwP0BVsXD2AyPoB8exQjMwLF4DBfgcdyKn+JJPIE38ST+jqewdEHuH7ABnsF2eBa1+BnG4zmchOdxGV7ATfglnsKv8Hu8hE/wayxZiPMSHfAKtsSr2BOvYQLewHF4E2fid0b9C6QunDqe7POX3NfIdRTb4CMMxcdSHp/gPXwq/WeeYZH8uWuH77/A1tIW/y/WFj+GYzKJsJaQQbhFsFnI2PoEb0IMYQphC+E84QnBbhF/I0QQphDSCOcJDwklU17tGD5/Rvv/4BCl+f8f7/v/vJRGP799itTXOmBlrIO6984j5J0l0ea2TUqLkbltmxvOkAKmbXNZFyRtMXIxJqD6PWy8ybv1INM+w+r2YvJbN5JQmZBI8ClPXoyUfc5qChcaGxeai30vYbSv0rf9Je/Xo3LxvjkqmhSYtEOOHaRvYyTvEcOkff4RaR+xF5V9cXvPzL5oo6K1QbGBUcFhun3KeMnxPD1afzx16ThjZh8vmOzjFZN9vKXaR9N2pf4mbXj8pI2X/Ntce1wZ63GI/t+eJse6h7z7VI+lYDrOo7p8+pq0b+2ka4cZkz/zxO4E+5IM7fwn4hHdPkVEM5iE1l2OSdZ3QvjON6yrMcrQdtPfTNtYaz4XQOgun83aforJ9lvL9rNCfTn2JaWNfQZffAsPom95/mesbluhCcER4SGa3Lw7LlB8/7ic2sMEmvR1CTI51+JJs/H5GRcW3jeeW2x1m48fpG28nw3lFL3RTymn43XxhkcxtkWUmfMu9SXp7v6xuoymmSmj203KaLpJGc0wKaOlpaxLOwvdiahvv/qSsjslF2XX36TsepmU3RgzZdfBpOwOeUnZLaPUTZL+dDLnw4mGcuiqPk6Z5VY+f4vPO3P9CPpAPm+mnRqft/T1t/T1z3Nf/yDdu/wmwctnBFlV1T44um795duzNC/u639LI/chcn9CHQv98nXPGCx8T54BSqCubgedsQy649+wK5bFQCyHfbECDsWK+B5Wwuloh8lYGZdhFUzDangQq+NJrIFfYE28irXwEdbGf2AdfI718E3SXR9LYQOsgI5YE52xDrro56qVexC5N7E3mat2pOzvKGyPo9EHx2A8jsVEHCfbc8gv9wFyf6Bsz0PZH1SWI1IXdRRrYwY64yl0w9Poi2cwBM/iIPwMJ+I5nIvncS3+Hffj53gCv8Cz+CVewq/wFl7CR/g1/gMvY34SeQWL41WsgNfQBb/FJngdffAGdsObGIi38D38CSfhPVyG9/EoPsAT+BjP43O8ia/npw4A38DC5EkJdMU3sQVWxHZYBbtiVXwXm+IwbIZJ2ByTsQUuwFa4ElvjRnTHXeiBh9ETj2NnPItd8Af0wfvoh8/xHbRT6lzRBf2xEfZAV+yJ7+K72Bt7oxb74BjU4jgMxMkYjEswBNdiKO7AfrgXw1DXhiSf3ENAhpx3yvnlp6yQOWrfwiZYCVuhI7qjB3pgV/TEcGyDUdgWR2E7HI9eOAfb41LsgOuwI36CnXAHdsET6INnsSteR1+8i2/jE/TD/DKGcCHsgaU=
*/