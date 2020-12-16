//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_READ_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_READ_HPP

#define BOOST_GIL_EXTENSION_IO_PNG_READ_ENABLED // TODO: Document, explain, review

#include <boost/gil/extension/io/png/tags.hpp>
#include <boost/gil/extension/io/png/detail/read.hpp>
#include <boost/gil/extension/io/png/detail/scanline_read.hpp>
#include <boost/gil/extension/io/png/detail/supported_types.hpp>

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
GKtV/VMkbM9u9xN/AoY1YPQ/CcX0w9CAA9u/HAa2lyjYvlBr2Naw2tpA95CzJq/rn4B5NQz/p2EdpgkHpi/VUt6+XGuYVltNbWHp8JF9h29dxz4NfyPVVOXmVrr2NXsu3gJ/MLwnrsrss9Y5FKlnS7+SwqHqXN7r2hpaibe0xDfXX+a1fXN1rNlVps4zdRLtLn/tuRnPJdXuivN5SeLqz9PviaMsL7cooH+7W8cqC4jzXNd6Dhbl6W3q221ygoX5zn0jwIL+/SV25FNv28ged+5B5cdSHgpVjRNjPWvjNrHGCJUX6+80o8yvtWlhtdH6aMVzUUGONVunrA1lpXNKnDuc3rRiN5TxBb4z965WG1+xX79Dr7sqw6Cy223nvR7h92JVX8wR+gyPSZCN3Nkq3/5bGi5HRPL9JqRlameMsg8qBZ/dlY00Qp1xLw7fUhjhXm+o0F9QxhxLLP5VZ9TfjsIjNb6rOLT27dVe8aHurEqNnB7KHBR2tqOUR+6nan+I+6n+BJzsc4eqr6dFp/FxXC5KHEincZUDPa0g02enK66W4znLX+zDbSKVXE5xQMvjnB6GQlZpZmVxbmmRK59wI6fPcHVIGy9G5cBOs23jnCJ1oFqj63hEUE4evSNq/JAv8FXfxH+g+yYReIzi81wdIO5idY68T/X7sPx8AZlTFCV/dR17fuLY/B9pY9ZXY6rkAckkdbfuNXCGddXUnIv6T8499VB9pNnpIOJS1AsOkUWvtPur/t1BZjWfcod1HsrK++yrfk/OJ7Yv7MKaRftKPu/U4WT8OdqPGsP4J2BtyfdP21flJEj1VKN9W7o7+Rx4nlkaTOEOQl9QfVqo53sgw5C/JGq9TifhlO16eX1Vnux8sRtOd+7whqon0aOrhdMHPKIIM63APuBoc5tW30xw311j23FDVx5y2rIWxddVR0WdfrraeHYqHHnfIwybNDskQxA9s5L088UKCBov97RgVIt2vcP92ZNTtc5Yfew+otf1Db+XWZ4bcnrW62Otd6PVO3d+TfSX9I9VxRMsq8ipG6zwYA+swXaoKg9TeMhpPwK55MublYnGddaVIM7QzpxGCd+PukWYfgeY6j+zjM891bFWvT5dr7eu+fRXne2dVDW3gHrVqZuu1anXnDUV8m2RtRr7q0ptrUWOnM6YkxNXkm/1EKn/DD4K2N88J/iD9m1Plfb3gR1gnc81Xt/1L8ihKXLYuzhHc/o2I859scahmzhn779UOrCG+4aRQoTi7A7V30p3fq3e26Dk5Fc8a3mB7JsZq86b25iyeM4piwmXpfjBgv59cSuLXsJMkuXPFae8I3wIGnQ5QZnDR047vkUO5vrLiK9VZoN9pYTD/XzT3uIX65MG9g7UPT3fangaXMN6ZzrfcmsyNzPRvlChhrPT4/yhPOfjWXf5iKhdhO2knoZ+NybRPJX3+3vmGW0I2lJnwdh61uyLmvW3Y19k5FRUg2ezKpslUuW800qr81keocsOaldVb924W2IzjWZXd3T4SHtdk3+dnXr99ao5d41i84xS33vv0nDYIzp+FKNFB/ugaro+vbAy5M9zAOfMQbOJLPBRDl1Y+e7r7rHsgf8wXXTX+cw+1y9hGWTn3Kq632KKssl+0OOw/yZ5EdUG+Sfgbd9HpeSH4/9quV/2tw/Hfl9Teyw/t686X38i6721Zbg+vB9pygF1pq6jVM/d+BvltLfb/tQ+3PZ31fY97ezCPvW38i/0uTjfzfaV8Fw8HcLvf6LaRd+LjnK/Du/U7WCv2e6vHn+LigGo/tWzuvvflStltfp7RrXvNdkNpJ/IXJ9wzbURdfrzGzHhuZ8QU32NfV25b2I6VMG7r1bfV8E=
*/