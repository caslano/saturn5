//
// (C) Copyright Jeremy Siek 2000.
// Copyright 2002 The Trustees of Indiana University.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Revision History:
//   05 May   2001: Workarounds for HP aCC from Thomas Matelich. (Jeremy Siek)
//   02 April 2001: Removed limits header altogether. (Jeremy Siek)
//   01 April 2001: Modified to use new <boost/limits.hpp> header. (JMaddock)
//

// See http://www.boost.org/libs/concept_check for documentation.

#ifndef BOOST_CONCEPT_CHECKS_HPP
# define BOOST_CONCEPT_CHECKS_HPP

# include <boost/concept/assert.hpp>

# include <iterator>
# include <boost/type_traits/conversion_traits.hpp>
# include <utility>
# include <boost/type_traits/is_same.hpp>
# include <boost/type_traits/is_void.hpp>
# include <boost/static_assert.hpp>
# include <boost/type_traits/integral_constant.hpp>
# include <boost/config/workaround.hpp>

# include <boost/concept/usage.hpp>
# include <boost/concept/detail/concept_def.hpp>

#if (defined _MSC_VER)
# pragma warning( push )
# pragma warning( disable : 4510 ) // default constructor could not be generated
# pragma warning( disable : 4610 ) // object 'class' can never be instantiated - user-defined constructor required
#endif

namespace boost
{

  //
  // Backward compatibility
  //

  template <class Model>
  inline void function_requires(Model* = 0)
  {
      BOOST_CONCEPT_ASSERT((Model));
  }
  template <class T> inline void ignore_unused_variable_warning(T const&) {}

#  define BOOST_CLASS_REQUIRE(type_var, ns, concept)    \
    BOOST_CONCEPT_ASSERT((ns::concept<type_var>))

#  define BOOST_CLASS_REQUIRE2(type_var1, type_var2, ns, concept)   \
    BOOST_CONCEPT_ASSERT((ns::concept<type_var1,type_var2>))

#  define BOOST_CLASS_REQUIRE3(tv1, tv2, tv3, ns, concept)  \
    BOOST_CONCEPT_ASSERT((ns::concept<tv1,tv2,tv3>))

#  define BOOST_CLASS_REQUIRE4(tv1, tv2, tv3, tv4, ns, concept) \
    BOOST_CONCEPT_ASSERT((ns::concept<tv1,tv2,tv3,tv4>))


  //
  // Begin concept definitions
  //
  BOOST_concept(Integer, (T))
  {
      BOOST_CONCEPT_USAGE(Integer)
        {
            x.error_type_must_be_an_integer_type();
        }
   private:
      T x;
  };

  template <> struct Integer<char> {};
  template <> struct Integer<signed char> {};
  template <> struct Integer<unsigned char> {};
  template <> struct Integer<short> {};
  template <> struct Integer<unsigned short> {};
  template <> struct Integer<int> {};
  template <> struct Integer<unsigned int> {};
  template <> struct Integer<long> {};
  template <> struct Integer<unsigned long> {};
# if defined(BOOST_HAS_LONG_LONG)
  template <> struct Integer< ::boost::long_long_type> {};
  template <> struct Integer< ::boost::ulong_long_type> {};
# elif defined(BOOST_HAS_MS_INT64)
  template <> struct Integer<__int64> {};
  template <> struct Integer<unsigned __int64> {};
# endif

  BOOST_concept(SignedInteger,(T)) {
    BOOST_CONCEPT_USAGE(SignedInteger) {
      x.error_type_must_be_a_signed_integer_type();
    }
   private:
    T x;
  };
  template <> struct SignedInteger<signed char> { };
  template <> struct SignedInteger<short> {};
  template <> struct SignedInteger<int> {};
  template <> struct SignedInteger<long> {};
# if defined(BOOST_HAS_LONG_LONG)
  template <> struct SignedInteger< ::boost::long_long_type> {};
# elif defined(BOOST_HAS_MS_INT64)
  template <> struct SignedInteger<__int64> {};
# endif

