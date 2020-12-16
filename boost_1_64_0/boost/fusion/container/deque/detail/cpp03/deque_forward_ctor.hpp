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
ObSHypmmaWNjtraDTEvVzu/+jp8slzgp00f+HoSOc9Rr26A1kTb0i6U90ELCj935dnrSoA19BY0jqGn3L3NpS7s0h/ZmpyVts2XcGhMhsy7lfUrSpjQSdkhToXGaIpUN1qQk861lUckad5FBeZ8xaDschIfry98SLbMsDmWYJG3rJxMaSDrDlLZdz0g6bW2q+scMHqGpFa7b/RuUodoOdojaV0I/t722DGPkluxuqbNRGE7aCtS00R7WoQwTXKQpySFNATJffB9rW0vN9P2StuBr7Xt1c+n76NOv5ruaZj84tKeUxtf2c+6/JnkdKW3gYghn+T+xtvcCyjztdNboTrMNbXtO523ZgjDYmk/WlL/Jt3zp93Fz27EZvz9z9r6t4uZw975v+/9435Zufd92vGSkf7tlK858Pjz77Fev+l+9vvdtuT5y3ZPrYb7DnNH+8r6tvqb9STsMwG7YGPtiE817t1RshlsxEN/FIPwaW+BVDEYl0lZom7NWrlVyDct3mLN2lKRjtMQ/FvtgAkbjOM3clgtxojrnp1xncLZsVzs3WlvZXgeMxI44ATujCbuo7W3kOoCTDdrbDJX0xWBbHCbrj5D18wkFsv7dUs7KSWiDrB8i6/eS9cOwJ/bGBOyDU7Gv5DMc1+CduAH74W68C9/GCPwG++PtxDcAg3Eg9sUojMDBGIXSbg/lPCvn39gbmHP1gvd9qPd96C/8faj3Xeiv/F1oHvuCUELwWU/9IUSv974fvUnP/6lZWTf+/K+MR99T6RdGI+EqPCopDxCJSvcVOhA247+16aI8zGr+W1aqKVuee5R3B99wQVb7Usq7g1jC7YShhFXcJAXZ7qGiRo1KzJhuSkm0bYlkZLvu/yPPHswD6/wZw/he1vk9sfE9n+fPKp62ATC+V/b8Xt/4WcLZvX7FPSNtsd5bD5171e/hKQ+PjBn8Rd4Pf9y23PmzkO2eSfa/1Itch3umZdIHZCW2x1UYhqtxEK7DoZiHeVXYp/uZ72u/r1tzGZZ/P+R4L6S/D6rez/D+x/jeR3evUzH3OXKPo7m/0d7b2N/XREdo72WM72NOE+zuXXT3LY73LMb3K9p7laIZru9PNPcm5d6XnOffpYSye5GOhBTNvUd0pPZ+w/P7DKN7DOP7C/09hdxPaO8luI8wuIfw4N6hvHuFGPUe4ee/PzhK0NwPGNwHaO8BUPn/+73Xeu/P+/P+vD/vz/vz/ry/m/j8nzw9c7LyAuCGnv+VZ/iLPICr4+HJM7xJvvNOILRUxs7YI99SrXOVWQeqsWSbGMwj2cJnUNfP8WXfRD+yzkumJF2+6avfH2VTDmOK/FXSs02+dz5ECCY9pXbpsb5XsI5k4047hFo+VesM3cv6bCo1M8XWLkFNx2TKxXEuM9uWa0l6f2f9ZjvLLp2l8h2/Mxv1w3bYinQW7TVOZ7akM81FOnc8Yp9Os0E6o+3SmS1jpmjmLpR0/9v2rdmSlpplW1Azblj7LrZv7RnyX5Q5/z4j4kuVbc/qibZ0qGX1ma0M0qWthd33+IPSVmC31KEdhNaURcQ+fVlMTZ3t1v7avc/1/kpQ/2Y2ZWc77kNi0szVV2DrY8If7etbrIwx9zaRNcHz2Ja0196vTbttIMjk5JwsU/Jsl+0JlPSfOyDpz8qS9gX6YyFNfyyo+zww1LqsZZb8LUKd9y8jPdsiedW0g0HHNgfWOKLVdjVq8vm7tv3CNOs5w0fi6aj+nTRlO7RRYNkMouf/WutLQRXKjPJ7i3+/bisvtbxrWtPKHItSX2rRIqbWAdsyz7bwsf57qMO/l6j/dthHMs7eYZkT6jFCe8on6VHHfSSHmlvjT1at882j6j6y/vs=
*/