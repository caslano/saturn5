/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR30_11052014_2316
#define FUSION_VECTOR30_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector30.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector30.hpp
JOZbRTdtq/IdDvsq98ChgQZ9AN6gDkCAE9agFqU5B1MO7LWcBk4HY4d9EAUYALEeAl3ULR8UpFeIWEJXVAKdztEmQP1idS0xvsKonAIvY93tDywDISEvszFLdWGCGfc9vk78OaF9nMLkWQoZ054BG8SRQnr4bhcj5Ajyh4i8vPfi+OzgOTj796cn/7qs2QwApQqIiSFzggD5861YXxcPnIaiBD5gsAltFjQtDdWyOJq7bGHbliVQNKljshi6SNN+gjhbRRVI16uShhWph7ONDK8WVnU7VUtWGrxIZN2Nt284jJ1BXLkkWqd+cM2pqqDRAM4l5rdGZCwWmLOWAyNSVhaUmoE3gEwaxJyDyCA/LWY+N1T0XMkC9LDENDcCMkBZU5YkLTHXCQf2Q1Q01qa1h3H4UK+NiZvjaqZR7dTR8LRdG5JEF+nQbQAkxICQMq5yc8cQOK3B7b1Ng2u9XSYx/uVuZJ4gEhlHDwZoMqzlLcPGt0PXfRMib6D1GJ/Cw4BCFNLhyWRyeHD4+sh7e3L4Zkjd8D00A2vx6yLU1I62OcPFpDmHQSFaidnzNk2vRZnRfgwe3EBmi06kxQrKz/GVRkEhnwk1BgYQLR6YjWK+jVmqcTlbqAlguJOT86ONjafiA3ogSP2ZIMi34XmW
*/