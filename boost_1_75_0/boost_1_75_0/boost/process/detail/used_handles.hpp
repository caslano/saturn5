// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_USED_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_USED_HANDLES_HPP_

#include <type_traits>
#include <boost/fusion/include/filter_if.hpp>
#include <boost/fusion/include/for_each.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handles.hpp>
#include <boost/process/detail/posix/asio_fwd.hpp>
#else
#include <boost/process/detail/windows/handles.hpp>
#include <boost/process/detail/windows/asio_fwd.hpp>
#endif

namespace boost { namespace process { namespace detail {

struct uses_handles
{
    //If you get an error here, you must add a `get_handles` function that returns a range or a single handle value
    void get_used_handles() const;
};

template<typename T>
struct does_use_handle: std::is_base_of<uses_handles, T> {};

template<typename T>
struct does_use_handle<T&> : std::is_base_of<uses_handles, T> {};

template<typename T>
struct does_use_handle<const T&> : std::is_base_of<uses_handles, T> {};

template<typename Char, typename Sequence>
class executor;

template<typename Func>
struct foreach_handle_invocator
{
    Func & func;
    foreach_handle_invocator(Func & func) : func(func) {}


    template<typename Range>
    void invoke(const Range & range) const
    {
        for (auto handle_ : range)
            func(handle_);

    }
    void invoke(::boost::process::detail::api::native_handle_type handle) const {func(handle);};

    template<typename T>
    void operator()(T & val) const {invoke(val.get_used_handles());}
};

template<typename Executor, typename Function>
void foreach_used_handle(Executor &exec, Function &&func)
{
    boost::fusion::for_each(boost::fusion::filter_if<does_use_handle<boost::mpl::_>>(exec.seq),
                            foreach_handle_invocator<Function>(func));
}

template<typename Executor>
std::vector<::boost::process::detail::api::native_handle_type>
        get_used_handles(Executor &exec)
{
    std::vector<::boost::process::detail::api::native_handle_type> res;
    foreach_used_handle(exec, [&](::boost::process::detail::api::native_handle_type handle){res.push_back(handle);});
    return res;
}



}}}

#endif /* BOOST_PROCESS_DETAIL_USED_HANDLES_HPP_ */

/* used_handles.hpp
fOe3XOIFlG4A//NvSUrmn4xjeEvKMONDIg68YUIaXgF2vMR289K2fh5sCt2AYNN64KQV/NF0gHPkaER9H+7Kys7s09P1/dXVSBjxOvDijUvnUhIeZoanr9mPUUcezzUYuaWy4yULQGuqb61tpDirefnb1dNm4T01+EkIsZQiluvQox7UbacABxX/w+JZx5E51ybdbJXn1C5/eRqNQhMH0qzz3If1SCvwAtdT5aE61I4qzB+gnfxoJ3MDv1w7HA/fTGfOfu/6IBHg67qOgl8M70pkpoZ4K2h/Tj2n21bpasssceoWq35/1Q9IcWnn7Jz04NnoSmKTOqH+G7MpvUVLhH3LvK3ua+4VVIhvoA/D3m/YeG7qUq0gob/ZejT3d6UL+dCcfJgEPUa03peHlZkhI9SoVQg44LXRDg7Y69lZnALsKoVwoztQHQ+dSYAV1wcwhZPL3o7DP/lI7gYSI/txLMs7v6s9zJQxgKru7zBuV7lizCnddsnFJ1wl2BaSy7CKW25E8u01Xt9UX73+qtE8x1Ki07LPj0Ug/1sZaqSaPsHARo+V1dpt0sgPlZkSO328IFqCbrLBv9Q2CRrQ5O4xwTgVpLGcY1eaXl0UhiaAZQzeVK9Fvzbev9WywZRwkgRmdCtmxRojEE632AAOru+3a/NU1NGEda56agx9p2ydXh6sKevyYF1gGflFSzZYNr2T44VGhFAv5WmlCAKt
*/