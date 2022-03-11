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