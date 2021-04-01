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
j7xDb8zKbCn94a2wTOsjwZsQI/B/YOVCJ/yuzPvaKmtyhc13WD7Ln8eh6Ra/JdpvKEJ2wRWg+WwGaj9d+iRYjpWBxmMr21FkneXvulJCx5cgA217awr+EnALRraLMYJ+XEUuOeUVmDls4hPDCBGdmW6QRfTzbskMI25cH1Z5oKTI6A3CDZgqfyUs84sHt/SEPScnyLgGQAUwMHWtFwYIZmyi9nXUnu3IubF5tZo7apIowdfQSV8TC6P6cb/bfguGNCD8jWVQlb/w9xjBixwiWM17yDdyocOFn5oYkHcsOIK1qPUhpUHXtupHQOPJWalAJoLcqfQJ0696G0nS1sSklVQUunAvmNOogVH4LzTvrVT6hbt/8pWBsCvDkf8L+LPz366T9jvbvy1zzBufUAIA9A+BkPQV4050Leav8x1UuxSpQAucSNsKTwvzJOyCr6zBhBklmjH0k1lnmWmKpxbS+2WubOkCBn23XElsbXlnumzWVIP+HDmqYAju557MvpsbpuQt8YAk21ufSQ4LmWmSnfShYcz0X9oviVTLcDZjE/bwQqvV5KUTOyvQGA==
*/