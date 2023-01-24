//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP
#define BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

// interprocess
#include <boost/interprocess/interprocess_fwd.hpp>
// container/detail
#include <boost/container/detail/transform_iterator.hpp>

namespace boost {
namespace interprocess {

using boost::container::make_transform_iterator;
using boost::container::transform_iterator;

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP

/* transform_iterator.hpp
N93WbMfWz0NDlR9Oriil4Zh3M7P9QZ84/AhlWjXi6uPDkhxbAGVnplGoVmj+9cvWQ4zVeYnJYK04mJ/UqYYr/18gbryzsPdSCf4RDJURjY3PjWUJe0OIZv42NmqJi/O3thV+3NNljOIr2EJyZYXyiROBGe8hSkcUeSY/J+QUBgQzVGZB03Og3XMmMtLF3X1KMJTT6uHkqa/NlplmAjgd/rLyp9Xm4UvfLN4Tse5HHT4SOAp+uHIb8KXfktV2naXe8T4VCnJpqyqqjt5B1lF4wem2bbANhBi553XxnhBO2+Tq+F8QydMEeWlwvPq49VYdQDW9cErkIGrF1o2xKCezrLhzbOHgeWbDe0ngwtBmtqYnnNSlO16l7h1vORGKqndYhDnzcL/LrUPwN+qtqa0ikCFTb6XFE8tAX3HU7bNxECC83OCmDIrDmwvHvc3JXMFRYnVGFQjBY5Q+6NUWanA69dkHTNX3zEj/FLdKRgxx33VV1bpr5Zd2vL5nxjCpIBeqLMtVf/9e9VVReFV3jHS4f1NupBm6y5o+oWZC9yAzjXQ7fYV6kpxpNd3LJkrB58VQu6yfoVdxLslfx7pSDN/OvKx+xaPyUlEH5WZey3zt/0CYhkLJmUx+lqWmsT7dmczx2lDA9EmjbGQ2PLquIUQgBHeLS8XqPNjwGzcEhyxRiIOMzTHbfDP4WyFPinYeuj32NhfccP8dJRDpRzeJ
*/