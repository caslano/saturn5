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