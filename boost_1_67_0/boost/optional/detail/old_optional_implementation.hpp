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
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x581))
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