/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332)
#define BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<1> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
MI2pM/odM7SQwZiWvOoxHTqTn+NhnmhDmO29nWGhsDBaL5O0OstvNhXmzx+9TfTMMXo3xaEVZnan+0fLKM8CanOi8THbl56wRZhXF0efYaIFDCyM1lwau6bF2gtqkInV9w58g6i+ONrH0KL3sZCBQTzuY8z4PuZEe5BmBdB2jln0XJjHqsF6ZnlC5+dQnjaNrs8KotH1GZrbwDwG5jUwn4H5DSyA5kqzODR6houmaRr9dmY82smDb7dSLmhtmT1f+iPFRdBKMutzcuMCYQ672jxoFZgdP77khLAgWiVmpx++oG3ekqCOc6MVZuafGLZTz9BqMktu4E6lGtB47fty2qrT2n4UXfu1fNnJgmi8vrv3V3qFQSG1OdF4DbXvbb5EeaLx2j85cmyCsLBBnKNwdO30m9NobrSavL7+rV9RDWi89q5F2o0VphWJrj11+Yo5lCcar69Jzg8fCgsZmKVodA1/WorspDzReO3PytT7S1jAIA6KRdc+qUvn9tQXNF573gXXFlMNaOJ8ZEUbO6Z+Sao9Mdr828sfo1x0NmHEq3y0tsU1GMrsZK9PAtQXtM+YdYYPPhTmSdKgJ7MmIyd/LiyC1pxZ7dy1D1LPSmgwg9fwx4qW1OuS0XHHcxe5IMyLNphZhTpLrlFcKewns+JTJuWg+nS25aq1FtWAllUae+6N86GV5zVc+Lgd9QWN9/PzOsFeVF9pDVw8bn/byhSHppmkZXR+c4ryLIPbLosb1yolQOuHlk0ae+aPY6KlmtjaXmm7g8Ysp8EaZk1/37lPmKu8Bq3N0nxBWz2Kq6RBcRa3odasy8KClaPX/fb6HI0prgrWwOLufO48ICxSNdq0wxUrCvNX1+AUSJv8zN+Maq+hQTsWt+N2jwTqdU15HYImP+tB8+pMvt+D8+lM/oYp1qcz+r1YtLDO6D0kNKgVbfK3T7FWndE7Q2hOnY0/Wuczqg+tLLPhL3u7qAYep7sGC3LTXfOFdUa/M4sGtaNtZM3l26gGncl3orAGncl307AGtGLMao3/sCPVgNbGJO37ztVpbV11NCjN4hZvO0S5+NDyM0v86eYeYQGd2RtUGSIspLM539muC4vo7PfxYzcLs9SNNk/HF7TtOnQ28+6npakGNL5+8+fdfUs1oFVlljps3UlaI7SSzOh/GNG0etHzjTqlRWgddDYl4XBeWgedXXqypqcwr86+GHDgLq0RmiqXsIFp9aPHPO+I/YTy1Nn1PVcXUp5oyu0FbTGzu/m+n01xDfAamhm/hvah5WXG730DaEnM+P1txMAcDdXzudFU83kN4gJoylzQEpnx+wBHI3WcB001n9/AQgYGjdXzOQ3Mi6aqIYim6lnYYEytidrcaFuZdftnzmLKs6kGfU3S/hjaYYwwi0uDsRnemw3tzbOLl6if7ekaBS36/i+MZmfGe2bpgLUz47W70L5Ny0VD61Kh1iSqoZMcU9Nv12jONLOjXb7iGUe5oHVg9uBJk2U03ycadGK28MAJeW1jYK7OGpRhtmevKUK5oC1hFmxTPx3FddFggElat41TKU7riscQFie//4e1o7VnVu9Jwi7KE43n8ve577zU624a1GI2cVrZWFo/tOzM+HnMh6bKJYRWgZn8TiHW0B3vA5jJ7yLifGiFmdH3DdH8aBmZ/dnzSIKwANq/zCJ7PG9obXuoa9d68vmin4e40Hjt/JrIo4sr+/BAPOWJlpMZvV+AFkRrZpL2sE+ljDRmLw0qs7hWScvPUByayCVBdx0S5qa7XoLe3KKvwTSdNS69roQwJ1otZsemrY5QfTxOd80XRCvN7Ga9nw4Jgz4aFGJG73ujOdBUNbjQVDV40KozW3y67lvKRWc=
*/