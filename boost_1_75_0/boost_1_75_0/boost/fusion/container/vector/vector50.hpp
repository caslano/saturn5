/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR50_11052014_2316
#define FUSION_VECTOR50_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector50.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector50.hpp
hC14ng2p7WFeW8fw2m6F2l75ntUGvABrS8La7GXICaHGDKqxP6/RwmoE281BpfYXjU6OKB0YT+loSgcyKtlSjDeKxtuWDZYNWWllBrP4HvuGfcoxRmXQfpEOG7y86xmdTDrTq4FMwqL9hWTyi1fopiiRyX1yc2QSJ965LQ4Zs45U/M1fjBjSn4hME8/oBVh7W2EnBqcqO8g5Lf0bTi07rUFq+aGgli3fENRyj7L+VUEtk18R1LI7+yuQDtQy8wSb2ms4tXzuZ6CWrBmilscCHZBahsjpbTKMd6i+TNm9tDUT11VHsAonMgWjjElwT9LHBOtM+WPAJNAf4apOy51Y6CrJP5gNyWrfwIoFoyVfZ/v6SO0I+sGlIcK14ge5Wj+r8jvyvkZCoVxaCSfAGA9hKnsVnEFGrtvZ34q6Qfu2GL6NpG/l8O1H/dsz8O16+rYavlXr316Fb5fQt5fg2+v0rS37/T524RO849zoXE3ThdtzB/C/Jfm4bJl5pLVpjdnT1Vtj9lmmsB9sNj/fAgzFMgF++eMHvmE1KSP90ZQ7iS7CzLExaTblK4gikyyl195ThDkw/KMjCr1zI2LsmSekyOOb4rEoE3qf2QX2hhp1p8Q6yjQii3sL3Q5OdVYmCF1YGXwG4o/tBNWHkf/4usOtTUrwA64Mpiq2lyym4HAG3FcHtmvA0QxY6nlW2q9m+4ebDdU8AdW8CNUENzgr
*/