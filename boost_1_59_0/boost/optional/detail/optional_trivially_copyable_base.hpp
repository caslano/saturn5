// Copyright (C) 2017 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

// trivilally-copyable version of the storage

template<class T>
class tc_optional_base : public optional_tag
{
  private :

    typedef tc_optional_base<T> this_type ;

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

    tc_optional_base()
      :
      m_initialized(false) {}

    tc_optional_base ( none_t )
      :
      m_initialized(false) {}

    tc_optional_base ( init_value_tag, argument_type val )
      :
      m_initialized(true), m_storage(val) {}

    tc_optional_base ( bool cond, argument_type val )
      :
      m_initialized(cond), m_storage(val) {}

    // tc_optional_base ( tc_optional_base const& ) = default;


#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES

    template<class Expr, class PtrExpr>
    explicit tc_optional_base ( Expr&& expr, PtrExpr const* tag )
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
    explicit tc_optional_base ( Expr const& expr, Expr const* tag )
      :
      m_initialized(false)
    {
      construct(expr,tag);
    }

#endif

    // tc_optional_base& operator= ( tc_optional_base const& ) = default;
    // ~tc_optional_base() = default;

    // Assigns from another optional<T> (deep-copies the rhs value)
    void assign ( tc_optional_base const& rhs )
    {
      *this = rhs;
    }

    // Assigns from another _convertible_ optional<U> (deep-copies the rhs value)
    template<class U>
    void assign ( optional<U> const& rhs )
    {
      if ( rhs.is_initialized() )
#ifndef BOOST_OPTIONAL_CONFIG_RESTORE_ASSIGNMENT_OF_NONCONVERTIBLE_TYPES
        m_storage = rhs.get();
#else
        m_storage = static_cast<value_type>(rhs.get());
#endif

      m_initialized = rhs.is_initialized();
    }

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    // move-assigns from another _convertible_ optional<U> (deep-moves from the rhs value)
    template<class U>
    void assign ( optional<U>&& rhs )
    {
      typedef BOOST_DEDUCED_TYPENAME optional<U>::rval_reference_type ref_type;
      if ( rhs.is_initialized() )
        m_storage = static_cast<ref_type>(rhs.get());
      m_initialized = rhs.is_initialized();
    }
#endif

    void assign ( argument_type val )
    {
      construct(val);
    }

    void assign ( none_t ) { destroy(); }

#ifndef BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    template<class Expr, class ExprPtr>
    void assign_expr ( Expr&& expr, ExprPtr const* tag )
    {
       construct(boost::forward<Expr>(expr),tag);
    }
#else
    template<class Expr>
    void assign_expr ( Expr const& expr, Expr const* tag )
    {
      construct(expr,tag);
    }
#endif

#endif

  public :

    // Destroys the current value, if any, leaving this UNINITIALIZED
    // No-throw (assuming T::~T() doesn't)
    void reset() BOOST_NOEXCEPT { destroy(); }

    // **DEPPRECATED** Replaces the current value -if any- with 'val'
    void reset ( argument_type val ) BOOST_NOEXCEPT { assign(val); }

    // Returns a pointer to the value if this is initialized, otherwise,
    // returns NULL.
    // No-throw
    pointer_const_type get_ptr() const { return m_initialized ? get_ptr_impl() : 0 ; }
    pointer_type       get_ptr()       { return m_initialized ? get_ptr_impl() : 0 ; }

    bool is_initialized() const { return m_initialized ; }

  protected :

    void construct ( argument_type val )
     {
       m_storage = val ;
       m_initialized = true ;
     }


#if (!defined BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES) && (!defined BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    // Constructs in-place
    // upon exception *this is always uninitialized
    template<class... Args>
    void construct ( in_place_init_t, Args&&... args )
    {
      m_storage = value_type( boost::forward<Args>(args)... ) ;
      m_initialized = true ;
    }

    template<class... Args>
    void emplace_assign ( Args&&... args )
    {
      construct(in_place_init, boost::forward<Args>(args)...);
    }

    template<class... Args>
    explicit tc_optional_base ( in_place_init_t, Args&&... args )
      :
      m_initialized(false)
    {
      construct(in_place_init, boost::forward<Args>(args)...);
    }

