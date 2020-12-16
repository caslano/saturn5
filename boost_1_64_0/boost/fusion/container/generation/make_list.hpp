/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_LIST_10262014_0647
#define FUSION_MAKE_LIST_10262014_0647

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/generation/detail/pp_make_list.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_list
        {
            typedef list<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_list<T...>::type
    make_list(T const&... arg)
    {
        return typename result_of::make_list<T...>::type(arg...);
    }
 }}


#endif
#endif


/* make_list.hpp
x/NYhD6U3RPYDp/EaFyJ43E1zsCncA6uwVW4AXfhRtyPz+Eh3IRf4vN4Fv+JAZyTLdgDX8Rh+BLG4RuYgNtwCm7HqfgmLsJ/4SP4FhbhDtyAO3ETvoPv4S7ci7vxR3wXL+Ie9PfhfYFN8QMciB/iENyLU3Ef3ob7sQgP4Go8iK/iR7gND+FR/ARbcD1+ip3wCPbAMozAz/BWPIo5eAyt+CW+iyfwQ/wKj+ApPI7fYlNu2N9hWyzH9ngag/F77I1nMRJ/wCF4DsfgebwFf8SJ+DPOwQu4HC/i41itOseD1XE31sD30RfPYk38FWuh8pu2Np62xVSR3yq4Wj4P6mGmSZ3S5fMlA1virdgJJ2MYZuIgzMJEzMY8zMHb0YKFOAUXYy4WYR6qn4vymwbrGnwuLiSfvrgI6+BDku8gUqBuveoYIOs9LMsvQXU/8nsCuxjspx7LNcH62BEbaNYrkvW6G6x3lazXBIOxqWM9+b6OPQzWq19NXa8BdsUr8DSWk+R7Nt+/1fWaS0xKZWrO9utjIF6HrXEwtsWRGIQJ2AnTMBinYWe8C7vgPdgV52F3XIwhWIRhuBr74kbsh1vxGnwLI/B9vA4/xkg8ggPwK4zGq8j3YAzAGOyAQ7EzDsM+OAKvwZGO8pLv8PLdvtikKS8p34ZSvi2wGe7w4Lkc8WG+pkxSIWkFqYS0g1RGukBqzIdUCCmOZCEtIBX38v2vfJ7H3l6+l/VMj2YDyGMv37/0mR7E4PlDn+vhaXydSz3XI8Ti+myPOD4ojJ7vkcl8o+d7XKCMm/X2NYWTkkkFpMWkEtIu0glSvT6+pi6kaFJyH29/RO/knbyTd/JO/52TDyn7j2r/t+RkTg/tGdLL8Y/LHwOgtEGv6mByxGWOlTH8e0lNSe+Rbgnle/R223fOONlx0uCM7JRMD9qJ7bG1x4VKm4qzrVLq+rNSUmVeoEHbhz1f/J5lYh42xV9ISWwz5E3XfF1P+3JV6vv1+QpHH39bu5p5ui4PC6RObwM7DMC1mBKqVGC55uEGSxrdIi6vbNQ8ZGRbnG3LUjaZ5myZF+RSXvoyzKWl1DV2ermaf+aoky9pe2d+t+1wzT85ScrLmMERVN6O5Wij19RB3UaqTZpBWsmPshJ1+zf07BE/MtyDbTZwaRuz2F77q/FOeT3VZZ87ZJ9WOZ48Uin7jNup7jM8fiT79Xyfarlb5LxL3wP52rkNW+NWHB1Kear7sNjLbYLSDiNtPcWVnPcSrFHT9bxvMTjvpdrzLm3XOxxlYUlJm8D1LssmO5ZN62GfF+9YNrcnOK7x1FC13dc+L8ixXHoIyPvDMc+xvVjHvDzH9ro4lwvV9DuQealynTvyEWpfL8y5nmNb7ZzzwuzzLM59OtaNcW7Pkbdo5zzHMaQ7y8Sxjzjn9hzrFjiXc6yb4JwXCi7XhFXand+vrt4LduENLBXyvus1Yc5y3o/SK7kmLAbXBFa4T87GKNt1kp2TnWq2zYtwHNOkEH0ZMc9x7JHOedpzJcdplfJxXh8G5zjE4Pz1MLhmQiuel0mO5cINzn2C9tzrr0uOP2+yOi/Rub0w/Xmp5yftPfI5cSOayUnpXpfz4nE/JymzCuclxvVzQu692nLTxq1x18bnro2y6m18v1c8m6q25blrk72ptTJ/2SO9Xow+/eKG60bNOPDNvnF91Da+ZJN8n5DvGeXyeREvBd+4OnXB2BxDMADjsQUmYku8E1vhSmyDpdge38MOqMbTlu8H8r2B/Wjiaat1601xB8bgTpyOb+M6fAcP4bt4Cg/jL/gpnsZSk3z24wbZ/lWkzbL9r1kuAH/AvnhO9nMe4/FHLMCfcAX+jBvxAv4Lf8Ed+Cs=
*/