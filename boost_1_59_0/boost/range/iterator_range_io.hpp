// Boost.Range library
//
//  Copyright Neil Groves 2009.
//  Use, modification and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ITERATOR_RANGE_IO_HPP_INCLUDED
#define BOOST_RANGE_ITERATOR_RANGE_IO_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
    #pragma warning( push )
    #pragma warning( disable : 4996 )
#endif

// From boost/dynamic_bitset.hpp; thanks to Matthias Troyer for Cray X1 patch.
#ifndef BOOST_OLD_IOSTREAMS 
# if defined(__STL_CONFIG_H) && \
    !defined (__STL_USE_NEW_IOSTREAMS) && !defined(__crayx1) \
    /**/
#  define BOOST_OLD_IOSTREAMS
# endif
#endif // #ifndef BOOST_OLD_IOSTREAMS

#ifndef _STLP_NO_IOSTREAMS
# ifndef BOOST_OLD_IOSTREAMS
#  include <ostream>
# else
#  include <ostream.h>
# endif
#endif // _STLP_NO_IOSTREAMS

#include <boost/range/iterator_range_core.hpp>
#include <iterator>
#include <algorithm>
#include <cstddef>

namespace boost
{

#ifndef _STLP_NO_IOSTREAMS
# ifndef BOOST_OLD_IOSTREAMS   

        //! iterator_range output operator
        /*!
            Output the range to an ostream. Elements are outputted
            in a sequence without separators.
        */
        template< typename IteratorT, typename Elem, typename Traits >
        inline std::basic_ostream<Elem,Traits>& operator<<( 
                    std::basic_ostream<Elem, Traits>& Os,
                    const iterator_range<IteratorT>& r )
        {
            std::copy( r.begin(), r.end(), 
                       std::ostream_iterator< BOOST_DEDUCED_TYPENAME 
                                              iterator_value<IteratorT>::type, 
                                              Elem, Traits>(Os) );
            return Os;
        }

# else

        //! iterator_range output operator
        /*!
            Output the range to an ostream. Elements are outputted
            in a sequence without separators.
        */
        template< typename IteratorT >
        inline std::ostream& operator<<( 
                    std::ostream& Os,
                    const iterator_range<IteratorT>& r )
        {
            std::copy( r.begin(), r.end(), std::ostream_iterator<char>(Os));
            return Os;
        }

# endif
#endif // _STLP_NO_IOSTREAMS

} // namespace boost

#undef BOOST_OLD_IOSTREAMS

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
    #pragma warning(pop)
#endif

#endif // include guard

/* iterator_range_io.hpp
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
*/