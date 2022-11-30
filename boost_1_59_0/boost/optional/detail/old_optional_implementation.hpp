// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2014-2016 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the maintainer at:
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_DETAIL_OLD_OPTIONAL_IMPLEMENTATION_AJK_28JAN2015_HPP
#define BOOST_OPTIONAL_DETAIL_OLD_OPTIONAL_IMPLEMENTATION_AJK_28JAN2015_HPP

#include <boost/detail/reference_content.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/conditional.hpp>

namespace boost {

namespace optional_detail {


template<class T>
struct types_when_isnt_ref
{
  typedef T const& reference_const_type ;
  typedef T &      reference_type ;
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
  typedef T &&     rval_reference_type ;
  typedef T &&     reference_type_of_temporary_wrapper;
#ifdef BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES
  // GCC 4.4 has support for an early draft of rvalue references. The conforming version below
  // causes warnings about returning references to a temporary.
  static T&& move(T&& r) { return r; }
#else
  static rval_reference_type move(reference_type r) { return boost::move(r); }
#endif
#endif
  typedef T const* pointer_const_type ;
  typedef T *      pointer_type ;
  typedef T const& argument_type ;
} ;

template<class T>
struct types_when_is_ref
{
  typedef BOOST_DEDUCED_TYPENAME remove_reference<T>::type raw_type ;

  typedef raw_type&  reference_const_type ;
  typedef raw_type&  reference_type ;
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
  typedef BOOST_DEDUCED_TYPENAME remove_const<raw_type>::type&& rval_reference_type ;
  typedef raw_type&  reference_type_of_temporary_wrapper;
  static reference_type move(reference_type r) { return r; }
#endif
  typedef raw_type*  pointer_const_type ;
  typedef raw_type*  pointer_type ;
  typedef raw_type&  argument_type ;
} ;

template <class To, class From>
void prevent_binding_rvalue_ref_to_optional_lvalue_ref()
{
#ifndef BOOST_OPTIONAL_CONFIG_ALLOW_BINDING_TO_RVALUES
  BOOST_STATIC_ASSERT_MSG(
    !boost::is_lvalue_reference<To>::value || !boost::is_rvalue_reference<From>::value, 
    "binding rvalue references to optional lvalue references is disallowed");
#endif    
}

struct optional_tag {} ;

template<class T>
class optional_base : public optional_tag
{
  private :

    typedef
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    BOOST_DEDUCED_TYPENAME
#endif
    ::boost::detail::make_reference_content<T>::type internal_type ;

    typedef aligned_storage<internal_type> storage_type ;

    typedef types_when_isnt_ref<T> types_when_not_ref ;
    typedef types_when_is_ref<T>   types_when_ref   ;

    typedef optional_base<T> this_type ;

  protected :

    typedef T value_type ;

    typedef true_type  is_reference_tag ;
    typedef false_type is_not_reference_tag ;

    typedef BOOST_DEDUCED_TYPENAME is_reference<T>::type is_reference_predicate ;

  public:
    typedef BOOST_DEDUCED_TYPENAME conditional<is_reference_predicate::value,types_when_ref,types_when_not_ref>::type types ;

  protected:
    typedef BOOST_DEDUCED_TYPENAME types::reference_type       reference_type ;
    typedef BOOST_DEDUCED_TYPENAME types::reference_const_type reference_const_type ;
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    typedef BOOST_DEDUCED_TYPENAME types::rval_reference_type  rval_reference_type ;
    typedef BOOST_DEDUCED_TYPENAME types::reference_type_of_temporary_wrapper reference_type_of_temporary_wrapper ;
#endif
    typedef BOOST_DEDUCED_TYPENAME types::pointer_type         pointer_type ;
    typedef BOOST_DEDUCED_TYPENAME types::pointer_const_type   pointer_const_type ;
    typedef BOOST_DEDUCED_TYPENAME types::argument_type        argument_type ;

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
    optional_base ( argument_type val )
      :
      m_initialized(false)
    {
        construct(val);
    }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // move-construct an optional<T> initialized from an rvalue-ref to 'val'.
    // Can throw if T::T(T&&) does
    optional_base ( rval_reference_type val )
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


