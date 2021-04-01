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
rnnR85nkimcs+zc6UPh5sBVyUl0JQYAA3LDYvaJvFZZdbfakn8tMjOCE0Ob43gzTxydgvcihrZJY023oXRbi4uMDDpsbpjXdUS206oDtHDyMMbE1PLvWbh3mU+WjP3VW4jJJWCDynIvC4ZiXg2Aw8MWoEwClVtePs7ZCmPyHcsB6FrDvN5XsHqy4i9ndEtqehVCA0PkW5AxSs/EVl3ucmamxdiNFzMGploxsWMPLhBKnfbVQVtFLx1cLNTLBsxDX6GX60h+c7SfMbvmFC2cY+zesvqhrkpxLjW2KuKsWuPRrWNeJswuOUdkHGP6Y9E/2JvfF1o18M8MRfp94aXqGzhF34WdFjarnbS2i8AQ8rPNNK7QW0EWBg3MCMhmaEspGUFnwiO8paEWidunIFSzTPi5AS5339bnKMdXMNG/EHuy9jgRKFIqA15cXtbSGt3g2wk2XT936KZzuIkXWrzhILIUQbDinqDlSYmhilP1N5/At80gTDhO0Nordt8NG/LHCa2PlF9gLM0b/n/7wvegGleHPIQVv1RMCY22PMCMafyiympKfv77PXJAJdA==
*/