// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_RING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_RING_HPP


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{ring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_RING, ring} The
    ring may contain template parameters, which must be specified then.
\param Ring \param_macro_type{ring}

\qbk{
[heading Example]
[register_ring]
[register_ring_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_RING(Ring) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<Ring> { typedef ring_tag type; }; \
}}}


/*!
\brief \brief_macro{templated ring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_RING_TEMPLATED, templated ring}
    \details_macro_templated{ring, point}
\param Ring \param_macro_type{ring (without template parameters)}

\qbk{
[heading Example]
[register_ring_templated]
[register_ring_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_RING_TEMPLATED(Ring) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename P> struct tag< Ring<P> > { typedef ring_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_RING_HPP

/* ring.hpp
/+n7241LLoW16CiEy80a3sVzk/wXEGBFZ7cKX3axlMgjMvuq54F770G1yXkVOzjUFTnfA5OHdVItz/OxX3BbqSeWfyO0/kZUDvGjp8W33HvO48B/p8l/1CvdF7ZSw4gZsmKjGcafnLBRBQ9ukopc6hyRwt3Qc8UzvFygkHsbjby2IuI9Hv7d86oH8B08QCVPITeLd/P0ZfdsMXb3Lwq5Gwx1+vbYzx4k6/PEnam67ABdKPzcTPKt7izE0cpgWZbPyTs5yNqPf7sH1hEeYKk5oHC5zsc1jzsHKR/5N7Z0xO8AAfrbk6s8NbZ8q9L/Hup0Lmv5fO/OP6OB3T6612IUZnA98Pu8NLUH6AxIl3nniKtFMuxvbXD+fdgSQ2P3vC61jYC8+s7Ni94lTY+BHyd2Vm5vgbE8yXNSVEZhUGrSlc4rCcz9ImxuCfNS6gI3mMrqcgoehyRmfbv91Jad4r2bQnHOzHyroGz8C2Et1VJfsyNdCwV/GzNxrTuy7tbxEXjWq6wc2r/EP+dUnasDD0qg53eF2X1RtslJMj7gDjDz1+bYdJDonI94ARkzdYMxHwePyBZJ/3JZ4yZMpd2/3WzLrG7juFf2zvD460Ew1iKVUNSZ80KSFb7xsi9deuB4a85bcXeSM8iq3x+JM9c6Yg0fYWiMl+zrJH646i4m8K62ydtuGGIXvPRa1uEUfRTfZdMsV4/VwYMyajFrQZsf
*/