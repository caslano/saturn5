// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2014 - 2021 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
// Revisions:
// 27 Apr 2008 (improved swap) Fernando Cacciola, Niels Dekker, Thorsten Ottosen
// 05 May 2014 (Added move semantics) Andrzej Krzemienski
//
#ifndef BOOST_OPTIONAL_OPTIONAL_FLC_19NOV2002_HPP
#define BOOST_OPTIONAL_OPTIONAL_FLC_19NOV2002_HPP

#include <new>
#ifndef BOOST_NO_IOSTREAM
#include <iosfwd>
#endif // BOOST_NO_IOSTREAM

#ifdef BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#  include <type_traits>
#endif

#include <boost/assert.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/core/swap.hpp>
#include <boost/optional/bad_optional_access.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/conjunction.hpp>
#include <boost/type_traits/disjunction.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/type_with_alignment.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/is_assignable.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_constructible.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/is_nothrow_move_assignable.hpp>
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/move/utility.hpp>
#include <boost/none.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <boost/utility/result_of.hpp>

#include <boost/optional/optional_fwd.hpp>
#include <boost/optional/detail/optional_config.hpp>
#include <boost/optional/detail/optional_factory_support.hpp>
#include <boost/optional/detail/optional_aligned_storage.hpp>

namespace boost { namespace optional_detail {

template <typename T>
struct optional_value_type
{
};

template <typename T>
struct optional_value_type< ::boost::optional<T> >
{
  typedef T type;
};

}} // namespace boost::optional_detail

#ifdef BOOST_OPTIONAL_CONFIG_USE_OLD_IMPLEMENTATION_OF_OPTIONAL
#include <boost/optional/detail/old_optional_implementation.hpp>
#else
namespace boost {

namespace optional_ns {

// a tag for in-place initialization of contained value
struct in_place_init_t
{
  struct init_tag{};
  explicit in_place_init_t(init_tag){}
};
const in_place_init_t in_place_init ((in_place_init_t::init_tag()));

// a tag for conditional in-place initialization of contained value
struct in_place_init_if_t
{
  struct init_tag{};
  explicit in_place_init_if_t(init_tag){}
};
const in_place_init_if_t in_place_init_if ((in_place_init_if_t::init_tag()));

} // namespace optional_ns

using optional_ns::in_place_init_t;
using optional_ns::in_place_init;
using optional_ns::in_place_init_if_t;
using optional_ns::in_place_init_if;

namespace optional_detail {

struct init_value_tag {};

struct optional_tag {};


template<class T>
class optional_base : public optional_tag
{
  private :

    typedef aligned_storage<T> storage_type ;
    typedef optional_base<T> this_type ;

  protected :

    typedef T value_type ;
    typedef typename boost::remove_const<T>::type unqualified_value_type;

  protected:
    typedef T &       reference_type ;
    typedef T const&  reference_const_type ;
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    typedef T &&  rval_reference_type ;
    typedef T &&  reference_type_of_temporary_wrapper ;
#endif
    typedef T *         pointer_type ;
    typedef T const*    pointer_const_type ;
    typedef T const&    argument_type ;

    // Creates an optional<T> uninitialized.
    // No-throw
    optional_base()
      :
      m_initialized(false) {}

    // Creates an optional<T> uninitialized.
    // No-throw
    optional_base ( none_t )
      :
      m_initialized(false) {}

    // Creates an optional<T> initialized with 'val'.
    // Can throw if T::T(T const&) does
    optional_base ( init_value_tag, argument_type val )
      :
      m_initialized(false)
    {
        construct(val);
    }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // move-construct an optional<T> initialized from an rvalue-ref to 'val'.
    // Can throw if T::T(T&&) does
    optional_base ( init_value_tag, rval_reference_type val )
      :
      m_initialized(false)
    {
      construct( boost::move(val) );
    }
#endif

    // Creates an optional<T> initialized with 'val' IFF cond is true, otherwise creates an uninitialized optional<T>.
    // Can throw if T::T(T const&) does
    optional_base ( bool cond, argument_type val )
      :
      m_initialized(false)
    {
      if ( cond )
        construct(val);
    }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Creates an optional<T> initialized with 'move(val)' IFF cond is true, otherwise creates an uninitialized optional<T>.
    // Can throw if T::T(T &&) does
    optional_base ( bool cond, rval_reference_type val )
      :
      m_initialized(false)
    {
      if ( cond )
        construct(boost::move(val));
    }
#endif

    // Creates a deep copy of another optional<T>
    // Can throw if T::T(T const&) does
    optional_base ( optional_base const& rhs )
      :
      m_initialized(false)
    {
      if ( rhs.is_initialized() )
        construct(rhs.get_impl());
    }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Creates a deep move of another optional<T>
    // Can throw if T::T(T&&) does
    optional_base ( optional_base&& rhs )
    BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value)
      :
      m_initialized(false)
    {
      if ( rhs.is_initialized() )
        construct( boost::move(rhs.get_impl()) );
    }
#endif

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

    template<class Expr, class PtrExpr>
    explicit optional_base ( Expr&& expr, PtrExpr const* tag )
      :
      m_initialized(false)
    {
      construct(boost::forward<Expr>(expr),tag);
    }

#else
    // This is used for both converting and in-place constructions.
    // Derived classes use the 'tag' to select the appropriate
    // implementation (the correct 'construct()' overload)
    template<class Expr>
    explicit optional_base ( Expr const& expr, Expr const* tag )
      :
      m_initialized(false)
    {
      construct(expr,tag);
    }

#endif

    optional_base& operator= ( optional_base const& rhs )
    {
      this->assign(rhs);
      return *this;
    }

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    optional_base& operator= ( optional_base && rhs )
    BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value && ::boost::is_nothrow_move_assignable<T>::value)
    {
      this->assign(static_cast<optional_base&&>(rhs));
      return *this;
    }
#endif

