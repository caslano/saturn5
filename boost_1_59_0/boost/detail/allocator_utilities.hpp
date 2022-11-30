/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See Boost website at http://www.boost.org/
 */

#ifndef BOOST_DETAIL_ALLOCATOR_UTILITIES_HPP
#define BOOST_DETAIL_ALLOCATOR_UTILITIES_HPP

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/detail/select_type.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cstddef>
#include <memory>
#include <new>

namespace boost{

namespace detail{

/* Allocator adaption layer. Some stdlibs provide allocators without rebind
 * and template ctors. These facilities are simulated with the external
 * template class rebind_to and the aid of partial_std_allocator_wrapper.
 */

namespace allocator{

/* partial_std_allocator_wrapper inherits the functionality of a std
 * allocator while providing a templatized ctor and other bits missing
 * in some stdlib implementation or another.
 */

template<typename Type>
class partial_std_allocator_wrapper:public std::allocator<Type>
{
public:
  /* Oddly enough, STLport does not define std::allocator<void>::value_type
   * when configured to work without partial template specialization.
   * No harm in supplying the definition here unconditionally.
   */

  typedef Type value_type;

  partial_std_allocator_wrapper(){}

  template<typename Other>
  partial_std_allocator_wrapper(const partial_std_allocator_wrapper<Other>&){}

  partial_std_allocator_wrapper(const std::allocator<Type>& x):
    std::allocator<Type>(x)
  {
  }

#if defined(BOOST_DINKUMWARE_STDLIB)
  /* Dinkumware guys didn't provide a means to call allocate() without
   * supplying a hint, in disagreement with the standard.
   */

  Type* allocate(std::size_t n,const void* hint=0)
  {
    std::allocator<Type>& a=*this;
    return a.allocate(n,hint);
  }
#endif

};

/* Detects whether a given allocator belongs to a defective stdlib not
 * having the required member templates.
 * Note that it does not suffice to check the Boost.Config stdlib
 * macros, as the user might have passed a custom, compliant allocator.
 * The checks also considers partial_std_allocator_wrapper to be
 * a standard defective allocator.
 */

#if defined(BOOST_NO_STD_ALLOCATOR)&&\
  (defined(BOOST_HAS_PARTIAL_STD_ALLOCATOR)||defined(BOOST_DINKUMWARE_STDLIB))

template<typename Allocator>
struct is_partial_std_allocator
{
  BOOST_STATIC_CONSTANT(bool,
    value=
      (is_same<
        std::allocator<BOOST_DEDUCED_TYPENAME Allocator::value_type>,
        Allocator
      >::value)||
      (is_same<
        partial_std_allocator_wrapper<
          BOOST_DEDUCED_TYPENAME Allocator::value_type>,
        Allocator
      >::value));
};

#else

template<typename Allocator>
struct is_partial_std_allocator
{
  BOOST_STATIC_CONSTANT(bool,value=false);
};

#endif

/* rebind operations for defective std allocators */

template<typename Allocator,typename Type>
struct partial_std_allocator_rebind_to
{
  typedef partial_std_allocator_wrapper<Type> type;
};

/* rebind operation in all other cases */

template<typename Allocator>
struct rebinder
{
  template<typename Type>
  struct result
  {
#ifdef BOOST_NO_CXX11_ALLOCATOR
      typedef typename Allocator::BOOST_NESTED_TEMPLATE
          rebind<Type>::other other;
#else
      typedef typename std::allocator_traits<Allocator>::BOOST_NESTED_TEMPLATE
          rebind_alloc<Type> other;
#endif
  };
};

template<typename Allocator,typename Type>
struct compliant_allocator_rebind_to
{
  typedef typename rebinder<Allocator>::
      BOOST_NESTED_TEMPLATE result<Type>::other type;
};

/* rebind front-end */

template<typename Allocator,typename Type>
struct rebind_to:
  boost::detail::if_true<
    is_partial_std_allocator<Allocator>::value
  >::template then<
    partial_std_allocator_rebind_to<Allocator,Type>,
    compliant_allocator_rebind_to<Allocator,Type>
  >::type
{
};

/* allocator-independent versions of construct and destroy */

template<typename Type>
void construct(void* p,const Type& t)
{
  new (p) Type(t);
}

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1500))
/* MSVC++ issues spurious warnings about unreferencend formal parameters
 * in destroy<Type> when Type is a class with trivial dtor.
 */

#pragma warning(push)
#pragma warning(disable:4100)
#endif

template<typename Type>
void destroy(const Type* p)
{

#if BOOST_WORKAROUND(__SUNPRO_CC,BOOST_TESTED_AT(0x590))
  const_cast<Type*>(p)->~Type();
#else
  p->~Type();
#endif

}

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1500))
#pragma warning(pop)
#endif

} /* namespace boost::detail::allocator */

} /* namespace boost::detail */

} /* namespace boost */

#endif

/* allocator_utilities.hpp
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
*/