    // No-throw (assuming T::~T() doesn't)
    ~optional_base() { destroy() ; }

    // Assigns from another optional<T> (deep-copies the rhs value)
    void assign ( optional_base const& rhs )
    {
      if (is_initialized())
      {
        if ( rhs.is_initialized() )
             assign_value(rhs.get_impl(), is_reference_predicate() );
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
             assign_value(boost::move(rhs.get_impl()), is_reference_predicate() );
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
          assign_value(rhs.get(), is_reference_predicate() );
#else
          assign_value(static_cast<value_type>(rhs.get()), is_reference_predicate() );
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
             assign_value(static_cast<ref_type>(rhs.get()), is_reference_predicate() );
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
           assign_value(val, is_reference_predicate() );
      else construct(val);
    }
    
#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Assigns from a T (deep-moves the rhs value)
    void assign ( rval_reference_type val )
    {
      if (is_initialized())
           assign_value( boost::move(val), is_reference_predicate() );
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

    bool is_initialized() const { return m_initialized ; }

  protected :

    void construct ( argument_type val )
     {
       ::new (m_storage.address()) internal_type(val) ;
       m_initialized = true ;
     }
     
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    void construct ( rval_reference_type val )
     {
       ::new (m_storage.address()) internal_type( types::move(val) ) ;
       m_initialized = true ;
     }
#endif


#if (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES) && (!defined BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    // Constructs in-place
    // upon exception *this is always uninitialized
    template<class... Args>
    void emplace_assign ( Args&&... args )
     {
       destroy();
       ::new (m_storage.address()) internal_type( boost::forward<Args>(args)... );
       m_initialized = true ;
     }
#elif (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES)
    template<class Arg>
    void emplace_assign ( Arg&& arg )
     {
       destroy();
       ::new (m_storage.address()) internal_type( boost::forward<Arg>(arg) );
       m_initialized = true ;
     }
     
    void emplace_assign ()
     {
       destroy();
       ::new (m_storage.address()) internal_type();
       m_initialized = true ;
     }
#else
    template<class Arg>
    void emplace_assign ( const Arg& arg )
     {
       destroy();
       ::new (m_storage.address()) internal_type( arg );
       m_initialized = true ;
     }
     
    template<class Arg>
    void emplace_assign ( Arg& arg )
     {
       destroy();
       ::new (m_storage.address()) internal_type( arg );
       m_initialized = true ;
     }
     
    void emplace_assign ()
     {
       destroy();
       ::new (m_storage.address()) internal_type();
       m_initialized = true ;
     }
#endif

#ifndef BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Constructs in-place using the given factory
    template<class Expr>
    void construct ( Expr&& factory, in_place_factory_base const* )
     {
       BOOST_STATIC_ASSERT ( !is_reference_predicate::value ) ;
       boost_optional_detail::construct<value_type>(factory, m_storage.address());
       m_initialized = true ;
     }

    // Constructs in-place using the given typed factory
    template<class Expr>
    void construct ( Expr&& factory, typed_in_place_factory_base const* )
     {
       BOOST_STATIC_ASSERT ( !is_reference_predicate::value ) ;
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
       BOOST_STATIC_ASSERT ( !is_reference_predicate::value ) ;
       boost_optional_detail::construct<value_type>(factory, m_storage.address());
       m_initialized = true ;
     }

    // Constructs in-place using the given typed factory
    template<class Expr>
    void construct ( Expr const& factory, typed_in_place_factory_base const* )
     {
       BOOST_STATIC_ASSERT ( !is_reference_predicate::value ) ;
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
      new (m_storage.address()) internal_type(boost::forward<Expr>(expr)) ;
      m_initialized = true ;
    }

    // Assigns using a form any expression implicitly convertible to the single argument
    // of a T's assignment operator.
    // Converting assignments of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting assignment of T from U.
    template<class Expr>
    void assign_expr_to_initialized ( Expr&& expr, void const* )
    {
      assign_value(boost::forward<Expr>(expr), is_reference_predicate());
    }
#else
    // Constructs using any expression implicitly convertible to the single argument
    // of a one-argument T constructor.
    // Converting constructions of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting constructor of T from U.
    template<class Expr>
    void construct ( Expr const& expr, void const* )
     {
       new (m_storage.address()) internal_type(expr) ;
       m_initialized = true ;
     }

    // Assigns using a form any expression implicitly convertible to the single argument
    // of a T's assignment operator.
    // Converting assignments of optional<T> from optional<U> uses this function with
    // 'Expr' being of type 'U' and relying on a converting assignment of T from U.
    template<class Expr>
    void assign_expr_to_initialized ( Expr const& expr, void const* )
     {
       assign_value(expr, is_reference_predicate());
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
         new (m_storage.address()) internal_type(types::move(expr.get())) ;
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
         new (m_storage.address()) internal_type(expr.get()) ;
         m_initialized = true ;
       }
     }
#endif
#endif // defined BOOST_OPTIONAL_WEAK_OVERLOAD_RESOLUTION

    void assign_value ( argument_type val, is_not_reference_tag ) { get_impl() = val; }
    void assign_value ( argument_type val, is_reference_tag     ) { construct(val); }
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    void assign_value ( rval_reference_type val, is_not_reference_tag ) { get_impl() = static_cast<rval_reference_type>(val); }
    void assign_value ( rval_reference_type val, is_reference_tag     ) { construct( static_cast<rval_reference_type>(val) ); }
#endif

    void destroy()
    {
      if ( m_initialized )
        destroy_impl(is_reference_predicate()) ;
    }

    reference_const_type get_impl() const { return dereference(get_object(), is_reference_predicate() ) ; }
    reference_type       get_impl()       { return dereference(get_object(), is_reference_predicate() ) ; }

    pointer_const_type get_ptr_impl() const { return cast_ptr(get_object(), is_reference_predicate() ) ; }
    pointer_type       get_ptr_impl()       { return cast_ptr(get_object(), is_reference_predicate() ) ; }

  private :

    // internal_type can be either T or reference_content<T>
#if defined(BOOST_OPTIONAL_DETAIL_USE_ATTRIBUTE_MAY_ALIAS)
    // This workaround is supposed to silence GCC warnings about broken strict aliasing rules
    internal_type const* get_object() const
    {
        union { void const* ap_pvoid; internal_type const* as_ptype; } caster = { m_storage.address() };
        return caster.as_ptype;
    }
    internal_type *      get_object()
    {
        union { void* ap_pvoid; internal_type* as_ptype; } caster = { m_storage.address() };
        return caster.as_ptype;
    }
#else
    internal_type const* get_object() const { return static_cast<internal_type const*>(m_storage.address()); }
    internal_type *      get_object()       { return static_cast<internal_type *>     (m_storage.address()); }
#endif

    // reference_content<T> lacks an implicit conversion to T&, so the following is needed to obtain a proper reference.
    reference_const_type dereference( internal_type const* p, is_not_reference_tag ) const { return *p ; }
    reference_type       dereference( internal_type*       p, is_not_reference_tag )       { return *p ; }
    reference_const_type dereference( internal_type const* p, is_reference_tag     ) const { return p->get() ; }
    reference_type       dereference( internal_type*       p, is_reference_tag     )       { return p->get() ; }

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x581))
    void destroy_impl ( is_not_reference_tag ) { get_ptr_impl()->internal_type::~internal_type() ; m_initialized = false ; }
#else
    void destroy_impl ( is_not_reference_tag ) { get_ptr_impl()->~T() ; m_initialized = false ; }
#endif

