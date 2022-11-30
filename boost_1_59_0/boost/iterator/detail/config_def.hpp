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
    || BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x531))

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

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x5A0))                      \
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
    || BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x551))
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

# if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))

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