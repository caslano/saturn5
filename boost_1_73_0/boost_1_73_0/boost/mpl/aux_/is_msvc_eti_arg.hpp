
#ifndef BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED
#define BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)

template< typename T >
struct is_msvc_eti_arg
{ 
    BOOST_STATIC_CONSTANT(bool, value = false);
};

#else // BOOST_MPL_CFG_MSVC_60_ETI_BUG

struct eti_int_convertible
{
    eti_int_convertible(int);
};

template< typename T >
struct is_msvc_eti_arg
{ 
    static no_tag test(...);
    static yes_tag test(eti_int_convertible);
    static T& get();

    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(test(get())) == sizeof(yes_tag)
        );
};

#endif

template<>
struct is_msvc_eti_arg<int>
{ 
    BOOST_STATIC_CONSTANT(bool, value = true);
};

#endif // BOOST_MPL_CFG_MSVC_ETI_BUG

}}}

#endif // BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED

/* is_msvc_eti_arg.hpp
lSK2l9B9N7sRTait75GZVyIROXp8uJovHlguVq6qjCYMt8JY0y9zcLV2QeuP/SAT1gsQaq52kuoZ+90JsoP6wuKpRU3j23YUyUYdRm1GpVDW95p6uevNUQtetJexCTW9i+XvmQetW/jaDbWu3aBQCVndneR34ziBkm4c6j84/t8pOTnMBKPx7ff7P4jy9PHh6+LrNRwXwtSHlAYhv9Nu0s38yQ+Cf/64uPk0byUJ3eVltSjbxc9/wRTevQORwvExLX76G9ifXRx2Am/fwn6DhFOaiVe2DdeSTCfuFnyB23a5KxTr/un+AVBLAwQKAAAACAAtZ0pSx4Nu4BQBAAAcAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMlVUBQABtkgkYI2STU/DMAyG7/kVVhHHEbQjynrhQ0LaAYGAIwqpu0ak8ZR4G/33OF3LJA4TJ8v2k9f2qxjGzM5mrJXxsSUJXzgcKDW5Vg+P63tl9Klg9JFRF/CCaY9pkX2DyiTchkHajWVbqDlOdcFvg8fIE+7GRIA8itSq9UHKek7BRNvLRnwgKK0breH1eZ2BCTI3tGNB9JExjvrexgZoy57iqoq08NGFXYPVUVheB3I2dJT5spz08fR+J6WNLrcvr5dX/M1Q
*/