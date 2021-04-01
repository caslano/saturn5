
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
LvmI0KiiPFbaAgZRQ7Klrd0QjyOpmuwQDpPrCDNxDfELaxY4DQp8uBk0VvZm5VmlwUhJOHv1ipCzLbnUAFt0Nkanx+uzbpT8UwpG5ZugVtX5G9dTgGwIpJ62RQdTWnOkwDRgVjgh52nHy8esMBJ4yMt+Sex3KSjSf2lOBZ/ZnPvdX/DlshgdKbPHsb023rxwPe6WjSDnqorXQDBC6VAWCqg54tP9I4rlnZugmvNEbKkkHw8vnuC9zlusvnPncYcZPPKf01yurIDoibEYYjOWHMU0aPmdRUQbyp2+cEp/VJFCZjn6CWZOpq2lGUMXSBuWtrDKVTMWxTOc6eotg4aLrkA/CSVj0RBW6e7FItuMeWr0rrJvvZS/de7ZurwVfMH0V1dunWkRiRgQ2vW5pIaKVg28OpVOzAbrnCboTZoXnjMzVkH5aQhEh8QTBMoE1fJitte42Et2V/3Zvm/XtdxwGw36IuRX3vSBBUTy93S6Liz1yaSaTFTw5JlFVbeb0h9Lb7Xzu5FopVkR3L5VtRcq61Fzb51+n7dB6A6JwCeIpD7kaWYEqBzibnq1Fg==
*/