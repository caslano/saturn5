//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/auto_link.hpp>
#include <boost/container/container_fwd.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! <b>Returns</b>: A pointer to a static-duration object of a type derived from
//!   memory_resource that can serve as a resource for allocating memory using
//!   global `operator new` and global `operator delete`. The same value is returned every time this function
//!   is called. For return value p and memory resource r, p->is_equal(r) returns &r == p.
BOOST_CONTAINER_DECL memory_resource* new_delete_resource() BOOST_NOEXCEPT;

//! <b>Returns</b>: A pointer to a static-duration object of a type derived from
//!   memory_resource for which allocate() always throws bad_alloc and for which
//!   deallocate() has no effect. The same value is returned every time this function
//!   is called. For return value p and memory resource r, p->is_equal(r) returns &r == p.
BOOST_CONTAINER_DECL memory_resource* null_memory_resource() BOOST_NOEXCEPT;

//! <b>Effects</b>: If r is non-null, sets the value of the default memory resource
//!   pointer to r, otherwise sets the default memory resource pointer to new_delete_resource().
//!
//! <b>Postconditions</b>: get_default_resource() == r.
//!
//! <b>Returns</b>: The previous value of the default memory resource pointer.
//!
//! <b>Remarks</b>: Calling the set_default_resource and get_default_resource functions shall
//!   not incur a data race. A call to the set_default_resource function shall synchronize
//!   with subsequent calls to the set_default_resource and get_default_resource functions.
BOOST_CONTAINER_DECL memory_resource* set_default_resource(memory_resource* r) BOOST_NOEXCEPT;

//! <b>Returns</b>: The current value of the default
//!   memory resource pointer.
BOOST_CONTAINER_DECL memory_resource* get_default_resource() BOOST_NOEXCEPT;

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP

/* global_resource.hpp
zRoNco4W0H4ulEabrRay8tA9B82bhbJmCAQrlQR2w0TJZuiOaSi0rtVvg0HWNiVGMshlpgbZKhVeoRcPorpENAt2B7LWoCW0irtA8i4sZC7mdMcU4WHdzkqhCncDCx1W+UA2oHhZWnOoKrjqQuAQ22y5JAk1oheabkpWirwtC7m4J4hptYbmbVOhO0wLyuUSE+9CW+W8MfImESsvNssm5d8p2QZ7DrJCVNAbxRDEPZgxJZQLn4LkLLpI4NNoOh2FySVE72AUXlp7H4LwFLkh0GsD/LZuuEIUDYhFXQqe33P+Qzvd8ZIzOLmYjs+jSZJOgok/DkKK+RB6wyP4u62I2q960CvFjGoPR97hkbePB/QtXbSlFqnimsqM/8gohUbjMwhH577zlOWrPeCVodVZkkygFjUvRSWqa1NLY7Au+S0eGDvxZRhN4iB2fhJVVrY5h7fkuSNi8afT+cgk/vAIUd/8BrsFWi6RLE/AcaGU6Hom9IKprzu/G5+nfnwyDSZJEIXOhGEpbO9dzY+t4NV8Qj3FFlwTcyRKIAFaHH2rPOHZVpjO/TCJ3HQ8OLgXMMxl07WoOYUOt+c4nwpeWXO5u3axFGWJvan5Yt1jqC3xWjdSy0yWMOdMt8gm7Ai0kEvKKuEuS5xTDf+35Uqb
*/