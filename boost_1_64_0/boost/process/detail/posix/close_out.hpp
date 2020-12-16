// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_CLOSE_OUT_HPP
#define BOOST_PROCESS_DETAIL_POSIX_CLOSE_OUT_HPP

#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {

template<int p1, int p2>
struct close_out : handler_base_ext
{
    template <class Executor>
    inline void on_exec_setup(Executor &e) const;

    std::array<int, 2> get_used_handles() {return {p1 != -1 ? p1 : p2, p2 != -1 ? p2 : p1};}
};

template<>
template<typename Executor>
void close_out<1,-1>::on_exec_setup(Executor &e) const
{
    if (::close(STDOUT_FILENO) == -1)
        e.set_error(::boost::process::detail::get_last_error(), "close() failed");

}

template<>
template<typename Executor>
void close_out<2,-1>::on_exec_setup(Executor &e) const
{
    if (::close(STDERR_FILENO) == -1)
        e.set_error(::boost::process::detail::get_last_error(), "close() failed");
}

template<>
template<typename Executor>
void close_out<1,2>::on_exec_setup(Executor &e) const
{
    if (::close(STDOUT_FILENO) == -1)
        e.set_error(::boost::process::detail::get_last_error(), "close() failed");

    if (::close(STDERR_FILENO) == -1)
        e.set_error(::boost::process::detail::get_last_error(), "close() failed");
}

}}}}

#endif

/* close_out.hpp
r4s+LTkUk9ofJGiK1h8karz4f5qxS5tosYq22GvjDcYa1WJlbbGnbz07rugdLaau46oWC7TFPtVi6nonaTF1vc20mLreysTs+5yU0mLqOgoQs+9z4q3F1PU6E7Pvc/Ig/tk+J3e0WDl134jZ9znZR0zf5+Tk+LR9TvgOSNPnZNH4v9bnhJj4vcFvENlXRPQT4beAYT8U+XefuPb7QMR32sebiTh/x9Ppt0LcqN9Kkn05sanbeFDbHv4GiLx8txr2ceF7Lf0+Ln6WjI8lmNGxLo37iGS8T4xx35f0+5TM7GaNDz3h3XbvgupdvVaXPO8x5Nu6Ge/bkdG+MsZ9QdLrE/Of6/uyWxyfLjMHr4w4Eb0nIN9n43ee/iIw/b4pxn1l0u+zYtynJL0+MRnva/Wy+8TcJf8lJ3m9I6/BzuJ80mniiryHrhjWwAAMwU3YApOxJZ7ETvgTdsF7GI6PsRuaZF8UZ+yBrtgLPTEKc2AfzId9sRBGYwnsj6/hAAzEWKyKcVgXB2FDfAPDcCh2xuEYiyNwGI7ERByF83EcrsR4PICT8DhOxjM4Bb/GafgTzsB7OBMf4yw0ybECM+PbmA3nYmGch6/gQiyNi7AiLsZquAxr4HLsgCsxDFfjG7gGh+I6nIMtcAVuxjW4BTdgG0zGtngI38JvcQJexvb4E3bAu9gRH+AHsu/KDsyNO7EA7sYSmIQVcA82wr3YEvdhD9yP0XgIh+DHOA8P4zI8iu/hJ7gXP8XjeAxP4Wd4Dk/gNTyJP6KHieOM2fChHDvQxLn4Bbqh9XVPzIY55BiB+fACVsRvsBVext54FfviNRyF3+M4/AEn4g2chj/i23gHt+Nd/Ajv4X78DT/F3/EnfIx38Qk+xD/QzZnfgeiLCtuXB81YCJ2wLDpjIHpgDcyGddEFm6IrhsrXw+Tr4ZgdY9EHJ2EOnIW+uAzz4CrMixswH36M+fFzLIBX8RX8AYviLSyGd7AEPsLX0E+OAZgPy2EhDMJqWAVrYVWsh9WxMdbCbtgA+2FDjMVGOBlDMRGb4iL5fDU2w/XYHN+X8b1YEE9hW/wa2+FlbI83sQPew474CMPQ7Mr3EObAzlgMw9HPObVvVFmS+wnG6yMFkUJIvUijSfNIm0kHSWdJt0jKSfOf9rtKrv/898nmPWl29LXKQF+rmhwvtb9VcfO/tc9VxEmzo9/Vv7nf1cSTZkffq39z36tlJx19rxwPx8PxcDwcj/+ex0tv/w98Me3/Pxu0/xOzb/8nZt/+T8y4/Z+4ffu/VoaTzK/oYs62vLqYi3bfvRpzVe/P19aT2WCsQOKGbfvjdW37ofJ+/BDr9bz0Aa8sG6227Qf+s3ECE8aQl9oiP6WGvP9eLk9p+ezuvyee/v336Swn40bt/Or94IfF68Utv5otdvfoa/cCO4ntvGXeRR6je+1TyJMiylEsx83P3msv2p3xksjzjfm8YmYHXHnz16tzIH4o1lHJbGZk//Kmeozw11A5aaoo7g//2a7PQCaRdwL7N/if3rNvdF/+NV67LrbFzfIl25tZK0Ntv5s/ltfZFhdqNzKbnNU5yD8R8V5q22ZlUa/YUG6bbT8myvmVWYZn5UWeUM4/8un3lz00Kx8bjofoK+fuvCa2091SkZwNTImG4yLmxOMiX4rZhy223WOfLNZbVn+PeGAXbhOP5omvHP/goVjuofmw6YByiGOhtXuKjF26R8YyNS355f3zt0R+J8tXpr3KSfLbz116nzw7RZ4gi7PFYtSeq859bN2Xnt6p2yX2WR7jzWL5rJYKVIrlNicR1x/HPWI+7VDldfUYpR5Li7k0n85wxcv+vnl17tgDotzfzA8YTe2m6aKMa+c=
*/