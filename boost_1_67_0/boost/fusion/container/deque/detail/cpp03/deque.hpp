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