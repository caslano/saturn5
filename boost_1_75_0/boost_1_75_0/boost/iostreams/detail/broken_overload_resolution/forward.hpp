// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

#include <boost/config.hpp>                     // BOOST_STATIC_CONSANT.
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename U>
struct forward_impl {
    BOOST_STATIC_CONSTANT(bool, value =
        ( !is_same< U, Device >::value &&
          !is_same< U, reference_wrapper<Device> >::value ));
};

template<typename Device, typename U>
struct forward
    : mpl::bool_<forward_impl<Device, U>::value>
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* forward.hpp
TyyHIBoKKQSSE5ITmtNLJ1QnZCf04xfHKMe5pFnzyPdIhC8WMRfRF3GFJbmevV4RvnqNhBoqLRkuJS+Zk82pIbjHyIhEiBGJJBtqIdknWZUtGHmeh6JBx4jx7uX70PxswshzRSGFl1ohOm/5FJCVUAuCa99SMVLlo1t/4ZZCi7yLEsZMwBbGGXy5HXIheZeNpEFb/MoqN5kvHl+DqRhLB+f3C92Q4WxmDb5+pN8vZ0LKsoXHMTTEil9OKwQGBNGnNsxX4csH8dFDG6MaOaEaLePQVc1pl/Wn8NMCOyFX71K8/y9w+j9tS0LNLHwkf4rhdDVgq4YvfO4+vAyOa1oj3A/yAraT3NmX/KEftgJv/iaUigRwYB1ca++HZylLh+TyHWTU/VKXQ28gzvrxs15h24tZsf6dIO8blSAXSZnEhYUo2T/x20Jq6On7CDbivB1VVaOUeGlEgMaQ8sb5sVkGUqpFnWVKQhMfxmYvkNXuczHM6rhYL5Ws3g0izG3h6Tu/gC3/JwJY3cyolM48yRSP6VQtbuEd02z3XnoCpEnoMPVA9inQ6PWBDN1ILUSAJrKe6i8HKxRcvq23xvXG1G32eeVNCwsjf4+B9sOkzcPBP8j44IuWh1LOQcLA4XuMJkWphfuROr7Slmbv7dmvciRU0WCs6BLMH5+FSWeCdCZt6zPFfa4dVauYfKNA6IsiIW/7GyJq8ujtH6Dj1uiF
*/