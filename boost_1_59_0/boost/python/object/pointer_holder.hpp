#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# ifndef POINTER_HOLDER_DWA20011215_HPP
#  define POINTER_HOLDER_DWA20011215_HPP 

# include <boost/get_pointer.hpp>
#  include <boost/type.hpp>

#  include <boost/python/instance_holder.hpp>
#  include <boost/python/object/inheritance_query.hpp>
#  include <boost/python/object/forward.hpp>

#  include <boost/python/pointee.hpp>
#  include <boost/python/type_id.hpp>

#  include <boost/python/detail/wrapper_base.hpp>
#  include <boost/python/detail/force_instantiate.hpp>
#  include <boost/python/detail/preprocessor.hpp>
# include <boost/python/detail/type_traits.hpp>


#  include <boost/mpl/if.hpp>
#  include <boost/mpl/apply.hpp>

#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/repetition/enum_binary_params.hpp>

#  include <boost/detail/workaround.hpp>

namespace boost { namespace python {

template <class T> class wrapper;

}}


namespace boost { namespace python { namespace objects {

#define BOOST_PYTHON_UNFORWARD_LOCAL(z, n, _) BOOST_PP_COMMA_IF(n) objects::do_unforward(a##n,0)

template <class Pointer, class Value>
struct pointer_holder : instance_holder
{
    typedef Value value_type;
    
    pointer_holder(Pointer);

    // Forward construction to the held object

#  define BOOST_PP_ITERATION_PARAMS_1 (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/object/pointer_holder.hpp>, 1))
#  include BOOST_PP_ITERATE()

 private: // types
    
 private: // required holder implementation
    void* holds(type_info, bool null_ptr_only);
    
    template <class T>
    inline void* holds_wrapped(type_info dst_t, wrapper<T>*,T* p)
    {
        return python::type_id<T>() == dst_t ? p : 0;
    }
    
    inline void* holds_wrapped(type_info, ...)
    {
        return 0;
    }

 private: // data members
    Pointer m_p;
};

template <class Pointer, class Value>
struct pointer_holder_back_reference : instance_holder
{
 private:
    typedef typename python::pointee<Pointer>::type held_type;
 public:
    typedef Value value_type;

    // Not sure about this one -- can it work? The source object
    // undoubtedly does not carry the correct back reference pointer.
    pointer_holder_back_reference(Pointer);

    // Forward construction to the held object
#  define BOOST_PP_ITERATION_PARAMS_1 (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/object/pointer_holder.hpp>, 2))
#  include BOOST_PP_ITERATE()

 private: // required holder implementation
    void* holds(type_info, bool null_ptr_only);

 private: // data members
    Pointer m_p;
};

#  undef BOOST_PYTHON_UNFORWARD_LOCAL

template <class Pointer, class Value>
inline pointer_holder<Pointer,Value>::pointer_holder(Pointer p)
#if defined(BOOST_NO_CXX11_SMART_PTR)
    : m_p(p)
#else
    : m_p(std::move(p))
#endif
{
}

template <class Pointer, class Value>
inline pointer_holder_back_reference<Pointer,Value>::pointer_holder_back_reference(Pointer p)
#if defined(BOOST_NO_CXX11_SMART_PTR)
    : m_p(p)
#else
    : m_p(std::move(p))
#endif
{
}

template <class Pointer, class Value>
void* pointer_holder<Pointer, Value>::holds(type_info dst_t, bool null_ptr_only)
{
    typedef typename boost::python::detail::remove_const< Value >::type non_const_value;

    if (dst_t == python::type_id<Pointer>()
        && !(null_ptr_only && get_pointer(this->m_p))
    )
        return &this->m_p;

    Value* p0
#  if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
        = static_cast<Value*>( get_pointer(this->m_p) )
#  else 
        = get_pointer(this->m_p)
#  endif
        ;
    non_const_value* p = const_cast<non_const_value*>( p0 );

    if (p == 0)
        return 0;
    
    if (void* wrapped = holds_wrapped(dst_t, p, p))
        return wrapped;
    
    type_info src_t = python::type_id<non_const_value>();
    return src_t == dst_t ? p : find_dynamic_type(p, src_t, dst_t);
}

template <class Pointer, class Value>
void* pointer_holder_back_reference<Pointer, Value>::holds(type_info dst_t, bool null_ptr_only)
{
    if (dst_t == python::type_id<Pointer>()
        && !(null_ptr_only && get_pointer(this->m_p))
    )
        return &this->m_p;

    if (!get_pointer(this->m_p))
        return 0;
    
    Value* p = get_pointer(m_p);
    
    if (dst_t == python::type_id<held_type>())
        return p;

    type_info src_t = python::type_id<Value>();
    return src_t == dst_t ? p : find_dynamic_type(p, src_t, dst_t);
}

}}} // namespace boost::python::objects

# endif // POINTER_HOLDER_DWA20011215_HPP

/* --------------- pointer_holder --------------- */
// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == 1
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, pointer_holder.hpp)
# endif

# define N BOOST_PP_ITERATION()

# if (N != 0)
    template< BOOST_PP_ENUM_PARAMS_Z(1, N, class A) >
# endif
    pointer_holder(PyObject* self BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, a))
        : m_p(new Value(
                BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_UNFORWARD_LOCAL, nil)
            ))
    {
        python::detail::initialize_wrapper(self, get_pointer(this->m_p));
    }

# undef N

/* --------------- pointer_holder_back_reference --------------- */
#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == 2
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, pointer_holder.hpp(pointer_holder_back_reference))
# endif 

# define N BOOST_PP_ITERATION()

# if (N != 0)
    template < BOOST_PP_ENUM_PARAMS_Z(1, N, class A) >
# endif
    pointer_holder_back_reference(
        PyObject* p BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, a))
        : m_p(new held_type(
                    p BOOST_PP_COMMA_IF(N) BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_UNFORWARD_LOCAL, nil)
            ))
    {}

# undef N

#endif // BOOST_PP_ITERATION_DEPTH()
#endif

/* pointer_holder.hpp
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
*/