//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_DETAIL_THROW_EXCEPTION
#define BOOST_PTR_CONTAINER_DETAIL_THROW_EXCEPTION

#include <boost/assert.hpp>
#include <boost/config.hpp>

#ifdef BOOST_NO_EXCEPTIONS
#define BOOST_PTR_CONTAINER_NO_EXCEPTIONS
#endif

#ifdef BOOST_PTR_CONTAINER_NO_EXCEPTIONS

#define BOOST_PTR_CONTAINER_THROW_EXCEPTION( If, Ex, Msg ) BOOST_ASSERT( !(If) && Msg ) 

#else

#define BOOST_PTR_CONTAINER_THROW_EXCEPTION( If, Ex, Msg ) if( (If) ) throw Ex ( Msg )

#endif // BOOST_PTR_CONTAINER_NO_EXCEPTIONS


#endif

/* throw_exception.hpp
mU+rbUWuiA3UK26ZmEn22IkEuaUkEYYWYRmLU3+7jZbd1TdA6llz+aiFDfuSV6geC0qlCT79dufbUirqakkY8dHHYiSGsYekGn25dwo70OFGzNVDR0wk/drNzfnHxchtjG0XIql1lLZLQyPgzLD7xAa6zRvg5Nn5kLdVaFUn4W5jca083qrJEr2g6FxgiaD83k/BqWtRlUdj8giLBGTZaOceh+ZLqD/O6KE1GzgbhD1mK/cghxZygzMjYSU5fstRte81kDw6uzGdopkH5yHBWuzXoVMn8au59gJVIkdxpj3ZZoBFa8+4yuzBFlIFx1OwVUpHkB+GrG5R1JoI4VvGNB1rPzJ1Kmv4M1bNc0aAPskodETbFydiK5I+TmpOeIouPL9opjudoeVk/9NlcA3gEi+d1WjpgA+dE9f+iRHU15//2FLPm4CyFaxLmCNcHXFDinJssz7jkZgKHvdvyXjr7DE6oSS1yn3Anhn4bf6RT2O/QgYKhq9J3yAxK9jg2xhBBwiorHcx20iaNhzJXu/3sRHJGK6Y1zbgaMjanKjGvHyVrxLTjOu3QZ2tKQ==
*/