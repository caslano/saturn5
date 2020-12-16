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
uctx3o3j1+b3jMTVQ+Ky1iXyW2wX1xSZkk05X8g8IS7iC8LK8q1cm7foqsblG3TaMT7yV4Flq86jI/H3IjQmWMd3IP4ko/gTJ81OHD5k4I3v40yZU8HueDBlW8zTsx3St7ya/liNUc4lztLH6PY3kj7bHG+c/F2kb4Ckr+MtxuXn85KT9CVnpVvSk00ZN5BGW3qUDTlPo7ZOb5c0tpI6HUQYRhpjDdOYPD0n0+Jx2rTxRct8ff0lrnDCCOLLNYwvJST9hsvCVp/U82s1tXzknCd/k3ZE2uPvaHX99TGWtJYYpTXb/euitlzU638NfVwjlbrysmNcmrGBPbgWS5z2c6AaxDmKOIN0cVrHrXU7Ls5luv3uW1MfVxzLRTjGJcPSMo6x2/EZ1TOLxFfWJjCQEE98Sbr4ZqRmKQPDelDPjPJ3taYsKOfqOwmjWS7PLr7s67o2SP7Yrrbdo7odu3p0UOb9e1Dur9YSxpKOUsd0aOuRG+0Y5f5KTYvMe2k4XnUz9V5H7rMc4tLWwYG36dM7TjmHv2KfXqmDHqdT7gMdx1+WeaQkfbJt7f78zCBd40mX+YxjutT66nHanM1dHCDpq6amT/1vdmk0y9yCHaXOtSFMJI1dz9ql8brquDaNYWq7WnU79nO61NK3t0xUyuqs8VwF19Pm8mODeXcW2I/f721D6G1D+ItpQ/iDdUzcW27p1Hvvvls+yhv0QVzj29d9c31tCEmq7T0B1iLkO4wJ2p/kVcUBeDtGYtl6ebLeHQbrDZX1YrAWDtOMOVYg6+XJetoxx7pJW61QbI09sBP2xHDshQMxDNOwN2ZgX5yN4bgU78RV2E9NrzyHY2+D9A6StliDMRSjNesVyXpjDdYrkPWexFF4RF1PnmWxk8F6j7NcfTyIbfGQZqxIs6wXKetpx4pbKWPFrcIAXC3xr8FuuBb74TrtWLGyvR4G6ciV7S3CrnifZr2g087Tv0/Sv1/Sf0CzXpKs18txPRmDszFuxhDcolmv4LTz/bNd8rkDQ3Gnuh6/l5zHt0vi2y3x7dGsFyvrtTJY7wEplwcxCDdo1suV9fobrHdMlj+O4XhCs17JS86PlyVyvCzFWrhMm7+Xna/XUdbrJOt11u6/ctbLkfVmyHoztWNDlbNekqxnkvUmafe7rBdssF4DKc+GGIiNNGOr5sl6A2Q97Vicc6SezcUwnId34nzN+aRU1n/Q4HzSRM4ngdgGg7AzNpfttMAobInpGIzTsDXOxTa4AtviWmynPY+94jzeVIk3TeJNl3h/K/FOlXgzJN5pEu90idcs8d4r8Wap8RLOOI83VuKNk3jjJd7REu8YiXesxJsg8f5G4h0v8U6QeCdqz2fS1ryjwf71k/1UV+L117QJNst6HeSc7zgWWlsPxkTxtl399bZdvVntVq+nzeovdRyUn7PdakW2Wf0ltFctpE1qCaH6KsYEISQQZhE2EwoJFwlXCUGrab9KMBM2EAoJFwg+a/hvhIGENMJqwlHCecIVQpO13jav3p/3V9G/m/T9v0L7///U1kd9DzpBvsWPwwYYj9WU77vPad/lqd2DXb5rdNrvXP8+Wd4zqu8xHfuje9+red+r/WLeq3WPVP4+PHd7aFDPuXveb2W65+1Ay6jre69W6CPHH46TPrP+1vc9/OQ5qQE2wEBsiK0xAEOxMd6NTXEiBmImBuF8bI5LsAVuxmDcj62xENvgaWyLb2F7/Bw7YCXS0wnDsSuOwBCMx+54xtuX0Ps85n0e8z6P/cKfx/K8z0ven/fn/Xl/3l85P1/C5J/3+T8jfZLy5H/jz/1X2vqobURz5bm/KjZAHzztxzeW38lzv23cNBqbRw2OGnXjY88=
*/