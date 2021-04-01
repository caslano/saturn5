// boost lockfree
//
// Copyright (C) 2011 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_POLICIES_HPP_INCLUDED
#define BOOST_LOCKFREE_POLICIES_HPP_INCLUDED

#include <boost/parameter/template_keyword.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost {
namespace lockfree {

#ifndef BOOST_DOXYGEN_INVOKED
namespace tag { struct allocator ; }
namespace tag { struct fixed_sized; }
namespace tag { struct capacity; }

#endif

/** Configures a data structure as \b fixed-sized.
 *
 *  The internal nodes are stored inside an array and they are addressed by array indexing. This limits the possible size of the
 *  queue to the number of elements that can be addressed by the index type (usually 2**16-2), but on platforms that lack
 *  double-width compare-and-exchange instructions, this is the best way to achieve lock-freedom.
 *  This implies that a data structure is bounded.
 * */
template <bool IsFixedSized>
struct fixed_sized:
    boost::parameter::template_keyword<tag::fixed_sized, boost::mpl::bool_<IsFixedSized> >
{};

/** Sets the \b capacity of a data structure at compile-time.
 *
 * This implies that a data structure is bounded and fixed-sized.
 * */
template <size_t Size>
struct capacity:
    boost::parameter::template_keyword<tag::capacity, boost::mpl::size_t<Size> >
{};

/** Defines the \b allocator type of a data structure.
 * */
template <class Alloc>
struct allocator:
    boost::parameter::template_keyword<tag::allocator, Alloc>
{};

}
}

#endif /* BOOST_LOCKFREE_POLICIES_HPP_INCLUDED */

/* policies.hpp
e1HuD6cEKJ3EF20CHR4GvkeH7RaXFzBujbgY0tXZqsAEaSN8s8YtQbKsUn/rmVLj9doLAExxB2lP6/8kGzWAg5mC07xhPGp5b7NCQLRjgkmUdwGN88YtzVTqnbsQcoNHeKzqDv/OTStTdT+9rJfm/a0dr3RIus0TqEHvQOqGfI+MhnLkZp1ktqY+12VaqUNDG61e385QEpmnp2HZRBLcHIEfNl0scXyRzXVpqJ0064556SJe7yiHoPF7BtSeO9bq0hgehnSLZakKLJbEWsU5/s1D9TZadDvFfun+rPeKcbWuSZtQFdHciVQQBduG9MN+GMu9aZ8SoD2I2hSL4RwxS9TJRcNsqNshx4UkOSUV0G2viJimzPYIDoxeI2seEv2emPA4mf0N6prDMpt6s6ipjMmm8YPQTM4X5TphqCUg5BH7ce4HHM7URY5yWb8hpGiCx+819FVi3tjF135163xsd6EgoXX7arBRofF1f/Punteg+bMCrxJa8VnJLTNMk5HGMaxvLA6UsaYD9oTeTMQQCxNgxU2YJ3ZZQ+MMRHmtAM1UNNENN71T+xJb6A==
*/