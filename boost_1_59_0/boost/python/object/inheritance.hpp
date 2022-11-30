// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef INHERITANCE_DWA200216_HPP
# define INHERITANCE_DWA200216_HPP

# include <boost/python/type_id.hpp>
# include <boost/shared_ptr.hpp>
# include <boost/mpl/if.hpp>
# include <boost/detail/workaround.hpp>
# include <boost/python/detail/type_traits.hpp>

namespace boost { namespace python { namespace objects {

typedef type_info class_id;
using python::type_id;

// Types used to get address and id of most derived type
typedef std::pair<void*,class_id> dynamic_id_t;
typedef dynamic_id_t (*dynamic_id_function)(void*);

BOOST_PYTHON_DECL void register_dynamic_id_aux(
    class_id static_id, dynamic_id_function get_dynamic_id);

BOOST_PYTHON_DECL void add_cast(
    class_id src_t, class_id dst_t, void* (*cast)(void*), bool is_downcast);

//
// a generator with an execute() function which, given a source type
// and a pointer to an object of that type, returns its most-derived
// /reachable/ type identifier and object pointer.
//

// first, the case where T has virtual functions
template <class T>
struct polymorphic_id_generator
{
    static dynamic_id_t execute(void* p_)
    {
        T* p = static_cast<T*>(p_);
        return std::make_pair(dynamic_cast<void*>(p), class_id(typeid(*p)));
    }
};

// now, the non-polymorphic case.
template <class T>
struct non_polymorphic_id_generator
{
    static dynamic_id_t execute(void* p_)
    {
        return std::make_pair(p_, python::type_id<T>());
    }
};

// Now the generalized selector
template <class T>
struct dynamic_id_generator
  : mpl::if_<
        boost::python::detail::is_polymorphic<T>
        , boost::python::objects::polymorphic_id_generator<T>
        , boost::python::objects::non_polymorphic_id_generator<T>
    >
{};

// Register the dynamic id function for T with the type-conversion
// system.
template <class T>
void register_dynamic_id(T* = 0)
{
    typedef typename dynamic_id_generator<T>::type generator;
    register_dynamic_id_aux(
        python::type_id<T>(), &generator::execute);
}

//
// a generator with an execute() function which, given a void*
// pointing to an object of type Source will attempt to convert it to
// an object of type Target.
//

template <class Source, class Target>
struct dynamic_cast_generator
{
    static void* execute(void* source)
    {
        return dynamic_cast<Target*>(
            static_cast<Source*>(source));
    }
        
};

template <class Source, class Target>
struct implicit_cast_generator
{
    static void* execute(void* source)
    {
        Target* result = static_cast<Source*>(source);
        return result;
    }
};

template <class Source, class Target>
struct cast_generator
  : mpl::if_<
        boost::python::detail::is_base_and_derived<Target,Source>
      , implicit_cast_generator<Source,Target>
      , dynamic_cast_generator<Source,Target>
    >
{
};

template <class Source, class Target>
inline void register_conversion(
    bool is_downcast = ::boost::is_base_and_derived<Source,Target>::value
    // These parameters shouldn't be used; they're an MSVC bug workaround
    , Source* = 0, Target* = 0)
{
    typedef typename cast_generator<Source,Target>::type generator;

    add_cast(
        python::type_id<Source>()
      , python::type_id<Target>()
      , &generator::execute
      , is_downcast
    );
}

}}} // namespace boost::python::object

#endif // INHERITANCE_DWA200216_HPP

/* inheritance.hpp
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
*/