  BOOST_concept(UnsignedInteger,(T)) {
    BOOST_CONCEPT_USAGE(UnsignedInteger) {
      x.error_type_must_be_an_unsigned_integer_type();
    }
   private:
    T x;
  };

  template <> struct UnsignedInteger<unsigned char> {};
  template <> struct UnsignedInteger<unsigned short> {};
  template <> struct UnsignedInteger<unsigned int> {};
  template <> struct UnsignedInteger<unsigned long> {};
# if defined(BOOST_HAS_LONG_LONG)
  template <> struct UnsignedInteger< ::boost::ulong_long_type> {};
# elif defined(BOOST_HAS_MS_INT64)
  template <> struct UnsignedInteger<unsigned __int64> {};
# endif

  //===========================================================================
  // Basic Concepts

  BOOST_concept(DefaultConstructible,(TT))
  {
    BOOST_CONCEPT_USAGE(DefaultConstructible) {
      TT a;               // require default constructor
      ignore_unused_variable_warning(a);
    }
  };

  BOOST_concept(Assignable,(TT))
  {
    BOOST_CONCEPT_USAGE(Assignable) {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = b;             // require assignment operator
#endif
      const_constraints(b);
    }
   private:
    void const_constraints(const TT& x) {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = x;              // const required for argument to assignment
#else
      ignore_unused_variable_warning(x);
#endif
    }
   private:
    TT a;
    TT b;
  };


  BOOST_concept(CopyConstructible,(TT))
  {
    BOOST_CONCEPT_USAGE(CopyConstructible) {
      TT a(b);            // require copy constructor
      TT* ptr = &a;       // require address of operator
      const_constraints(a);
      ignore_unused_variable_warning(ptr);
    }
   private:
    void const_constraints(const TT& a) {
      TT c(a);            // require const copy constructor
      const TT* ptr = &a; // require const address of operator
      ignore_unused_variable_warning(c);
      ignore_unused_variable_warning(ptr);
    }
    TT b;
  };

  // The SGI STL version of Assignable requires copy constructor and operator=
  BOOST_concept(SGIAssignable,(TT))
  {
    BOOST_CONCEPT_USAGE(SGIAssignable) {
      TT c(a);
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = b;              // require assignment operator
#endif
      const_constraints(b);
      ignore_unused_variable_warning(c);
    }
   private:
    void const_constraints(const TT& x) {
      TT c(x);
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
      a = x;              // const required for argument to assignment
#endif
      ignore_unused_variable_warning(c);
    }
    TT a;
    TT b;
  };

  BOOST_concept(Convertible,(X)(Y))
  {
    BOOST_CONCEPT_USAGE(Convertible) {
      Y y = x;
      ignore_unused_variable_warning(y);
    }
   private:
    X x;
  };

  // The C++ standard requirements for many concepts talk about return
  // types that must be "convertible to bool".  The problem with this
  // requirement is that it leaves the door open for evil proxies that
  // define things like operator|| with strange return types.  Two
  // possible solutions are:
  // 1) require the return type to be exactly bool
  // 2) stay with convertible to bool, and also
  //    specify stuff about all the logical operators.
  // For now we just test for convertible to bool.
  template <class TT>
  void require_boolean_expr(const TT& t) {
    bool x = t;
    ignore_unused_variable_warning(x);
  }

  BOOST_concept(EqualityComparable,(TT))
  {
    BOOST_CONCEPT_USAGE(EqualityComparable) {
      require_boolean_expr(a == b);
      require_boolean_expr(a != b);
    }
   private:
    TT a, b;
  };

  BOOST_concept(LessThanComparable,(TT))
  {
    BOOST_CONCEPT_USAGE(LessThanComparable) {
      require_boolean_expr(a < b);
    }
   private:
    TT a, b;
  };

