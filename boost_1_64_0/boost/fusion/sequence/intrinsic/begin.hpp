/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_04052005_1132)
#define FUSION_BEGIN_04052005_1132

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_begin.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag; // iterator facade tag
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct begin_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_begin<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct begin_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template begin<Sequence> {};
        };

        template <>
        struct begin_impl<boost_tuple_tag>;

        template <>
        struct begin_impl<boost_array_tag>;

        template <>
        struct begin_impl<mpl_sequence_tag>;

        template <>
        struct begin_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct begin
            : extension::begin_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence>
        >::type const
    begin(Sequence& seq)
    {
        return result_of::begin<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence const>
        >::type const
    begin(Sequence const& seq)
    {
        return result_of::begin<Sequence const>::call(seq);
    }
}}

#endif

/* begin.hpp
8dFy5zW9aLnv1PjpeyX4/PN7x6A1wMtc02UiD6Ov63VlOmF7vr+2PVFGeQdeqa9pK/Ex2DlikLRGYTyj9ht/k4bBleWlMt4gYPLInn7FbDA9fQpyipipMzsNt8YmbLs64JvfpzbVgMf9BQeQsxyhL/b74EV0trMyQOwFCIapjfLjIY3GUt0i/dtIL2Z9VADzMgwjHdocyXLvuIXQSdnXCE0v29hK6LhIPyb4kc7LJfmKkYZtQs7aSMd3PWz7/Zj/ADFMNyz31dvxd9QZdUIa6ivvs3cATbzJ5qudd8EkGUHJoBpirjdgznWVfrZTwYjnYl4//G51GBCCsUV2CbprU1WUGJsEQ1TBchZ3S4yiCtLvEjqqIe1j9gh6OSaAV963Uxrwyb38+qhKm5rNTwavnwXhxU6skIJYGNkPwjKpUp9LFEv0ObCX0oBTxtVFGv0eyPtkSaffAngljX4JNfbOPh2jyvgs0k829q2Jp2gYrW9dJZjCmEbrF8Z+DSPEyPsjiWnso/lTdQxIQfpNpOP8BBKQH/aTGp30zVuUDnMI5V94mkYHfsVGgtKBV9IWHyM0Uvc7jFbsH5rHef/pGkb7Fv9SMXob8pxQBKP1rZ3PEPTmcf4xDaOP8wOPI6Z2nH+W0LVxDjmcBV0f55eRpo/zF4+rtCmpXgDmhJVxfvuBWJCqYD/5LI59hPnjxc/m2EeYP65RLKmn8RykafPHdaTVzx/OQaRr3/gbSGueP/Ln6hhVxk2kN88fC8/TMFqf/S1imueP/vM1jDZ//Etimvv+IYLR5o+dLxD0+vnjokanfX7fCwldmz8uEbo+fxx4EdK1+eOTlMb4SDz6l5R7iHnMglymw5VxOuBsptomZjFc2kbehm0TVd/iF1f2rmePHUVrp+fhvWc9rr1McQuDOg4u9PhmS+Ju1uB6iJN3Jmc2A07G3ydt9SLcIxJWLGNqk4bhLhbF25W0SdBxsIdjr05KfIFqu5teFicbj4+i+jm/sGqbwA/Q7JI0DRzEXtn0YCx4ASH2s4MPxvbX5f3spzfXYeFrlbedKHNsqAmHPmdyTanFUpvHkeFajFbujUacXu5btlAsi9kATt2r71Ha/H1bGzCiwSUW4uE0YEWDq99yWwNWNLjqU7udYHlUFlRVxoLcQXAloHTIRky8k2Lgi2h1/l4NBi7U2us1db64qwmLdcZ6dHfr2D68jwmxGKdwTzMOROI4HxsFnBzneN93qfhdf1fnDYe4g0+qx0EFmM+R9E0nOM2WAHHGXoqj7/nSb/vW0jg8A69z/xfwxeycJ3FJDlXmDct3bRMe5jY6b2As9fcOkNw0ceAneWIaEPCu6BwnJturq9Js/oQ6z7+g8hYj/cfkd33xJh0n30kVe+QanHwfHSA+rRRH/ZcwlqOGw/tzcudBMZg/ReqlYYj6Uq+hKo6oj2PiYxpO851C/UaHKVauI7LcD1IM6zO17Qth7DWc3r6gXwWHbVIucdIWbquGQ90eE21HMexSGvc8EyOEBi8Y0OOUdrqCdPHd9D72UvTHqsfSd3+J/2wDXvUjLWwdMV6thof6auJR96/V4ql4vEfeAVjhL4bNQX3G7jFM87sCz/mgYbR3gB/VYqh//vVXDii2B07s24Hl+AZ/36R2Covblblo0nXTzInBL7T7xHwPk/hi3oMPbVJtIFotx/IT8JM9D/NbMQJKhk0C/+2/Uh/VxMnNFsx3MK2BG3anvVzJP3yL4hPHT9M0ygs8NDz0TZqj/K6KB7lR6qVevHGjb2YDsDoF+7l7IA9tDfpzZ5faBa0PtIGfMjuEwgWDU5RYsUVeGFi5Zs/2wLl8frFEYF/68CZG1yyC2Z5ABI9B7Pg=
*/