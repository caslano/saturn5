// Copyright (c) 2017 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_SIGCHLD_SERVICE_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_SIGCHLD_SERVICE_HPP_

#include <boost/asio/dispatch.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/strand.hpp>
#include <boost/optional.hpp>
#include <signal.h>
#include <functional>
#include <sys/wait.h>

namespace boost { namespace process { namespace detail { namespace posix {

class sigchld_service : public boost::asio::detail::service_base<sigchld_service>
{
    boost::asio::strand<boost::asio::io_context::executor_type> _strand{get_io_context().get_executor()};
    boost::asio::signal_set _signal_set{get_io_context(), SIGCHLD};

    std::vector<std::pair<::pid_t, std::function<void(int, std::error_code)>>> _receivers;
    inline void _handle_signal(const boost::system::error_code & ec);
public:
    sigchld_service(boost::asio::io_context & io_context)
        : boost::asio::detail::service_base<sigchld_service>(io_context)
    {
    }

    template <typename SignalHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(SignalHandler,
        void (int, std::error_code))
    async_wait(::pid_t pid, SignalHandler && handler)
    {
        boost::asio::async_completion<
        SignalHandler, void(boost::system::error_code)> init{handler};

        auto & h = init.completion_handler;
        boost::asio::dispatch(
                _strand,
                [this, pid, h]
                {
                    //check if the child actually is running first
                    int status;
                    auto pid_res = ::waitpid(pid, &status, WNOHANG);
                    if (pid_res < 0)
                    {
                        auto ec = get_last_error();
                        boost::asio::post(
                                _strand,
                                [pid_res, ec, h]
                                {
                                    h(pid_res, ec);
                                });
                    }
                    else if ((pid_res == pid) && (WIFEXITED(status) || WIFSIGNALED(status)))
                        boost::asio::post(
                                _strand,
                                [status, h]
                                {
                                    h(status, {}); //successfully exited already
                                });
                    else //still running
                    {
                        if (_receivers.empty())
                            _signal_set.async_wait(
                                    [this](const boost::system::error_code &ec, int)
                                    {
                                        boost::asio::dispatch(_strand, [this, ec]{this->_handle_signal(ec);});
                                    });
                        _receivers.emplace_back(pid, h);
                    }
                });

        return init.result.get();
    }
    void shutdown() override
    {
        _receivers.clear();
    }

    void cancel()
    {
        _signal_set.cancel();
    }
    void cancel(boost::system::error_code & ec)
    {
        _signal_set.cancel(ec);
    }
};


void sigchld_service::_handle_signal(const boost::system::error_code & ec)
{
    std::error_code ec_{ec.value(), std::system_category()};

    if (ec_)
    {
        for (auto & r : _receivers)
            r.second(-1, ec_);
        return;
    }

    for (auto & r : _receivers) {
        int status;
        int pid = ::waitpid(r.first, &status, WNOHANG);
        if (pid < 0) {
            // error (eg: the process no longer exists)
            r.second(-1, get_last_error());
            r.first = 0; // mark for deletion
        } else if (pid == r.first) {
            r.second(status, ec_);
            r.first = 0; // mark for deletion
        }
        // otherwise the process is still around
    }

    _receivers.erase(std::remove_if(_receivers.begin(), _receivers.end(),
            [](const std::pair<::pid_t, std::function<void(int, std::error_code)>> & p)
            {
                return p.first == 0;
            }),
            _receivers.end());

    if (!_receivers.empty())
    {
        _signal_set.async_wait(
            [this](const boost::system::error_code & ec, int)
            {
                boost::asio::post(_strand, [this, ec]{this->_handle_signal(ec);});
            });
    }
}


}
}
}
}




#endif

