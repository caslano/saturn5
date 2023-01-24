
#ifndef BOOST_CONTRACT_DETAIL_CONFIG_HPP_
#define BOOST_CONTRACT_DETAIL_CONFIG_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/preprocessor/cat.hpp>

// Turn off BOOST_ASSERT(...) in lib's implementation (always on by default).
// BOOST_CONTRACT_DETAIL_NDEBUG

#ifndef BOOST_CONTRACT_DETAIL_NAME_INFIX
    // Do not use underscore "_" to avoid generating reserved names with "__".
    #define BOOST_CONTRACT_DETAIL_NAME_INFIX X
#endif

#ifndef BOOST_CONTRACT_DETAIL_NAME_PREFIX
    #define BOOST_CONTRACT_DETAIL_NAME_PREFIX \
        BOOST_PP_CAT(boost_contract_detail, BOOST_CONTRACT_DETAIL_NAME_INFIX)
#endif

#endif // #include guard


/* config.hpp
wo6uRFuQd2PHn7k+2JqUbgi5rjpbTZuVtpwb08xhrWYiDF3jqhQgf8JwfbikeWPp9kze4FaHpCExYcvNiqn03LJqDJWVB3T9dCjMN4U6pfbTj1E/YnQdlGDvc3tXf5z+zeHDjyvGepeT7+VuWA6kJ38SqO8ldob8Sant2fDlJs7N7VqXdgmvrR+xtliknujZKzd6Mno64rH9Bp2tUzodcYdsehlHH+mEaKbYje832lt2dD+Te/VAsD9du5Zun0yyAtF5o4vN3NZ7OZ2OvI17s4PY6JKpKeVJuQIPOoeFwOfJsnQeZksbN9kPblV/wGOT/mG9pXOftt5YXI82IUbdQ7F/5y6hY3PbWMzKrw+QVThZ+daYeqVQY30WWXnPcXb32xtAxkyScB0V79ixmSKxQr1d7mbVw6RH2FeuhDg5VXNOcBNmGJ5g9jlaKUfimbqZbr/6izHbWy7HUrd7x3g3sKjEfhKndzYgvxefSSs+N90Vf929JH2tA+/8aHGY/rIwrMdsExVmad1ke2nLQGZniAuNZC3Hka1uJGEtdU+Ze1ViKkwueiWMhx69yfzWsSmau+9R50LuNGHn089HKitp0lhG9Z3Z3lk0NX9+btlcOblhzDOfKDzlWISgw/LK0KebjplubiS8Y+Zz71596Ciby2WnJHUhSFKwl56qrVhPWKWdbK6/1juJwyACFMocre2512ID5ONHLNjVymbM
*/