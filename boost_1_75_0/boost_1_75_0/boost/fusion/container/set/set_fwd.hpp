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
w4gUnZ9ApHj3tyTLfPTD+12K9Qn5QjWsCMG6z2504SJVMisKJazAcbWWwEqiCV1JN936GN6UpzGizDWURoB+YhhdZEjvQj3gAYrGWUcpdZXokFQh1cpOEnW/vsYHmJeThvB9OfsGbRky+0Y665eZ68pni0mZBETJx5pgB14oLiA7VQI8+QuA7ilgOdQZUuPI0Sl5nMbUzbYxdWqIyWFDBKme3lT6zsB8fjQFoxajmZIe7Huu/haNK24hnUMI+sRh8UOImKRBQfww/3yK2Xsa0/gpOtJNoCd5b6CtS5oW7jMOY4vYJsdoLj45TnlPreGVBustUPsE22TNq6KmNRVjIRTi6/PZaAR8rEu1DcJb/edfYifwvSqgseUX8VMqhyt5QqRmcq1iogW2DrqAYqOSCsEK4acdWKOflih78dOEhHufp3KouDa/41Pscy4/ex4Rdsvz4WcVbR3Or0JdJDEkjsjtiJ6CHnr3flZNwhn14X10RhXDDE4mdGyZhuj42qOIjoN+SeLl8k+iM0psbHfdLzc585KxpI7MhnMEIz28UK1Hv0B1ZHa2VEceLe1jjsEjKDyrHiJGV/0ICpChOuglxPkqum7gpNn5CPEQarQE44NCaipxApVfjCGK+RQopCPotkf5CBJ9dKkGsseVE9yIbXA7/9hSDv4bF3Fn2b+VWKn1EW8tDD74pQpmsaKKv1/0924Vb/LFvMlPkKhI
*/