/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_GREGORIAN_DATE_HPP_JOFA_080416
#define BOOST_ICL_GREGORIAN_DATE_HPP_JOFA_080416

#include <boost/icl/detail/boost_config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4100) // unreferenced formal parameter
#pragma warning(disable:4127) // conditional expression is constant
#pragma warning(disable:4244) // 'argument' : conversion from 'int' to 'unsigned short', possible loss of data
#pragma warning(disable:4702) // boost\lexical_cast.hpp(1159) : warning C4702: unreachable code
#pragma warning(disable:4996) // Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how to use Visual C++ 'Checked Iterators'
#endif

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>

namespace boost{namespace icl
{
    template<> struct is_discrete<boost::gregorian::date>
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<> 
    inline boost::gregorian::date identity_element<boost::gregorian::date>::value()
    { 
        return boost::gregorian::date(boost::gregorian::min_date_time); 
    }

    template<> 
    struct identity_element<boost::gregorian::date_duration>
    {
        static boost::gregorian::date_duration value()
        { 
            return boost::gregorian::date(boost::gregorian::min_date_time) 
                 - boost::gregorian::date(boost::gregorian::min_date_time); 
        }
    };

    template<> 
    struct has_difference<boost::gregorian::date> 
    { 
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };  

    template<> 
    struct difference_type_of<boost::gregorian::date> 
    { typedef boost::gregorian::date_duration type; };  

    template<> 
    struct size_type_of<boost::gregorian::date> 
    { typedef boost::gregorian::date_duration type; };  



    // ------------------------------------------------------------------------
    inline boost::gregorian::date operator ++(boost::gregorian::date& x)
    {
        return x += boost::gregorian::date::duration_type::unit();
    }

    inline boost::gregorian::date operator --(boost::gregorian::date& x)
    {
        return x -= boost::gregorian::date::duration_type::unit();
    }

    // ------------------------------------------------------------------------
    template<> struct is_discrete<boost::gregorian::date_duration>
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<> 
    struct has_difference<boost::gregorian::date_duration> 
    { 
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };  

    template<> 
    struct size_type_of<boost::gregorian::date_duration> 
    { 
        typedef boost::gregorian::date_duration type; 
    };  

    inline boost::gregorian::date_duration operator ++(boost::gregorian::date_duration& x)
    {
        return x += boost::gregorian::date::duration_type::unit();
    }

    inline boost::gregorian::date_duration operator --(boost::gregorian::date_duration& x)
    {
        return x -= boost::gregorian::date::duration_type::unit();
    }

    // ------------------------------------------------------------------------


}} // namespace icl boost

#endif



/* gregorian.hpp
m0d5au9KDZrSWE4YJ5YTr5kOJt2sIs3qsa9kX0iThQYiRzOumSeG0z0OHzxg8WQcQyyLEx9FDWGhgaGxZB+xDxg002izntH+USzVPFrjmny0X8V4l8jocPWvf2xV+ujpjl/tN7y46vniB/1kgaGhlClOPLWOsNAYuk8pEE8PqKC6v2IMKSg0uorrYrwOQDIZZW5GXU+p66UZxtkYqGsqdT10wXgIhlgM1HWzL35TMGRhyMUwDQPlPAUDZZ+6vlDXj0XIp65f1HWUumZuwTR1TTqEX+raV4xf6npl5+jqKWf9OXEiA6l9Z2udJuQ81s6hTbCDODGB0aFRsZHR6nnjYznREf7EWzSH/vWhen3Yrq5+6vNXsxRNWTu/inF3rXEPP3IOB3EiK05EkoJx8EMqzjO1RXpaM79bR2p+6rHDC+9zqUcM1W8Guw9eBLH7YYqUK1TTmCLvW0SaafWyMEktK8A/iB3NCYyLjgmNjMDuR8WGGGvajQoAcM/VREOqEjsPUaIXdT32tXPEC6gUka8d+gDwrzt+VPMyy4TiJLa6jH68oR53kkkPJPWUhp4JVDSueJ9NbRh9UCqmNRc8TNspWX1wUrOD4sKj+mFrkMhrdCRH6n7roppHc1FUTetcEJHXh8WiWsVe9UDjwKqaN2667ltERyoFcIJDI9h2cjJhXJHPiQjS5GqemXmk4zA90YMad3TzIJ8ak/F2nu6acQ9XNzKeLIHUdu6uro4dSaFqc+l6ZFukHdLpY40nIR7VQeCc5Uj1XnZwJJUYZdoltbFRVPelYw88jaLQi409Vr1UDKSDF8dYPFZ5VYQ6zng2xONdxVtPPO9KFBL0Zvs2t5NrHhybayogEODjKdKX+kahubcmUvJtTjWKnRwzkRWSFEs9s+N/OCdinKkNY9NrUz/satd1JKkihzSzJoe5/Vqb5q3aLqpv1Le5ugmxIYz9lvHEcvQ6OnJUBrzYCTy5oL07XU+nbpBQLpXIhQrShDyFgsdPSUd+RRsk4Us35vrIhjK3XbP96D/MEIhwKiY6khCWJGofkCET8AVCqUInT1OJj6/r5I70W3j6mpAulaH5tOuoN2KQ7rbhaFTadqS6t3pfyJQj9bTtayf3pvO05q9iG9IVNfuP7VTNo36MZ55xVJ4mzP7D+a45xn8675k1kBRkHytfHrWnfzSkKWW2F9Xd7Ix+OaG4tjGEqVJFrvr8pX+NGYnFSKaMxCx3YSRmeQdGYlX5OifR/h6DvKdR905XfRnU2xDdBwYqR3tB6BKgvpXDICfvcJNEvGScDuhDITn4pXsX2tK9SuSBhfQ9Y4ycdlXdFuolsdam1NdHjDERzywH9MwGHNIzy8FwCMN9DFFH9czKMEiP6Wm+NaGWU6X9pt6jUSOadVX2zSteYzv64bUG6LF9fDWT1BeD/8i3JNS6xIi4/5HvOqgXglJ8uviPrIfMo8Q8lad9kxAbWbA0bWWI4RDynHxYZnrquA3T6u+TjDAcwzRzOejIYuEtMGlr9SvjKm2fIEPKaPNKv/Pra1yFZSX99fegLlXZhiTV++N/5Fjg5eg/fCwwD/NY0G3+t9PZKfTx0K5fjDxXu4pjZIJp0vcxmY6Zb2BaswAqfwrzOCNNNTfzTqrIM6KGqbrHPgrzGZBSut/BCuWsKiSJnLxHQ+8O4jFEn4H+URz1V+ecIPImk9SjOtPU1yX6xS79bEx9pUDNjKSZXz0XM92/DeuMNA/bad+dZTZba3+XIm+necW+dZ5Kt5k9fql9X1P5vpH7jOb+rL09gZzoWG5FdMlMVtP++rixkSccULENx6bq2rJHOXM56G0kloQKurs+KoAT5R/tH16lc05K3pz/0b8=
*/