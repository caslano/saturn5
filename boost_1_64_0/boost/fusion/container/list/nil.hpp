/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005, 2014 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NIL_04232014_0843)
#define FUSION_NIL_04232014_0843

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct void_;
    struct cons_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    struct nil_ : sequence_base<nil_>
    {
        typedef mpl::int_<0> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef forward_traversal_tag category;
        typedef void_ car_type;
        typedef void_ cdr_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        nil_() BOOST_NOEXCEPT {}

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        nil_(Iterator const& /*iter*/, mpl::true_ /*this_is_an_iterator*/) BOOST_NOEXCEPT
        {}

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void assign_from_iter(Iterator const& /*iter*/) BOOST_NOEXCEPT
        {
        }
    };
}}

#endif


/* nil.hpp
2+B7McQZ78WQ8RjpG6GPi/W4R8Ly5LtW/fJijc+B7Okg75DrR78HHIpTyfP5Zdp27fMzLa77P8MvdT+XkiJ1qH8XBEh+ygtBjQt053uc/v0Nku9Y/XseZL7xuvdiyHse7PKOBG2eONf3OrvjDO+WkOU3u59UpN5PmvHnPe9En3l854efffjq7ncq1kk/knbafi+1qN4b4b3BcoyQ+0l9MQL74yQcgE0YhFv58kDci4PwKA7GmSwjGF/EIfgmDsX3cRj+E63YXd4vMBiHYzSOwAcxFJ/AkThJ3i+QgKNwNobjIx25/4TPodr/BNX+JxiNn+JobE+9jsFAHIu3YAzux1gc1on7T3gU4zCHip6Aq3Ei9urC/Sc8jPF4Ai/Dj3AyOrqyj+D1mIBdu7H94WCchpF4OU7HRMzA6fgazsBFrMQkXI7JuApn4hqchaU4G7/AFOzcg40ab8K5eDfOwx9hKh7DK/AtnI9hvdg+cAym4URchL/DK7GClb0YG3AJvohL5XmjUxbZj2T/ssi2dUJ2muXyPoqVGI1ZOAmzMRVzcCnmYhXmyX3C1ZjK+lmDh6j3fAym/gqwhnKuxXM9eW8CprN9FuIRNsZi/CWWYDA7nB0jsRTnYRkWYjlW4gY8gRX4GVaicny42uO5qICtnSwxW/338vyTf/JP/sk/+Sf/9D+4/s8vyslV/lEv/79523+X4Zwbezwv/zfpM35OkRPmgHj1/C7liulJrb7rryfXqeed84cyerE2hvWhPuq14wZ7VpFN//6/S3Xv0Osv17MOi8Rlca0q1z/52nWuTf1s18b2KvZ4loDl654lKJc4WZR2fZoSqbbFq+POD6eM6cXtuTaylRcVVWaRsnqv4k1OXI++rjw/X2QYyzpfroHeljEXf0cIZRmJl2n1lJWUnsG4b/ZKX8YGU+qs22R3nfUx5NGW66iQZwO0uDIlzpCnU+2aj6MWRp6yJxvztLo0L8+XPBnzoCRnTC9F7hX1JHSUcb0ilWtqj/QYqpE13vp4Ya7r1/AoSc+jL8chSW+ppLWIEKVsm1OM6TEaeqvX8HK/wGvZ4uR+wWGpy0cJ0aRV7ZFWaR5vjvShLpX1OyrB2/olfY93Vh6R9BcS+hNSCWNI355gTJ/Us1YX5qwp8yEPZmka76WoS9LXufZ+wfcJUYTXCDH8p0mXj1kFxdr4m7WtvAPELu8AUerj0anG+qgzydtu/T4tcfXaPs0Orb83QuB+lVZO9l0+rypf7bEdxcuzMavkGLeCME7Zjqa5yzSHseh8Hb8z0STfKcbjmta/iYVKvuX4J8dFKZ8hnxlyqfl75dkXfB7jlHuxHvnMyqtQ83m8lbpv1NV9+gxj3Z80KcMpkzI0mZThrL4MEnceX+6rro8ie6Hne10L1M/h2ue1zcbbZrvW1uN1g5U4Rsn1qJ9zUj8pMv5KEmGiso8kuetnsd2W42jD+01N9g35zWE5OZ5jSlIHnuuss3vM0T6yfU0iTyd1eSoruLpNx1/teOgx7vdxSatE0lorx3uL856dcoKQxbeycgvzcorL7T6n53lM+hQz2nkfw858rMD/3ViK5mMmeh9j0XzMRO9jR5qPveh9bETzMRDbPkah+ViN3sdeNB+L0NsYi20fA/Fu9d7xP+3byl+cfuin1fbPn7w9vP2vvI2N2PKYho0WOceUc88A6qAvHpAN9EW51/wSRuKvcRyexGn4G0zDV3AxvoY2fB3t+Abehm/ibnwLG/FtfATfwZfx9/hrPI1vYBM24R/xfXwXz+EZ/BhZlpzzsSzJdwBul3w/Jvc+f4oj8WeS/8M4Ex/HufgE5uGTuAaP4PfxKazBp/EAPoOH8Cgew2fxJfw=
*/