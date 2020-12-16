// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_AUTO_LINK_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_AUTO_LINK_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#if defined(BOOST_EXTERNAL_LIB_NAME)
# if defined(BOOST_MSVC) \
     || defined(__BORLANDC__) \
     || (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) \
     || (defined(__ICL) && defined(_MSC_EXTENSIONS)) \
     /**/
#  pragma comment(lib, BOOST_EXTERNAL_LIB_NAME)
# endif
# undef BOOST_EXTERNAL_LIB_NAME
#endif

//------------------Enable automatic library variant selection----------------// 

#if !defined(BOOST_IOSTREAMS_SOURCE) && \
    !defined(BOOST_ALL_NO_LIB) && \
    !defined(BOOST_IOSTREAMS_NO_LIB) \
    /**/

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it.
# define BOOST_LIB_NAME boost_iostreams

// If we're importing code from a dll, then tell auto_link.hpp about it.
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#  define BOOST_DYN_LINK
# endif

// And include the header that does the work.
# include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_AUTO_LINK_HPP_INCLUDED

/* auto_link.hpp
y8T/HLFXq13LNc+udu2/fK52f//lgLlu0iBGv4a1cuR3YYj7wsWwA/q1e0u8fpWpfk0V/cLmmWv6WORnhCY7jW06R3jBdW73lrrpHPJWnfO2251ucWWG0PdO1jiYOsC0xwNEpnsox2mkYcX3AVrBfiLXI9SC2NboZJFp72uuFZp+QaZe8/ZrDpjrsX2QfRb932/R/2rj37TpRvdPRL/d/Jyiuj0VfpZVYz8Dfieh3gfrlw+qtOv9VNG3sq+k93uMvhZpe4bdtIOqz7520JQFSUN/+VnoKz+0g97younmKRPSZ3A0zmHMIkwnykRVZWSPpyJKWFE+831anmq+acBur3Px6ztjU9fDW/TfyGpbpLIJ1yz7w9Y1ztZvK5C1roe2f1vhC/uc1g6/+Uw01PTrfiHu53nKVNkFjud7k1fFvdDpgj42wt6TgK8glXvDPmqOwPRtcfBvFFS/9HsC0tp/LqimqdEvyzcGWSrrXYudY1+LbfpAd3Z0+EXWyJ4CX4ON0IcZWyP6sCDyemJB4YWJ550uFdnRVt0gHHt+63zKns++/PI+kbk1bMYOYu8Xmu3MQ4Zr2Npsc6/1tOiU7R5mXjoy3uAem0TmqXC0z9b5Vte+L5TGSs71hHKDMyEU7S+tEtkcmz5yL/t7lpbcZwf32Sru68NjSOXTnMxwdCz8a7neysnmevQ+N8q1TKsucx//OxgZ5+3kHg+K203htqFBJs53yrX2Nj0nLNuYV98NEd6T4r5ZxmI5UjHOMuXA9f+8uC8LNzHvYqh3NK+ectORp8rUuL0i9hXeuTHTttws4RSGuzjPahmL5msPebZd+H9aZDaGQ6Hhnvm9SDXaUtOy520yP8iZZN91fuqkmHH3F3I9jbCi8eRzjPL5pd4y+4CEv4FnRSbyHmgRb3QibQv3d/0mt9R3QK4DP2nn1I10M+G6KtZc8/1PEu7ccJgcM/UF5QQZE++IzNtOROY5k4Z/l+txum7SpOpWiTMp0pprE7Pddq5vB+a3YEbOiq1mHl3HsOdid8Nti/1MDG2eeQd1ltqnw7Mx52DOxTDWNdd+mBV7HXm51o6/b4Ly3io5+HsrnkffWwUZP8a+g8qAse+atK6zvOfKiX3PJfqIHph2krTUeTFtJ1333thVB7if5HNyS70fFzV+kseRetTkPWEek/2+m3caF287m9zVkd9YHBvpe98U7pX1A2+9OreogBbX9p6lreprO5E/LtSb0Fdg+oWS7e+KkDN1YIB3MCrPs5nvEM8vLs2vtS+KH3/fVTOrpi/6J5EpYf18iqVes4ZBQidso428rT7pIG6jmP0OmfrkFq65tpaUk3s7Mo/SWedxRjHl07aJdQ4nGy4Vf53E7t7mXLG3VfdouMneeJh6fLq4pZp+Q4HYT/DHScpmF43XlMMj8SJWSRW70qem93UnmZiVIpH8cWyu92l2u8wjMtPUxMRzv4TdTuNCKywyjWLTS+uZv4pssTOduMq8usblOY1LRqOK+9OPSe+W3sWNS+OEafWOhNPcPP9LYs+xps17mq7e+7XvovdLrtiQfnRqakaLpIxw+7jnNmHcJWF0NPn+gtg3Oiv5n3B5Nk3TLp403eR442PS63bxO0n86Xdw1G/GxPXTsurwHnKx7z1kW+/8h7d8qZ8sM04w5Uj7bHrdlI3YefmXuzvyO6DvNfc7kXn57bdH6xam5v11irb3BKtybUw5M9fs9Yepi54VmXedcfh4FPMrjKVuISz7eLil5kGLO1z3tXxzk8436I29dYzxq/WPxsc/16LlX8JZ5ZxNXbMU452T13w3z/wLCfcdx9enMGNK02br3FV0XNof3UqjLv+cidJ80dmC1OyktPQ=
*/