    // No-throw (assuming T::~T() doesn't)
    ~optional_base() { destroy() ; }

    // Assigns from another optional<T> (deep-copies the rhs value)
    void assign ( optional_base const& rhs )
    {
      if (is_initialized())
      {
        if ( rhs.is_initialized() )
             assign_value(rhs.get_impl());
        else destroy();
      }
      else
      {
        if ( rhs.is_initialized() )
          construct(rhs.get_impl());
      }
    }

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Assigns from another optional<T> (deep-moves the rhs value)
    void assign ( optional_base&& rhs )
    {
      if (is_initialized())
      {
        if ( rhs.is_initialized() )
             assign_value( boost::move(rhs.get_impl()) );
        else destroy();
      }
      else
      {
        if ( rhs.is_initialized() )
          construct(boost::move(rhs.get_impl()));
      }
    }
#endif

    // Assigns from another _convertible_ optional<U> (deep-copies the rhs value)
    template<class U>
    void assign ( optional<U> const& rhs )
    {
      if (is_initialized())
      {
        if ( rhs.is_initialized() )
#ifndef BOOST_OPTIONAL_CONFIG_RESTORE_ASSIGNMENT_OF_NONCONVERTIBLE_TYPES
          assign_value( rhs.get() );
#else
          assign_value( static_cast<value_type>(rhs.get()) );
#endif

        else destroy();
      }
      else
      {
        if ( rhs.is_initialized() )
#ifndef BOOST_OPTIONAL_CONFIG_RESTORE_ASSIGNMENT_OF_NONCONVERTIBLE_TYPES
          construct(rhs.get());
#else
          construct(static_cast<value_type>(rhs.get()));
#endif
      }
    }

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // move-assigns from another _convertible_ optional<U> (deep-moves from the rhs value)
    template<class U>
    void assign ( optional<U>&& rhs )
    {
      typedef BOOST_DEDUCED_TYPENAME optional<U>::rval_reference_type ref_type;
      if (is_initialized())
      {
        if ( rhs.is_initialized() )
             assign_value( static_cast<ref_type>(rhs.get()) );
        else destroy();
      }
      else
      {
        if ( rhs.is_initialized() )
          construct(static_cast<ref_type>(rhs.get()));
      }
    }
#endif

    // Assigns from a T (deep-copies the rhs value)
    void assign ( argument_type val )
    {
      if (is_initialized())
           assign_value(val);
      else construct(val);
    }

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Assigns from a T (deep-moves the rhs value)
    void assign ( rval_reference_type val )
    {
      if (is_initialized())
           assign_value( boost::move(val) );
      else construct( boost::move(val) );
    }
#endif

    // Assigns from "none", destroying the current value, if any, leaving this UNINITIALIZED
    // No-throw (assuming T::~T() doesn't)
    void assign ( none_t ) BOOST_NOEXCEPT { destroy(); }

#ifndef BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    template<class Expr, class ExprPtr>
    void assign_expr ( Expr&& expr, ExprPtr const* tag )
    {
      if (is_initialized())
        assign_expr_to_initialized(boost::forward<Expr>(expr),tag);
      else construct(boost::forward<Expr>(expr),tag);
    }
#else
    template<class Expr>
    void assign_expr ( Expr const& expr, Expr const* tag )
    {
      if (is_initialized())
        assign_expr_to_initialized(expr,tag);
      else construct(expr,tag);
    }
#endif

#endif

  public :

    // Destroys the current value, if any, leaving this UNINITIALIZED
    // No-throw (assuming T::~T() doesn't)
    void reset() BOOST_NOEXCEPT { destroy(); }

    // **DEPPRECATED** Replaces the current value -if any- with 'val'
    void reset ( argument_type val ) { assign(val); }

    // Returns a pointer to the value if this is initialized, otherwise,
    // returns NULL.
    // No-throw
    pointer_const_type get_ptr() const { return m_initialized ? get_ptr_impl() : 0 ; }
    pointer_type       get_ptr()       { return m_initialized ? get_ptr_impl() : 0 ; }

    bool is_initialized() const BOOST_NOEXCEPT { return m_initialized ; }

  protected :

    void construct ( argument_type val )
     {
       ::new (m_storage.address()) unqualified_value_type(val) ;
       m_initialized = true ;
     }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    void construct ( rval_reference_type val )
     {
       ::new (m_storage.address()) unqualified_value_type( boost::move(val) ) ;
       m_initialized = true ;
     }
#endif


#if (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES) && (!defined BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    // Constructs in-place
    // upon exception *this is always uninitialized
    template<class... Args>
    void construct ( in_place_init_t, Args&&... args )
    {
      ::new (m_storage.address()) unqualified_value_type( boost::forward<Args>(args)... ) ;
      m_initialized = true ;
    }

    template<class... Args>
    void emplace_assign ( Args&&... args )
    {
      destroy();
      construct(in_place_init, boost::forward<Args>(args)...);
    }

    template<class... Args>
    explicit optional_base ( in_place_init_t, Args&&... args )
      :
      m_initialized(false)
    {
      construct(in_place_init, boost::forward<Args>(args)...);
    }

    template<class... Args>
    explicit optional_base ( in_place_init_if_t, bool cond, Args&&... args )
      :
      m_initialized(false)
    {
      if ( cond )
        construct(in_place_init, boost::forward<Args>(args)...);
    }
#elif (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES)
    template<class Arg>
    void construct ( in_place_init_t, Arg&& arg )
     {
       ::new (m_storage.address()) unqualified_value_type( boost::forward<Arg>(arg) );
       m_initialized = true ;
     }

