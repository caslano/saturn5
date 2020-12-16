// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_ASYNC_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_ASYNC_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/handle_info.hpp>
#include <boost/winapi/error_codes.hpp>

#include <boost/asio/write.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/async_handler.hpp>
#include <boost/process/detail/windows/asio_fwd.hpp>
#include <boost/process/async_pipe.hpp>
#include <memory>
#include <future>

namespace boost { namespace process { namespace detail { namespace windows {


template<typename Buffer>
struct async_in_buffer : ::boost::process::detail::windows::handler_base_ext,
                         ::boost::process::detail::windows::require_io_context,
                         ::boost::process::detail::uses_handles
{
    Buffer & buf;

    std::shared_ptr<std::promise<void>> promise;
    async_in_buffer operator>(std::future<void> & fut)
    {
        promise = std::make_shared<std::promise<void>>();
        fut = promise->get_future(); return std::move(*this);
    }

    std::shared_ptr<boost::process::async_pipe> pipe;

    ::boost::winapi::HANDLE_ get_used_handles() const
    {
        return std::move(*pipe).source().native_handle();
    }

    async_in_buffer(Buffer & buf) : buf(buf)
    {
    }
    template <typename Executor>
    inline void on_success(Executor&)
    {
        auto pipe_ = this->pipe;

        if (this->promise)
        {
            auto promise_ = this->promise;

            boost::asio::async_write(*pipe_, buf,
                [promise_](const boost::system::error_code & ec, std::size_t)
                {
                    if (ec && (ec.value() != ::boost::winapi::ERROR_BROKEN_PIPE_))
                    {
                        std::error_code e(ec.value(), std::system_category());
                        promise_->set_exception(std::make_exception_ptr(process_error(e)));
                    }
                    promise_->set_value();
                });
        }
        else
            boost::asio::async_write(*pipe_, buf,
                [pipe_](const boost::system::error_code&, std::size_t){});

        std::move(*pipe_).source().close();


        this->pipe = nullptr;
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        ::boost::winapi::CloseHandle(pipe->native_source());
    }

    template <typename WindowsExecutor>
    void on_setup(WindowsExecutor &exec)
    {
        if (!pipe)
            pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));

        ::boost::winapi::HANDLE_ source_handle = std::move(*pipe).source().native_handle();

        boost::winapi::SetHandleInformation(source_handle,
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);

        exec.startup_info.hStdInput = source_handle;
        exec.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        exec.inherit_handles = true;
    }
};


}}}}

#endif

/* async_in.hpp
Ztzw3AnDc8aNzje0/7IIaWse6QO+svJHDCuYoH0IXIOOdfxYv7M3g7gHpPzd3iBfd/rbdvPQSdFxQ5nHC4oKi0aMZVv7p/xS8rjWG6nXyKdo/4j5Ehce3i9snHGY/l3gjdM2CxW3EccMUEb5n+tJXg7/MeH21aezzAmjx40bNbHQ6kutk+jEaRuUjZJPlJ3tgvbPtlrqccBr6rA/80cM5fGI9g16q+hscM00TjnnulL0NwXXbRU7BeZu//iYTX7rRPcFb7BfNesa/nzROek94Lzf/TeOeVt7innSrkTDafFp95Kk70PKutrPxutSvyHOiczcDmcnbdtRKOl7kndVowXlVQtx/H9A2mXYz6x2ldU+t1pI2ieNbEofYESLHUB/2n1UyqrjGk9ZtnYbaj+ulLYf8g6l7VpP+zA07XIMya8/54x4bZezXsrGx60qc4Pk9Zy3sXu88aT7qCPBYhejRrTslynoOuR4GGXZL0Ny83mdX87P6PRG57TkN937At+sXIWPzHQ8EQbZluixNlTqEnlBn5ajXyobdaTcQvIslDzPy1wwJlGOAa6UzHPMfOnz9tr2ZaXk04t8dVuYOyYW8kVEfXyuId+dku8f/fO7366FTjT9tj4g+T7qyGQ8TGRF5ztjvX8f6v38oyvOWCf72Ncn1SznsMAcMVDZh7zr9/eIu9ICPd7qSB5OR55xxwV1D/gEnSx1/Jo6WucpaYP4xHlU4p8K+f3M0Tbfz4xVPuv2Sdr1XrOfRudOCOqnu9Db5j+He61jQ50tRacYHY+MjWHoqHmKPp/sN+fR7W3hH9+OMdKPyPTxf4VrFg+jU51XW2yB8gtGF+fq43266J0wakpaZDptlms9x0stZ7akrSrjwz8o09SYfFL0urgWofeGY6Exxek1Pne65BjDRkWff6x1rfUUaahTddIE6npC8ol1dUJ+wsE5XfsdGattobY97dO5hlGM7ZMq35+uimsEeZlz0Ug9fndJmqtDlSPtik3Wfi9lv24n32z8nvVi+4c4O/uW0OHpYL9mFp9mcYl+Px/dCVmEW5H9geBJYX5kjfllwofovALDkLnitR8TSfszjIcMKijxwnC2j6l8roURcDJ8l7DUn56ATOlEpph/R8nf/hCdIrYkejsmhRAki01RPs6Cvr15CzuoDHHzYcAmJ17V707+TlA+zrba2uhIt7D/2oj9ImcDba9jbDftdaY/EbCbaaZtaYZpWVPtm2uQKdN2Pd1NmbbraWfKtF1PI1Om7XqqapnpFy3BlGlbH8OUNdF2Qo9f6BftpJaZftGWaZnpF+1VU6bbsceU6XY8bsp0O+4xZbodC02ZbsdMU6bbMcGU6XaMMWW6zjnIgv2iDTBlun5XmDJdv8amTNfl2ScutJ964Im/3w5qeAg7qGu0XzN9zSnyeVrfvJZELueZaiLX5x+Rj7b/HqjMS1UTkau5MlbJJprfapc5hnmHbZl3LHZYv/07kv8uvzv29lmh7ZswGESeftFny/98U+6Qn74PS8x/eMG0325n9Fvttn6rf51/lx1WqR8dscMSW6eeHvUMQz1TOQo3EDoi5ye2M9Vge9gApsNGsANsCTPgJfBy2B72ha/BfvAE7A+/gHkwjEIKYBQcBpPgcFgejoSpcDSsDMfCOnAcvAiOh43hBNgUToSXwkkwHU6BXeFU2ANeB/vD6+EgOA0OgTfAUXAG/xXCmXAinAWnwdnwRjgH3gLnwoXwFngXXADXwtvhRrgIPgSXwG3wDrgLLoUH4DJ4GK6A78GV8CS8G56Gq+AZuAb+CNfCn+E6GO1k3RvGwvWwItwAU+FGWBNugrXhg7AB/CO8FG6GbeHDsA/sB4fAx+E=
*/