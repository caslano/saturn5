// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// no include guard multiple inclusion intended

//
// This is a temporary workaround until the bulk of this is
// available in boost config.
// 23/02/03 thw
//

#include <boost/config.hpp> // for prior
#include <boost/detail/workaround.hpp>

#ifdef BOOST_ITERATOR_CONFIG_DEF
# error you have nested config_def #inclusion.
#else 
# define BOOST_ITERATOR_CONFIG_DEF
#endif 

// We enable this always now.  Otherwise, the simple case in
// libs/iterator/test/constant_iterator_arrow.cpp fails to compile
// because the operator-> return is improperly deduced as a non-const
// pointer.
#if 1 || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)           \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x531))

// Recall that in general, compilers without partial specialization
// can't strip constness.  Consider counting_iterator, which normally
// passes a const Value to iterator_facade.  As a result, any code
// which makes a std::vector of the iterator's value_type will fail
// when its allocator declares functions overloaded on reference and
// const_reference (the same type).
//
// Furthermore, Borland 5.5.1 drops constness in enough ways that we
// end up using a proxy for operator[] when we otherwise shouldn't.
// Using reference constness gives it an extra hint that it can
// return the value_type from operator[] directly, but is not
// strictly necessary.  Not sure how best to resolve this one.

# define BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY 1

#endif

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x5A0))                      \
    || (BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 700) && defined(_MSC_VER)) \
    || BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))                \
    || BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
    
# define BOOST_NO_LVALUE_RETURN_DETECTION

# if 0 // test code
  struct v  {};

  typedef  char (&no)[3];

  template <class T>
  no foo(T const&, ...);

  template <class T>
  char foo(T&, int);


  struct value_iterator
  {
      v operator*() const;
  };

  template <class T>
  struct lvalue_deref_helper
  {
      static T& x;
      enum { value = (sizeof(foo(*x,0)) == 1) };
  };

  int z2[(lvalue_deref_helper<v*>::value == 1) ? 1 : -1];
  int z[(lvalue_deref_helper<value_iterator>::value) == 1 ? -1 : 1 ];
# endif 

#endif

#if BOOST_WORKAROUND(__MWERKS__, <=0x2407)
#  define BOOST_NO_IS_CONVERTIBLE // "is_convertible doesn't work for simple types"
#endif

#if BOOST_WORKAROUND(__GNUC__, == 3) && BOOST_WORKAROUND(__GNUC_MINOR__, < 4) && !defined(__EDG_VERSION__)   \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
#  define BOOST_NO_IS_CONVERTIBLE_TEMPLATE // The following program fails to compile:

#  if 0 // test code
    #include <boost/type_traits/is_convertible.hpp>
    template <class T>
    struct foo
    {
        foo(T);

        template <class U>
        foo(foo<U> const& other) : p(other.p) { }

        T p;
    };

    bool x = boost::is_convertible<foo<int const*>, foo<int*> >::value;
#  endif

#endif


#if !defined(BOOST_MSVC) && (defined(BOOST_NO_SFINAE) || defined(BOOST_NO_IS_CONVERTIBLE) || defined(BOOST_NO_IS_CONVERTIBLE_TEMPLATE))
# define BOOST_NO_STRICT_ITERATOR_INTEROPERABILITY
#endif 

# if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

// GCC-2.95 (obsolete) eagerly instantiates templated constructors and conversion
// operators in convertibility checks, causing premature errors.
//
// Borland's problems are harder to diagnose due to lack of an
// instantiation stack backtrace.  They may be due in part to the fact
// that it drops cv-qualification willy-nilly in templates.
#  define BOOST_NO_ONE_WAY_ITERATOR_INTEROP
# endif 

// no include guard; multiple inclusion intended

/* config_def.hpp
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
*/