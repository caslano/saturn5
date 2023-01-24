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
KcKvYRY2e7LCfuv12Vql0gfO8BHSPzkUVt1dq7+srdqQ82rkplB0PPZDK36TjqxxCGd26cYbrNa3dNtdiybbOzvSnR1L9qbHdEf6hlBqTWepY2m7KwBvbCUURSi+RW+0jKgba44Qam+NpZe2xcS+PFP8wwr/+qebs1fw+l8RXP/fqnZe0r8KuQGmns66aUY6cfUKjm2+iSqzPxlVp1BpL8ddm9zHm8Hc+UxArIDgURszPxirMxqxqaXeqI4EFGqeqFilN/uMzKxkm9gwS6u2RbWf9PbSEzTadS0X3qStW+1dziXhjZHp2I3x4WgisiqcdgO4o2vC6xObqbYisag+1bio6bnW99uyi/K6baC1vdn8oWVct7XcrZuak531nYkV9OhnxOyWWHXm0tdIc6y1flG2ZUD/B2N1+JM8Vt+lytyVUbVwZTlOa0GQETNJKnwotsofgMbcxIS45Lo/Jn4O8RGI0zpppWcCWHI3YZTk6tO1db094awJl6gPxfDKaDa2WMdHE4eT1+uO5HJiIJoNAzGenK/rhxvP0vUT0ayrKqWfZ8w1JR0Px2LpeCzZ1tjIee2iqoFwdgPh7IZJL6/dvpW+9fZNuvn7lez/vjK43q7R9ve1SwIUx1AyHaqIoTy+MurlzP2AbuadCXjVZ3r46Rrq7QXVzrshfUSl9OSH+Q4uO9OnLz+Dbv7kTNDKs84Mtq0uFH2UBM3LOd66
*/