  // This is equivalent to SGI STL's LessThanComparable.
  BOOST_concept(Comparable,(TT))
  {
    BOOST_CONCEPT_USAGE(Comparable) {
      require_boolean_expr(a < b);
      require_boolean_expr(a > b);
      require_boolean_expr(a <= b);
      require_boolean_expr(a >= b);
    }
   private:
    TT a, b;
  };

#define BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(OP,NAME)    \
  BOOST_concept(NAME, (First)(Second))                          \
  {                                                             \
      BOOST_CONCEPT_USAGE(NAME) { (void)constraints_(); }                         \
     private:                                                   \
        bool constraints_() { return a OP b; }                  \
        First a;                                                \
        Second b;                                               \
  }

#define BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(OP,NAME)    \
  BOOST_concept(NAME, (Ret)(First)(Second))                 \
  {                                                         \
      BOOST_CONCEPT_USAGE(NAME) { (void)constraints_(); }                     \
  private:                                                  \
      Ret constraints_() { return a OP b; }                 \
      First a;                                              \
      Second b;                                             \
  }

  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(==, EqualOp);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(!=, NotEqualOp);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(<, LessThanOp);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(<=, LessEqualOp);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(>, GreaterThanOp);
  BOOST_DEFINE_BINARY_PREDICATE_OP_CONSTRAINT(>=, GreaterEqualOp);

  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(+, PlusOp);
  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(*, TimesOp);
  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(/, DivideOp);
  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(-, SubtractOp);
  BOOST_DEFINE_BINARY_OPERATOR_CONSTRAINT(%, ModOp);

  //===========================================================================
  // Function Object Concepts

  BOOST_concept(Generator,(Func)(Return))
  {
      BOOST_CONCEPT_USAGE(Generator) { test(is_void<Return>()); }

   private:
      void test(boost::false_type)
      {
          // Do we really want a reference here?
          const Return& r = f();
          ignore_unused_variable_warning(r);
      }

      void test(boost::true_type)
      {
          f();
      }

      Func f;
  };

  BOOST_concept(UnaryFunction,(Func)(Return)(Arg))
  {
      BOOST_CONCEPT_USAGE(UnaryFunction) { test(is_void<Return>()); }

   private:
      void test(boost::false_type)
      {
          f(arg);               // "priming the pump" this way keeps msvc6 happy (ICE)
          Return r = f(arg);
          ignore_unused_variable_warning(r);
      }

      void test(boost::true_type)
      {
          f(arg);
      }

#if (BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4) \
                      && BOOST_WORKAROUND(__GNUC__, > 3)))
      // Declare a dummy constructor to make gcc happy.
      // It seems the compiler can not generate a sensible constructor when this is instantiated with a reference type.
      // (warning: non-static reference "const double& boost::UnaryFunction<YourClassHere>::arg"
      // in class without a constructor [-Wuninitialized])
      UnaryFunction();
#endif

      Func f;
      Arg arg;
  };

  BOOST_concept(BinaryFunction,(Func)(Return)(First)(Second))
  {
      BOOST_CONCEPT_USAGE(BinaryFunction) { test(is_void<Return>()); }
   private:
      void test(boost::false_type)
      {
          (void) f(first,second);
          Return r = f(first, second); // require operator()
          (void)r;
      }

      void test(boost::true_type)
      {
          f(first,second);
      }

#if (BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4) \
                      && BOOST_WORKAROUND(__GNUC__, > 3)))
      // Declare a dummy constructor to make gcc happy.
      // It seems the compiler can not generate a sensible constructor when this is instantiated with a reference type.
      // (warning: non-static reference "const double& boost::BinaryFunction<YourClassHere>::arg"
      // in class without a constructor [-Wuninitialized])
      BinaryFunction();
#endif

      Func f;
      First first;
      Second second;
  };

  BOOST_concept(UnaryPredicate,(Func)(Arg))
  {
    BOOST_CONCEPT_USAGE(UnaryPredicate) {
      require_boolean_expr(f(arg)); // require operator() returning bool
    }
   private:
#if (BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4) \
                      && BOOST_WORKAROUND(__GNUC__, > 3)))
      // Declare a dummy constructor to make gcc happy.
      // It seems the compiler can not generate a sensible constructor when this is instantiated with a reference type.
      // (warning: non-static reference "const double& boost::UnaryPredicate<YourClassHere>::arg"
      // in class without a constructor [-Wuninitialized])
      UnaryPredicate();
