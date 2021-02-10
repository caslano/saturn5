// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_VOID_050329_HPP
#define BOOST_PARAMETER_VOID_050329_HPP

namespace boost { namespace parameter { 

    // A placemarker for "no argument passed."
    // MAINTAINER NOTE: Do not make this into a metafunction
    struct void_
    {
    };
}} // namespace boost::parameter

namespace boost { namespace parameter { namespace aux {

    inline ::boost::parameter::void_& void_reference()
    {
        static ::boost::parameter::void_ instance;
        return instance;
    }
}}} // namespace boost::parameter::aux

#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))

namespace boost { namespace parameter { namespace aux {

    typedef void* voidstar;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* void.hpp
ehIICwEyb7QEDSxATK5gcESNzFn7WF/0lmHjprf2G0ey05qTklBCneGYRuMOzVIjTETvRpPfrv+Y0Lvh7e3wanJH17/S8OoOWL+Pri5w3gJMmvi+1mzArElUdSk494Tfb3j54wwCK/zrdMGh6Xnncrbu9TOqYjKO3NtOa3RipqoKVc2VrlJrhVxQhXrT92xaO64bWzeuYUugLEUqM/bWGws/dT8IcNrkDMrswK9hmwSMGQTIXrFvjAWInNu50KSVsmhMJaQ3tLFBtaYzKHaCzenZ8PbtnwO31wW+0oZO6QBYppmRQW2bQPoQuJcUYWHXnV0PYWcJ4txurQFOnfOCs/fkH09lZ+AfqZpleBlR58Tvd/D5eIAspo5ETU1W+E44brM2OU5LKSSD4rDdwatXcnhy+aa30eGGmIfdhE4/UvzP9If4yyc7TePJxS+3t9Tx8Mctqr/Acg1bVmgVnJBc4IT+a5Tlvc/Kt2Njy+vXu+3Hr2iYTufhXz+P/u6F/Ve9Z2pa3/yZR9RFW1pnYNg9xN1R7ymhw3QRtNfC3jxD+//60E+uIkJq90PL+ehfQiFTq/TzCr9R5dNKdyvPsg1st7NSGQ4vUchjEATg9GdYUfi5z7YlfNFSYbdqE/geX5mNgEHwCVBLAwQKAAAA
*/