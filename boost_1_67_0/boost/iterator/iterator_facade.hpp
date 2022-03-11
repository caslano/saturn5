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
wJfRS9HbtAjA3B8XbSDYHAlQCIL9AApKH+kBuKIPp7jMpTrTV6bkfVmNHH0oAC9cOvc9vpSCp0aAmIG5wjvgPWuz8Tp8m/6h/49fkI3ZS5mh57CWA5Xgh3eCz0cBGsJ8u3W6ZwAfRchHFwUysP3WHYczSbh34IOjDGhfGR3EnsV700k/VgUfLzKdgQtxffkLYUbqOHa4AfANKAy3AzcOxocoXfD28thkbDYA9rkEyvMO4NkxJVeI8SOj17E62PP2A9zrvAEJAfjcFKJY5p4SQ3xEHodE5KHwD7HwixCu6ri5vYQXQx/dXO8qufgHEMgFNggg8ROeMZ+FIm0jpn2LSw/iACdQVl/APWw27jcKKRQANSFmRXWZ0B2nMQbIfeBod/Wb/kXdSPHBB3a60Mos6NAwGZIYrZeNYFJH6vvg8PURXxKXoyjBetwxH5KnV0lazv4aIyrcr613HZK9CVejJQBCaXRMIih8EO0o7Fre9r/n1Xdibio1qcOJkwwYlURmL+QPXP+0zAkMHDUELtkQQ5NT1ebSIBBEAM1Hg528/fGBtg37KqGoHqr3ZoKXfUPb7Pq3LY/OnXGABYAsfvARuCAyJhAgVVYs04C3ACoXtNWlzD8vPZAM3xkQG3AVtEFHhBqauSHm8QENpwIQgIEgjwrmgMf634zAfaRtg+Bi4CGOiIhjAAgd2AMNjhCIwO9JDZ5/GADQGA+/aMyhPld1Qj2Ejb9/fJrPG9ln+QA9L17OgXxIpx8ciGugvGoaCr6YX8ttrszOgT6O4Yvpr/n04EVoiJ/5Boqjy4QKAMUBJxhNIn1fxnj8hwAc/s4FUs0ag5sPsGWz0gPfD/8QSCAAwgO4b22TrC6GXmxvgsqkf/pb/qG32AHbGuzgHpjc4r7JEPtKVRW2bMkoDQPfudo8DzvWBmBdUbcjAtLwZrr0GrekBYzIlfKo4lihgLApOqe+Wh5TeuIyzdwVNyh5uQRAiy5em6TecewXmFKTBpwRvMm6+1uhbO+jsWJ6lhIrAOsKnE0B7mOaVJqtgIHQ6CqkLDDevDUk+5awRC3CQ4YjohCdsDSXtWBDbk5lGMt6Aej1RwF2CT4YM5WqgiPdsfvJqBkeROy5/5DNTQv0+x03kJykCq4XGGorf8fO3BpFmwA/+8DilAPpQMffjzUN/+2fSmGJxDkN64jFz+E8qmyUO4DC0QZ+Xn16wAkZDGk0Be5vB7g1K+w3IMAgU+h38wBOUTQCeACM5gffUFnuEfBHORLo0JmLEXIby6oynMVKPxJpqg/cpergxr4Nqm6pU9k6qK7SFaLqBSJ6i39VeIv4EBIbDnS3xyMIN+5gn69tprpif2eSCFdfKRjLDdwaGuHw/TMR1HBfv8L7jND2hDHXyzMMKMwEBR4NOqcioqxSTxoLqRr6cwek0fVPDpKgjASkczzvxmgUs+yZAjLx0/YKfY2He+kpdC2jurHpxqGyNiw/YCqN/0cX6H+BS/38ZxEh+A/Ea9cR06251e+c2t+MBVhBdIDoZkIamJdl+4wO3UDEWgZzwGtulqZ3cuu8kOFEclDfdSKVl+Y73MoeFz1lVz/eE3sLudv0jS1ZtTF6B5iVL60ZcDtIGvz2f+r8ps7eicjnm85R4RdC5X37uK80xMlIz5lwkGap+bnfClpSITmpqCDNAIHruD+IT8H1VBDAddo5g+G18oeNlUN2DRihaJbxua0hOH2Oo1MI8LNXhA67oReJdZqlPAZvJNGXPz8RNHd7eV94zP/+DuC0tZ/K/fl//AHR7c/f/555u/4CDGxhCC2TCJqQHO83mdk+CAMMK0gU632NbRnrMjh/OU72A4OSn0ZkSGpmFoeFwpoTg7O1g6iGi/w7YgAxQUR300UfdYxorrRynhj/9PhNuTFee0wPBhgd8D2odRXyzQx+wA8KDfSNEw80xfh+jDEUx3Ao8UBuZPhVeE2/kiv0TMZ0j8lXIjv0lfZRfFPOmErWOFjGgXjNbndJfdzVCtBi8U2KnUNJD+aPi/rwD8P5hj9iiVG3N4C45t20XpcGgrgRcLk7QJbJPZ3WRm0f5sgWxxn84NTdXNGEsxupGG/dpiHnHILFOzmjEkxBrrJXe7U/6++AGgV/f4BT7s/s36Z43k9A/+WP2gHYG//jf//99wFzfzF/8cPbrP4lEvcv4gytFpdvI9QbU95hFEaE78Wy4p2iztY5KAz1jXFJSHwxCvyON+xiyaJppPz8ShnxL6uUJDiMjhb7URl0/FrOminJ7cN2j1Na7WpEMv4HhjIZTGJe7L0+V24SQ/3/BdXbtEn3aBQIZGXSUt6ePlPDQob7ffeOhk9qO5ZFw5M9zv8Vrdif/apyh50PviKeRFy/8MiBO7vt1OQqNkcv2wMXki0r5IVmw4lkTFA6NVWVxaoZX3f18FAXJUrKYXzqcYxGDMpcy94LqyRtPdeIoOAM3R9PKxHMFsvRy3KTsDeTisi90S6dUrb8sS282Bg8211aHEoSHTIoFr7Tnq0Pa6RLIQyas5xCpAQUpl4ltXVwJfGHRtgiLjEnqdCK7DCHDUtdMpJ4d/YzNpd7wicfuqJBBnbegzaY2kwAr/E/0pmuNbJhO348UYW0GaFfWMLdnkH+TS4pmOY/B5USXj6/828Jk2bCc+jZj+dlI/62XhXjOFUnIHz+lTOs3XAJmRe8CcGLKIYrQ3yGQzMjzkrLLeSS1dLD7f3g+umWTeVr6T55dBvQ/GnX4Meqay577E1Dyb+cE1QmIhxnTFrx+ujdNBScTqX5FJBHurW7HWj76wLuvfAyoygIVHf6212IFL+7V0O5rt7DFJ/qxL8i3qRgNmbyWm/c2Eg7NfOGb4KR4sSf1qH7wWWqrWiE+Lah8P+R3pwUvfASlecjH6Mtn1QvY4+28a/7IDQcpUn6HL638QYTfot0mmZeFpuTXRr+gIgrvGKs6vJK2cZrD0k4o535T3aei6TWI3taE1y1V/JUm/iOvQnW63J5LzWYHyxKVdI29NA9xkoP9xJYbKjS3fRp6bpWcI3oPxZVYqUfyGqLFDhkPY2PJPC54ya9zfVvkSDOavh27a9bSsjZ80vM3bsX8K1RzkwnEuzjfI3dypYoPUT7jhM00b1lduMyoVublSs1c3j4gF+ezRkcm/3EjwF0W3cDycr87hK69qyKvXZxPVHZIq1h+IT7A8aiENxMkAhV/shyBPVX/palAVkMl8XanhErvFXD+AjHR8Sunvq22PWkvuysabZJZ1a1EGMTnEhNm7m+sgDYL8ydagPbvPzffQzJjU5RFnIhprJ7EOFzI6oX7NOcJykiXzGU7E7z4ia8/wGEZguVWZ5RME8E+X645ya9Fj6+8ropZDjWrV7gYY29ohomuZdVCLupQPENV8d0M+1UlOYFBWAycfGe3rq19nJz7Gf+sBwe8a7yZMb6l8YW55E6hvTU9hBpRZxhNCrwSofoXg+Qge6WbKBpo203LMy0CBP+ETOPKAZN1AOPbNSeCnEaTfGFeljjGHymtDqPifIWbfFY3zmjM5RWWrmz7kxad7/puOe/uWfrbW2g2rKN0WZqqgbmr6GHRyUWlJhJ+ysafFOM18Qda3L+BDb+uEWi/xgYL6TUDjLW4qRup+XfIsQmKNT3nXRX3fxfz7CMZvyW8SorQ+k9cRiUXfR1VBySp+33Js+/mCZSTJOUuhO3/X0oC9sCZ9RTQqqvPCKvlZCUZz3ZA3Sg+7eyXM8egepDoFSlj6ELFDb2q8NDI8tfQ76XvE8Qc5rDo2NQnmbVpfS4pnveu+p0qsmtb5G2AAAglcyh7/mt2GlJ2DYdAftkG3snPf+oHLje61h/YmnZYlgRvWjzETCVvPULH5N73+Gm8Mmo116R4NORHmIyebw9h8WBgQnntfVIm95BcU1yBzbUnkpXeIF3dwyAd/+L8m3GcUel5voTzp0SSHsgSwxxoCufXcIaFj+ywfiVUdlOuV5SCyDz22e3RW57dlJ0cn6FxXl1/bpNVvD5e+wKsRYiDM3r+D07C/kOXc2uM4TwBNkZa9PdYWuT6bxr0wR+9mezbfYDVzx0w2nu+TyqdoesTu9WXokkWeP5px1icb2LTPd3mwYddDc0JWdhHTZhGovJwgXNyDUbQSX4cF++tr8PNOD7Ja3wXxv00e7cfH/vKKp6GOUveQDHAR/f8S82SIGO2Nc6uxjfi0Veo4k0/6naPCgpikdWd35jOrf5noS5OrZmUo3EJBHmqRzN/sS/9lpqpHZWxvLsNuzSzaT7dGDyvDfeV1j7QZ51KbEv5y/pvWBQM4d2NXn+rb4VUv55dx28vXfk+y1ZsQUcLPNQG2v9HktGBp/9t8bpg4l1KLyaYL+TBahVg05XVYI+UVXXAF4b8VNzzTOevO/DSeq9VoCeDmh+43djYrCLUQ9eB11JrX64G3n4J3O/0vBsa8L9tS5nLOpeS+auA6c/D3hLvDzu4tzit5hyLN1vLxgD/vfai37VLe3eafDIWPjjMWxjWv/8QSQBT/XxxbHGnApIs2wK3Z9WqZTsKM2C3Y5BuPfEg1xNRNJbXJyfh6NwdU0QTYMXdFhovIn6uasrezAanj/H3k/VsaLk+bAXnyOl/hhnDvR02TwGroGAt80B2noNiX977w2rNWL3hboqSTlWA7WbdnAWqUCZdjVo/TdGvGDsanDnppFOtTJbXlEx/unNNq6Hbg03eJQLEj95aXd3qGddl16pfLGIlzMw+449wwDwTgJ2gSXeDa9negc9D4XxUd4Pf6C9POeyoV4u7/gWCvaahZsTZRxEJALrFdDjqr3NLfkfGaeabcjGusbXLzrN3uDwusVc3bFJv4Tgd09Jk4+TydMLOcio7Tqlqe5WVFexQtvb7IoewQOb2A12eN3xtJuNFx9yG+3AALACAHTMwCqcHbf2xjU9G0RPZ07X/xe1vGfbBYTZEF10McBW1MDJWjCs8e5lGMVfW1Y+7d/+9hSD3SnVxffmWb9tcQqzQqhwTLTz6cnhNcj8yVJiYsZ82FbGpvBDUum9e/g9aei4Dr6FPWnY3oYx0JCG1i1Ju8++rt/CB/NFHsm0mWLK8b9pVj9wnYweAG9dXAcA6bP9yV5e7Y4Pqf/FFdMNaoK7kjnkeeJr81C2bnPGzjuaJY4SriCc8/PALIsve5D758VTYOwbgi07UXFSnrhqdPQP8oejmhsI8wJsVtOarO7n9dfJqNfJJVL68DbIPbgtRur6FZhHi1CjP65h7Ya12Z6t5VLx5O8hKvc01LICyOpDKTk4XaKSCCEGp1FGpTkoQySTSzE6uHzxJzY9ppBOJQU6H+3Iutuz2e6WjrY3idPSjF/JN/uXKg4E2Ze0YgBjhb92r9AKu/U3+833y+27ThyVpRdacb+ow/Xq7tVrM5oublvLAtzWO37VVQgPac/nSrJCdJ7y0Q4Sr9Xf6FhJ6qsbuiLrKPVpKeD8lOsLKWdepXPaKmdmnhIAACz/0/PetbdfnUJRreIetwA18j8ZwsBa0vE+1GcxosYtntmJ+ptF1cz+J77v82n6e1AK270ed9hKSJc9ewoi+GXWR6TG7tecNnGMvdbrYHPmH/8i9frlv5Lh4Zpe4bg5VfbEPykwZzZV3qa6bbX7C+Rf2NrX+1fZZwHlPBt//8oXaEz4UrYyjzjrdnHvDGmX9HskJf9ve7+OizbpvPrc4O8Z7P/mQdITN/f8u/W6SkLUu+NKvgrsZgVa7bt8FmxfwOrCv7ObaGzIb+3xb/VwMatbpOsbwJlnRmV9Z3hzAd7LP5p5LZhrrVfm2pVrshxWvZZXA5F11RcJE4dbj1KaJ9PGSzxjLa/kedyD9OOFqfX49bl4TeEPyuEj4kEaaW1Nh0VsZ31g5joGGkqGvL+8wDkd3KsHRiC1HTf/jupspXxsBgDAUsiBsrlsRjAM7J1ko/+tYfuITqS1G4RH7ri2uS84e3/zItvDkWGd/t2P8ODu/A29ntdbwt5rUG/MD2BbmPeLOM+qwdx0zRva8N8HB/p0Xbb9IHd5C5CA9tIBVtz55RUSdBYlE45hJg92+PpxF2hvMn3SJ/BwVg2VCIm9nvqvaDUe72M/nPDQ+NK83LoQ3Kxolxb8ezuQL1y25+BCB6hPcQkD8t46I+syr+Nz7sevpb2xx7eZoUsd0G9iIL63UsI9GT/oyHbjAND4LdH9bpSLLAVvun5mm75RHhtZDm14tgmnRstJi5qG4zHOY/z477wXk6qbDqT+v6STvjxKyW/2jh1aPe/luFWJhxxsfM5exqTIOX8bB3yTrkcvJM7vve3Xx9eaWNt9slRC2efV980tKCSSxIZ0p8+TaEJNBtdknck+dlu7vrLcBYNvbIXksryk2iTwj+LF1N1hhreBo8D+l4Ctuhty4x//Pq2smGHhrkI1EhNR1xfpvFZmkY2Rlls/P3MrSV9ly+7+KsKrcaLVrYJVijv0FSNbwCREV9DqSI7FzvXJRssXeArj5L/kCcqo/q9D313P6LBkLdqFySqr6rWCjJEmHiIjfjkCITDrRAEMvcESqkUHkdWCP7ZWMhfoZgZq/FnDiRzs+x8dr0peL1KvHiZHZ6/8HvkPQ7fSAgX9BHCw5h9kfyK5rX9FBsUBhUXLxw/NCIiISEzMxIwNDD9JKNqAOkAb8eFWAo0fQ5hb28caxiVuxEk2Q9HxSjARb3zebOCVQLPGnt4fQ1ZPNc+Aa8X3EQwTnhXCmyYmwgPKcAehgTuoMns/JbiEUoCXsqfcR5dZcZzgSmhzxYhRTY9Q8jkDDsdBFfFGi0TyEN8BS+q2dpi6zefP2nN4ylyNx8/wnva3N/wrNv5qbZmRZQ9L395xxr16qMIIR2PqqM2FdAkQxCww4QhF9JjLYeSFfCRlGaYwolR+CdMMNGZboLgxrs026PNHxf6k77NlXzQKVbMzxu8QMWWv0hR+0Td3DzcurApNi9wL6gaS/YTaSF0RVNiMQtRtZAasRI0kKnftxtJriQ2DIsbofHACp1qCkGlJ6X65AKUdsZLaRWVK+ZydcVSmqIVHdLwCFxVRktBa9x1QZL0Vd7rExBQvbDIOc9BOcOmMsf8ACzxdD3MP4g6A0P2DE4cBIcypFM7B3DgQTiie64rWIiJzngQuGVmnicO4/HjMsP6BamjlEkwiCRSsuVXDtqQDlRTbtosi3N5Vo39yTVCgDTJpjPL0stEnv1SSNozAmd3ToywKJ2/2HeFI01HsA2katEdujMsc3Fy02NoWBcy2HUELEZLamzK+WJ1y9HJSAc5KxUcHHTr7Lhb9+WiNJKRARyLPFwRmwM1nr9qei8RHgeaGRZLaS8t7EjpgbjhiSkvLa9bqCgIId5WYlEExmzyaFPqpKMR9YkTGUFAA8+KReMghRmEGpuU9gV8MHqw5i3EaWW2QegoFee9kmCJEgmEwot5QfRMcn1QcDkISCoPAs/yuZHileETcGkJRVeYSDQ6tCQqD0kcFqY5+Yg9Doe+AsaXBJHxSOenGJZlkjEC452pp3UW+UBb3RLKk9UxPjJ6jeuZkoIWQSQOysYGa/knqbxaHrmmIOg43+84X8BhZzuYb61o/pZi09C44gx288CbIdMcBByBN/wsqMLwviMFL4xSs6q2Fv3eilQLFlDRKk44097DqEmoLlmIGWGLZfhb350Kp/s38BhlLMBK3LEdMkYfVtpLqwECOjmCzKWYxOXiyZTt2AATm2OnPMWOYWJdWw4KVN82uDS962F9rO3QG+eEHj+Ts6xcKmglve6ACrEJgBMInMQ7009Hrh9slUA0rpf1vu1je2L4uCL6M9DYpIbjpPgsvp62X/w4GEFmOhvRh5k9F8b+WQxtYS93y+uuqPfNzZ4TDwbSkWqJ5GmEXEYusr/i5BxZjSNuRrve3eLPu0sklMszlvxjpkacq98awiH/ggBILE6TpwhCO1V9nJkL/cMUWublGcdess3IuDx22PSiVPChi3mscWdOQtnwXgZ9E3w8vm6Yg4m5C/klGxJiFYVKYAwllcAmqxTZfyKrV0sFI3Gy1kmYRbWHFWpqcSGGAYcp/gOOGzWueTdo/IRpgrd6/RLtsZv9YpxsjAYGoakSf+nuoXtMMf7mszewKQRRw67L3jZkg2MNQMpzZ68fK+sLUEAvq9PSIvs30Z625c2S4BALfSuhj2nrmtHRsSqYhAnromXiaomHon51ehGEq/k0armMwb2QP8HA4DVc3twcG43EC54QXM9Ky6EvU2yQjfeQrQRGY3jewSXMGLBBELeLxYxAFhhmFDCkYUgayVC7uYTlxgYRFZi14kMBvrbJLCFIjMHxoIDrHlQbkGKjo3CvMmnfBtWAWb2tarZNAqhttpqZXPs/xrJJW4wFk/6zhRC4xJzzoXzMNw+RWg0kBa+bzY8I3RcyuMwpZfPtQaLk7LgSCeb2KJhAmJj+nnzMMRwgPTF5qGN++ayLGkEC3YEXkjeZcK38T8WmzrAnitW/Wlu0kWCnGhvLWIgITw62RDPQliCDyxMgry/qYmUAUyiZkPjPq08OHe1QAKGpNKLyTmfPmu8XBDw2aJQ+bfcjMFBqlu5XHhtiTuRC4oxnCihRS0SZ38UrA5+jfuIrK3YZ5AU4RP8IHjWubQWHA2a0XlFB7fxvWrGPYojwJsrRHXhK6AqiN2LqgFiJgl5JeUXl9rUlIaLXQxC8m2tUXm4v1hbcPPArqGXEfwEe+ZIT9G55hMiTr212CAXblPmO481z7wD9t4wO0UrvCUt9I2e/nlxNKAjTiK4pJmDC+vg1I4RKAlUe8k6v5ckSI6Nk5WP0EdwB5OzvzF34+ycqoIpxP8BDrpbiRvKjD0qAn8+30c5L1aSNLNNJWEE7FJaxo3XkDh84DmZhCQqOASIiC5GL4B1bfOUbBz0VHIkSrRIebBV5hqc1BgkclflKyzWdpQYDrGKBeEiM2FG9jEVktjonct8Sw7ePs5hczcawY05cRB/fmzMFyfDR32UZbESWnWYPlUU5x8pegWjojxByYkq1mE7WNqtbq9bD/MygLlWNJ0VBzEDXF31t+m61k4UpG0tGEDyfm2Hq9nznPrrb6og6xtfdCf8Yv6K6JPAVyn7vtzYsm6Ukzs+gPv8Aw2ZEZ6pYn0Py401GG5pmFblOPJghTgltlgzTCcs2TMhbCOkrQtiZy4yHNxjtxoirFo7QEqisT+PlycYE=
*/