    void construct ( in_place_init_t )
     {
       ::new (m_storage.address()) unqualified_value_type();
       m_initialized = true ;
     }

    template<class Arg>
    void emplace_assign ( Arg&& arg )
     {
       destroy();
       construct(in_place_init, boost::forward<Arg>(arg)) ;
     }

    void emplace_assign ()
     {
       destroy();
       construct(in_place_init) ;
     }

    template<class Arg>
    explicit optional_base ( in_place_init_t, Arg&& arg )
      :
      m_initialized(false)
    {
      construct(in_place_init, boost::forward<Arg>(arg));
    }

    explicit optional_base ( in_place_init_t )
      :
      m_initialized(false)
    {
      construct(in_place_init);
    }

    template<class Arg>
    explicit optional_base ( in_place_init_if_t, bool cond, Arg&& arg )
      :
      m_initialized(false)
    {
      if ( cond )
        construct(in_place_init, boost::forward<Arg>(arg));
    }

    explicit optional_base ( in_place_init_if_t, bool cond )
      :
      m_initialized(false)
    {
      if ( cond )
        construct(in_place_init);
    }

#else

    template<class Arg>
    void construct ( in_place_init_t, const Arg& arg )
     {
       ::new (m_storage.address()) unqualified_value_type( arg );
       m_initialized = true ;
     }

    template<class Arg>
    void construct ( in_place_init_t, Arg& arg )
     {
       ::new (m_storage.address()) unqualified_value_type( arg );
       m_initialized = true ;
     }

    void construct ( in_place_init_t )
     {
       ::new (m_storage.address()) unqualified_value_type();
       m_initialized = true ;
     }

    template<class Arg>
    void emplace_assign ( const Arg& arg )
    {
      destroy();
      construct(in_place_init, arg);
    }

    template<class Arg>
    void emplace_assign ( Arg& arg )
    {
      destroy();
      construct(in_place_init, arg);
    }

    void emplace_assign ()
    {
      destroy();
      construct(in_place_init);
    }

    template<class Arg>
    explicit optional_base ( in_place_init_t, const Arg& arg )
      : m_initialized(false)
    {
      construct(in_place_init, arg);
    }

    template<class Arg>
    explicit optional_base ( in_place_init_t, Arg& arg )
      : m_initialized(false)
    {
      construct(in_place_init, arg);
    }

    explicit optional_base ( in_place_init_t )
      : m_initialized(false)
    {
      construct(in_place_init);
    }

    template<class Arg>
    explicit optional_base ( in_place_init_if_t, bool cond, const Arg& arg )
      : m_initialized(false)
    {
      if ( cond )
        construct(in_place_init, arg);
    }

    template<class Arg>
    explicit optional_base ( in_place_init_if_t, bool cond, Arg& arg )
      : m_initialized(false)
    {
      if ( cond )
        construct(in_place_init, arg);
    }

    explicit optional_base ( in_place_init_if_t, bool cond )
      : m_initialized(false)
    {
      if ( cond )
        construct(in_place_init);
    }
#endif

#ifndef BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Constructs in-place using the given factory
    template<class Expr>
    void construct ( Expr&& factory, in_place_factory_base const* )
     {
       boost_optional_detail::construct<value_type>(factory, m_storage.address());
       m_initialized = true ;
     }

    // Constructs in-place using the given typed factory
    template<class Expr>
    void construct ( Expr&& factory, typed_in_place_factory_base const* )
     {
       factory.apply(m_storage.address()) ;
       m_initialized = true ;
     }

    template<class Expr>
    void assign_expr_to_initialized ( Expr&& factory, in_place_factory_base const* tag )
     {
       destroy();
       construct(factory,tag);
     }

    // Constructs in-place using the given typed factory
    template<class Expr>
    void assign_expr_to_initialized ( Expr&& factory, typed_in_place_factory_base const* tag )
     {
       destroy();
       construct(factory,tag);
     }

#else
    // Constructs in-place using the given factory
    template<class Expr>
    void construct ( Expr const& factory, in_place_factory_base const* )
     {
       boost_optional_detail::construct<value_type>(factory, m_storage.address());
       m_initialized = true ;
     }

    // Constructs in-place using the given typed factory
    template<class Expr>
    void construct ( Expr const& factory, typed_in_place_factory_base const* )
     {
       factory.apply(m_storage.address()) ;
       m_initialized = true ;
     }

    template<class Expr>
    void assign_expr_to_initialized ( Expr const& factory, in_place_factory_base const* tag )
     {
       destroy();
       construct(factory,tag);
     }

    // Constructs in-place using the given typed factory
    template<class Expr>
    void assign_expr_to_initialized ( Expr const& factory, typed_in_place_factory_base const* tag )
     {
       destroy();
       construct(factory,tag);
     }
#endif

#endif

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Constructs using any expression implicitly convertible to the single argument
    // of a one-argument T constructor.
    // Converting constructions of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting constructor of T from U.
    template<class Expr>
    void construct ( Expr&& expr, void const* )
    {
      new (m_storage.address()) unqualified_value_type(boost::forward<Expr>(expr)) ;
      m_initialized = true ;
    }

    // Assigns using a form any expression implicitly convertible to the single argument
    // of a T's assignment operator.
    // Converting assignments of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting assignment of T from U.
    template<class Expr>
    void assign_expr_to_initialized ( Expr&& expr, void const* )
    {
      assign_value( boost::forward<Expr>(expr) );
    }
#else
    // Constructs using any expression implicitly convertible to the single argument
    // of a one-argument T constructor.
    // Converting constructions of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting constructor of T from U.
    template<class Expr>
    void construct ( Expr const& expr, void const* )
     {
       new (m_storage.address()) unqualified_value_type(expr) ;
       m_initialized = true ;
     }

