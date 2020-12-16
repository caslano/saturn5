// Copyright Peter Dimov and David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef GET_POINTER_DWA20021219_HPP
#define GET_POINTER_DWA20021219_HPP

#include <boost/config.hpp>

// In order to avoid circular dependencies with Boost.TR1
// we make sure that our include of <memory> doesn't try to
// pull in the TR1 headers: that's why we use this header 
// rather than including <memory> directly:
#include <boost/config/no_tr1/memory.hpp>  // std::auto_ptr

namespace boost { 

// get_pointer(p) extracts a ->* capable pointer from p

template<class T> T * get_pointer(T * p)
{
    return p;
}

// get_pointer(shared_ptr<T> const & p) has been moved to shared_ptr.hpp

#if !defined( BOOST_NO_AUTO_PTR )

#if defined( __GNUC__ ) && (defined( __GXX_EXPERIMENTAL_CXX0X__ ) || (__cplusplus >= 201103L))
#if defined( BOOST_GCC )
#if BOOST_GCC >= 40600
#define BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS
#endif // BOOST_GCC >= 40600
#elif defined( __clang__ ) && defined( __has_warning )
#if __has_warning("-Wdeprecated-declarations")
#define BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS
#endif // __has_warning("-Wdeprecated-declarations")
#endif
#endif // defined( __GNUC__ ) && (defined( __GXX_EXPERIMENTAL_CXX0X__ ) || (__cplusplus >= 201103L))

#if defined( BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS )
// Disable libstdc++ warnings about std::auto_ptr being deprecated in C++11 mode
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#define BOOST_CORE_DETAIL_DISABLED_DEPRECATED_WARNINGS
#endif

template<class T> T * get_pointer(std::auto_ptr<T> const& p)
{
    return p.get();
}

#if defined( BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS )
#pragma GCC diagnostic pop
#undef BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS
#endif

#endif // !defined( BOOST_NO_AUTO_PTR )

#if !defined( BOOST_NO_CXX11_SMART_PTR )

template<class T> T * get_pointer( std::unique_ptr<T> const& p )
{
    return p.get();
}

template<class T> T * get_pointer( std::shared_ptr<T> const& p )
{
    return p.get();
}

#endif

} // namespace boost

#endif // GET_POINTER_DWA20021219_HPP

/* get_pointer.hpp
QmoYUoOQRoY0ImQzQzYjZDtDIKlqsoefQJ4BfR0C7IjwMMID0AKCFiCkB0MgivGXCndG3pKaQDRQqrnPrYE353Ln0qKNXn31PPeitri7EyhphJH6dQKlHfjOadiPkP6n5d4RiNUGIt90mPGsEpx+GZefvy1v9r1Mdg7vBmb8mc7No94/Z/gjKyCc/KHDjHcmTEiBv92E9z7sZwL8BsGGcvjnfmeDp4cZb4E1c0ASsh/356eiGYSkBRQzqu8MOMXipxl/uBQyTuoqMCPW0bjiaCVJ33N+3RLyK4BTLcjSOuGSDAY6lANfuOHcxe0pMv07e1cC3lSVhZOmLaEUEqDF6iAUKVioYMeiUwhqQxNJIEgRFFzBqSIKoygJi0UWQ0fiM4qOjqgzo6Mz476OSqmCLZW27IsLRUYF11czIKCWgkDm/+997zVNAYuDs32T70vy3t2Xc88999yzlNE1K5MeZ/vs8tV4t+rvuIWnAzqnFV87RCwnhprbh7YtwXtL+x/d9PvT9rgj3L5Qk6GfPeCo+ofFMkfeNip9FlCtjMaq1GVtpHNVN15+2LmqaE/CREiVBlJt9gRxhwrwr0LISYGuCMHLXpt9mH0vFwOMx6BDIhF7e0z5l1P1/uym/jr6Aw1JtU09mIs0ZkX99Tuk/EsOFdsWGfrrmepDbQ0JmLxVE0PWH5B/QUOOKp9yvmwFhtxL3zarRUfbvZEobmJHJUZsop/nvGGXAVZer2eL+3fY44e+nHpPSWchRWvxhLqLfjcJyWAEWi0DF/sJHkgInI6lnRgYZ4CKsgJQYlsCCYGJIScYoCZ4YAwPwa5w4KTAWUhrD5wRD1bNs8jLb5sdkych8VjzbRbDkGRb4kwQE+3/DhlawJelqwFfPsJXhYSvK5OOE74gWFB1rPeJwYEJZZwAf1JZV0JW6/zfCpJk/M9kG6NOZau0SYErMGdw/0m2O15FPAzKzDPZnqizBf/C1IXfHYxSkLqUOnrsj0v6lcvnTwF/PMLFM3/GwX8BgZLRaMAAeh9KbCvcpd0lzfuHmZtetNZH0ycU9zApdbj+zy+/Q1f3T2Ca9l1KKVz8kCvs/EStgAQDhFc8nYU5G6nDUJiHsJpIzlt8w8NpRgEhWcB7C7QChhxU5yZzZei+sOxeZXIGfEDAD0QJ/UD8ROL72vgbyr3UVI9zJ1V3sqbb8RnUO/J2upX98wZePkL4IraVvi7k2/pF0y+/Gkhbc18UFB7bdvvC15lBOZpH5HwLb3pX5DXAR5htwb1muc4mQTxCJhXub6fhwct5aOecNzirr23BLxHgXNpBjFPS80FIitDJ21o1uOtgVFO/LnUjTX0JfgYPspW2xz+3SK7c9fnJkgI8F995tuAaIfBUGa0oyO8TiNS/Saw0iOIN6b+Z0EM+CtNDddH0+xDAjjiq/KeXL9SVFOV09Q5yuhZjuvarGxOFSkh/s4C20gb6fG/wKV+C4PPl7BNN8I9dJOqfNtKo++tIIQjAQG8kzG/j76TFg6aoYfyZga9dym4n3GJ1r98gvPjuQ6qOLRIpqq38u+6oFH7gkEy2n6D63ng0nlNwL4KN1veUrZ90u976A2on0frINE3jie3/5QgYIbyS/v0hRnDIHEiad15fv9u5NENOQV/kxoqg+JVp58GoN+RmTYEzjFp6y1oSjFqWqs9ZRC3tvTVuEz8xav9CzF7xS/dP/9EiC8f85FXkm5smiLM8b6Ap8LWtfHf3o/sLxvmrbB62KfW2Lvqha8oN2qFrQdZUxHgpEdhIWak96g27NcRGq5AUoPXh2qzMzPzv+jsD+IisJggst+9D/nmEL12B7Mq7ak/jnEuZ42cVwe0pE4PnJQjsSNI=
*/