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
cctmvYOxbNqPfZZN+7HLsmk/3lE2z+fOzZZN+/G6ZdN+rLZs2o9XLJv2Y7Fl0348b9m0H09ZNu3HY5ZN+zHTsmk/HsLm/dw5ybJpP/5q2bQfoy2b9iPTsmk/Ui2b9mOwZdN+DLRs2o9+lk37EWfZtB9dsXk/i7a3bNqPlpZN+9HUsmk/Glg27Ue0ZdN+VLVs2o/ylk37UdKyaT+KYvN+Fi2obY2UHqb1GKUHar2h0g2tN1D6
*/