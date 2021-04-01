// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// no include guard multiple inclusion intended

//
// This is a temporary workaround until the bulk of this is
// available in boost config.
// 23/02/03 thw
//

#undef BOOST_NO_IS_CONVERTIBLE
#undef BOOST_NO_IS_CONVERTIBLE_TEMPLATE
#undef BOOST_NO_STRICT_ITERATOR_INTEROPERABILITY
#undef BOOST_NO_LVALUE_RETURN_DETECTION
#undef BOOST_NO_ONE_WAY_ITERATOR_INTEROP

#ifdef BOOST_ITERATOR_CONFIG_DEF
# undef BOOST_ITERATOR_CONFIG_DEF
#else
# error missing or nested #include config_def
#endif 

/* config_undef.hpp
BUItR+Yn91T0KT+SqmBkeB+39DBL+SQB6u7AXo4ufu4C4iB6hYFKFXvL/W8WZSdZJembaZ+YuPoJB+8/atM7RlMUaFpyjYnCQ2uo2tqbSVt8EDe3DklfP72kupbt51DKowU3kImnYU0uO+ymxrmPVmDh3YQ6sclgqUBOi9TrqXO0bCipYGGSwSWxRjAFM9WqehwHLQsavWoFoG14XbPN4xt5WrIJPnhQpwdbT3SJdkGdwoLLdVfhXr4+lH09eFYDi+r2bObvRsnnUH4YM5BFpIEY+vm49E1Y32wWbi62o4d323vQrtcIOsstPTE/FRzw9Ut78SXg4Q08Kkvj+XmdaUX8AafpEMAtKaIluRVb0+HaxIBIDBbPeGCvXT75GUuRmpVjinz7oCLlSQ2nEi8YQdncSAoWDVzn7wcGQ22oK/l+Zo8g39kYSUS7wye7xYB3T5HzcZhYWvrTsdb1ItVCInDkuImtRFm+TrH7dNJzFuBrijkfAI+DJkdK0sm4ef+uvBTchUBTUEcCmnOWqWwdlw0lIa3RKju/GejWbPlNNv/H6bnDmT9Ctc6X2Q==
*/