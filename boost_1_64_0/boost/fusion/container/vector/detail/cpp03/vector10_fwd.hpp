#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR10_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR10_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost { namespace fusion
{
    template <typename Dummy = void>
    struct vector0;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector10_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector10_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
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
    // expand vector1 to vector10
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector10_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (1, 10)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector10_fwd.hpp
BZPrKmwk71fb5snz/+swFBtiY+19cn3EMvI+X+OQNcKWqI7/JO/7St6nH//pghxPf8Ne+A/sj5Vow0+l3i/iXfg5luMXeAC/xEP4L/wV/hvfxa/xQ/wGz6PFVR7Ai1gb1eNjk8TBmBwfo6V8SdgKx2AkjpVyJuMQHC/lnIA5OAmX4WRcham4BafidpyGn6GddELyf0vyvxEzJf8SiTdYiLG4BAfhHZiBS3E2LscVuAJX4534LK7E53AVHsUytY2mXAdgN5P9OUzOG8OxE45Qj2f5DY82k+O5n3ye+sv7BmAPHIiTMAGn4WBZ3wlSuayvj5xvmrnOM0wSd9UCH8P2uAW74TbsgztxID6Bibgb83APOvFJXIg/xg34ND6Nz+LzuA8P43NYgQfwN3gQT+OL+Dkexi/xJfwGX8H6Em8VhRXYA19T4xdIm7X4inKSPn6hnz7OQZZrXc1ydlmuSzXL7fNzuUpZrpPZchLvVNaZZ/ak46TLpOguPM8mrSdVkC6R9LEXp0lazIU+1sI8xuJilBZncZ4U2lWLs7DydzzOIMXwdwkmYh6plLSetM8QZ0Hqqo+zMIup0OIpIjGFVKKLqSjj7wSJp9jD31Z8EY+REvn7DFbFVIR118dUaPEUKbw+gqfb1rFk8reTpI+tOEY6RbpMkrgKLaYiWoupiOLv9RiPM0h5pFKSr1iKkzgDjx8IsVyIVmMp1DiK08yvP5R8+b8GPbRYiguUM7KH9CdGWkJaK3EVR3po/Yud5O9zJH2MRd2e7jiLMGxH0sdXpPK3k3RuqDGuYmVP89iKrcp7SUdI+jiLkz21OAtLL7aZ7dDHW4Qxrx3JM+ZiCWkt6eleWtzFSom3yCSdYN4Z0kVS/Zgrx13E83cSKU8Xf1EeI/EXJIm5IN7CO9biEl7CsES2qTfHFCmalKCY6I6tSONvOyk1UYutKO2txVaU93bHVoQeZBwg0gxSGelp0nHSeVL9Q4w/REoiZZLWkvaRTpEsL9BelzSMlEYqJW1+IRh3EZyCU3AKTjU1fQ/P/7n9/N2f/zen779Byn3CaH738+hJ6TfdptzidDosP+L/EpT7mD11/1eUle4oLFAueV2xA/G3WtTnjIkSO5As95dHk9aE8dp9/2T4hAnue+3uNVEMR/XPF+T+Iu2afN8/M7+/6Pt+pPn9vJq7zxRoO7FA7/+Z3zf1dR/O9/3CJguU+ZGVt0Q07rQrckRJwVfl9zS8y/d9Prnuk/2JSvLok2isXPeNx844AeNwIo7AyTgap2A05U16LcSS81qI39cOp0jGuGyvmGyuE7RrhK1YQdKuBXxdBxhjqi0J5E1KJF3qZv77/ghJ/3v+FEn7Da/9fl9PYmOvEPvs/Ru9/lD1d7nENpvFNZv+1pbf2f7FLnvHLZvHLMvvZvnN7F9scqC/ieU3sO63r/a79wjzy14L/k4NTsEpOAWn4BScglNwCk4/zOl7uP6f1Sfmu1//K9fwsbo+/fdVtfvHCByC/ZT7A6u12FQ1DlJCEf2J/ZY4Oa9YyOZqvLdnfKPEyXnEqzYyxO/bJSZJHzdafSxogsVXLKj0HSjx79NrsxxOxnjKXb5WHW/Oowaq334l3vVn96nxrmp9WF1lnJ9V5CBu06s+qKTcTDWP5lIfN7vqkMH/ihbanAvtWRap3xKT8c5+xPxSdX1ZJU4OMHJyyEpd/1+m/r/azZb8t2dfaJlZGUotmva55nPfUNfyXo+YtcqqepZ2BpNxoFLP90uMppTCxlsLM7P8quM3y036xguVPr9M+8bzPCaYN6uYR/ie2858tt2rjzzWy2xd/02B9xke6Lhw5nFngff3ZH6fx9f9q5qLXzOPj/N1X64=
*/