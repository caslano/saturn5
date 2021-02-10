
#ifndef BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>

// MWCW 7.x-8.0 "losts" default template parameters of nested class 
// templates when their owner classes are passed as arguments to other 
// templates; Borland 5.5.1 "forgets" them from the very beginning (if 
// the owner class is a class template), and Borland 5.6 isn't even
// able to compile a definition of nested class template with DTP

#if    !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x560) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif


#if    !defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__MWERKS__, <= 0x3001) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
        )
        
#   define BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif

#endif // BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

/* dtp.hpp
mzwvHsMofm1hr3HIluHkYTlkAT/VDbijYpfsEpZY7rD0jEqQBSUWWUUAqamctE4CH/QGcN3vw8RFlc6BVIu3TJkUE0b1jngWJMKKT3nhA/shLPoQb/Eb9G9hrnf0YdCHwY1/c+sT5O4pZlTeYm69R8zfberD92MkrgrKtniwvMiEyhmjkgF3VI5SpijXZ+r9b+JaUQFv+9o0fJKpOs01XDYbgphmDCOWWls0i+ema7Rcm3p8HwAIcrEhu7SHA6vBFCjVSklItbGwUwKaoTt/gMgTONkFvpi9sjKt85xpYKMTBLG1eiOskiLLqq/Ewh1NsEJhtyWSbZyggJ8iQEbZbIjA6fY53+/3PTyITZFhj771rvvDIa8X8LzWJB4x+367+QPsd2utUbiIwTtAdxYu4/vI70aL8OcvF6XGoDuK6w2xHmHNuWtY48lWGr22XW76/4KlWlVQzwfEymIJNkWo7yGkwsAbYg4XJtX2ggW7BkslGkJqurtXcIb6D5N12Iym4p+R0mHPNGRv/E5aCb8tM959mS6W9+G8w6JagHdytA8PiIU3ztQOO6xDh2wl1lKtljobMfprgGv+ZzF/G9M/6cdSYkHhK351ZGtZaHNsEz/9zn4DUEsDBAoAAAAIAC1nSlKJjlKUcwIAAGAF
*/