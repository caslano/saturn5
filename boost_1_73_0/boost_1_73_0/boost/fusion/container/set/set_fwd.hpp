/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_SET_FORWARD_11062014_1720
#define FUSION_SET_FORWARD_11062014_1720

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_SET)
#   undef BOOST_FUSION_HAS_VARIADIC_SET
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
#   define BOOST_FUSION_HAS_VARIADIC_SET
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/set_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct set_tag;
    struct set_iterator_tag;

    template <typename ...T>
    struct set;
}}

#endif
#endif


/* set_fwd.hpp
GmASH7p1dWTZn5uk8CIFHvxfBHFh51QeuTZE15pbm8sABsYa3SYaa0iOIM2SykOgbGQLq2DB0VOiBSdNX4AXm2DRxRtA6jNwtYS+Atoqltn8GVnuwbyxHPfqDpktkI09tC1QGbW0t6ZavwqcV+esKcIdumeXYqxhvHrNMv4AScT73HH34njv+5A+UJE+9CF9pCJ9ZC2xTlOAexFDn+jK+IGqfQk4T8KITMF57saiFzSNsziXSj+ybblWoUpU+Kf+KTP9Qp8zaRisgx6/DJD22JgYNK8MoFmwFvFywZ97GHWNiW6NhtpdweyTKO3vPWQi/pnMnkOVFYEnilOlZC3cjY2rASZE4HIsOx+oKqH6AxTJrLEPDeWo4k6Q/y1eQ3Gl5ElQpFSY8rew7jja1CilWge4NmdEEHzyAMiNCNYLHhKBbnRjMtTGh8BQBWhAVGUJ/Dh63AlZNqVsDCzzljJkwSLiXqkr3QptDE1tqxA0PheRt0xFz5QGXG9k66TJ/AkgzxCSEGKVuLSc4CvmMF6fG1Tpy54LPBwLqeTb54nKxMvASNGIsjjpFggSMV1r2sd3FxUIoaN+KhAmmzS5RxnmpbI35jRMFxNRhxR2BrHfGXYa1uCIsDNHGxkQShpWH6pXPkfksijMdEoUcWmZ
*/