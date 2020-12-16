//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_INTERMODULE_SINGLETON_HPP
#define BOOST_INTERPROCESS_INTERMODULE_SINGLETON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#ifdef BOOST_INTERPROCESS_WINDOWS
   #include <boost/interprocess/detail/windows_intermodule_singleton.hpp>
#else
   #include <boost/interprocess/detail/portable_intermodule_singleton.hpp>
#endif

namespace boost{
namespace interprocess{
namespace ipcdetail{

//Now this class is a singleton, initializing the singleton in
//the first get() function call if LazyInit is false. If true
//then the singleton will be initialized when loading the module.
template<typename C, bool LazyInit = true, bool Phoenix = false>
class intermodule_singleton
   #ifdef BOOST_INTERPROCESS_WINDOWS
   : public windows_intermodule_singleton<C, LazyInit, Phoenix>
   #else
   : public portable_intermodule_singleton<C, LazyInit, Phoenix>
   #endif
{};

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif

/* intermodule_singleton.hpp
ry8fNnnZ7TjuIx7O5tVgHoZTfhapeD2QyPvIj5kcDsGU58cNvFMfeMLQUB9wEX/Sizcr/Ez7KYk7LlRHqwBnJdWZo6eZw/rxlIGfP5q8LAOlibafNXhlnOvkOeYwGvvzeROzmlQ++azR5OwSdcdCq9Xk8evFTrx8YQHrXvoNnfh8j9S9/Fu61raqP7zi08EuGbtloxLtvOrl9asnOD1p57Wgjoxwv3o9yJvFQ80bHTScFGre7KQp1ts1vlfzltK0oOdVsf28LbF2TY5EmO93NG54Spf/3U68zjrq3uug09kn3fta16lmsJwfaF1IzZCtD7WmU+1gGT8K06EhsvNxB14XkXSfdNRxcqz7VOs61BI/J2UdD4LYhz73YrIX0fNS5LKD+iE1le9LExdp8UZTOYd9FeD1uaCvPZw+p/ONwmVzobN+0ua3khd34WHmI5Zsfic5kRbuhCX8ew+u99j/oPDt4XOypP2RsEw/HmzQexJ/8uLlBvvyZ4mjX6gefpEYDprqjSXiGLczhtsRqSyxcQ0db/yU5ewyOXFHUyyqmBtHc4H3AoyrOIdOy6NGfzNqvDDed/Z+fL9G+xNtTBDKt90mdgF+VhumoYt55CcK8K4nnxMHeSMN8v0kSlOpF/hs/qQeTNffZB5cn8WeXOGcTKGk1o5TKC6smPyMVmuC2WR/TuXTiC2p8Axgc1nXU/t5zCPFnSaUw0aE/LR+HjeX6X3F00meNgTj8QJZvukVp1+so/sw+W0GU0OvIsB0Z0R8eMBKpuEe5FBWndzkdGcK4eW9sJmDnOc+4izEbziUz1rwjV7+bC75Y9ZQzmrIvX6z+XjBqu/G+jgdk/rtHAafX3M4FU+qs8QV8ZRC+m3OgA4HK7i+hUs6tjVXQGOeOwYd25o7VOdNb56gBtoPi+Q5w6BGDIyed3bMF65RZ7DnD/C4gxtF0sYCIZp2zRIbONDGgkHeleVRZxADGt4RyWVZOMDTjlZz3+YihqbQqledoui5ZH9RzYm791DV8oqB+MUCvFz5k+3FTb5YFXxB9sclfJy2TfW+ZEde/Fx2afV9Wa9O50GeUezAazuU196ADtsGprFUgBN14WytziYGedhVz9+W1Zz8zLf5OW86oxjUqFzKci7n1QR83ad5Y38UxV3ez4nmWIFGwLZX+JWx8wCTq6riOL333pGuNMmGQGjCZneSLEl2l51NSGjD7MzbzZDZmWHeTEiC0hQERQURpUmVjiIqICgiShcURKVJFwQUQQTs4n3nnHvPuffcWf0+vi/s//d/99363p13m+StpsrDAzry7M/JXTaOB3q+VJXpQR059T4onE/4PhWfgztyv49ziPPhEkqa5g/P425mXtueFujuIuI9mtMSOxrvFnwsqPM5n6n8mR7lOp9n+D6VPzOjXIfTp330QqXxccm5TQCbpRjvdTBbMzrgH/kcySPtqV9y156QDTCTSyahHQ1qxisgqa0dFnjGk3GYPoCj/DSuLjzj0FDw3nnW4TpY0kPXDPvM7as219fdnjzzWIdIynQcLpnpZ3Bb4TGO+aEn3p4gvAVRrz9mcoTydG5XRwpvvTTi1fGjFPPPtTw6wusN+CoM/Bifq3dOQfOkJvixPld1uqg41+kRxbhOl3ym6mzZ51Rn8dpEMu/ZTWP/zO2TGcptjHU7R6NYarWLVdzYBzwLtQcCKLYS13etKA/vDXKcZlTlMfxFnXihXK9RHKodPSZrqX6NT+ip4D6FFN+a9rZTQ7P41jVbBuHQtQ3J8RnAZ9BKhm0ftwygtDYV18+GVHpaTdOeUW/5es0AuGdb6Eu8NkVrP5lTQjAdJ4A+PHtgRiE/PDCE2+hRPJcEDD+bVOs=
*/