#endif

    Func f;
    Arg arg;
  };

  BOOST_concept(BinaryPredicate,(Func)(First)(Second))
  {
    BOOST_CONCEPT_USAGE(BinaryPredicate) {
      require_boolean_expr(f(a, b)); // require operator() returning bool
    }
   private:
#if (BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4) \
                      && BOOST_WORKAROUND(__GNUC__, > 3)))
      // Declare a dummy constructor to make gcc happy.
      // It seems the compiler can not generate a sensible constructor when this is instantiated with a reference type.
      // (warning: non-static reference "const double& boost::BinaryPredicate<YourClassHere>::arg"
      // in class without a constructor [-Wuninitialized])
      BinaryPredicate();
#endif
    Func f;
    First a;
    Second b;
  };

  // use this when functor is used inside a container class like std::set
  BOOST_concept(Const_BinaryPredicate,(Func)(First)(Second))
    : BinaryPredicate<Func, First, Second>
  {
    BOOST_CONCEPT_USAGE(Const_BinaryPredicate) {
      const_constraints(f);
    }
   private:
    void const_constraints(const Func& fun) {
      // operator() must be a const member function
      require_boolean_expr(fun(a, b));
    }
#if (BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4) \
                      && BOOST_WORKAROUND(__GNUC__, > 3)))
      // Declare a dummy constructor to make gcc happy.
      // It seems the compiler can not generate a sensible constructor when this is instantiated with a reference type.
      // (warning: non-static reference "const double& boost::Const_BinaryPredicate<YourClassHere>::arg"
      // in class without a constructor [-Wuninitialized])
      Const_BinaryPredicate();
