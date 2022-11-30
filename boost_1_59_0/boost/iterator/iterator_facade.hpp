// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_ITERATOR_FACADE_23022003THW_HPP
#define BOOST_ITERATOR_FACADE_23022003THW_HPP

#include <boost/config.hpp>
#include <boost/iterator/interoperable.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/iterator/detail/facade_iterator_category.hpp>
#include <boost/iterator/detail/enable_if.hpp>

#include <boost/static_assert.hpp>
#include <boost/core/addressof.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_pod.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>

#include <cstddef>

#include <boost/iterator/detail/config_def.hpp> // this goes last

namespace boost {
namespace iterators {

  // This forward declaration is required for the friend declaration
  // in iterator_core_access
  template <class I, class V, class TC, class R, class D> class iterator_facade;

  namespace detail
  {
    // A binary metafunction class that always returns bool.  VC6
    // ICEs on mpl::always<bool>, probably because of the default
    // parameters.
    struct always_bool2
    {
        template <class T, class U>
        struct apply
        {
            typedef bool type;
        };
    };

    // The type trait checks if the category or traversal is at least as advanced as the specified required traversal
    template< typename CategoryOrTraversal, typename Required >
    struct is_traversal_at_least :
        public boost::is_convertible< typename iterator_category_to_traversal< CategoryOrTraversal >::type, Required >
    {};

    //
    // enable if for use in operator implementation.
    //
    template <
        class Facade1
      , class Facade2
      , class Return
    >
    struct enable_if_interoperable :
        public boost::iterators::enable_if<
            is_interoperable< Facade1, Facade2 >
          , Return
        >
    {};

    //
    // enable if for use in implementation of operators specific for random access traversal.
    //
    template <
        class Facade1
      , class Facade2
      , class Return
    >
    struct enable_if_interoperable_and_random_access_traversal :
        public boost::iterators::enable_if<
            mpl::and_<
                is_interoperable< Facade1, Facade2 >
              , is_traversal_at_least< typename iterator_category< Facade1 >::type, random_access_traversal_tag >
              , is_traversal_at_least< typename iterator_category< Facade2 >::type, random_access_traversal_tag >
            >
          , Return
        >
    {};

    //
    // Generates associated types for an iterator_facade with the
    // given parameters.
    //
    template <
        class ValueParam
      , class CategoryOrTraversal
      , class Reference
      , class Difference
    >
    struct iterator_facade_types
    {
        typedef typename facade_iterator_category<
            CategoryOrTraversal, ValueParam, Reference
        >::type iterator_category;

        typedef typename remove_const<ValueParam>::type value_type;

        // Not the real associated pointer type
        typedef typename mpl::eval_if<
            boost::iterators::detail::iterator_writability_disabled<ValueParam,Reference>
          , add_pointer<const value_type>
          , add_pointer<value_type>
        >::type pointer;

# if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)                          \
    && (BOOST_WORKAROUND(_STLPORT_VERSION, BOOST_TESTED_AT(0x452))              \
        || BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, BOOST_TESTED_AT(310)))     \
    || BOOST_WORKAROUND(BOOST_RWSTD_VER, BOOST_TESTED_AT(0x20101))              \
    || BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, <= 310)

        // To interoperate with some broken library/compiler
        // combinations, user-defined iterators must be derived from
        // std::iterator.  It is possible to implement a standard
        // library for broken compilers without this limitation.
#  define BOOST_ITERATOR_FACADE_NEEDS_ITERATOR_BASE 1

        typedef
           iterator<iterator_category, value_type, Difference, pointer, Reference>
        base;
# endif
    };

    // iterators whose dereference operators reference the same value
    // for all iterators into the same sequence (like many input
    // iterators) need help with their postfix ++: the referenced
    // value must be read and stored away before the increment occurs
    // so that *a++ yields the originally referenced element and not
    // the next one.
    template <class Iterator>
    class postfix_increment_proxy
    {
        typedef typename iterator_value<Iterator>::type value_type;
     public:
        explicit postfix_increment_proxy(Iterator const& x)
          : stored_value(*x)
        {}

