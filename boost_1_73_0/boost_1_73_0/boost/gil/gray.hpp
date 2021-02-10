//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_GRAY_HPP
#define BOOST_GIL_GRAY_HPP

#include <boost/gil/utilities.hpp>
#include <boost/gil/detail/mp11.hpp>

namespace boost { namespace gil {

/// \ingroup ColorNameModel
/// \brief Gray
struct gray_color_t {};

/// \ingroup ColorSpaceModel
using gray_t = mp11::mp_list<gray_color_t>;

/// \ingroup LayoutModel
using gray_layout_t = layout<gray_t>;

}}  // namespace boost::gil

#endif


/* gray.hpp
mP1PY+B4yWlhl9vY8BBH+OuLgwMSDBTJAshhpLpfIK96YCsXG9ee3KPn/6sYACzZeGUw3SJJZiSiolj7hhI47l701e3tLYY0pIg+lzDGnW6FNdgoGCNkahDYbzln9wrpHzfwbJsj1Eyne8v5PCGKX9v/aJNt/KJXgw8j96QT3Av/iS5vQWs2GqEF7BsuiECacSMA4/tnz3//4XDLf1ZJUleR6mh/SWt+De3FB5M7O/RuzNd5giAmzm/b5CAL9J4WHr6UR9pENmNblSV6oTq5IXipEpCdl8MUDc35yRMlQXRbZU77tkNKPqn55ImJYYQhAWEkGZQ6ReJyfreD/QCvxyU2qBKKlnyXVqrwQoR28LvW4l4B3spudszm6S74cH/RJj/l4k5MwwLgQNigoDL8Wl0mo5jS3U+4AyBslguMawwzKuBsXfxBSVZwEpxDjKVOMaCtS74OuOyppJTjFg7ago27SvEmzq/nLUko7xZrSMW4ityYfNbJ8GhqnwYYTMloZNxySQK5UrKSWNQlUevVY0rM9eIx0ctomnQTT5ec5F5WRcJj9FfmjXisRb2PqZ8DwGxacOZEP4IjXlymwKNQ3Hzt4snTRC1Y8ok7UZTu5COFz7fihAd0oOhZUGc/KbDRthek5WlikR3g18O9
*/