// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_set_view.hpp
/// \brief Unconstrained view of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a bimap.

template< class CoreIndex >
class unconstrained_set_view
{
    public:
    template< class T >
    unconstrained_set_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

/* unconstrained_set_view.hpp
GUkbGBgyf3ylaN7m8rUQ+SoTdqcEbqRLNPhxeoTJVrjOhD9jTGT4nqZG6hTCYiV5EB0C3oxsKL+nqZGwtc/gWbTgeZnPc5NotRxaJZODcuSKmMIcJk5u67XA7cDh1g7F3w80iZ7WArMpYfUmShdM1kXIZD0x12qq6wRFXwLSFgnBJS6D19kIwHcJ8N0DI9/VHUZ+Sp63izlKFiVFPbV/nhUo5vLj8osgDRfPJdeYc1/lxWQBrhOQWxeT2xSV3tYiEqAgiT3DCAMg1c3fmqnGFq1UqnkbVvLz3hG07e4YwTHPb8ZNx0EmN0TzfkuNTXb7jqb5FCdGFxXduu91K6lJnPn3xsZBrJZ4NGGJUwb1IH3Ji9j6vbGJJrCkiUP27Vmcj1AISJQoZvjdmezXGWKsQhWCFRvhFMy3YrpZ8Lb+EaITXyvHbsLfo0HBrOBvNGFBuyJlGB1tu0R9iBe5QZ29gZiQdqFWNWrkWHT589BwGve9w1UI7ZPG9gBRYgo0mPugkxrwPc13Mg1iuRxlmNubP75awBwE3LQsR32/o1KM6vD1DB2P3KhCR6WyO98IHUPnaDA3VJ/xtaCM3THjHszYXZ8xLyjjMR8A54sMb5UQIWOH8mEX2HLV8DO9K9hV+S1Xy66yLNJcICOO7v61mXZTEe8m2EmEn27lUL7zO6rbJB4D+Z4EniIHY2dLngIihMJGceoMfdB6m2OEXqfK
*/