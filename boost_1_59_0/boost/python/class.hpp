// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef CLASS_DWA200216_HPP
# define CLASS_DWA200216_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/noncopyable.hpp>

# include <boost/python/class_fwd.hpp>
# include <boost/python/object/class.hpp>

# include <boost/python/object.hpp>
# include <boost/python/type_id.hpp>
# include <boost/python/data_members.hpp>
# include <boost/python/make_function.hpp>
# include <boost/python/signature.hpp>
# include <boost/python/init.hpp>
# include <boost/python/args_fwd.hpp>

# include <boost/python/object/class_metadata.hpp>
# include <boost/python/object/pickle_support.hpp>
# include <boost/python/object/add_to_namespace.hpp>

# include <boost/python/detail/overloads_fwd.hpp>
# include <boost/python/detail/operator_id.hpp>
# include <boost/python/detail/def_helper.hpp>
# include <boost/python/detail/force_instantiate.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/python/detail/unwrap_type_id.hpp>
# include <boost/python/detail/unwrap_wrapper.hpp>

# include <boost/mpl/size.hpp>
# include <boost/mpl/for_each.hpp>
# include <boost/mpl/bool.hpp>
# include <boost/mpl/not.hpp>

# include <boost/detail/workaround.hpp>

# if BOOST_WORKAROUND(__MWERKS__, <= 0x3004)                        \
    /* pro9 reintroduced the bug */                                 \
    || (BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))

#  define BOOST_PYTHON_NO_MEMBER_POINTER_ORDERING 1

# endif

# ifdef BOOST_PYTHON_NO_MEMBER_POINTER_ORDERING
#  include <boost/mpl/and.hpp>
# endif

namespace boost { namespace python {

template <class DerivedVisitor> class def_visitor;

enum no_init_t { no_init };

namespace detail
{
  // This function object is used with mpl::for_each to write the id
  // of the type a pointer to which is passed as its 2nd compile-time
  // argument. into the iterator pointed to by its runtime argument
  struct write_type_id
  {
      write_type_id(type_info**p) : p(p) {}

      // Here's the runtime behavior
      template <class T>
      void operator()(T*) const
      {
          *(*p)++ = type_id<T>();
      }

      type_info** p;
  };

  template <class T>
  struct is_data_member_pointer
      : mpl::and_<
            detail::is_member_pointer<T>
          , mpl::not_<detail::is_member_function_pointer<T> >
        >
  {};
  
# ifdef BOOST_PYTHON_NO_MEMBER_POINTER_ORDERING
#  define BOOST_PYTHON_DATA_MEMBER_HELPER(D) , detail::is_data_member_pointer<D>()
#  define BOOST_PYTHON_YES_DATA_MEMBER , mpl::true_
#  define BOOST_PYTHON_NO_DATA_MEMBER , mpl::false_
# elif defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#  define BOOST_PYTHON_DATA_MEMBER_HELPER(D) , 0
#  define BOOST_PYTHON_YES_DATA_MEMBER , int
#  define BOOST_PYTHON_NO_DATA_MEMBER , ...
# else 
#  define BOOST_PYTHON_DATA_MEMBER_HELPER(D)
#  define BOOST_PYTHON_YES_DATA_MEMBER
#  define BOOST_PYTHON_NO_DATA_MEMBER
# endif
  
  namespace error
  {
    //
    // A meta-assertion mechanism which prints nice error messages and
    // backtraces on lots of compilers. Usage:
    //
    //      assertion<C>::failed
    //
    // where C is an MPL metafunction class
    //
    
    template <class C> struct assertion_failed { };
    template <class C> struct assertion_ok { typedef C failed; };

    template <class C>
    struct assertion
        : mpl::if_<C, assertion_ok<C>, assertion_failed<C> >::type
    {};

    //
    // Checks for validity of arguments used to define virtual
    // functions with default implementations.
    //
    
    template <class Default>
    void not_a_derived_class_member(Default) {}
    
