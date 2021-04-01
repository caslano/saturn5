// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_EXE_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_EXE_HPP_


namespace boost
{
namespace process
{
namespace detail
{
namespace posix
{

template<class StringType, class Executor>
inline void apply_exe(const StringType & exe, Executor & e)
{
    e.exe = exe.c_str();
}

}



}
}
}



#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ARGS_HPP_ */

/* exe.hpp
lgKkM9fFafqji/dGzIhVsy8N7GDULXQE1VCrH5nO+fYvYgXMORxKSfK0BwU1w9K6azLliilr/w30Wxvc4um/+V70bo41M6q3YR7dM+BZcLhzwMeZ8M2o1rYW9RNDQhRcJvEwSxml1i5JamDlEnWJXww9LyCoqwfh09DUVP5DEUa03adnWmN0fcNAU1cvFs+WsyoLFl9X8gt+NlD3CSwhmOXvl5xk17TgfiWyhVi3Uo3ly845jYSN2P0hn859mdYaLEiHpaMnXvp/wM2uLYRwmOLbgBZ/S799Hwb63hym3E0xgkXpz9M8pQd0gWaRC3OqXwVZNoloNr9Rkig83OaCEEP0J8Nqpf//23Hs0V9gs2tcSSdpDltxUzzlv3zVu8M6mvrCEYBGidArU8mhTRKhIYq0IoueMkKUQM6qTitcP3XgGpnP1QInmxF8GBdpojQJO7ZpJny+gkgR9mjV7XJk3CS2bIo6zEqqT/8LBLihTm01ZIqK7zoBeLAenWNAS4qbTMxgUIh1rcbFu3wpYRNW54KObpOj9PLnhLdE2aXSCV/+o+uwUUlU5o9fTQ==
*/