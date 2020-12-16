/*
 * async_handler.hpp
 *
 *  Created on: 12.06.2016
 *      Author: Klemens
 */

#ifndef BOOST_PROCESS_DETAIL_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_DETAIL_ASYNC_HANDLER_HPP_

#include <type_traits>

#if defined(BOOST_POSIX_API)
#include <boost/process/posix.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <boost/process/detail/posix/asio_fwd.hpp>
#else
#include <boost/process/detail/windows/async_handler.hpp>
#include <boost/process/detail/windows/asio_fwd.hpp>
#endif

namespace boost {

namespace process {

namespace detail {

#if defined(BOOST_POSIX_API)
using ::boost::process::detail::posix::is_async_handler;
using ::boost::process::detail::posix::does_require_io_context;
#else
using ::boost::process::detail::windows::is_async_handler;
using ::boost::process::detail::windows::does_require_io_context;
#endif

template<typename ...Args>
struct has_io_context;

template<typename T, typename ...Args>
struct has_io_context<T, Args...>
{
    typedef typename has_io_context<Args...>::type next;
    typedef typename std::is_same<
                typename std::remove_reference<T>::type,
                boost::asio::io_context>::type is_ios;
    typedef typename std::conditional<is_ios::value,
            std::true_type,
            next>::type type;
};

template<typename T>
struct has_io_context<T>
{
    typedef typename std::is_same<
            typename std::remove_reference<T>::type,
            boost::asio::io_context>::type type;
};

template<typename ...Args>
using has_io_context_t = typename has_io_context<Args...>::type;

template<typename ...Args>
struct has_async_handler;

template<typename T, typename ...Args>
struct has_async_handler<T, Args...>
{
    typedef typename has_async_handler<Args...>::type next;
    typedef typename is_async_handler<T>::type is_ios;
    typedef typename std::conditional<is_ios::value,
            std::true_type,
            next>::type type;
};

template<typename T>
struct has_async_handler<T>
{
    typedef typename is_async_handler<T>::type type;
};

template<typename ...Args>
struct needs_io_context;

template<typename T, typename ...Args>
struct needs_io_context<T, Args...>
{
    typedef typename needs_io_context<Args...>::type next;
    typedef typename does_require_io_context<T>::type is_ios;
    typedef typename std::conditional<is_ios::value,
            std::true_type,
            next>::type type;
};

template<typename T>
struct needs_io_context<T>
{
    typedef typename does_require_io_context<T>::type type;
};

template<typename ...Args>
boost::asio::io_context &get_io_context_var(boost::asio::io_context & f, Args&...)
{
    return f;
}

template<typename First, typename ...Args>
boost::asio::io_context &get_io_context_var(First&, Args&...args)
{
    return get_io_context_var(args...);
}

}
}
}


#endif /* BOOST_PROCESS_DETAIL_ASYNC_HANDLER_HPP_ */

/* async_handler.hpp
fIYqI+X3scfm05ZrHnaffxin+2ea9GzODYz7HEpI/xkezakZX0c5ra6HzXd5tuPhcojls1hV6f+iRzT7fqKHn3w+idSHY80tczQxxmfmrfc5pKXq4wvGl6X/IK0wy1WRJanhzJP5XPLnHF5adfa4KG0KR6u3KHWEIa9qTbQ4RyXai/fUVrEslue0DLV+BzH4JzmuGOcR3WScvTyCVXn1lE713W1z2W5bSZkBHpbnssjBSj/mVJF1E67luU7vuhRtlHlLynhbjoUZPDbUnK+t0r8R3eocROazmOVYx1c6MlXNqN/NMsyPLHlf6z0jUkrfRu9JmbV8Emr90LiL8zkrkPewO+Vdn4E8k/0ryicsD+cnLK8ieT9fmd9jjJD6SNVKagGsiTKsH/LG+tnA+gkn52m7jqIdvZ3rSD6D9ecYx+h5v877GewzXt9H67nV56r/F5Z+04gDdP+TyJT+Zr9hejzWeVgAsI5+Mj/DPfGT/jmshnHvQ5iZM64vFjJzxmc4XzNXXfsP98Zw/DG+58t7b4w6zli/p5Zjh/l5zTwncX/eoezjeT+vGfsrOeOalNqe1HXNdqw7+e6zWN5r3bUqafJ3j/Am7hIFmO+1P6njcHas7DBcrHK7zmIeH7ZJWc7dOVZ9qnnZHpcZ3+M/a++n/3wNdJP0v6U5t/Uv834/aHxvfcZZhrlZpOVzO1aY10weSJml2hjN2zinOSu54pr+/vwl291BYpjbOekhcoeJI06Dice4lmDzHcajn0mmzkEnV3GN4DsiP/Etsd25fn7Ou3442HD/Il8BaZrbvQHmevpKhnlf68K+u4KwXU8/Wz8DyDgYvXkeuVH6l9eKPuIzuXV4joO8Ys4ecU3WWraf3DMpn72N96+t0v8Q9cLRiNhH2Ly3Mh73a5hyT3GsjM32earmMJb3hST5VG65H2+HlNkn3xkH8N6XzKvdhH5t6WgIdUocU9vH7GAJeT31sb7TYHuw3g9g2R6oe3JS98axQ87ZpD7NYwf1Rk7Vm/XY4VYHcp+B2qYCq2nyN1vt87OIuUXpvpBnm3rE9mR+Hlwo5Yezr9h+nlTjcxjPgnOoJ2Rz07WxL78mZaZqMfw/zu46v+14qAMZjfn++7WUKWiznZnDF2e9eTvLWu6x+8a5/h7zHkib9WVcp2O+yFmXj3Vm5M35ta6HjGjXyJ04iGrEavbtqIsO/dmPTCRWvz/ZfT3Y1TnD2t6HbFevlHXfbygbm8DDwp1fZ9nvs9bxnwp1XR+2nn9FS/8Sxnd8nzMPx0M0xvBw/Xo9Rv3a3EPsdg3UOs957y+eU13GTTfLQjQiZjPuLnnr1/isoT5iuNWzuWy9ZLiadvXOOG2+k+mXnpX4iPc4Vd6op2+po++I70P+t3pyv14s01bfc64sxvu8/D4hK6Gf2/uLPFRDhnf9FSaWRFBP7nWUbXy9+VjbIcNb38N5xeCPqAtV1rg/64RNHWiPUQf294ua+9uEmq4RPKX2t/bEq5Rday4rA8kunJmYqLnNu7kdbJLyrezfP92WW9PYuDLN49R56V9QnnU5gbqvxzzVoEdAAfP++/fV/Wlq25BrXZ7EwsDH3zasdWC9zpygHhz2jKqDHup7bO2Sex1kZCbyK5wEzf37bPNaxxMyTH27emB8dudw5mfrIOnfUou2rPe5/8Xymd9Zux1T67oKf6DOlzYR6yjb11w++a5efuuR9XjbsmtYh/FZjX27/4gWzTLispNstudHlpc3AP06fX8p84LNMdZu+PgkNTmb859HlZfJmc98lTKN7M6FGP6R7xnu1woo+9fvGW7fnzKM23sG82e9TylN+uda+lNflv0tRfovs/3MH4pJ0n+1VpU=
*/