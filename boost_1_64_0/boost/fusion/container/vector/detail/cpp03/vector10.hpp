/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR10_05042005_0257)
#define FUSION_VECTOR10_05042005_0257

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector10_fwd.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/container/vector/detail/at_impl.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/detail/begin_impl.hpp>
#include <boost/fusion/container/vector/detail/end_impl.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

    template <typename Dummy>
    struct vector0 : sequence_base<vector0<Dummy> >
    {
        typedef mpl::vector0<> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<0> size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector0() BOOST_NOEXCEPT {}

        template<typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector0(Sequence const& /*seq*/) BOOST_NOEXCEPT
        {}
    };
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector10.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector10.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

#define FUSION_HASH #
// expand vector1 to vector10
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, 10)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* vector10.hpp
8LKq5xekZJa1rvPMTwtkn7WQQWcCaH8+Vsv7qsa18epPgOddVgpXX7mOZF7GOl2/Ad7t7Q1x2/tke5OkfkeSxrP8Ca/tZVPTM22ZWdnpxXlOW3ZuXkDjd+jrW+IQpP+EbHu6M8cVE/yxlLtjqDHGfr08z8/lP5thJk5kfdEPmpeRsvn1XM7VNn69Ot6HPKfzLmuOVlbWLMeQWv9FWag+k58kdU0xXMHWzWX77e5xswrSZ+URWM6+cBjHtwmTZ/Ob5Lncg6TJrMuywXMb/Rs3TNm2RRu057facS9l9oiZKJX8b5fjYCqpD8tW6PPnExbI2FcttOPO8Iw1Up7Zd5V42ShSKssmPKTlpR9dMZDYe/VY12Lvecbq/dkKx7b1PD9bxn2yyWQMwKnKs1KvchakBxKLr5XReJyHmowBOI1lt3rlx3gwtLWyMZTL1daNft+/LPl+JfdcLpJmKPteny9HnT99hyjH3Z6N6nHnMQaNsdxNDP2oKHXoeexox+lAeRa683qJ95Cybifd7rqx48pTGUCnaqAxDtfCfNd4N36We9Um3efFWG5WIv2+eI4zJ9sR43E+aK6dI+T9nDqLJJ5BHQdO/3/yGZHtLJVn6W/J99BRUppyXq7aTrJX9ol7IzMKC7Kr38amsk1x0hZEqSf9fvj7La75rEv6dtH1cZOh9GUi2xWHdq3ss9IdWX1itG2W92RmOTKKcu1O3XhRsm2XZdu6ybmmE2mWsm0Py7apzWRsVSdSv8f3leNHzsO80+P4ccolvU0+z9NIGSwb+ojvvKnmauvWPF9tf5bJM/w+8hynB9p5mF/uI19eVvv91YRj9r5H3cdsfla+jePWY7+xFjk3NZfvMSdJm68cj1rcSZ167rGHq86didjCcKwE9t3XxPDd58y3e9TJ+Ru8Y1EyWYd1s8Q1SAMsNRrFj1gOfdxEyo3eMSI5vEjwXH9xfrXrrdrubDVuwrgtZ270jhGZw7J2j7yISPHjWDbmOcxkXKtYr3GttBifzAbeZclj+X2eZSFi5WrL0UTK0UKNWTGW4XwD75iVApatNJbBHbUSQBmy/YxbOVHbd9yKebyJ77gVnukyv3LIuIjiyPvWvhIef1/ImW/+yjPwKGV+89eWrL3cNvWnq0pG7b/7pb3H+Y3lWs+vF7/7xref339x4ZpWzZ5fO72e73gN87gP33Ec5nExvuNxzONQai6OxldcT8toZf6Tjz8x7M66db4ZkhH7VMFHsVwFLq2jzN82+Wjdhnf/+9k2B95rE7llFA+KenZX5l8+/Xr9h5cuLx/5/hfpudPbn+FZo2u7bn9p8c7Q95ruHrXi/My8S6mP+47fMY+X8R3/Uuqaf2Gt9dGuRwouL/9s5+EVO1vxgPxr1363n8i/+/PKjm+8u25oRNTZuFd9xfsEHjf0eKgyf8MLA7af3bb4g62PfFpo+bgHC8921duIsRnNz6ZejAqxR5xZ1vsS+brG27DIta9cE29lW69D3uaa7NLWbh42xyLshg4cjsWoxtXI9VaZrEcfV9NBntd2wqHYGadiFyzBKFyGXXE5dsc7MRrVcY9k/Umyfn1bsTVSzrXYDu/DKLwf4/ABHInrpLzHLHK9J9eBrM91XnlZ1ndE4iF+jq3wF9gJ38A++CaOwLdwAh7HKfg2zsN3cAOewEfwXTyEJ/EV/A1+hO/hOXwfm1OO3+NAPI0J+AEm4oc4GT/CNDyLmXgO3XFVcm0Hm6R+9HFVM6Xt3+2yHWnYA9NxEs7CqZiF2Zgt2zEbHZiLi3AuPoB5+CDmo+wfubYjD5P9U0/Ge7kem2N9jMEQHII34FRsoI5vI9dv2FXWp41v434+fxM2RSs2wygMV8c=
*/