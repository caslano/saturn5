// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_MULTI_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_MULTI_POINT_HPP

#include <memory>
#include <vector>

#include <boost/concept/requires.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost { namespace geometry
{

namespace model
{


/*!
\brief multi_point, a collection of points
\ingroup geometries
\tparam Point \tparam_point
\tparam Container \tparam_container
\tparam Allocator \tparam_allocator
\details Multipoint can be used to group points belonging to each other,
        e.g. a constellation, or the result set of an intersection

\qbk{[include reference/geometries/multi_point.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_multi_point MultiPoint Concept]
}
*/
template
<
    typename Point,
    template<typename, typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class multi_point : public Container<Point, Allocator<Point> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef Container<Point, Allocator<Point> > base_type;

public :
    /// \constructor_default{multi_point}
    inline multi_point()
        : base_type()
    {}

    /// \constructor_begin_end{multi_point}
    template <typename Iterator>
    inline multi_point(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    /// \constructor_initializer_list{multi_point}
    inline multi_point(std::initializer_list<Point> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it shoudl be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{multi_point}
//    inline multi_point & operator=(std::initializer_list<Point> l)
//    {
//        base_type::assign(l.begin(), l.end());
//        return *this;
//    }
//#endif

#endif
};

} // namespace model


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template
<
    typename Point,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct tag< model::multi_point<Point, Container, Allocator> >
{
    typedef multi_point_tag type;
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_MULTI_POINT_HPP

/* multi_point.hpp
4eNcfVxzjdx1UGXE3DfWq1bAs39simPQzWd1Rd/r1mYdV+grdmm74561kScdMCffnSdm9lkbrITw8wTUL+eb99g4Vc75d+ZWmf/T1dypOi6RI/oOWrfR4sS7bhW483Md5f0ua5pV37FH6hQ5sMszTztH9M1F7hdW91hWaD3qVNGzUHYjNbQ6uufq9BH13jKjacbVM8nD48kDLe29sgXmppsyCTG007G00/6osPBqWl8qdlS1KoXvddKzg3nOoc1yytY+GceQvKTjeE7/0c0rofWloq5JquqD3blaTeti37pzvrAdvZOnNs8CnjJpxPXsSPlbEqxkHtcyOl7MTNI879iRXXr+dvW0c9udBSKPLHlnr7YzM+V9bc3njvlmoj+uKhrJ06ND5x+59d5A6p14HRt8NnK8d0qRuqdNSpHEl0/S4FCENHi/RBqE7lzBz6jjZ8/+V/yFGv4qdkbKvq9sh//NU0nPo+yB3uQrw+M+P0+GLiLOM2hcq5kst7w3EXm/xbq9UucYLlZz3namscj7rPI6Lze9kjGXn+f9dm0gep5H1vW4rj1VSpQ3p0yOkfcNqEP97vrZNaI2QMz8XMHoHje9wJPW/eR9qsqMdorsl3K5gHzbmfhrKX3nAQkxspExEGTjONOUgaRI4y0zxXxzd53EgyL3tKKs7LAxmLFGHVPVQmMwanY59qVgQ9BqjxnvPFgseSuOZwf+eeC/6INHGpNvVWJMPlQfkB6o5+eVOCfua8sS6pzX09pv7TjHm5ec61qcHkvkvS39xMwun7nv5B4ezWNqV2oojXVvi/P9dNNc+2zlROsCp12Wuu6NCvY4w5SUEA+dU7scTDk8V9dnTZ8esZ1u76w7OWIb/E3b6Y80/IXzwsJffDt5pL67mmnl7oneK/IDvtC+6dA+ZKc9f32+9PFkPiLS/mqnbYhdYI+9x4r97lqpqVPGhspXodhVxZRAVaP/LWp7qSljQuZ073g1NXdC/PmLlYaea3nu4dmDiTS1I17suNQXY91qfcg77/eB8+3woNjxpBvW2BJ7zH3WUbFnqZSZdEvPDBU1v6r5RO0eUXtd/evEW2ht9n55XyS7Nhz3JC40brO0TQiKvpWUunTU2lojGO+aSS5bgor6KeSWftOwB1YS2FlHXlvifYD4b5KzR1XC2sRKEzVR1Dia6qvsq+lZ28J56vZSMl1bxPkjYjbdF/TFWS3M+WKUv6VH7LPlAoVbOFuyFmdLJrtnS+YEYvRkyTh+BdhRZ4XqDy0n96ZJHwGeS9mgzS+lz3rsmJ476MMemAdTsdNaWKwsaCEoOSfl6K3n5ot6IneSfJGcJm25TuCE+uh1Rc8FPq1v1Y66of6mpIm2/87+dtHTS8z0cc3U8s4lyI48S81McPXUcM8zrSHyIF+ofzpDvmbT1M48ef+FtdWqQH+7nNZfobXrzjmEL4m+qTL+08BqpOrEmKi/SjsxxVpj5YT1cdOcM+pEz1FyczIryKK8bpixEtFXzpQT0XeTuDFY3SjnujFXzsquZfXSNjv8jFSnPhogesv6TDv4Dnku9phzbkrhFjJcaBDJsiKe73W/pktV7Z9WU3u6qT2BwiUJWX8zFrVU7KjtzcPavz33Pq6p3zMXufV7ibk7py0kvyG7+U3UO7r92lCeSgsbl9Z8U6ydHPN9yf5uefM9tyhS2dAOb/F5W83v5a+SvqqWGceOZqX2XWNF/3naH3H0Z5ea19NhtpgZoN/zakb3KCVX1fxRSn+3gvZ3C/1n7+8W+KW/K/G/xh+Kf1nb7Pf0aTWON/hLxrHT18VPztmX4fOVP+l8KmZTlG34UXRVKN61bZbOUClrclR/ZStLx9VeFTndn2Q=
*/