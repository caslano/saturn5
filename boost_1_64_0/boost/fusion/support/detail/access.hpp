/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ACCESS_04182005_0737)
#define FUSION_ACCESS_04182005_0737

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct ref_result
    {
        typedef typename add_reference<T>::type type;
    };

    template <typename T>
    struct cref_result
    {
        typedef typename
            add_reference<
                typename add_const<T>::type
            >::type
        type;
    };

    template <typename T>
    struct call_param
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T&>
    {
        typedef T& type;
    };

    template <typename T>
    struct call_param<T const>
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T volatile>
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T const volatile>
    {
        typedef T const& type;
    };

}}}

#endif


/* access.hpp
BFxOb4Gd7Q5KOYW5OSdVvX53TrtTeguC+ltTrJCQbypccbvzs5iy06GpAKrar/goyaMHae6g6YnlNMYESdh4vISy8STlFF9/R4KPjyG51fpw1bIu+cdEKWwsZ+ySLY1Luw3YP3z41wQhxwjN/thvTYeS7R+xyvCNygG3ulhLlQW2cEGisavKStlnG7imeq83dSF7W2cvCo3r/4jPTrzqmjs1Sqz1Xpv5xA+nYRlFBXSfotITXNl5cTcpfbXEDMzbl+02a5y6FqxLKOaEHow+L1wytlkPPAVtcS9QOooLLhE7xg1rbZPXTKlbdIC292+Ypn0yD2sSL7hYLJeyk3fsgGWPiZSPvfM/W92YI4Y1oxhu4EctsqfWfBlZVE1xU2ztcJoiVX2RbUA8xaHX5gcMm5gWrAS6lJ0XgVSuHGEEykVc4rRyMlugwQXa1v1vnggIu6ZzhRh7hyrUUW1PmZN0r7jplBPFEF/98yFd4vJNdUUniE6kcQ72ugwGau9gryAy79BSCudINCHaFM9Mr1M6SZ+Z2NaNNLHqTumSi09EIrkPLGnuYra2HjQqSQ==
*/