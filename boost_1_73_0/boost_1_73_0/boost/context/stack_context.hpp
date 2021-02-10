
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_STACK_CONTEXT_H
#define BOOST_CONTEXT_STACK_CONTEXT_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

#if ! defined(BOOST_CONTEXT_NO_CXX11)
struct BOOST_CONTEXT_DECL stack_context {
# if defined(BOOST_USE_SEGMENTED_STACKS)
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];
# endif

    std::size_t             size{ 0 };
    void                *   sp{ nullptr };
# if defined(BOOST_USE_SEGMENTED_STACKS)
    segments_context        segments_ctx{};
# endif
# if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id{ 0 };
# endif
};
#else
struct BOOST_CONTEXT_DECL stack_context {
# if defined(BOOST_USE_SEGMENTED_STACKS)
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];
# endif

    std::size_t             size;
    void                *   sp;
# if defined(BOOST_USE_SEGMENTED_STACKS)
    segments_context        segments_ctx;
# endif
# if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id;
# endif

    stack_context() :
        size( 0),
        sp( 0)
# if defined(BOOST_USE_SEGMENTED_STACKS)
        , segments_ctx()
# endif
# if defined(BOOST_USE_VALGRIND)
        , valgrind_stack_id( 0)
# endif
        {}
};
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_STACK_CONTEXT_H

/* stack_context.hpp
b2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0FERFJFU1NfU0NPUEUuM1VUBQABtkgkYK1UbW+jRhD+zq8Y0S/2icNJc2rqXnoqsUlC44AF+FJLkdAa1mEr2EXs4jhq+t87CziJ3UjJh8PCuzvMPPP2zNp3Jnz6YY9hazh490naN8EH153RvBZ/01S9bZAkT9D90PAO1w+4GsGL1VMyhA9ZPcGgtUp6X2d6nyQfcHeng9R/I218l+gtSjrL3n4iqsea3ecKBpMhHI/Hv8Jn+PnoeGzBlHBGC4gU5Sta31twlrWSP3Ky3dqSfrOAKiCFvQcY50yCFGv1QGoKuC9YSrmkGRAJGZVpzVZ4YBxUTmHNCgqTYL70/EsLHnKW5j3Oo2hA5qIpMsjJhkJNU8o2HUxFagVijQiInzGpELNRTHAb3VNQtC5lD6ODIIUUQDaEFWSF7oiCXKlK/jYapU1dYCajTKRylO5KYeeqPMhqidGU5BFEpUAJaCS1QOtbUIqMrfWKJUJh1awKJnPrJSx0yLORqEHSoujh0JRR2aVAIeqrZWlNqDB6pvQiBZfa20Muyj1FLGsPtG5qju6wLKiXCSy8BQ3PaN3qt4XYeemr3Jb8nZa9xJ6B4BgVmE4EXmTCikgmLbj14qtgEcOtE4aO
*/