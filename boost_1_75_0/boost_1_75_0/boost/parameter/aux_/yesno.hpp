// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_YESNO_HPP
#define BOOST_PARAMETER_AUX_YESNO_HPP

namespace boost { namespace parameter { namespace aux {

    // types used with the "sizeof trick" to capture the results of
    // overload resolution at compile-time.
    typedef char yes_tag;
    typedef char (&no_tag)[2];
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux {

    // mpl::true_ and mpl::false_ are not distinguishable by sizeof(),
    // so we pass them through these functions to get a type that is.
    ::boost::parameter::aux::yes_tag to_yesno(::boost::mpl::true_);
    ::boost::parameter::aux::no_tag to_yesno(::boost::mpl::false_);
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>

namespace boost { namespace parameter { namespace aux {

    // mp11::mp_true and mp11::mp_false are not distinguishable by sizeof(),
    // so we pass them through these functions to get a type that is.
    ::boost::parameter::aux::yes_tag to_yesno(::boost::mp11::mp_true);
    ::boost::parameter::aux::no_tag to_yesno(::boost::mp11::mp_false);
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* yesno.hpp
V1e72uC1oPucB8F2DzPBmZosrFbMZ/Bu7E93TtaqutqSfL5MHqG+kvfaeOb65Taniv2RfsijqMiqXYSqtYuul4S+6+Klf9Fu0jDMRcDdbrjzVpeXm2yiOZ66+TFN9bNKsYgqjUpHW6711NYNoYm73Qc6PqmjHzGU88I/LYSzjrVsFZ03V5Y6y4XWTq5OHC+w71raWp0vHUAv2yHOWM4Orq643nztUU/TlLmCrM0PaXWUyTcNlQtv/ZTNmlZtOvF8pcuHkUCmiSu5egICfG5RDxEpb3VKf0b7+PWLJq7zhXx6NZ3bVuK/uLKyAkFVXVifX/9NHMtUQ62yNbHmzholvv943U0TMPbjcksssDuwi75RRk0gCqYPOkxUERv/BmE6/7TZSPuZnG5ezGfqpzQoZCxgIImZUDH2BPZgueT4ydnzCM7AkLb08/WWdAohl82oO05Ah9lDiOXjDAwmnbaNd9WsqvzLXi5YbDM8n5Fo78jL0kWA8hJpcBErOfbywBWLgwRrBFZnkc6c886MBkDWt0OdPxij7FTyNsvXrX1Cp6ImJ5UEFKzWc/8QMkneQiiaT/Dkvzr/2Ej2Yi8CX8RHbdADApge+wc6a7NNMtw3SJUJO3xfujPt8ujEmuFIdwiBMnjZ+isiEfvBvPptBniUmY1uPsNZKorZF71HYCb+6RwHTS5Vo+mW7RyRVDoPEGTHue/K6zUtc79zFdWH
*/