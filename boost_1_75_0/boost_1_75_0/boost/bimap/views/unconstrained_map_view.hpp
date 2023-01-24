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
5EmyuZ8uIENXjFg4n2ZJuikW3XmVihJeQhsi/uBfoLcdKjdp81pu0q+RohW5nYoQGlVZDfB/tqCRQqj/gmDkXfvVMYDVUbFZGB5PO036XPn+FJk23Wk2sd4esqmnSVmG06SmtEjEbEPvUYuk5m7ijEH1oY6HDJdji7nJqaCodiQcr519CI5wTmjCwvj5jYSFm+Y3EhZaacJCMUdktBV8ezgQqP38MFZoXJWo+c2syoln/+NV2fpsE6tiKyhFR26r6COk1r7YwD35L/RzHXX6uboWybOzYycCs+Cryj9ltjl2FG7PeZiOXkY+qzvcYUa0RmNE6eSIBDX6qDeW2qYzluoVcU5jKeXzdDoS+5Sf425g+x9+vpWuHpF1HAlnakvb0pnagnQ6Q5vDBQv4PeYGtcAvbvZRwXVZ+HlmJNrm7FTSuczhkfTh4Eh6T+T0r0aqdT3PdW3RkmZy0ttc+lV+/sPNPMfvc/n5k9azEW4YyhdRNJTtN1BzW7jgen7P0Nrqwm1dx3UNlnXfgEPZpRRymQv5Q2ceSlutjm9c6s8dLvr6F1dbx8+f+XkV92TADRjvD2NQGWJmij1kuaSrGvTP6fvO5Tua/IGZT6xr8sfvNWFYPb+lPZ4eOKrh/lQKmxv/PEo1LKhWhs7S2RpbA/YN82DLfIkZN+gzdg/K+Mw8VMoNl7X69ZnrZxoz3ysyu/0fsblBNeIPOAKPuwDQ
*/