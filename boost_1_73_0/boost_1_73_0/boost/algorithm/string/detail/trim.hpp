//  Boost string_algo library trim.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_TRIM_DETAIL_HPP
#define BOOST_STRING_TRIM_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/detail/iterator.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  trim iterator helper -----------------------------------------------//

            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end_iter_select( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace,
                std::forward_iterator_tag )
            {
                ForwardIteratorT TrimIt=InBegin;

                for( ForwardIteratorT It=InBegin; It!=InEnd; ++It )
                {
                    if ( !IsSpace(*It) ) 
                    {
                        TrimIt=It;
                        ++TrimIt;
                    }
                }

                return TrimIt;
            }

            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end_iter_select( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace,
                std::bidirectional_iterator_tag )
            {
                for( ForwardIteratorT It=InEnd; It!=InBegin;  )
                {
                    if ( !IsSpace(*(--It)) )
                        return ++It;
                }

                return InBegin;
            }
   // Search for first non matching character from the beginning of the sequence
            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_begin( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace )
            {
                ForwardIteratorT It=InBegin;
                for(; It!=InEnd; ++It )
                {
                    if (!IsSpace(*It))
                        return It;
                }

                return It;
            }

            // Search for first non matching character from the end of the sequence
            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace )
            {
                typedef BOOST_STRING_TYPENAME boost::detail::
                    iterator_traits<ForwardIteratorT>::iterator_category category;

                return ::boost::algorithm::detail::trim_end_iter_select( InBegin, InEnd, IsSpace, category() );
            }


        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_TRIM_DETAIL_HPP

/* trim.hpp
bGDF5gT8OHcYCw80HQWh7HBXGk4sEM5KazdxFsGt1/jIWxZfqXTLjhFkiQtmeii9RTeLuswZQYW1oaBYSk6ae3pjtuwh791QP9fwyRk6nJ1C7i1uJ6m1vQr8SOGYDlyJVbl2P0rcvZW5+0HqbqAl1HX9In8zcnbqzi+aj5H2PPHeRWf7Jp/tewlt1cqaKO3wktf2l4gF5IP4asvnlZM9f4f5AB/QpnZY8qO0kdpOJ4KPMg8nPqElHfFoOGmDLJ4eSyXBnP8fxBGa8q6B9Z4wPpeXU8G5vLCKLXt17zSWL8q0YsV0BMLjQQfPHuuyJY7Y5kH8iCcjDZwnnkCVVWEjqfnSe+lNcWCkMBlQ6npQzwvnpeCnPZe5JnO4KbHNXNyZbSdDuFeyZa6H5/WwM1EuwS8P19c1fDU8SasnYYPaQx46U7VQL8tkHH2+3iHylcP3XBEJzC5SuZZkSFXK7XnWMX6eboLr8Bs9gjszJpt7AOT6LjakRx+Si2bjGPDIkPQTjvC0P4L5SW+qJ97Ab3tTTd7AL3nD9CZrptY/WMIr73Qk932Z0Ecd7coJqOEvz+dAeLNmm3SR/eR/UpX/J8nmuvofUEsDBAoAAAAIAC1nSlIrvkeb5wcAAIMSAAAXAAkAY3VybC1tYXN0ZXIv
*/