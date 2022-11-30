///////////////////////////////////////////////////////////////////////////////
//
// Copyright David Abrahams 2002, Joel de Guzman, 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_PP_IS_ITERATING)

# ifndef SIGNATURE_JDG20020813_HPP
#  define SIGNATURE_JDG20020813_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/mpl/if.hpp>

#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/python/detail/type_traits.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/enum.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/empty.hpp>
#  include <boost/preprocessor/arithmetic/sub.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/python/detail/type_list.hpp>

#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/arithmetic/sub.hpp>
#  include <boost/preprocessor/arithmetic/inc.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>

# define BOOST_PYTHON_LIST_INC(n)        \
   BOOST_PP_CAT(mpl::vector, BOOST_PP_INC(n))

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace python { namespace detail {

// A metafunction returning C1 if C1 is derived from C2, and C2
// otherwise
template <class C1, class C2>
struct most_derived
{
    typedef typename mpl::if_<
        detail::is_convertible<C1*,C2*>
      , C1
      , C2
    >::type type;
};

//  The following macros generate expansions for::
//
//      template <class RT, class T0... class TN>
//      inline mpl::vector<RT, T0...TN>
//      get_signature(RT(BOOST_PYTHON_FN_CC *)(T0...TN), void* = 0)
//      {
//          return mpl::list<RT, T0...TN>();
//      }
//
//    where BOOST_PYTHON_FN_CC is a calling convention keyword, can be
//
//        empty, for default calling convention
//        __cdecl (if BOOST_PYTHON_ENABLE_CDECL is defined)
//        __stdcall (if BOOST_PYTHON_ENABLE_STDCALL is defined)
//        __fastcall (if BOOST_PYTHON_ENABLE_FASTCALL is defined)
//
//   And, for an appropriate assortment of cv-qualifications::
//
//      template <class RT, class ClassT, class T0... class TN>
//      inline mpl::vector<RT, ClassT&, T0...TN>
//      get_signature(RT(BOOST_PYTHON_FN_CC ClassT::*)(T0...TN) cv))
//      {
//          return mpl::list<RT, ClassT&, T0...TN>();
//      }
//
//      template <class Target, class RT, class ClassT, class T0... class TN>
//      inline mpl::vector<
//          RT
//        , typename most_derived<Target, ClassT>::type&
//        , T0...TN
//      >
//      get_signature(RT(BOOST_PYTHON_FN_CC ClassT::*)(T0...TN) cv), Target*)
//      {
//          return mpl::list<RT, ClassT&, T0...TN>();
//      }
//
//  There are two forms for invoking get_signature::
//
//      get_signature(f)
//
//  and ::
//
//      get_signature(f,(Target*)0)
//
//  These functions extract the return type, class (for member
//  functions) and arguments of the input signature and stuff them in
//  an mpl type sequence (the calling convention is dropped).
//  Note that cv-qualification is dropped from
//  the "hidden this" argument of member functions; that is a
//  necessary sacrifice to ensure that an lvalue from_python converter
//  is used.  A pointer is not used so that None will be rejected for
//  overload resolution.
//
//  The second form of get_signature essentially downcasts the "hidden
//  this" argument of member functions to Target, because the function
//  may actually be a member of a base class which is not wrapped, and
//  in that case conversion from python would fail.
//
// @group {

// 'default' calling convention

#  define BOOST_PYTHON_FN_CC

#  define BOOST_PP_ITERATION_PARAMS_1                                   \
    (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/signature.hpp>))

#  include BOOST_PP_ITERATE()

#  undef BOOST_PYTHON_FN_CC

// __cdecl calling convention

#  if defined(BOOST_PYTHON_ENABLE_CDECL)

#   define BOOST_PYTHON_FN_CC __cdecl
#   define BOOST_PYTHON_FN_CC_IS_CDECL

#   define BOOST_PP_ITERATION_PARAMS_1                                   \
     (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/signature.hpp>))

