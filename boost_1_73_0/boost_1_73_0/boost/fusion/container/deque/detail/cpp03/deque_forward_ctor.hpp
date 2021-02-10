/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_PP_IS_ITERATING)
#if !defined(BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_FORWARD_CTOR_04122006_2212)
#define BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_FORWARD_CTOR_04122006_2212

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#define FUSION_DEQUE_FORWARD_CTOR_FORWARD(z, n, _)    BOOST_FUSION_FWD_ELEM(T_##n, t##n)

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/deque/detail/cpp03/deque_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (2, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_DEQUE_FORWARD_CTOR_FORWARD
#endif
#else

#define N BOOST_PP_ITERATION()

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::call_param<T, >::type t))
    : base(detail::deque_keyed_values<BOOST_PP_ENUM_PARAMS(N, T)>::construct(BOOST_PP_ENUM_PARAMS(N, t)))
{}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& t))
    : base(detail::deque_keyed_values<BOOST_PP_ENUM_PARAMS(N, T)>::construct(BOOST_PP_ENUM_PARAMS(N, t)))
{}

template <BOOST_PP_ENUM_PARAMS(N, typename T_)>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(BOOST_PP_ENUM_BINARY_PARAMS(N, T_, && t))
    : base(detail::deque_keyed_values<BOOST_PP_ENUM_PARAMS(N, T)>::
      forward_(BOOST_PP_ENUM(N, FUSION_DEQUE_FORWARD_CTOR_FORWARD, _)))
{}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef N
#endif

/* deque_forward_ctor.hpp
YlwY5YhDhrOG8B5D+SjrXyFsUeRLoMVK/utNox1IVMKq/rUTXvvX3I2afa158D7B1gdubpbL2x+eDYJ2n/HEetRFHEe0XoBocPxRbTK+1UmLJZVyca8xRy8hEiWqCIgzjfDDWlAqykILFZXC40J5MccegeCjsISKZVqlG3Q4pUJHzyw67XI2lxtEjgXMTIgewEvHkGVoxbBlzrMtaZhh1CNjY2GSE2k3m0hECcrVZSWjqglK4VYptpL3VEaRkBtuPanRFzjerpGWvtW4oimmCdGleD2HMSJbKG6AZmbNbBkpd5qwwSHoKOCzqxXG1dxd7vP2Mjdh/ybY0Rvtr1ZGJAYVrvkAyrkmtwDbk6FmcxovvcVqCu/IXEWxzhuBdHge9DIdVqJtImhcPpVpcz0j8Twc9DKogozruZkYBZ8sif4NQAXkk/3g4tJM7QSWrDqYItuDV6gS6So1EHCr+1MZn2BL4x1+3BJHIQJeHI/oPATQ5kvVwf8W47DexikPOQ6rMwdeZQoj1IJAzzkZAJ1JhOds/Pa9YOkRFr9aQkwmF3tKNAr+XI6bPzBmSh3aAfMHVpQAsB3E8MfJMzwSp/vSrowyYbVI8WPK7Td4TZahPBKPNZ7CuJIBO0gK8EIIFCZmXxMD7k/pNnOIdCss
*/