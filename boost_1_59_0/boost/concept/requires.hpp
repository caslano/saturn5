// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_REQUIRES_DWA2006430_HPP
# define BOOST_CONCEPT_REQUIRES_DWA2006430_HPP

# include <boost/config.hpp>
# include <boost/concept/assert.hpp>
# include <boost/preprocessor/seq/for_each.hpp>

namespace boost { 

// unaryfunptr_arg_type from parameter/aux_/parenthesized_type.hpp

namespace ccheck_aux {

// A metafunction that transforms void(*)(T) -> T
template <class UnaryFunctionPointer>
struct unaryfunptr_arg_type;

template <class Arg>
struct unaryfunptr_arg_type<void(*)(Arg)>
{
    typedef Arg type;
};

template <>
struct unaryfunptr_arg_type<void(*)(void)>
{
    typedef void type;
};

} // namespace ccheck_aux

// Template for use in handwritten assertions
template <class Model, class More>
struct requires_ : More
{
    BOOST_CONCEPT_ASSERT((Model));
};

// Template for use by macros, where models must be wrapped in parens.
// This isn't in namespace detail to keep extra cruft out of resulting
// error messages.
template <class ModelFn>
struct _requires_
{
    enum { value = 0 };
    BOOST_CONCEPT_ASSERT_FN(ModelFn);
};

template <int check, class Result>
struct Requires_ : ::boost::ccheck_aux::unaryfunptr_arg_type<Result>
{
};

# if BOOST_WORKAROUND(BOOST_INTEL_WIN, BOOST_TESTED_AT(1010))
#  define BOOST_CONCEPT_REQUIRES_(r,data,t) | (::boost::_requires_<void(*)t>::value)
# else 
#  define BOOST_CONCEPT_REQUIRES_(r,data,t) + (::boost::_requires_<void(*)t>::value)
# endif

#if defined(NDEBUG)

# define BOOST_CONCEPT_REQUIRES(models, result)                                    \
    typename ::boost::ccheck_aux::unaryfunptr_arg_type<void(*)result>::type

#elif BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))

// Same thing as below without the initial typename
# define BOOST_CONCEPT_REQUIRES(models, result)                                \
    ::boost::Requires_<                                                        \
      (0 BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_REQUIRES_, ~, models)),           \
      ::boost::ccheck_aux::unaryfunptr_arg_type<void(*)result>          \
                     >::type

#else

// This just ICEs on MSVC6 :(
# define BOOST_CONCEPT_REQUIRES(models, result)                                        \
    typename ::boost::Requires_<                                                       \
      (0 BOOST_PP_SEQ_FOR_EACH(BOOST_CONCEPT_REQUIRES_, ~, models)),                   \
      void(*)result                                                                 \
    >::type

#endif 

// C++0x proposed syntax changed.  This supports an older usage
#define BOOST_CONCEPT_WHERE(models,result) BOOST_CONCEPT_REQUIRES(models,result)

} // namespace boost::concept_check

#endif // BOOST_CONCEPT_REQUIRES_DWA2006430_HPP

/* requires.hpp
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
*/