//
// Copyright 2013 Christian Henning
// Copyright 2012 Olivier Tournaire
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_READ_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_READ_HPP

#include <boost/gil/extension/io/raw/tags.hpp>
#include <boost/gil/extension/io/raw/detail/supported_types.hpp>
#include <boost/gil/extension/io/raw/detail/read.hpp>

#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/make_backend.hpp>
#include <boost/gil/io/make_dynamic_image_reader.hpp>
#include <boost/gil/io/make_reader.hpp>
#include <boost/gil/io/make_scanline_reader.hpp>
#include <boost/gil/io/read_and_convert_image.hpp>
#include <boost/gil/io/read_and_convert_view.hpp>
#include <boost/gil/io/read_image.hpp>
#include <boost/gil/io/read_image_info.hpp>
#include <boost/gil/io/read_view.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>

#endif

/* read.hpp
uBTcGZO9mXO/sCouF+8Yl2eRxxmDEnLDY+xDPY1v9oDIJtNFfnIubd+KMm7G3pfy7Hvo0XzKWiny85/EpezzyNLsmJxxO3XBt+kpC+YO5JP575WamCx6LiZvM7e9TLtueyIh1yBbp53AHIduL0EmSn8v8l4M/+NQfJGt6Iv9sc9r8X8Oxq9kjnsY/erdErt7I88XIuvxuLz8fEw+F4NWn5CTsaO7PRiTW8DaHsGeNKB7k5hnsXULroiL9BHfeyYhX8HvKEfWL7gCuzoOmZzHXHOYyCU7oad7IMMnJWT1m4zXT/HnjqOsRegjuvQyvsfdxzF+jPnmX2D8/pCQntPpH/rj0WLmcXypFPbiC/Tp7i34FOjLC/sy36Vo+4Fx2f8o5oWmmDx0C3zbMydT1kVLqPcLzEWPxeX540UeejchRdi1PebE5Uvfxo/7Orbpp3GpPBgfZFv6ZxZzHPPBAsb3rZkJGUGZo5Gji48Qie1JmcfjY+5IXb8ak+XYooexT1dWxqTshph0o5N3PYxP+Qp+w7SYBPcNnLoe/3kePC/TL+C37oU9HolNQydHfgvflXl455fQ+zuYC1+OyQH0xd0/or6bx2X0YfgyF9GmW0XueJexWoMNwseZc6jISXsjsz+MyVn4Ob1fQ19o356zGfvviNzMPFeyW1zuHI1f1IJ8XJmQg5bGpGsE9vKLMbnqPMbjA/yxzZGlwfhEq/HT7mePlXoWY/c/M4V5nDL+iE1cehl91sLcPJ0+eigmwzdBnz+OyTd+ybyzBf7Ie4wnfdOBj7fVY4w/svUc+axYRZ+9E5cn4qyFviYyA/2p3I6+mIH9Y0649Bx8sr2Q398iZ+hV82/QQ2zLrV3ILf12xBcYD2T29heRB3yRWzgMdA5+7eH0792Px6QWO/vpL8Slk7x3nxmTysOxK+cxp/6ZfsE363gAv7otLvswP5xehR4sYL20A7KBfViOnKxjvNrQ65IE/c4c9gb9cvaurItIT5OeJ22dSshfkLfBlyDjjMF5yOM7n8FHwJdrv5ln0ZlTT4nLX5jXrrgH/+LLCfnZXNYexJznL8IfxTd86iLqN4v54SL8h7sS8odp+CVvYWPxQ4/YH5/0EmxteUJmX4k80L/PLojJS/NFbrwZvx7f9PzX0d/x+GAl9Ekz6yl09ZRj0KM98Tc74nLuV6nfBOzIi4wTNuPBYuQX+/5T5qiJk9Dza+JSdDVrFebslYcwbzImM/A/P/kd7PTR9PnJ/E1/vLIH8zz+SO199AHricPWYwNHM8/cjW+DTZyLXh7PXDBhBX13N/4rPtaW6FXD+wmpeh09w17eSvsOOjsuQ3/Fv/Ehd6XMc66n76/Gp76UOmD7f0RfTRmNXT8d2diPsVmUkJno7ogr8CfoswcqEnIE9q27BTlEJ0/cFB5k4t2VzHHI5IPXohPTWXOhoy+i6+X4WoO+KvJn5rFpQ5DB25FN6h+LoSfXI8PI6PtnMkfgH+wRjN8FrINGJaQJPd9vFs8yR552PjaOMVhKPy4mbX13UQwxRQlE5g2nP9/H15CPP0b0+X8ioMjoMVHaT1iH8Mt/9n7zmOCLkUEsvc9hsBNqMthYsPlC3pLBxhm+B/fMYOMN9pbCdjHYxeUZrATss4KPsGkGm26wT2yWwUoNNlHxVRjsWoXNA0N0pTGRwSrBngTbW9V5gcH2VNgiMJZG8mOFLTZlfEWVsdQ8O0zxHWD49lZ8DQYrVtgh5tky9WwX2JIY61GFHWeevUE9e4rBUEOLnQWGaZcC9ewlYD8BO1ZhV4G9BHaQwn4JxlJAKhV2v6lfrcIeNX36B4X9FgyTLnMU9nuwY8CqVf3eAnsQrDyhxm1w1I4=
*/