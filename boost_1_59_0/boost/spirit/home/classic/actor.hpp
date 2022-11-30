/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_HPP

#include <boost/spirit/home/classic/version.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Actors documentation and convention
//
//  Actors
//
//  Actors are predefined semantic action functors. They are used to do an
//  action on the parse result if the parser has had a successful match. An
//  example of actor is the append_actor described in the Spirit
//  documentation.
//
//  The action takes place through a call to the () operator: single argument
//  () operator call for character parsers and two argument (first,last) call
//  for phrase parsers. Actors should implement at least one of the two ()
//  operator.
//
//  Actor instances are not created directly since they usually involve a
//  number of template parameters. Instead generator functions ("helper
//  functions") are provided to generate actors according to their arguments.
//  All helper functions have the "_a" suffix. For example, append_actor is
//  created using the append_a function.
//
//  Policy holder actors and policy actions
//
//  A lot of actors need to store reference to one or more objects. For
//  example, actions on container need to store a reference to the container.
//  Therefore, this kind of actor have been broken down into
//
//      - a action policy that does the action (act method),
//      - a policy holder actor that stores the references and feeds the act
//        method.
//
//  Policy holder actors
//
//      Policy holder have the following naming convention:
//          <member>_ >> *<member> >> !value >> actor
//      where member are the policy stored member, they can be of type:
//
//       - ref, a reference,
//       - const_ref, a const reference,
//       - value, by value,
//       - empty, no stored members
//       - !value states if the policy uses the parse result or not.
//
//  The available policy holder are enumerated below:
//
//      - empty_actor, nothing stored, feeds parse result
//      - value_actor, 1 object stored by value, feeds value
//      - ref_actor, 1 reference stored, feeds ref
//      - ref_value_actor, 1 reference stored, feeds ref and parse result
//
//  Doc. convention
//
//      - ref is a reference to an object stored in a policy holder actor,
//      - value_ref,value1_ref, value2_ref are a const reference stored in a
//          policy holder actor,
//      - value is the parse result in the single argument () operator,
//      - first,last are the parse result in the two argument () operator
//
//  Actors (generator functions) and quick description
//
//      - assign_a(ref)                 assign parse result to ref
//      - assign_a(ref, value_ref)      assign value_ref to ref
//      - increment_a(ref)              increment ref
//      - decrement_a(ref)              decrement ref
//      - push_back_a(ref)              push back the parse result in ref
//      - push_back_a(ref, value_ref)   push back value_ref in ref
//      - push_front_a(ref)             push front the parse result in ref
//      - push_front_a(ref, value_ref)  push front value_ref in ref
//      - insert_key_a(ref,value_ref)   insert value_ref in ref using the
//                                      parse result as key
//      - insert_at_a(ref, key_ref)     insert the parse result in ref at key_ref
//      - insert_at_a(ref, key_ref      insert value_ref in ref at key_ref
//          , value_ref)                
//      - assign_key_a(ref, value_ref)  assign value_ref in ref using the
//                                      parse result as key
//      - erase_a(ref, key)             erase data at key from ref
//      - clear_a(ref)                  clears ref
//      - swap_a(aref, bref)            swaps aref and bref
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/spirit/home/classic/actor/ref_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_value_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_value_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_const_ref_a.hpp>

#include <boost/spirit/home/classic/actor/assign_actor.hpp>
#include <boost/spirit/home/classic/actor/clear_actor.hpp>
#include <boost/spirit/home/classic/actor/increment_actor.hpp>
#include <boost/spirit/home/classic/actor/decrement_actor.hpp>
#include <boost/spirit/home/classic/actor/push_back_actor.hpp>
#include <boost/spirit/home/classic/actor/push_front_actor.hpp>
#include <boost/spirit/home/classic/actor/erase_actor.hpp>
#include <boost/spirit/home/classic/actor/insert_key_actor.hpp>
#include <boost/spirit/home/classic/actor/insert_at_actor.hpp>
#include <boost/spirit/home/classic/actor/assign_key_actor.hpp>
#include <boost/spirit/home/classic/actor/swap_actor.hpp>

#endif

/* actor.hpp
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
*/