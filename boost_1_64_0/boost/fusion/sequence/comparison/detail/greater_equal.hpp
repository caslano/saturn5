/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_EQUAL_05052005_1142)
#define FUSION_GREATER_EQUAL_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater_equal
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) >= extension::as_const(*b)
                && (!(extension::as_const(*b) >= extension::as_const(*a)) || 
                    call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* greater_equal.hpp
8pFgtL7I+Y0UrF7gTBRtjdK4Y0UmbQ55vZMjQ5Xj2stB5yo6+XC2HpI8hlcH7mWuvR6OZ2oNPZLr/sKOBxE//r/fEMUbyZ3E28m7xBuJfjybSnudY7DX0VmE+/hVHM8apoPeykPdOGe+h5+OvqMbqCtuOwnoXp3cy9Qlwlo2DIp2jm1xZ6qWC+HuPszEzbvIOYYdx9lpwl03+/XRRZh7SYzZLRvI1+2uifuYTjdyfUT9F+F2eKJ7upfxcY66CP6fiFhF4iJ45AwOPvEb959568NrOV/8FCFuUkW0PdzAMn3+sDGP9qWH1/LvIA19kSA9gPa7Z/czys3O2gW3hBBBsBKdkVLiB2SrbeInTpDEvQJ6YKMa2SY6n7j+2osyhORzA9FzPirZHp3eEXtPISqb1vw+H8Hb1G5DgZHmJW1fV7hcj910kPmnIzp/gihTkbM13jhnxldcVvPgoSb+owooyYWOvcT3XHmeUTypGk9hlrYxabISe7q1OWSzR+e0L0w6qL0CD/bUXZFartIs0A7V0rblp7iffTuOMygWypoGsxm1g3ibSHzKa55BE4GnAjsmP38neOUjantFG1Xl3v/tv6T4vsz4RkpWD+oQ12GTHmhD0hE8gu9vnQDPCkix2DDhN5Tu5KqkoXM0bntZJ29wuLfCGEzUuP+dj3sRpt08yMv+deW4e5Qfa4nnw+65kQ/7dV1fWKYGFLdYUSmNTVfNySW+DjoxLhoZcuZRASdka2UhNuePoZxZrCwIHQmSQQamP36OJsjQlkeNw3pKjD0mVHNsieenRPpzbDlJXi/Lc62SmJxynpXTBk/t2M97hkNILGd6dYBL8intfUv1vS9ABjEoEqvql7dE1K4TbG25ZDe9xHOIxXHcRbr6tN4Gd1ZtN8PmplBblp7X4v6pSHWKQ0QX1xjpojVS8+rKErOph3zdgxTPmPdVXdeW+H6StbtxO8kCXVkZ0S2uDhmaWSNxLv/icVgHDxD01aZDcZAA+8wNWFcPFLDaAdAf7Owa/uqtB1k4pCq7p7Q7ntRxuD87DlQBr23K+tJb4n0JOrmixKPdiJcndW6fukHa8IJNRLUvv31GfpNpQ+hu/Erce8OFer3crvfPjThk10u+XTYOj4P6vRKn3k+8LmdPEw6v6zNNOLIuylWxl+PIakgf8vI6HFVQ7OgaTBatfTn31eBTYXMxoXhmMkYycOxxqusmXjMPb2S8wd6sGaceX2CjxCujHNWypLRYno+w1F/Uxor6TtgSSxwDbpbxVg3nY2DIpUu3UDg23yzvQ4U3GWOiVnWQbQe+nxV9OtWNEf/UfDz+VsApdSzz23KZcJrb4tzagltt+Qrh/Oe2JLep8LarSFP0/dht1fcRvmq9yJ/Fd2kfTcKiYZ/xlUUNPwvJoWXANm5HMLpNkD7l9gI2HVal9stiZaA/on/lHSQOURsxXe4I2H+K6SLg/8Ob54vvZOFZep29N0gcNq3td9h1G4/x9FMb3sjTxp0tPMvG5k82DvFNbTsgcP5znorrAud/yFNx/i42Xj2+1f67WjhWLos3KZxagiXJlrZ1v1sznsEalXlxDm49RvFD7w48oZ8r577+/sF7yO/V3Kc7zfn7cd0Bnq+7eY7boHC0RbAND3fY0o82DihYAcVgNWmPZUE7zNuRdBsf1XRFHzRxE4QlyKCg6MaOSERTvgVOOf5nOD5YKOAZ25MhFMRrfC1W/MZNDDmli7hfkFPo5ZaX/XXGN7RrLsT0Enl1MoXvRP3+e+V+/K2wcCM3C0sCcQdDLJKRzFWu72HXTJpHJ4EIJgw/4Ilor+ob0kWauAWaCLkpSnzZ1ic92U2ovfoN+f7srosIVj6S+1Y=
*/