        // Returning a mutable reference allows nonsense like
        // (*r++).mutate(), but it imposes fewer assumptions about the
        // behavior of the value_type.  In particular, recall that
        // (*r).mutate() is legal if operator* returns by value.
        value_type&
        operator*() const
        {
            return this->stored_value;
        }
     private:
        mutable value_type stored_value;
    };

    //
    // In general, we can't determine that such an iterator isn't
    // writable -- we also need to store a copy of the old iterator so
    // that it can be written into.
    template <class Iterator>
    class writable_postfix_increment_proxy
    {
        typedef typename iterator_value<Iterator>::type value_type;
     public:
        explicit writable_postfix_increment_proxy(Iterator const& x)
          : stored_value(*x)
          , stored_iterator(x)
        {}

        // Dereferencing must return a proxy so that both *r++ = o and
        // value_type(*r++) can work.  In this case, *r is the same as
        // *r++, and the conversion operator below is used to ensure
        // readability.
        writable_postfix_increment_proxy const&
        operator*() const
        {
            return *this;
        }

        // Provides readability of *r++
        operator value_type&() const
        {
            return stored_value;
        }

        // Provides writability of *r++
        template <class T>
        T const& operator=(T const& x) const
        {
            *this->stored_iterator = x;
            return x;
        }

        // This overload just in case only non-const objects are writable
        template <class T>
        T& operator=(T& x) const
        {
            *this->stored_iterator = x;
            return x;
        }

        // Provides X(r++)
        operator Iterator const&() const
        {
            return stored_iterator;
        }

     private:
        mutable value_type stored_value;
        Iterator stored_iterator;
    };

# ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <class Reference, class Value>
    struct is_non_proxy_reference_impl
    {
        static Reference r;

        template <class R>
        static typename mpl::if_<
            is_convertible<
                R const volatile*
              , Value const volatile*
            >
          , char[1]
          , char[2]
        >::type& helper(R const&);

        BOOST_STATIC_CONSTANT(bool, value = sizeof(helper(r)) == 1);
    };

    template <class Reference, class Value>
    struct is_non_proxy_reference
      : mpl::bool_<
            is_non_proxy_reference_impl<Reference, Value>::value
        >
    {};
# else
    template <class Reference, class Value>
    struct is_non_proxy_reference
      : is_convertible<
            typename remove_reference<Reference>::type
            const volatile*
          , Value const volatile*
        >
    {};
# endif

    // A metafunction to choose the result type of postfix ++
    //
    // Because the C++98 input iterator requirements say that *r++ has
    // type T (value_type), implementations of some standard
    // algorithms like lexicographical_compare may use constructions
    // like:
    //
    //          *r++ < *s++
    //
    // If *r++ returns a proxy (as required if r is writable but not
    // multipass), this sort of expression will fail unless the proxy
    // supports the operator<.  Since there are any number of such
    // operations, we're not going to try to support them.  Therefore,
    // even if r++ returns a proxy, *r++ will only return a proxy if
    // *r also returns a proxy.
    template <class Iterator, class Value, class Reference, class CategoryOrTraversal>
    struct postfix_increment_result
      : mpl::eval_if<
            mpl::and_<
                // A proxy is only needed for readable iterators
                is_convertible<
                    Reference
                    // Use add_lvalue_reference to form `reference to Value` due to
                    // some (strict) C++03 compilers (e.g. `gcc -std=c++03`) reject
                    // 'reference-to-reference' in the template which described in CWG
                    // DR106.
                    // http://www.open-std.org/Jtc1/sc22/wg21/docs/cwg_defects.html#106
                  , typename add_lvalue_reference<Value const>::type
                >

                // No multipass iterator can have values that disappear
                // before positions can be re-visited
              , mpl::not_<
                    is_convertible<
                        typename iterator_category_to_traversal<CategoryOrTraversal>::type
                      , forward_traversal_tag
                    >
                >
            >
          , mpl::if_<
                is_non_proxy_reference<Reference,Value>
              , postfix_increment_proxy<Iterator>
              , writable_postfix_increment_proxy<Iterator>
            >
          , mpl::identity<Iterator>
        >
    {};