#endif

    Func f;
    First a;
    Second b;
  };

  BOOST_concept(AdaptableGenerator,(Func)(Return))
    : Generator<Func, typename Func::result_type>
  {
      typedef typename Func::result_type result_type;

      BOOST_CONCEPT_USAGE(AdaptableGenerator)
      {
          BOOST_CONCEPT_ASSERT((Convertible<result_type, Return>));
      }
  };

  BOOST_concept(AdaptableUnaryFunction,(Func)(Return)(Arg))
    : UnaryFunction<Func, typename Func::result_type, typename Func::argument_type>
  {
      typedef typename Func::argument_type argument_type;
      typedef typename Func::result_type result_type;

      ~AdaptableUnaryFunction()
      {
          BOOST_CONCEPT_ASSERT((Convertible<result_type, Return>));
          BOOST_CONCEPT_ASSERT((Convertible<Arg, argument_type>));
      }
  };

  BOOST_concept(AdaptableBinaryFunction,(Func)(Return)(First)(Second))
    : BinaryFunction<
          Func
        , typename Func::result_type
        , typename Func::first_argument_type
        , typename Func::second_argument_type
      >
  {
      typedef typename Func::first_argument_type first_argument_type;
      typedef typename Func::second_argument_type second_argument_type;
      typedef typename Func::result_type result_type;

      ~AdaptableBinaryFunction()
      {
          BOOST_CONCEPT_ASSERT((Convertible<result_type, Return>));
          BOOST_CONCEPT_ASSERT((Convertible<First, first_argument_type>));
          BOOST_CONCEPT_ASSERT((Convertible<Second, second_argument_type>));
      }
  };

  BOOST_concept(AdaptablePredicate,(Func)(Arg))
    : UnaryPredicate<Func, Arg>
    , AdaptableUnaryFunction<Func, bool, Arg>
  {
  };

  BOOST_concept(AdaptableBinaryPredicate,(Func)(First)(Second))
    : BinaryPredicate<Func, First, Second>
    , AdaptableBinaryFunction<Func, bool, First, Second>
  {
  };

  //===========================================================================
  // Iterator Concepts

  BOOST_concept(InputIterator,(TT))
    : Assignable<TT>
    , EqualityComparable<TT>
  {
      typedef typename std::iterator_traits<TT>::value_type value_type;
      typedef typename std::iterator_traits<TT>::difference_type difference_type;
      typedef typename std::iterator_traits<TT>::reference reference;
      typedef typename std::iterator_traits<TT>::pointer pointer;
      typedef typename std::iterator_traits<TT>::iterator_category iterator_category;

      BOOST_CONCEPT_USAGE(InputIterator)
      {
        BOOST_CONCEPT_ASSERT((SignedInteger<difference_type>));
        BOOST_CONCEPT_ASSERT((Convertible<iterator_category, std::input_iterator_tag>));

        TT j(i);
        (void)*i;           // require dereference operator
        ++j;                // require preincrement operator
        i++;                // require postincrement operator
      }
   private:
    TT i;
  };

  BOOST_concept(OutputIterator,(TT)(ValueT))
    : Assignable<TT>
  {
    BOOST_CONCEPT_USAGE(OutputIterator) {

      ++i;                // require preincrement operator
      i++;                // require postincrement operator
      *i++ = t;           // require postincrement and assignment
    }
   private:
    TT i, j;
    ValueT t;
  };

  BOOST_concept(ForwardIterator,(TT))
    : InputIterator<TT>
  {
      BOOST_CONCEPT_USAGE(ForwardIterator)
      {
          BOOST_CONCEPT_ASSERT((Convertible<
              BOOST_DEDUCED_TYPENAME ForwardIterator::iterator_category
            , std::forward_iterator_tag
          >));

          typename InputIterator<TT>::reference r = *i;
          ignore_unused_variable_warning(r);
      }

   private:
      TT i;
  };

  BOOST_concept(Mutable_ForwardIterator,(TT))
    : ForwardIterator<TT>
  {
      BOOST_CONCEPT_USAGE(Mutable_ForwardIterator) {
        *i++ = *j;         // require postincrement and assignment
      }
   private:
      TT i, j;
  };

  BOOST_concept(BidirectionalIterator,(TT))
    : ForwardIterator<TT>
  {
      BOOST_CONCEPT_USAGE(BidirectionalIterator)
      {
          BOOST_CONCEPT_ASSERT((Convertible<
              BOOST_DEDUCED_TYPENAME BidirectionalIterator::iterator_category
            , std::bidirectional_iterator_tag
          >));

          --i;                // require predecrement operator
          i--;                // require postdecrement operator
      }
   private:
      TT i;
  };

  BOOST_concept(Mutable_BidirectionalIterator,(TT))
    : BidirectionalIterator<TT>
    , Mutable_ForwardIterator<TT>
  {
      BOOST_CONCEPT_USAGE(Mutable_BidirectionalIterator)
      {
          *i-- = *j;                  // require postdecrement and assignment
      }
   private:
      TT i, j;
  };

  BOOST_concept(RandomAccessIterator,(TT))
    : BidirectionalIterator<TT>
    , Comparable<TT>
  {
      BOOST_CONCEPT_USAGE(RandomAccessIterator)
      {
          BOOST_CONCEPT_ASSERT((Convertible<
              BOOST_DEDUCED_TYPENAME BidirectionalIterator<TT>::iterator_category
            , std::random_access_iterator_tag
          >));

          i += n;             // require assignment addition operator
          i = i + n; i = n + i; // require addition with difference type
          i -= n;             // require assignment subtraction operator
          i = i - n;                  // require subtraction with difference type
          n = i - j;                  // require difference operator
          (void)i[n];                 // require element access operator
      }

   private:
    TT a, b;
    TT i, j;
      typename std::iterator_traits<TT>::difference_type n;
  };

  BOOST_concept(Mutable_RandomAccessIterator,(TT))
    : RandomAccessIterator<TT>
    , Mutable_BidirectionalIterator<TT>
  {
      BOOST_CONCEPT_USAGE(Mutable_RandomAccessIterator)
      {
          i[n] = *i;                  // require element access and assignment
      }
   private:
    TT i;
    typename std::iterator_traits<TT>::difference_type n;
  };

  //===========================================================================
  // Container s

  BOOST_concept(Container,(C))
    : Assignable<C>
  {
    typedef typename C::value_type value_type;
    typedef typename C::difference_type difference_type;
    typedef typename C::size_type size_type;
    typedef typename C::const_reference const_reference;
    typedef typename C::const_pointer const_pointer;
    typedef typename C::const_iterator const_iterator;

      BOOST_CONCEPT_USAGE(Container)
      {
          BOOST_CONCEPT_ASSERT((InputIterator<const_iterator>));
          const_constraints(c);
      }

   private:
      void const_constraints(const C& cc) {
          i = cc.begin();
          i = cc.end();
          n = cc.size();
          n = cc.max_size();
          b = cc.empty();
      }
      C c;
      bool b;
      const_iterator i;
      size_type n;
  };

  BOOST_concept(Mutable_Container,(C))
    : Container<C>
  {
      typedef typename C::reference reference;
      typedef typename C::iterator iterator;
      typedef typename C::pointer pointer;

      BOOST_CONCEPT_USAGE(Mutable_Container)
      {
          BOOST_CONCEPT_ASSERT((
               Assignable<typename Mutable_Container::value_type>));

          BOOST_CONCEPT_ASSERT((InputIterator<iterator>));

          i = c.begin();
          i = c.end();
          c.swap(c2);
      }

   private:
      iterator i;
      C c, c2;
  };

  BOOST_concept(ForwardContainer,(C))
    : Container<C>
  {
      BOOST_CONCEPT_USAGE(ForwardContainer)
      {
          BOOST_CONCEPT_ASSERT((
               ForwardIterator<
                    typename ForwardContainer::const_iterator
               >));
      }
  };

  BOOST_concept(Mutable_ForwardContainer,(C))
    : ForwardContainer<C>
    , Mutable_Container<C>
  {
      BOOST_CONCEPT_USAGE(Mutable_ForwardContainer)
      {
          BOOST_CONCEPT_ASSERT((
               Mutable_ForwardIterator<
                   typename Mutable_ForwardContainer::iterator
               >));
      }
  };

  BOOST_concept(ReversibleContainer,(C))
    : ForwardContainer<C>
  {
      typedef typename
        C::const_reverse_iterator
      const_reverse_iterator;

      BOOST_CONCEPT_USAGE(ReversibleContainer)
      {
          BOOST_CONCEPT_ASSERT((
              BidirectionalIterator<
                  typename ReversibleContainer::const_iterator>));

          BOOST_CONCEPT_ASSERT((BidirectionalIterator<const_reverse_iterator>));

          const_constraints(c);
      }
   private:
      void const_constraints(const C& cc)
      {
          const_reverse_iterator _i = cc.rbegin();
          _i = cc.rend();
      }
      C c;
  };

  BOOST_concept(Mutable_ReversibleContainer,(C))
    : Mutable_ForwardContainer<C>
    , ReversibleContainer<C>
  {
      typedef typename C::reverse_iterator reverse_iterator;

      BOOST_CONCEPT_USAGE(Mutable_ReversibleContainer)
      {
          typedef typename Mutable_ForwardContainer<C>::iterator iterator;
          BOOST_CONCEPT_ASSERT((Mutable_BidirectionalIterator<iterator>));
          BOOST_CONCEPT_ASSERT((Mutable_BidirectionalIterator<reverse_iterator>));

          reverse_iterator i = c.rbegin();
          i = c.rend();
      }
   private:
      C c;
  };

  BOOST_concept(RandomAccessContainer,(C))
    : ReversibleContainer<C>
  {
      typedef typename C::size_type size_type;
      typedef typename C::const_reference const_reference;

      BOOST_CONCEPT_USAGE(RandomAccessContainer)
      {
          BOOST_CONCEPT_ASSERT((
              RandomAccessIterator<
                  typename RandomAccessContainer::const_iterator
              >));

          const_constraints(c);
      }
   private:
      void const_constraints(const C& cc)
      {
          const_reference r = cc[n];
          ignore_unused_variable_warning(r);
      }

      C c;
      size_type n;
  };

  BOOST_concept(Mutable_RandomAccessContainer,(C))
    : Mutable_ReversibleContainer<C>
    , RandomAccessContainer<C>
  {
   private:
      typedef Mutable_RandomAccessContainer self;
   public:
      BOOST_CONCEPT_USAGE(Mutable_RandomAccessContainer)
      {
          BOOST_CONCEPT_ASSERT((Mutable_RandomAccessIterator<typename self::iterator>));
          BOOST_CONCEPT_ASSERT((Mutable_RandomAccessIterator<typename self::reverse_iterator>));

          typename self::reference r = c[i];
          ignore_unused_variable_warning(r);
      }

   private:
      typename Mutable_ReversibleContainer<C>::size_type i;
      C c;
  };

  // A Sequence is inherently mutable
  BOOST_concept(Sequence,(S))
    : Mutable_ForwardContainer<S>
      // Matt Austern's book puts DefaultConstructible here, the C++
      // standard places it in Container --JGS
      // ... so why aren't we following the standard?  --DWA
    , DefaultConstructible<S>
  {
      BOOST_CONCEPT_USAGE(Sequence)
      {
          S
              c(n, t),
              c2(first, last);

          c.insert(p, t);
          c.insert(p, n, t);
          c.insert(p, first, last);

          c.erase(p);
          c.erase(p, q);

          typename Sequence::reference r = c.front();

          ignore_unused_variable_warning(c);
          ignore_unused_variable_warning(c2);
          ignore_unused_variable_warning(r);
          const_constraints(c);
      }
   private:
      void const_constraints(const S& c) {
          typename Sequence::const_reference r = c.front();
          ignore_unused_variable_warning(r);
      }

      typename S::value_type t;
      typename S::size_type n;
      typename S::value_type* first, *last;
      typename S::iterator p, q;
  };

  BOOST_concept(FrontInsertionSequence,(S))
    : Sequence<S>
  {
      BOOST_CONCEPT_USAGE(FrontInsertionSequence)
      {
          c.push_front(t);
          c.pop_front();
      }
   private:
      S c;
      typename S::value_type t;
  };

  BOOST_concept(BackInsertionSequence,(S))
    : Sequence<S>
  {
      BOOST_CONCEPT_USAGE(BackInsertionSequence)
      {
          c.push_back(t);
          c.pop_back();
          typename BackInsertionSequence::reference r = c.back();
          ignore_unused_variable_warning(r);
          const_constraints(c);
      }
   private:
      void const_constraints(const S& cc) {
          typename BackInsertionSequence::const_reference
              r = cc.back();
          ignore_unused_variable_warning(r);
      }
      S c;
      typename S::value_type t;
  };

  BOOST_concept(AssociativeContainer,(C))
    : ForwardContainer<C>
    , DefaultConstructible<C>
  {
      typedef typename C::key_type key_type;
      typedef typename C::key_compare key_compare;
      typedef typename C::value_compare value_compare;
      typedef typename C::iterator iterator;

      BOOST_CONCEPT_USAGE(AssociativeContainer)
      {
          i = c.find(k);
          r = c.equal_range(k);
          c.erase(k);
          c.erase(i);
          c.erase(r.first, r.second);
          const_constraints(c);
          BOOST_CONCEPT_ASSERT((BinaryPredicate<key_compare,key_type,key_type>));

          typedef typename AssociativeContainer::value_type value_type_;
          BOOST_CONCEPT_ASSERT((BinaryPredicate<value_compare,value_type_,value_type_>));
      }

      // Redundant with the base concept, but it helps below.
      typedef typename C::const_iterator const_iterator;
   private:
      void const_constraints(const C& cc)
      {
          ci = cc.find(k);
          n = cc.count(k);
          cr = cc.equal_range(k);
      }

      C c;
      iterator i;
      std::pair<iterator,iterator> r;
      const_iterator ci;
      std::pair<const_iterator,const_iterator> cr;
      typename C::key_type k;
      typename C::size_type n;
  };

  BOOST_concept(UniqueAssociativeContainer,(C))
    : AssociativeContainer<C>
  {
      BOOST_CONCEPT_USAGE(UniqueAssociativeContainer)
      {
          C c(first, last);

          pos_flag = c.insert(t);
          c.insert(first, last);

          ignore_unused_variable_warning(c);
      }
   private:
      std::pair<typename C::iterator, bool> pos_flag;
      typename C::value_type t;
      typename C::value_type* first, *last;
  };

  BOOST_concept(MultipleAssociativeContainer,(C))
    : AssociativeContainer<C>
  {
      BOOST_CONCEPT_USAGE(MultipleAssociativeContainer)
      {
          C c(first, last);

          pos = c.insert(t);
          c.insert(first, last);

          ignore_unused_variable_warning(c);
          ignore_unused_variable_warning(pos);
      }
   private:
      typename C::iterator pos;
      typename C::value_type t;
      typename C::value_type* first, *last;
  };

  BOOST_concept(SimpleAssociativeContainer,(C))
    : AssociativeContainer<C>
  {
      BOOST_CONCEPT_USAGE(SimpleAssociativeContainer)
      {
          typedef typename C::key_type key_type;
          typedef typename C::value_type value_type;
          BOOST_STATIC_ASSERT((boost::is_same<key_type,value_type>::value));
      }
  };

  BOOST_concept(PairAssociativeContainer,(C))
    : AssociativeContainer<C>
  {
      BOOST_CONCEPT_USAGE(PairAssociativeContainer)
      {
          typedef typename C::key_type key_type;
          typedef typename C::value_type value_type;
          typedef typename C::mapped_type mapped_type;
          typedef std::pair<const key_type, mapped_type> required_value_type;
          BOOST_STATIC_ASSERT((boost::is_same<value_type,required_value_type>::value));
      }
  };

  BOOST_concept(SortedAssociativeContainer,(C))
    : AssociativeContainer<C>
    , ReversibleContainer<C>
  {
      BOOST_CONCEPT_USAGE(SortedAssociativeContainer)
      {
          C
              c(kc),
              c2(first, last),
              c3(first, last, kc);

          p = c.upper_bound(k);
          p = c.lower_bound(k);
          r = c.equal_range(k);

          c.insert(p, t);

          ignore_unused_variable_warning(c);
          ignore_unused_variable_warning(c2);
          ignore_unused_variable_warning(c3);
          const_constraints(c);
      }

      void const_constraints(const C& c)
      {
          kc = c.key_comp();
          vc = c.value_comp();

          cp = c.upper_bound(k);
          cp = c.lower_bound(k);
          cr = c.equal_range(k);
      }

   private:
      typename C::key_compare kc;
      typename C::value_compare vc;
      typename C::value_type t;
      typename C::key_type k;
      typedef typename C::iterator iterator;
      typedef typename C::const_iterator const_iterator;

      typedef SortedAssociativeContainer self;
      iterator p;
      const_iterator cp;
      std::pair<typename self::iterator,typename self::iterator> r;
      std::pair<typename self::const_iterator,typename self::const_iterator> cr;
      typename C::value_type* first, *last;
  };

  // HashedAssociativeContainer

  BOOST_concept(Collection,(C))
  {
      BOOST_CONCEPT_USAGE(Collection)
      {
        boost::function_requires<boost::InputIteratorConcept<iterator> >();
        boost::function_requires<boost::InputIteratorConcept<const_iterator> >();
        boost::function_requires<boost::CopyConstructibleConcept<value_type> >();
        const_constraints(c);
        i = c.begin();
        i = c.end();
        c.swap(c);
      }

      void const_constraints(const C& cc) {
        ci = cc.begin();
        ci = cc.end();
        n = cc.size();
        b = cc.empty();
      }

    private:
      typedef typename C::value_type value_type;
      typedef typename C::iterator iterator;
      typedef typename C::const_iterator const_iterator;
      typedef typename C::reference reference;
      typedef typename C::const_reference const_reference;
      // typedef typename C::pointer pointer;
      typedef typename C::difference_type difference_type;
      typedef typename C::size_type size_type;

      C c;
      bool b;
      iterator i;
      const_iterator ci;
      size_type n;
  };
} // namespace boost

#if (defined _MSC_VER)
# pragma warning( pop )
#endif

# include <boost/concept/detail/concept_undef.hpp>

#endif // BOOST_CONCEPT_CHECKS_HPP


/* concept_check.hpp
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
*/