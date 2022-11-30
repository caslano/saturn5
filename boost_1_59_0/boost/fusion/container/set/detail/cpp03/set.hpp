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
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
*/