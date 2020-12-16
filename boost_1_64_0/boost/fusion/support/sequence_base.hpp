/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_BASE_04182005_0737)
#define FUSION_SEQUENCE_BASE_04182005_0737

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end_fwd.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        struct from_sequence_convertible_type
        {};
    }

    template <typename Sequence>
    struct sequence_base
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Sequence const&
        derived() const BOOST_NOEXCEPT
        {
            return static_cast<Sequence const&>(*this);
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Sequence&
        derived() BOOST_NOEXCEPT
        {
            return static_cast<Sequence&>(*this);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        operator detail::from_sequence_convertible_type() const BOOST_NOEXCEPT
        {
            return detail::from_sequence_convertible_type();
        }
    };

    struct fusion_sequence_tag;
}}

namespace boost { namespace mpl
{
    // Deliberately break mpl::begin, so it doesn't lie that a Fusion sequence
    // is not an MPL sequence by returning mpl::void_.
    // In other words: Fusion Sequences are always MPL Sequences, but they can
    // be incompletely defined.
    template<> struct begin_impl< boost::fusion::fusion_sequence_tag >;
}}

#endif

/* sequence_base.hpp
2z9w2zKvxg9MkPYWbGgb2II9AfGobDoqQoAjUTUGGXgGHTrf8qxqFyRNETgmet3SZpKisl3whmCbV8xDME8nNfeqM4DQGz4gnmstTyIhaK6kHuVgNVLhZP7sYB4ubOAqBoJe2ic8J7i/kmJCy6wgUdVbQT9Hno+0PKX6amDAHRt53HjQBZ3GPJaJzDqWxrbB3B55foj7LWibo5SOjMfYq7Nz+C+egM/9VsvoQmqZ+pdAHDfjDxO+0nHORJPJ1IGk54PYPC2fJ0EaEZkfumI0bQTf8yfi2F6cSWacGRj6LwzMcx/MY3hkWuk48CCbSLizKTwoFiGz2sdkycS5Zck1rqeXW77nWNsxLa0hddc3fbOuDrKTltaTmhaMdnxB26r0+kCfMT2TwqosEqmfkb1JC5LhoNCjGDaaa86l6dfr2UIN9zkT2bkMMrLAyGS/nerot1u+QHhmwbGqOoOJlRntYAeZfoxlclTQsh4qMhxx6DGOOfeLln4tOpeY8RSm9cxu77dIFkG8pGUPGZcn3AvYRvcvE12LNETN3DjnIAzv+C3zj0nfpZSTir5bLO49pICv5iYfH77P5JkLTxPBj3KTPIyPb3me4yj1XGtHll51ve4MtE9HtMJLHSmnpPeiw7SrLe1zmZDU5pxI7zWHx0MXWhSf2XGhi9yjLxnOuXcN1Z2pcdwFRWpmzbKZT+4ECi2ag9XuhHtPJo5u07vBa9dvQ2POi+4qETSBszBYFM/G/D14HJLJXY7GEOxztGSreet+8uCyPz+k8rR2LzhH3nahufXQngYOv0AD9Zx7WE8DJwcggnp+3NOMO/iMprwXAA3sqD3V2B6ggZ0NKnpkT3PuEYjGiPIJuMjF15cfQDks8LM2v7X2T0+HFs6mrt/Vuh4JNOMC0/ZRT0cehdrUZj6EfrzPo4EGps5A9Mi+Tb9Y0oCW9uUgW34MlI+KhtrT1wN0o3b0ZCiG8tdvw+2Z5r0Tt5/TtHnvfn5aOfgC9r7jd+hpQA9xzsGPzMpxzsF/zsrxm9m1O/blaBxxzsFfn0qDcw6SO51C02OBDUxD8yIPooAt2D3ujMsLBPC+Z1I27ac/9uXjXMT9pO8yLcf99PNZOW77+btCeSmEWL7jOMzKC0A7DrNybCd37W59OawBuP5fz8px/c+7+6wc2Sh9GcrH9WOqr3e5x5ym1df3zMuHIQaaP2GaMYNlg5PvOadpczT9al5eYaD88fdC5bM5cWtWjsf6DvdG5bM58Rooh3V0JsNv5zRIBnGfeXlBAYzvQzmss6BTYG9T/mIa0CuguXUqDR77v/U0eN3Dc/w19zuNBs/xP5xKg/tu9f5AA2vnVM9+eApNq2ePfsC8fKpn7+lp8N6CZfrbqTRYpp0HnkaDZfr1gqa+Qhe6Zq1u9eE1D2pp+rW2jROGy8c1ss07+uCGBrz2x/JHn4fycZ1q8xpBebvOjOX6IVDerBONvS2U4znetuH4oUDTzs8xR+7DZuVGtHsAlKO5MerPw8dyrNOND+tIg3WxHddHAA32LAea2iigwePf0Hx5QVPMg04de4jvAjTzsS9ls/L52D/60YhmNvbfRuXzsX/0Y6AcjT3wo/L52D/6sVB+5th/H9HMx/7Jj0Pls7H/ISqfj/3THw/lZ479j4Hm7LG//ASgOXPsfwY087GH/HkPad9nMtFMhs5G8V+/z5ToFQvf8HKuvPczyhrxh/pmVD5YXr1xcND8vjP8frIsqPnC71d+/8UDC379fb+YhBwdQh7wB9SyB+OyV58cbr+ulhf77YeU8qNi2VRKyovTwd72wpSpPmEtyx85K6/r5lj+2FP4rx/U8vGs9vjyhvS12xKzC7u40o7drdE=
*/