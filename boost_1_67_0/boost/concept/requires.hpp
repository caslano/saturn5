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

#elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

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