// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_TYPE_NAME_HPP
#define BOOST_HISTOGRAM_DETAIL_TYPE_NAME_HPP

#include <boost/core/typeinfo.hpp>
#include <boost/type.hpp>
#include <string>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
std::string type_name_impl(boost::type<T>) {
  return boost::core::demangled_name(BOOST_CORE_TYPEID(T));
}

template <class T>
std::string type_name_impl(boost::type<const T>) {
  return type_name_impl(boost::type<T>{}) + " const";
}

template <class T>
std::string type_name_impl(boost::type<T&>) {
  return type_name_impl(boost::type<T>{}) + " &";
}

template <class T>
std::string type_name_impl(boost::type<T&&>) {
  return type_name_impl(boost::type<T>{}) + " &&";
}

template <class T>
std::string type_name() {
  return type_name_impl(boost::type<T>{});
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* type_name.hpp
sSc8NIHGW3jjt+UH/aIVPjx5UtoXfw73jKE75mbhnpk7bfAh3LPGpq6O4Z495PypAdxzfvGNI9fhnv/IpKPPNNXxGQ4uQmZ6iGeY0304V/67/JhRianqzDt4svlHPNmcIZp4sjn4OE02B99/e9BxNYowXuLzn3N5/vNtRc5/EmmY/yS6jPlPpq3YyqQV25myYgcTVuxkuopdTFZxlevkx5p33HxXvPxuecz+zUnl4ektj4vfPk4eN7w6oFLKY/lvb3iK5HErnJpJHuMOTPoZyeP2awdPJnncHej3MMnj0a21o0gew1p2T9flkU7INN8Zl4froW55fG/ZCeTxyu/OUB7y/G1HZEEGFkA1mtVlhbVvx/0BGjDdrxK9Vx5VeMdyHBT2ttnwB0hMMBoJbCtLPhkqzsHtE6HiXNw+Hioeh5snVJyHmztUnI/bhaHiy3AbDX+A4svxkF7hDxVfoT1iprnhiqaSQBJv8Hg7iC2pgkNA7WHsFnqNCYUeTg9ec5t+YLN68FfYIztmu9OSLLcgFo4/Rbxmsa4YLlSh0ndoLa89VPou3S2h0mMhH472r4p2JOd13fr3+BnOwiai1Al+T3eDSSd1N5h0UneDSSd1N5h0AncD6W0APwMxyaHHOvTY8/XYj4XGDxWTnHqsU48dpscOD40fISa59FiXHnuB4cgw0nBkGPW/Sbou1/+Al8YHdyXYw5aDuj0k0wJ7SHbFsIdsW4qtbFqK7WxZih1sWIqdbFeKXWRWYA/T39senpG/SHrcX8RD/iLpYkKA/UU8ur9Ixon8Rd46oCT4iwRO4C/yAlKQv0hGgr9IRlNhINFf5IkDSt/8RTLCXw8A5tIDytnzF/kln3/2i+72os7zSBKfI0X7X6PleAw3cgJb/oKt7od2BFnKxFR7uQg4eI6g1MKD9qVWGN6FZh4CKXUKrwufyRPx6Zkfxicrf4bDHQX7wcPirwbA8eFve57FnebShsOHgFYYRXfb4UXAi4WS4TTLD0rqfpxtEJaZ4De6+nx8qW/Ad2LwUJtocANudHUK1oE20BCNe426FuLFRIPYFfnOg59dcSWdiIFRkMbo6jSxHiNp6k51LZDCYZbuY9HVA5U9yFAEz4oGfJA3iXYlCmwYQ3nI2ykRE2t01AixFkZsoVhzqI2RAnZFgJ5P3+GEGvTMS34U9xVdOg+IOYHYekZN2QbUEI/ngYyQw93ICG3siRDwBlNPidQJuLVY51a+5NYaGo1zN6hrCZ3Wt1c/ST7f3egcZXQgwPQ4SpDwfqCEZG5g7gYq6n6ly8AMG5DrWAElIJa6X2yO4wUKCDUglrrfQK0JB90t09nWqm441IaJ8KZuSea7m1AoBhwIv59tf7JDoIQE/Hqzi3ADTjRUiISEoUrFJiKYeUq2ASlObSAFFOsYVxanG4xEUenuJkxnra2JTq+vyFWMQfg9AgUQdkAMCIJ3CO3Gz642Mn4YXoQQMyjE3Qj8kCujJxszTomlwcE1hsY9wecQQr5rRBXQa5FchPISpizhb3UN6ZrGe1q0mWjcvBlYigbGEzcdx0yW75vuBnDP3hOp9PdCitYUHydaGkVtE6S3wJDxu5uCo5KLrSRhYgX83wGZ8GOZRu5/5I4rvkkiZtkCT7vBP+KYBv41qnuZrTj6dDTdIeUeeJ6kuh6Po70XjvcaOMYl7SCF0jn4QPss16PQR1RZ9lNoAsZSB5sMHNOJf1DbQ+4g8G1/H/p3Asl+W5csTXSwXFl11jDvMpl3TWpj5FsP/jqF1/cR+0jOhh66jyHNtm4+utzAkwyLEu22KZ5TIyYPpST8DItt2BaqucTMBsYOiDYQx4Cdh+RKsxpAo6beNL32PEI=
*/