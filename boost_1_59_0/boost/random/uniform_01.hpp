/* boost random/uniform_01.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_UNIFORM_01_HPP
#define BOOST_RANDOM_UNIFORM_01_HPP

#include <iostream>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/ptr_helper.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {

#ifdef BOOST_RANDOM_DOXYGEN

/**
 * The distribution function uniform_01 models a \random_distribution.
 * On each invocation, it returns a random floating-point value
 * uniformly distributed in the range [0..1).
 *
 * The template parameter RealType shall denote a float-like value type
 * with support for binary operators +, -, and /.
 *
 * Note: The current implementation is buggy, because it may not fill
 * all of the mantissa with random bits. I'm unsure how to fill a
 * (to-be-invented) @c boost::bigfloat class with random bits efficiently.
 * It's probably time for a traits class.
 */
template<class RealType = double>
class uniform_01
{
public:
  typedef RealType input_type;
  typedef RealType result_type;
  result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const;
  result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const;
  void reset();

  template<class Engine>
  result_type operator()(Engine& eng);

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
  template<class CharT, class Traits>
  friend std::basic_ostream<CharT,Traits>&
  operator<<(std::basic_ostream<CharT,Traits>& os, const new_uniform_01&)
  {
    return os;
  }

  template<class CharT, class Traits>
  friend std::basic_istream<CharT,Traits>&
  operator>>(std::basic_istream<CharT,Traits>& is, new_uniform_01&)
  {
    return is;
  }
#endif
};

#else

namespace detail {

template<class RealType>
class new_uniform_01
{
public:
  typedef RealType input_type;
  typedef RealType result_type;
  // compiler-generated copy ctor and copy assignment are fine
  result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return result_type(0); }
  result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return result_type(1); }
  void reset() { }

  template<class Engine>
  result_type operator()(Engine& eng) {
    for (;;) {
      typedef typename Engine::result_type base_result;
      result_type factor = result_type(1) /
              (result_type(base_result((eng.max)()-(eng.min)())) +
               result_type(std::numeric_limits<base_result>::is_integer ? 1 : 0));
      result_type result = result_type(base_result(eng() - (eng.min)())) * factor;
      if (result < result_type(1))
        return result;
    }
  }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
  template<class CharT, class Traits>
  friend std::basic_ostream<CharT,Traits>&
  operator<<(std::basic_ostream<CharT,Traits>& os, const new_uniform_01&)
  {
    return os;
  }

  template<class CharT, class Traits>
  friend std::basic_istream<CharT,Traits>&
  operator>>(std::basic_istream<CharT,Traits>& is, new_uniform_01&)
  {
    return is;
  }
#endif
};

template<class UniformRandomNumberGenerator, class RealType>
class backward_compatible_uniform_01
{
  typedef boost::random::detail::ptr_helper<UniformRandomNumberGenerator> traits;
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;

  BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);

#if !defined(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS)
  BOOST_STATIC_ASSERT(!std::numeric_limits<RealType>::is_integer);
#endif

  explicit backward_compatible_uniform_01(typename traits::rvalue_type rng)
    : _rng(rng),
      _factor(result_type(1) /
              (result_type((base().max)()-(base().min)()) +
               result_type(std::numeric_limits<base_result>::is_integer ? 1 : 0)))
  {
  }
  // compiler-generated copy ctor and copy assignment are fine

  result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return result_type(0); }
  result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return result_type(1); }
  typename traits::value_type& base() { return traits::ref(_rng); }
  const typename traits::value_type& base() const { return traits::ref(_rng); }
  void reset() { }

  result_type operator()() {
    for (;;) {
      result_type result = result_type(base()() - (base().min)()) * _factor;
      if (result < result_type(1))
        return result;
    }
  }

#if !defined(BOOST_NO_OPERATORS_IN_NAMESPACE) && !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  template<class CharT, class Traits>
  friend std::basic_ostream<CharT,Traits>&
  operator<<(std::basic_ostream<CharT,Traits>& os, const backward_compatible_uniform_01& u)
  {
    os << u._rng;
    return os;
  }

  template<class CharT, class Traits>
  friend std::basic_istream<CharT,Traits>&
  operator>>(std::basic_istream<CharT,Traits>& is, backward_compatible_uniform_01& u)
  {
    is >> u._rng;
    return is;
  }
#endif

private:
  typedef typename traits::value_type::result_type base_result;
  UniformRandomNumberGenerator _rng;
  result_type _factor;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class UniformRandomNumberGenerator, class RealType>
const bool backward_compatible_uniform_01<UniformRandomNumberGenerator, RealType>::has_fixed_range;
#endif

template<class UniformRandomNumberGenerator, bool is_number = std::numeric_limits<UniformRandomNumberGenerator>::is_specialized>
struct select_uniform_01
{
  template<class RealType>
  struct apply
  {
    typedef backward_compatible_uniform_01<UniformRandomNumberGenerator, RealType> type;
  };
};

template<class Num>
struct select_uniform_01<Num, true>
{
  template<class RealType>
  struct apply
  {
    typedef new_uniform_01<Num> type;
  };
};

}

// Because it is so commonly used: uniform distribution on the real [0..1)
// range.  This allows for specializations to avoid a costly int -> float
// conversion plus float multiplication
template<class UniformRandomNumberGenerator = double, class RealType = double>
class uniform_01
  : public detail::select_uniform_01<UniformRandomNumberGenerator>::BOOST_NESTED_TEMPLATE apply<RealType>::type
{
  typedef typename detail::select_uniform_01<UniformRandomNumberGenerator>::BOOST_NESTED_TEMPLATE apply<RealType>::type impl_type;
  typedef boost::random::detail::ptr_helper<UniformRandomNumberGenerator> traits;
public:

  uniform_01() {}

  explicit uniform_01(typename traits::rvalue_type rng)
    : impl_type(rng)
  {
  }

#if !defined(BOOST_NO_OPERATORS_IN_NAMESPACE) && !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  template<class CharT, class Traits>
  friend std::basic_ostream<CharT,Traits>&
  operator<<(std::basic_ostream<CharT,Traits>& os, const uniform_01& u)
  {
    os << static_cast<const impl_type&>(u);
    return os;
  }

  template<class CharT, class Traits>
  friend std::basic_istream<CharT,Traits>&
  operator>>(std::basic_istream<CharT,Traits>& is, uniform_01& u)
  {
    is >> static_cast<impl_type&>(u);
    return is;
  }
#endif
};

#endif

} // namespace random

using random::uniform_01;

} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_UNIFORM_01_HPP

/* uniform_01.hpp
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
*/