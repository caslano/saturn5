/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_05042005_1144)
#define FUSION_PRIOR_05042005_1144

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct prior_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct prior_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template prior<Iterator> {};
        };

        template <>
        struct prior_impl<boost_array_iterator_tag>;

        template <>
        struct prior_impl<mpl_iterator_tag>;

        template <>
        struct prior_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct prior
            : extension::prior_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::prior<Iterator>::type const
    prior(Iterator const& i)
    {
        return result_of::prior<Iterator>::call(i);
    }
}}

#endif

/* prior.hpp
DOln7vJdqN3W15KPwxusH7A+dKzbERLXa+O37wy5T0u7a23oOHH5ftrOUGzeGdrv2RAyCfsoR2d+e8j8aGso2yZ7YGOofm5NiMl/u/WqEuftDFV13CG+OqxPlU7K9yv80xbtUd2wzm9LjZHNm0Pqm/JWjvvftdL7sxj4iTa7Wx2KidTeVc7fm/0eXfripLxK2RyvWvZ3v+ui0+Puk6/3W/TN5mybfUaXsF7HuhA+IbaD2HyJeta+VWvUJVY0hbDFtjXbZjf6n1g7Q+H2Dd7fHOrPXe/7166F/e+TcrP2uFzs5TeHonhO3Gr8vn97SMl35z/F4WdW+y7TllAtrTMeev0dO0LxejF5yc4Q/q0e5CvVKmZP2xAKPs+pVjeH9PQmn++sC523bAjhsxtC9tQtobwgzutibcm9PWUuD4uTM5X9i9vF7gqf2esfY9tD1jrfuZfuDLEF9TVufF6hje6y3c36wj+U/wxxPJYI2aOP1ke3hdylyvW4tn2rdnrjJteVjvNGbSA2Ooa07adW+23wBvcUxKH6rqfU2RXi4qtiS/ylltv817t853qN7y5vDx29sVB+lvZ8rraTbrVto/V+YqH4SDy0x9TBq2OhIIYyvxOPl0rn++L8OGW/Y03IHYha935XiJ26MZTfKo2rlfU3+pDPizvPVAfrV4fcZdZ5+p20xGjmstU+998eYmvkyXVI4cGNfjO5O2T/uFWdaYuj9SPHLH7Haxc4/vuSIaz29/JcLqePX6vPJuTlHO3xXu89EvU9ykRIXL4+FCra6t8bQmrb6hDEdvFgLHTYL/PZ9aHTe9XampDq3xLqo+tDcf2mUH1oh3ti6ie22nfM5OexNT6/sj7tiVu0YdwaDcp1vLoeWxuqd4iBNatD4RR9oqDNTt/4v/XyijnX+MtjoL8LY/5H1MlH68vW+FvaFFLG9Nx5G3zfRfpN60L5RH23Xf78H/zE6eJyfyKkzpcX6x/VHzNmfV28yEfs1WJPbPsrtP99a6juse7unL79gZj/kdWkDsV53Zp+xob6sU9SV8owvDwGOf4v9KVTNllfZU0I/9wcMvs2+f2KWCpvDOEZ8v4S2z642/8Il48bxfGjXtMW1W+sCdW/6HMx5wBtFdu5w2fOG0L5yf4fWc9O35XTfy8SozcZQ36mno/Td06x33Vi9MXGp7qyX5T0P7Zt+0nt173D/36QjjiqRpzrzl1eV8n4MGT8vsTn46fYft3y/zkTEwe2hOzVXnu/vvL2zaG6UV0fv814o8zTxtOzjHHiNaw9St1tcg5JGoMj1g4V73POt2t3ubdu3I8Yqz12nLE2ZPaK3Xcq61na4Eh983na+1fa+Y/isy/pnst2dRANiUft2yv/z97s/986531Uu7UbP2aM+QXnqF+pn9XGav2z/Kh+nhVHn90dOj/rcZtz3thK+dHffGYTblAv3xQ3A/L/87WhuMW58AZ9sE3fl+f2++1j3cyEuUnxVOe3M8T7IXHc6nzwyeV207/uUt+Pb/U9GzGzKK/eLxxj3H2f/n52MsScNzv0n/oF/h517pwWn893fjvb+WpI+hfvCLFT9NcbtPd3jQ+XO0c81TxTm9aHxe/jy/OMneJZWrcYm6+Qztvi0jBe36QPjKvna9aFjHgtGgurv9EH3Vdt95l1x0elc60YdfysMTEYu3JbbHee2DFfCC8xT+h2XnrRmpD5XFTsx0LsKmW+cntIP9WaXM471TesD6maPGuj7AFzjePWmbevkM4K9308X16P9GHngMfUa8pz8dP+4FprIRjPn7Yu5M4xLp2mDx+UD+fN+ozzZKf8/sFY8jr1KX+5vPc+Fw8ZfaPdZ7aJu/XPf2uP9kbnff0=
*/