    // operator->() needs special support for input iterators to strictly meet the
    // standard's requirements. If *i is not a reference type, we must still
    // produce an lvalue to which a pointer can be formed.  We do that by
    // returning a proxy object containing an instance of the reference object.
    template <class Reference, class Pointer>
    struct operator_arrow_dispatch // proxy references
    {
        struct proxy
        {
            explicit proxy(Reference const & x) : m_ref(x) {}
            Reference* operator->() { return boost::addressof(m_ref); }
            // This function is needed for MWCW and BCC, which won't call
            // operator-> again automatically per 13.3.1.2 para 8
            operator Reference*() { return boost::addressof(m_ref); }
            Reference m_ref;
        };
        typedef proxy result_type;
        static result_type apply(Reference const & x)
        {
            return result_type(x);
        }
    };

    template <class T, class Pointer>
    struct operator_arrow_dispatch<T&, Pointer> // "real" references
    {
        typedef Pointer result_type;
        static result_type apply(T& x)
        {
            return boost::addressof(x);
        }
    };

    // A proxy return type for operator[], needed to deal with
    // iterators that may invalidate referents upon destruction.
    // Consider the temporary iterator in *(a + n)
    template <class Iterator>
    class operator_brackets_proxy
    {
        // Iterator is actually an iterator_facade, so we do not have to
        // go through iterator_traits to access the traits.
        typedef typename Iterator::reference  reference;
        typedef typename Iterator::value_type value_type;

     public:
        operator_brackets_proxy(Iterator const& iter)
          : m_iter(iter)
        {}

        operator reference() const
        {
            return *m_iter;
        }

        operator_brackets_proxy& operator=(value_type const& val)
        {
            *m_iter = val;
            return *this;
        }

     private:
        Iterator m_iter;
    };

    // A metafunction that determines whether operator[] must return a
    // proxy, or whether it can simply return a copy of the value_type.
    template <class ValueType, class Reference>
    struct use_operator_brackets_proxy
      : mpl::not_<
            mpl::and_<
                // Really we want an is_copy_constructible trait here,
                // but is_POD will have to suffice in the meantime.
                boost::is_POD<ValueType>
              , iterator_writability_disabled<ValueType,Reference>
            >
        >
    {};

    template <class Iterator, class Value, class Reference>
    struct operator_brackets_result
    {
        typedef typename mpl::if_<
            use_operator_brackets_proxy<Value,Reference>
          , operator_brackets_proxy<Iterator>
          , Value
        >::type type;
    };

    template <class Iterator>
    operator_brackets_proxy<Iterator> make_operator_brackets_result(Iterator const& iter, mpl::true_)
    {
        return operator_brackets_proxy<Iterator>(iter);
    }

    template <class Iterator>
    typename Iterator::value_type make_operator_brackets_result(Iterator const& iter, mpl::false_)
    {
      return *iter;
    }

    struct choose_difference_type
    {
        template <class I1, class I2>
        struct apply
          :
# ifdef BOOST_NO_ONE_WAY_ITERATOR_INTEROP
          iterator_difference<I1>
# else
          mpl::eval_if<
              is_convertible<I2,I1>
            , iterator_difference<I1>
            , iterator_difference<I2>
          >
# endif
        {};

    };

    template <
        class Derived
      , class Value
      , class CategoryOrTraversal
      , class Reference
      , class Difference
      , bool IsBidirectionalTraversal
      , bool IsRandomAccessTraversal
    >
    class iterator_facade_base;

  } // namespace detail


  // Macros which describe the declarations of binary operators
# ifdef BOOST_NO_STRICT_ITERATOR_INTEROPERABILITY
#  define BOOST_ITERATOR_FACADE_INTEROP_HEAD_IMPL(prefix, op, result_type, enabler)       \
    template <                                                              \
        class Derived1, class V1, class TC1, class Reference1, class Difference1 \
      , class Derived2, class V2, class TC2, class Reference2, class Difference2 \
    >                                                                       \
    prefix typename mpl::apply2<result_type,Derived1,Derived2>::type \
    operator op(                                                            \
        iterator_facade<Derived1, V1, TC1, Reference1, Difference1> const& lhs   \
      , iterator_facade<Derived2, V2, TC2, Reference2, Difference2> const& rhs)
