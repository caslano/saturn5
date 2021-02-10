
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! defined(BOOST_WINDOWS)
#  include <boost/context/posix/segmented_stack.hpp>
# endif
#endif

/* segmented_stack.hpp
Qh8sZXRv6UgmnO/1pi1sOft+x7XHNFq756HITIJpWcEOPIIWPg5Ja4xFIEXVo1Fxw90rlT0iptwU3Osr5xeHsvx+LpaA7YRd5qp7M5wLRql/MJmO5+PeeDgT3Hj+Uf/f3Q+TYV900pUoVyZPJ39vLFQ61e4I65FeHfHDY/ovCO7ZvsUPDnsWLm1qVT8kMNWw3KoOEtCCIoifnYTC8MxsjMp6ejZ2Q0snZ9+2+Gyzax1MTVQO2G2bUH2qMyuPlBG+Ff8TnZX2Cer+2h0Mu78MhoP5rWhwgm8EBge8rnyoF96lgjKFcfX6VedvZX3rTaZibN4W82pMeoLx1T5sTWVb+uFZbhw+X+iMBn/ziPG8HqZM3U0YRl6cQw6zEYpyme+faAgvazmvrRblGdkQbI4OflVPe1sibtqf30xH9Gt3eNMXU+Xw+8v67PQX4/ekyxYJ+avaneveDoduRu9H44+jxdgv4CyALmiDWkVQcjNfjK8WH/ofxtPboI/HBEqB/atYIb+a2w3jJ0PGZaRKv1qzfp+6w9kYP1Z+mdb1muPn2eyqPz0UroU5BOjQ8wFVvXqkgF8veuPRvD+aLy77j5WI/wNQSwMECgAAAAgALWdKUt78Ka7FAwAAKAgAADUACQBjdXJsLW1hc3Rlci9k
*/