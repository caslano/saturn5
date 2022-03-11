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