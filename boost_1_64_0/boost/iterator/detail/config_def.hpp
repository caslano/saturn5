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
67/0q++/m8RtlNkQpT4G5aHeLpLfx9jfLpIGqfSOyre3UW9QHhH/W9DawjCeOXGuk6ra3UfiN5plpNqhOmt2Vrmb6vy2qo9VkndW1Y/4uV6NKzFs2+nG4NilKMtR4Rgr0blC5u4IDQ+pF9E6onmoI9IZYvtmVUfjJWyqrTwK1HcViFuiyvtMoZ1IaUis59z4NfKx8F8pH5P3TtheLL51bqn32yaP2miLj3Wm7sIe1gEf9W/IvQ/Y1+FnbpnwMTKwYkSLtFTfkWwVVtj6//XiP13HhxiXaejq7UZxS7HXm+o7y8UtoSad2QPtutqkzFTeqEuc35kdof/Ojb7fmZtfUjyptNB1gu99wv/3Mk5T2nFPlG8M0t6F9hUZZaIdR9fYjv9cQ3k8y/Kw2u2J9Ijry8S77rtG6stknyqT889j1ddYFp/4LwvGpa/7gzV861enoe5PVrZibaKJ399fMH3AhqbfOLq6v5o2/8PKvb9+2Ypvbe9LWO0xA5hI3pcBXAz7NexWNT8E8jzcqs9NDJuNLh3N88j2wJHAc4FXALsARwEvAuYBsykPMJdyAzdSbmAd0MXz44nAp4GTeI5cBHwLeBXwPWAJz5Gn8By5FGhlrgwYAiwHxgErgWnABTy/NUyOk5ynZQAbwR7md6yi7pa1wK7Au4HdgfcALwCu4/ns74Bu4Hp+x33A6ymvsYTyGsuBTwBvBv6J5+RPAX9HuY0XgJuBO4BbgJ8DnwOGUR4jAriN3/ECsBnlMtoCXwL2A24HXgrcAbwc+DKwAPgKcCJwJ3AacBfwWuDrLIccxYOlr0s5hMFmshwS4GwCE4ExwBRgEjAVmApMA6YDGwGbA/G/0uW0UcVbXZdTM8bbnuHOt+VnXw35WcRwi5mfm5ifZczPcuZnBeO9GYg6r7WeG56Pn9LZuKXfJmsKzsVhV8Fugn0neCYeNEETNEETNEETNEETNEETNEETNEFz0ubsnP9PnHC6zv/fsJ3/7+WGpaUDuSlwMTC6JfZNJnidE0riuZ2UBIBWr0oc8IIC/+d9iFN/3kcdZe+K+1R1v32H0A3V2dRRibuT/l7uBN/zPzxmVKl995J+/euy2C/uE804pvum0MXmX41b1P3JOyQvWp0WjN+/TosD4j7B9JwV7hK6zHxJzrLxm4q/gfas0B6/23amp71/a/cr5YIqBGrO9+hXfwd/k3WPWNzHq/rZJ3S67vwPcWl0j7GNvCJuFWaZ8aG6339IfrvStPzvaS977eLfxH/9pSyGGqF8Q8pk+XhkPB5A+M44y9hU9d6Csds6ywgpD3VGOppGmrERoyP6RQyIGBgaGhITGhXpiMHhxuhQyrC8LWmVWfUjcb3D93zctrMAeTNL0rufNCRCmL511nHm7+xbbbn2Z3Seu51un3O4NOs3iU/agF8Zg7wCvS6yzHDyCu6JLjLIK1waXtGjZl6RBPxSwoXoeYWrZtmAD8Rde0dfhY2zywJMchfZz3bfED/pev7g0vIH1X/fEnf3z/fzhZ6HE/kWen7g0vIDdT61X9xH6/u6K4C+7gqgr7u0fV3xwPfEvfxnnQFCl6HeO+j7O+NrhX64D/nMC6vqhyG9I/pGDI4YEBoaWbd+pDMqtF5keLit74Wz71lvgDlYXomFrFv2R6uPnQm9OYlefYxtJICz8FPtZ8dc+n62NMoQc7UDeQDOBFr9rLxQ08/8y+ShdfeRvPxOwg10jMK993AzyfiNGYr3DVJVX7pD3Eep9njNRL57y376pNDfgSNfpXSTDpHf7jRjjHlmIsfEJpOs37ahfXU3CiFflig6S5lvfM0SpP97M1S1G7rpdXLwrcR7xH2IYyzCRppdzTjKej0r6Xc=
*/