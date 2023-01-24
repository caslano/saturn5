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
l7sjiRaz8j8WiY5MjORKCDpIFgeGmk2aeV9g/CqB8cjMB/BTJ+G0nsHtJsLpfRVyzwS+OdrTsdOQXbH6Gv/1ED95AhDQ2eiM+aTnEokMJ1gq9uEo7WPwTtCRZ6DGNnSKdhTVf4rxKGpCkRWvf8NYXw0xnHA/fGVSun4a5fLHdYLTqNz0aO3UW3W8O81qEj3TLCdF4rQcjPrF0JNW2Hz5NKthJgzuBKrjjmlWsZwkT6OBy7CWi4sMlhMJLSduuCJbhCI1yme9pnFDCFuwa6cZnArZeotPycoaiaMskaoWoiCRzr8L+U8i2UHxk/jJ14WaqeU2STO1jJa4qcXgOPlkobWxtCROfYzejJpAV1po9Fkj8fpmeBe0ZcpbtPOuAoOI7SRDTB6Xsb/oiTJ2QZMytuU+HgN3CT3/WkzP3/jz58UoVS/ln+/jz730upoeVfTYSI93AVT5Ot5okHl+Ktha9iqP8WqXUdEl/OciBHkVQTDUIGPddzMQJihNwU/L4rnRZiy9zeWAQ/jz6P1Qqihes9lcvbhZm80P3/0PbDZ/TfmvbTZfTvn/ZrNJ3yFsNr8ta95m02K5wWaTV6DZbLIKQmw2hVOatdnc1bdJm83ovprN5oPJ57fZbJ/cpM1m1/Jz22yendLYZnPHr/8zm82Nk//XNpt2U85rs/lpEona/Y8YbDZjljRns4H5CLHZiOtC/79sNhmTQqwFXSb9
*/