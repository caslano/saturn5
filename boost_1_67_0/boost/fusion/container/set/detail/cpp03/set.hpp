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