    // Assigns using a form any expression implicitly convertible to the single argument
    // of a T's assignment operator.
    // Converting assignments of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting assignment of T from U.
    template<class Expr>
    void assign_expr_to_initialized ( Expr const& expr, void const* )
     {
       assign_value(expr);
     }

#endif

#ifdef BOOST_OPTIONAL_WEAK_OVERLOAD_RESOLUTION
    // BCB5.64 (and probably lower versions) workaround.
    //   The in-place factories are supported by means of catch-all constructors
    //   and assignment operators (the functions are parameterized in terms of
    //   an arbitrary 'Expr' type)
    //   This compiler incorrectly resolves the overload set and sinks optional<T> and optional<U>
    //   to the 'Expr'-taking functions even though explicit overloads are present for them.
    //   Thus, the following overload is needed to properly handle the case when the 'lhs'
    //   is another optional.
    //
    // For VC<=70 compilers this workaround dosen't work becasue the comnpiler issues and error
    // instead of choosing the wrong overload
    //
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Notice that 'Expr' will be optional<T> or optional<U> (but not optional_base<..>)
    template<class Expr>
    void construct ( Expr&& expr, optional_tag const* )
     {
       if ( expr.is_initialized() )
       {
         // An exception can be thrown here.
         // It it happens, THIS will be left uninitialized.
         new (m_storage.address()) unqualified_value_type(boost::move(expr.get())) ;
         m_initialized = true ;
       }
     }
#else
    // Notice that 'Expr' will be optional<T> or optional<U> (but not optional_base<..>)
    template<class Expr>
    void construct ( Expr const& expr, optional_tag const* )
     {
       if ( expr.is_initialized() )
       {
         // An exception can be thrown here.
         // It it happens, THIS will be left uninitialized.
         new (m_storage.address()) unqualified_value_type(expr.get()) ;
         m_initialized = true ;
       }
     }
#endif
#endif // defined BOOST_OPTIONAL_WEAK_OVERLOAD_RESOLUTION

    void assign_value ( argument_type val ) { get_impl() = val; }
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    void assign_value ( rval_reference_type val ) { get_impl() = static_cast<rval_reference_type>(val); }
#endif

    void destroy()
    {
      if ( m_initialized )
        destroy_impl() ;
    }

    reference_const_type get_impl() const { return m_storage.ref() ; }
    reference_type       get_impl()       { return m_storage.ref() ; }

    pointer_const_type get_ptr_impl() const { return m_storage.ptr_ref(); }
    pointer_type       get_ptr_impl()       { return m_storage.ptr_ref(); }

  private :

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1900))
    void destroy_impl ( ) { m_storage.ptr_ref()->~T() ; m_initialized = false ; }
#else
    void destroy_impl ( ) { m_storage.ref().T::~T() ; m_initialized = false ; }
#endif

    bool m_initialized ;
    storage_type m_storage ;
} ;

#include <boost/optional/detail/optional_trivially_copyable_base.hpp>

// definition of metafunction is_optional_val_init_candidate
template <typename U>
struct is_optional_or_tag
  : boost::conditional< boost::is_base_of<optional_detail::optional_tag, BOOST_DEDUCED_TYPENAME boost::decay<U>::type>::value
                     || boost::is_same<BOOST_DEDUCED_TYPENAME boost::decay<U>::type, none_t>::value
                     || boost::is_same<BOOST_DEDUCED_TYPENAME boost::decay<U>::type, in_place_init_t>::value
                     || boost::is_same<BOOST_DEDUCED_TYPENAME boost::decay<U>::type, in_place_init_if_t>::value,
    boost::true_type, boost::false_type>::type
{};

template <typename T, typename U>
struct has_dedicated_constructor
  : boost::disjunction<is_optional_or_tag<U>, boost::is_same<T, BOOST_DEDUCED_TYPENAME boost::decay<U>::type> >
{};

template <typename U>
struct is_in_place_factory
  : boost::disjunction< boost::is_base_of<boost::in_place_factory_base, BOOST_DEDUCED_TYPENAME boost::decay<U>::type>,
                        boost::is_base_of<boost::typed_in_place_factory_base, BOOST_DEDUCED_TYPENAME boost::decay<U>::type> >
{};

#if !defined(BOOST_OPTIONAL_DETAIL_NO_IS_CONSTRUCTIBLE_TRAIT)

template <typename T, typename U>
struct is_factory_or_constructible_to_T
  : boost::disjunction< is_in_place_factory<U>, boost::is_constructible<T, U&&> >
{};

template <typename T, typename U>
struct is_optional_constructible : boost::is_constructible<T, U>
{};

#else

template <typename, typename>
struct is_factory_or_constructible_to_T : boost::true_type
{};

template <typename T, typename U>
struct is_optional_constructible : boost::true_type
{};

#endif // is_convertible condition

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)
// for is_assignable

#if (!defined BOOST_NO_CXX11_RVALUE_REFERENCES)
// On some initial rvalue reference implementations GCC does it in a strange way,
// preferring perfect-forwarding constructor to implicit copy constructor.

template <typename T, typename U>
struct is_opt_assignable
  : boost::conjunction<boost::is_convertible<U&&, T>, boost::is_assignable<T&, U&&> >
{};

#else

template <typename T, typename U>
struct is_opt_assignable
  : boost::conjunction<boost::is_convertible<U, T>, boost::is_assignable<T&, U> >
{};

#endif

#else

template <typename T, typename U>
struct is_opt_assignable : boost::is_convertible<U, T>
{};

#endif

