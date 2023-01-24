//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <functional> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/functional is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_FUNCTIONAL
#  define BOOST_CONFIG_FUNCTIONAL

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#  include <functional>

#  ifdef BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_FUNCTIONAL_RECURSION
#  endif

#endif

/* functional.hpp
F2iXBem2nVP6R7FQoVxIRgrNbke///KWtlLXploWZduanRZ0+b7VvvRas12CMUUrY3HqN6dgCQ48I4Fb1Sp07Im1Po2OQiDk/V7X0adLh/PgaXVcN+fc3xTrxyUsDfCM3ImhTAk6LERkxQTNrDqQV4h0bCTK2MFFekgErfZo8FPWo5wpM+ig38z7ux3wlk9SnY1cESnd0l7Rpn0qPyDrEQNfhFQNiOqGPej3YuxsZRvvswVyx6Qv/3Piw5PcvoywePvwWqGICDKP0gif7a7W3btLr8mrdMH38tUqNPaAqrtoJ/4FhSt5PU4NiKoBd1WepsB5Ym1q63k3jXvXIpAYJwNUdjxsjO89dxptTEwvt/N+k8QyNXHmRZbs1hat/+1DVdQol1+x6b8Vwzfb55M8nZepJ0Z1QvIoJlWtnu8hH6XH8n2idTaf29qeRMzLPBIs33fbM6jaomqcjypv8wkmxq5sCnSlDfK8uCpvUsgLd0Dt9eOouns644OIvKEtSZ3hyzrld7A/xXOcd3b87AvKA/Tbwqrv74c488ytaEutqbXl/5Z0DEUXKJpe03kmHFG+G4g+Auztc48Q2TJuXDw5bK9keAJu9mSmSu1dlqqVt+SwHlUyvuBElRyyyOJ0qnRWfAHWsRaY4rJnmKTzP0vYude15JDvmmNrd/ueJ2E7+sNLr5p1blPSNPZOqPt7T5inngdeKn40NzBb3H5q
*/