    template <class T, class Fn>
    struct virtual_function_default
    {
        template <class Default>
        static void
        must_be_derived_class_member(Default const&)
        {
            // https://svn.boost.org/trac/boost/ticket/5803
            //typedef typename assertion<mpl::not_<detail::is_same<Default,Fn> > >::failed test0;
# if !BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
            typedef typename assertion<detail::is_polymorphic<T> >::failed test1 BOOST_ATTRIBUTE_UNUSED;
# endif 
            typedef typename assertion<detail::is_member_function_pointer<Fn> >::failed test2 BOOST_ATTRIBUTE_UNUSED;
            not_a_derived_class_member<Default>(Fn());
        }
    };
  }
}

// This is the primary mechanism through which users will expose
// C++ classes to Python.
template <
    class W // class being wrapped
    , class X1 // = detail::not_specified
    , class X2 // = detail::not_specified
    , class X3 // = detail::not_specified
    >
class class_ : public objects::class_base
{
 public: // types
    typedef objects::class_base base;
    typedef class_<W,X1,X2,X3> self;
    typedef typename objects::class_metadata<W,X1,X2,X3> metadata;
    typedef W wrapped_type;
    
 private: // types

    // A helper class which will contain an array of id objects to be
    // passed to the base class constructor
    struct id_vector
    {
        typedef typename metadata::bases bases;
        
        id_vector()
        {
            // Stick the derived class id into the first element of the array
            ids[0] = detail::unwrap_type_id((W*)0, (W*)0);

            // Write the rest of the elements into succeeding positions.
            type_info* p = ids + 1;
            mpl::for_each(detail::write_type_id(&p), (bases*)0, (add_pointer<mpl::_>*)0);
        }

        BOOST_STATIC_CONSTANT(
            std::size_t, size = mpl::size<bases>::value + 1);
        type_info ids[size];
    };
    friend struct id_vector;

 public: // constructors
    
    // Construct with the class name, with or without docstring, and default __init__() function
    class_(char const* name, char const* doc = 0);

    // Construct with class name, no docstring, and an uncallable __init__ function
    class_(char const* name, no_init_t);

    // Construct with class name, docstring, and an uncallable __init__ function
    class_(char const* name, char const* doc, no_init_t);

    // Construct with class name and init<> function
    template <class DerivedT>
    inline class_(char const* name, init_base<DerivedT> const& i)
        : base(name, id_vector::size, id_vector().ids)
    {
        this->initialize(i);
    }

    // Construct with class name, docstring and init<> function
    template <class DerivedT>
    inline class_(char const* name, char const* doc, init_base<DerivedT> const& i)
        : base(name, id_vector::size, id_vector().ids, doc)
    {
        this->initialize(i);
    }

 public: // member functions
    
    // Generic visitation
    template <class Derived>
    self& def(def_visitor<Derived> const& visitor)
    {
        visitor.visit(*this);
        return *this;
    }

    // Wrap a member function or a non-member function which can take
    // a T, T cv&, or T cv* as its first parameter, a callable
    // python object, or a generic visitor.
    template <class F>
    self& def(char const* name, F f)
    {
        this->def_impl(
            detail::unwrap_wrapper((W*)0)
          , name, f, detail::def_helper<char const*>(0), &f);
        return *this;
    }

    template <class A1, class A2>
    self& def(char const* name, A1 a1, A2 const& a2)
    {
        this->def_maybe_overloads(name, a1, a2, &a2);
        return *this;
    }

    template <class Fn, class A1, class A2>
    self& def(char const* name, Fn fn, A1 const& a1, A2 const& a2)
    {
        //  The arguments are definitely:
        //      def(name, function, policy, doc_string)
        //      def(name, function, doc_string, policy)

        this->def_impl(
            detail::unwrap_wrapper((W*)0)
          , name, fn
          , detail::def_helper<A1,A2>(a1,a2)
          , &fn);

        return *this;
    }

    template <class Fn, class A1, class A2, class A3>
    self& def(char const* name, Fn fn, A1 const& a1, A2 const& a2, A3 const& a3)
    {
        this->def_impl(
            detail::unwrap_wrapper((W*)0)
          , name, fn
          , detail::def_helper<A1,A2,A3>(a1,a2,a3)
          , &fn);

        return *this;
    }

    //
    // Data member access
    //
    template <class D>
    self& def_readonly(char const* name, D const& d, char const* doc=0)
    {
        return this->def_readonly_impl(name, d, doc BOOST_PYTHON_DATA_MEMBER_HELPER(D));
    }

    template <class D>
    self& def_readwrite(char const* name, D const& d, char const* doc=0)
    {
        return this->def_readwrite_impl(name, d, doc BOOST_PYTHON_DATA_MEMBER_HELPER(D));
    }
    
    template <class D>
    self& def_readonly(char const* name, D& d, char const* doc=0)
    {
        return this->def_readonly_impl(name, d, doc BOOST_PYTHON_DATA_MEMBER_HELPER(D));
    }