template <typename T, typename U>
struct is_factory_or_opt_assignable_to_T
  : boost::disjunction< is_in_place_factory<U>, is_opt_assignable<T, U> >
{};

template <typename T, typename U, bool = has_dedicated_constructor<T, U>::value>
struct is_optional_val_init_candidate
  : boost::false_type
{};

template <typename T, typename U>
struct is_optional_val_init_candidate<T, U, false>
  : is_factory_or_constructible_to_T<T, U>
{};

template <typename T, typename U, bool = has_dedicated_constructor<T, U>::value>
struct is_optional_val_assign_candidate
  : boost::false_type
{};

template <typename T, typename U>
struct is_optional_val_assign_candidate<T, U, false>
  : is_factory_or_opt_assignable_to_T<T, U>
{};

} // namespace optional_detail

namespace optional_config {

template <typename T>
struct optional_uses_direct_storage_for
  : boost::conditional<(boost::is_scalar<T>::value && !boost::is_const<T>::value && !boost::is_volatile<T>::value)
                      , boost::true_type, boost::false_type>::type
{};

} // namespace optional_config


#ifndef BOOST_OPTIONAL_DETAIL_NO_DIRECT_STORAGE_SPEC
#  define BOOST_OPTIONAL_BASE_TYPE(T) boost::conditional< optional_config::optional_uses_direct_storage_for<T>::value, \
                                      optional_detail::tc_optional_base<T>, \
                                      optional_detail::optional_base<T> \
                                      >::type
#else
#  define BOOST_OPTIONAL_BASE_TYPE(T) optional_detail::optional_base<T>
#endif

template<class T>
class optional
  : public BOOST_OPTIONAL_BASE_TYPE(T)
{
    typedef typename BOOST_OPTIONAL_BASE_TYPE(T) base ;

  public :

    typedef optional<T> this_type ;

    typedef BOOST_DEDUCED_TYPENAME base::value_type           value_type ;
    typedef BOOST_DEDUCED_TYPENAME base::reference_type       reference_type ;
    typedef BOOST_DEDUCED_TYPENAME base::reference_const_type reference_const_type ;
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    typedef BOOST_DEDUCED_TYPENAME base::rval_reference_type  rval_reference_type ;
    typedef BOOST_DEDUCED_TYPENAME base::reference_type_of_temporary_wrapper reference_type_of_temporary_wrapper ;
#endif
    typedef BOOST_DEDUCED_TYPENAME base::pointer_type         pointer_type ;
    typedef BOOST_DEDUCED_TYPENAME base::pointer_const_type   pointer_const_type ;
    typedef BOOST_DEDUCED_TYPENAME base::argument_type        argument_type ;

    // Creates an optional<T> uninitialized.
    // No-throw
    optional() BOOST_NOEXCEPT : base() {}

    // Creates an optional<T> uninitialized.
    // No-throw
    optional( none_t none_ ) BOOST_NOEXCEPT : base(none_) {}

    // Creates an optional<T> initialized with 'val'.
    // Can throw if T::T(T const&) does
    optional ( argument_type val ) : base(optional_detail::init_value_tag(), val) {}

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Creates an optional<T> initialized with 'move(val)'.
    // Can throw if T::T(T &&) does
    optional ( rval_reference_type val ) : base(optional_detail::init_value_tag(), boost::forward<T>(val))
      {}
#endif

    // Creates an optional<T> initialized with 'val' IFF cond is true, otherwise creates an uninitialized optional.
    // Can throw if T::T(T const&) does
    optional ( bool cond, argument_type val ) : base(cond,val) {}

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    /// Creates an optional<T> initialized with 'val' IFF cond is true, otherwise creates an uninitialized optional.
    // Can throw if T::T(T &&) does
    optional ( bool cond, rval_reference_type val ) : base( cond, boost::forward<T>(val) )
      {}
#endif

    // NOTE: MSVC needs templated versions first

    // Creates a deep copy of another convertible optional<U>
    // Requires a valid conversion from U to T.
    // Can throw if T::T(U const&) does
    template<class U>
    explicit optional ( optional<U> const& rhs
#ifndef BOOST_OPTIONAL_DETAIL_NO_SFINAE_FRIENDLY_CONSTRUCTORS
                        ,BOOST_DEDUCED_TYPENAME boost::enable_if< optional_detail::is_optional_constructible<T, U const&>, bool>::type = true
#endif
                      )
      :
      base()
    {
      if ( rhs.is_initialized() )
        this->construct(rhs.get());
    }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Creates a deep move of another convertible optional<U>
    // Requires a valid conversion from U to T.
    // Can throw if T::T(U&&) does
    template<class U>
    explicit optional ( optional<U> && rhs
#ifndef BOOST_OPTIONAL_DETAIL_NO_SFINAE_FRIENDLY_CONSTRUCTORS
                        ,BOOST_DEDUCED_TYPENAME boost::enable_if< optional_detail::is_optional_constructible<T, U>, bool>::type = true
#endif
                      )
      :
      base()
    {
      if ( rhs.is_initialized() )
        this->construct( boost::move(rhs.get()) );
    }
#endif

#ifndef BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT
    // Creates an optional<T> with an expression which can be either
    //  (a) An instance of InPlaceFactory (i.e. in_place(a,b,...,n);
    //  (b) An instance of TypedInPlaceFactory ( i.e. in_place<T>(a,b,...,n);
    //  (c) Any expression implicitly convertible to the single type
    //      of a one-argument T's constructor.
    //  (d*) Weak compilers (BCB) might also resolved Expr as optional<T> and optional<U>
    //       even though explicit overloads are present for these.
    // Depending on the above some T ctor is called.
    // Can throw if the resolved T ctor throws.
#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES


  template<class Expr>
  explicit optional ( Expr&& expr,
                      BOOST_DEDUCED_TYPENAME boost::enable_if< optional_detail::is_optional_val_init_candidate<T, Expr>, bool>::type = true
  )
    : base(boost::forward<Expr>(expr),boost::addressof(expr))
    {}

#else
    template<class Expr>
    explicit optional ( Expr const& expr ) : base(expr,boost::addressof(expr)) {}
#endif // !defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
#endif // !defined BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT

    // Creates a deep copy of another optional<T>
    // Can throw if T::T(T const&) does
#ifndef BOOST_OPTIONAL_DETAIL_NO_DEFAULTED_MOVE_FUNCTIONS
    optional ( optional const& ) = default;
#else
    optional ( optional const& rhs ) : base( static_cast<base const&>(rhs) ) {}
#endif

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Creates a deep move of another optional<T>
    // Can throw if T::T(T&&) does

#ifndef BOOST_OPTIONAL_DETAIL_NO_DEFAULTED_MOVE_FUNCTIONS
    optional ( optional && ) = default;
#else
    optional ( optional && rhs )
      BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value)
      : base( boost::move(rhs) )
    {}
