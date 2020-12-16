/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_05052005_1141)
#define FUSION_LESS_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_less
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) < extension::as_const(*b) ||
                (!(extension::as_const(*b) < extension::as_const(*a)) && 
                 call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* less.hpp
rCC3iGrCIfKNvD+T46BIyPD4D/+9SemyyvV6Jm7iiOBfyIcE3e0yHizyldgLOP+OiY/010FcIGZZxzGTLNff8wvGvwejcOGrKRsw3iK5mO6PDB9tTYSyyanYORGEdTl6IvHpPQSp6v3Ydf/fe+CD1fw1y3tUipXRCZLQgbk3WlnLr3pJ4tL9IYYXXdoJ5NKov39TnsOvmHQ39noiorFI018s1+YvH58Eca2h7CnzLWTGXBzS/OXjE7gJ1kbbGcpAIsIp3NLtXbs/13WDmQTSvxygjOVxf6yax/fneoF2iGqSzHJDN+LoHKE76QMYLYYr9LqZcXVDLxie67REFf2BB/A+R8wVxIlIYl1AdYOUHUSXj1DNeUaPTo9yFy6uXYNeZcd9ktqyjIYcVuUUrJwQcaCzsOjmHeP+ZqwKq0WH1Vy4+G3TrzPp+UEaYQnKLtd3+ckD2DgFYZRFkRkwsBqqqhLiV+tjzz+A6xijTuIXiSCPxdFvZKZoTbtKx/IAfv+PI+Q4dVNDgUAxapojDuDOTueCWdaxHsIWYOQQtqkWM3CV4o+Y+CI0NV5ucoRPy8TjAac6ivUoz38W3yTNoxyJPDW3Nd5mFLeEtdPDW0q3l0Wh0c5sy5gOqgh6Q33gfQS9fZDq+6TOnXG+xNWnm7xHAl6Vdb2EVxsI8nQPdjZmZEfyrUM4D+4r4PzEgM36aWQL0jFNLBxeD3BwYggcvdPX4ZMSTtuuBENOEbkrEaNHSigqLojvrrjkV6tyT/5V5b5EPhOpHi/pFx7bTK99bSu8/c14pchk+uT+2ahH5QDdC1qTMMv9QMH+Af7rhZo6/o/g/h0sNI2nqFnjHVwgPGvcmd/sXDx+h27tEXjU55adxQaHMzuLn3KYtLMgW1rA9Jyr383fV4fT3VzkL+Kw+h14RnA+H5mPhoVDPFA9p25q45jx/q7YcOKF2nkzgaPntNXOGpy1cz+DWXYIsxJen1EUnlPL5TcXeLY980fE90oPYM8Dg8foFgqPxpJ4/CnB9HgwndAtCc76ifqosp+VOLqtbK4KuLh7z+WT8ntKPJvP9xGsmc9DtyH4XD4/SDicT8rFedsKvt0XD7TYL427699LWCXBkE7GGKMLtyvhEJ/7kECNO+/txfdq7yU6o84rdwBc6gCq0g3dwh01TN91NO3n7wS4iNlC/Oo1dOzOgDXnJCOcjzTi8DvrkQMWjpVr7LLEmadrOHIXwP8HXcNXLDxb15DcVeLoadCoa7hk4zGeDt3Ngjfy9Ekbz9I1PP7uFo4Vz/MrhMOmZ6Ov0UPvYeFa/L+vGceK0bl0TwuP8ZepO/C9+duXnyObfPD/5xRSstbiwIy9maf/Ju3aYqtqqnApLZR7RcT6i79VUfFekGLxxr6ffd9bWhSvpbQHe/xLe+w51WpMJMZEH0zkwQeMmmjig0Zi0PjAAw8kamIMMRpNRKMGIyreUVHx7pq9Z9bM2rM30EiC8p/1rTVrZs991gWGWpSERZzrqvPLktjPHVR5Jh3YxJumbbJXX4STc8ZFVefjGSRta5luBGXwcVZXxqcJj+35iQVPGjLO9ETJgLGaLgNezcefe36UOIbjnsTgLoj9ioqdDDKwv0u8zGAjR4BN9l7xHuZn+im2NC8X2aJLhyzou5x2q6AVpCWWhEkAWL6z9wOdDY8BkfOb/zd3hsM59y78dVQfRrheLfwQmVhlbr62qQFXqCZxHx6kOJZhuk7ezGYdp8p7NsampjgpS2JGhzWMptfNRgwkjwI6rnNbKK5a1ie31tArOV4WRiiGu3wi/cA2Sq/WeWR7lY6FIOYOx6AfKO/LxL91B8WIzNDo87FT0gV/9c3i2wQDMmR3w3I=
*/