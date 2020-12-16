/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    noexcept.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP
#define BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP

#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_NOEXCEPT_DEDUCTION
#define BOOST_HOF_NOEXCEPT(...) noexcept(__VA_ARGS__)
#else
#define BOOST_HOF_NOEXCEPT(...)
#endif

#endif

/* noexcept.hpp
B1l4RHH2qIm9znFsXsfvFZ0vNn3v6mk+MXKMiUEGuwcqFBwqAIekXOOZtwILQuZox/aWaDNLt7wClCftGdTO5eienJfNN2B4Xytoy00/QHEViKMPFASu5PrI3noq6gtMM4Iu8Xk/BK+SwRHiAwpNN2bqd/34uDlDs4zNpIZXstvhuxxwNE1gazUFAKg8lTlanYEy0CdotT+46nQqJ6oz2tLWUTvK/LltZR6mMh+2vX86lXv1ZM+2tFXInsbbBr9PbCjz17b3bw+V+6xtsNhEZVwH2zAmvWynraYNbeiD698AzFrrZTxb3rrxzmZUTNSM0Y6ozQQb3EuxCSsHnskT18jzeM2fmzjCf9yH9z92OTC2l3BKKStL/VtWURqZwVcVDiWWgS+rdbUs8qnwu6+MMOzjfqpATbLppsERt0T0DZ39LtrnKheMqpBFhPCH4Tc32PKiz1BD1Vhof8Zfia8WdEqr/oYNfzvAjg3+hl8ONdn14fgKrioYGAyW1N1oX99Z7D1PysqibBi5pHSlX2y9QNpQKrPnRSNTC8YEM0uecSB9XzJ8SaKIMoKuIUfkEtTXv4SSVnIS4mRqsWH63C+myfo2eOwedLNmPnGEP3cEC0vEJNWB4KXacLsa3pLI5dpFcaFcrTOxRPpqGfSnl9HNyNwS4TTLe7QCs8TiwBKs10OXSMXPySpeer7s/X6UFWOYGPlbRXNTeCDXTby2LZncZ218QmkXSpNVaaT8izDH039KlJn6y8+XDBDYVQWOf8PJ91gR5gRScvINVs2HEMgm/6J8KX6INaXVnUeGa/5QYNyPrbBzxdeVlO87NZ8lk9NBwBwVPg6yEZ+fMdKRfYWravXIqC1on46O2QnMPj8D+x4Xa1bh2YpcEIVL8+yj5RHtPhAG0CS5ZndZPdn7Puub9fT9GXOW/tAUBhxxPWp39h4926oeKfyG8zZi3ClKS0lScbemcEMtVKL81ay9LJ4/4KZhZbEeDTCR62D8Lc6XTB0a9Hn1buJ3aUqSrJCNZEW6iGWdVdQgpoMa3cn1yoecSJOdYR6AG5RyFpuRzoszeABMP89F7Dl7ZdGODu0q3zdrxzR/3yj/YoobuOs4LVs3L9u3MoxlO7pj3LIdzbW4W8LllP77UPLtn3ekpER7FGGa7lq8icU81G/weYPO+SDIEuIvfjvKfPlv9sEC80jC7EE8ejlFsnbJqkgwk+yajUoOpoNIzOeZGJpkiu6BHrx1lGnvkB5GfvFsb44Iw4ZeGyi/9RUresW/D+NJKQFpj6rxEqZUg8vQ/Z27aRVkNvNfPS632frJ9Lewbh7qpIYx7jlj3YxMVVEDn2N4vq5ogJl+dlnhE6KjYtNAsuenQ3ioQMTVSvrsMnMl8bmCqKbLzmUZSfvSy4bEjyeLidq5oOQHhpTKISnSXNf57MgqC+2t4vayG33aT5OMk7tU7BtmPs/SqneRXOHepBMAzPo+RYmwcTNsNpmAuPUZAza9OqqoRc8QbChv0l48Yq6mA/V51ZQvfEK809Ow5I47cEz+B8ERItze8L+cU5c6pJiVRkvEvR0Ujbo7zC2GG9UA6ofKAWivm5WKO1ElHtiDeRMgH6mzYMjIvQG5/wkWm/l6iV859B6nvnYRNwMSpoFWkH2FrUNcBGRmWzyvYRCgh6GLggN3LR6MfyExlPepMfbk3U2z4dgQjuGm92f9emCceF7daVdCpEAUDqsrGWkiclnsud7Tj6w39DJlb8uMtrQ3VQm/8EDkBLmWc4Vu+SgvayWVNPZhrhKW/BF2dptWXUro2EhaXVfGeCybDpJn3iJnWs0IRIZO9AheSEcS/g+g/2BVzMweSMSEdGimbkq1k6sRCAY=
*/