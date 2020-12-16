// Circular buffer library header file.

// Copyright (c) 2003-2008 Jan Gaspar

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See www.boost.org/libs/circular_buffer for documentation.

/*! @file
Includes <boost/circular_buffer/base.hpp>
*/

#if !defined(BOOST_CIRCULAR_BUFFER_HPP)
#define BOOST_CIRCULAR_BUFFER_HPP

#if defined(_MSC_VER)
    #pragma once
#endif

#include <boost/circular_buffer_fwd.hpp>
#include <boost/config/workaround.hpp>
#include <boost/static_assert.hpp>

/*! Debug support control. */
#if !defined(BOOST_CB_ENABLE_DEBUG)
    #define BOOST_CB_ENABLE_DEBUG 0
#endif

/*! INTERNAL ONLY */
#if BOOST_CB_ENABLE_DEBUG
    #include <boost/assert.hpp>
    #define BOOST_CB_ASSERT(Expr) BOOST_ASSERT(Expr)
#else
    #define BOOST_CB_ASSERT(Expr) ((void)0)
#endif

/*! INTERNAL ONLY */
#if BOOST_WORKAROUND(__BORLANDC__, <= 0x0550) || BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
    #define BOOST_CB_IS_CONVERTIBLE(Iterator, Type) ((void)0)
#else
    #include <iterator>
    #include <boost/type_traits/is_convertible.hpp>
    #define BOOST_CB_IS_CONVERTIBLE(Iterator, Type) \
        BOOST_STATIC_ASSERT((is_convertible<typename std::iterator_traits<Iterator>::value_type, Type>::value))
#endif

/*! INTERNAL ONLY */
#if defined(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
    #define BOOST_CB_ASSERT_TEMPLATED_ITERATOR_CONSTRUCTORS BOOST_STATIC_ASSERT(false);
#else
    #define BOOST_CB_ASSERT_TEMPLATED_ITERATOR_CONSTRUCTORS ((void)0);
#endif

#include <boost/circular_buffer/debug.hpp>
#include <boost/circular_buffer/details.hpp>
#include <boost/circular_buffer/base.hpp>
#include <boost/circular_buffer/space_optimized.hpp>

#undef BOOST_CB_ASSERT_TEMPLATED_ITERATOR_CONSTRUCTORS
#undef BOOST_CB_IS_CONVERTIBLE
#undef BOOST_CB_ASSERT

#endif // #if !defined(BOOST_CIRCULAR_BUFFER_HPP)

/* circular_buffer.hpp
bGnRhZPgLtKP+Awq3rzYFbgdn6afi8td6YX/QKkYx2vCEnZunSUZUcU9MDRDdVZXcZL5st6Cl4O2QEb5nQY1v16u8ZP/AYbksvtB18/UFu0QKsC6eOjCGqrtMcB+CaxEgRO1QgN4hx0E6+tK3QYLvgYw+LQuTKTas8kVseMZxTFR4jiy38TRU+sFHG51A9xcTgPm8rSo/84NbzfppNUjV9ikxUZHKm1+nC6ynGhn+awx5cuXuB+P4k7QqrfL8g0S5dus143HEqV+XTcGD0XV1f0+9TNu1fHgu8V8ZL550rQ0upq89oyufffqNXQo1cD373KDKg8Q5r5o9lfJ7M+IZp+kuY3sy1EBtMxe0TKzr8lpmn1VNNmtMln9l2ay07V2280WabO/RYtcsaNVixxBKi3okC1ypY1hchDARAmkXRIQwvEMvgA1eTGOg+iO5hYLyrx/Ec3bpt27TRY5gUWWuF61YjwtsQYSXunIdXDEEhteO8mtF8l47SK3Xjjw2pmv57nKdyVOS3qlJ9PakhHSAyFOhPRgiIMhbV9J4jtHagHaMwG208VWvKsX0lmGBJos/pk+9XIuZRv2pVg8/T9Uyu4Tu3+glS0Iz3Z6wpcq4ckOLMzrleet2q4t0R057UzGrI4KQq5zXn84U8VczNkQ7A2DkU9uEOi+UYpRyVbZHk8wyZ85hz5nyQJ52B4ZOI9/uoWabMFrIo5XLPiRWsC1YLsNFRkWcQw2vpfw+yJMcn7cxY9zvBFEiXlPrQt7Av2AFv8M45Gb7THHALuRbQ1A1PTDvZK5WGmRzEX2X+W+wmxWq7+n+MOAkwWfD06FBaasJ3oTOJ/ea/ZijbbuTdGL9blEW6BudOM5ACsXF3ux6A91egtJmfm12mHFuGGwsQtBW8jirfKr7Am2nyQxzZ5sBhWikyhpe+qBpqg7G+2m/0mOOP8jv5P1p/GqtlIyJ1ypbceAgApDrcRiqZRaBJRS6rV6QzaCxsanIp7PZKU0zyoS4MVmprAjhaP6uOcBZn1irIxvYwKU62LUJGpPgqRidMvyWROPYfrSZSbVrfF98LHAp+4IHZxzu9M8OU5PGT+gNw1TcaGv04J1IumJ2NMWS2zEZdo3I8qjocZut58dUVby+SM4mIQa29zeLXQwLdBZ3Qwft998himaYj+vt4WqGVmJb7VemuXv/XFMe4TW6vDRerCqSbfaY8p8/PONKQRJXNs+Erh8ah3kIHpz76ClZrmxI2DC3CbS7WAH1/JEOn1uJBdSN4/ErcnGiNMRAWsEg6kB8MLnJbGWX6EvbPXXzm1yEOgiAZRqAlXuSiaM+LBV7nJGP+xI7jCTO+p7cpWCfZoyTqeXxfo5SEVc30auoJDMPgu08alv6W9yl2qJ7ioZoZte8ab1eiQbQ4gjJGTa66f2F+tvJxrz7g/lwOoODap6kIxFVwyL6S49xdq/t7R56mkBe+iDpoZqW2BQSJ8z/YLIMDFW+kWGibGSHhkmxkoPQnZF5SPtbq3nWNnWV4yVIFIfaahODjiR+nZ8fNFQ7QgkztU5Lfj9tav8AyycCNAR4AD/lwh5thPqz1bJJPufzVb5SbWpGWgR/H2EgrJxgv//QI5O85ILrhDk5oUa3x/mGyVPNz4HYPnJE1LtG9sEqzzuuLlDLpI7nY15cJqRE5dGDNwsvUFJc1DYbUO/679Tcr2Kkus+6l2lPHuBCB3H0J0MDd+FDsxpyE9zBk4HSCpA2guQawlSJkFSw3d1BojVqyKjQIpS9lNEcp2FaMnBeS/Avsvpk9LeMWaPqIVSNlRiXQisEe9ebfFShKPD+2BZvhNhXKq9AImMvIsaAmhntbM3RC1LNXlp32oGPFk=
*/