#endif

#endif

#if BOOST_WORKAROUND(_MSC_VER, <= 1600)
    //  On old MSVC compilers the implicitly declared dtor is not called
    ~optional() {}
#endif


#if !defined(BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT) && !defined(BOOST_OPTIONAL_WEAK_OVERLOAD_RESOLUTION)
    // Assigns from an expression. See corresponding constructor.
    // Basic Guarantee: If the resolved T ctor throws, this is left UNINITIALIZED
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

    template<class Expr>
    BOOST_DEDUCED_TYPENAME boost::enable_if<optional_detail::is_optional_val_assign_candidate<T, Expr>, optional&>::type
    operator= ( Expr&& expr )
      {
        this->assign_expr(boost::forward<Expr>(expr),boost::addressof(expr));
        return *this ;
      }

#else
    template<class Expr>
    optional& operator= ( Expr const& expr )
      {
        this->assign_expr(expr,boost::addressof(expr));
        return *this ;
      }
#endif // !defined  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
#endif // !defined(BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT) && !defined(BOOST_OPTIONAL_WEAK_OVERLOAD_RESOLUTION)

    // Copy-assigns from another convertible optional<U> (converts && deep-copies the rhs value)
    // Requires a valid conversion from U to T.
    // Basic Guarantee: If T::T( U const& ) throws, this is left UNINITIALIZED
    template<class U>
    optional& operator= ( optional<U> const& rhs )
      {
        this->assign(rhs);
        return *this ;
      }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Move-assigns from another convertible optional<U> (converts && deep-moves the rhs value)
    // Requires a valid conversion from U to T.
    // Basic Guarantee: If T::T( U && ) throws, this is left UNINITIALIZED
    template<class U>
    optional& operator= ( optional<U> && rhs )
      {
        this->assign(boost::move(rhs));
        return *this ;
      }
#endif

    // Assigns from another optional<T> (deep-copies the rhs value)
    // Basic Guarantee: If T::T( T const& ) throws, this is left UNINITIALIZED
    //  (NOTE: On BCB, this operator is not actually called and left is left UNMODIFIED in case of a throw)
#ifndef BOOST_OPTIONAL_DETAIL_NO_DEFAULTED_MOVE_FUNCTIONS
    optional& operator= ( optional const& rhs ) = default;
#else
    optional& operator= ( optional const& rhs )
      {
        this->assign( static_cast<base const&>(rhs) ) ;
        return *this ;
      }
#endif

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Assigns from another optional<T> (deep-moves the rhs value)
#ifndef BOOST_OPTIONAL_DETAIL_NO_DEFAULTED_MOVE_FUNCTIONS
    optional& operator= ( optional && ) = default;
#else
    optional& operator= ( optional && rhs )
      BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value && ::boost::is_nothrow_move_assignable<T>::value)
      {
        this->assign( static_cast<base &&>(rhs) ) ;
        return *this ;
      }
#endif

#endif // BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

#ifndef BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX

    // Assigns from a T (deep-moves/copies the rhs value)
    template <typename T_>
    BOOST_DEDUCED_TYPENAME boost::enable_if<boost::is_same<T, BOOST_DEDUCED_TYPENAME boost::decay<T_>::type>, optional&>::type
    operator= ( T_&& val )
      {
        this->assign( boost::forward<T_>(val) ) ;
        return *this ;
      }

#else

    // Assigns from a T (deep-copies the rhs value)
    // Basic Guarantee: If T::( T const& ) throws, this is left UNINITIALIZED
    optional& operator= ( argument_type val )
      {
        this->assign( val ) ;
        return *this ;
      }

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Assigns from a T (deep-moves the rhs value)
    optional& operator= ( rval_reference_type val )
      {
        this->assign( boost::move(val) ) ;
        return *this ;
      }
#endif

#endif // BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX

    // Assigns from a "none"
    // Which destroys the current value, if any, leaving this UNINITIALIZED
    // No-throw (assuming T::~T() doesn't)
    optional& operator= ( none_t none_ ) BOOST_NOEXCEPT
      {
        this->assign( none_ ) ;
        return *this ;
      }

#if (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES) && (!defined BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    // Constructs in-place
    // upon exception *this is always uninitialized
    template<class... Args>
    void emplace ( Args&&... args )
    {
      this->emplace_assign( boost::forward<Args>(args)... );
    }

    template<class... Args>
    explicit optional ( in_place_init_t, Args&&... args )
    : base( in_place_init, boost::forward<Args>(args)... )
    {}

    template<class... Args>
    explicit optional ( in_place_init_if_t, bool cond, Args&&... args )
    : base( in_place_init_if, cond, boost::forward<Args>(args)... )
    {}

