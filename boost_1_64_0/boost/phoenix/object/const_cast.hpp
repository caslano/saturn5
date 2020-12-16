/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_CONST_CAST_HPP
#define BOOST_PHOENIX_OBJECT_CONST_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(const_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct const_cast_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Target, typename Source, typename Context>
        struct result<This(Target, Source, Context)>
            : detail::result_of::target<Target>
        {};

        template <typename Target, typename Source, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Source const& u, Context const& ctx) const
        {
            return
                const_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::const_cast_, Dummy>
        : call<const_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::const_cast_<detail::target<T>, U>::type const
    const_cast_(U const& u)
    {
        return
            expression::
                const_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* const_cast.hpp
Sm8DxA29DIWFme9MWXErqPzrOMkWh+8k/A3B3wz8SZGX9jEYIy/mE2Gq+vd+2D4gSdLPJ4XcWF9ZudxAe1siOMXDQe6PSCulgPv7wYtaK+vswWKdrcDgtFwolPMKEMoLacWDW0Odrm5X6NRwagP7wzvUmM1aZEjKM0Sk/SlJUeeqFpxhUrVgZcYM6QIG2sbyXQKNrQ4axSRrrjbqGFWKoLBb+QQeHxkZREazKla1NGVIz65f2LlRhOtaNaKUIxoWJzpgl8KbC6N7CIozLf6f0yGvWZRetJvy5jJINw3Ea+5GPdniiaVAlqlbdgOFRpgQdOMVjMKONCFqBTtc6pw0RSDFvGdIhpV7a44JMTiUdyUhV9EC0+pBklRoI1L47H5/d7WcC1EJF/VR9e37fwgGQ/O/eSwCsa+ERGDHdiW9MJJG4zy12eeHTx3m66YO83nqYBM9v3IpBQ2aXZFOvT/44oWJarg8uICBZvqMYsiL+qP3BDaxjyI9u+jcFgyh+dDBau+SvWyn0yT9DvloELJXyxOe3sKYaLsy4fEbeMLTrdb75j3Iei77h1f0848n0NNClsCtQZ9YEbykj/6BxO5O7kY8p5A7GcKsxq7glrlNTGUA/zaVs2sbb1R5imyU4w8I0TwCRwWKWQCmIC2Qrp9/NFSyBlduGFQuSVICNIJst1HASWsk94547mi3AkjMknLlPNF2SBWnETlKU5gcDtCtmHPNkZhspvbJ7Qq1gWSQQ4RmzaAEceDkzbXRpusFrsUu5UPtqaqRRK5aJsnr3Bm61u3/itK6cZLYlv0FQXbbJwTbw1NAVaopRR3s58zgRswW2Qf+nOCs7rWSopIrXwrN8awlRdS49C+Vy3x9m1LmY0ETlSnwK4NlCPc323S4593EeD8RcfocDm3yQaE8x3Vcxr1qGX1FGYFQ57jnX8VqTd7fxyxG2Pe9rE58SG6+aGrfEq7VO4Vr9daiWuViH3npco31RXuKecRpD1cbhtThcQXBRawkCEUzsV8kR5KX9pV7MEsHbVW40uEMc+XiOEH2OzinU8eG+dwrrhTWnWIoCRUpG0T8eapElDHn1m1RKHP/yJQxuatfughtqb//9LLefsiXWQMbKBMMU3zZJ3N9+TV5wQQzQrhG0ENactP73my56MNPX3rSgGsHuELikOxLHl2Nysh5dNFALtzEBkIeQ+OEJ5CwZnssPeT9PaqO/TmxaT715UvcNFfkwxzB+wmeWKEnuonQCGJD0/rGs1XfZsXeL3TC6BvdogF3ABmFvbJIlsTHYXRIPrJBvK8rN49I186c8uuXFRtqECjFqr2eTsKy67lV7crRkwAxNwJxAK+KwzcyEoaMCdxbr/ktW5IJy1NpcYKeGgLnAxsd/ukHYRFSbCPs2MxwJShnONlmvgUx7QeWDNbsONXqxfFOPgB2GDlgL9pDefMcXJIZ9pSMfA6dCSfR+nc7F+tsySfK5PfAgjFFOz5271glUXpryl7Kw8hKivHks8mj89YwdoHW5cwsbHuISiinp1ol4vZ5suniQa7dPEQoxiAwEddrL0lA/slPyP55k6Kv0l5QxmDnKO5wp55Tx+Rh2kCVGDwYWssVRkKxBWbykJzsaGsvpvH6C5oAW8QuRtRpk7qLcWtRYTwdMy1KdnQQgLcbQoCffK8BXqW/JyUu4P2BF0dCj14yq/4l++ng0knD2fa7Iy54v7tCana/23je/c+z5DeKmer58+v3T6Xm90+dxovcP5X+yf1T6d+7X3me/cMvfrzw/UOaxdahbJEzPZIZ1Wj9uqQKAGeZb7PRbxaprPJ9rHpaUGWLyB/oG6AdRWWm6eyi6Rz39jqOaaXZvXiXUAxtC14=
*/