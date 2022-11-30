#ifndef BOOST_METAPARSE_V1_DEBUG_PARSING_ERROR_HPP
#define BOOST_METAPARSE_V1_DEBUG_PARSING_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/build_parser.hpp>
#include <boost/metaparse/v1/start.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/string.hpp>

#include <iostream>
#include <cstdlib>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class S>
      class debug_parsing_error
      {
      public:
        debug_parsing_error()
        {
          using std::cout;
          using std::endl;
          using boost::mpl::c_str;
        
          typedef display<typename P::template apply<S, start>::type> runner;
            
          cout << "Compile-time parsing results" << endl;
          cout << "----------------------------" << endl;
          cout << "Input text:" << endl;
          cout << c_str<S>::type::value << endl;
          cout << endl;
          runner::run();
          
          std::exit(0);
        }
      
        typedef debug_parsing_error type;
      private:
        template <class Result>
        struct display_error
        {
          static void run()
          {
            typedef typename Result::type R;

            std::cout
              << "Parsing failed:" << std::endl
              << "line " << get_line<typename R::source_position>::type::value
              << ", col " << get_col<typename R::source_position>::type::value
              << ": "
              << R::message::type::get_value() << std::endl;
          }
        };
        
        template <class Result>
        struct display_no_error
        {
          static void run()
          {
            using std::cout;
            using std::endl;
            using boost::mpl::c_str;
            
            typedef typename get_remaining<Result>::type remaining_string;
            
            cout
              << "Parsing was successful. Remaining string is:" << endl
              << c_str<remaining_string>::type::value << endl;
          }
        };

        template <class Result>
        struct display :
          boost::mpl::if_<
            typename is_error<Result>::type,
            display_error<Result>,
            display_no_error<Result>
          >::type
        {};
      };

      // Special case to handle when DebugParsingError is used with build_parser
      // (it shouldn't be)
      template <class P, class S>
      class debug_parsing_error<build_parser<P>, S> :
        debug_parsing_error<P, S>
      {};
    }
  }
}

#endif



/* debug_parsing_error.hpp
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
*/