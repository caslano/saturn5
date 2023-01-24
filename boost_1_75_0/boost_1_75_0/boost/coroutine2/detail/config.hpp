
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_CONFIG_H
#define BOOST_COROUTINES2_DETAIL_CONFIG_H

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_COROUTINES2_DECL
# undef BOOST_COROUTINES2_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES2_DYN_LINK) ) && ! defined(BOOST_COROUTINES2_STATIC_LINK)
# if defined(BOOST_COROUTINES2_SOURCE)
#  define BOOST_COROUTINES2_DECL BOOST_SYMBOL_EXPORT
# else
#  define BOOST_COROUTINES2_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_COROUTINES2_DECL)
# define BOOST_COROUTINES2_DECL
#endif

#endif // BOOST_COROUTINES2_DETAIL_CONFIG_H

/* config.hpp
N1Lozi9qhKVnTToN+gMIcBS3+d7yuyX3whJ7BxE12DhOPT+MUpziJd/uGEVdSJlfAAmYTM043p0cj2paHOrH14xpWtq8cxVoSvceurJtOqjnXItUFk2+Chi6u5Ed/GIQbu8w4Euymy78nogOes86MSeWlB5eczcrmbSFVqHzZstRxq4xHPCB1HPWoH0j87gE+peuUIA6J9ztywtEO7RLMER394gdup95ww0XhgMOT59yL8XIps+janGDDQf+wHn7jpxSaEpuOMMlvtK5+WfUPpMpsg57n8xr6tE16f7o2ZvnPo5seN1zx3rPz8yu04D1HJJvMCWDL9Rym29YSXzat4DdrsJFLhwu9qV6AaBTsKSYFbBk1VEpp5BlRTwuK/sjV6jy3YzytXHa+KCERGp9hMXr+NH5yNBdH35tLmKlwQe4PUmViXgututJ82FdivThUK95L1mvRS/595xm9GYyNBcDG0iztMVUWUl6THS6bormKG2g4dtzUYo+gXdyVtKPRYW5H79u2XzHterEc1jko0Qo7kAeBI7jF5jDHwTo1ND4ZH6+/vjdtqpSMa/3J3Ap0t2k4AIjU+b9w+Dkl3WtHTLqkHneXgNzeRaaRMQSesaQRR0uDK7Qp9C7QWUi+ykpUKPQaEye4NAtWYebiv/35+82dXJ2vWAt5h7r/XetpWh8whTv3qSs8w4GtFGIuAwZJXFmNYkJvpzgwpwY
*/