# else
#  define BOOST_ITERATOR_FACADE_INTEROP_HEAD_IMPL(prefix, op, result_type, enabler)   \
    template <                                                          \
        class Derived1, class V1, class TC1, class Reference1, class Difference1 \
      , class Derived2, class V2, class TC2, class Reference2, class Difference2 \
    >                                                                   \
    prefix typename enabler<                                            \
        Derived1, Derived2                                              \
      , typename mpl::apply2<result_type,Derived1,Derived2>::type       \
    >::type                                                             \
    operator op(                                                        \
        iterator_facade<Derived1, V1, TC1, Reference1, Difference1> const& lhs   \
      , iterator_facade<Derived2, V2, TC2, Reference2, Difference2> const& rhs)
# endif

#  define BOOST_ITERATOR_FACADE_INTEROP_HEAD(prefix, op, result_type)       \
    BOOST_ITERATOR_FACADE_INTEROP_HEAD_IMPL(prefix, op, result_type, boost::iterators::detail::enable_if_interoperable)

#  define BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS_HEAD(prefix, op, result_type)       \
    BOOST_ITERATOR_FACADE_INTEROP_HEAD_IMPL(prefix, op, result_type, boost::iterators::detail::enable_if_interoperable_and_random_access_traversal)

#  define BOOST_ITERATOR_FACADE_PLUS_HEAD(prefix,args)              \
    template <class Derived, class V, class TC, class R, class D>   \
    prefix typename boost::iterators::enable_if<                    \
        boost::iterators::detail::is_traversal_at_least< TC, boost::iterators::random_access_traversal_tag >,  \
        Derived                                                     \
    >::type operator+ args

  //
  // Helper class for granting access to the iterator core interface.
  //
  // The simple core interface is used by iterator_facade. The core
  // interface of a user/library defined iterator type should not be made public
  // so that it does not clutter the public interface. Instead iterator_core_access
  // should be made friend so that iterator_facade can access the core
  // interface through iterator_core_access.
  //
  class iterator_core_access
  {
# if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
      // Tasteless as this may seem, making all members public allows member templates
      // to work in the absence of member template friends.
   public:
# else

      template <class I, class V, class TC, class R, class D> friend class iterator_facade;
      template <class I, class V, class TC, class R, class D, bool IsBidirectionalTraversal, bool IsRandomAccessTraversal>
      friend class detail::iterator_facade_base;

#  define BOOST_ITERATOR_FACADE_RELATION(op)                                \
      BOOST_ITERATOR_FACADE_INTEROP_HEAD(friend,op, boost::iterators::detail::always_bool2);

      BOOST_ITERATOR_FACADE_RELATION(==)
      BOOST_ITERATOR_FACADE_RELATION(!=)

#  undef BOOST_ITERATOR_FACADE_RELATION

#  define BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(op)                                \
      BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS_HEAD(friend,op, boost::iterators::detail::always_bool2);

      BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(<)
      BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(>)
      BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(<=)
      BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(>=)

#  undef BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION

      BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS_HEAD(
          friend, -, boost::iterators::detail::choose_difference_type)
      ;

      BOOST_ITERATOR_FACADE_PLUS_HEAD(
          friend inline
        , (iterator_facade<Derived, V, TC, R, D> const&
        , typename Derived::difference_type)
      )
      ;

      BOOST_ITERATOR_FACADE_PLUS_HEAD(
          friend inline
        , (typename Derived::difference_type
        , iterator_facade<Derived, V, TC, R, D> const&)
      )
      ;

# endif

      template <class Facade>
      static typename Facade::reference dereference(Facade const& f)
      {
          return f.dereference();
      }

      template <class Facade>
      static void increment(Facade& f)
      {
          f.increment();
      }

      template <class Facade>
      static void decrement(Facade& f)
      {
          f.decrement();
      }

      template <class Facade1, class Facade2>
      static bool equal(Facade1 const& f1, Facade2 const& f2, mpl::true_)
      {
          return f1.equal(f2);
      }

      template <class Facade1, class Facade2>
      static bool equal(Facade1 const& f1, Facade2 const& f2, mpl::false_)
      {
          return f2.equal(f1);
      }

      template <class Facade>
      static void advance(Facade& f, typename Facade::difference_type n)
      {
          f.advance(n);
      }

      template <class Facade1, class Facade2>
      static typename Facade1::difference_type distance_from(
          Facade1 const& f1, Facade2 const& f2, mpl::true_)
      {
          return -f1.distance_to(f2);
      }

      template <class Facade1, class Facade2>
      static typename Facade2::difference_type distance_from(
          Facade1 const& f1, Facade2 const& f2, mpl::false_)
      {
          return f2.distance_to(f1);
      }

      //
      // Curiously Recurring Template interface.
      //
      template <class I, class V, class TC, class R, class D>
      static I& derived(iterator_facade<I,V,TC,R,D>& facade)
      {
          return *static_cast<I*>(&facade);
      }

      template <class I, class V, class TC, class R, class D>
      static I const& derived(iterator_facade<I,V,TC,R,D> const& facade)
      {
          return *static_cast<I const*>(&facade);
      }

      // objects of this class are useless
      BOOST_DELETED_FUNCTION(iterator_core_access())
  };

  namespace detail {

    // Implementation for forward traversal iterators
    template <
        class Derived
      , class Value
      , class CategoryOrTraversal
      , class Reference
      , class Difference
    >
    class iterator_facade_base< Derived, Value, CategoryOrTraversal, Reference, Difference, false, false >
# ifdef BOOST_ITERATOR_FACADE_NEEDS_ITERATOR_BASE
        : public boost::iterators::detail::iterator_facade_types<
             Value, CategoryOrTraversal, Reference, Difference
          >::base
#  undef BOOST_ITERATOR_FACADE_NEEDS_ITERATOR_BASE
# endif
    {
    private:
        typedef boost::iterators::detail::iterator_facade_types<
            Value, CategoryOrTraversal, Reference, Difference
        > associated_types;

        typedef boost::iterators::detail::operator_arrow_dispatch<
            Reference
          , typename associated_types::pointer
        > operator_arrow_dispatch_;

    public:
        typedef typename associated_types::value_type value_type;
        typedef Reference reference;
        typedef Difference difference_type;

        typedef typename operator_arrow_dispatch_::result_type pointer;

        typedef typename associated_types::iterator_category iterator_category;

    public:
        reference operator*() const
        {
            return iterator_core_access::dereference(this->derived());
        }

        pointer operator->() const
        {
            return operator_arrow_dispatch_::apply(*this->derived());
        }

        Derived& operator++()
        {
            iterator_core_access::increment(this->derived());
            return this->derived();
        }

    protected:
        //
        // Curiously Recurring Template interface.
        //
        Derived& derived()
        {
            return *static_cast<Derived*>(this);
        }

        Derived const& derived() const
        {
            return *static_cast<Derived const*>(this);
        }
    };

    // Implementation for bidirectional traversal iterators
    template <
        class Derived
      , class Value
      , class CategoryOrTraversal
      , class Reference
      , class Difference
    >
    class iterator_facade_base< Derived, Value, CategoryOrTraversal, Reference, Difference, true, false > :
        public iterator_facade_base< Derived, Value, CategoryOrTraversal, Reference, Difference, false, false >
    {
    public:
        Derived& operator--()
        {
            iterator_core_access::decrement(this->derived());
            return this->derived();
        }

        Derived operator--(int)
        {
            Derived tmp(this->derived());
            --*this;
            return tmp;
        }
    };

    // Implementation for random access traversal iterators
    template <
        class Derived
      , class Value
      , class CategoryOrTraversal
      , class Reference
      , class Difference
    >
    class iterator_facade_base< Derived, Value, CategoryOrTraversal, Reference, Difference, true, true > :
        public iterator_facade_base< Derived, Value, CategoryOrTraversal, Reference, Difference, true, false >
    {
    private:
        typedef iterator_facade_base< Derived, Value, CategoryOrTraversal, Reference, Difference, true, false > base_type;

    public:
        typedef typename base_type::reference reference;
        typedef typename base_type::difference_type difference_type;

    public:
        typename boost::iterators::detail::operator_brackets_result<Derived, Value, reference>::type
        operator[](difference_type n) const
        {
            typedef boost::iterators::detail::use_operator_brackets_proxy<Value, Reference> use_proxy;

            return boost::iterators::detail::make_operator_brackets_result<Derived>(
                this->derived() + n
              , use_proxy()
            );
        }

        Derived& operator+=(difference_type n)
        {
            iterator_core_access::advance(this->derived(), n);
            return this->derived();
        }

        Derived& operator-=(difference_type n)
        {
            iterator_core_access::advance(this->derived(), -n);
            return this->derived();
        }

        Derived operator-(difference_type x) const
        {
            Derived result(this->derived());
            return result -= x;
        }
    };

  } // namespace detail

  //
  // iterator_facade - use as a public base class for defining new
  // standard-conforming iterators.
  //
  template <
      class Derived             // The derived iterator type being constructed
    , class Value
    , class CategoryOrTraversal
    , class Reference   = Value&
    , class Difference  = std::ptrdiff_t
  >
  class iterator_facade :
      public detail::iterator_facade_base<
          Derived,
          Value,
          CategoryOrTraversal,
          Reference,
          Difference,
          detail::is_traversal_at_least< CategoryOrTraversal, bidirectional_traversal_tag >::value,
          detail::is_traversal_at_least< CategoryOrTraversal, random_access_traversal_tag >::value
      >
  {
  protected:
      // For use by derived classes
      typedef iterator_facade<Derived,Value,CategoryOrTraversal,Reference,Difference> iterator_facade_;
  };

  template <class I, class V, class TC, class R, class D>
  inline typename boost::iterators::detail::postfix_increment_result<I,V,R,TC>::type
  operator++(
      iterator_facade<I,V,TC,R,D>& i
    , int
  )
  {
      typename boost::iterators::detail::postfix_increment_result<I,V,R,TC>::type
          tmp(*static_cast<I*>(&i));

      ++i;

      return tmp;
  }


  //
  // Comparison operator implementation. The library supplied operators
  // enables the user to provide fully interoperable constant/mutable
  // iterator types. I.e. the library provides all operators
  // for all mutable/constant iterator combinations.
  //
  // Note though that this kind of interoperability for constant/mutable
  // iterators is not required by the standard for container iterators.
  // All the standard asks for is a conversion mutable -> constant.
  // Most standard library implementations nowadays provide fully interoperable
  // iterator implementations, but there are still heavily used implementations
  // that do not provide them. (Actually it's even worse, they do not provide
  // them for only a few iterators.)
  //
  // ?? Maybe a BOOST_ITERATOR_NO_FULL_INTEROPERABILITY macro should
  //    enable the user to turn off mixed type operators
  //
  // The library takes care to provide only the right operator overloads.
  // I.e.
  //
  // bool operator==(Iterator,      Iterator);
  // bool operator==(ConstIterator, Iterator);
  // bool operator==(Iterator,      ConstIterator);
  // bool operator==(ConstIterator, ConstIterator);
  //
  //   ...
  //
  // In order to do so it uses c++ idioms that are not yet widely supported
  // by current compiler releases. The library is designed to degrade gracefully
  // in the face of compiler deficiencies. In general compiler
  // deficiencies result in less strict error checking and more obscure
  // error messages, functionality is not affected.
  //
  // For full operation compiler support for "Substitution Failure Is Not An Error"
  // (aka. enable_if) and boost::is_convertible is required.
  //
  // The following problems occur if support is lacking.
  //
  // Pseudo code
  //
  // ---------------
  // AdaptorA<Iterator1> a1;
  // AdaptorA<Iterator2> a2;
  //
  // // This will result in a no such overload error in full operation
  // // If enable_if or is_convertible is not supported
  // // The instantiation will fail with an error hopefully indicating that
  // // there is no operator== for Iterator1, Iterator2
  // // The same will happen if no enable_if is used to remove
  // // false overloads from the templated conversion constructor
  // // of AdaptorA.
  //
  // a1 == a2;
  // ----------------
  //
  // AdaptorA<Iterator> a;
  // AdaptorB<Iterator> b;
  //
  // // This will result in a no such overload error in full operation
  // // If enable_if is not supported the static assert used
  // // in the operator implementation will fail.
  // // This will accidently work if is_convertible is not supported.
  //
  // a == b;
  // ----------------
  //

