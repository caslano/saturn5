
#ifndef BOOST_MPL_BITOR_HPP_INCLUDED
#define BOOST_MPL_BITOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2009
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// agurt, 23/jan/10: workaround a conflict with <iso646.h> header's 
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitor)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitor' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitor)
#   pragma push_macro("bitor")
#   undef bitor
#   define bitor(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitor_
#define AUX778076_OP_PREFIX bitor
#define AUX778076_OP_TOKEN  |
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitor)
#   pragma pop_macro("bitor")
#endif
#endif
#endif

#endif // BOOST_MPL_BITOR_HPP_INCLUDED

/* bitor.hpp
AnHb5BvR4vL7MduLpsb7ACEI/ZExjo9U3BEeu6TMo6nrjzLXDDmxkcsowF76GTtFiP/gpWxKnaFBeYXePBNVisso9g2mi2XcX8O8iDdafyn55FWmzjHjODRzK8fDaBsOFKNfqAN1DVNYpEvHRnPhaCqzfijGZJ/dVoeAknJRya6CRzOo2tND+PuvmV8570taLh6KIwNRF0xkIahz7fN4iN6rqxM8NYL7p8gQx8sZTQQObLOpuzOUJosOSVb4sfPmTiiLFYmD7oiH5KRdPAuxQt9Auzgzg284/x3H5BSy4rCQkYamhY6Q/S9je5IoplhvjoPqWxTLleLBmn+w7y+1x2DJvNgz1X3uqJDkpjYJszuUVs/GeddB1+s2CgDXoiCxqu7n4M5m7oz2x8Qfd7JFaU9tN1R5QV+DTi6vu1MIzlH0KsOorn/guPe0LEjgHwYttv/xiftfA1Z0vGw8FVy/2HjaWlj906mVjWdMNQQaImf0j/VqU1hOXSiuXF7glyPdr/vV4JD5usZKwCMjqt8hszjWeT5XH1fuhRh0seqM9W6nBt0rXQt3jf4veXNXDwLM3izZVXPXjYT1kAbW71y8gpxlmg+ouUfd8qW1Vp8bgQISuvYOWMAECZyuSZ307pk31XWRy4drM+i2bagxNZ2thjv25b1S5gQ/R0bdGxSXMfrPBwBjAN1ZqK8n+MxSHBxx2y55G3qKtYbTRneF
*/