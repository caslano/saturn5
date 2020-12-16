//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_RFC6455_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_RFC6455_HPP

#include <boost/beast/http/fields.hpp>
#include <boost/beast/http/rfc7230.hpp>

namespace boost {
namespace beast {
namespace websocket {

template<class Allocator>
bool
is_upgrade(http::header<true,
    http::basic_fields<Allocator>> const& req)
{
    if(req.version() < 11)
        return false;
    if(req.method() != http::verb::get)
        return false;
    if(! http::token_list{req[http::field::connection]}.exists("upgrade"))
        return false;
    if(! http::token_list{req[http::field::upgrade]}.exists("websocket"))
        return false;
    return true;
}

} // websocket
} // beast
} // boost

#endif

/* rfc6455.hpp
eWi4kcxtxoQ/t8iUl9GwMLk2VkunZ1TP9TByPKV1o55PcwaCkelhNfpDe5Q1f0mjnvNp8tekW66nuORvamT+yj7lKyRN5Gdi1b7t4zyfv/Pf2HFep1B98/nO6wuqbz7/Z1kv8PnC4gsOW/PA2HYNXr7q1eteudd9nt95/YXb/H/17RN3Xley8/u1ndehuH0TyXV9iqxT2GLeVfpu9pWV45XQ/mZKG9gbdob9YC/YHw6CyfBwOABOgYfAmfBQWAIHwWPhYLgeDoEb4HC4GY6ED8BR8DN4GPwSToA+H/Uf7gYPh/XhaBgHx8BmcBI8CE6Gg+CRcAicAg+H02AJzIDHw0x4IjwKng5z4LVwJtwMZ8O7YAF8BxbCD2ER3J3yKIYxcC7sDOfBUXA+HA1LYAY8Bs6DC+EauAiuhUvgpfB4eB08ET4KT4Kvw5PhO/AU+AlcDr+Gp8LdKJ/TYF14Otwu+SptWcSe8JrwQIc91wmwHewP28Nk2BkOg500vcw77XBuijmL//bc1O/snQl4FsUZgHf/HIQkakg4wyE3Qa5wB1CI3KeEQ0FAk0ACiUASk3CKCoIWK1qsYimiolJFpRUrttp6oFLB1iq2alVs1bZWa61a1Kqt2r7/l28nu5vdJAja48nq8GZ2vpl/7p17vqL5qf/2e10C56iO0/xU2P0uKVzcmrW3YU6q4Wl45PnP9/8XF8jx/8e+97+L6+y/ldr//6fNt0e5sxt/LHPOLhqfO2n02NzZQ3IHsQbStW9VujDaz3fkJ5q17xNFf499vhWv/UK149qjMcnYG2HW6Y8Q/YP2Ov5NNPsK5kifOAPxqWK+25Y+hWMfX2/mjlJnj/8OedfB9Cmxb/YWTDN2Bpg+5gDRH7AvJyWxY/bRlCwsNX3xmSJzu52qYxWniv4n9kx+171nBrfNPhigYTfu4Y/qPnFfkf25fZUVqd5L43MjQe9VfSU16sbSAulT63rzcSK3lx2pCcZ+ls9+Cu9M3xr7eMCMPbwqcgl2NJ6XudbwN+evt8UsTu52L9IxELNPR/PBljRxUwZHnD0T14i9fPsEjX8dH1lu6Tr6znCeyNwkbj/dUtyQAQhnH2A/+n1JsGkTyhX9oC7wZJdaEn2nbES8NG9S1T/cYwU+5l7YtZB7YaVv/uvl3r75a2bfDHlU+4hvwU5ix5Vvef++WeM+R+x+onLozdp2HFcZSXdxj7RUOZMXzB21pC/vNX11H0+R7qEtd/VviS/eSXyZvmiWHda3DO/j9amMvv/b70568vJN99zd8dmECeu+tXBcWF8rrM8W1nc9fn2zoz2L6mjP5Doie/20zGj9lwlboPa7zm/qDtvC9fBkeA1sD3do3+pJ2BG+BLvAqGM9YBbsBWfAPnAR7AcvggPgOjgQrodd4CY4GN4Iu8IdcAj8ARwGH4anwl/AbPhrOBIehqPgh7AdTIZBdzkelLa/t93/Dkrb+npHY802/Uxty38C3e31Xag9Zu2YtMdr3KuYjdJ2N21pbxta28/+trNpL+egtH0cdNehtn1D27q0aVEN7diGp+FpeBqehqfhaXiO8/N19P9zmfotqTz2/n+6ldwkI3p2GAP7Mdb4MbNzR08YN2HmDLwuYwMnt7PMmRif6Z4Z+ifMtaJH7erGWPT5OjaQmzN1whkzc+eX9JON3Bibfdu2zhnr+IDaOdnMMV8s+vdc59zMd48LqHwPMy5whegr2VWepO84vac8+m4UoW/p7ClHL14xfdyNYu93os8x7magd52l5JyDZMw7mj3dl4j+beO+2Zuv/vqbmOMrYnMYPgn0m38eXvvKB8TuFu+8uZ7v4MzV3yQyj1ld6RMnWKSbzk3/XM+Pm0s=
*/