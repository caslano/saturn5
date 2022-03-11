# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002-2011.                             *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_CONFIG_CONFIG_HPP
# define BOOST_PREPROCESSOR_CONFIG_CONFIG_HPP
#
# /* BOOST_PP_CONFIG_FLAGS */
#
# define BOOST_PP_CONFIG_STRICT() 0x0001
# define BOOST_PP_CONFIG_IDEAL() 0x0002
#
# define BOOST_PP_CONFIG_MSVC() 0x0004
# define BOOST_PP_CONFIG_MWCC() 0x0008
# define BOOST_PP_CONFIG_BCC() 0x0010
# define BOOST_PP_CONFIG_EDG() 0x0020
# define BOOST_PP_CONFIG_DMC() 0x0040
#
# ifndef BOOST_PP_CONFIG_FLAGS
#    if defined(__GCCXML__) || defined(__WAVE__) || defined(__MWERKS__) && __MWERKS__ >= 0x3200
#        define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_STRICT())
#    elif defined(__EDG__) || defined(__EDG_VERSION__)
#        if defined(_MSC_VER) && !defined(__clang__) && (defined(__INTELLISENSE__) || __EDG_VERSION__ >= 308)
#           if !defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL
#               define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_MSVC())
#           else
#               define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_STRICT())
#           endif
#        else
#            define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_EDG() | BOOST_PP_CONFIG_STRICT())
#        endif
#    elif defined(_MSC_VER) && defined(__clang__)
#        define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_STRICT())
#    elif defined(__MWERKS__)
#        define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_MWCC())
#    elif defined(__DMC__)
#        define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_DMC())
#    elif defined(__BORLANDC__) && __BORLANDC__ >= 0x581
#        define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_STRICT())
#    elif defined(__BORLANDC__) || defined(__IBMC__) || defined(__IBMCPP__) || defined(__SUNPRO_CC)
#        define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_BCC())
#    elif defined(_MSC_VER)
#        if !defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL
#           define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_MSVC())
#        else
#           define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_STRICT())
#        endif
#    else
#        define BOOST_PP_CONFIG_FLAGS() (BOOST_PP_CONFIG_STRICT())
#    endif
# endif
#
# /* BOOST_PP_CONFIG_EXTENDED_LINE_INFO */
#
# ifndef BOOST_PP_CONFIG_EXTENDED_LINE_INFO
#    define BOOST_PP_CONFIG_EXTENDED_LINE_INFO 0
# endif
#
# /* BOOST_PP_CONFIG_ERRORS */
#
# ifndef BOOST_PP_CONFIG_ERRORS
#    ifdef NDEBUG
#        define BOOST_PP_CONFIG_ERRORS 0
#    else
#        define BOOST_PP_CONFIG_ERRORS 1
#    endif
# endif
#
# /* BOOST_PP_VARIADICS */
#
# define BOOST_PP_VARIADICS_MSVC 0
# if !defined BOOST_PP_VARIADICS
#    /* variadic support explicitly disabled for all untested compilers */

#    if defined __GCCXML__ || (defined __NVCC__ && defined __CUDACC__) || defined __PATHSCALE__ || defined __DMC__ || (defined __CODEGEARC__ && !defined(__clang__)) || (defined __BORLANDC__ && !defined(__clang__)) || defined __MWERKS__ || ( defined __SUNPRO_CC && __SUNPRO_CC < 0x5120 ) || (defined __HP_aCC && !defined __EDG__) || defined __MRC__ || defined __SC__ || (defined(__PGI) && !defined(__EDG__))
#        define BOOST_PP_VARIADICS 0
#    elif defined(_MSC_VER) && defined(__clang__)
#        define BOOST_PP_VARIADICS 1
#    /* VC++ (C/C++) and Intel C++ Compiler >= 17.0 with MSVC */
#    elif defined _MSC_VER && _MSC_VER >= 1400 && (!defined __EDG__ || defined(__INTELLISENSE__) || defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700)
#        define BOOST_PP_VARIADICS 1
#        if !defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL
#           undef BOOST_PP_VARIADICS_MSVC
#           define BOOST_PP_VARIADICS_MSVC 1
#        endif
#    /* Wave (C/C++), GCC (C++) */
#    elif defined __WAVE__ && __WAVE_HAS_VARIADICS__ || defined __GNUC__ && defined __GXX_EXPERIMENTAL_CXX0X__ && __GXX_EXPERIMENTAL_CXX0X__
#        define BOOST_PP_VARIADICS 1
#    /* EDG-based (C/C++), GCC (C), and unknown (C/C++) */
#    elif !defined __cplusplus && __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L
#        define BOOST_PP_VARIADICS 1
#    else
#        define BOOST_PP_VARIADICS 0
#    endif
# elif !BOOST_PP_VARIADICS + 1 < 2
#    undef BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADICS 1
#    if defined _MSC_VER && _MSC_VER >= 1400 && !defined(__clang__) && (defined(__INTELLISENSE__) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1700) || !(defined __EDG__ || defined __GCCXML__ || (defined __NVCC__ && defined __CUDACC__) || defined __PATHSCALE__ || defined __DMC__ || defined __CODEGEARC__ || defined __BORLANDC__ || defined __MWERKS__ || defined __SUNPRO_CC || defined __HP_aCC || defined __MRC__ || defined __SC__ || defined __IBMCPP__ || defined __PGI)) && (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
#        undef BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_VARIADICS_MSVC 1
#    endif
# else
#    undef BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADICS 0
# endif
#
# endif

/* config.hpp
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
*/