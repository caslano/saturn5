#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/expand_pack.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/expand_pack.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file expand_pack.hpp
    /// Contains helpers for pseudo-pack expansion.
    //
    //  Copyright 2012 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/expand_pack.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else
    #define N BOOST_PP_ITERATION()
    #define M0(Z, X, DATA) typename expand_pattern_helper<Tfx, BOOST_PP_CAT(A, X)>::type
    #define M1(Z, X, DATA) expand_pattern_helper<Tfx, BOOST_PP_CAT(A, X)>::applied::value ||

        template<typename Tfx, typename Ret BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct expand_pattern_helper<Tfx, Ret(BOOST_PP_ENUM_PARAMS(N, A))>
        {
            typedef Ret (*type)(BOOST_PP_ENUM(N, M0, ~));
            typedef mpl::bool_<BOOST_PP_REPEAT(N, M1, ~) false> applied;
        };

    #undef M1
    #undef M0
    #undef N
#endif

/* expand_pack.hpp
h7uSqWg4mYqHkmEUFU3GY324IRbq7AujTKpbLdq1oY2pzlC0e0OkO+noq74mfXeiqz+VDK1y6jyjJq1RTqqnL7QqoRBvof71VP9Sg6qVk/IYXUxIpvVySZBeIrFAtRid1KJLJKGPUF8sGk6tj/UNrA1T+9bKw6v6pFPXOqprpUH5c06mqoFUzljXEej/6BpOqlwxPtAmjR/UPnQ75Fho3AB8aJ2rr67Y2sja0KqwU0Iqgmr3bSIdCdzSjs5IMh5eNxCJh8nm68fmT/VFOuOhuMNjpsQnUJvoqmhobTgRWRUFG8dGGyRdNIQeH06FUftN/bEIepBT3m41VuZkHN2kO9w5sKo7lAwply5YfniQnnAcFfDqGE+tD8cTkVgUfWG1TnWgrGCcyTPND4/Akbh1Bbw73BdOhrtTuoqpvnB0FXoV6ujh1ye1Ea4K9XMK8lNU6eSm/rDpl12dbh9+VueFcteGk72x7lRCm0gC7svpv7raichpYdd/O5VGDkjXm3LyxNeHXF8n8OFei5spcJ3g29XZF+taQ7xZHRx9kq44fPkyD17P4T3x2NrUQHRtKIoiuq3OgvGpeDgZikRTof7+7thafHN10cDzdBkdxBJJKD4O5ZFdLmD1CIeSq1PJ3oHompRREvDoA0a/faFEwrSD5m3h/bAn5HYwe+PoywdTX96JPhTPFnXoV+4qlHqHStHqaBYxcbe5kVR2+nEtCqcPB8cwg7mC23+dr14Mc6YbM6Afd7r9GLHQz+ppDNz9bKw/mYJhK6ceyiRjPdSuU0y6N9zX77YX0hi+ejAIunWvM7DYQFIDvTmvhq0Jb2KwaQYGP0Dp6TqNhuC8ZhCMclJbaxi6Pf5x6WZpGOx3U8KRa7ZJ96NZbHsf4NRlY7In0ufOtee4sHBU98KES3uggdu8B7l1onxzXRmikMz1PSSrm6fRym7kbqJ0AgaGgMHQNDt8MB4RlPK2GDiq3BVO9Q90goVD32rgoe7uZHwgQX2jzYXFw9rlm7LaXb4YTkKkk3lO+eF4Ev+SzAdrmLFPCzvEoTN8DnX0g27TZ9LzHT10JfpTA/GIw/cFgEn5D3P4QrGEIN4v1HD0s+6BvgGM5dTHAKNauvkPN7CNxy0+MRmDhZiyFxpYEjydcl/k2GIo0eukj3DaLJEYQKSnwcT/xY58A2ZAJNiRjNYt8yWOziPRVeE4YqWoS3uUY1sYRRNGjpeSvPH+WMK1o6MNDAN+PAlCxzcc4+gu2g2IS3eso9vecNcaIBy5X2ZhvXBAJu8iRgfle3p9uYVH+onnYkfXMVinybvEpI2BAOSU0eHk64szu1nqwpjdLDMwx2h0+jiy2a54GJXwt/FyNz9axIUd79kHolmCncD077RXKtZHdT+RtYNFOflWaBxGjm50M5fXKxz78XifRDpeFYl6vvdk0oe2dBPnwO+eQn73bPg8YPWAm9lSyGVoocwH0nFgNNCvlivpzFa401SkPzQ0hAlNOVaK4w6bs8AwLhYMlwfy0/adwgzY89YMQD4ba2W7G+xa2blsvnaemEu+Hml8fHPFN9D873yiXRQoR3Frpny8KwMlbPkXsPIvZOW/SZT/5gZ8RPkXUfkXE22wHqq5lLPM5MpgAUyOS5gcb2VyXCrkeFsDPkKOt5Mc73DXO2htwsGPZPPDlS18XayercstqFcYc/QSh5NuAn6O2jySHi7DRqeZuchlbN2iQekn8kWN/CC5fiNtQl8CzutlP2sYAkprHUVl9fBuppP3CJ28twEfoZP3kU6uINoVQfI4dXF+pJjXhUA8tvjAxHwm1Inmc1VNW9Hz+GgsieVxl42FWL18sCYPU7BuYJeFBTA5Pkw8VpKtXG0=
*/