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
    boost::asio::io_context::strand _strand{get_io_context()};
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
                        h(-1, get_last_error());
                    else if ((pid_res == pid) && (WIFEXITED(status) || WIFSIGNALED(status)))
                        h(status, {}); //successfully exited already
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
4+AMmABnwvpwFrwezoZNYSK8ESbBnrAv7AMHwSx4DxwH+8HZsD9cBAfCZ1W6tTAdroMZMB8OUXqObPgxzINH4VDoon9HwHA4ElaHY2ADeCdsC8fC7nAC7APvgpOUnmS60n+sUnqOwxfwfvf6Efr9bvCd7v/5O13TnzjoS/xb3u0G3+sW773uf8qXuNeI4Pvc4BbcgltwC27BLbgFt+AW3IJbcAtuwe1/dftD9f942eDH97vo/++20f8jC9T/Iwv0/Q9DZq+Pz4njXbbSx09y8I/IfZuH0KES73OiHJRXkJiYnpmclI5bYkpaZmJOclJGv8RMqpqZkfNLa9RXQRdIPLrA6vDoLq86JLGDL1+n3MzspP6pyK3+kYvVa5Zm1KcWvBSeJKaP1GOcr0ft7QK0r/5kSRtt50tGOb+8Hv1YiS+jbQw2y/4ufMs62/mV6fLQUavzkal9lx+UuMnYJ9RFl1AxUNdvfitQ0s016nCUVLSHdmval4MvSrqd9FVnOV41SZMu9Tr1s0+PHE3FGNF5/fy+j8gvR48cYeqRJbxMmF0aPbHS+eaSL48wTOl2sWfXW5j5Z3PaxbGvExuFOOlHT8y06OKvX41eVepcTdKle9NIXak/+9RfjYvL1bjYq5wma6iKXEwYiV5slc9eJEeGJLJY+mCgnNfEG/P69UvNtl//QeVzWNPfLN66AedXpTPPvT43ibel5uSl87ceO7skrVu+YbjERR9woCfp4ygq6/9G4NA49e3BX75mtC/mQOkz1RYlD9NyXWfqcG3MG0qHNj3B1D3XcxWtG7bXARetQ7XXJRelWy1aZ1z+Kq/ctSkmpe+Quo8seuq5rj9X25FctM7YXsdctG548yivfMzWbHf7STEv/3jT/ApXe6ouL75utbg+gPa62KJ03v893bO9DrhonbS9rrdo24UvGnrl63et2XOmYstRrzTNfmtbwy33FaWTLr6twx/t63dC27PI9StOOmMYI8dEF63uiTBE2Xa44MUq/R0k97IP9MAkeAwW+O8V6t52FMYR1qp8F6n1vmvAa2BN2AzWgh3Ufnd4JewJG8IseBW8G14Np1u+uXcjfBA2h8/BOnCbku9Q8k9hY3hE6dKd1KsJrAAbwtrQm/5S2Byq9qs5UepK3xRu/4dhvvbvg17ZAVjb49P91iNMGun6RV1xx9VOdMW/XU+8uI0jqCu20RXn0y+2+uJLnP+Wzvgw5aZDd1tHkbrji9s6Llh/3I20WQR7HTKyto4/pQ45v63jP65HPtzW8X+pSw5rx/erCX6dctt2jv+4Xrm4OuX0do4L1itPIa1fr7yMvx9nTtxJ+HpkUMf8n97+2Of/jP5pGam/y/P/DJvnf2QBz//IAp7/SyiZU2TN9X6K7HeR9wPs274fGGlZf2+uWjvgZUKo+j2zgnxHz4mbNs3l8S9Rntssz9ayr5+lT0jaDbIeit0zGWXpZ3OenfgrJ21kqvn8e0bi1xjj7dd40fkj9DoxObZrvKh06nlcrRdk+XZYT4mtze+zkkYFnts8yBZQ3igKeAguUiHwGS7Kdl0/9dyr+0J9n8+NTNpnrq9Cnb2yQu9DCtR6O2kh2N8rnoxBLnUc5xth9u9D9HfPWjq8aQ948vHI3owt+8eO4S67/qdMe58I9V6lqZTThGHs1OfU40TGF+auN75RMnKJzO12G+dcdudJHee89xw1lb/E2xK71TMcj/xqzsrGTc7SPLPU4d1QjOMeTxjtIh0pVrpJh/VoRX4FDyK8g6d7rPqG30CpQwP3PUYa6c31/HJyE5OGJqWlJ2ZkpuWkmuvyHZNjNgph7KjrKtOopto9Rdr9iKc1I/923g1lGz8aY5gyFjg=
*/