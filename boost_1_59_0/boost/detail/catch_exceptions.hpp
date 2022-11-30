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
#include <ostream>            // for ostream
#include <typeinfo>           // for bad_cast, bad_typeid
#include <exception>          // for exception, bad_exception
#include <stdexcept>          // for std exception hierarchy
#include <boost/config.hpp>
#include <boost/cstdlib.hpp>  // for exit codes

# if defined(BOOST_BORLANDC) && (__BORLANDC__ <= 0x0551)
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