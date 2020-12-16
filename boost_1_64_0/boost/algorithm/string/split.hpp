//  Boost string_algo library split.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_SPLIT_HPP
#define BOOST_STRING_SPLIT_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/compare.hpp>

/*! \file
    Defines basic split algorithms. 
    Split algorithms can be used to divide a string
    into several parts according to given criteria.
    
    Each part is copied and added as a new element to the
    output container.
    Thus the result container must be able to hold copies
    of the matches (in a compatible structure like std::string) or
    a reference to it (e.g. using the iterator range class).
    Examples of such a container are \c std::vector<std::string>
    or \c std::list<boost::iterator_range<std::string::iterator>>
*/

namespace boost {
    namespace algorithm {

//  find_all  ------------------------------------------------------------//

        //! Find all algorithm
        /*!
            This algorithm finds all occurrences of the search string
            in the input.
            
            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& find_all(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            Range1T&& Input,
#else
            Range1T& Input,
#endif
            const Range2T& Search)
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search) );        
        }

        //! Find all algorithm ( case insensitive ) 
        /*!
            This algorithm finds all occurrences of the search string
            in the input. 
            Each part is copied and added as a new element to the
            output container. Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            Searching is case insensitive.

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \param Loc A locale used for case insensitive comparison
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& ifind_all(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            Range1T&& Input,
#else
            Range1T& Input,
#endif
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc) ) );        
        }


//  tokenize  -------------------------------------------------------------//

        //! Split algorithm
        /*! 
            Tokenize expression. This function is equivalent to C strtok. Input
            sequence is split into tokens, separated by separators. Separators 
            are given by means of the predicate.

            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>
    
            \param Result A container that can hold copies of references to the substrings          
            \param Input A container which will be searched.
            \param Pred A predicate to identify separators. This predicate is 
                supposed to return true if a given element is a separator.
            \param eCompress If eCompress argument is set to token_compress_on, adjacent 
                separators are merged together. Otherwise, every two separators
                delimit a token.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename RangeT, typename PredicateT >
        inline SequenceSequenceT& split(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            RangeT&& Input,
#else
            RangeT& Input,
#endif
            PredicateT Pred,
            token_compress_mode_type eCompress=token_compress_off )
        {
            return ::boost::algorithm::iter_split(
                Result,
                Input,
                ::boost::algorithm::token_finder( Pred, eCompress ) );         
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::find_all;
    using algorithm::ifind_all;
    using algorithm::split;    

} // namespace boost


#endif  // BOOST_STRING_SPLIT_HPP


/* split.hpp
YQ5+8USGpfNLUWSYBqTqyDAnNi0xRgZeGCMTL4yByUatKxhuw86f4Xzi5oaO8N4O982tdMRpuCtcnxUY3xjStnoXGs3hvVlXT4Gpqs9d5GEKThRvnnXNlR7sJIwnNlBxE8HEkvjGIqKcXqUY9oer84PfRnPwphT0pmR0+cDDuwzFR/3gdFHAqoULNnypteCL9FbxR1jxR6QLvo79hL7IGM0XGeGMjFBxdYo2IhNhWTTfmWwfvcWWqBCz2jUdoegPcHYrCm8tITCdTlznd8/ph78rhetQacJ28ip8J6/CeKauOE9eFeuZ0BMiS/ls8MwktjuzIXrDWLbnM9dRLeHlm0GjGY8ZlGNOu82F7RYXylsGQTuiVcKChNCRzH8A3bDdPBvLGEZFu3Hxdt2LPTUVAd27IpJD24Www/F9VDzW+PHVUiS1j12Z52mRC51S5dbOTFR65MIkphsFpguB6YwbxoYT4Lu3US5iDicxVBaXhErB1GNPzGcWoMkqQE5jfKMnp5mqIHrx2OjF21EJ5o3YtgKGiY0AtX4U4Q0wth+qrbYm3JAVTmRdfRndB/IrYu0GYu17LdYOJBYrPtGsV0/nq4tfffy/8Ju8WUjCVagIsOuksago5hdYrP2RfsRdYDjZIaUzx9UhTPZJ/QiX/4CB/JErnQBlAERItLsKjIfQrBA5AkpmvMDPPGlD8Hci/krwdxj+cvGX+KknbTv+ClCiHvhLw9+OKzxp7fh7D39r8bf0in8/v2L/Lb/O8zg0DSjiCxl8Bnro87TTy9Cdr2p4+t0vNmLE0tHKGLV87hebfLHL0vF1OymE08D9ObqxLL4pL25m0BbAmp1Nekm8jN70kmpIKQ3vOcvKzve4X4xjOWhnc0ljWTNe9JKF9FxYNjp3ZzPSXaYbTfFN+XrJIuSVruc0lTULEh5lo12MU6MbzfFNbr2kUW9u0XOaBWVRWXPZaCfAi/RwKzrveHRe9OJKv24sCifSdfddteGNZ+vh2owyp4Gc8eF+sdpXVmAge3z4kbkPIIb4GZRr4Lmw5TAee6iaDKomA9Wko5vjnz8nrufU+KOZenS4MwToweyI+2K//bQXt5Khg4hloHk1GonaCkdE8OGLjaSmkv00RhPay7NzGVVZU8lirVkb3a5ry1FtPmONtlCPt7p9OWsIChGyfOeykuWEsl3XmhgljmTzY7mxNBLxKL3RRK25DNglTYTYwUkZa+KtebHc1wkLiS03FhMK0uTE9nBakMYbM+JmDhIJtyS11zeNRmmuODdXPMOv9blFNxZTq2hOvDVSOMI4SEdQS39ETWob94uLqX1AHv7HB7cdskEboam+4may7Lt3rmZtD1vKHSFjDbS5nug/2Apv63S6rdPpSqeTzfLBLAwlPGL4MD0fiDFjmBozFsFfBBTLQWxh8ZMx1vwANs7WDFPHCoSBQPcczNsimhEXZQNPHu0oeBDGPox5BuJD21AYGYwBCI1852UdsJH48/kzZX/yXJpAwJ3EK2z76xiy0ke326Arn78WxQiOX4epxCc4Vz2yw4/Z21GhMnIv7u4LbB5vna4I5FEQu7k2O6ra9NgwjIKQOidclZWbNhzgnoEhb99washYd26s4JDgznXkG6NssYp/DhAOD8S+5dA1KMiNPnwe54uckwjS1rBN6BpZcxOUTfwTbed6vWxr+IOscvecpaHx9cs7zosVeAw6+BMoaaR4kXTsOehXMX6h2g+o0g/1SCCDRMCrkILwI1n1QUXspj1sjiWLazB2zgzpf+45oxwVsXKckXAFYuV7cdogp1mPjnIKPUrMUO0ZqD3w81fJq920l32aRLj49RUyZ5FlZ2xrbKFx/xqdndKzJ8E=
*/