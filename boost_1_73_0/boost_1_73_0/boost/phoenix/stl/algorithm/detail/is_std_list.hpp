// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_list.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_LIST_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_LIST_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <list>

namespace boost
{
    template<class T>
    struct is_std_list
        : boost::mpl::false_
    {};

    template<
        class Ty
      , class Alloc
    >
    struct is_std_list< ::std::list<Ty,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_list.hpp
aOetr8Kx/nD0l7Ceh/eQpr9h0bPeUfuIRk/yf0W54J9faD8YTWdSfVocEX7vRXhPHnjzRNo74Cm0DCErriT2950/qLPBo33YF6T97iGclrW5RHZJah6+Z5X1b2OwpW08BX91IpPsXitbUGxwc4CT7E8P5CSKfFdxg4BrZ9J9vw6jpTP9MdbnZNmdAo+fUyfn3jtEGZMb8w+GsVdldmAjkcUOv9PsIOWM6bFz4og5er+7nx0n2ZfuDV4DK+vl/as=
*/