/* sigchld_service.hpp
36LT2d84wQ8f+VU4VrworAIxnL+1XQaGYgK9Wsq9FIju5YD9Nb83jlxqpLnrynG8SfdpzFuEg+4z2j9XQ/XkJaEZFXR7bDXTOlnr2YFwF5urdbrB6mqFDe06ZHP9PC2VFf5sbcSIk9MNrNFaeJJVYIG2r01D97Ca002uK6sdgea+jkB1r9MHrqy+oRQnt7qvrXF6JqqrY1fDK8/gAIafdtgap9FLo/qnTRM2mEZsMY2oNll2nTCNbDxhGgV/HzOvbTboTrhNfY+Hr4fGynZnRrtX+wx1r5NCMfZ+q3AF+d6zz6Z/4vR5E48kk4gtLXTZ1OxxMH32BLrsDMjK/YPb89VJvybmq8WCXLoMOITA+ST/E4H1tHYIsMqOluzm2jHABA6Wc4WF9eLdQr8KwMy68m7azNyAa3n5r/TC+XLnG+XYCSzDQRY1yDmcG2Noe1cWNGxKFXoarzHOPx8aQARnCfXeASh5zSI7dGxZ9XHYtQFLqk635phd+sgUYYvhLF9zXIbNFGElaFs4W4a9IMLQmemachlWJMIKgM1b0yLDnCIMXQSvmSrDckSYzghhR2XYVSIM4ZXWTJFhRhHWhOl+kWEn11PYCiDUa16TYc0iXVXnmPJKaiisunNM3qdEWH3nmP6+/SWFbesc7W90UEOnvjiu3b/hFp58Ji0ig9BAKk2dyYAZpvEhYWItVFv5dsmlbX/KQBhPWR7l6mcPIT/JMAtxhIQ+xebRdzBtSDXGvtWvFx1OvHXLSTXCyq0/TNKfPaLzktrBAzz0Ga5NNi5VJ12BrxmEajRz2dOo8aauBgvUqsN4tW7b4DQ5q52KYdw05FIDjZ2FrcCT7sDixT1JxbW2FQ9AfGPHMDawVaWWjibzDZGBzWsVDf7T+jQdz6dmzuNU1G60pKKMmiU95jVSwU1U8OC2/dcSuu1AEPrAeI01ELumkL0apSXToXyMzyAp6u+QhNGEoRGvoWFnmtDNhZ48AJJT1Lberumex6E4ORFpcglsTjjkZtXgEuVfzUI7nP5PzkhHhgkfLweWniEGILBeNNeKK+Tir9iUCmp2YClFREmYEHN7jzVowz+Y9liF3YizoD5loPdq+NRATtlOftenwB4Fy89QBxZU0Z+0f04HWarpCyEEpge2qKp5zRMg6KzTCQOretX8p6dwaOhCs3QpmjLMvhw60TRAGPePxpns6WHlokCClR+34RQQKaW8SUw0CJeDnDBEgcX2XsJ3spiKTGzVHXSf2ai9LLDo6A2Ek6Wt+j4NfdR+9H2aTo6COg+lG/RlKc3r0u5O6azj14xpAb5MdDNYQSM8aaa4UhuHNlwTkdqWaDZcGu8wS7ThgGCMbRuAtv51ICoay1FO0tbNLbAW7LSQlsRMwJoHaa2/g4QwyLDG3N1cndGiBpbIedT4hQ5sIVr00sfZm9WdE5gXx7J186r+Y4oV/yFFkCEl43OHnyJoMCR/fJb8QBrMffKDxq5umPhAqsvXyA8ky/xj+YG0kl8oEB9IYHmL/CAX0/+SH6Qb+oo+NDOPoVVo5tGOj9oba6tQa29vqyCh+uKvdgpwpYzGG5ZAf/NU2kvTkogq5tHkmv4gXqRsdeC0zvxdB6ZUXd9KaErlYa8TXT92nzC+KeLvHTqq0u4ryJaHeAN/bzRM+plOvux4gQwtX4/RUtcsX3+g1Tm8I/bdE3xd7Ms/yn3pmgL70r76NJmcRrZmn5GwNcVDq7ltyHmTm/XL3U0+wEKjccM2SoyXBeMIRGRuc2dx7F/jZFSXRxTBzK8VaVqzesq4g+cQQo5Wg3ilsket5MntK3Yy5N7JXcSGEYIvoEdIozW3U3TXmMg2HyavAGkjjONZ2rz8D8uRLq5HOg5zeTxZ14a2ZSINMF9PjWwNbFdtm0yl23DFvT+6g7m9tTLR3NqBWlXHzq2db/5X3NzacW43jxJzez1ZTW0SVlGbcGofTY6d2vxkMbUxSWKtHA96xmxGm6WC2E6MeoI6QTS1FvveGd+DsXdbhV9p2yI82Oym+ZtMq/4o5tudqZqXPYb3la8L91AVjTSJ3bWTrBGxpI1CjaOvxDd4FdqU3wpT/ragXswceESb7gOjDDqJ11/RqE1qBr0ZKRfff6Sqgmk3VsGRuw9l1V9MpT9S9aIVSjk2lIBS3CITWzYRjnRM9yX26zZ8A8YQxlEW+XYRRJtWfaWavy4SY6D1JIn6UDnR2LZ3ZLy7L9K9SLfynGwTdWlFodalFNxDjDC8Fgbgf2zbtm3btm3b39i2bdu2bdu279zFkzTpqulp+p4uKovjAnFRaj0RYaojDfYqcIqrDpLNpeWjCFPVyy/Mh8LD7xpTGfGlVweCTpkjtD9dhtKa6vFW+PRfOdKvjt95GHea64cT+UOpy1gBf0TjkoIlnOAbjDiijQ8VJjWgKw8taxwWmzyAB1zirf/czZpNVJd/jEsbLONum3QTu2v+/A3CmnTM8mEQyEeG7GshzJemgQHrsRrRewG4KryB6y+KS7Sb73KElCWKw1k/ZMFuq35UA2ViigvI/CuViHwlOOGHHbIAYEpTwEyoH10J4a5nHVL7SZEYOopzFLa2dLgU9DxRhy4wyhxVHSRnCC/Su92twDvNU0tFgGxlMCHDD5yAc8Y0qsDT7ycR18av08btryM37bsUjkl7H6KxQMHU7SX5ZIqwRlyfe9Jx27+sCUUdNGanDoM7ZqCMCkcfSMBbtcIJbnWB6/eqk7IIBgIfaWiVTvmRq6jo/oV36jCHhkqvrqwYtr4xR6bB7MwFZ8l31n4mVkhTY4pUP61jPUMTQCm6ML4AEwQy2/i87bqnkWFufJk7VNlE4JmH258QLm1qI+ZvDzH6hoD8X5grLP0TFlndmw6QhEQ7bYhN45HUNpkw2pE4r2XrwO1/FXFkBPkWFQKjbsSF3T0AACz/0xp8KO20mCxN67ma0R8NkEaSxJ/CE74A5iQ50lzvPmv81Y8D9I8gQ1vPCA+UHdAIzV4jylbOnK9oy10vDNHCn7j39HsFqPLJAmpkHV/eiU2otz0yt64jrWXe9F+M1RtE5M9ywZizV7PqhZkAJLb+3zRAIOlwfK2s0Kdw2MzDck1lCDecCyzKPA+FergkdbX4qomqCWO9IN0H/kDu0w744BXvRNUJ6p5UtAtWHwj+FWFISeAXqoiqHGG4LRKwBxWEHGG2JggxeHw9TSIw+Rk5nx/x5VoDzQTCythK96qMooJTwaS8GkHITh0w7lYMNy4bbZWmaIgim6TOfROGKcAQqS4V72zwNlxMLkpH91Zf0inZD1j+KqlK00cZws01iv8G8+gFVo0uUbq+XsSCv1Z1OmfAezdVyYyCeKZ6exurZUuoIIi6yE8GmE5ihJh2Kp1UIF5+qeX88kSym3FbqSRHf3ZHnBFO/iOxXPbGYxarVpu45Lo8oqR9/0fr6esNj8futY2Ze+QHvEkf1SXYsbfnTg2k5RLnrreLU8Z+VOtDSEvtGd54jj/2+eWEUl6qTqgpUVfVdXMH+VPaaZ4ub+yrn6megZfY+I8SeVXnyvhoLYMkpFkb2ioh8Nqmc7l97YKPNlTztJa3/IF3FkHsv64fsrK/mCe2Af61YyXxMLwlxQyffUajjPoMiUUvGJJApxZW764fDzbN52teVNkoR9syJyog5vbuT+cQKJC+7TCM43yMG4Fn1B/oA8MFUnt68xyzvhYj8NkgT4/YDVznP6ga4vdVPgR9+OkS2oGg/q+YfsmkzcZjhYjG8smcPjmhvWKtFG6cqV/ln/v1zF6f8RnIV69OdRWZ6VDkXKgV6MjKbm6LA9IcMd1mj6m69ZILsohQTq7aiiSudRbZVlXdf7dg9iPY1kT1BbDfI6yrrMy5Z9IET27qMQdvF4qgo2h4Omv956i0MvZYqk034As1OF+1sZHDy4k5bIc26gizWtHE7W3kbpGqymQ3HYG2qVgbLk/7oc0xB9hDLsxwBdotiT9NHY7cFUNCxUgNl2ezWD/uIE7f+tY9xGOjVHg3eXxqpBexPts9AEu5OrHN17HZfFoi3/WjL6O5VB+HJlirPHHE+JbHO9/f9oEz98e+jJfrM2aWIKI1UNfcTAL+6/OARhMdkROWCSbb8XlVNpUbqcvOXgUNMdxBJjhxJvcFLybT0vIrWUEm3VImPjSTH04BDTfi8ik8BhpwPEXZS4/xpUG9TrKLjw/73L4Eo92qFNQDy7i5+oLOxbHx3oTyJ6VkTWVWmsUbz8Wn4b5Cd/Lgulq0snuBsRGwT2F8PmS+vsrRNr9Tm3nfBeUE+nweu6Gc6kaVpiTqRlQr39QvU29imzX1KFt3HDCrEWsXHbsrtrPgz7or9EJVpJSItkF3wIeohZCQT3B8YhkJfudHXj5Bqyc0rzkjAGJ4jBYw5pRbh7dlHuQ1r+TDN/RxlDwL+95BajBBjO2fNubUzpQKm5JQ0B1SLACSLl7+OO/0OcSRU4FQ9hTAM8TpqDZzxrHFdE1l4Qu6GLkpR0EUdHE61E9j3rsWLNziKQCN2zjRVyKUbwuRtdIIr7en51DFSG+c1D1Fqrd9jwc8kGMeQsHxIwYHbveq7qu9Si5fwUwbKPRTa0itA1HZGe+ASZlBdAwStAGKJwIUpYDoWQe9kpL68NwqysEJsN4y/2opLe45GG4KkK+L5dAhhPoQ3ZfLHp+NYmzr/tk2ckYNTHVvMJXgqldQu63fIKZusk4xXvuyORmD3FQv9ReosrEvXXhv1pRPI17w+UkXVlZ1DElTyLhQJBcdOKDjfFzctX5la8kbsN6moE7r/Qu1qYdh6tmaZa3aPNK+pC/0mrpJ6CS3g23H5tl2NnHJ49ColpP0YMIL9DqZnCgtBm6gGp+oSIHLM7xFGSZdgFgv5jyzUqeemo8YfefL06l11fkuo3Uh/d12XlM25np33rEpaQDhfJd/NEBOw3rL0dwSEK25zV/Nv2YB1Rvgx4CQV/sZWzGe5hTCs8sWkB+B8dasbhL89xtanYp2D5LaFmbmwlCHiwCh+7Ia8z0dTk7/qIHENer34MovopuRIu7FAjsNcdcixl+3txhKTWZ/JvDofyiqaBZ9yOZqQ3BKcli37qdJlslzk/ACRAThM4RrcUny5AKm/96/oOS/uHU9GxwSazG0CdrqTqHkWLzJOsQ4HQUf4X+1ztmqedhik/1hBG7j+tbtE965NZF6Y6fCgqLOaWPdqsCyu8dwhj6r0rwJpXsbflqZsfGo0hfBpYp0RsiLh1p7FyBTXeG9u9xH5V/eCsPc411to986rqYBhjkfe4SaeKcTYOMjY0Vl6gufcT9KIPjWJQX1Nghf/xl7bRVtEWNXlyn94ka0owPQHVlO+h+cp97WvXmlS4teqQ7KBVDgZLXqFipb360kw3WtTL6FXB6YZFNIEKK2gH92cNzrbvV5t9uvaozzr091xQu6tbJx0Srvf0TbESVChid3DAvy4Hpv/7lsC2cVB/732VzmAN9MPan8AbF+Cx2em9YYTlpCzskgctC8OO4ThsWKaDgnP8Fslmzqed9EJHfbiQcDPH16/uLRMbYcJnBJW1ZhJg20kYo872PmPYiLQ2zLFfnApVpvZYH1MCy986YinDGSvjmzO8xQ3ezDVe1XlmwLcN/utMnRxTph+IRoXL6/XLgxpdJLaVaDLxttuHrFhDg5bg5/5Q60W9Z23qv6iSXmvlNlnP35C7Dc5ayxK/j/TxGyu730kUxe+LJYJbDySADClQWibecbBKqRmxnycDLmwovkVeM7/u0FUNeMqbItU9pYuGnqe4MrKwDY5Z1FXPom6+jk581BzTnS5Sn2QVFOLIHTFNgAOPieZpmRSti13X6KJaSTzX475jxmnWbNGkD/PnI3zz4uvUSV8vqjo9RvT9JneAp4k2uKErWVZKEZDbZYRzprsYoTnlq0WI9PfKsdZOl78otJV7N4YMqj9u5+teiqFDrbfhBeiN9FFJZS61jTcW5/qgnffOcCqSpotGbs3pP9d+twaj4T1z00CIlIcKWY/8jjfn9xx9Mm5NsBXyspdt3bXNsfYMk8SEgTcP4z7cK87UM/hHLuzBDqobnKps7mm4scEToz6FZ8wXCxBhPeQa/a/DrBfCmwhKyAwzhixXoV07EIs9h/vpSjqGu9tHBKJTfIP9ktu/gLYphVsKS9AogEbEI1kUEwRt00eCQyyBjYbx52DyaC1JDky/zI4UC1cjTMDTtWsGHXFW3rGFdTBGtLsPP2TDCNnUMssu6E0cqcgxssxxAuhTWATEiIFxIhlRzZDnqHJB7OxgdP0Mduc1E0zMCJjEVFUD6G2m9dRpwXX2Jse6qHaHNaOwfjwmXtTrk/gU1sjnEzNKLJ+q8zAGil3J8TPRfV+EyOSPTRpA0Q3eKFNcZ68dfhVa2obYaDF1YyvmYjNSof6rqBEabPFXkFSZ2inF5DGlq6eFfgXQlcT2o9MCy9R4G0TEz/qcz9yyHx7D+aiXlbfRyx5DblyS2WEKumgUOaN/QWOv7Kf/JdTSGeMhtFLjvdxGafJIvYEJhCAq+Q4sE1AbLwSyYqzg29kr0+aEud1JqiHSJ6YlD6B9dvb3FKWLz/tQr5nXMbSNJYVP4+oxjmffGDJN5csPMNEmHfGRg9vjULVvGfUmUwtkIHtYf9I/DosRzuJ4ed5r6lqcOaE9aSXGlA9prhzyLoTNLTFYW4WMka3/90mlVyZIgvUexy9ImonVJDu9wgUM3byylFjyVUSDIJZsZB1zjv+fSmlthcuYviWmcDmX7sbRW2BhatjWWc8DrMuLEGpqdxGSP+dsQ7HefAHhnE9BSWBX0BdQDXVlJqzg2ZeVZf/UzkKbv3B2rP2RPzxhB8VmPlq9w054+e5n2u+M6WpsX9ui++sXb59UvK/s00GT0zgZu9qrIDMZL/AEJYNV+cvG0lADYsYEKZsav93iqQzER1OAR+sieK9jRgj5su+GS3lL1i5lSGwJrLZdFSzSPILqIUtOugGRj93QseMBzwjsOIwc3Fm7Q7Qs2x6w1jE8O1TUirMP5PD69DZVMxaZrZaU5vcbrr8MdHVuV5kk77ZzZ6AaJ/nmuqDC9iOn1qllOGAOo8gec7cPguk3s2tu8liddCwFOfRow34XtedT32w/2M/OJQNP8JSwjCFdgTNWXGDNRT4rS2NcVvmOUxDzLaVlbnRaHhty+T0cAZTvrdLNa5klb/Oy/LtPM5UB/hl2aUlmi5Ku97Eo86A1FAnmdYQFzdFOpulglT+NBfMhBocjusEzVHO28zp/Q08OmLmGfQ9o6ZB7tCusgSNsCy4kW41fXoNr421Gkm58Y9ocSrAgG8Uwwn2UPdbEmBALQYKrFPzZFtTLnpmnI1dQhT3AH4xbN4H7QGIcCoyvr9MhbhOa6dLV6AdhHaUY1nEMYx9deTUtLqSIvMplSLLKK/mUK9dwEPs2mcTtS1PYA4Pn30ehX5eKKy6bJ8eTBT5XjPh2cra6vAuq0WrHQ/8XetakDUZowevG2333I/IdcEnjb6YTes8jxnDFOzpjYf+1gwqyXEMandHPoR2zbjwdEH4lrpBnckde4KxRvi2Pz8n4EdIb2VBZSD/vuq2ob9Y7YTCBq6hogFp2zRkFAZLz4QV7u8EUoShE1bj3yEf/dvK1h8D+3sYWsH
*/