// ----------------------------------------------------------------------------
// internals_fwd.hpp :  forward declarations, for internal headers
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_INTERNAL_FWD_HPP
#define BOOST_FORMAT_INTERNAL_FWD_HPP

#include <boost/format/format_fwd.hpp>
#include <boost/config.hpp>


namespace boost {
namespace io {

namespace detail {
  template<class Ch, class Tr> struct stream_format_state;
    template<class Ch, class Tr, class Alloc> struct format_item;


  // these functions were intended as methods, 
  // but MSVC have problems with template member functions :
  // defined in format_implementation.hpp :
    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>&  
    modify_item_body (basic_format<Ch, Tr, Alloc>& self, 
                      int itemN, T manipulator);

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>&  
    bind_arg_body (basic_format<Ch, Tr, Alloc>& self,
                   int argN, const T& val);

    // in internals.hpp :
    template<class Ch, class Tr, class T> 
    void apply_manip_body (stream_format_state<Ch, Tr>& self,
                           T manipulator);

    // argument feeding (defined in feed_args.hpp ) :
    template<class Ch, class Tr, class Alloc, class T> 
    void distribute (basic_format<Ch,Tr, Alloc>& self, T x);

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>& 
    feed (basic_format<Ch,Tr, Alloc>& self, T x);

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>& 
    feed_impl (basic_format<Ch,Tr, Alloc>& self, T x);
 
} // namespace detail

} // namespace io
} // namespace boost


#endif //  BOOST_FORMAT_INTERNAL_FWD_HPP

/* internals_fwd.hpp
s+VBngHww9ROAY0hWYDaP8TLBmL/iZfNxO8QL8i7Ua4vvM3wcQM91sPHzfQYg49b6VvtoUwtey8DANLlxSR+YdAj+YVKaAPgpeJLJLspmYdygxjt1UpzyX6mHIkljNyqIrudKNczFIdK1TyxuZgZqwCs8ljgV+JLY6YYF5IYdpKFcsz+/SuBsvurUE2IkLnbhKzCWEa19K1mosxJU+gy/kmc3lhShK/CgUf7kUfSMIm3Cbsrrp1eNYk/haxqCfeNkAdnK8w2Zy/DZDyKyEyvhZPxZ56M3/aA5DlqMkZ+xJNRuM3+vqecjLO6Iimg85Jd0sNgCO+ZTuqyUgJ/fQ+lQgw1IeInwB6pDV8Td2k0sz7nYY1uVeO6D2GXfxShHROcw7atiXNoN/+Pcg5rfqHuUxY3IHpEqQNZ5OTVE+95UKkDPaLUgU5aaaoNuJKogzWflBv5jSjNOm2l6dTuSjmdbiazjO+TNGuMX0/IWNMVXFO6u/Qsl/6uO5SepkpHQWntxEdIDJuY8jvQXTKR9nVga5Vh2lN980LOF6z/lcSiK6F10igtStp3f1fXkRTqGkiWZSEJD13a5TDuq3riyE3UyGvhfgc0FzcKNFEQYTahDUHsjIpZZjz/53EX+LpBF+RhF2CgWd/TdTpDTYEPU6gyo6dqMEnOI/KXbjQipo8DzjhIy09ngPcjQLcCuO1dhMPuHhTyfq/Twdg/cD9hf5Oe2FBg7y7J55rd3SQVng5ip+BGPUhMjdmMQ73ARnV8VzRq/Qc0PbxddqEAsCdDu6eJkAORdbr5XNk7XWVlbyGFUEwkkuCudfPFcQSmiwtHubD3UyQ7PFjVXY7aNe/o+sU1xXBRfoYD7bFEofS6IzEGSJ5VHSwGjqSR+qdhKo0miqYt6uXekYh6uYux2AJbxbhzl4sg9WEqNwpKnCNnLcy5kXK2hpya7e/lusG74vPflLMftrhJ/SH1oyhWR92hVGxaqgx9MYMuMqznTa1PXRK6tsWkW2MwybsIon3xFJ2A0Tv0cozOEzpCCtwpDyRujaYy14lbmc2PiMSPMPHMF1SyA9LhDHA3Ro9IojL1Ud+Vq38Co0/GChrYaT5n10Vhh6xogx3SOAHKPfmZ+PhQbvO5rgO88Qivp42qmc4TN62ORK0fJqb9SKhdD2WafkVlUjHa/DFGy2+hZ21Zpi4m5ldQ4uWc2Okn2REn+0HivJPlrHA7TZv+cQCPGeJuIBqlOHF8XaZncmmaSc0HNzqmwg810xlFKs60PC9eT2zB+ntt9wN8szjZUdI0SGKN3pbu0gpWterUSS40k4lBfEinBfq/+95AuL+QW0PfOso+g9koNpAeIJ1GPU607rgeVzFlrx75TV3luvT4W7puMHX2AHzDwTyrvX6HZYOUPCyX8//2tR6wI8fJO3MViwWB6jRw+pp8obMwTE9cey8wX8aEMu7EwjO2zTsMchnBW3ztMoSQqKFoQo72BXyYwTU9D5+D73GYNwzHBnBQYeOSL76V5BX3OwLkFcsTlLxib2ZjumSYKXgwmdQTkgEuOeXQ0oOp0FLkg+sHmIMOvL4k4AK+FC5Dvz58NUIc4h1dnGk9LzP/q/hgZr71vMz85+4lxaZkEzKAnuT9d317+WlOwb54GvDX7qfvs8INu4RcBoxMf1KCgvkxb41kJr3AsK5FWJMUrHEIayDD+sks72xizgEmP2GJkIrWSObgXxiSCSFNUZAaICQrQjrMBexQAKA+ZMaTfCbuFQs7ihFY8CZqleG9DBw2AAfp7pLdTCtsbUck0bdvGxWugHv0Gldb1C6gM7YAqIp4xJxV03x2UAHTd7EKGYyWwSbGAAfei0X5U0GtvZmxtP4=
*/