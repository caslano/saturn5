/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
itl_rational provides adapter code for boost::rational.
------------------------------------------------------------------------------*/

#ifndef BOOST_ICL_RATIONAL_HPP_JOFA_080913
#define BOOST_ICL_RATIONAL_HPP_JOFA_080913

#include <boost/config.hpp> // For BOOST_MSVC and more

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#pragma warning(disable:4512) // 'boost::detail::resetter' : assignment operator could not be generated
#pragma warning(disable:4800) // 'unsigned int' : forcing value to bool 'true' or 'false' (performance warning)
#endif                        

#include <boost/rational.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/has_inverse.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>

namespace boost{namespace icl
{
    template<class Integral> 
    struct is_numeric<boost::rational<Integral> >
    {
        typedef is_numeric type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<class Integral> 
    struct is_continuous<boost::rational<Integral> >
    {
        typedef is_continuous type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<class Integral> 
    struct is_discrete<boost::rational<Integral> >
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = false);
    };

    template<class Integral> 
    struct has_inverse<boost::rational<Integral> >
    {
        typedef has_inverse type;
        BOOST_STATIC_CONSTANT(bool, value = (boost::is_signed<Integral>::value));
    };

}} // namespace icl boost


#endif



/* rational.hpp
CYuR/6T/RnW4Frqq1PhXr16FMWPGQMOGDcHY2BjKlysHdT+pxeYHmqNonlTpOCiRD6RrouYD6X/dihP1Ea+dhet71pQaf9++feDo6Ai9evWC7t27gw3KosXXX6vnSYbP9W5yUkV9Vab38+Caug5MBy4pFpL2ris1vl5Sz1FZDP/gT0RdBVRUQRcGQXJBQmTplI5dShoJFxCkpJHuEOkuiaWWRjoFEWlEkJJml1C6pGHp7ob99+9z3s7M3pk334159915Z865bwxQS51XKGsm1DeUd13HA8nwjoslCkp2jCIA3+enf3u3uS49HswsvSbZyrljmhR/sO/T6GvmXnuVZZ4yDPBJP3/9rlLnve6u0kZUc6PqEw75CYmVQ2HCXRfFCqxz3DH5bvH5GLxkWLv1qNOFiQaF0gsB+wAVJVpHouMio5d7fdVM8C9itDRjAOZE1ATKOwD13EnzHEVPZMZ5Egw+kWF/Hn28MlW4n3z8k9fV9hC7PpSNoVEttTS2x9Nli87Gj4nBTSfAR+G7UuicopcSnD33xWqt2lXHktGJ+JrjFBN37vSKgTldBnFaqUrQ5hZf/5VE+rCt29QaKu64ktE1hw1VubxFwr0m8wf1pudhSW8N9Xq1PffxEGrDQXpeqsFI4OFAh9AVtr7TYNqLU+/8dFrnzx/d0xU6pDz1uPEzz1UF6fm4RW6q4ENqBjjSQr4Tl8hYp0r+zw7j
*/