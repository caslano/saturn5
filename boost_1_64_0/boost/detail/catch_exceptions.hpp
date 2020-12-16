//  boost/catch_exceptions.hpp -----------------------------------------------//

//  Copyright Beman Dawes 1995-2001.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for documentation.

//  Revision History
//   13 Jun 01 report_exception() made inline. (John Maddock, Jesse Jones)
//   26 Feb 01 Numerous changes suggested during formal review. (Beman)
//   25 Jan 01 catch_exceptions.hpp code factored out of cpp_main.cpp.
//   22 Jan 01 Remove test_tools dependencies to reduce coupling.
//    5 Nov 00 Initial boost version (Beman Dawes)

#ifndef BOOST_CATCH_EXCEPTIONS_HPP
#define BOOST_CATCH_EXCEPTIONS_HPP

//  header dependencies are deliberately restricted to the standard library
//  to reduce coupling to other boost libraries.
#include <string>             // for string
#include <new>                // for bad_alloc
#include <typeinfo>           // for bad_cast, bad_typeid
#include <exception>          // for exception, bad_exception
#include <stdexcept>          // for std exception hierarchy
#include <boost/cstdlib.hpp>  // for exit codes
#include <ostream>         // for ostream

# if defined(__BORLANDC__) && (__BORLANDC__ <= 0x0551)
#   define BOOST_BUILT_IN_EXCEPTIONS_MISSING_WHAT 
# endif

#if defined(MPW_CPLUS) && (MPW_CPLUS <= 0x890)
#   define BOOST_BUILT_IN_EXCEPTIONS_MISSING_WHAT 
    namespace std { class bad_typeid { }; }
# endif

namespace boost
{

  namespace detail
  {
    //  A separate reporting function was requested during formal review.
    inline void report_exception( std::ostream & os, 
                                  const char * name, const char * info )
      { os << "\n** uncaught exception: " << name << " " << info << std::endl; }
  }

  //  catch_exceptions  ------------------------------------------------------//

  template< class Generator >  // Generator is function object returning int
  int catch_exceptions( Generator function_object,
                        std::ostream & out, std::ostream & err )
  {
    int result = 0;               // quiet compiler warnings
    bool exception_thrown = true; // avoid setting result for each excptn type

#ifndef BOOST_NO_EXCEPTIONS
    try
    {
#endif
      result = function_object();
      exception_thrown = false;
#ifndef BOOST_NO_EXCEPTIONS
    }

    //  As a result of hard experience with strangely interleaved output
    //  under some compilers, there is a lot of use of endl in the code below
    //  where a simple '\n' might appear to do.

    //  The rules for catch & arguments are a bit different from function 
    //  arguments (ISO 15.3 paragraphs 18 & 19). Apparently const isn't
    //  required, but it doesn't hurt and some programmers ask for it.

    catch ( const char * ex )
      { detail::report_exception( out, "", ex ); }
    catch ( const std::string & ex )
      { detail::report_exception( out, "", ex.c_str() ); }

    //  std:: exceptions
    catch ( const std::bad_alloc & ex )
      { detail::report_exception( out, "std::bad_alloc:", ex.what() ); }

# ifndef BOOST_BUILT_IN_EXCEPTIONS_MISSING_WHAT
    catch ( const std::bad_cast & ex )
      { detail::report_exception( out, "std::bad_cast:", ex.what() ); }
    catch ( const std::bad_typeid & ex )
      { detail::report_exception( out, "std::bad_typeid:", ex.what() ); }
# else
    catch ( const std::bad_cast & )
      { detail::report_exception( out, "std::bad_cast", "" ); }
    catch ( const std::bad_typeid & )
      { detail::report_exception( out, "std::bad_typeid", "" ); }
# endif

    catch ( const std::bad_exception & ex )
      { detail::report_exception( out, "std::bad_exception:", ex.what() ); }
    catch ( const std::domain_error & ex )
      { detail::report_exception( out, "std::domain_error:", ex.what() ); }
    catch ( const std::invalid_argument & ex )
      { detail::report_exception( out, "std::invalid_argument:", ex.what() ); }
    catch ( const std::length_error & ex )
      { detail::report_exception( out, "std::length_error:", ex.what() ); }
    catch ( const std::out_of_range & ex )
      { detail::report_exception( out, "std::out_of_range:", ex.what() ); }
    catch ( const std::range_error & ex )
      { detail::report_exception( out, "std::range_error:", ex.what() ); }
    catch ( const std::overflow_error & ex )
      { detail::report_exception( out, "std::overflow_error:", ex.what() ); }
    catch ( const std::underflow_error & ex )
      { detail::report_exception( out, "std::underflow_error:", ex.what() ); }
    catch ( const std::logic_error & ex )
      { detail::report_exception( out, "std::logic_error:", ex.what() ); }
    catch ( const std::runtime_error & ex )
      { detail::report_exception( out, "std::runtime_error:", ex.what() ); }
    catch ( const std::exception & ex )
      { detail::report_exception( out, "std::exception:", ex.what() ); }

    catch ( ... )
      { detail::report_exception( out, "unknown exception", "" ); }
#endif // BOOST_NO_EXCEPTIONS

    if ( exception_thrown ) result = boost::exit_exception_failure;

    if ( result != 0 && result != exit_success )
    {
      out << std::endl << "**** returning with error code "
                << result << std::endl;
      err
        << "**********  errors detected; see stdout for details  ***********"
        << std::endl;
    }
#if !defined(BOOST_NO_CPP_MAIN_SUCCESS_MESSAGE)
    else { out << std::flush << "no errors detected" << std::endl; }
#endif
    return result;
  } // catch_exceptions

} // boost

