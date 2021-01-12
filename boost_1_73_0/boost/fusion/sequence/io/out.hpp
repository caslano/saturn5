/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_OUT_05042005_0120)
#define BOOST_OUT_05042005_0120

#include <boost/fusion/support/config.hpp>
#include <ostream>
#include <boost/fusion/sequence/io/detail/out.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/or.hpp>

namespace boost { namespace fusion
{
    template <typename Sequence>
    inline std::ostream&
    out(std::ostream& os, Sequence& seq)
    {
        detail::print_sequence(os, seq);
        return os;
    }
    
    namespace operators
    {
        template <typename Sequence>
        inline typename
            boost::enable_if<
               fusion::traits::is_sequence<Sequence>
              , std::ostream&
            >::type
        operator<<(std::ostream& os, Sequence const& seq)
        {
            return fusion::out(os, seq);
        }
    }
    using operators::operator<<;
}}

#endif

/* out.hpp
g+S9gBe/wXhfjrw3Zlri46XS3l8TeyTfy94q7f900efUrw80y/tCVP16zx3ij/cZ7yeR92vJe0t/8RH9evdVokfSU/K+5Cv5TzZuJC7ecky/3vsHB1f4u9hzt7w36AJ5b4m8n6pK3s95Wa1+PXSvvH9jScq5WOJF9Fws7x9+0sVSjrx//JaAxNEF+vU79+rX7gGJ+1H9+v0H5X0hZ8QP90u8VMp7ZyakvRSHfj0u7z16v8Rh
*/