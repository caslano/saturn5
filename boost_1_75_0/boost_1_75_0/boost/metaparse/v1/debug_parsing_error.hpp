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
mdd0nPvTHMKAnun6Gs9qJ/ZXeSf21WzTXxLkm/45YZ5xvRrVhr2WaG7Yt0LeYzWp1n1GetFSUKcT1gvHQuExdBUefR2tArKbApmpxnJsQ72mtJEhPm82ytrwEbzK4uthVXIaNQ8/1rl+EPTdvhHM7mrf7ZEHrab6d387Ed13e+Qqa3Tf7VlvW01a3+3z31YrxDcoiVc+bDPJ9x89EdV3u8vsZvtuD7n/v9p3++7emu58ur7bq6x/su9277esMftu72zfor7bdyw0m3R9t9OqOJP+/6Pv9i7LX++7bZ8Vu++2Uiz6TfxWTFup6yMoLJ1NhwwJDwmP6Gitru925SWai6W5vtvtLP9R3+17Xjhh7Lu9zfwX+m7bZ8buu60EIWtt8KETMfpuR3ppNuWovttuc/N9t8f9ZP3TfbcLHmxZ3+05xXwdRB5YfrI75E7gK5LuAXVJplUI5tVS6busWhIQbPeBtg2STgaE9QNwzga458uPP2Hm5gXIR2dSMsScSf+CoIOHEiFvzR9XogS20s1LHoWby6mJtjQdC0GnI0T/6rz2DmhmXr8/rpvXe0/o5/VG++h5nQydeV7eUBbOC6ox0rTc0o8x5zSSzynPOKc8eRqfUx7M6QIxp+3y13Z1Qjvozun6CcGyMi627a/M5YPMZuayZ5FuLkseV+dyTofoudTNjz0XQ//2Tq9a/1L/9vI0vZ81un974ilLrP7t
*/