    void destroy_impl ( is_reference_tag     ) { m_initialized = false ; }

    // If T is of reference type, trying to get a pointer to the held value must result in a compile-time error.
    // Decent compilers should disallow conversions from reference_content<T>* to T*, but just in case,
    // the following olverloads are used to filter out the case and guarantee an error in case of T being a reference.
    pointer_const_type cast_ptr( internal_type const* p, is_not_reference_tag ) const { return p ; }
    pointer_type       cast_ptr( internal_type *      p, is_not_reference_tag )       { return p ; }
    pointer_const_type cast_ptr( internal_type const* p, is_reference_tag     ) const { return &p->get() ; }
    pointer_type       cast_ptr( internal_type *      p, is_reference_tag     )       { return &p->get() ; }

    bool m_initialized ;
    storage_type m_storage ;
} ;

} // namespace optional_detail

template<class T>
class optional : public optional_detail::optional_base<T>
{
    typedef optional_detail::optional_base<T> base ;

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
    optional ( argument_type val ) : base(val) {}

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Creates an optional<T> initialized with 'move(val)'.
    // Can throw if T::T(T &&) does
    optional ( rval_reference_type val ) : base( boost::forward<T>(val) ) 
      {optional_detail::prevent_binding_rvalue_ref_to_optional_lvalue_ref<T, rval_reference_type>();}
#endif