#endif  // BOOST_CATCH_EXCEPTIONS_HPP


/* catch_exceptions.hpp
V1n3IgchIdxBwhz8VIEq/akFPN+XJt9ImZ8qM5im8mCayoNpKg+myoTfevnVNTzI5kanOMFjM3LLv3pAt27PbCCSKlrP9LoV3/qahqPqNBxVp+Go2taRFP88NbgdvQsCfHzLMD+ZhZwuUdQAp0tAtILtKcY7LMpuVZuR5ZMnJv2JbyLUkQ4bRXrJ2hNV1sYImoyFVewDQISkQkzs0+QbKfO1mUzs0+T70uQbKfO1mbxd9JuvF5Li8AtorMdz3CyO56Avh1Y+H31pPzyPqjXrZv3TFz8PTV4DOXgnPrLuuisbWcGxxl72QC/HCtrJHSqqh+iTxzfdC++MeBbWzvRh/pIZj+D013dS4cKZ9M6hLs7myePJ7fRVEQmouwcMaKMTv/rjaqud7Yu9wDAWnFwKMlUP1JwCGu4EhCXmNJOIhjtmeu5mOmzIKu8jA674Dk97XZGPfNSmMHFgMk0xEinuwtoiH39wtM0smiNV47EgzElCmJuEME9G6LQgNCwI85MQFiQhLJQRuiwIiywIByUhLE5C6JURui0IHSZM4Y7B9TBzLzqrfaYHwCoTWFh+kMQmKj1n8eQiljxsE1NyMUt2bWZKNlhybBImS8dMkzrL22Z7MKzrKUcjliC5tqieHtpsSneJdJ8p3SnS/aZ0B6Tz+lwilZBUT0hq2EDNt4vlV483ceJkyWtSTgStLLmgxpRcwPjuDVn5dur5ztPwnavhO0fDt0fm2y2wM0obq9R857L8ULWJkxyWPGqiKdnDkktCpuR8xvdvlVa+XXq+CzV8F2j4ztfwbch8OwUWRmlTpZrvfJYf3sjESSFLHrexWaBZ8vBNzdCMb/dGVr7der69Gr6LNXwP0vBdBOmyBaqH+Pf6wx3zador+e2TS+vrOnIOJKpe0146hwRlKp+wykXYrOe5nH+znrs4/+uzZOnUfKPNUyAW1BgZP4xLkFHIyPhgA4kMq5wtGK+Us1snKak7bwOzklrJKGJkHCaRMYiRsZtMhlWfJ4xXsr2WRIYkO0UWaCsZxYyMT4MJMryMjMVVEhlWa3OfpIyS7brcrIxFLPl0c7LbSobL2tiTg1wnrhY6IctEVZWyM1arVnZG7kQlsd9upLH9czS236ex/T6N7fdpbL9P1CdSmZruNVbNt4vlT6w0ixVLXttsItwsuXhjpaz8PEFh+3V852n4ztXwnaPh2yPz7RTYGaVTxqj5zmX5tWatzmHJ621oFgOWPGSCcoSMr6ew/Tq+CzV8F2j4ztfwbch8u63D8OHrqfnmw1XdOKU132ADpTOz+nilC5BHkci2X8+3V8N3sYbvQRq+i0x8g7MI7z+MTpgZFzEzPmJmDgkqzEwR59+s54M4/9Vq/kebxcFqZpyMjJ8qEmQ4GBkfj5XIsDqPT0tqJ3mgd26kpO6isWZhtZKRx8iYKpGRy8jYUybDyt8mlUqfZh219vvM0LlWMnIYGdF1E2R4GBmvjZHIsArtQ+srhfJqSRkl1W6zJHMytH5/w7qp/f7qMUq/f831lX5/gbl6g/u/41Y4v79xVGq/P7Se0qqNGqdU+pINlH7/b1UrnN/fFEjt94dHK/3+cUGlCzC8Sqkj7sAK5/c3r5Pa76+vUPr948cq/f4RlUqlLKz4p/1+N3MxTx0p2X7mYh6xrsr2c/7HmK0r5399pac7YqS5WRS2H8n4dW3J9jMyPh+lsv0M8SKz2nlZ8r3jlJ7uZaPM1ClsP5JxjERGLiNjX5kMa/9utp6S7YpxShev1AxdoLD9SMZX5ZLtZ2S8FZDIsArtw6OVQnl9UOl4dwTN0Gn9/r3KU/v9EwNKpV97tLL64qDS7/+5YoXz+6esldrvr11H6fevV6E=
*/