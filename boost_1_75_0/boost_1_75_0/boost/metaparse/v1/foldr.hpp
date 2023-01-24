#ifndef BOOST_METAPARSE_V1_FOLDR_HPP
#define BOOST_METAPARSE_V1_FOLDR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr : foldr_start_with_parser<P, return_<State>, BackwardOp> {};
    }
  }
}

#endif


/* foldr.hpp
xu+DqvEboF//XfPQL9KkLDbsLvZ/jbQXBmeQ3thLDB5PEFyJ8VtqpzDci7mr5AtHn1AoeDLkW1lcFrjTHbb9DPaPkGshe2pp9vyi5YwoLpXX55xQ4KUUXIxdu+3FA1XlAABecg9YVeGmc1CSW84muwA6GXj/P9a+PSCqavv/zACCJg6aI1SWWJqUdaW0wqslU4wONZOYYVZalI/QpKiYwhRTgWQ8TmIvvd1Ku1lSWdrNAssSryaYJVimlCX0uh5CAysFn+e311p773PODHi99/v7Qw9znvux9trr+Vkquw5feyz9OGKM/ElyOcy3C8qkYebh68ZgAawA64Mc2BvePANSueCN/0AqD1OZxXLxjvJQVipEqXV9af9p6ECUYlzkYDLx11/48Xt+/Jofv0jGSs87tBUDOVbLpRBI/PrS4zqI5AsHynJ1oy8lKf2xgXKPNYWnfVN4TPe7Qpg0MGhg1Lrz0jeA4tQSMtrnRXmGVeedzW7DEFBI+tQA/p5qDxqxbK53bY3o3jPqDMgyed8YXO/jnYLr9XEv/AHB5n/3gh8CvOb+S+CdVAu7KJH2hJR2kpqxgMUS2hI38i2RtS22pB/fHoJ2QUMbQxTMZm8gZykS36p7cWeYuJTUsAijGtEdQPxDcyL8Ma6FJxuT0BGSE50WyNGJdUYbrPMa/JAvWuILQvHEEiaGUQUg9hbdUfQlKpk5rcaNrXpGPtY9
*/