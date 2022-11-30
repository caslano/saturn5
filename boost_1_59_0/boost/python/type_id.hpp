// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef TYPE_ID_DWA2002517_HPP
# define TYPE_ID_DWA2002517_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/detail/msvc_typeinfo.hpp>
# include <boost/operators.hpp>
# include <typeinfo>
# include <cstring>
# include <ostream>
# include <boost/static_assert.hpp>
# include <boost/detail/workaround.hpp>
# include <boost/python/detail/type_traits.hpp>

#  ifndef BOOST_PYTHON_HAVE_GCC_CP_DEMANGLE
#   if defined(__GNUC__)                                                \
    && !defined(__EDG_VERSION__)
#    define BOOST_PYTHON_HAVE_GCC_CP_DEMANGLE
#   endif
#  endif

namespace boost { namespace python { 

// for this compiler at least, cross-shared-library type_info
// comparisons don't work, so use typeid(x).name() instead. It's not
// yet clear what the best default strategy is.
# if defined(__GNUC__) \
 || defined(_AIX) \
 || (   defined(__sgi) && defined(__host_mips)) \
 || (defined(__hpux) && defined(__HP_aCC)) \
 || (defined(linux) && defined(__INTEL_COMPILER) && defined(__ICC))
#  define BOOST_PYTHON_TYPE_ID_NAME
# endif 

#ifdef BOOST_PYTHON_HAVE_GCC_CP_DEMANGLE
// Runtime detection of broken cxxabi::__cxa_demangle versions,
// to avoid #ifdef clutter.
bool cxxabi_cxa_demangle_is_broken();
#define BOOST_PYTHON_HAVE_CXXABI_CXA_DEMANGLE_IS_BROKEN
#endif

// type ids which represent the same information as std::type_info
// (i.e. the top-level reference and cv-qualifiers are stripped), but
// which works across shared libraries.
struct type_info : private totally_ordered<type_info>
{
    inline type_info(std::type_info const& = typeid(void));
    
    inline bool operator<(type_info const& rhs) const;
    inline bool operator==(type_info const& rhs) const;

    char const* name() const;
    friend BOOST_PYTHON_DECL std::ostream& operator<<(
        std::ostream&, type_info const&);
    
 private: // data members
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    typedef char const* base_id_t;
#  else
    typedef std::type_info const* base_id_t;
#  endif
    
    base_id_t m_base_type;
};


// This macro is obsolete. Port away and remove.
# define BOOST_PYTHON_EXPLICIT_TT_DEF(T)

template <class T>
inline type_info type_id()
{
    return type_info(
#  if !defined(_MSC_VER)                                       \
      || !BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 700)
        typeid(T)
#  else // strip the decoration which Intel mistakenly leaves in
        python::detail::msvc_typeid((boost::type<T>*)0)
#  endif 
        );
}

#  if (defined(__EDG_VERSION__) && __EDG_VERSION__ < 245) \
   || (defined(__sgi) && defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 744)
// Older EDG-based compilers seems to mistakenly distinguish "int" from
// "signed int", etc., but only in typeid() expressions. However
// though int == signed int, the "signed" decoration is propagated
// down into template instantiations. Explicit specialization stops
// that from taking hold.

#   define BOOST_PYTHON_SIGNED_INTEGRAL_TYPE_ID(T)              \
template <>                                                     \
inline type_info type_id<T>()                                   \
{                                                               \
    return type_info(typeid(T));                                \
}

BOOST_PYTHON_SIGNED_INTEGRAL_TYPE_ID(short)
BOOST_PYTHON_SIGNED_INTEGRAL_TYPE_ID(int)
BOOST_PYTHON_SIGNED_INTEGRAL_TYPE_ID(long)
// using Python's macro instead of Boost's - we don't seem to get the
// config right all the time.
#   ifdef HAVE_LONG_LONG
BOOST_PYTHON_SIGNED_INTEGRAL_TYPE_ID(long long)
#   endif
#   undef BOOST_PYTHON_SIGNED_INTEGRAL_TYPE_ID
#  endif

//
inline type_info::type_info(std::type_info const& id)
    : m_base_type(
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
        id.name()
#  else
        &id
#  endif
        )
{
}

inline bool type_info::operator<(type_info const& rhs) const
{
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    return std::strcmp(m_base_type, rhs.m_base_type) < 0;
#  else
    return m_base_type->before(*rhs.m_base_type);
#  endif 
}

inline bool type_info::operator==(type_info const& rhs) const
{
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    return !std::strcmp(m_base_type, rhs.m_base_type);
#  else
    return *m_base_type == *rhs.m_base_type;
#  endif 
}

#  ifdef BOOST_PYTHON_HAVE_GCC_CP_DEMANGLE
namespace detail
{
  BOOST_PYTHON_DECL char const* gcc_demangle(char const*);
}
#  endif
    
inline char const* type_info::name() const
{
    char const* raw_name
        = m_base_type
#  ifndef BOOST_PYTHON_TYPE_ID_NAME
          ->name()
#  endif
        ;
    
#  ifdef BOOST_PYTHON_HAVE_GCC_CP_DEMANGLE
    return detail::gcc_demangle(raw_name);
#  else
    return raw_name;
#  endif 
}


BOOST_PYTHON_DECL std::ostream& operator<<(std::ostream&, type_info const&);

template<>
inline type_info type_id<void>()
{
    return type_info (typeid (void *));
}
#   ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template<>
inline type_info type_id<const volatile void>()
{
    return type_info (typeid (void *));
}
#  endif

}} // namespace boost::python

#endif // TYPE_ID_DWA2002517_HPP

/* type_id.hpp
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
*/