# ifdef BOOST_NO_ONE_WAY_ITERATOR_INTEROP
#  define BOOST_ITERATOR_CONVERTIBLE(a,b) mpl::true_()
# else
#  define BOOST_ITERATOR_CONVERTIBLE(a,b) is_convertible<a,b>()
# endif

# define BOOST_ITERATOR_FACADE_INTEROP(op, result_type, return_prefix, base_op) \
  BOOST_ITERATOR_FACADE_INTEROP_HEAD(inline, op, result_type)                   \
  {                                                                             \
      /* For those compilers that do not support enable_if */                   \
      BOOST_STATIC_ASSERT((                                                     \
          is_interoperable< Derived1, Derived2 >::value                         \
      ));                                                                       \
      return_prefix iterator_core_access::base_op(                              \
          *static_cast<Derived1 const*>(&lhs)                                   \
        , *static_cast<Derived2 const*>(&rhs)                                   \
        , BOOST_ITERATOR_CONVERTIBLE(Derived2,Derived1)                         \
      );                                                                        \
  }

# define BOOST_ITERATOR_FACADE_RELATION(op, return_prefix, base_op) \
  BOOST_ITERATOR_FACADE_INTEROP(                                    \
      op                                                            \
    , boost::iterators::detail::always_bool2                                   \
    , return_prefix                                                 \
    , base_op                                                       \
  )

  BOOST_ITERATOR_FACADE_RELATION(==, return, equal)
  BOOST_ITERATOR_FACADE_RELATION(!=, return !, equal)

