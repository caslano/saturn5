/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/macros.hpp

 [begin_description]
 Some macros for type checking.
 [end_description]

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2010 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED


//type traits aren't working with nvcc
#ifndef __CUDACC__
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

#define BOOST_ODEINT_CHECK_CONTAINER_TYPE( Type1 , Type2 ) \
        BOOST_STATIC_ASSERT(( boost::is_same< typename boost::remove_const< Type1 >::type , Type2 >::value ))

#else
//empty macro for nvcc
#define BOOST_ODEINT_CHECK_CONTAINER_TYPE( Type1 , Type2 )

#endif // __CUDACC__



/*
#define BOOST_ODEINT_CHECK_OPERATION_ARITY( Operation , Arity ) \
        BOOST_STATIC_ASSERT(( boost::function_traits< Operation >::arity == Arity ))
 */

#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED

/* macros.hpp
vgZNUyfapbt+j83LZ2C0pf5saParZ4hm+8xvT7N3rYih2Vd0mp3yO0cnSqc9OqCQU9Sp4O1MX/Gyrl7W5p2KB5hlHjDyzlGcvf64UeVjn25cYhZy8affsIjHqUABjiFqKZfzhG1/HOUQwZ0BqLfAN2H9mw1Y9Dh8ceeKyqppBkF8+g2ML9fvSSGoi47iws90haA/1sqZioo9QC2ANRGwmRzYmiiweb+hg7AB4LWV/h0VgtBxjSsKnrLGwBxDP/gORPUKdfzTpB889QjpBysk5SYz3a8nivKvw6YNnL45KvSDdaAObAL94J+x+sEmrh+sUL/FeQ1bsD36Pe1pUgf64wQtGWtMDCX2nCzI7JOvkczK7xL5z4nONm4mfQYjfoDUpiO+7ehs0vazobOZTxGd/XNeezr742lBZ7E9Ian99mu8fvfaU/H63ZabTqPfGetjZCoB/e6vfH0Y9338/nP8PsZCLD78rND/tkWdvHRH1MFgW/VqtxsD8LUnPHypJzxyuV8ZWQ6MxxsevgrsVayhzHh2FAQw8yYCDFvmOTQPT4Tm8KePpeHmA+NVBXgOyVKKRuNbEbxzOlVDGUkcdZJ2k1WPs6A8IRzc/VvjwPWwnW74KsvNeP4yHyZBeJowWJ9MxFdHGx5u3E3a6E81cfvNjbk5FNkKBhYMD9pjXizdWsqHFiNDGC82ApduuNzLLwdo9olHaPFp9v4/40VV
*/