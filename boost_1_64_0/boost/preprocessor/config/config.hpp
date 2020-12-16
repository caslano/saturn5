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
CZPQVrLHm85NgaYtYJ3ajPMp1vLvsBcoxbnOzGWObCbOtftEPrnclkc2sO5lDzGgpkgSDITxUHqEIzeOZK/N85kwD+5Vr208x5H+7DejB7A/oJ4Ps58ocZYt02ux54F5cC+sau7IGvZVe3i+HXbBq+eLXMUeIivAudJOR+6qjT3BLFjJGUgnzgl+JF5/9l9PrnMX3djAleylX7blLeJsg52wAx7vxV6J9fAenvc7w5EP2JtNWEJeg9m3vmdLgyjOweowVpxF3cG6+ks+XPEFe90ktNVbRSazl+15krsn5wxqK2cwl9pyaTHqfj3FEqcz7GL/ksOefGAddFgMyzMtscZRBs9LqXk9qU5kvs/jcS7cr+K7Nv0Wj66NLmFveVEVRzaVsuWW9bR3EzbBnm4UZ0rXcC53w2zadI8tN/VmTzXHlocuwTf0dORubOUyznvKDXIoK7ec/LK38uiW+QGshy2wGz6Ck2NFqkMMuHU6PTZSr7o81oIyUArKQznQ6yplOUepbcu95ThLqG7J1XczXytyBpUuctu37ME7cWbyNPvIFno/mPsgVtUhDjp4yrHZn2+s9cd56GkyNjrSfoYU6gsVjzj0VxFbLp9ZkG8HVX5K7O+XEeOpW5GqnGWxp1Txj8qrs0pzQaxW5l5bWjVyTqgt57B/Szrv2G0Z3oj9bbPC9ehO2ReBHnfOj7Y0e9s+Zn4tv+J87RPOrE/j/G+9I/1ij20/n3/MOSL19ObZP/b4bM+1u3EwAXTbu8tgf3fHRnz/VB5nQl4/7WrC2YV97LI+4/xgeTrnpbGF+/M+tMXHWd8Fnvkylsc7YQq49ZsGm+AAbHXbwB7/NDgZ6oDexmT+7wxuO3vw2AHQ8tvcNS7S7i5xkbamxUXa+2Q05+AphdvRK+742qDX39vvGXHklzcn9THQ5udA4qRo/b+BM5Wfor31Ob66UA9zHY7hf7ouYl6st/5UeQVtPz6byyvz6We47q6NtHFqXEG5s+K0vod7YfFxjsOx2j6ex4ngxpsSVzAWk3g+HWKPY1wePuLI5NXOMeuxNduWl4oX9gnvktd22Asf/U3t2qi1jXj0o2qb1u8pnjatd20ftkJeu8pXcuTB8+38s7SSFagH8R/nsUVb8YMf/OCHf3W4GOrC5VCT97V78Z7mmrTIa/MgrQd+82n2E6c6UsXCL8K5Tbn2NxRpy/vtJdx1QnHSRvF8JXlVFsk5jX3MOJGmvD/71FkiZ7KvbVc7Ei+tLO/DRXNN6cB+lX3fmpNFXmGNl30S65ailNMcH9pdZFQSfr4i19gyrGESSR/jrvHJtxX1Kk8+jfHDdd33pwVnHLlGzYblpSiHPNYRd7fwfBNxi+DzoWIR4jiktykL7neoi4NmRxgFZUpH4r+CvlO91tThNdqdDenFSCO0vSj5ncRz4u7m9SLuWhptHeknCnoJyhDa70T+/6Yk15jESL8Oa0E+xCOKDCLPgdAOkuACaA8doCN0gmTV752hC6RCV+gG3aEHpEFPuBAucusJveBi6A19oC9kQD/IhIpwClSCyuCOb1WIhmpwKsQAwyPVIRbioAacDjWhFtSGOlAX6kF9OAPOhAbQEM6CeGgEjaEJNIVm0BzOhhbQEobCJXCp6vPBMAReF2wGNsMWeFOwAeGaDB/C2/COsF6AHcLaQRhDYV0O78H7ErGJDyTyGaM9sBf2CWsH2C/YGhyEj+ET+FRYs8Pn8IVgf/AVfA2H3HGFw/CtRD7f9L1EPh/8IxyBn+Bn+AV+BbH4AxscKAJFoRgUhxJQEkpBaSgDZaEcnATloQJEwcnwmpBWSCukEdIIaSDMa4lwPrSCc+BcOA9aQxtoCwkQgCCE3LI=
*/