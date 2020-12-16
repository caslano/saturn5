// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_WINDOWS_ENV_INIT_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_ENV_INIT_HPP_

#include <boost/winapi/error_codes.hpp>
#include <boost/winapi/process.hpp>


#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/environment.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<typename Char>
struct env_init : public ::boost::process::detail::handler_base
{
    boost::process::basic_environment<Char> env;

    env_init(boost::process::basic_environment<Char> && env) : env(std::move(env)) {};
    env_init(const boost::process::basic_environment<Char> & env) : env(env) {};

    constexpr static ::boost::winapi::DWORD_ creation_flag(char)    {return 0u;}
    constexpr static ::boost::winapi::DWORD_ creation_flag(wchar_t)
    {
       return ::boost::winapi::CREATE_UNICODE_ENVIRONMENT_;
    }

    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &exec) const
    {
        auto e = env.native_handle();
        if (*e == null_char<char>())
        {
            exec.set_error(std::error_code(::boost::winapi::ERROR_BAD_ENVIRONMENT_, std::system_category()),
                    "Empty Environment");
        }

        exec.env = e;
        exec.creation_flags |= creation_flag(Char());
    }

};

}}}}



#endif /* BOOST_PROCESS_DETAIL_WINDOWS_ENV_INIT_HPP_ */

/* env_init.hpp
rxrprk8Nn7te5Mjoma5gv+AmiaNXn2/QWdL5tKvUjDTFHx2nvikZRpOogVH7jGbeL4we0R8YbWKOetPV+d6bxZ9Orlr03jqzo5v4p91eFRtnjIq1nacs5aaGfi5UmVL3OdgWtJH7cbuvJrXlZurTn6lPu3iXVN2t6tN0XZ8WVahPrbKWX2ivS5Pg53/062fFrDAWRTeOSdTntu/OCTz7jYyDUh4KiNtSCX+Qz4ojU378zbltTt5Wec6vNXcbTdk3kmdX5MF7Niwq2djtOebpYQ6OdJl+fxvj76vib6LteaLxzxlbVKzm1sxEx7KbTEHNnzKuMFBOx2FXvY/cI1tdRk2WUzKrOM+qf/pLfZUqbopxM0zcXGm5oa0pGO/fW9mqC/40WOYFm+HbqmnSxq/Ev4vEv8vFv9ZV5Zkak5NbUjJF1Tkb0FHnAvBHOFRHU9WzFofdIMmDpb4Y6wxyI1PFPWuItOMy8zeR0nA+TFbldafEaSB2Z2ETuAc3iqx2XKLRiHfUh1yJbGjRAzPHMzUqQZXPWoMkzwPPmU7bkGiX0S+6Yt1VrPOwmcSjqjx3C4lzwM2z1SQ/2P3uAX753Z6v0m/wN1/F6Wvpd51ZM4qv8XNdB41J7nXso32zcdQz1rgwIse1PaqZcQwz2rvSuCa6vXFvzLvG67FnGt/Hbje2xW03lyScYTySsMF8MjHJ823qG663q/5glGdcz0aMScauaguMGtWbGyeqNzVa1hhsvFvDY3yNiWTjkpSaLl0Gf5bn/w0+H38ZU50n8NzY1TLn9CD9oZryvJ5M/Sw1yj7nNG+KVLZWOdotZaIROlzrfJtNmRgXGcyX6XIvx/te885yt6L+XsXzaZuPq++rS9wWmv77Wo3dUy/iV3CP8gFS7zzsqmrmmsH+wg0SxxxXX3aiTLDXnTLv2l5femxt39iJ8iTYzn24R8K9hlQ0kPLXkjjPlPI7rrZ2J2m32sw5qk3rGpiJR+VkzU29VPLke9O5DrKekwb40UPyZrVP7fuuwslh/pdVh3wxGh1mRO02GtK65Ju1KqQtjW2B/hh/WfwWT25ynDE7ebWkwesvj+L3Ip+t/1g8KXdsjqrz9D10Szm4Ul2rcqHmrt+OP9eJP711eyptbvG0kpxx0p6K3pvoNZQ8e7hC3+8SWz91arbUFxGtXS6zWUQ0z6c9f67maekfWRRZ7hoRPTlmf8pjno8z6KOq8thB/L6ldnn0LWZR3Ijk12sFylBcmtSPEoctxKGVxPVOn3q30H1mQ923EycD9+3tRPXewb+tVBl7JlAnp+w3fPERCRFmlSo+45kqnxknE/sbS3jjPZONOx9P7s57QxxvEVUkzB/x7wIJc4GtTyzHkemyW0/6UI8ylyVa993KJKxG+PiR67BrckwR7Xwt/FtLGiaKfyW+OlUyje5M8cut0i7xNp4Z/X5hvS/JrQy+s5bIu9E0T5ZxHXv5RrG/ZbTR2LVT9V95uxkvzwt95w6uwa5j7AMXj9vA+3kw7V8Yu+IiEhZJWrvQb7DaStogCc1qD2aPkDGEQDr1O3G+K1L1DV/E39slLW3sZXBqjhTxivWIV9rdeboMfiTXUdJX64s/N4g/XX1rq15rNslsJ/VqHx/u1LzYZKYcm1Dq2Fx5LpQsIB0tstjAHH7V9iQbKi8DXXOxax9qN5FRzKkBuzbKTo9BULTsZ4XEy/tBcz1/PmWC9OMC9vodwUOa7PejN/fjJmMnu3cm2+9vDvlte0Z3iV8pei77KrnexRjVzbqcnTNO8tq8xuim6+Pjojealq27csvKEYnnmcQjFmMvj82quIwbPU96hsX4798o0nuZ5HuO7f4RLwZt82W4ytYOSFk=
*/