#elif (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES)
    template<class Arg>
    void emplace ( Arg&& arg )
     {
       this->emplace_assign( boost::forward<Arg>(arg) );
     }

    void emplace ()
     {
       this->emplace_assign();
     }

    template<class Args>
    explicit optional ( in_place_init_t, Args&& args )
    : base( in_place_init, boost::forward<Args>(args) )
    {}

    explicit optional ( in_place_init_t )
    : base( in_place_init )
    {}

    template<class Args>
    explicit optional ( in_place_init_if_t, bool cond, Args&& args )
    : base( in_place_init_if, cond, boost::forward<Args>(args) )
    {}

    explicit optional ( in_place_init_if_t, bool cond )
    : base( in_place_init_if, cond )
    {}
#else
    template<class Arg>
    void emplace ( const Arg& arg )
     {
       this->emplace_assign( arg );
     }

    template<class Arg>
    void emplace ( Arg& arg )
     {
       this->emplace_assign( arg );
     }

    void emplace ()
     {
       this->emplace_assign();
     }

    template<class Arg>
    explicit optional ( in_place_init_t, const Arg& arg )
    : base( in_place_init, arg )
    {}

    template<class Arg>
    explicit optional ( in_place_init_t, Arg& arg )
    : base( in_place_init, arg )
    {}

    explicit optional ( in_place_init_t )
    : base( in_place_init )
    {}

    template<class Arg>
    explicit optional ( in_place_init_if_t, bool cond, const Arg& arg )
    : base( in_place_init_if, cond, arg )
    {}

    template<class Arg>
    explicit optional ( in_place_init_if_t, bool cond, Arg& arg )
    : base( in_place_init_if, cond, arg )
    {}

    explicit optional ( in_place_init_if_t, bool cond )
    : base( in_place_init_if, cond )
    {}
#endif

    void swap( optional & arg )
      BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value && ::boost::is_nothrow_move_assignable<T>::value)
      {
        // allow for Koenig lookup
        boost::swap(*this, arg);
      }


    // Returns a reference to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
    reference_const_type get() const { BOOST_ASSERT(this->is_initialized()) ; return this->get_impl(); }
    reference_type       get()       { BOOST_ASSERT(this->is_initialized()) ; return this->get_impl(); }

    // Returns a copy of the value if this is initialized, 'v' otherwise
    reference_const_type get_value_or ( reference_const_type v ) const { return this->is_initialized() ? get() : v ; }
    reference_type       get_value_or ( reference_type       v )       { return this->is_initialized() ? get() : v ; }

    // Returns a pointer to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
    pointer_const_type operator->() const { BOOST_ASSERT(this->is_initialized()) ; return this->get_ptr_impl() ; }
    pointer_type       operator->()       { BOOST_ASSERT(this->is_initialized()) ; return this->get_ptr_impl() ; }

    // Returns a reference to the value if this is initialized, otherwise,
    // the behaviour is UNDEFINED
    // No-throw
#if (!defined BOOST_NO_CXX11_REF_QUALIFIERS) && (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES)
    reference_const_type operator *() const& { return this->get() ; }
    reference_type       operator *() &      { return this->get() ; }
    reference_type_of_temporary_wrapper operator *() && { return boost::move(this->get()) ; }
#else
    reference_const_type operator *() const { return this->get() ; }
    reference_type       operator *()       { return this->get() ; }
#endif // !defined BOOST_NO_CXX11_REF_QUALIFIERS

#if (!defined BOOST_NO_CXX11_REF_QUALIFIERS) && (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES)
    reference_const_type value() const&
      {
        if (this->is_initialized())
          return this->get() ;
        else
          throw_exception(bad_optional_access());
      }

    reference_type value() &
      {
        if (this->is_initialized())
          return this->get() ;
        else
          throw_exception(bad_optional_access());
      }

    reference_type_of_temporary_wrapper value() &&
      {
        if (this->is_initialized())
          return boost::move(this->get()) ;
        else
          throw_exception(bad_optional_access());
      }

#else
    reference_const_type value() const
      {
        if (this->is_initialized())
          return this->get() ;
        else
          throw_exception(bad_optional_access());
      }

    reference_type value()
      {
        if (this->is_initialized())
          return this->get() ;
        else
          throw_exception(bad_optional_access());
      }
#endif


#ifndef BOOST_NO_CXX11_REF_QUALIFIERS
    template <class U>
    value_type value_or ( U&& v ) const&
      {
        if (this->is_initialized())
          return get();
        else
          return boost::forward<U>(v);
      }

    template <class U>
    value_type value_or ( U&& v ) &&
      {
        if (this->is_initialized())
          return boost::move(get());
        else
          return boost::forward<U>(v);
      }
#elif !defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    template <class U>
    value_type value_or ( U&& v ) const
      {
        if (this->is_initialized())
          return get();
        else
          return boost::forward<U>(v);
      }
#else
    template <class U>
    value_type value_or ( U const& v ) const
      {
        if (this->is_initialized())
          return get();
        else
          return v;
      }

    template <class U>
    value_type value_or ( U& v ) const
      {
        if (this->is_initialized())
          return get();
        else
          return v;
      }
#endif


