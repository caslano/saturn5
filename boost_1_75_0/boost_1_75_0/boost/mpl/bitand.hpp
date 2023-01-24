
#ifndef BOOST_MPL_BITAND_HPP_INCLUDED
#define BOOST_MPL_BITAND_HPP_INCLUDED

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
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitand)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitand' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma push_macro("bitand")
#   undef bitand
#   define bitand(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitand_
#define AUX778076_OP_PREFIX bitand
#define AUX778076_OP_TOKEN  &
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma pop_macro("bitand")
#endif
#endif
#endif

#endif // BOOST_MPL_BITAND_HPP_INCLUDED

/* bitand.hpp
kBvUI3ZaZP3+2zvL+Wj5PS+5qZI7+YSljDKa3VrigvrGLGDhONRUjHK+eG3xNiVyyEjgt6mD9246ZcBU5ojJwCXVC2Ea1f06ltQrRw6CbwKenqZmQvvwZfyn3EplJ/7UyPGY0VEykh4u+B87hiyDnx4rcloUzCdz7nuwudk5anEBiSZjhLNQyitEBoThbkJ1mF1pPFcqYZVpEk2AXubVsqTrAHWjH8uC0f2w8tMsfahXTvUFgAsoqONO4RV4w7vv1a6U7nXmeTDfXZKbzf5UuXr+nUnvQKvxH8W6HZdqzjGqMp3XPf1Fm21bdUIJTLbHk3yOHd7w7EtCOA8YWa/enfdx5Gx9t8MUovFuxDxtmYwk8jJYh1KMPNAVeskVVrXxj7ek9bK28s2wmpOfbvQOMarqNkrpLWwd1rCp6v14hzOSx3lgL+Vbv9AREzhWm3AqiWkgU+7wbjI18zAYxtA+IqfSgCMcmRMWafInrq1WS1TVriwVUZrDoT6LNKSXJD98YVKcOIOL5A/CEF4iQ5gAvgGLjxdngAPo51htX7NPEg8I9O05t9ag5Vd8CB5A+lNWp0yI5EbxGcRs2mzK9/DsgK4G/IgbMAQ+6DpQgeGiPnflNh9mO1i9ERf32/MIvksQET8PDg7e3I9R+yUoJ8Jodbu/K3bH3kreKbNNXasKxCEavZTQHyz4BQ/00AVyUvt3+kkCOZ/0gZydH6CL
*/