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
xsQ7ymNcvkbm9WthGFwHS8ANsBL8J6wGN8JGcFOUKZctsBV8EnZRZRxl0vcUVHX9jLSXPagcif+SxB+v3Ev87WPNvCANpqr8wYaqHGA7lU/YFw6BI+BQOEvlL9bkcyD8h5IjuE7065W8wwMS3hE4Ap5Vcgg/UWUBP1fjeqja8Rj4nSoXmAPHxcr7KhsZeET2HflM+lV7mW+b9P/oM+m/LPsQr/hMvTXxI6di3gz+AluLfTttb+T1N/S3wd/hFHgVThf72fAvn1kX8aHfCUPgWzDUb943h/lNvxAJf4ZR8t4qBoaQxlgYCQvAAjAOxsHCMAEWkfdb8bAhTPSbdYIm8p6rOLwNJsNRsAycAFPgHNHfAyvCtbAy3ACrwMdgNfgcrA73whrwOKzpN+OB2vAyrAuLqPdd8Cafib8kbAyrwpthLTF3+hNrvamXrR79yUTqT3FSrJHrLBgv+mQ4BS6EU0WO7oAPirvH4IxYmXdBZ/5+TuKr5DF/3xxj4nsCFlFpgsVEX1K1ixjTjz0NU1S7gRVF74SfvEH2I3mE/6yEvzPGzCN3weKiLwd3S3h7Yky7fQ5WF73T/wyW8Dt59D8/4c5W8irp/xUmKrmU+H6BNcW8tpjXEfOblVzDpkqeYUexd+rpoMRb2aOevpR8/QuGwAtQ2X8D49ScGsYrvZTjDzFmHJwTY+rxouQ3R+JbjbL+aeLrLs/FOOlz9fe4JL6/pPx8Ig/FYk39hMEKWm/KMwpW03pTngVgba03+S8k/RV63T/Gw2aibw6LwlZab9J3HLX9MZO+p6U8ElH7JX2v+Uz6zsKqSuZ8JpzPYFv4OeypysNnnktf+Ez/eB4OU+UJM8V+oipXeIcqV3inNjf9yps+85x/Cy4T8+XwQ6jK8CP4iDY3/eq7cItKL3xKm5v8bEfdt9HkZ4rkpwhqo+TnBSnvAzBC5R9GwpdEbg8ruRXzSspc5OwgrAsPwR7irpe46y3mSoZegUPEPl3sM+AROAYehePhMZgl9s6+uNRNJt1VJd3ufXGvSbpPSns9BcuKvoronXFYpoRT2mMcNifWyPN8kbN5sSZfC2NNPS6Bt4n+cbgY7hLzQ6J/Hd4N34D3yPNrKfwMLos1+22Ww6twBQy3dXy6X18FS8LV0Fk/P/e4Se9oj/XzurFmHFZf2kPDWFNPzWB5Ma8BG4h8N4419dMUjhJ3zjg5c7OsK3uMk98IM8/N98JMO38blhR9dyV/YaZczsFMJedQ+f0SPqzkGioZex9uhhfDzDj1W7hL9E79DN5i0nHFCq6fS5KOK7CF6t/gUNVPwOGqnwgz7cUKN88FGz4DfXAf9EPVduOh3lsZbtaDI6BuC/ATbW/GG1Hhpr4KyHuGgvCSshd9JRK6/glZJxZ5SkGVkPFGAz3ewA7eBJv4TLk19Rn5GuUz9dXcZ+SsBWyszGUc0lLGG61gf9gBzlXjT7hE3C1TfafPvH+5Be5Q40y4W40zfWY+0ge+Avv6jHwO8JlxyUB4XvQX4SCfGU8Ngb/DofAPOMxn1iszVH7gSFjENvEXFfNKYl5dzOvC/rCB1ss+2xDn++76Xbsur4WoJrL+er6AaX/fyXu5HwqY51UObAr/LfvifoSD4E9wpJILOFbJBVytnmsFjLz9XsCMC/6QfW9/yT5Gq6CpX19BMx6LgMVJVDQsbWMNm8E42AoWgj1g4YJmfJUEH4Al4aOwFNwKy8AXYTl4EJaHR2AFeEyNt+AJWAW+DqvCM7AGfEONs+C7MBW+D+vAD2FdeA7WU+mGDeF52Ah+DRvDb2FT+B1sBn+EnWCIj3kJjIddYDLsBquIeQvYA7aDPWEX2FvlF7aCt8O+cArsB2c=
*/