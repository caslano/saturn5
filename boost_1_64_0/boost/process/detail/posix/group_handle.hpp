// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_GROUP_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/child_handle.hpp>
#include <system_error>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

struct group_handle
{
    pid_t grp = -1;

    typedef pid_t handle_t;
    handle_t handle() const { return grp; }

    explicit group_handle(handle_t h) :
        grp(h)
    {
    }

     group_handle() = default;

    ~group_handle() = default;
    group_handle(const group_handle & c) = delete;
    group_handle(group_handle && c) : grp(c.grp)
    {
        c.grp = -1;
    }
    group_handle &operator=(const group_handle & c) = delete;
    group_handle &operator=(group_handle && c)
    {
        grp = c.grp;
        c.grp = -1;
        return *this;
    }

    void add(handle_t proc)
    {   
        if (::setpgid(proc, grp))
            throw_last_error();
    }
    void add(handle_t proc, std::error_code & ec) noexcept
    {
        if (::setpgid(proc, grp))
            ec = get_last_error();
    }

    bool has(handle_t proc)
    {
        return ::getpgid(proc) == grp;
    }
    bool has(handle_t proc, std::error_code &) noexcept
    {
        return ::getpgid(proc) == grp;
    }

    bool valid() const
    {
        return grp != -1;
    }
};

inline  void terminate(group_handle &p, std::error_code &ec) noexcept
{
    if (::killpg(p.grp, SIGKILL) == -1)
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();

    p.grp = -1;
}

inline void terminate(group_handle &p)
{
    std::error_code ec;
    terminate(p, ec);
    boost::process::detail::throw_error(ec, "killpg(2) failed in terminate");
}

inline bool in_group()
{
    return true;
}

}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_ */

/* group_handle.hpp
Df8M/6J6n8K3sH8H34YeMrUftoEB95Pg+9hPgYF0ZMCzYG9176v7NY2AH8Mx8ACcqPrnqv5U1Z+m+zldAA/C+fAQXKL6y1T/56p/he7rdDv8K9yu7o+q+074PfLX1P469MJv1P4tjIGpXuywKawH0+Ao2AGeBbuo+ykwEZ6q7gPUfbC6D4WN4HB1H6vu49X9HNgUTlH3Wepeou5lsDmsUvfF6n6Jui+HreDl6r5a3dep+02wDdyo7lvU/X51fxC2g9vV/Ql1/72674Ed4XPqvk/d31b3d2Bn+KG6f6Hu30ApT3gK9Phwh/XhWTAZjoYpMAM2U/f26t5Z3bvCnrC7up+h7kPVfTjsA7PUfby6T1b3KbA/zFf3EnWvUPcqeDqcr+6XqPtl6n45HASvUvd16r5B3TfCofAOdb9f3R9S9x0wEz6u7k+r+/Pq/oLK31b5+yo/LM+P+q5M37mthOkYv44/krXfbATTYCpsDXvCdNgUtld7B5gGu6i9K2wBu6u9B2wF+6q9H0yHZ6h9IGwLh6l9OGwHs9R+JuwAz1b7WNgJjlf7BNgZnqv2KbArzFf7NNgNzlT7LJgBS9ReCnvASrVP1H2WfmgfpabcqLtiBmMmYooxizHXYO7G7MS8gAnts3SAv/kE/0/Zb6md31e351Ldnkthey6d7vf9y/ZdWtzJU7f30v/p3ku5tKtizArMeswOzGuYI5hEbridMIMxEzHlmBWYjZgdmL2Yg5g4HmLaYQZj6n51v7pf3e//9ReFmfGvW/8vav+MPQAC6+jX84K9Jl3W0VeXTq8qKiutlLP5NricAbjB5QxAZM4zAGUd78eOs/os3c5vpM6HGoFpwMurLYPl239OWUXViNKh88eE5i5+mUh4nLYQOp+gEdwquq3c1+Dixr8wvz0c5/VtF/czrAT+7+O2js8O47jX6ATiaaxpREZ4toy4nXMfeGdr5oIZ3taS/4ZI/qlSdqufVV1VEJxmbubLHUg5vjlioXPKFmliGxJfIkyAdxJP4hCPnok43ax/2ITco3spuJSp+vFEnv3jVnboup/t00rLv3PAHXEOIS/HvIz5BuM2l9cZ1l3S1maYsxeT4Ahxp53QxruS83rofZskehLeQZmfMjqpmLyv9bFWPYVwkzqZMv0kJTg3OqSz0+gs3hWpk4Y9WtdzdEiuvXYz8TjaSaCcG0s5aztxOf/AH3H+AXMyJB/kC9kMmVczT/LNeA1ZwH5XhP1RtS9PC583mBsdnj4f5itcpg6UNlFYU1SlpzxFnvPk2i7w51bXru0C3eObo3O850KQL9OndNUJlmkaUDPMVso6fZjkK9SR0eLLpY1sbilpdcuT+vE49Ka55Qe948tPaE4NYQXSLvY4Y58m9ZUxzK4vZ1+xJyZ8XmxDzAP4GxyRr+CJkdaP5g1/YWsWPz2OPiUy/c72tFUXKdPcCJXwPcH2VB5sT4EFrifUnspPoD0ZXfssQp6A7LWWUYPkjC++w8SpjNO7RHa61YGWH3HOlrk/rJBwC6xO/N9f28GGiHO2rhCd07jHdovsm8x5WIdE55HINR0SxwFx2yV+v5CSrDJ+U+D74r7b6kE9JZiza+xzanbq37Y58XUIx3N9hdrhlPja96zt5HlssB0Wz8obMX7MMDmjd0ZFYaHjnlIs7dJ1DUhEWzz4g20x3aUflbDD0vltPf2Oqr5yMI+gO1XTWVQZ2tAjb0apXi+HpZ1NN3VbILodcWvmlm7Cijw/c0ZFWYm9LnONuDd2abNufqvKnOuUfy7uia73QqdfX5ReG8hdzvg1uqnWZEl/y2S+UUj7OL61iKFr/rC0h+kR5xJKfiPOJZR8iCwR+qK0HUXUz6I=
*/