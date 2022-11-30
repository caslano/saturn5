/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_PP_FUSION_DEQUE_26112006_1649)
#define BOOST_PP_FUSION_DEQUE_26112006_1649

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/deque/detail/cpp03/limits.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>
#include <boost/fusion/container/deque/back_extended_deque.hpp>
#include <boost/fusion/container/deque/detail/cpp03/deque_keyed_values.hpp>
#include <boost/fusion/container/deque/detail/cpp03/deque_initial_size.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/fusion/container/deque/deque_fwd.hpp>
#include <boost/fusion/container/deque/detail/value_at_impl.hpp>
#include <boost/fusion/container/deque/detail/at_impl.hpp>
#include <boost/fusion/container/deque/detail/begin_impl.hpp>
#include <boost/fusion/container/deque/detail/end_impl.hpp>
#include <boost/fusion/container/deque/detail/is_sequence_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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

#define FUSION_HASH #

namespace boost { namespace fusion {

    struct deque_tag;

    template<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename T)>
    struct deque
        :
        detail::deque_keyed_values<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)>::type,
        sequence_base<deque<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)> >
    {
        typedef deque_tag fusion_tag;
        typedef bidirectional_traversal_tag category;
        typedef typename detail::deque_keyed_values<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)>::type base;
        typedef typename detail::deque_initial_size<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)>::type size;
        typedef mpl::int_<size::value> next_up;
        typedef mpl::int_<-1> next_down;
        typedef mpl::false_ is_view;

#include <boost/fusion/container/deque/detail/cpp03/deque_forward_ctor.hpp>

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque()
            {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(typename detail::call_param<T0>::type t0)
            : base(t0, detail::nil_keyed_element())
            {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(deque const& rhs)
            : base(rhs)
            {}

        template<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename U)>
        BOOST_FUSION_GPU_ENABLED
        deque(deque<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, U)> const& seq)
            : base(seq)
            {}

        template<typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        deque(Sequence const& seq
            , typename disable_if<is_convertible<Sequence, T0>, detail::enabler_>::type = detail::enabler
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : base(base::from_iterator(fusion::begin(seq)))
            {}

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque&
        operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        template <typename T0_>
        BOOST_FUSION_GPU_ENABLED
        explicit deque(T0_&& t0
          , typename enable_if<is_convertible<T0_, T0>, detail::enabler_>::type = detail::enabler
          , typename disable_if_c<
                boost::is_same<deque const, typename boost::remove_reference<T0_>::type const>::value
              , detail::enabler_
            >::type = detail::enabler
         )
            : base(BOOST_FUSION_FWD_ELEM(T0_, t0), detail::nil_keyed_element())
            {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(deque&& rhs)
            : base(std::forward<deque>(rhs))
            {}
        template<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename U)>
        BOOST_FUSION_GPU_ENABLED
        deque(deque<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, U)>&& seq
            , typename disable_if<
                  is_convertible<deque<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, U)>, T0>
                , detail::enabler_
              >::type = detail::enabler)
            : base(std::forward<deque<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, U)>>(seq))
            {}
        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque&
        operator=(T&& rhs)
        {
            base::operator=(BOOST_FUSION_FWD_ELEM(T, rhs));
            return *this;
        }
        // This copy op= is required because move ctor deletes copy op=.
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque&
        operator=(deque const& rhs)
        {
            base::operator=(static_cast<base const&>(rhs));
            return *this;
        }
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

    };

    template <>
    struct deque<> : detail::nil_keyed_element
    {
        typedef deque_tag fusion_tag;
        typedef bidirectional_traversal_tag category;
        typedef mpl::int_<0> size;
        typedef mpl::int_<0> next_up;
        typedef mpl::int_<-1> next_down;
        typedef mpl::false_ is_view;

        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque(Sequence const&,
            typename enable_if<
                mpl::and_<
                    traits::is_sequence<Sequence>
                  , result_of::empty<Sequence> >, detail::enabler_>::type = detail::enabler) BOOST_NOEXCEPT
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque() BOOST_NOEXCEPT {}
    };

}}

#undef FUSION_HASH

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque.hpp
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
*/