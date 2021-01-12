// Boost.Function library - Typeof support
//  Copyright (C) Douglas Gregor 2008
//
//  Use, modification and distribution is subject to the Boost
//  Software License, Version 1.0.  (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_TYPEOF_HPP
#define BOOST_FUNCTION_TYPEOF_HPP
#include <boost/function/function_fwd.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(boost::bad_function_call)

#if !defined(BOOST_FUNCTION_NO_FUNCTION_TYPE_SYNTAX)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function, (typename))
#endif

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function0, (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function1, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function2, (typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function3, 
  (typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function4, 
  (typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function5, 
  (typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function6, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function7, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function8, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function9, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function10, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename)(typename)(typename))
#endif

/* function_typeof.hpp
Dg4Q/3xCcAlMhpfBFLgMcl/q1wfDpvon1Z8eZP0KnAd/hAuhe/9SGMbdEpgGH4XpcAPMgN/CTPgd7JZqqnfBXPQJCaQTbAgL4IGwCPaC+8PRsAE8EzaCc6Hrfh5sin45bAZvgAfDl2E7uAF2hLthZ2gSqZdhGHaFOfAI2BH2hMfBo+BweAysgCfBM+Gx8GzYD54LB8KF8Dh4DRwMb4KnwHvhqfAJOBK+BEvgGjgavgfHwA9h
*/