// Copyright David Abrahams 2004.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_object_class_metadata_hpp_
#define boost_python_object_class_metadata_hpp_

#include <boost/python/converter/shared_ptr_from_python.hpp>
#include <boost/python/object/inheritance.hpp>
#include <boost/python/object/class_wrapper.hpp>
#include <boost/python/object/make_instance.hpp>
#include <boost/python/object/value_holder.hpp>
#include <boost/python/object/pointer_holder.hpp>
#include <boost/python/object/make_ptr_instance.hpp>

#include <boost/python/detail/force_instantiate.hpp>
#include <boost/python/detail/not_specified.hpp>
#include <boost/python/detail/type_traits.hpp>

#include <boost/python/has_back_reference.hpp>
#include <boost/python/bases.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/single_view.hpp>

#include <boost/mpl/assert.hpp>

#include <boost/noncopyable.hpp>
#include <boost/detail/workaround.hpp>

namespace boost { namespace python { namespace objects { 

BOOST_PYTHON_DECL
void copy_class_object(type_info const& src, type_info const& dst);

//
// Support for registering base/derived relationships
//
template <class Derived>
struct register_base_of
{
    template <class Base>
    inline void operator()(Base*) const
    {
        BOOST_MPL_ASSERT_NOT((boost::python::detail::is_same<Base,Derived>));
        
        // Register the Base class
        register_dynamic_id<Base>();

        // Register the up-cast
        register_conversion<Derived,Base>(false);

        // Register the down-cast, if appropriate.
        this->register_downcast((Base*)0, boost::python::detail::is_polymorphic<Base>());
    }

 private:
    static inline void register_downcast(void*, boost::python::detail::false_) {}
    
    template <class Base>
    static inline void register_downcast(Base*, boost::python::detail::true_)
    {
        register_conversion<Base, Derived>(true);
    }

};

//
// Preamble of register_class.  Also used for callback classes, which
// need some registration of their own.
//

template <class T, class Bases>
inline void register_shared_ptr_from_python_and_casts(T*, Bases)
{
  // Constructor performs registration
  python::detail::force_instantiate(converter::shared_ptr_from_python<T, boost::shared_ptr>());
#if !defined(BOOST_NO_CXX11_SMART_PTR)
  python::detail::force_instantiate(converter::shared_ptr_from_python<T, std::shared_ptr>());
#endif

  //
  // register all up/downcasts here.  We're using the alternate
  // interface to mpl::for_each to avoid an MSVC 6 bug.
  //
  register_dynamic_id<T>();
  mpl::for_each(register_base_of<T>(), (Bases*)0, (boost::python::detail::add_pointer<mpl::_>*)0);
}

//
// Helper for choosing the unnamed held_type argument
//
template <class T, class Prev>
struct select_held_type
  : mpl::if_<
        mpl::or_<
            python::detail::specifies_bases<T>
          , boost::python::detail::is_same<T,noncopyable>
        >
      , Prev
      , T
    >
{
};

template <
    class T // class being wrapped
  , class X1 // = detail::not_specified
  , class X2 // = detail::not_specified
  , class X3 // = detail::not_specified
>
struct class_metadata
{
    //
    // Calculate the unnamed template arguments
    //
    
    // held_type_arg -- not_specified, [a class derived from] T or a
    // smart pointer to [a class derived from] T.  Preserving
    // not_specified allows us to give class_<T,T> a back-reference.
    typedef typename select_held_type<
        X1
      , typename select_held_type<
            X2
          , typename select_held_type<
                X3
              , python::detail::not_specified
            >::type
        >::type
    >::type held_type_arg;

    // bases
    typedef typename python::detail::select_bases<
        X1
      , typename python::detail::select_bases<
            X2
          , typename python::detail::select_bases<
                X3
              , python::bases<>
            >::type
        >::type
    >::type bases;

    typedef mpl::or_<
        boost::python::detail::is_same<X1,noncopyable>
      , boost::python::detail::is_same<X2,noncopyable>
      , boost::python::detail::is_same<X3,noncopyable>
    > is_noncopyable;
    
    //
    // Holder computation.
    //
    
