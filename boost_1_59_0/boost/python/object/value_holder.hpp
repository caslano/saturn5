#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# ifndef VALUE_HOLDER_DWA20011215_HPP
#  define VALUE_HOLDER_DWA20011215_HPP 

#  include <boost/python/object/value_holder_fwd.hpp>

#  include <boost/python/instance_holder.hpp>
#  include <boost/python/type_id.hpp>
#  include <boost/python/wrapper.hpp>

#  include <boost/python/object/inheritance_query.hpp>
#  include <boost/python/object/forward.hpp>

#  include <boost/python/detail/force_instantiate.hpp>
#  include <boost/python/detail/preprocessor.hpp>

#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/debug/line.hpp>

#  include <boost/preprocessor/repetition/enum_params.hpp>
#  include <boost/preprocessor/repetition/enum_binary_params.hpp>

#  include <boost/utility/addressof.hpp>

namespace boost { namespace python { namespace objects { 

#define BOOST_PYTHON_UNFORWARD_LOCAL(z, n, _) BOOST_PP_COMMA_IF(n) objects::do_unforward(a##n,0)

template <class Value>
struct value_holder : instance_holder
{
    typedef Value held_type;
    typedef Value value_type;

    // Forward construction to the held object
#  define BOOST_PP_ITERATION_PARAMS_1 (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/object/value_holder.hpp>, 1))
#  include BOOST_PP_ITERATE()

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
    Value m_held;
};

template <class Value, class Held>
struct value_holder_back_reference : instance_holder
{
    typedef Held held_type;
    typedef Value value_type;
    
    // Forward construction to the held object
#  define BOOST_PP_ITERATION_PARAMS_1 (4, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/object/value_holder.hpp>, 2))
#  include BOOST_PP_ITERATE()

private: // required holder implementation
    void* holds(type_info, bool null_ptr_only);

 private: // data members
    Held m_held;
};

#  undef BOOST_PYTHON_UNFORWARD_LOCAL

template <class Value>
void* value_holder<Value>::holds(type_info dst_t, bool /*null_ptr_only*/)
{
    if (void* wrapped = holds_wrapped(dst_t, boost::addressof(m_held), boost::addressof(m_held)))
        return wrapped;
    
    type_info src_t = python::type_id<Value>();
    return src_t == dst_t ? boost::addressof(m_held)
        : find_static_type(boost::addressof(m_held), src_t, dst_t);
}

template <class Value, class Held>
void* value_holder_back_reference<Value,Held>::holds(
    type_info dst_t, bool /*null_ptr_only*/)
{
    type_info src_t = python::type_id<Value>();
    Value* x = &m_held;
    
    if (dst_t == src_t)
        return x;
    else if (dst_t == python::type_id<Held>())
        return &m_held;
    else
        return find_static_type(x, src_t, dst_t);
}

}}} // namespace boost::python::objects

# endif // VALUE_HOLDER_DWA20011215_HPP

// --------------- value_holder ---------------

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == 1
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, value_holder.hpp(value_holder))
# endif

# define N BOOST_PP_ITERATION()

# if (N != 0)
    template <BOOST_PP_ENUM_PARAMS_Z(1, N, class A)>
# endif
    value_holder(
      PyObject* self BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, a))
        : m_held(
            BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_UNFORWARD_LOCAL, nil)
            )
    {
        python::detail::initialize_wrapper(self, boost::addressof(this->m_held));
    }

# undef N

// --------------- value_holder_back_reference ---------------

#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == 2
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, value_holder.hpp(value_holder_back_reference))
# endif

# define N BOOST_PP_ITERATION()

# if (N != 0)
    template <BOOST_PP_ENUM_PARAMS_Z(1, N, class A)>
# endif
    value_holder_back_reference(
        PyObject* p BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, a))
        : m_held(
            p BOOST_PP_COMMA_IF(N)
            BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_UNFORWARD_LOCAL, nil)
            )
    {
    }

# undef N

#endif // BOOST_PP_ITERATION_DEPTH()
#endif

/* value_holder.hpp
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
*/