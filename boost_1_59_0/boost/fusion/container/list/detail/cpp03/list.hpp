/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LIST_07172005_1153)
#define FUSION_LIST_07172005_1153

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/container/list/detail/cpp03/list_fwd.hpp>
#include <boost/fusion/container/list/detail/cpp03/list_to_cons.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/list/detail/cpp03/preprocessed/list.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/list" FUSION_MAX_LIST_SIZE_STR ".hpp")
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
    struct nil_;
    struct void_;

    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, typename T)>
    struct list
        : detail::list_to_cons<BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, T)>::type
    {
    private:
        typedef
            detail::list_to_cons<BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, T)>
        list_to_cons;
        typedef typename list_to_cons::type inherited_type;

    public:
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list()
            : inherited_type() {}

        template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, typename U)>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list(list<BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, U)> const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence const& rhs
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : inherited_type(rhs) {}

        //  Expand a couple of forwarding constructors for arguments
        //  of type (T0), (T0, T1), (T0, T1, T2) etc. Exanple:
        //
        //  list(
        //      typename detail::call_param<T0>::type arg0
        //    , typename detail::call_param<T1>::type arg1)
        //    : inherited_type(list_to_cons::call(arg0, arg1)) {}
        #include <boost/fusion/container/list/detail/cpp03/list_forward_ctor.hpp>

        template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, typename U)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(list<BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, U)> const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::enable_if<traits::is_sequence<Sequence>, list&>::type
        operator=(Sequence const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }
    };
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* list.hpp
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
*/