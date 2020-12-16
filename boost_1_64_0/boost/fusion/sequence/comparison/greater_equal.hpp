/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_EQUAL_05052005_0432)
#define FUSION_GREATER_EQUAL_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/greater_equal.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    greater_equal(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_greater_equal<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(a < b);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator>=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::greater_equal(a, b);
        }
    }
    using operators::operator>=;
}}

#endif

/* greater_equal.hpp
EZNuW7ykyRpJDmZ0EWTvJICBZ1vTib16OED30ZZv+m5PGD3MzYW9ZJyTH7/RYbyElr47XHh6TbbpZu2460W6jNF4HWLDbDBeHcr6Kf7E02txX9wuAgF4Bv+jCd+S9Zq7zGiFfXcSxDHukUS7KfxXJ8JXYXuNYmjRWX7VpIf5sxtH7QRzh8j1Mj1Ksb6yfbzONAzg7O5pIqErxGhtn90RobtVnSRX8/ZCgHARtMoip5rZ/vQMvj8hg3036XYsYhKUDFnicrdlnnthDueHJOlqUpqU/Aw7+Iy67Fm0s17Q4YR0taP9+BijgwMTlD+4oIWSjg5NjC9dD+uy5EmUYfAMPZwLyZemlQpwRjHpaE7X6g7cIut0u9RYvZLtukM1p1kZmQO3GdwQMmM9QnGze46Koo2u1obP1PovQKAheA0YjZjsbE+2pmpdqLn5vWewuRnGbRHXwuj26eDMqDbGV+t1IcBA7PWMupi4SDEJ/8z7OXfdAFcD6i614dH6o7hlz+TrHoqYIo8wH6VuVcg4W2t8xyZ5KmmZ8knQSSCIRYmzCVp0I01i5o/H6suhAIYhu5/0nPFwKGbD9tkB1M+D6ogdjOtzk9Zg8czaOoL3GhwT21ASloLGmRHqh2p8cHqgxmWH7oHPrMsp2AGSTlTSynYzNwF5TtE98Jk12bwDIbmTpYx+bTiDMntal5EuPpOf9R3U3EtCUff8KY26Vf9dfib3h8lxPuZREoOeprNgXRe2gRNnB7lYBEv6rPrg7k3Y2OWdXicOEhTDo2zI+s/R3lfrd7xGuIELZbkglPfYWuMHqu37n8X7XYTHQSyzwBEe2QMKdCPI8f5JAsaA/KKexddGmnegeMGBtzVbH9oi8ZqScZxncRkHp3kIZWXs2F1EorFmgcta68+q3ecCv427TkJliZcYHjCH4uWcZ3xAF9/23SwmPjhtnRdH72uXWDm508XFqQcjHCrnBevDMc0G3bjtIcI8GGvo2rP4PO4iWBv0d4WjZVwuNRrxclrP5nurB51UXuQF4rUMTiuvaFw25ywIh/YDVk7i5G2Emuu688sRs5KuHrqc6Nk1Xx3oIOE019Nxb06PZiT90NFuyUGTZ/M+yXMv8oPEo3Lsu8emmt+vfHZNz+chyB/8pyxaEujlHk7rYw/TS+CoCrtRpsn5WblJ8tez6zGrUshALg+dw2lduvMXLX4H91xIzV6PE+uwrSSLmHWKKVi4qXijEfGmxKBh1EjPrHw43vkgdPR7hQ+HVCgYnib3AXz7CTiPPsDh5GlSxSWmWBVP1/Y1Elnbzqg8Wwe/d18rz9YUL5OUfcrw7z61/z/k2SqJjBzeVbnye39DvD3eoOr8g4BJCpFbWZ3rN9XlYyZPxEu9gp3fq2Ei4sz6ts4xfJLi0JRxY1bV90R9h8wivquyLumyRI+IsqieyzdlsDGKpPxn3zNgJXBUVrip6rv6fdEu8VhdyvLE32KZ87k00QGBfnP++v+aD4wGRKcDy9T+9CRzn0txn8SCSnv/NV6FCN6CbePwLiaG6cO//jxjrh+JPBGEEdHKEA08ILmI5oOJexS5fqHLwE6NBGPLElnj3v2EGT8qyeFIDF2kM9veGVK5yo/xkIn7yCyEgjTB9vk0ieiQXyTDC1zEAyySwjlXx3uoiXdjXEBAb0MyfZp6C1B4yQf2mXhejMyKeOU7N5zyeAxLZnlHE7isZwi+dGawMbXbcoy3BfGUcJjhTb/O4/uet89sSxjG8A+ExFDHe/wJFmMhTPDwk+EVq45XmG053IN3Z4KgAEIC4e/6F25rvmHAdRNbuY8sa0uVXHpjha5j4LzDxH8U6k4SRJ4EPqY3oRv4HzTxjxUe7nE=
*/