    // Compute the actual type that will be held in the Holder.
    typedef typename mpl::if_<
        boost::python::detail::is_same<held_type_arg,python::detail::not_specified>, T, held_type_arg
    >::type held_type;

    // Determine if the object will be held by value
    typedef mpl::bool_<boost::python::detail::is_convertible<held_type*,T*>::value> use_value_holder;
    
    // Compute the "wrapped type", that is, if held_type is a smart
    // pointer, we're talking about the pointee.
    typedef typename mpl::eval_if<
        use_value_holder
      , mpl::identity<held_type>
      , pointee<held_type>
    >::type wrapped;

    // Determine whether to use a "back-reference holder"
    typedef mpl::bool_<
        mpl::or_<
            has_back_reference<T>
          , boost::python::detail::is_same<held_type_arg,T>
          , is_base_and_derived<T,wrapped>
        >::value
    > use_back_reference;

    // Select the holder.
    typedef typename mpl::eval_if<
        use_back_reference
      , mpl::if_<
            use_value_holder
          , value_holder_back_reference<T, wrapped>
          , pointer_holder_back_reference<held_type,T>
        >
      , mpl::if_<
            use_value_holder
          , value_holder<T>
          , pointer_holder<held_type,wrapped>
        >
    >::type holder;
    
    inline static void register_() // Register the runtime metadata.
    {
        class_metadata::register_aux((T*)0);
    }

 private:
    template <class T2>
    inline static void register_aux(python::wrapper<T2>*) 
    {
        typedef typename mpl::not_<boost::python::detail::is_same<T2,wrapped> >::type use_callback;
        class_metadata::register_aux2((T2*)0, use_callback());
    }

    inline static void register_aux(void*) 
    {
        typedef typename is_base_and_derived<T,wrapped>::type use_callback;
        class_metadata::register_aux2((T*)0, use_callback());
    }

    template <class T2, class Callback>
    inline static void register_aux2(T2*, Callback) 
    {
	objects::register_shared_ptr_from_python_and_casts((T2*)0, bases());
        class_metadata::maybe_register_callback_class((T2*)0, Callback());

        class_metadata::maybe_register_class_to_python((T2*)0, is_noncopyable());
        
        class_metadata::maybe_register_pointer_to_python(
            (T2*)0, (use_value_holder*)0, (use_back_reference*)0);
    }


    //
    // Support for converting smart pointers to python
    //
    inline static void maybe_register_pointer_to_python(...) {}

#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
    inline static void maybe_register_pointer_to_python(void*,void*,mpl::true_*)
    {
        objects::copy_class_object(python::type_id<T>(), python::type_id<back_reference<T const &> >());
        objects::copy_class_object(python::type_id<T>(), python::type_id<back_reference<T &> >());
    }
#endif

    template <class T2>
    inline static void maybe_register_pointer_to_python(T2*, mpl::false_*, mpl::false_*)
    {
        python::detail::force_instantiate(
            objects::class_value_wrapper<
                held_type
              , make_ptr_instance<T2, pointer_holder<held_type, T2> >
            >()
        );
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
        // explicit qualification of type_id makes msvc6 happy
        objects::copy_class_object(python::type_id<T2>(), python::type_id<held_type>());
#endif
    }
    //
    // Support for registering to-python converters
    //
    inline static void maybe_register_class_to_python(void*, mpl::true_) {}
    

    template <class T2>
    inline static void maybe_register_class_to_python(T2*, mpl::false_)
    {
        python::detail::force_instantiate(class_cref_wrapper<T2, make_instance<T2, holder> >());
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
        // explicit qualification of type_id makes msvc6 happy
        objects::copy_class_object(python::type_id<T2>(), python::type_id<held_type>());
#endif
    }

    //
    // Support for registering callback classes
    //
    inline static void maybe_register_callback_class(void*, mpl::false_) {}

    template <class T2>
    inline static void maybe_register_callback_class(T2*, mpl::true_)
    {
	objects::register_shared_ptr_from_python_and_casts(
            (wrapped*)0, mpl::single_view<T2>());
        // explicit qualification of type_id makes msvc6 happy
        objects::copy_class_object(python::type_id<T2>(), python::type_id<wrapped>());
    }
};

}}} // namespace boost::python::object

#endif

/* class_metadata.hpp
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
*/