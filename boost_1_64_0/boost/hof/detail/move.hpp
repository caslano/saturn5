/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    move.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_MOVE_H
#define BOOST_HOF_GUARD_MOVE_H

#include <utility>

namespace boost { namespace hof {

template<typename T>
constexpr typename std::remove_reference<T>::type&&
move(T&& x) noexcept
{ 
    return static_cast<typename std::remove_reference<T>::type&&>(x); 
}

}} // namespace boost::hof

#endif

/* move.hpp
6Dqqo9umyY4GrpKpy3lA747l5nwiZ6phNhLZZ7KB5XJZ4KxT84V8pL01ksedP+K08o1Onn+co+AD9zPtZA5Qk1OOsfSWY2FDUGSliUEmnurJ9YHGK+1jTpjCA+VcbDQ2Obzv7Jaj6o/eniiftDUxLHURyT7C9s6YtkJTUmGANi1kSCo8M0V6ejwivn81n9LA/xb4/MzvLkGC8EyXDiwx+T/oyeIXqpZRmiZrKRArUUvAo1WHWJ0sl2XCWPY6JYOrnyimcu0FUFj9AbDfc1AWM+E9pAj8BV+cA04QKUEyU8jrBBCk7rqKvThDNx+9/u1IdXkODkRL5OIVa0aoyKGgWD08XVGs9oBmRluvkQSklvCApD/ZNZjLGfmm6aZzEkfSMD+G/YNJ5nqypovX5pxeHke9j/KOkKEdHyA4GmNPq56GX0pRrBC/2egWGRzpDEGk6fYNyR6WaP8odKqw8kKW/OZhSffglRjWbWPUEsWrxB9eYwMJcbBGa0tMnhPnkfn7jLBCh9mWalrEJFs2tWtsUnLj4WJFIOurfdtsp0a10021w88fOdh3ZpvezfQrwtNkx93hj+p89oWbVdc/9hWT7czx/KhgimYJaTIX56nm6E6AbE9tknIgoT2umsc2pLbvARGQWywRddAU5dH5xe0TGAXaP9lGH9WxzWbZm7js3NFGv7+QR1sbPoAqLeAsRbEN9mq2JJ8bpawUEtrS9D2ApOX6fGJHB8PZHEkWgSQ6ooMCYU/F4fPRl7iGYeuG3b7VCoxrSf9nFJ11s/lMyzgrXQJQVva/xzdf76a+PMwj0XRefKX5/iRRHrK3Q9H7ptIKKSX1gw5qz/ZkrfRjV6hde9jQ14e66pme1n4aNAD6Sl5M/qgvq7fEoKpVGf6vR8aMIFM5tzg0XcolzS3gZdgKM8ZwyNSeWiKqOTXtF/tcCt69jForjFrbxdWqvRJbvdo62Z/DI5BPvJ2v/Mi3ZiXKPbzO19J5gnSLvOzhiQnyslut6U+qdFU+3v61zyJPq8or+9fN0puGTbXY/yxKDKdb0ucPsdg/S8wf85d0ZIpaS1P98GJxe5F8EWxL4S7kHZT2LPOdL1eN7+XWB44PnXQs/4hvBn8AN0wWZ/OUiK9OUUts53w6Y6E7jqy3/JyzRoe9XI3iKDB+AJStX37pzB8l37gM/ARRemXMfvF1ml7NU/1dOdWRYab9YhdLEGewBPF7ot2UBJm0zaUlzFpl18rh22g1J4VvA4tb+eeODvsbdTDehodeDg15x/I/BDrwEJCU+dVebmao0/iqIG+/Iv+EvrzmWMXSdTAHg3fwQlGZbKzi8bhbkxCQtndeG8QCxsMml4ibirjLpLe8KN4IMQaA5m65MzzsbwTpyI5ApWWwp/IkW3p0YAWnsKadSvwtEqO3GPLDtxjyw3lKfvibWdLj6d+KDNvDTUWGDsC/SLSx3lWdKL+OsDzvLimwnndmOrhLLcrbjrOs93RPYthl2R9XD7TQvyZZ6F+TLfSvxHQ8w502FmThnWPIqd+PQobJEkgwFk0ydEXCQWf48IbO8M6XVXVyjJ5edXKgnlZ1crDeAc76yO55UyRlQtUYW9rkj6suzwkmg0LvITuSXpCLgAJKVg59ib18iGWSGCHEGXMnK3LinQoxPFdfT4Q5K0+ywJIgBBu4RHu4mh7u35xgaj7qNxO2wKk5RurqCaYpUr0kMIhjA6nCVRgz3F5AYoHkpCmYKrYUGR6a9Iv2J9NGq6101pa5fIRp77pUnfAdYsMJjEKVfIneiFXdcSiQ5dEc4xMb+yMwhgN+sZYC+RwoEcv58TTqC3RjiPl2Qd4H5BPX3ZDbbNqANwsFNlKAHjBnyT8=
*/