    // Creates an optional<T> initialized with 'val' IFF cond is true, otherwise creates an uninitialized optional.
    // Can throw if T::T(T const&) does
    optional ( bool cond, argument_type val ) : base(cond,val) {}

    // NOTE: MSVC needs templated versions first

    // Creates a deep copy of another convertible optional<U>
    // Requires a valid conversion from U to T.
    // Can throw if T::T(U const&) does
    template<class U>
    explicit optional ( optional<U> const& rhs )
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
    explicit optional ( optional<U> && rhs )
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
                      BOOST_DEDUCED_TYPENAME boost::disable_if_c<
                        (boost::is_base_of<optional_detail::optional_tag, BOOST_DEDUCED_TYPENAME boost::decay<Expr>::type>::value) || 
                        boost::is_same<BOOST_DEDUCED_TYPENAME boost::decay<Expr>::type, none_t>::value, bool >::type = true 
  ) 
    : base(boost::forward<Expr>(expr),boost::addressof(expr)) 
    {optional_detail::prevent_binding_rvalue_ref_to_optional_lvalue_ref<T, Expr&&>();}

#else
    template<class Expr>
    explicit optional ( Expr const& expr ) : base(expr,boost::addressof(expr)) {}
#endif // !defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
#endif // !defined BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT

    // Creates a deep copy of another optional<T>
    // Can throw if T::T(T const&) does
    optional ( optional const& rhs ) : base( static_cast<base const&>(rhs) ) {}

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Creates a deep move of another optional<T>
    // Can throw if T::T(T&&) does
    optional ( optional && rhs )
      BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value)
      : base( boost::move(rhs) )
    {}

#endif
   // No-throw (assuming T::~T() doesn't)
    ~optional() {}

#if !defined(BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT) && !defined(BOOST_OPTIONAL_WEAK_OVERLOAD_RESOLUTION)
    // Assigns from an expression. See corresponding constructor.
    // Basic Guarantee: If the resolved T ctor throws, this is left UNINITIALIZED
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

    template<class Expr>
    BOOST_DEDUCED_TYPENAME boost::disable_if_c<
      boost::is_base_of<optional_detail::optional_tag, BOOST_DEDUCED_TYPENAME boost::decay<Expr>::type>::value || 
        boost::is_same<BOOST_DEDUCED_TYPENAME boost::decay<Expr>::type, none_t>::value,
      optional&
    >::type 
    operator= ( Expr&& expr )
      {
        optional_detail::prevent_binding_rvalue_ref_to_optional_lvalue_ref<T, Expr&&>();
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
    optional& operator= ( optional const& rhs )
      {
        this->assign( static_cast<base const&>(rhs) ) ;
        return *this ;
      }

#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // Assigns from another optional<T> (deep-moves the rhs value)
    optional& operator= ( optional && rhs ) 
      BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value && ::boost::is_nothrow_move_assignable<T>::value)
      {
        this->assign( static_cast<base &&>(rhs) ) ;
        return *this ;
      }
#endif

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
        optional_detail::prevent_binding_rvalue_ref_to_optional_lvalue_ref<T, rval_reference_type>();
        this->assign( boost::move(val) ) ;
        return *this ;
      }
#endif

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
    reference_type_of_temporary_wrapper operator *() && { return base::types::move(this->get()) ; }
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
          return base::types::move(this->get()) ;
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
          return base::types::move(get());
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


#ifndef BOOST_NO_CXX11_REF_QUALIFIERS
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
          return base::types::move(get());
        else
          return f();
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
#endif
      
    bool operator!() const BOOST_NOEXCEPT { return !this->is_initialized() ; }
    
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
} ;

} // namespace boost


#endif // header guard

/* old_optional_implementation.hpp
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
*/