# undef BOOST_ITERATOR_FACADE_RELATION


# define BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS(op, result_type, return_prefix, base_op) \
  BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS_HEAD(inline, op, result_type)                   \
  {                                                                             \
      /* For those compilers that do not support enable_if */                   \
      BOOST_STATIC_ASSERT((                                                     \
          is_interoperable< Derived1, Derived2 >::value &&                      \
          boost::iterators::detail::is_traversal_at_least< typename iterator_category< Derived1 >::type, random_access_traversal_tag >::value && \
          boost::iterators::detail::is_traversal_at_least< typename iterator_category< Derived2 >::type, random_access_traversal_tag >::value \
      ));                                                                       \
      return_prefix iterator_core_access::base_op(                              \
          *static_cast<Derived1 const*>(&lhs)                                   \
        , *static_cast<Derived2 const*>(&rhs)                                   \
        , BOOST_ITERATOR_CONVERTIBLE(Derived2,Derived1)                         \
      );                                                                        \
  }

# define BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(op, return_prefix, base_op) \
  BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS(                                    \
      op                                                            \
    , boost::iterators::detail::always_bool2                                   \
    , return_prefix                                                 \
    , base_op                                                       \
  )

  BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(<, return 0 >, distance_from)
  BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(>, return 0 <, distance_from)
  BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(<=, return 0 >=, distance_from)
  BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION(>=, return 0 <=, distance_from)

