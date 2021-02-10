
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_FIXEDSIZE_H
#define BOOST_COROUTINES2_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_FIXEDSIZE_H

/* fixedsize_stack.hpp
9BxnU8OlkBKJq0sSm7K8K/g/JdcGz1ZayPnSmpPE6gRpqQnEqQLBXNAVGSxR7mVuhIRcocpRGbpMMmiOFdSTDOqPGH0/G2xKc+1/nPQvBpPwoHt4PxvbzKacWoYVqRSkbhtROce+SphtybKX0LM0ra3GfoA1WBTKqERh9dAdK42aYx4JBr+u7ah1VP2QJQlfoJadrQ1FTyRYokhhJ3gbeTyeBFHQC4Z1Ch6cr7F1z1gpDdSxODZC1pDetX9DFy6x9oQxPkNqHpvc4ODU+/037+TQg0BSxZE9muSFADQJWn/U49H3NthdL3xFuSB+SnPqU8T41BZZc3QhzNopUD7o9wxCFBtHfR+/8l7C5WDYt4GFvbFNf2NcdV1dn33Z8ToQXp9XR6/PQ6eZIBsDLMhtxvMaZoHCYlsauba0u4QHq2urm00WNP+MdeqkIjHMcF3Nvoa1KNNM2VMWZyTPZmLqcqrpUG42h8/gEtPvdo5dp9s5sYF3O93mfg17pNJYcryovmBW4GgZB2FE1HzXj5DxErv1Lp9p19Ki5rPIcTiUSNbGrxXcUpC2fVn/ayGgzHXFlDn7zBsDahpVMtiPNqGwByZyxJaSwXwLgkTRiM8/27N8hVOJ0JY11jsFEER2BTnDnuHar5qGDXfQ16cS
*/