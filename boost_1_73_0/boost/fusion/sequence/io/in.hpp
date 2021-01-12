/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_IN_05042005_0120)
#define BOOST_IN_05042005_0120

#include <boost/fusion/support/config.hpp>
#include <istream>
#include <boost/fusion/sequence/io/detail/in.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace boost { namespace fusion
{
    template <typename Sequence>
    inline std::istream&
    in(std::istream& is, Sequence& seq)
    {
        detail::read_sequence(is, seq);
        return is;
    }

    namespace operators
    {
        template <typename Sequence>
        inline typename
            boost::enable_if<
               fusion::traits::is_sequence<Sequence>
              , std::istream&
            >::type
        operator>>(std::istream& is, Sequence& seq)
        {
            return fusion::in(is, seq);
        }
    }
    using operators::operator>>;
}}

#endif

/* in.hpp
yb+PPyLvjZL3nN79RP164QdFTt6T/fU1ef+RvJ/kj7fL+1TGJP8L5X0H8p7OW2r064PP1q+77tGv9dfL+xRc8n6jCXmPy7qU/1h5D5/U7355n0GrR96zU6Vfv3lUv+6W97rukvcq/O4D4s8XG+8nlvdDHBa/vEvk5T01f/mzvA9M3q/4FUXeT/UxSZf67d4t71E4Ie97aZb3Ich7n343LO+Fi4n8GXk/xq/0a1DeR/D838j7
*/