#   include BOOST_PP_ITERATE()

#   undef BOOST_PYTHON_FN_CC
#   undef BOOST_PYTHON_FN_CC_IS_CDECL

#  endif // defined(BOOST_PYTHON_ENABLE_CDECL)

// __stdcall calling convention

#  if defined(BOOST_PYTHON_ENABLE_STDCALL)

#   define BOOST_PYTHON_FN_CC __stdcall

#   define BOOST_PP_ITERATION_PARAMS_1                                   \
     (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/signature.hpp>))

#   include BOOST_PP_ITERATE()

#   undef BOOST_PYTHON_FN_CC

#  endif // defined(BOOST_PYTHON_ENABLE_STDCALL)

// __fastcall calling convention

#  if defined(BOOST_PYTHON_ENABLE_FASTCALL)

#   define BOOST_PYTHON_FN_CC __fastcall

#   define BOOST_PP_ITERATION_PARAMS_1                                   \
     (3, (0, BOOST_PYTHON_MAX_ARITY, <boost/python/signature.hpp>))

#   include BOOST_PP_ITERATE()

#   undef BOOST_PYTHON_FN_CC

#  endif // defined(BOOST_PYTHON_ENABLE_FASTCALL)

#  undef BOOST_PYTHON_LIST_INC

// }

}}} // namespace boost::python::detail


# endif // SIGNATURE_JDG20020813_HPP

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1 // defined(BOOST_PP_IS_ITERATING)

# define N BOOST_PP_ITERATION()

   // as 'get_signature(RT(*)(T0...TN), void* = 0)' is the same
   // function as 'get_signature(RT(__cdecl *)(T0...TN), void* = 0)',
   // we don't define it twice
#  if !defined(BOOST_PYTHON_FN_CC_IS_CDECL)

template <
    class RT BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class T)>
inline BOOST_PYTHON_LIST_INC(N)<
    RT BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)>
get_signature(RT(BOOST_PYTHON_FN_CC *)(BOOST_PP_ENUM_PARAMS_Z(1, N, T)), void* = 0)
{
    return BOOST_PYTHON_LIST_INC(N)<
            RT BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)
        >();
}

#  endif // !defined(BOOST_PYTHON_FN_CC_IS_CDECL)

# undef N

# define BOOST_PP_ITERATION_PARAMS_2 \
    (3, (0, 3, <boost/python/signature.hpp>))
# include BOOST_PP_ITERATE()

#else

# define N BOOST_PP_RELATIVE_ITERATION(1)
# define Q BOOST_PYTHON_CV_QUALIFIER(BOOST_PP_ITERATION())

template <
    class RT, class ClassT BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class T)>
inline BOOST_PYTHON_LIST_INC(BOOST_PP_INC(N))<
    RT, ClassT& BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)>
get_signature(RT(BOOST_PYTHON_FN_CC ClassT::*)(BOOST_PP_ENUM_PARAMS_Z(1, N, T)) Q)
{
    return BOOST_PYTHON_LIST_INC(BOOST_PP_INC(N))<
            RT, ClassT& BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)
        >();
}

template <
    class Target
  , class RT
  , class ClassT
    BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class T)
>
inline BOOST_PYTHON_LIST_INC(BOOST_PP_INC(N))<
    RT
  , typename most_derived<Target, ClassT>::type&
    BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)
>
get_signature(
    RT(BOOST_PYTHON_FN_CC ClassT::*)(BOOST_PP_ENUM_PARAMS_Z(1, N, T)) Q
  , Target*
)
{
    return BOOST_PYTHON_LIST_INC(BOOST_PP_INC(N))<
        RT
      , BOOST_DEDUCED_TYPENAME most_derived<Target, ClassT>::type&
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)
    >();
}

# undef Q
# undef N

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // !defined(BOOST_PP_IS_ITERATING)

/* signature.hpp
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
*/