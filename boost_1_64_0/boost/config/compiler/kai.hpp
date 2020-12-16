//  (C) Copyright John Maddock 2001. 
//  (C) Copyright David Abrahams 2002. 
//  (C) Copyright Aleksey Gurtovoy 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Kai C++ compiler setup:

#include <boost/config/compiler/common_edg.hpp>

#   if (__KCC_VERSION <= 4001) || !defined(BOOST_STRICT_CONFIG)
      // at least on Sun, the contents of <cwchar> is not in namespace std
#     define BOOST_NO_STDC_NAMESPACE
#   endif

// see also common_edg.hpp which needs a special check for __KCC
# if !defined(_EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#     define BOOST_NO_EXCEPTIONS
# endif

//
// last known and checked version is 4001:
#if (__KCC_VERSION > 4001)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif




/* kai.hpp
qajVRZZWKGRR2ijJtestMOpp2xnHUdfIzQBsdZKmo0KnQzLLVWlImbYXNgcQzPh8uLm0tdzYki0uDHpnSVzzVZaOFBBTLY1yko5eG/S3Bms7zRhxJiULS6sbDoLq1f10sdUnVrdMVFEaWh3Da6gVt/P6n/Ujba9Qj1iaUqgwcknavTpwXE9eQJ9mNC0rMhWGFvyM9VyIjfWtvlO/82Dg2JYB5W5zuTRMZW6SUkBHg9B2b6m31t9BOfS1SeUKUSRBboooRjmSmWhlJj/MdN1EZRymqhLwDsjVbmtzHe9xRFu+41RGBkJHtojBIR54MIb4jTwzjEM/9WHum7Q2Xi67OfxTQ/5Oq3OC5SOhf6u01GO6l08P7XyM31CWTiziKkltpqM9xhMUh86jQTu2r3n1Niq1hU7BJnModH6nNTeGdGgaQrY6+2E+P1RJUtXHONP/sz6irc9NmoaKRRTLzNhUP8OxiLaFT/CyFKrKsiqSYqlJpqkOZH6+7fsnvT4xubJaRmLMlwjkttDO5CP03j4zWRxVmRHtfI/+/Ns6HqN8WYlMlXC8ovb6fpNJEFLCPpth6RTClIEtq6Dk6YxPBO1KaRpnpS1ylWeZ2GmUpi37x9o8V1meqYgS2NFV2V5lB93x72cfZmkkQgVSqUhrnsZIAkHZvp1k8qWw7p+oLJNRnYc4cC6l9YU1WPLDo9rmf5k/u1s0vVyUtsyzuEoFkcY+xPM5KnNKBrCxy+XwM+rPeU8Bt4kjP7Vw5z+wPm7ljs0TuZU7/6FyU0Tu9NSd/1A5S+XO3fkPyMFb+a+6cy7i6H0CfvtU+1tjc4F7Iffvqyfk2TPDo4v6/Iv5UdgPuA2LeYznXXPqUKsLG3ju8LpDwJuts1jaXl+p3cdT+6BJxOsDmDajl7Xyz+tw6GMWR+YFiNFS4j7w3uOAY2zarm7177Bbgjc3/V3fvv9rL2/xJtnhehL384++EnAIi1qXGIhdfOYTgKEfBWiWpkWIXd9rgAODZb6ed4YvLcjZ0usRX13ehn1u7TYb8//1GxkOj38Q+8r9DIN3FIhNvJlhcISA2JMMgzM00h5vQ6wuyDDHDr/8dg+HXAn+63d4OORM8OtTFB/UJaDnJ585B3g9s88P3KyzQzD9gMNgzy1N5af7Z4Lhg0Uq+26Cw0aeyhIMD1yI7E/fQ3B4vEGw6xc6rDkAwDOCXDQYGYhNeyHnRDDKgfLTs9zHx3CwnCStR+Uory0vvldToxy/3Fa3HJwsmmKT98DhCIe9I/31KD72LOuH0SgPikw51+MRTltkLM9c0nCIC3J6XvOPURzTQFtuAxy4aOzDe6TujDxjvw+o/dSNnGBb6ygzU+Lvwxhx5G79W+9n9qyq0lFVJiKsvBhoD8/SM45Uh+CDIxTo+JdybzBumCiTZGUkmDdc9K9M889FmFWZzTOXsJm7MM19oR7A8xMqU4rMxnGhIyXAOY8ndaAt069omc6aoFBFGRlBPUuX7f73sfd7cXl1pUptkpY9rUNn/GzsXNVUhsYToLIzaZLrMAkzgX5HGr5ty/UXyj9jsygo89yIi2HHFW3aP55lbZWVJiyCrBC+x2BcU9C0z9fujE1sav8p8JFw5y8n4U7OywcmVpaPVtLGQVkK31MwrkEus3zSKHYZxDSf0yyfVu4ElytkqjKjqdyZsXJTXK4sc9daIZWbZnKt3hy/xGPtRYEuqjgQdfMZRauGeT06x/c8UZaYPA+1GOf+mLThLSp3PipkIoPSCs/z8UTclk3QOlmRl0FRyjAX7zM6rJwfo3E+1i3LI60KN3JiKUzAB87r0O6ejcvEVLnWpWCOjgPcg8/yeudZKU0qpRjn4pi08eXLrI0=
*/