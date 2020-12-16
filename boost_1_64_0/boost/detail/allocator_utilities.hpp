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
0Je7u+iC1hTviZoU3qRdN8neYIHzce7f0YBzbxZ0xhLnEp2wu5WdYM7lGo/2ViMmOOXgP6jGTXTEBNbw5L/VHU466PMqpzaFNLYXNbYA65S6xvliIjRNRa6fAuNXr8fvyEGH8Vs9CGaDgBIf56hoPapkOh3UFgrWn5VUQb1L+XR2nLra89Tv/+pn9+rNHCuuIeebqurNnuMqLy+2C8fh5Csl+QBJv4FoscV8RwCqPZfgI2lfougvuw/T+UR469bhMRNNvWaHHW3MBG+APgtckfyzy5Y73aiwEivw1vt72T8C8ikft2VyqIkhWxa660o79ZxXletX4zWihpoq3l+v0psxNxHCd0mEzfP5rdvojBeE0hGsU9PZmAmxGHYy6oEM7PeT7OTrhT/KR9vO89sZpSi6vwNv2FqUZoSAPho/y9xy3a2UJIw3ls6iStqNredbGGvBHStUvrP+gCuCwfAX5gr308Vrltl6lVxE5nKwkN6tOefYYXmGqvjBWtJE0vdGVvUYnzCMT6rNNHKdGVRweXNJ2AD1NA8WWTTess1VtANdle6xIjl1sMwbwQU9xr/cNv62Uf83pOEWJvItTp+Fevh+OkH6CESd/R6LnbeaxqJKv64bRDtAyc9b+C3TyF+p+6zzUAX7HmE41Dgo92NnsmIPBvGNh+96wcWVcQC4D9E619MnuaD2gvFdPSulbjg5Q2Q/L946wnKfG337CBioeBPE79H1QoM4GGyG0nFS19eZryTVqh6kG9WC9DeQ+MTfD8tDAPGFmMOyDOFcOzkty96C2XCYGfNodlSQEKWKFLwbOMH72nq0v8zefmwwr1d7vWwA3FmO69VZ0fStvlMni8/+xYuFmyNYqQ/MJ9dwBDeuZtUymFsAGpeg1YyyARBWn52uHvA2rzAbX7Kfomp7MrBqYc88+i5uVIug3QFxwigCjLzFXyIR6gZ/XyyKRmBJVJ1XT3NIB7k4eR8zPMN/KlWbmp19abEEs7qdbIFJIyCQOBxnGKMLV8vB6fd+YpTX6efoD2/E/a9hHB8ctpwPWf+7w3zS9LIc4QKerHzIdAH8YJOY/D07cM05yKEm82nIJLPQJD5KNSIm5W5KiZmU2zBF3uDXhYfY2WjbhMXkaYOWxBcHkOvpsy5Fd8gg8mYufSWUJrwyRLxFrwEvjCV/x3wux94CeQ1tU2LqbxTFWHCMC0C+E5UB/svbC+JI4te/ZoA/8NowCzt6IUO7ly+VFah+NZwyW73iZHV8NBu9XO6lMVTuMijHPcYh3zGMUrA2Ys/vyUx+i6rhkL+TIZaofHktCURI18LtASDeyVc5azzILj7oYaBEE4kAux+eYn+4zngbu0se9lj7cKdVzD05msi4xQjK236NrpsI+jq5mXhtsOGVPWeZUa0dlj5E7lnrS12AD3Ffaqy9D7+mUflS45JFSoLAXSc50iF7kbI+2BFk2Hz2c4cxGOMND3p6A3+O+/NhPP9Rwle5xDx++LgRdDle3Ee33/5MPUIabt3H8PA6dG/af3WUNyt2Gv/lB5Q3Wj+d+TvS2tzu5IIrT9de2ANsNLGzkMa6DsPuxcdrV8JhRHzyDcSd4NjG5PKZnet8KV/qCxrtAoXWQKeLdYNKJynS2ZNUdp+/AZmxf53lf5Dlf8wjuXKesnX4PJ+U5v8BEUfOf/4aj8z/LeVDut572HO5RwQcr+StmK2igLzvOVpA/foROTsjUiKFLbu38jrvKgzGkv69HU6CtSlx1gjCEoCWW+bjV1ULgKFez/koxsNmqVw1SJ53ks6H3+WkY0q/brZtfv5zlIKwVc1JF/4Wk/hq6LRUrYVHvgPj+6O1gdLIwo93K/aUpyGVSMkHSvM=
*/