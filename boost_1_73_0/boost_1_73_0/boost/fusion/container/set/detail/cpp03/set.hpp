/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SET_09162005_1104)
#define FUSION_SET_09162005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>
#include <boost/fusion/container/set/detail/begin_impl.hpp>
#include <boost/fusion/container/set/detail/end_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_impl.hpp>
#include <boost/fusion/container/set/detail/deref_data_impl.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>
#include <boost/fusion/container/set/detail/key_of_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/core/enable_if.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/set/detail/cpp03/preprocessed/set.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/set" FUSION_MAX_SET_SIZE_STR ".hpp")
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
    struct fusion_sequence_tag;

    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, typename T)>
    struct set : sequence_base<set<BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, T)> >
    {
        struct category : forward_traversal_tag, associative_tag {};

        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<
            BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, T)>
        storage_type;

        typedef typename storage_type::size size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set()
            : data() {}

        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set(Sequence const& rhs
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : data(rhs) {}

        #include <boost/fusion/container/set/detail/cpp03/set_forward_ctor.hpp>

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }

    private:

        storage_type data;
    };
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* set.hpp
e6ImBPnjK1puEIC4cjj3+lOYQJXLB42YxyzRqduY/29k26M5GX7urSlcWOy2IXWN47FTa2TMVW3MxHcvSROZVsehkTT1WKVIwy6HE7DQX9U3OnZnzHdcOeAmlsVHsNjjcrtdsdQxxw1HbaQ2h/nGdDxgR+RzGIkAYoLz9nz3SRtBTXQMDPZZb0LzlyJaUsuN/DzBPAAeiS0ZPldnA+Hf3ORd41TTzP8yst5dDBMRJ/3ndEq+aREP65RwGfQR4XnYNwD+/eMvn8j0r/AwDd/SoRVrz7uSMq9HTXt+JzrO860+QhIj8qLOtMhcm9NTV1Ho+51BxtyY7h2+doKQaFm+uRSsinVajI0QSnMjtLe9D3Wbw3z1dVgmQhYZkInI1X9eUbS/GxONxVT0MRePnQk1+Yw6IWXU5LOJGwvRE1DKB62Rqaq0JUcOhuVhlvTqatmKvaCc4oiF+9QFU0e3RMo6DrsOMiLp2jRIZxlbHGS1/aRrJLRcInx8XapdN0udqiNKtjAREAN0cXSKiXxORPqvbX/wY6n2/85occ8DIPNlQJdpADBfBBCJ23DVx5sZYyqtP3FrDUjcAhBXrfhmVCcQF6/GvI94cGNHXKvtsFjFEA9S+HERijNLHtN0R7B1a2Lb90Rr9x6d/BxoR7to
*/