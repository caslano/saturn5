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
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
*/