    template <class D>
    self& def_readwrite(char const* name, D& d, char const* doc=0)
    {
        return this->def_readwrite_impl(name, d, doc BOOST_PYTHON_DATA_MEMBER_HELPER(D));
    }

    // Property creation
    template <class Get>
    self& add_property(char const* name, Get fget, char const* docstr = 0)
    {
        base::add_property(name, this->make_getter(fget), docstr);
        return *this;
    }

    template <class Get, class Set>
    self& add_property(char const* name, Get fget, Set fset, char const* docstr = 0)
    {
        base::add_property(
            name, this->make_getter(fget), this->make_setter(fset), docstr);
        return *this;
    }
        
    template <class Get>
    self& add_static_property(char const* name, Get fget)
    {
        base::add_static_property(name, object(fget));
        return *this;
    }

    template <class Get, class Set>
    self& add_static_property(char const* name, Get fget, Set fset)
    {
        base::add_static_property(name, object(fget), object(fset));
        return *this;
    }
        
    template <class U>
    self& setattr(char const* name, U const& x)
    {
        this->base::setattr(name, object(x));
        return *this;
    }

    // Pickle support
    template <typename PickleSuiteType>
    self& def_pickle(PickleSuiteType const& x)
    {
      error_messages::must_be_derived_from_pickle_suite(x);
      detail::pickle_suite_finalize<PickleSuiteType>::register_(
        *this,
        &PickleSuiteType::getinitargs,
        &PickleSuiteType::getstate,
        &PickleSuiteType::setstate,
        PickleSuiteType::getstate_manages_dict());
      return *this;
    }

    self& enable_pickling()
    {
        this->base::enable_pickling_(false);
        return *this;
    }

    self& staticmethod(char const* name)
    {
        this->make_method_static(name);
        return *this;
    }
 private: // helper functions

    // Builds a method for this class around the given [member]
    // function pointer or object, appropriately adjusting the type of
    // the first signature argument so that if f is a member of a
    // (possibly not wrapped) base class of T, an lvalue argument of
    // type T will be required.
    //
    // @group PropertyHelpers {
    template <class F>
    object make_getter(F f)
    {
        typedef typename api::is_object_operators<F>::type is_obj_or_proxy;
        
        return this->make_fn_impl(
            detail::unwrap_wrapper((W*)0)
          , f, is_obj_or_proxy(), (char*)0, detail::is_data_member_pointer<F>()
        );
    }
    
    template <class F>
    object make_setter(F f)
    {
        typedef typename api::is_object_operators<F>::type is_obj_or_proxy;
        
        return this->make_fn_impl(
            detail::unwrap_wrapper((W*)0)
          , f, is_obj_or_proxy(), (int*)0, detail::is_data_member_pointer<F>()
        );
    }
    
    template <class T, class F>
    object make_fn_impl(T*, F const& f, mpl::false_, void*, mpl::false_)
    {
        return python::make_function(f, default_call_policies(), detail::get_signature(f, (T*)0));
    }

    template <class T, class D, class B>
    object make_fn_impl(T*, D B::*pm_, mpl::false_, char*, mpl::true_)
    {
        D T::*pm = pm_;
        return python::make_getter(pm);
    }

    template <class T, class D, class B>
    object make_fn_impl(T*, D B::*pm_, mpl::false_, int*, mpl::true_)
    {
        D T::*pm = pm_;
        return python::make_setter(pm);
    }

    template <class T, class F>
    object make_fn_impl(T*, F const& x, mpl::true_, void*, mpl::false_)
    {
        return x;
    }
    // }
    
    template <class D, class B>
    self& def_readonly_impl(
        char const* name, D B::*pm_, char const* doc BOOST_PYTHON_YES_DATA_MEMBER)
    {
        return this->add_property(name, pm_, doc);
    }

    template <class D, class B>
    self& def_readwrite_impl(
        char const* name, D B::*pm_, char const* doc BOOST_PYTHON_YES_DATA_MEMBER)
    {
        return this->add_property(name, pm_, pm_, doc);
    }

    template <class D>
    self& def_readonly_impl(
        char const* name, D& d, char const* BOOST_PYTHON_NO_DATA_MEMBER)
    {
        return this->add_static_property(name, python::make_getter(d));
    }