#if (!defined BOOST_NO_CXX11_REF_QUALIFIERS) && (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES)
    template <typename F>
    value_type value_or_eval ( F f ) const&
      {
        if (this->is_initialized())
          return get();
        else
          return f();
      }

    template <typename F>
    value_type value_or_eval ( F f ) &&
      {
        if (this->is_initialized())
          return boost::move(get());
        else
          return f();
      }

    template <typename F>
    optional<typename boost::result_of<F(reference_type)>::type> map(F f) &
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }

    template <typename F>
    optional<typename boost::result_of<F(reference_const_type)>::type> map(F f) const&
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }

    template <typename F>
    optional<typename boost::result_of<F(reference_type_of_temporary_wrapper)>::type> map(F f) &&
      {
        if (this->has_value())
          return f(boost::move(this->get()));
        else
          return none;
      }

    template <typename F>
    optional<typename optional_detail::optional_value_type<typename boost::result_of<F(reference_type)>::type>::type> flat_map(F f) &
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }

    template <typename F>
    optional<typename optional_detail::optional_value_type<typename boost::result_of<F(reference_const_type)>::type>::type> flat_map(F f) const&
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }

    template <typename F>
    optional<typename optional_detail::optional_value_type<typename boost::result_of<F(reference_type_of_temporary_wrapper)>::type>::type> flat_map(F f) &&
      {
        if (this->has_value())
          return f(boost::move(get()));
        else
          return none;
      }

#else
    template <typename F>
    value_type value_or_eval ( F f ) const
      {
        if (this->is_initialized())
          return get();
        else
          return f();
      }

    template <typename F>
    optional<typename boost::result_of<F(reference_type)>::type> map(F f)
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }

    template <typename F>
    optional<typename boost::result_of<F(reference_const_type)>::type> map(F f) const
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }

    template <typename F>
    optional<typename optional_detail::optional_value_type<typename boost::result_of<F(reference_type)>::type>::type> flat_map(F f)
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }

    template <typename F>
    optional<typename optional_detail::optional_value_type<typename boost::result_of<F(reference_const_type)>::type>::type> flat_map(F f) const
      {
        if (this->has_value())
          return f(get());
        else
          return none;
      }

#endif

    bool has_value() const BOOST_NOEXCEPT { return this->is_initialized() ; }

    bool operator!() const BOOST_NOEXCEPT { return !this->is_initialized() ; }

    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
} ;

} // namespace boost

#endif // BOOST_OPTIONAL_CONFIG_USE_OLD_IMPLEMENTATION_OF_OPTIONAL

namespace boost {

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
template<class T>
class optional<T&&>
{
  BOOST_STATIC_ASSERT_MSG(sizeof(T) == 0, "Optional rvalue references are illegal.");
} ;
#endif

} // namespace boost

#ifndef BOOST_OPTIONAL_CONFIG_DONT_SPECIALIZE_OPTIONAL_REFS
# include <boost/optional/detail/optional_reference_spec.hpp>
#endif

namespace boost {

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

template<class T>
inline
optional<BOOST_DEDUCED_TYPENAME boost::decay<T>::type> make_optional ( T && v  )
{
  return optional<BOOST_DEDUCED_TYPENAME boost::decay<T>::type>(boost::forward<T>(v));
}

// Returns optional<T>(cond,v)
template<class T>
inline
optional<BOOST_DEDUCED_TYPENAME boost::decay<T>::type> make_optional ( bool cond, T && v )
{
  return optional<BOOST_DEDUCED_TYPENAME boost::decay<T>::type>(cond,boost::forward<T>(v));
}

#else

// Returns optional<T>(v)
template<class T>
inline
optional<T> make_optional ( T const& v  )
{
  return optional<T>(v);
}

// Returns optional<T>(cond,v)
template<class T>
inline
optional<T> make_optional ( bool cond, T const& v )
{
  return optional<T>(cond,v);
}

#endif // BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

// Returns a reference to the value if this is initialized, otherwise, the behaviour is UNDEFINED.
// No-throw
template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::reference_const_type
get ( optional<T> const& opt )
{
  return opt.get() ;
}

template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::reference_type
get ( optional<T>& opt )
{
  return opt.get() ;
}

// Returns a pointer to the value if this is initialized, otherwise, returns NULL.
// No-throw
template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::pointer_const_type
get ( optional<T> const* opt )
{
  return opt->get_ptr() ;
}

template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::pointer_type
get ( optional<T>* opt )
{
  return opt->get_ptr() ;
}

// Returns a reference to the value if this is initialized, otherwise, the behaviour is UNDEFINED.
// No-throw
template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::reference_const_type
get_optional_value_or ( optional<T> const& opt, BOOST_DEDUCED_TYPENAME optional<T>::reference_const_type v )
{
  return opt.get_value_or(v) ;
}

template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::reference_type
get_optional_value_or ( optional<T>& opt, BOOST_DEDUCED_TYPENAME optional<T>::reference_type v )
{
  return opt.get_value_or(v) ;
}

// Returns a pointer to the value if this is initialized, otherwise, returns NULL.
// No-throw
template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::pointer_const_type
get_pointer ( optional<T> const& opt )
{
  return opt.get_ptr() ;
}

template<class T>
inline
BOOST_DEDUCED_TYPENAME optional<T>::pointer_type
get_pointer ( optional<T>& opt )
{
  return opt.get_ptr() ;
}

} // namespace boost

#ifndef BOOST_NO_IOSTREAM
namespace boost {

// The following declaration prevents a bug where operator safe-bool is used upon streaming optional object if you forget the IO header.
template<class CharType, class CharTrait>
std::basic_ostream<CharType, CharTrait>&
operator<<(std::basic_ostream<CharType, CharTrait>& os, optional_detail::optional_tag const&)
{
  BOOST_STATIC_ASSERT_MSG(sizeof(CharType) == 0, "If you want to output boost::optional, include header <boost/optional/optional_io.hpp>");
  return os;
}

} // namespace boost
#endif // BOOST_NO_IOSTREAM

#include <boost/optional/detail/optional_relops.hpp>
#include <boost/optional/detail/optional_swap.hpp>

#endif // header guard

/* optional.hpp
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
*/