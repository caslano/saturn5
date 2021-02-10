
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
glkmiHCiSj4ZnDU+z35rpn35j/0GUEsDBAoAAAAIAC1nSlKx1Z3xSgIAAP8EAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUyNlVUBQABtkgkYNVUXW/aMBR9t8R/uGPqS7XghNJuWBESoqhspSWiYdqeJje5kKghjmJDy7/fjR2Kpn1oe9yL44/rc8699zihQW0SqXHEwrxcK/o84eFZ1akesVkcR3aAm2nsJpPF/f100i6qWr0cmB3NriyxYJPVcr6I4m/RcvHl62w6vp4uWchPiCF3JOwtPGC9x9rTeYosrLEqDnScKIJJjKPmQS+Avu/D4rbDXLggTtRYmg7rENhreJhKI3+6BfpZJ4XS2GHX0qCAeIfvwB/CvdpTSOBDMBCDoaDgm7v4xNHUxNN2wdfyia7PJe3cqTRf55i2OMEFfNqVDRXh9EXgv+JMY7kR0O0Hfv/SS5P33sVwcNUfDD90G9FOqlWcZJg8/V2y/01qbU4hb3tKrZ4UOWXRtjqxCwpwKkYsM6ayg+f8FPLjSWiUKkasyB+Dy/4VHbg1hKXckmF/YTYBGitZU0UgU9pwiwgZyhRrTRe5uwlktO1WlilNG2bBucmwp4q0t1Wq17CJs6bi0WIZ82YJZ7PFQ/wxEmeW
*/