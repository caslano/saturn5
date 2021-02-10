
#ifndef BOOST_CONTRACT_DETAIL_INLINED_OLD_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_OLD_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/old.hpp>
#include <boost/contract/detail/declspec.hpp>

namespace boost { namespace contract {

BOOST_CONTRACT_DETAIL_DECLINLINE
old_value null_old() { return old_value(); }

BOOST_CONTRACT_DETAIL_DECLINLINE
old_pointer make_old(old_value const& old) {
    return old_pointer(0, old);
}

BOOST_CONTRACT_DETAIL_DECLINLINE
old_pointer make_old(virtual_* v, old_value const& old) {
    return old_pointer(v, old);
}

} } // namespacd

#endif // #include guard


/* old.hpp
KXLnsWfOnNn+ogcn/9rH65M7ePKT2v8UP3jdGk0b9RvPzJcN0vQTuD80XOD1GaEGsLf6lB7Ds6w+wZG1SrtYb+k+TZ8RbkFJ0teAjBcp3eITZ9nZX6h604gPpYGji2M4e/PmHE7hm5dnr324ZFLwCmLD5ZI3H3x4m9snP5fs48e+5j/5wA2wqv/AYVIKDVoVZs0aDnhfiYxLzXNgGnKus0Ys8YeQYEoOhag4XETTu3Dyiw/rUmRl52ejWtClaqscSnbPoeEZF/fOTc0aA6pAD+g/F9qgz9YIJfsYnoPhzUp3bigJVmkF7J6Jii0xHDNQGlPr7weDrG0q3MkgV5keZFso+qVZfbarO8xmxTagagNGQau5D7Teh5XKRUFXhAgf1u2yErr092lhQJkPVAOaV1XnDk0F124LHOIOLZ9WQo3ZC0MXraSmaOtSrR4sRFg7R0XbSAyHsOC6XCHwPrQy541db4HYRulQtpA/UbJ97jkoiVlBL4ghjHuwZFpoH96HyVU0T+B9MJsFk+QOohEEk7vO33U4uURuCIzaAP9YN1xjFg2IVV0Jnj8I/q92utdPruBiPhtH0yS9iCa36WgW3aSTYfI+ml2no/nkIgmjCbyC3tkb+LWVxPRve9CrxJKoAK/7r173X+ID+pVy
*/