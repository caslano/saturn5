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
gBV6KLJR5bQCSdMIZdHujiafvCO0ZSkKYLkgFLO2AYulrjOgaSULmR7CUWDFtp29lDaQ7YsKRSm3AtCA6oRyD9VVnnP9LjlpLl4Ier3ECDZawSirZO3VcXBZsjNEXmaFVb5NVT1UICi2xDgOiL9YSoazzjwRRYojIBL231WEIzf2IQWW0EZTMySwKDBPcWgaIqwwE4bnTZ0KW/FGhysYhLgUCh6vYljs2LB4ZfklojuRVNL0iUpzY2DUuATuVOx5MA2O3jRMDl15QOnYEB255TsEatYVbkDYRAJJ1hWoWyOwdqv3cKth2Kd3b8oSAdbqlsOF0FQpZjDUc8FTlCeLYpsB5K4QxdpQMmaXlUL1hQnXwU7x7vC1s6ULer3qnw+mNc3CnJYXJIhlKmwV+N+wjHNVPO3YI+qGVN9YigFs20Zil2JnHUYqkQBp0bquFJ41YXLJBbQhJPYszeBMWcqlHQZrzlFly45ShnQgLt0lHl7J0GaQ8ptHupwdXJG7qBiOugP2rLuhcgeOjW1mPDZFuInOUnyRtc3eN8w9ErfAKurVdoGL4Ko/9c7WqK+FqJJHVI3fg6t+36itUuA6sjtH4+F02Bn2J8hbYp50/wh+H/W7ZrZB+961xUwHHPTafalLYQbmbQAO+bqIDrk1
*/