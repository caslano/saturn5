// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_map_view.hpp
/// \brief Unconstrained view of a side of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a side of a bimap.

template< class Tag, class BimapType>
class unconstrained_map_view
{
    public:
    template< class T >
    unconstrained_map_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
    typedef void reference;
    typedef void const_reference;
    typedef void info_type;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP


/* unconstrained_map_view.hpp
7yEOwK/3FsPpvHi247zKhGWzjUjbSgwqlXKQVTXk5AHD01FCQimuRwYstYGFyefrlwxdRcNWsaA+fGZHd2xvDoSGgVYAehKpQG1Gg15XSbX+xLQvyXdCxM8XzYQwLszT67NptmLRA/wckzz6KUtX8NMl7l6hn7UJZctSpBTo4hc46CFTKUWuioePnNHNHpojDgt6tuJPAsA0Ly4YHuPtRxr6VMA9HTrhCPn3Q2urN2WtD4fL6rlVKjMsiOt2YiwiMladucG7jxK7YR5WG9Bh/2xQCh/m/KyqZoUQdVTzif0lLL9x4rEeIP6kgZ+1hllCS/hNa3mZ1I2L9QG55QRh8uiXR71B+8HTgvmwInJiED3tmBdTAZ21S1wdFbKEgGGWmqQ3YUidiMJXl+bXYZ5pPJ3W3DcLD7WWBFHxtkdfvmDNl0HxnZNalsanoNMAxmxBlxt6agOw3yHHU6RpWLYize6oXgasnmfnLr4eWjATD5fy89hslToJmgdu8MYqVG3N6ThNWtmEmnOGUqxnoxh0ghS6qDFXo2a41GM2/YEVnGKb7nrby6PrquhA8g==
*/