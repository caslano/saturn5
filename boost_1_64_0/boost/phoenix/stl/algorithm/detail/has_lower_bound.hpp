// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_lower_bound.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_LOWER_BOUND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_LOWER_BOUND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_lower_bound
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
        >
    {
    };
}

#endif

/* has_lower_bound.hpp
OdgSp2MUzsSeOAsn4IOYhrloxIcwFx/GOZiHEi/3PTmO91HJdyF642Oq5YrKWO4pWS4fvfFp9X4iy/npLDdOlrsf78LxeBFjSeZ7gFiHLHcn9pblFsl+sRgD8AkMxicxDJ/CuzEfI/BpvIjFpBhZ72U53tY09znnxXG3MuvF0xiAZzAEz2JHPIfd8UfsjedxGl7Ax/AirsCfcT1ewl14GY/gL3gKf8XK5H8F6+JVbI7XsB+WYBz+jkasRPyL0Q3XYlXci3fgUbwTf0IPVLZXsePtNUaOM2PRG8ehsr3KWC5elpuA3piA5uOa3LsDtXWOa5fk8/kyeuIvGIi/Yi28gub8Sd86zn+65D9D8p+pyj9Wlmuik3+GLGdEP5yGwZiJjTBLVf68MvK/JuUoQW/8HZX9SpYL1VlusCw3BGviULTEfbiMevtRljuPnvhPDMQLWAt/UvKXe0Wgmk7+90r5R6IHjlKV1/c7x+VNleUmozdOUdV3pCwXohN3X1muH3pif/TBARiEA9XbrYz1dJf1xMh6eqAP9sQg7IXK54WsJ1KnHEmynAEjMBkv4kJSgSz3oixXHXNluUZyfGqModgEm+Pd2AabYVdsjn0xAu/FFpiELTEZW2EORuKj2BqfwyhchW2QeOjSL/dHoJscn0zHoTUSj4fE44mhWA3D0BtbY3Xsib44GP1wJPrjaAzASRiIuRiED2EwPoU18QWshZsxFLdiHfwQ6+LfsT7+geF4EQtJh0/KdpS4A/n3Bol7uIwpEYcN8V5shiOxJ47CATgGR+JYTMRxaMT7cS6Ox6cxHp/HCbgVE3A/TsSDaMAzmIxXcRL6EFcK+uFkDMQpKGPqy30a5EUabTemfjNph83REyOwCbbE5hiJbbA1dscoHInROBbboDJ2fxn55Eo+syWfh5B8mEk++IjkM1fymSf5LJB8HlX2B7l/AuvpnXfJcaU/1sEBqIwJI8vVJY22G8NliMQ3VOIbhj4YizVxONbGEWhZX76sL0xnfe1lfR1kfR3RBzthTeyMdbGLan1Fsr48nfV5yfLVMQrvwnboj4kYgLkYiObvu3I/AVKPrM/2+257abfdsB52x+YYg62xB3bFnjgMe+EI7I3K+eEZx8fX1rIdotAbo/EiziRdkOUel+W8MU2WC5Z6C8G7sCaGYy3shqHYE+tif6yHcRiGyRiOM7EBzsNG+Bg2RvP5l1z7xwid8681kv8r6Imvog++hjVxLTbC17EZrsOLuJZULOu9Luv1x5Wy3u2y3kL0xzexJb6FnXEH3o+7MBXfxnn4N1yIe/BJfAdfwL24Dd/FT/E9/Az34fe4H3/GD/AqHsIS/AilHrhm77geNkq8f0VPLEAf3IQ18Q1shJuxGW5RjgMkWe9kneOAj5u0YwxEX2yGftgS/XEUBuL9WAOTsB4mYxjK7xByrZz3kIx2v0PEVba8T65nY02d3ytOV7G+L1Le53eD9cWecy5fo5Pvy3fifYWkAnnfTyT7z6H9cn5/AAPxIDbHD7E1HsJe+BEm4GFMwY/xIfwEn8Qj+Gc8ii/iMdyMn+Ob+AW+iyfwEH6F3+LX+D1+g2exGH/Eb1Xl5HqnUr9n7MrZ37odOCl07n1hvE/qjXHlbN9HGaWdyzVATNRp5yXSzq9jJ6wk5xVueD9WxnisgglYFc3PWJLrfHL9b7TdM5YaSDtvgoHYFEOxGd6NzTESW2J3bIUjsTVOwWicjW1wEbbDJdgeV2EHXIsdcTt2wj3YGT/ALvgFdsW/Yzc8j93xd4xBD4LvgX7YE8OwFzbH3tgG+2AM9sVB2A/jsD9OwAE4BQdiNg7Ch3Aw5uEQfAGH4jochpswAXfhRNyHiXg=
*/