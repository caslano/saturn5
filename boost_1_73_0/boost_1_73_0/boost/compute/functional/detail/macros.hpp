//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP
#define BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/compute/function.hpp>

#define BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(name, signature, template_args) \
    template<template_args> \
    class name : public function<signature> \
    { \
    public: \
        (name)() : function<signature>(BOOST_PP_STRINGIZE(name)) { } \
    };

#define BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(name, signature, template_args) \
    template<template_args> \
    class BOOST_PP_CAT(name, _) : public function<signature> \
    { \
    public: \
        BOOST_PP_CAT(name, _)() : function<signature>(BOOST_PP_STRINGIZE(name)) { } \
    };

#endif // BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP

/* macros.hpp
IFFPyUAvYZUGDIN7TlYcdTzpfRtVzLubC/J1iC8NFJ3MWF28RKjEc9hsZfAlRc6q8hnbbaAB5Iq7Fx1njvfluS0SuGuR555DT/AgzLo5PrkObwwklCkuhJJXKSywRUO77baqG0R8bJpsRPVb1u9K8oD1ftswGo+V6fmb+fza/kggMbWkrWtEAeHu0J7Pr4d2Prm4nMwpb0hfhADAkqIYv2eXqtIiZsXyhNok7T9K2o+8DR5g2/4nYsAyR7Tcdo/RUkmx/039i6AGSiR8Vlfbdv1OIvaM+V6oWJcJEBoUAkcyciR2plDTb//EICpzWSSHJbahVdn69pwukIaTHVd3rH0h+UgM0UoUr4qEAomEffaMgRM5afUgc2m+hSCzAWKk8gXwjCRNZlqVh2pEvFQtGkqIKA9kQFE2Jd+T+03ne4P0+awmq5wPXPBlBSQFLXB9Zh3bs3zlfDO0pzcnb0dvz/48tD+7mpLEivR3dn05+emKdjCX84u3BySM7RWlBPdsIgRp62OhtHsGHG0VkvmvTpghHB6q2amV9KuAgtnY2dVDYykzhJXkjVrAu3LUX/+0fZss4bq/mRgfJ5wwEdLIDeyEtR0BZLt+pNmIiCRnw8gZL6WuhsslJ3pXVg+yLssXQWdXMhWCsztUWrsN
*/