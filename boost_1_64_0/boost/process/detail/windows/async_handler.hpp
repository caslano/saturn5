// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_

#include <boost/process/detail/windows/handler.hpp>
#include <type_traits>

namespace boost { namespace process { namespace detail { namespace windows {

struct require_io_context {};

struct async_handler : handler_base_ext, require_io_context
{
};

template<typename T>
struct is_async_handler :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<T&> :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<const T&> :  std::is_base_of<async_handler, T> {};

template<typename T>
struct does_require_io_context : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<T&> : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<const T&> : std::is_base_of<require_io_context, T> {};


}}}}

#endif /* BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_ */

/* async_handler.hpp
l6+NL0I9lr6WtJ2ZT+rKWPpYjaVhCf5+kblV6XYS3RjqI/2kykhzNsGyd7Ojmt4PAXkL406xU42mv+4ND9iOznj119iOVpY8vDI3BvLYHx6wFZ2x08ZGVXT+jI4rUexJU0PpxEXwjDxBdNqF0mkWwXai2Lo2vmCuVjrDIwL2ozf2EfvRqvb2o9Z8F0QE7EdvzLexHxWdLRHKNjRsZnjwueQWtquG/jYjwfr9RdM33vJ4SHt2KvvNH5NZ17HYcvzM3waDaVC8P9xKcKT4dddZbEJGmnacck6q8SvsJzl2tf1k1DMX2vC5kQXb8J3bcaEN32lTpm0RPzZl2u7wgCnTNoZ/eOZCH3iM05L2f8/8/fZ/H4T4ZuHHNv7rTPuN389fm729Ryi7jt/PfiOUfcipm33y5uMuqv/xRQO2bCpfb/Gp5rHv/HY7DXv7ltB2Gvb2Lf959hv2dhq/3e7F3o4ltP2Gvd1IaDsNe7uR39d+YwmBn8zJu2Au4Wr9t8zn8vf7BKf+W67h5e/z/6Dtx/eWfL6z/P0lYX/gPkjdrx0lpBAQ8fN/Iy8GPg3rw22wIdwOM+AOmAl3w75wD7wK7oVj4bOwEO6HM+ELcAF8ES6CL8G74MvwHngAroOvwo0q3RPwMNwK34C74RH4InwTHoRH4ZdwuFNdJ8u1PXLYlcC4kF9d9GJhC5gHW6r6tYLTYAa8E2bCZfByVb8ucBW8Am6AWap+3eEjsAd8DF4Jn4LZcBvso+rZD76jyjsFB8LP4CD4ObwUuqj0KBgOV8NYuAaWhWthFXgPrAXXwYbwPtgGrodtYTt4BWwPe8B0eCW8BvaBuXAUHALHwQI4BQ6Ft8BhcBEcDjfAEfABOBJuU/XbB0fDl2AhPA6LlE1MMfwGTlK2L1NgKrwW1oPXw4vgNNgYToeXwBtgO3gj7A5nwyvhHNgHzoX5cB4cBW+GU5V8LrwN3g1vh2vhEngfvAM+CW+Bz8P58A24AL4L74Sn4FL4JVwGv4HLYRjjZwVMgitheXg3rAPXwxNuWV/9xbXV8PfEt5msxdZ5r3QdtXQdtXQdtXQd9fdbR/0911CtfswuZa665r3SddTSX+mv9Ff6K/2V/kp//12/f/b6/+/17b9rbdb/kQWt/yOzWf9HFrz+r3Vdep3f1HXb2AQgD17/F1mY9u1XUtcbkFt0w/1l9erVJzNbfOEoeZTIO3Xpfnlmds/sLt2t+cdIXIf0jrjss9axjMgz0num9+5slccpuVgjWOTx6huDKoWWJ2i5pNDyRKsvQ0u7kvT3C01Zsr+/03t1NmVlzW8a6jzL+WXp3TKhJc/yIu/WUfkdRGZvP+FOMfS75jRIfg3CeddD8Vtk7R8LrFHbfkNP2yWMFr3H7GwmyMN27VnbFwyR+Ift7CV02hT9zcKxY4aOzh2WM4FlYGU30YP1gKWi94Z8Y2xTkn43V6/n9X+SeJ7oLeNpXJpazzsjsp9ddWn8H2j1AEey8ZYzW/tluk7y/MJr+qfJSC/MLR4eKPd6dDaLzg5vkA88/U5y4uPyHTdvsvOoO01kgXJ/knI78eZTC/wBHXReLWu61watX5eT9AsdEbyxYfctvnzqcErqMCfkt/iyn/DF/8EZZYx01lL76zXJ9zryiDcuYi+1I3QnDCKMJjRR69N3SNotbo/RyXm1s6wx2znK+MFZwajqqmBc6appLHB1NT5w3WOscHuNDmpdv4rkneV9lNwPEz4gfMNR6cGTUhKhOqEJYb4z0zjhrML30KYaG1yvOw+EJUqbOtOmT6VNN1q++cYQpFlDCopE5zZ0vhGdSV67bxg+SPyPEj/OkseICRMmkoHquwXoPCk6j3tDfXtwODo=
*/