    template<class... Args>
    explicit tc_optional_base ( in_place_init_if_t, bool cond, Args&&... args )
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
       m_storage = value_type( boost::forward<Arg>(arg) );
       m_initialized = true ;
     }

    void construct ( in_place_init_t )
     {
       m_storage = value_type();
       m_initialized = true ;
     }

    template<class Arg>
    void emplace_assign ( Arg&& arg )
     {
       construct(in_place_init, boost::forward<Arg>(arg)) ;
     }

    void emplace_assign ()
     {
       construct(in_place_init) ;
     }

    template<class Arg>
    explicit tc_optional_base ( in_place_init_t, Arg&& arg )
      :
      m_initialized(false)
    {
      construct(in_place_init, boost::forward<Arg>(arg));
    }

    explicit tc_optional_base ( in_place_init_t )
      :
      m_initialized(false), m_storage() {}

    template<class Arg>
    explicit tc_optional_base ( in_place_init_if_t, bool cond, Arg&& arg )
      :
      m_initialized(false)
    {
      if ( cond )
        construct(in_place_init, boost::forward<Arg>(arg));
    }

    explicit tc_optional_base ( in_place_init_if_t, bool cond )
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
       m_storage = value_type( arg );
       m_initialized = true ;
     }

    template<class Arg>
    void construct ( in_place_init_t, Arg& arg )
     {
       m_storage = value_type( arg );
       m_initialized = true ;
     }

    void construct ( in_place_init_t )
     {
       m_storage = value_type();
       m_initialized = true ;
     }

    template<class Arg>
    void emplace_assign ( const Arg& arg )
    {
      construct(in_place_init, arg);
    }

    template<class Arg>
    void emplace_assign ( Arg& arg )
    {
      construct(in_place_init, arg);
    }

    void emplace_assign ()
    {
      construct(in_place_init);
    }

    template<class Arg>
    explicit tc_optional_base ( in_place_init_t, const Arg& arg )
      : m_initialized(false)
    {
      construct(in_place_init, arg);
    }

    template<class Arg>
    explicit tc_optional_base ( in_place_init_t, Arg& arg )
      : m_initialized(false)
    {
      construct(in_place_init, arg);
    }

    explicit tc_optional_base ( in_place_init_t )
      : m_initialized(false)
    {
      construct(in_place_init);
    }

    template<class Arg>
    explicit tc_optional_base ( in_place_init_if_t, bool cond, const Arg& arg )
      : m_initialized(false)
    {
      if ( cond )
        construct(in_place_init, arg);
    }

    template<class Arg>
    explicit tc_optional_base ( in_place_init_if_t, bool cond, Arg& arg )
      : m_initialized(false)
    {
      if ( cond )
        construct(in_place_init, arg);
    }

    explicit tc_optional_base ( in_place_init_if_t, bool cond )
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
       boost_optional_detail::construct<value_type>(factory, boost::addressof(m_storage));
       m_initialized = true ;
     }

    // Constructs in-place using the given typed factory
    template<class Expr>
    void construct ( Expr&& factory, typed_in_place_factory_base const* )
     {
       factory.apply(boost::addressof(m_storage)) ;
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
       boost_optional_detail::construct<value_type>(factory, boost::addressof(m_storage));
       m_initialized = true ;
     }

    // Constructs in-place using the given typed factory
    template<class Expr>
    void construct ( Expr const& factory, typed_in_place_factory_base const* )
     {
       factory.apply(boost::addressof(m_storage)) ;
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
      m_storage = value_type(boost::forward<Expr>(expr)) ;
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
       m_storage = value_type(expr) ;
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
    // Notice that 'Expr' will be optional<T> or optional<U> (but not tc_optional_base<..>)
    template<class Expr>
    void construct ( Expr&& expr, optional_tag const* )
     {
       if ( expr.is_initialized() )
       {
         // An exception can be thrown here.
         // It it happens, THIS will be left uninitialized.
         m_storage = value_type(boost::move(expr.get())) ;
         m_initialized = true ;
       }
     }
#else
    // Notice that 'Expr' will be optional<T> or optional<U> (but not tc_optional_base<..>)
    template<class Expr>
    void construct ( Expr const& expr, optional_tag const* )
     {
       if ( expr.is_initialized() )
       {
         // An exception can be thrown here.
         // It it happens, THIS will be left uninitialized.
         m_storage = value_type(expr.get()) ;
         m_initialized = true ;
       }
     }
#endif
#endif // defined BOOST_OPTIONAL_WEAK_OVERLOAD_RESOLUTION

    void assign_value ( argument_type val ) { m_storage = val; }
#ifndef  BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
    void assign_value ( rval_reference_type val ) { m_storage = static_cast<rval_reference_type>(val); }
#endif

    void destroy()
    {
      m_initialized = false;
    }

    reference_const_type get_impl() const { return m_storage ; }
    reference_type       get_impl()       { return m_storage ; }

    pointer_const_type get_ptr_impl() const { return boost::addressof(m_storage); }
    pointer_type       get_ptr_impl()       { return boost::addressof(m_storage); }

  private :

    bool m_initialized ;
    T    m_storage ;
} ;

/* optional_trivially_copyable_base.hpp
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
*/