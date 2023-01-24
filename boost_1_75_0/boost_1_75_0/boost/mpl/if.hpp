
#ifndef BOOST_MPL_IF_HPP_INCLUDED
#define BOOST_MPL_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct if_c<false,T1,T2>
{
    typedef T2 type;
};

// agurt, 05/sep/04: nondescriptive parameter names for the sake of DigitalMars
// (and possibly MWCW < 8.0); see https://lists.boost.org/Archives/boost/2004/09/71383.php
template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename BOOST_MPL_AUX_NA_PARAM(T3)
    >
struct if_
{
 private:
    // agurt, 02/jan/03: two-step 'type' definition for the sake of aCC 
    typedef if_c<
#if defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS)
          BOOST_MPL_AUX_VALUE_WKND(T1)::value
#else
          BOOST_MPL_AUX_STATIC_CAST(bool, BOOST_MPL_AUX_VALUE_WKND(T1)::value)
#endif
        , T2
        , T3
        > almost_type_;
 
 public:
    typedef typename almost_type_::type type;
    
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,if_,(T1,T2,T3))
};

#else

// no partial class template specialization

namespace aux {

template< bool C >
struct if_impl
{
    template< typename T1, typename T2 > struct result_
    {
        typedef T1 type;
    };
};

template<>
struct if_impl<false>
{
    template< typename T1, typename T2 > struct result_
    { 
        typedef T2 type;
    };
};

} // namespace aux

template<
      bool C_
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef typename aux::if_impl< C_ >
        ::template result_<T1,T2>::type type;
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      typename BOOST_MPL_AUX_NA_PARAM(C_)
    , typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct if_
{
    enum { msvc_wknd_ = BOOST_MPL_AUX_MSVC_VALUE_WKND(C_)::value };

    typedef typename aux::if_impl< BOOST_MPL_AUX_STATIC_CAST(bool, msvc_wknd_) >
        ::template result_<T1,T2>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,if_,(C_,T1,T2))
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_NA_SPEC(3, if_)

}}

#endif // BOOST_MPL_IF_HPP_INCLUDED

/* if.hpp
ridBEAbK6+WtJrFn5p7vKau61h7PXovD+H5Ng3zM4cRU/EDk+rCZw2PWTPzbKI4sj1/UXA7gbhCSEki4gFVp79BdbH8WrW7dV9r1nGFYsP558esmAUUx67jCpWuKt9zOdh4Huf+H04jg4fOUZZtvQaqtXMvpJMG2/tlEUAwyR7HEZz3AsPykoPXpuE8ZVAZ8j7r7XHOsvOLKDds4Z7RALEKuG8dx54D+vQl1jlzf3HPKtzbDblMyFuTXe/2nr1mCz40CUY/Kxvwkb/vE/uJQCXY7GjsLgMKZYcgqlKXXvNbnfvHqPCZKOmgFVbZbPqthuAzHZ54bYgWHL3mM61t/cQivKTNNL3pGtbuVUV+iyc2kzkf/pfblc6VZ2XZjTPTFETjaPoKAn4A0nHBH+mkzV3iL9nWrMRbqL+xYgS5pQSvZRxDxG+3offqREfCLFPvJJzeByOFw0KgeZMmvkn22AAFcpZfjpRiDrDmzKuUv0JcyBk1A4ChEExclbBwJfy6OKCYStynLN/XFe4m1kLFUxO9lbqcHemOsko7+JE2YxOYRMaaWN9HCVQgCMGXvNq6pA/JH0RYv3LPWxpq9DJ5iu5lT85hPxxX2EwJAKwlnuKvtPQHNYoT1mnEs1rWI+zoMIy2VfNf0AFCn+JjJRmW75n7P3wR99ymifuWyg5Y7NBT2usTQ/f4AunV52U+mZnaqGiq4aGPHwcQyf1Pi
*/