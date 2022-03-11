// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2014 - 2018 Andrzej Krzemienski.
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
#include <iosfwd>

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
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/type_with_alignment.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_constructible.hpp>
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
       ::new (m_storage.address()) value_type(val) ;
       m_initialized = true ;
     }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    void construct ( rval_reference_type val )
     {
       ::new (m_storage.address()) value_type( boost::move(val) ) ;
       m_initialized = true ;
     }
#endif


#if (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES) && (!defined BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    // Constructs in-place
    // upon exception *this is always uninitialized
    template<class... Args>
    void construct ( in_place_init_t, Args&&... args )
    {
      ::new (m_storage.address()) value_type( boost::forward<Args>(args)... ) ;
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
       ::new (m_storage.address()) value_type( boost::forward<Arg>(arg) );
       m_initialized = true ;
     }

    void construct ( in_place_init_t )
     {
       ::new (m_storage.address()) value_type();
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
       ::new (m_storage.address()) value_type( arg );
       m_initialized = true ;
     }

    template<class Arg>
    void construct ( in_place_init_t, Arg& arg )
     {
       ::new (m_storage.address()) value_type( arg );
       m_initialized = true ;
     }

    void construct ( in_place_init_t )
     {
       ::new (m_storage.address()) value_type();
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
      new (m_storage.address()) value_type(boost::forward<Expr>(expr)) ;
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
       new (m_storage.address()) value_type(expr) ;
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
         new (m_storage.address()) value_type(boost::move(expr.get())) ;
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
         new (m_storage.address()) value_type(expr.get()) ;
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
struct is_optional_related
  : boost::conditional< boost::is_base_of<optional_detail::optional_tag, BOOST_DEDUCED_TYPENAME boost::decay<U>::type>::value
                     || boost::is_same<BOOST_DEDUCED_TYPENAME boost::decay<U>::type, none_t>::value
                     || boost::is_same<BOOST_DEDUCED_TYPENAME boost::decay<U>::type, in_place_init_t>::value
                     || boost::is_same<BOOST_DEDUCED_TYPENAME boost::decay<U>::type, in_place_init_if_t>::value,
    boost::true_type, boost::false_type>::type
{};

#if !defined(BOOST_OPTIONAL_DETAIL_NO_IS_CONSTRUCTIBLE_TRAIT)

template <typename T, typename U>
struct is_convertible_to_T_or_factory
  : boost::conditional< boost::is_base_of<boost::in_place_factory_base, BOOST_DEDUCED_TYPENAME boost::decay<U>::type>::value
                     || boost::is_base_of<boost::typed_in_place_factory_base, BOOST_DEDUCED_TYPENAME boost::decay<U>::type>::value
                     || (boost::is_constructible<T, U&&>::value && !boost::is_same<T, BOOST_DEDUCED_TYPENAME boost::decay<U>::type>::value)
                      , boost::true_type, boost::false_type>::type
{};

template <typename T, typename U>
struct is_optional_constructible : boost::is_constructible<T, U>
{};

#else

template <typename, typename>
struct is_convertible_to_T_or_factory : boost::true_type
{};

template <typename T, typename U>
struct is_optional_constructible : boost::true_type
{};

#endif // is_convertible condition

template <typename T, typename U, bool = is_optional_related<U>::value>
struct is_optional_val_init_candidate
  : boost::false_type
{};

template <typename T, typename U>
struct is_optional_val_init_candidate<T, U, false>
  : boost::conditional< is_convertible_to_T_or_factory<T, U>::value
                      , boost::true_type, boost::false_type>::type
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
    BOOST_DEDUCED_TYPENAME boost::enable_if<optional_detail::is_optional_val_init_candidate<T, Expr>, optional&>::type
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

#include <boost/optional/detail/optional_relops.hpp>
#include <boost/optional/detail/optional_swap.hpp>

#endif // header guard

/* optional.hpp
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
*/