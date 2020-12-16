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

#ifndef BOOST_GEOMETRY_GEOMETRIES_MULTI_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_MULTI_LINESTRING_HPP

#include <memory>
#include <vector>

#include <boost/concept/requires.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/linestring_concept.hpp>

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost { namespace geometry
{


namespace model
{

/*!
\brief multi_line, a collection of linestring
\details Multi-linestring can be used to group lines belonging to each other,
        e.g. a highway (with interruptions)
\ingroup geometries

\qbk{[include reference/geometries/multi_linestring.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_multi_linestring MultiLineString Concept]
}
*/
template
<
    typename LineString,
    template<typename, typename> class Container = std::vector,
    template<typename> class Allocator = std::allocator
>
class multi_linestring : public Container<LineString, Allocator<LineString> >
{
    BOOST_CONCEPT_ASSERT( (concepts::Linestring<LineString>) );

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST

    // default constructor and base_type definitions are required only
    // if the constructor taking std::initializer_list is defined

    typedef Container<LineString, Allocator<LineString> > base_type;

public:
    /// \constructor_default{multi_linestring}
    multi_linestring()
        : base_type()
    {}

    /// \constructor_initializer_list{multi_linestring}
    inline multi_linestring(std::initializer_list<LineString> l)
        : base_type(l.begin(), l.end())
    {}

// Commented out for now in order to support Boost.Assign
// Without this assignment operator first the object should be created
//   from initializer list, then it shoudl be moved.
//// Without this workaround in MSVC the assignment operator is ambiguous
//#ifndef BOOST_MSVC
//    /// \assignment_initializer_list{multi_linestring}
//    inline multi_linestring & operator=(std::initializer_list<LineString> l)
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
    typename LineString,
    template<typename, typename> class Container,
    template<typename> class Allocator
>
struct tag< model::multi_linestring<LineString, Container, Allocator> >
{
    typedef multi_linestring_tag type;
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_MULTI_LINESTRING_HPP

/* multi_linestring.hpp
7yrAiRHKEtV3pPKkY5BqZpx1MT50+tg+Tx+7nOXoGU1/slzkvUtal98u+hrj1yTnu1fGB8qnnttapEhnbuAfZPzjrL8uZQzeqWfKv2lbulrXpF7NM8SsWZ9UPG7cdbw6xinh1nrG0V/JnYfKEXmmrFdvVWweSvv9aqYlJT1Z8zaxIWrJ7tiXr9iYn7Mevo7om46f+SYNzU+pnWnF5mJ0rkzeVVPZdUva21SN3O6ilmhliJq0y6pvKjprWkOsuNL2mYv7PUVvP5VDbjhl59b/Yn9z0N7PLXIrzzd8RtidtaH4cfJ9E+c+dE3bprofoaHuhT7kTdtJ+aOml7IH+nPRl6nx5ZhzzhRFTj73sETaq13+rZJ32N6A/5Inh/znhG7mhMn57Ob527XvXvuT37ZfNFQNDXgSzX5pj/2UeKdgNCEGPXOijrKzh1HNYVuKVcm7t9qZ5tA87OqT+mFoVSn7snHBad/ayfukv11znubuSylZ5yW7+3LV/WJhPxYh7GlmH3x42KcQbMfi0vYvqZmGxcqUriuXd1XDxjZGi1qZ8LEN1Rdnlf3bcIfvxymZr9e8o+shNF830Hy9wRO2sdPz861S8vVDoq+65mvHXGrY2oFP/ue8rfta3rU1/qh+PMqTQ144HvKjLImWyNcFISX7b47+Cu4YWXCKkT+2nsRW756HGTOc9scxs40eRjlVY9ZGzHUlTOmo6V6IUF9H5z3VLL4+aJW323jJ4+H9EGfNoF/s/NR6TfuEfV3zqaExsWL9g2oarmwxu504a231ouQPxK8LrAZhdfHKKTpG5qmL14haJ3zXQOuhv70L/BzWXUr8aV/C2b8RipsMneOuKeUtPC68ab7mPdvBC9Rh415d0jxzaniah47zjJjmqr+RN52cTqSWO0fPBaE0itDX7BPS97dlrvj+Fq1jNC5c9yUu0sPiQl8Vi4thH9qWv675/wBPhlnj4omLSVOnTpxV4G73t+teu06VxbuUfI0Tx1wNN5/eI/JV1izPeohuBUYt2muPmddz7blY7NGyruXpRpF3qMxostjBPGu4HSH/aN6/S8ztVLcde6uF1kB71ln2dd8/rXLInVBfwnEitNZ6vZjZqHIkM27wrFTtf6QZPbKTJFb7ICFzcrcaeXTBB8SfGdPtkJCV0CY6NmAOtor1R/wWe0780ELlUBxLH17tO6j2JfpnJdQPWRiMZN8vYl9XlUN+847x3n8OfSTt2+o6rVB+0X3pqh5Kf+0zedVdM6lh48OSbpKXG2l7k/hReHuTq3ftrykI5eUp+VdGXFd9r+ipSXh9mpfVnKcfdeR/aGvM2MFesceydpcPb/vTP7ENLudlBTjPZ/v3sMe/rDbMo9I7254U9OsZ2rq25i+R83x1rKgS5+A44U2aJt+mvsr8j7TOwzlvprzo6+MrZ5XMdz15nyvvV5ZYCzWId9Hybqivqpb1ec45LHJdY2h8up3oS1WZHSUiJ5Z6dtN0ed/CXY/TX+RhVpzVM7Ruodh6mmGiJ+CuJRkhcneV1Q5saENaJ/F+O5ru1rMb/p3ifZyzoIrz3L4F+5TSxx78qa3xY550nv3mIVMcmh7KC7I6VTNCafsDTor+LeTkBM0fjh21I9Z5F8t7zT+apj+I/CjlKlrjU8zIAfHOXpGfRM9jVq6Wl/GuPVlh/bPz/4u9bcW/kb3lPDX8Wwq/FDtz8l+2hU9p2X9U+5rHZ3jiL3+mvVJTcjknrpXS70ydKetnNP4cO7Lc9Xu7K5T2/PfrWL1ztX98ZmusgJt1lb40yvfM8DBor0bSZl+KtH1yr4D6V/U3c8th+VlG/sx6Qfd81ox2zHjvS3bMneeW/RQx96X1iuXztNU=
*/