# undef BOOST_ITERATOR_FACADE_RANDOM_ACCESS_RELATION

  // operator- requires an additional part in the static assertion
  BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS(
      -
    , boost::iterators::detail::choose_difference_type
    , return
    , distance_from
  )

# undef BOOST_ITERATOR_FACADE_INTEROP
# undef BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS

# define BOOST_ITERATOR_FACADE_PLUS(args)           \
  BOOST_ITERATOR_FACADE_PLUS_HEAD(inline, args)     \
  {                                                 \
      Derived tmp(static_cast<Derived const&>(i));  \
      return tmp += n;                              \
  }

  BOOST_ITERATOR_FACADE_PLUS((
      iterator_facade<Derived, V, TC, R, D> const& i
    , typename Derived::difference_type n
  ))

  BOOST_ITERATOR_FACADE_PLUS((
      typename Derived::difference_type n
    , iterator_facade<Derived, V, TC, R, D> const& i
  ))

# undef BOOST_ITERATOR_FACADE_PLUS
# undef BOOST_ITERATOR_FACADE_PLUS_HEAD

# undef BOOST_ITERATOR_FACADE_INTEROP_HEAD
# undef BOOST_ITERATOR_FACADE_INTEROP_RANDOM_ACCESS_HEAD
# undef BOOST_ITERATOR_FACADE_INTEROP_HEAD_IMPL

} // namespace iterators

using iterators::iterator_core_access;
using iterators::iterator_facade;

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_ITERATOR_FACADE_23022003THW_HPP

/* iterator_facade.hpp
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
*/