    template <class D>
    self& def_readwrite_impl(
        char const* name, D& d, char const* BOOST_PYTHON_NO_DATA_MEMBER)
    {
        return this->add_static_property(name, python::make_getter(d), python::make_setter(d));
    }

    template <class DefVisitor>
    inline void initialize(DefVisitor const& i)
    {
        metadata::register_(); // set up runtime metadata/conversions
        
        typedef typename metadata::holder holder;
        this->set_instance_size( objects::additional_instance_size<holder>::value );
        
        this->def(i);
    }
    
    inline void initialize(no_init_t)
    {
        metadata::register_(); // set up runtime metadata/conversions
        this->def_no_init();
    }
    
    //
    // These two overloads discriminate between def() as applied to a
    // generic visitor and everything else.
    //
    // @group def_impl {
    template <class T, class Helper, class LeafVisitor, class Visitor>
    inline void def_impl(
        T*
      , char const* name
      , LeafVisitor
      , Helper const& helper
      , def_visitor<Visitor> const* v
    )
    {
        v->visit(*this, name,  helper);
    }

    template <class T, class Fn, class Helper>
    inline void def_impl(
        T*
      , char const* name
      , Fn fn
      , Helper const& helper
      , ...
    )
    {
        objects::add_to_namespace(
            *this
          , name
          , make_function(
                fn
              , helper.policies()
              , helper.keywords()
              , detail::get_signature(fn, (T*)0)
            )
          , helper.doc()
        );

        this->def_default(name, fn, helper, mpl::bool_<Helper::has_default_implementation>());
    }
    // }

    //
    // These two overloads handle the definition of default
    // implementation overloads for virtual functions. The second one
    // handles the case where no default implementation was specified.
    //
    // @group def_default {
    template <class Fn, class Helper>
    inline void def_default(
        char const* name
        , Fn
        , Helper const& helper
        , mpl::bool_<true>)
    {
        detail::error::virtual_function_default<W,Fn>::must_be_derived_class_member(
            helper.default_implementation());
            
        objects::add_to_namespace(
            *this, name,
            make_function(
                helper.default_implementation(), helper.policies(), helper.keywords())
            );
    }
    
    template <class Fn, class Helper>
    inline void def_default(char const*, Fn, Helper const&, mpl::bool_<false>)
    { }
    // }
    
    //
    // These two overloads discriminate between def() as applied to
    // regular functions and def() as applied to the result of
    // BOOST_PYTHON_FUNCTION_OVERLOADS(). The final argument is used to
    // discriminate.
    //
    // @group def_maybe_overloads {
    template <class OverloadsT, class SigT>
    void def_maybe_overloads(
        char const* name
        , SigT sig
        , OverloadsT const& overloads
        , detail::overloads_base const*)

    {
        //  convert sig to a type_list (see detail::get_signature in signature.hpp)
        //  before calling detail::define_with_defaults.
        detail::define_with_defaults(
            name, overloads, *this, detail::get_signature(sig));
    }

    template <class Fn, class A1>
    void def_maybe_overloads(
        char const* name
        , Fn fn
        , A1 const& a1
        , ...)
    {
        this->def_impl(
            detail::unwrap_wrapper((W*)0)
          , name
          , fn
          , detail::def_helper<A1>(a1)
          , &fn
        );

    }
    // }
};


//
// implementations
//

template <class W, class X1, class X2, class X3>
inline class_<W,X1,X2,X3>::class_(char const* name, char const* doc)
    : base(name, id_vector::size, id_vector().ids, doc)
{
    this->initialize(init<>());
//  select_holder::assert_default_constructible();
}

template <class W, class X1, class X2, class X3>
inline class_<W,X1,X2,X3>::class_(char const* name, no_init_t)
    : base(name, id_vector::size, id_vector().ids)
{
    this->initialize(no_init);
}

template <class W, class X1, class X2, class X3>
inline class_<W,X1,X2,X3>::class_(char const* name, char const* doc, no_init_t)
    : base(name, id_vector::size, id_vector().ids, doc)
{
    this->initialize(no_init);
}

}} // namespace boost::python

# undef BOOST_PYTHON_DATA_MEMBER_HELPER
# undef BOOST_PYTHON_YES_DATA_MEMBER
# undef BOOST_PYTHON_NO_DATA_MEMBER
# undef BOOST_PYTHON_NO_MEMBER_POINTER_ORDERING

#endif // CLASS_DWA200216_HPP

/* class.hpp
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
*/