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
          f(first,second);
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