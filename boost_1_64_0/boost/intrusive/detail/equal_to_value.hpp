/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP
#define BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>

namespace boost {
namespace intrusive {
namespace detail {

//This functor compares a stored value
//and the one passed as an argument
template<class ConstReference>
class equal_to_value
{
   ConstReference t_;

   public:
   equal_to_value(ConstReference t)
      :  t_(t)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bool operator()(ConstReference t)const
   {  return t_ == t;   }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP

/* equal_to_value.hpp
X6amVDGYn/jqUlNaC3R0Aeh7cTt5kZZvcnaH854XYzcpeMs4bsWBzzqSwKj1f19P75mWRlLd+OGbn0kG8mSRenxW99NArkkJoDEHu/hhTrx9FkU2mpByOMxivk5rTcIDh0mzLQNEuLillLnP809U2wmMMmZYzEVQDhz6vjbXvWFKzYz6cdva6Nt12NrZzxWtj+0vkFWL5yEt77dhb2XsgmiuALr2TFSxuXM52e8jF+KSZ0uAPxt9owS1DwW/n7PvNmxGlHmXJrUJ6MMsf+8IAIHVOeX/SQuB9PGzdmc1Lid+UtCZM44IfVsuJOFehh9MgAabKk5Uva5V8GcIhFGY9Wm/VJoKNLs/TphBGsDGS5mgCFL3SFkdFePXeVK8/Gk7ns1YvIo8br7tSQdEZXpSmWe5XIbXi6AjWPs99vjSyANJXaZc5FSDPp/7bXSwSDwPGjfREB0O64jmWge3cMrnj4hymbQdHeJV1tIjJpRbVoKobdA08n6L8EQbFqk2qvrpz3N0s3AQJKCn9tb9S+LxyJhJsYC0NnRmcjZcTeQiBVuk27r8ZTmg4zsptQ==
*/