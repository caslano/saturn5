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
ZU/7ScMpjsu9jAEazJ3zaM5V74WlpyUH+5mP9He1uWLc4C6yJ/3ixMAToVEGhcpwhUlAqlIKoN8glsUQD4fU30YzEjLGbdTtNXzByNzHVGnSf+nbHg79f1GfeuTV0s5fEMmJqFnZQVKoQMM8nKxgazCX9gWSklEAmHj7NVxACHQJ6Q8HUc2pc01x2PAqXlahoR+dZfVkxlDa8b+Kr32yyyshb+LkG+c7+5R3RUvu9XlftrFgXO51SAZfTLi8rJm2cVh18uNQX15EOQE9Do/qoFg0spqKsbTZeZXa91pAL3EJNNzEOaewzlLLBWXkThTXEDimM3JolwmK4I5Qb3bIr1Mfnp2ciyCoe3EfsUdH2KP3AxgZ2SIgb0g0+Gnl52VEjRCD/DT424/Zeqvg8SIXHijaugLF4FE6E5eipAw2LOYgus/tGRaAnFnyBPyUebHhlgImnj+OrLpsHWlRJYDMoFPBGlD+e8tnjVIltz2GAtFG9UutD7u3++5trDQttSp14x1X2aAJFn7MIeKOnN94MkfesO+Zs1hwJnfcrJnS7iagbSFuLg+lkvr3yw==
*/