/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED

namespace boost { namespace fusion { namespace detail
{
    // const reference deduction for function templates that accept T const &
    template <typename T> struct cref               { typedef T const& type; };
    template <typename T> struct cref<T&>           { typedef T const& type; };
    template <typename T> struct cref<T const>      { typedef T const& type; };

    // mutable reference deduction for function templates that accept T &
    template <typename T> struct mref               { typedef T      & type; };
    template <typename T> struct mref<T&>           { typedef T      & type; };

    // generic reference deduction for function templates that are overloaded
    // to accept both T const & and T &
    template <typename T> struct gref               { typedef T const& type; };
    template <typename T> struct gref<T&>           { typedef T      & type; };
    template <typename T> struct gref<T const>      { typedef T const& type; };

    // appropriately qualified target function in const context
    template <typename T> struct qf_c          { typedef T const  type; };
    template <typename T> struct qf_c<T const> { typedef T const  type; };
    template <typename T> struct qf_c<T &>     { typedef T        type; };

    // appropriately qualified target function in non-const context
    template <typename T> struct qf            { typedef T        type; };
    template <typename T> struct qf<T const>   { typedef T const  type; };
    template <typename T> struct qf<T &>       { typedef T        type; };
}}}

#endif


/* access.hpp
z3b7zm1ARCC0AmC5VCtzsf160iCyCgbNPYyY0A94Gla3QEn9jVob7A7pB9x8nY6jEh3ewgaMyp8xd8Cigz11VMrjqFiQ9TAMAzdbkbU1mRGRmd8QR/tdk6kuI7mYG3RHUUQBC+X2DfNzisE7flNYz46sqpHvTCXNvD8BzwFNtVtAKrxtBrpCl7HYKdFpGtgMlyF2C0ovWSt/DTSNHO72XrJIBO1SolPwwUATYPHh1mgQZJHnDuiug0Dkh1V5hwtJ81WE59Ba9AOBwn8aHOFmPyVOAnkkyPEMjQp8VTxTvsThTZb/yl0N1XzXCCPyX0YGaf9Vdcu78LKrFni8O6iab+2tVfbtuoprmGzJTRFfg6pzhFhNOcP8pbP+Tp7ZiYeLcsyUfW8ufZBbOF0qQhWafQ3VsdqUvWinqlM2s/vr+HOqlxQTYo6t9alPGh7ncJBz8M6/jEc8FgGh+efQ8IpTVC1dwjbAPpvlJUqF5WXKwY8mpbKZrOxYVRqOk6ni52Mg936GFa6lmyUdWKtRZMWGuaOohOqKIq050CqnOA4/HMMqFk37QqDD3LPBA/eqvTfw802HpBMRO+9VHPxDX3wtRiLvzb0OR4/yPalDF0lqOtEJGI8FPe2cyrJ3djr74zH89bUeazj0q/tHsZwF
*/