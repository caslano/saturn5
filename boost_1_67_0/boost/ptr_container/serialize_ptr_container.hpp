// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_HPP

#include <boost/ptr_container/serialize_ptr_array.hpp>
#include <boost/ptr_container/serialize_ptr_deque.hpp>
#include <boost/ptr_container/serialize_ptr_list.hpp>
#include <boost/ptr_container/serialize_ptr_map.hpp>
#include <boost/ptr_container/serialize_ptr_set.hpp>
#include <boost/ptr_container/serialize_ptr_vector.hpp>
#include <boost/ptr_container/serialize_ptr_unordered_set.hpp>
#include <boost/ptr_container/serialize_ptr_unordered_map.hpp>
#include <boost/ptr_container/serialize_ptr_circular_buffer.hpp>

#endif

/* serialize_ptr_container.hpp
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
*/