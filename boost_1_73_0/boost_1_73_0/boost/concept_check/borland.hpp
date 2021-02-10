// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

namespace boost {

template <class ModelFn>
struct concept_check;

template <class Model>
struct concept_check<void(*)(Model)>
{
    enum { instantiate = sizeof((((Model*)0)->~Model()), 3) };
};

#  define BOOST_CONCEPT_ASSERT( ModelInParens )                     \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =               \
         boost::concept_check<void(*)ModelInParens>::instantiate    \
  }

} // namespace boost::concept_checking

#endif // BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

/* borland.hpp
SwMECgAAAAgALWdKUgiYg0MVBAAA4QgAADUACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMSU5GT19DT05ORUNUX1RJTUUuM1VUBQABtkgkYK1UYW+bSBD9zq8YcbqTHVHctD1d0ybVUYdeUBywDG7OkiW0hiXsac3S3SWOdel/v1nA9fliXfOhRA4wzJuZffNm3KUNJz/sslwTDr57pe0vxQvvO9BUir9opo8D0vQRuj8ELvH+jFQj2KMe0yE8C/UIgxaV9rnOzXOaPiPd0hRp/o0MeJmaR7R0yB4/FvVWsrtSw2A8hNOzs7fwAl69PD1z4JJUjHKINa1WVN45cJ63lt9L8vDgKvrBAaqBcPcgYFIyBUoUekMkBXzmLKOVojkQBTlVmWQrfGEV6JJCwTiFcTRdBOEfDmxKlpV9nK1oQJWi4TmU5J6CpBll912YmkgNosAIGD9nSmPMRjNRuZiegqZyrfowpgjClQByTxgnK0xHNJRa1+rdaJQ1kuNJRrnI1CjbUeGWev2fUy2wmjXZgqg1aAGNog4YfwfWImeFuSNFaKybFWeqdPZlYcIqHwkJinLeh0Moo6o7AoW4Z8sxnlBj9UybmxKVMtk2pVgfOCKtfaCikRWmQ1rQLxdIvANN
*/