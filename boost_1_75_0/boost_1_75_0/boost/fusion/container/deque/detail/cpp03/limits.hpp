/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_LIMITS_26112006_1737)
#define BOOST_FUSION_DEQUE_LIMITS_26112006_1737

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

#if !defined(FUSION_MAX_DEQUE_SIZE)
# define FUSION_MAX_DEQUE_SIZE FUSION_MAX_VECTOR_SIZE
#else
# if FUSION_MAX_DEQUE_SIZE < 3
#   undef FUSION_MAX_DEQUE_SIZE
#   if (FUSION_MAX_VECTOR_SIZE > 10)
#       define FUSION_MAX_DEQUE_SIZE 10
#   else
#       define FUSION_MAX_DEQUE_SIZE FUSION_MAX_VECTOR_SIZE
#   endif
# endif
#endif

#define FUSION_MAX_DEQUE_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_DEQUE_SIZE))

#endif

/* limits.hpp
a3Zmar1jlF35hqiEqSeLbEg0VZq7wgjY3cNMajZWNMhEe9U9LFYdQDGxsnNrPBV1bo9H4PB8gvTRLOUiNMKqZCtd1B9YpKxSmyvC7ryf13qePfHtDCFlMbxWlWLYg6wyPhMNfrFaPZvQCGiVWocQwTZQljLbxJ2/sJZxGAhQ9tSzRbcF6P5zi/27P2dxgO57PscX2i4V0JtFdudsSSpiuFeOCbwfqMVIxMpgkJJBugMbDPC1WZxtmLV/9Blvlus+CeYjD5QF7O7Wu+2uHFAcmGN3m9l3ViwkFgBCs0NHaNizCB9FW9XHPjrr3a1OMJMSu5z6JXt/Gozznpfdd5oMD5gH7xcPGHbMkgHZXIyCQ5YN0T2onsG9Y4/BcKyfnRJA7f/6TjssZO7SLgnVc1ShYtjqfs38h3ALmAbWn6LKUTocJu7zFuwLGeLAfNiAArCj2b4HPVeZgWIum/BclpjL7sCYja/BecvmJSYEv2R2roefL6RXVKInFt0PJNCFSDZBKopaKRe4hUQ0DFGc72NJIM1AiKJbEQ3Vn+9BJw+KBQACls2uBXYXjGCzGFm7FPjSzlpTbdtzXphw/K6q178P0rd+77FGImX3c4BRekL77M90h8sXLZLqtVzwMjRxLMMUnUDGZEENBWRk1wnCw51F0iEKVEoC06VlmEHu7DRREEsB2UMNDz8SBxnJeurWSifgppGhkrg9fe5llzCi
*/