//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_BIND_DEFAULT_EXECUTOR_HPP
#define BOOST_BEAST_CORE_DETAIL_BIND_DEFAULT_EXECUTOR_HPP

#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/handler_alloc_hook.hpp>
#include <boost/asio/handler_continuation_hook.hpp>
#include <boost/asio/handler_invoke_hook.hpp>
#include <boost/core/empty_value.hpp>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class Handler, class Executor>
class bind_default_executor_wrapper
    : private boost::empty_value<Executor>
{
    Handler h_;

public:
    template<class Handler_>
    bind_default_executor_wrapper(
        Handler_&& h,
        Executor const& ex)
        : boost::empty_value<Executor>(
            boost::empty_init_t{}, ex)
        , h_(std::forward<Handler_>(h))
    {
    }

    template<class... Args>
    void
    operator()(Args&&... args)
    {
        h_(std::forward<Args>(args)...);
    }

    using allocator_type =
        net::associated_allocator_t<Handler>;

    allocator_type
    get_allocator() const noexcept
    {
        return net::get_associated_allocator(h_);
    }

    using executor_type =
        net::associated_executor_t<Handler, Executor>;

    executor_type
    get_executor() const noexcept
    {
        return net::get_associated_executor(
            h_, this->get());
    }

    template<class Function>
    void
    asio_handler_invoke(Function&& f,
        bind_default_executor_wrapper* p)
    {
        net::dispatch(p->get_executor(), std::move(f));
    }

    friend
    void* asio_handler_allocate(
        std::size_t size, bind_default_executor_wrapper* p)
    {
        using net::asio_handler_allocate;
        return asio_handler_allocate(
            size, std::addressof(p->h_));
    }

    friend
    void asio_handler_deallocate(
        void* mem, std::size_t size,
            bind_default_executor_wrapper* p)
    {
        using net::asio_handler_deallocate;
        asio_handler_deallocate(mem, size,
            std::addressof(p->h_));
    }

    friend
    bool asio_handler_is_continuation(
        bind_default_executor_wrapper* p)
    {
        using net::asio_handler_is_continuation;
        return asio_handler_is_continuation(
            std::addressof(p->h_));
    }
};

template<class Executor, class Handler>
auto
bind_default_executor(Executor const& ex, Handler&& h) ->
    bind_default_executor_wrapper<
        typename std::decay<Handler>::type,
        Executor>
{
    return bind_default_executor_wrapper<
        typename std::decay<Handler>::type, 
            Executor>(std::forward<Handler>(h), ex);
}

} // detail
} // beast
} // boost

#endif

/* bind_default_executor.hpp
SPq96ZcifvMhEPHLEy6x4i6gPJzRZ7ypwidHCtzi0acKlOrHuNKC8XiTVReQN90v3fL5eQECWnICM4xhM3zDnjFgV5YhU8IVFBXlmY/eF5Y6SyBRczzKeMf4xevLGTjOLJ84oRssrnRZ45wYJE5y+sQ5kGGym8iGwfzKFcc8TBX+wvnls0pnw6rrPcfizioww8iaap07305necG8Yksd5vqlzdDWZDVvftN8+rPrdlnkTq9yUXmhzl+J143Z87bLMn+5CZeOV8vfKXzF5bNLoUXlp60s8nf5xePL6VuueMZZbY2zoqgC356um6UB4yNXgPzVWOMqWgRplxZa87cqcHzk9MmfjnO1NU5nQZF0AJY41waOk5yBy1xrjbOwwFlqaY/rA8RHLmtkuq43Cv/istKZ3rZ4j3Zr2gdt8otfuHTE7rNPqT2Uvuc/h8Pva7kWvABUZ04kZ/jcY1/gKq4udVH/+OsuCn7sRvV6MFDCFKle3vVgxhMj4dAPw5QXX2sGtazHTxGeXrQbKlXsLZTfXWr6/fUU8e+hHCaPuHnC2CSdb7qDiflTljvYughPrtJ7e5qx9hzHtWeUGWvPLLPFHWlpd1jlTfXeM7j+l+L7pkJDC/2Wrugv+gO3wmeTr6y1xjJOy6ywqqKCaVv2rvW9ygyXauErK6h0kc8i36EmH7iSsDcqF/WdgHwMQRuwXx5ZHN7KHib/hmOPVIcwfa5teSz0qd1Evyn7oeIZtgxh0xA2KqKPPS48OqpdmNL3Ti5DmDUgs95+JfnBN1JQpvP7JynnhRLfCIRpo9zx/6M91n86Y20GYb9EmrcDh5p7tOKViob970mozQ4g4DC4f97tzGftzHpIlXJL3fm83bCR+xJuREHbA5fYQUgrMddaD/L98E+hzx1fTlelli3DJGo9ZqbYi+0j8W+23ZD2uCjefT+ZyyV/5PX3Mlx4/2IM532sE3R855AHutBrpM0a44xw/+9Bvx2SKjyxKkbsvmGugJxjeQfrvA6np5I4N5YTA9GhriY2X+fHfSSQmfcuO8gDbloeul/bosdo2A0Db/83N1ZR5z+LfVW+cn8/tfk+9eYeAOaZ8aBfRLu9B/UdHck2n+LX5qPDosI6sA3rdu9u83EMmx/pbvORbc0GH3XG9u6p3yckXyOgTwmT+E7f1/BNIeroTrKsCdR1duSZ1OgCKWvQgZWy7AMZk3ja72S8J82xTHN1lBLTnWkmUL6ZTPP0gznUOeR1CvkuQjzpsveytU9eRAbNOCPrkcGpqMAycDI/wQaCVhnsOEsZrG0dWAabzpCmVQZmwBLQBX4y2HEWMvDoao8zP+cyP/0og/1N8iPDQZ3WhtjmlXsE06nh3oYLmM5Qljt6ZqB0WFoY8xs5iQC5CJ9hlrdl63BHVKtYbz7Ovsz51POvYl6Ws8z5/nlxT80C9otmRG8If4vTjgmeE54kvd9kI/I7EuU41R5jtvgz/5053Thg30w9DvDZR7KP5TuH5evkkXVhgPJR1B55juhx5jxZZZlGReUAppVMWWYyLb/JiU6nW/zZtZ96pjOY6QxgmWqYTsBJENtPOt8dGmX2sa3DbVGtoiz5aH778eQltV3gfqOeeQk0+PbpN3s0r+yefmp3u8B9xrHTpGftL9LAuxE02r/P7HH2ZU+JCVz2xCLJS7DJkU7zQNfmlX2sp+wxgcueffr0WHx3+VNjUH7QWJbfm5d/ofztA5e/hvkJMnnVaQ7sdpblbx+4/HWnT8+3/IhjIyiL5ffm5V8of2zg8jcwP0EmsjrNCc1s+7r8sYHLH1182vR8y484NoLG+5V/wr/S/jsELn9mkPxwSUKnOets679D4PI7T5sei+8=
*/