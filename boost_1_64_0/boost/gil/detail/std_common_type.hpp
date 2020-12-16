//
// Copyright Louis Dionne 2013-2017
//
// Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_DETAIL_STD_COMMON_TYPE_HPP
#define BOOST_GIL_DETAIL_STD_COMMON_TYPE_HPP

#include <type_traits>
#include <utility>

namespace boost { namespace gil { namespace detail {

// Defines a SFINAE-friendly version of `std::common_type`.
//
// Based on boost/hana/detail/std_common_type.hpp
// Equivalent to `std::common_type`, except it is SFINAE-friendly and
// does not support custom specializations.

template <typename T, typename U, typename = void>
struct std_common_type {};

template <typename T, typename U>
struct std_common_type
<
    T, U,
    decltype((void)(true ? std::declval<T>() : std::declval<U>()))
>
{
    using type = typename std::decay
        <
            decltype(true ? std::declval<T>() : std::declval<U>())
        >::type;
};

}}} // namespace boost::gil::detail

#endif

/* std_common_type.hpp
zkO7k3Vh1mPwAOQZR+bPLCwsHfp1kkeeO0+EVsDxHttVY2Zzs9ybgTFNltHEymlqlhn95Xd6d5Wl23b4wydI98SuyjP7Y0+eL1FOslrMHgR9mloW+ot2NZZZQotL85GOzMXso29W63tIPaUxzaz36yeZ0EZkqX23kkffDSdLfZctSDvfb17WBP2T7J8m3V63WhMMe5b8HhFsf9GWdxDDc3rXmdmnhbY9QF2TLWd2mD4iin5GlhNmHLfqhV1FMEvo+r7+HTiy5m6rrM1nhzIsQrsL5nqpjzFtf/e6B4oGoV7Ioi0pVk1b+09/ZkXfNaXBO6/VtfsHZWbtRwxkxd2mjfvoX3p1ROxmPZ22QWKHJodHov3IyjMrVmRqSbQfWeq5sYHHuaqnYP0FixBsmGCjBBsn2BTBYgSbLdgCwZYI9o1gawXbKNg2weIF2yvYL4IdFey0YBeZNfSwq4LdFixJsCeCvRDMbPFuaQXLzKyRh+UQLK9gDsFKCFZWsAqCVRWspmD1BGsimEuwtoIFC9ZdsN6CDRQsSrARgkULNkGwGLLU85i2N2Wn4JLYhzxWsDjB4snSMHv02U59TSRYIs/TfU6F/ZuvewGrKV3jAL5RJGGXkIRQJoTcY1xyb8hMCKEZmQm5h5B74zYhJnKJwWTGJWRObiMjhJgQ04yGzIQQcg9xQjjvjvXvXe959nfOeZ5zzvM731rf+73vd1lr791pUMZg9/FZpr2IwfBpGYOjofh8Hfj1m+KzIpkzs6nWJVejJsi8mS0sH3wJ8ZHRfXDWOF3Ku7TJSn68r+ms4WXw8vJETz6YsYR5cy5p3jxKmTcvC/Pma2neAkubt5Ay5i2cwLfIfL0MpnNPPYuTmmWTWZjM6FFk6W+n3NEsl6xukXkV2cpSJZsi9rIGOmN+uKZpfLu9rttEs2BrGreP7Uz2eJ3dW/RF2O+VPsnQLIasDrN///0q+oMFGZKZlTRMNUyYFtmtyOifuWRVP1opynZh5/ohmlmV09uPf/T8XDM3sirMBnZMPaeZt7CeI+//plkwWV1mSdNeVNdiiCXzqvRhXCxM61tFD9cPNpz+3mhxDJaGUYYxc+93/GAlDLkETT5aGUNJw73C3ac0c6ablfqYI5PFNaiKdm5kdqxdw7djRmvmRdaM2eYpfb/QLJzMntn0utYvPlgpQwyZzUcz1VSWd+9IzeLIrJlFdUjdo1misMOVgv/WLJXMiplvp2V7Nctg8ZnsYseYgZplCht0edpuzbKEXQ9p9EazbLIm7H55c4OOaPlzcDEYGn+0svS/Hd4v7T7mH1ngx3lkbQiYsKx28/OapaLdB/u2RrNczUwHaMuPfTFZzHK3RM2syEoze3Rqy1OsL8KuDdu+VzMHcc3VK5+2xfyT7eb/ch1rD1lAkfkWmbNTx09Qn2RfMbt4MboM+lJPH59dzNmdmnmTVWNmf9FiN+a7sFXGneM1iyBryOzG3JLXNEsma8TMpufTGR9sqqGgXvFcKWeYbDhWNfsTzZzpP3l9jMFkrVfa+mgWQtaetWuZOu+aZslkrZl1XP1bvmZWbnSGYdblZrTFB5ts8CEr+XGsbajHXed8fU8zX7JSzOqH9tmjmR+ZBbPIzPrOmvm7Ib4i+7naZy00CyezZxZoqPVaW0Ni3IprojytIYvedh6tWaywO7XKvdMsgSz84x5gstQlN3dp5lvfYCj78X4m+2tWgymaBQrLrbb1O81CyMoxu13Y9rxm4WSVmD0u6TYYMQg7MfhBLvpJVpFZz6SOuF+quF/BFockzTLFNZ8Ptm6oWZ6w6yXPrNPMqoH+fgNzarzUzJnMhlnKq4tjNPMgq8Bs8629zpp5CevV7fM=
*/