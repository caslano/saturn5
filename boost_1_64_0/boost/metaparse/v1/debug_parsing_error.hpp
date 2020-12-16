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
/Lhafo/Xe7zB47HB+vl1wLXzS+Da+aVxtfweb/B47HTda3Ht/Abh2vklce386nG1/B6PnaF7La6WH1fLj6vlx9Xyezw2RPdaj6dw7fxuwLXzy+Da+TXgavnP1L3W4ymPZ/H9tf4nj0fPChfXN6suVT5c2z7l8azH857jx4bq29d6POXxrMfzuFq+YZ7yeTzl8azH8x6Pnq17wuNJXDv/LK6Wz+PRc3RP4NrxU7h6/Tye93j0XN0TuFo+XC2fx/Mej9bpnvB4Etf6R8fgWv/o9Xg3Zfwo59n/es/+t3r2Hx+u778bru2/D67tP41r8aM5/Fzl+7IeP1vJj/k73tVx2b6pPS8c3NRY7B+qKezhMnwh4zvHOT6RBtMhhf1fgc8R/t1PjKEX9j8OnyX8uP+Q16JQf5+JjxP+IF5s31xMpr0S6xsOMuXD14SwSuvDaNDuWyjfVfjzwmfj7Uz+NvxZ4d/ibQvlm4rPFz70K6d9MdrTvsC19muDvj0DdJ7+XY/H8AuV9bE64Bc4Lu+fP+GHuy7bx/hVZl3mUuuv4OMcl/vfgPdzXO4/cWk4+IX7Q+7/LDO+ia/Eb6m0/s73xHCZ9f3xx4W3/4HzLux/Cj5X+FjcrM9yP54W/jZevD/HMr5SYvzm0EL5zsEX40cX3OSHaWbGp/BFwmfgUZN/G79f+Ke46R+4HL/Xdbn+77hwsMV5/uX8g+n4eqV++iKecVzOD3gJn+O4XB9tNT7Lcbk+WuZK+m8dl/FF8/AHlPV95+MLhe/ez5bvd7y38KvusuWrvCocHCF8C27+SuHznfWn5fqQD+KX4gMqrX/9LVub9R/wEcIP/c6Ozy3FhwqfhJvyDb86zPqBO/tXuF3/lfZFhX3+5frnc/EEXun4mR3t7/sCHhU+crvd28/4myI+80m8OH59bTj4PtjZ23zrXL/xnL8SP3ITfo4SP3YzPkz5fgZ/DgcjlfkvIXyE4/L90x3v7rh8/6Tw//CwyP0fbvJr47dzsMNC1kf928kPMoH4JOGLcLP/vfBOwnfgxfUZ8f2En/+9c7dO8pw/rp4/rp4/fm2FdTm+dTs+Cm9jnfz4tv9zCn6R8MW46f+8Ax/puFwf5E58hOMyP35mMvEhje39IccHH8bb4mJ8yK4fh0fxcuND7W9lfp24v6d8a3+f6J3h4G6nf1Qevxk+rUT/sHn/t8KnOC7jR9vhN5foH97VrJ+IX6/0D+dwN3+lzA+4Hr/ScZkfcAM+Rlmf/HX8cmV98uRfwyI/oojvxU8U61vMrXHi39N6/0Sdx9Mer/d4A661b2JTuT+V+Ysd8PMcl8/fKXjcdVm/8ux/nmf/Gzz7j03z9C94PIV3Vtqn9R4P7tL3H8c/KfH7dDPlw58O+PdK602/ts/XEDwrvAbfzfRf4w8Kz+Ah8/3F/yZ8t2+c+M+7id/U+jfxU5T22Y14TGmf1eNL2Zms/55c2MMn+I14m0rrN1O+A0z+bPxa4avxfQr7r5hO/V94dQPPY+H8d8eHCL8JL+YfvIf3u1L/346PVOr/HWeEg8OU+n8KV+8vXHs+VuDa8/Etrj0fiXv146dw7fg34NrxH8O14wf38fso91cIP1+5v/6Aa+3/FH6e1n+N17kuy6/vn8ZAWF2/6xb80oJFS+TvTsy089ublBi/rsGb4OXyf0/Hnw2sy/k7mVnMj3Lii2T77VX8TJz2P277F0Imvhw/Q/hs3Oz/6Nlh1ofc2b/FzffxBPxdx2X/Qn4uv69yf23Dhyv3154Z4heV+6sO/4sSv3kVzv0RnOb4ui9sfMt4fJjwKuf8o/O4/iXKf0hh/13xuwOuqePvL7frd/XA7xT+8CYbn3wkfovwHbg=
*/