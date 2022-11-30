// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef UNWIND_TYPE_DWA200222_HPP
# define UNWIND_TYPE_DWA200222_HPP

# include <boost/python/detail/cv_category.hpp>
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/type_traits.hpp>

namespace boost { namespace python { namespace detail {

#if (!defined(_MSC_VER) || _MSC_VER >= 1915)
// If forward declared, msvc6.5 does not recognize them as inline.
// However, as of msvc14.15 (_MSC_VER 1915/Visual Studio 15.8.0) name lookup is now consistent with other compilers.
// forward declaration, required (at least) by Tru64 cxx V6.5-042 and msvc14.15
template <class Generator, class U>
inline typename Generator::result_type
unwind_type(U const& p, Generator* = 0);

// forward declaration, required (at least) by Tru64 cxx V6.5-042 and msvc14.15
template <class Generator, class U>
inline typename Generator::result_type
unwind_type(boost::type<U>*p = 0, Generator* = 0);
#endif

template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U* p, cv_unqualified, Generator* = 0)
{
    return Generator::execute(p);
}

template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U const* p, const_, Generator* = 0)
{
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}

template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U volatile* p, volatile_, Generator* = 0)
{
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}

template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U const volatile* p, const_volatile_, Generator* = 0)
{
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}

template <class Generator, class U>
inline typename Generator::result_type
unwind_ptr_type(U* p, Generator* = 0)
{
    typedef typename cv_category<U>::type tag;
    return unwind_type_cv<Generator>(p, tag());
}

template <bool is_ptr>
struct unwind_helper
{
    template <class Generator, class U>
    static typename Generator::result_type
    execute(U p, Generator* = 0)
    {
        return unwind_ptr_type(p, (Generator*)0);
    }
};

template <>
struct unwind_helper<false>
{
    template <class Generator, class U>
    static typename Generator::result_type
    execute(U& p, Generator* = 0)
    {
        return unwind_ptr_type(&p, (Generator*)0);
    }
};

template <class Generator, class U>
inline typename Generator::result_type
#if (!defined(_MSC_VER) || _MSC_VER >= 1915)
unwind_type(U const& p, Generator*)
#else
unwind_type(U const& p, Generator* = 0)
#endif
{
    return unwind_helper<is_pointer<U>::value>::execute(p, (Generator*)0);
}

enum { direct_ = 0, pointer_ = 1, reference_ = 2, reference_to_pointer_ = 3 };
template <int indirection> struct unwind_helper2;

template <>
struct unwind_helper2<direct_>
{
    template <class Generator, class U>
    static typename Generator::result_type
    execute(U(*)(), Generator* = 0)
    {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }
};

template <>
struct unwind_helper2<pointer_>
{
    template <class Generator, class U>
    static typename Generator::result_type
    execute(U*(*)(), Generator* = 0)
    {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }
};

template <>
struct unwind_helper2<reference_>
{
    template <class Generator, class U>
    static typename Generator::result_type
    execute(U&(*)(), Generator* = 0)
    {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }
};

template <>
struct unwind_helper2<reference_to_pointer_>
{
    template <class Generator, class U>
    static typename Generator::result_type
    execute(U&(*)(), Generator* = 0)
    {
        return unwind_ptr_type(U(0), (Generator*)0);
    }
};

// Call this one with both template parameters explicitly specified
// and no function arguments:
//
//      return unwind_type<my_generator,T>();
//
// Doesn't work if T is an array type; we could handle that case, but
// why bother?
template <class Generator, class U>
inline typename Generator::result_type
#if (!defined(_MSC_VER) || _MSC_VER >= 1915)
unwind_type(boost::type<U>*, Generator*)
#else
unwind_type(boost::type<U>*p =0, Generator* =0)
#endif
{
    BOOST_STATIC_CONSTANT(int, indirection
        = (is_pointer<U>::value ? pointer_ : 0)
                             + (indirect_traits::is_reference_to_pointer<U>::value
                             ? reference_to_pointer_
                             : is_lvalue_reference<U>::value
                             ? reference_
                             : 0));

    return unwind_helper2<indirection>::execute((U(*)())0,(Generator*)0);
}

}}} // namespace boost::python::detail

#endif // UNWIND_TYPE_DWA200222_HPP

/* unwind_type.hpp
++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
*/