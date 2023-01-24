#ifndef BOOST_POINTER_TO_OTHER_HPP_INCLUDED
#define BOOST_POINTER_TO_OTHER_HPP_INCLUDED

//
//  pointer_to_other.hpp
//
//  (C) Copyright Ion Gaztanaga 2005.
//  Copyright (c) 2005 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

namespace boost
{

// Defines the same pointer type (raw or smart) to another pointee type

template<class T, class U>
struct pointer_to_other;

template<class T, class U, 
         template<class> class Sp>
struct pointer_to_other< Sp<T>, U >
{
   typedef Sp<U> type;
};

template<class T, class T2, class U, 
         template<class, class> class Sp>
struct pointer_to_other< Sp<T, T2>, U >
{
   typedef Sp<U, T2> type;
};

template<class T, class T2, class T3, class U, 
         template<class, class, class> class Sp>
struct pointer_to_other< Sp<T, T2, T3>, U >
{
   typedef Sp<U, T2, T3> type;
};

template<class T, class U>
struct pointer_to_other< T*, U >
{
   typedef U* type;
};

} // namespace boost

#endif // #ifndef BOOST_POINTER_TO_OTHER_HPP_INCLUDED

/* pointer_to_other.hpp
sy6ipCwfeMjOl2Aa7lZwtsw+TGAuvtCiEvbNU4CThU+5jH81Xja/f/fXgO3ie++FWKCEPS+pnBXn1n7+YiLn+j0+VDCRooD7kb6HjQSYiopUCG5JJPg4Hv8CMp3lzrN0ozex9WCpTl6HxdV1JprZfjAe7LhSL/E+i2OIK9WSKX/3PUXYdsdaG0r64zblyQd+xBWdhiXjpo5EM88J7g0gICBXAPH32qpiWppYaBQLTeJIsTCSz7D4zThXMDbR8aLK4x+Dfnr3RbTFlM5DAYDTmRdxS6SgW7oIzUi4vwwqqnhfqw8pfQbURut1PgiFpbbuvxL/z7eo/B+vw0gwYs8aDbXAy8WaQfRtQ8mCdwH2LArhG8yGLhGtajtqTSANDMKrEyZlYYScG0voHzWzjS3V5clpWihayogQOTyecZsys+hDiPn5YpjaSKnOu3QMIfIj15vITrZrTRdJ+ujcjuuBYu67bI8KZsIpZtesw/eZd3ufOM72++UokG6u19Fdfefj1AMIPgwe3O9PYClMH+UEDq+QfWnyDm9F7fS3nHNEK+riuIn5tHsg282EQiXXVro/0GRoFKnXe+Q6PPIBvbDseB+NPlZuO8aufGZDIu4S442zDJSHvDTBzP9OsRmFjqUnirx7j9Ez6w48szbSM2uk9ttgTfCG3Eqf1r4saSAmXbgF3xPtTEju5ITI4ZpF/SzI4D3xCt7KKln/OJBJ
*/