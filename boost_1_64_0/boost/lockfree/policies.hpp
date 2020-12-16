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
l+U7ij7RD8eYp8Hwb+NvUdfdR53Hy5xHMznHZF13xcG8/KBumzvUcfc1to1Td5uq1d1uuu4ceRt2DNddVTsMVcdPld/+ow1T2wdw77ez0mUOfbySN9regZmaBshrKvKYQCYUFXH3aj3DSnX+T9qdrWvs8DXOUDJtV38vKsxz+Qs4V5U50orMH9D5C0uzh/IIyy47q1ieBwHYQJ3XtfZoSt5sfeEz1YlzX3/JNeyt9q22T7NtWi10Lgeqdi4oDo6qqo9NT6q+r659o6suSXf3QzmvslEl2epa9PMjXeV/xR5J3gts9zUMyS3lMsrGleRbrmvvo47XV+rPZ4Xq+iBfgtXa9xC6hPbye+vZPFPPoD9kEac0Y84kJRTnyH7n71v5+zYiOgYdb2f7DuKdxLuIc4l3E+cR5xPvCZUXmZSJ2K5obo73iT5jQfWof9/Nebv0F2b9l/OMT5VnfHI13eVYbU9A3bGtnrPIbaz6XKXyK8szK7u8aCgvnmB+aSl9Wqe/rdPdqbSNpH+k04ePGxJUzVfdJ4N88p8h+sXBxJ2cd9aaqO+s7IKSkO6tcienDFsE4/tpTY33k0nPRj7ju8b4PiGvWQcmfazn0yHbhobyXqUvah3276rs8VZr/s2kv9Vj3yAEn0Z02vd0eH8m/S9l6zrqcLtSB7RZQczt6q77DNHxD5K6H0gMUPclT0vdG2s+trpHhq77qdHrnny11+eKWupzvErrU2t9LqiD+pwq9enU3X5Sd1Ma1ey36VmUD9dddp8jBsbZXytjrLPKp2Pvr5Vbqd9Oz0Sv36+f3np/XViH9Rutv2ZZTVSd9xZdfSkV3hkOgs2o8xx1DReEKntIoYxDZFwrxwrrmK8gr/PMz+AIhjYQWT555zrl1SvXCkh9zVDp5YxqM9A51De2j8iQcYAaW5cXiP56JO+5CSr9BF/YB9D5arsX45mA9g9z5troNlJu+eWq/RmeufT416r0LEanLcx2AKSb+k/4fFaq9G70ifa6L6xT+35kj220DXDLbJmlWqksKH2yjGtuqMeThbrvNVHXOF+/j79VMl6kVldq30JPNlXvRjdVX7ve/M7rRTLnfaAaS6Uirfr7T/qC9Lumap9qX933nPZKlfYSmy9am31Sx6K7131U8qlr5LrZx3W79Pk97Pj13mY9dvz64Yv9zv45/Z9MSLp0y32tH3y1ddtbjjkkul79NqW3L5vy86gV+Td+n5gy+OKOD/Uqi67HNtsjRNdvm/X20fTz8dsdmO0m4rePMNsFxG83UVd2BOgdqSP5lpXv+7miS24v9vdHix+RY2AT0Yt2hqeKvnYAPEj0okeKXvQYOBj2hWfAk2EuzIcF8GJYCK+GZ8LpcCR8EBbBZ2AJfAWOFr1jEG6CZdDPyZ4Fk+D7MBWeA/eC58GD4AX8XwQvg5fDiXAyvNw5HpwMZ8Ip8BZ4PbwX3gAXwxvhk3AGfAbOgs/DOfAbeCe0bMbjMAneDdvD++AJcCE8CT4Az4APwgK4BJ4HH4Yz4GPwTrgSzoWr4BPwSfihLfp8f0iPnwDXwgB8DraE6+Fu8EW4B3wZdoOvwxPgW7AYvguvhu/DWfByeB/8CK6BH8MX4CfwNfgprISfwc/h5/AH+AXcAjeI3nq4Hruqtlb9pyHxdHlwpon+O0P03i1Ff54JO8LdRY/dSvTYu8LjYGs4EO4GB0s+OZ6M7XhPG463nxzvQDneQXK87nK8w+R4h8jxDpX+2gOeAnvKccknx5OxTpTrayPH21uO116O10GO11mOt68cr6NcXyc5TpZcX2c53lz9zlPjEbXdjDiTaIk9yIHwe7Fj2ST3XVMGKqfBH9geBjfD8fBneA38Bd4=
*/