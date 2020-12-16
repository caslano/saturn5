//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ASINH_INCLUDED
#define BOOST_MATH_COMPLEX_ASINH_INCLUDED

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#  include <boost/math/complex/details.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ASIN_INCLUDED
#  include <boost/math/complex/asin.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
inline std::complex<T> asinh(const std::complex<T>& x)
{
   //
   // We use asinh(z) = i asin(-i z);
   // Note that C99 defines this the other way around (which is
   // to say asin is specified in terms of asinh), this is consistent
   // with C99 though:
   //
   return ::boost::math::detail::mult_i(::boost::math::asin(::boost::math::detail::mult_minus_i(x)));
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ASINH_INCLUDED

/* asinh.hpp
/3u0vHRljLLLyDTPuhNTYOjKlFvLDm2ZBMuuszzx+ql2Q31gEvocydTP9pXMPUYx41V3xjXFmkbRnklId8Y1JXHdGdeUxHVnXFOS051xTUlcd0btGvqW6M788/RnjPK6WWO0ko6v+un4ylsm5aUTovjjq83KYo6v8Kf78ZW3LPnxlbcs8fGVtyy58ZW3LPHxFXZt+63Bqht0vjw/n7Kn5SE+1+rdjr2axM3jri0Y+RxPLt5sGXvdXWY/9hos46OgWSJ2armXTTkXmGOiPMZE99E+XxygY6JVRqC/mJYTOS7K5jpVxkX/3THRifKv5TwZHTu0lVrqfRJjorbSxPvittLlNyY6LNt+TOSzpqubMVFzaewxkS+JdPpKV8yYqEELcQedl26vY6IOa5qTGBN1lCY+JuooTW5M1FGa+JgIu3Z9i6lnuFieb0k7T4/qD3RuJeZpsVfEvdA87Fm5N0btucWeW/qNzLC5lt6LO47KSKIMe2McVZlrP44qsZZ3EuOokiTqdElpUuOorVbpYZ12DUIwG6pHE3Uc1VJuSWMS46iW8sTHUS3liY+jWsqTG0e1lCc+jmop/+ePo77jnu8/oHc7TvRu7x/v+6FmtzlT2gcP+XHME17Pv1/vdi9J1/pjxty64Ld9Zg3ctHz99PrRZ/639HF3U33cNUL6uOxLxNavfV/1Dz+Chv3qOPa/UPtdFvu+OPY/UfufWey3xLH/jdr/zmK/NY79H9T+Txb7bXHs80Dsp0LD/s1x7P+i/v9u8b8jjv109T9D/W831l113bpD+7OFav8K/PWo3u8keAPcDd4E94c3w5PhLfBU+Ag8Q/WIz4e3w+thO7wBPgRvUn3UO9T+3fAO+KLqE7+i91+H90I38boPDoH3wzUgz1XvFdH4r2Sj93qE5s+RMDNM3xaj7la30bedGwgXHgzzVI93KDxU3fuMdSC4ibr3IDWIVc/7RJgBT4H94WlwVXg6HALPV3/PgCPgWXAteDYsgudpvmNP463rI3BNm3j7NNwD4EDYBGXMoe4rjTk/mKDu+yKT1f3j6n6xxvsJOAg+CYfDp2ChXo/Xa61HzC+1HGzq0VZaj7bV9Oyg9WgGPADuCE+CO8F5cE94JtxF682u8FE4Cy7W50/D3WEnrIbvwdnwc7gH/Ebt/aDPf9bntC153g/uGapHOtch3jb1iPw19fxz4Lqh8mDuELsejdR6tJbWo1FwqOX9gjpz7EyeqPv+ks6gGavhbggHwElwTbgJHAmnaH3ZDE6ApXAjWAZL4eZwe7Wn8WVcGLv+rK7hraH1p0Drz/BQ/dGxDnGyqT97q/s6rT/1cDDcR+O7L1xLryfq9fspiZ3XNIkf+ekIOtOiI41OsegTGzrlDTxbCOfBSN3yhdwbAgdW9lvuOuZPE1Y8PfMF5em9omu+4OoM1+deT/I65+H65n+7rnnm+p5e1zdH1zxpPfO6u8N1zYuI12RkFuJH5iFXIvchS5DvkKyxnOuJTEVqkBZkPtKOvIh0IZnj0FMf5+imO8YxjnGMYxzjGMc4xjGOccyKMCtK//9P9q4EPK4pCr8sCBOVtmkSEYwKgmASqUQTOmmStiHSoYMgZNIk2hARmhL7oCiCoCiCQVEUQVEEY6/vs8Re+9iLIPZ+1PLPzXkvd97cd+e9SRrb3O87889779zlnLu9d89dDj96+Pv/Befz1wv2/y8FxYGcoFvwxOcc2j+/snraTH7//5vGhu7/fxPjLRbPB3CG7v//aAr2KE8N7h1uav//kPOpEG/Y/v/JNI/eQR52AV27fVCg0PTz+/8jHN3eNUDGn0XX2AGnlLO5kX3Ta8Lm9l/as/9qZjNam1/3zgXZE48=
*/