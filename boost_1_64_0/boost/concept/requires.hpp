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
jDW7LKriHB7JGhnloGWIwPo/R+syy0TIQydg2qRpP6s03fOaB+1iEjl55KVsz7RqqNPKF/mycsI6DfYY/tKeQ+gYcOvHtYifhsxLQy8v0IEFpmrYuPH/0v4quPAzJ0nQ6YauK1PlaFdf0SLzQ5VY6EYC7KO6XrGglIVGh8y3bk3SdJmnKloIyYd8paExxx7kZYTXZ1JGQeKmBeWtt2sHLN44kWGWenLIO9BUeTfEmtP2TV7J0kJKmWXhkJXO8x2cs5M0HRYGrhBR6DLoD2V6C4p/paoY545VWzb5MpZ4TigSB7jQ9BOdXmrVY+ImRZ4kieIo+7DaR100vKCUvOi7yOSdDmUU+bHvl5xqftOtloLHq7TOWvWXBy7PskwCR5k5khAdv8+bvAWLijCPQR3Aqkbu7rLydNkl/k7gP+IXJodFcijzkmfl+KF5tOkl29Bnz1bNh/N6keRB7ATKx6tpvadwzWToc9riDWMn9RKXslre5NOqnZm8nsNE5AapLwvKTC3IVOlKGe37ZdEmtmx/jEEWOjxkD1F3CpSCoYpg10OZ59mFxYVVbYtW4UzusbdWtlmC9qoZHbpFKc9j3rpd2bu9lI4P8803jernJoY/CA1GBwBh1WbNc0dXspBnaRgnEfMH+wtYT2hE6f0X9GlHzpyDKHALuP2yT3Sksz8usZjmFvO81w9YzoPCD1O2r989BN5hV/SAoxQ0r/7Z03/CnH8qKIZ9IDbl7I4Lyf04S1khOvf24sDjumKmwqqOSbqS5VHmBr6TkIR111tYOq6SVPfqoLYOK/vSNe76mHK8hPFYFTYsfFMOeOodKF3xa8MI84EyNoV518eUpQqXO0kQcCdl95nvrkILL3M0MweGGa0ISl4lsuTfTFmCJWGsWl1cmPl6KIod9vvl3jEYp0pZla7WTFmwX+nFiXRcwZy5OSgedKNlNbSDX+BSAohegH4NeRvqqvV3U1cSYuKHjuOFLCvTPt4fVC6WaEVnVdFmT2hd4T46kVUwXshUyuCi3x+gT0hT3p1zzy+4k/jsIYNjCTpOnzSxOZOh9BxXO3jsEFPWWqzuXsXSOFvX+3Xm3StZR9fnSyBjj7IFZ8r+WRHxoA7PZg+ADKTrAzWVyCXaB4Bz6xZSdcEgNEN5d9o3aCAT8PHgWycPcjAr4IQM8OUd7MSgwXEIEOD7+9VZiK96enivwuvsv68M9J1tPpQPPJjGfYbfceuypfO7z6AZui1pkZH+McyaEathTOlteJ8f94B/W343d3XLcxyMQ440zE1ZvNLsmuf/a1sMrHluounyCki3NoJbmJcvXNHElGcqSDtwJZMGnXMom10Fadamr3Ef6qqAoe2JvM29mkEH8RVocNiH+bjhOODUN/SFMtTxm5EGAgw/L9eA7ytH8Vqi9uuhj81Q361r1uLwSM7U52oT9vgxlLf1WrUY88gO8/ivemx1XIe4r1+7Fof3j9GXnDl2eoL5fubneXjR53qVPZiWlc+wpR6cox9SkRj1mTd5f3SjsabNdXI3B3F2XNj3XdaigSAjjdbla+jo5mjYFj6xBXCjvoP6V4DvUA5knj0xMGyIOX3FOgzUrIG5EsHo0patBNv8ziubGLw3inf0Tv/9iniXxgwxMNd9CLR6cpf8hmPNOLx382drDIqThOfJRd/VQx+nprzdeZHLOJQO0xnB/Y4u+jgl+IinsSdyttI7POiQeK8M995MfMFc7kvHcX08PoI5lmZarMbFK5vteirmDvcj8Cuay/3VAec8+gUm99ZiHvqFm/nM3B+bxz17E6vykKeuV3CV/WqTdGbxSE9F55g/hj41d6KveJP3zonDC9+JJNszUa05/WLEz/IBwpM=
*/