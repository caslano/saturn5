// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_WRITE_HPP_INCLUDED
#define BOOST_IOSTREAMS_WRITE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/ios.hpp>  // streamsize.
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T> 
struct write_device_impl;

template<typename T> 
struct write_filter_impl;

} // End namespace detail.

template<typename T>
bool put(T& t, typename char_type_of<T>::type c)
{ return detail::write_device_impl<T>::put(detail::unwrap(t), c); }

template<typename T>
inline std::streamsize write
    (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
{ return detail::write_device_impl<T>::write(detail::unwrap(t), s, n); }

template<typename T, typename Sink>
inline std::streamsize
write( T& t, Sink& snk, const typename char_type_of<T>::type* s, 
       std::streamsize n )
{ return detail::write_filter_impl<T>::write(detail::unwrap(t), snk, s, n); }

namespace detail {

//------------------Definition of write_device_impl---------------------------//

template<typename T>
struct write_device_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          write_device_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, ostream_tag, streambuf_tag, output
              >::type
          >
      >::type
    { };

template<>
struct write_device_impl<ostream_tag> {
    template<typename T>
    static bool put(T& t, typename char_type_of<T>::type c)
    {
        typedef typename char_type_of<T>::type          char_type;
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
        return !traits_type::eq_int_type( t.rdbuf()->sputc(c),
                                          traits_type::eof() );
    }

    template<typename T>
    static std::streamsize write
        (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
    { return t.rdbuf()->sputn(s, n); }
};

template<>
struct write_device_impl<streambuf_tag> {
    template<typename T>
    static bool put(T& t, typename char_type_of<T>::type c)
    {
        typedef typename char_type_of<T>::type          char_type;
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
        return !traits_type::eq_int_type(t.sputc(c), traits_type::eof());
    }

    template<typename T>
    static std::streamsize write
        (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
    { return t.sputn(s, n); }
};

template<>
struct write_device_impl<output> {
    template<typename T>
    static bool put(T& t, typename char_type_of<T>::type c)
    { return t.write(&c, 1) == 1; }

    template<typename T>
    static std::streamsize
    write(T& t, const typename char_type_of<T>::type* s, std::streamsize n)
    { return t.write(s, n); }
};

//------------------Definition of write_filter_impl---------------------------//

template<typename T>
struct write_filter_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          write_filter_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, multichar_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct write_filter_impl<multichar_tag> {
    template<typename T, typename Sink>
    static std::streamsize
    write( T& t, Sink& snk, const typename char_type_of<T>::type* s,
           std::streamsize n )
    { return t.write(snk, s, n); }
};

template<>
struct write_filter_impl<any_tag> {
    template<typename T, typename Sink>
    static std::streamsize
    write( T& t, Sink& snk, const typename char_type_of<T>::type* s,
           std::streamsize n )
    {
        for (std::streamsize off = 0; off < n; ++off)
            if (!t.put(snk, s[off]))
                return off;
        return n;
    }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_WRITE_HPP_INCLUDED

/* write.hpp
NuUy8zFxZthPofmlfL38Tiche+Ir3iedpO/T0srDKWvyh7vKn9sWkm7cVLpx022wqfS5c5DrvVVfnx5qHf0HNW33nt+0aD76+MLlGweOSz4csfLK0OvrH2hju8cWxxRMafJhr68e77Q1MWvwtKrbFxv0jO3+XlytYXeeuGraqzW++GSmP+/5UOvoq26vrbbK15J7b3vz452pqb/dOSp/+jW/P1z1/QdV3bfxS9mnM8/pVn2OeaAqh7x6V3/925G3jlvaauwd8Z2iDlb9OwbmueFQc8naHPBOmcs1rMMeLnPAI2Atbd1/CpIr4cIlnAdJkHBttHXei8qJ/1yJf4jEP1SLf3058XfQ/BU58Rv89dP8FZcTX1/N337xF1tufBy7Ql+3h+sP2RX6ut01f6niL7aC+EaIv3oGfwP0+inH30DNX6HBnym/RQZ/pvQVi7+kCtJ3xODPlD76COKv/PSlOv7KSV++87yAZ4u/GLVCp3Ttgs1EGAmTYB1YF9aDKdp+hBRYH7aDDWBneCrsIf56ytqHvvKb8TPX5uCS5qzdRnYhh5CYFmEh9gtAzq2G3ZifT0OC5+uPQHvOPv48wj0Teg9BWgX7CE7AmOHEyd9thlduT8E2/t6PNB3BeaQAt2lwLcyHwfsMimSvQTHsCY9AZ89B8sjQ+w7yg/YebITPIaY9CJHnl+xDaAH7IM5+hAbPlt2TkI/7OqR/b87Bng185e5RyJX1CFuQd5B1tjthNsI06unEqPLtJyaPJl7bDY5AlvThmqRrNZzGb1nbwAfjcEOcfQ1bRjtrHQiHf39f0gJTLih/n8N+ba9DwpjS/Q7jYS7pXQTXI/r+h3d+wh6INNzykXXINiTUnojDuDn7IpoieasoG1lvsSpozcX6NGevBGH5+yASvGfCupA0wxZwEJIu+ycWwXXI/n6kgXzeh+xCDiGRLcOsNsgIJA9Zi2xD9iEnkQatwqw+SAayBNmA7EIOt6pe91F9VB/VR/Xxn3z4kexfYf4/KzNvWskOgJ+/B+Ap2zaCFRdgs26Wh7zAmbAv40DrN5eMPedMsC+fy8f78tT4SFa8sv+fi1d3/fpzyu8AT3eP0QabxOXRxivz3TX596lz6Z7RnijTOA5hg79Pj8U/5UfWxqvzQzz9PR7D2I4pPHmZb/5WgO43Vw3g8NVCuVYt6N9in+9MuTeQ+Mrag/FtxQ+jWl7+q+36ycrJmKDGtF07NX9Q11psTcCfY/cijLD8q8qJxNnXd/1HqWt/je9GZfx3YSwqRmyjXEJmtsaXyI665Uj53xI411kbH7G17Np4WwcSRQfEPoaMAefL2JWMc7l1RXYcNyl/xq5cHdznKzunOdbelF2ig6ierYRqoleV+4WEoh7V4nyDvhEucAx0TyW+MenkzY47UeLW07jIX9ZG4SDSmBKQRmXTRqWxfXL5aUwJSuP3VUgjcbtp1G3b7Jcu4zkSaAAyBL/pD6s05szKcG7m+bZltJyMTKtS5Un4oLmk3AyaEuP9Kn61sV+8ovrmsVfxH+J7GrVgjjrfljsu3P126NOyV2R3fMVz6oZ6DZx/krwk6XqrpVkv35dl7j1BLlAHOY/y3WEo38xsVb6V0gXCa+P75ZYvfgP15pkq7K/S9EYf45cykLkoyesWmfsf4hQm0t/ec7XVHeOfOGtqzpwJeTkTsjJK8tlF6RHOuq1J5d88vk9cbr753gkHMWl2jdao86db9cirrdpXE2FPpLA2+xbswZNKjLs7ebfTlihp0+cyRkdKXUqg2nJf99ns5FPZwK1UPfbZXHVbVaa60eshXeaGG3ppF2E9OMCe9yyth8lZcwPtjl51ulqvNV3NKctz9kPlfw0=
*/