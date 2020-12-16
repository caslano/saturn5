// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_ON_EXIT_HPP_
#define BOOST_PROCESS_DETAIL_ON_EXIT_HPP_

#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/on_exit.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/on_exit.hpp>
#endif

#include <future>
#include <memory>

namespace boost { namespace process { namespace detail {

inline std::function<void(int, const std::error_code &)> on_exit_from_future(std::future<int> &f)
{
    std::shared_ptr<std::promise<int>> promise = std::make_shared<std::promise<int>>();
    f = promise->get_future();
    return [promise](int code, const std::error_code & ec)
            {
                if (ec)
                    promise->set_exception(
                        std::make_exception_ptr(process_error(ec, "on_exit failed with error"))
                        );
                else
                    promise->set_value(code);
            };
}


struct on_exit_
{
    api::on_exit_ operator= (const std::function<void(int, const std::error_code&)> & f) const {return f;}
    api::on_exit_ operator()(const std::function<void(int, const std::error_code&)> & f) const {return f;}

    api::on_exit_ operator= (std::future<int> &f) const {return on_exit_from_future(f);}
    api::on_exit_ operator()(std::future<int> &f) const {return on_exit_from_future(f);}
};

}

constexpr static ::boost::process::detail::on_exit_ on_exit{};


}}
#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ON_EXIT_HPP_ */

/* on_exit.hpp
++AH8BH4EVwGj8D18GP4IvwMfgs/hzpl+gsYA7+CyfB7WBmeho3gGdgG/gh7wfNwODwLR8Kf4BT4M5wJL8A58CKcDzWd8MAi8BWowy3QBffBEPgRDIefwEj4DawEL8DK0E29UhRGwCjog8VgSRgNy8EYWBfGwmthHGwGS8I+sBQcDsvC0bA0vAmWh3lQ9teA1eBCWB0uhTXgclgTroa14fMwFW6EdeBrsC48BOvBL6DstwEbwDMhvz/HQfYYyAvMczgPfWwWkYrpisnATMekorNoxtX5DVfnN1yd33B1fsN/5/yGY7Y5DqtnXJ3jcPXv6t/Vv6t/V/+u/v03/f1rx/8zx/8zxv/j6eueEkdb4mV/NxeOcp5V9gg5O1/GMrwiHz4sN32UjJMnOcwVSHKYK5DkMFcgyXmuAHLnuQJJznMFRB5qrMu3dK15AYjtumEi796uv003XGRtenRv36mDPRwR9vX+NjciVbjt7nqNMNvsRwXvI6DkxUw5+jY3okXeu1X3tpZunLEfArDcgMFzEZQ8IXivBCUvYc1xMHWTDN3WPfq0s7mRHNBt1a0dtMnLBMJyXevO7drYw51izpWwZOVF1rbVwD74o2QVAvbbYQhfK4ZdrHsV5R5OtOveh0kTfexhrxyIa1s1twKZ89wKt4/+XHXm92Nhaq93msQtFFOSMY/L3IphGRlpbbun8dBkpuca51Qy3sW97MC4Podh3yi6n+jG2F8LuU6V+yGa4VZ1l22OBbKC8yZ025yIM7g5Ue4f1o2zKtvL9dN6G20o/iDjap7IYsROmIM/YXZ/zLPuMzJH2PY6uEHun9Q/VOclex3c8TqGd9KwMTdZ532PkPuf6wdUeKId3FGyoHMy1Zmo2PE52PE520kbm5VtjrX3k/s/6se1YuJOooM7yJzdGTbFHDfuLvd/00+i4Xcn2cEdJTPP3Ssn7qSPkhXqKh4pDvZSHP0fSyIG7FRwsFPBwY41N0bt97HMfzdMXVPqlnLNUxw8v0P2vZV7a7Um3J+q1RE3N8Vr2B5+U6BMtKGrLvDnE91kLUlkAWlPkf2AXmnceCFw/i1l1X/G6Cg337yhlG0S0j1jXmSVyBGRrUNd3pgwrxsvNOPMP8ZY5SzRWlxHqOtEArcYLsFwbf72+LiG24kou0FIfA4N4J9Q9W5RaTBO0ug2PYmdh/3jtN4Qh3Fax/MEPTFdJP2i/Wu+63M7WNbIGHeUdJaB9oBO4PnUJjIng2BZ55xSN8hYnjHGKOOD6tk2zjdtIzrqOUQWberJMxV0vqk8HyJLNGWq/CNLtssoy/HIUrguJzKzXIpuBUNXlTtkkn+UAWRSBmQM8rtA3LRR0YHri+q6crI681rVnUOLavLndmFfsSo6PZeZdeew3NwJWcNvys1UVaiUuUNSD9FuwI6qI5Udl1n2LZlzHRnmYEfJHOo7a++NDLn/nf4O2jN1t7aLWU3HMVL3ObipZE51n7m3SJbc/0rfSQvhVjrud3Be6scYqQcd3FSywutBBztK5lgPllb1YJrcP60f0oqwRzJ7NxKWrzFSJzq4qWSOdWJpVScOkvvn9KP8O1/njYTJx0j96OBmQPbH9WOwPUMWfF58kqq7piznDiMokaTEIOqvuVpnrZpRf4UMdSprla+5Zmhd/qFgF6zbEsStsgXqtjYiC9NLaAm0A3bIucnLKVAvRRp12sA/rNMacu39gzot1GfMM7m8uu06SZP79fpad6nbtMLnoEi91PsJW312qayxUZ+dWF6wPstZZq/PrHkTh6Sukmf1v7BO80r+R8v3hlV/nVpWsP7Slxesv+qq+qun/Bs4byoKVoI10Rkq6ZXHblvj0vwzQbjlUG8=
*/