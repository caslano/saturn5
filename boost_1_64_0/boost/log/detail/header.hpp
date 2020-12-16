/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/config/abi_prefix.hpp>

#if !defined(BOOST_LOG_ENABLE_WARNINGS)

#if defined(_MSC_VER)

#pragma warning(push, 3)
// 'm_A' : class 'A' needs to have dll-interface to be used by clients of class 'B'
#pragma warning(disable: 4251)
// non dll-interface class 'A' used as base for dll-interface class 'B'
#pragma warning(disable: 4275)
// switch statement contains 'default' but no 'case' labels
#pragma warning(disable: 4065)
// 'this' : used in base member initializer list
#pragma warning(disable: 4355)
// 'int' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning(disable: 4800)
// unreferenced formal parameter
#pragma warning(disable: 4100)
// conditional expression is constant
#pragma warning(disable: 4127)
// default constructor could not be generated
#pragma warning(disable: 4510)
// copy constructor could not be generated
#pragma warning(disable: 4511)
// assignment operator could not be generated
#pragma warning(disable: 4512)
// struct 'A' can never be instantiated - user defined constructor required
#pragma warning(disable: 4610)
// function marked as __forceinline not inlined
#pragma warning(disable: 4714)
// decorated name length exceeded, name was truncated
#pragma warning(disable: 4503)
// declaration of 'A' hides previous local declaration
#pragma warning(disable: 4456)
// declaration of 'A' hides global declaration
#pragma warning(disable: 4459)
// 'X': This function or variable may be unsafe. Consider using Y instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#pragma warning(disable: 4996)

#elif defined(__GNUC__) && !(defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)) \
    && (__GNUC__ * 100 + __GNUC_MINOR__) >= 406

#pragma GCC diagnostic push
// 'var' defined but not used
#pragma GCC diagnostic ignored "-Wunused-variable"
// unused parameter 'arg'
#pragma GCC diagnostic ignored "-Wunused-parameter"
// missing initializer for member var
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 407
// typedef 'foo' locally defined but not used
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

#endif

#endif // !defined(BOOST_LOG_ENABLE_WARNINGS)

/* header.hpp
e+DP4aOqtw8egY/p9kHYAn8LfwHfgW9pf57Q/vyl9tOv4Ux4DBZoeiH8LayHx+Hn4e/hPk3fD/8ID8q2vm/ltX7D8rtd2z/Af32TsFH9J14PY2EdHA4/CcfCm+BEeDP8CNyq18Vb4DL4KMyDt+l1cRssh9vhtfB2uEnz1cEdcCv8LLwH7oS74N3wEXgP3Kf5D8B74fdhA3wDfgm+BXfBP8AHYCpteQhmwD1wFNwLL4MPw1nwUTgX3gBXws1wjcSrvy3rNxicafC3NVrHyYVQnsvCRDgZJsEJcBzMhhPgZfByTT8Ja63fMLBAy49BSrX8EvVPuhZ2h6VwEFwHh8Br9X5VDkfCCjgaVsLJsBrO13wL4Mdgvm6LnaFX5//62+QwHIEs13EwXPd/HuwKR+l4uAD2hxO1Hiu1HpdoPS6Fo+A4eCG8CI6DY+Cl8DI4G06GC1R/IZyq42caLITT4Up4OayAM2ElvAJWwyvhdXAOvAHOhdvgVXr/nQc/C+fDL8EF8H64CH4TLobf0f03wavhD+AyeAguhz/T9FfhR+EvYT48AQthRzqoGHaBK2FXWATjND5J4+s7hmdn+fR9nT0tiNtPmstHmvpGQ/fJ0O8tuv2hhfSFpv7PwrPNVF9ntk+zrcSthgY/Zi67zUa13bT8lZ2Abh9lZjvOWrctp+2PrEn9kQXadqr/MfU9Zvsds209054KtPcM9C1msv10+hAz+w/bC08tCGUTGp6fMN6ndPoHs+1F9/v+RyxfYDlPdWiXP7DQvsACfIB9gPcv8fMVto+vI9Dy65WJWH68tiEm/11LkWf4/ygSYIvKiUqd4TDo8Mvl8skVcyu+tZDZyGpkC7ILeRppQTy3RexXIyESIiESIiESIiESIiESIiESIuHshHNi/2+b/5+5/X8eumP1/f879Rmg2LYiVcjrWTxzHajv/8uO84os2+35o8mHXcA6D9tqE/iE5B1o/h4hadYa/WuUG2i//6ikF3ou4a/azIn9z5f1W7p17bDp9tUtUevGWrjdxtkd9DmntnEY8gZ1mTzI2Ub9DqTW026j1nO65B1kaqOW43XYybbPFp39ueo9Seut72bYtimdkRby1rnrjZPB0XkFFRV5RQXVjIGg42Sqs5bhDfsbfwF9a/uPqO9o101CNPJmFvGGOpYVrCsOt371Z1g/qw+zooL78Be+8R1Uv7zCsrx15UV5xbUVYdax4SzV8bChjm9Rx8bgOq7gPK6pLvbZZYVXx8YzrKN1nGs7BdfxKHVsCq7jSgzhqlaH2YdNZ6l+KdHB9fsl9Ws21K+0YFUVyYHnutmPSTvrF+pcfiLa3H8twfXTl63kIIfVhy3trGNgH07ROhZ1Dq7jr6jjiTbq6HcPE96xPnGG9VS/q1TQ3JeezMB6ik1mWHXzZJ5Z3ax7TYI+bi7We00R8mvqFuuuW1nxtR6HXbxcGU31Qi/w/RMZviYbP/IG3mupn+NeO0DSF3hGOO61D3zAe63YnWu93e8zSP1cY5/JiQT/BvVEfuO7R7j7pMp5Hwv3/KzXNsfb79DYJRj7qL6dx9lxPus3rvV9DHs/7uvQyO7+Qhbo8Z+P/I4yGoPaOsa6H4accxwTnT7m67q2wz2GQnw72dFHFXJAq9dVSPZW+8+nJM9l4kvJeq/uyzom7m6H/yRnf8m4cI8V17jIiAkeF7/PIn6wu69c9+Ywx4W/DMY5eZ+XvM4ijP2EzgcfG6na1uclzrkvd5sTegS3+Y/oTA5os/teH16bJzva/IzkdRVhfk/iLLT5GYlz7st9TrxnaPOf0MkParPOHcI8xujb4/p7ktdWN9tAn0FbrXP/exKn+wlo55Gewe18m/x1Ae0=
*/