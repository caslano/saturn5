//  Copyright (C) 2009, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_PREFIX_HPP_INCLUDED
#define BOOST_LOCKFREE_PREFIX_HPP_INCLUDED

/* this file defines the following macros:
   BOOST_LOCKFREE_CACHELINE_BYTES: size of a cache line
   BOOST_LOCKFREE_PTR_COMPRESSION: use tag/pointer compression to utilize parts
                                   of the virtual address space as tag (at least 16bit)
*/

#if defined(__s390__) || defined(__s390x__)
    #define BOOST_LOCKFREE_CACHELINE_BYTES 256
#elif defined(powerpc) || defined(__powerpc__) || defined(__ppc__)
    #define BOOST_LOCKFREE_CACHELINE_BYTES 128
#else
    #define BOOST_LOCKFREE_CACHELINE_BYTES 64
#endif

#include <boost/predef.h>

#if BOOST_ARCH_X86_64 || defined (__aarch64__)
#define BOOST_LOCKFREE_PTR_COMPRESSION 1
#endif

#endif /* BOOST_LOCKFREE_PREFIX_HPP_INCLUDED */

/* prefix.hpp
405ca5ZZuqyXUKD8jo4vJGbXYtp5oqzVUc9aS6O7Wk1j4qwnY6OsD2ObeRLjk81zaZKWeD2XVqrXYFyi3Lby3rm+tRaTIuWbXqHWEPFEEcIivr46Yt7bU4fdRM+vlc3LXpxdajnWNXpb+XkqrilStwNjed+yfub7NNo4D3eFe/6+aEkhDKwB98SVtvsKzyRC6se6lPMwyTInOH8zbqx82J2vEC/yROl1Zt5QYW7znEEK9mDus24wzus50/KYnnNUj77Or9hNtp9PY1ixJmZwzB7jnJ8znL92rM6TMrNuAf6N84mir8JRocrIU2I9q65v6bi+peP65Op1ETILylg3i1UkyvNyrWTJu70qnEKeo0bWWIxd373NHmy3qesT403rxCTDP6t83R39FJpJ1fegXDJ1Wev1OB9R5bPc05kve8+lbAowgbVDBmzBjackhfu+zH0vVvcdEn/U933rvOgNntdi7nXuk7e4eN6isoKVefqZbXyN7f9uznN1XfxzVR4pOq9uVnHt6xlmvSplRm2prjsHiWjLPMY7WufnVeV3rMqHI8TnOhWflvGO/QJFj4hD3Wc98wsTsPPL2xaVnmv4lrCjXsvqMZX+4fWu8Lzlk/xzPEvtdDt15GrsyB0VPr96qfCTPQ2t9yR8SkqFP4fnYjxpIXzO/qjifIuXt9Le2d6hyj4Zm3eU/c5or3WDt8r7qbdJUBrv9Y61kr3JpPME6fT73RP9rPUzT5X3DMf+iAt1vt621fYzQcf3fhWXflI/BO5X5R1n9eHbsu58J/+UR+6p3YbwsUtKsExmlyOW+faKbiuq9yDsoPIn29NQ0rha3StKycL30i0O1hjMLFuS49Dr2qTucZhleXf6lJ2Wr16eM62vVZk+QFrvU2X6dVx1W05YjnCmq2tmox/WQtcXkj/I+xHy5xLP0Khsj3qGdJncS5n0o1TGqX7G/qA8vYt0qDWBOJbZ8qvl5S0lG/meNlYf/PjL2HsVdviw43uQcO5U8U2Il+dAnjOJs8Tv3C3+5ziNOCs7Ha+H6XmuU2EdJazfqvsdjGnir1c46Bpkyrw/fr7ET66634R4v56F7IEr7sdw36zcO8RX95MW6bq4kyq3DE9bqxG223neoy0pC11nxFnXRicT1uGgPHqcfN3pia8uE63Tt1A9Fy97u1tR3k5OWeO6alk7wPXLPJOioqwLo9I91WswstpWXml2eXGpLt+h6rkqodfbQ6/5kqjypa8qu0+J1waVxu7xn8Q+hZ0uO9pltVGnXl/mUhWPeHWezPkbKq5t5TxQz8SqvDtEuHtVuFGqLLOUHAf6aNXry8xRfp6gbbpD5J9vUlWcL9N58nslIw28Xs+rui5tr9IQI+UfOH/UG4WWgTyj8uw/7J1Kvm0l3160Sj3tiNvzxK1Q3Xdg/GfE92bq6Gt9sdbtvhescdTDQbLnr4Z1+3ejCrOjJ4ae0wDrT3ptuVUqvAc9s9HnWYtphCwM8aRwHe663vqNNYG4XEFckuW5uVFd1yK+X/Qiz+P10n2p/ntLXvnb38ySvNJMFY/qfHtZ5dGPotKs5VE18kTquZv9fbx4X8xHXlu+v24WKNfqcEpVvKzoRta7Uf68xIcKp3/sRDROAvVfe1XWV5P/znrYq8r6ae51l7pXrOO5LS8uz16sOi+pcq9uKtw3fGdaHb1jveM928jzx33Nqst0i6wXSpgHCHOg8r8ktjrMwuzlfpHUz+CdSjY2RCdZu72fe/tYI3wDvSLnOrwm8vz9SMXRil8Vm+dpqMNEM6isWsabXVW9X21JVGBPbMkzyZ/xKu1Xeq6ljVV2WtZyvPG0S02kfT9f2Q2p93efbtclPJUGrRc2V/k=
*/