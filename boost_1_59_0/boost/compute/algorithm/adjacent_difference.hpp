//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP
#define BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

namespace detail {

template<class InputIterator, class OutputIterator, class BinaryFunction>
inline OutputIterator
dispatch_adjacent_difference(InputIterator first,
                             InputIterator last,
                             OutputIterator result,
                             BinaryFunction op,
                             command_queue &queue = system::default_queue())
{
    size_t count = detail::iterator_range_size(first, last);
    detail::meta_kernel k("adjacent_difference");

    k << "const uint i = get_global_id(0);\n"
      << "if(i == 0){\n"
      << "    " << result[k.var<uint_>("0")] << " = " << first[k.var<uint_>("0")] << ";\n"
      << "}\n"
      << "else {\n"
      << "    " << result[k.var<uint_>("i")] << " = "
      <<               op(first[k.var<uint_>("i")], first[k.var<uint_>("i-1")]) << ";\n"
      << "}\n";

    k.exec_1d(queue, 0, count, 1);

    return result + count;
}

} // end detail namespace

/// Stores the difference of each pair of consecutive values in the range
/// [\p first, \p last) to the range beginning at \p result. If \p op is not
/// provided, \c minus<T> is used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param result first element in the output range
/// \param op binary difference function
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// Space complexity: \Omega(1)<br>
/// Space complexity when \p result == \p first: \Omega(n)
///
/// \see adjacent_find()
template<class InputIterator, class OutputIterator, class BinaryFunction>
inline OutputIterator
adjacent_difference(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    BinaryFunction op,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    if(first == last) {
        return result;
    }

    if (first == result) {
        vector<value_type> temp(detail::iterator_range_size(first, last),
                                queue.get_context());
        copy(first, last, temp.begin(), queue);

        return ::boost::compute::detail::dispatch_adjacent_difference(
            temp.begin(), temp.end(), result, op, queue
        );
    }
    else {
        return ::boost::compute::detail::dispatch_adjacent_difference(
            first, last, result, op, queue
        );
    }
}

/// \overload
template<class InputIterator, class OutputIterator>
inline OutputIterator
adjacent_difference(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::adjacent_difference(
        first, last, result, ::boost::compute::minus<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP

/* adjacent_difference.hpp
lXFilucmPIVpixrd0X1by4icnY48x8Qu5OX62C7XveawR0RS3mThWgJTUAPNUwqRn5bgGWJruCyT44GorAU27PFgPUoFjZQ9tACkTnbKWfL5g+Q7XvE/AB6A4X+nEUZ1md4lqFxCH9kJC+IwuLMnUJLhma5FXTfg/mzVoeUYv5U9v6Keq/Qw2uZx7RXLU9erv5T3AIAsvPBcX2Fxp1BEnAI+MmA1WEpJio10bcrQsuO5cXlCQgeUjshyhN5Qe8CYOB539X3M9IlMjdhQHYBQFZa00kfkJiEuOF+dSAeqV/5/zlrUYLW1sLxFWLzGUUJJjENCkh+Gyb2Hrws2pfzqR/v6EZofsmt4KKz64Yq17rbzvMwOf0m3VayPwHC6CBkmpIZlqqwkvJ7jdySLbheK6XmEPf3Zt7oMgcbrZyOrG/40foxTbOZrUtbCJH36MCCfnQbduzt+UXcf/VHcxv9II+AEl2SDyad4OwgLTyIHwlQzAwEJalXngGM2P24Gg6Oqc1vBlszyBjZDMandS7VDFEk7Ojr3oAXqI5NgNW3fQtoIC5+YhbzVYsWKnAakeR7hrlOf1ZdpZvHky1u2f9sT9CbIKCLCKhCKGFuNg8e3HLtPSOQq1CJpfHcXh9WXAotJFRBngVYsqSF2fkMZA0g+Y93IjGDOdX/QZnACRKahoyBWKnLNMOCgT8ki9MIzszLln9AON74BbYK7hb7j6L+AuRdOcGwpU2mFvb7taPMbvR2BhMYbBSmY/Hwrke/R/2yk4P5A5wkwOJKixIgxdr2aQm16f54WOhMrGwUERoyLU8d1eKGPHzlYtLnAUb4zUEdA5F/yDicbPd6fO/pF0B3F3JOp7NSt5K4GHDygPglhEwyRpzjJ4aQ58nyL4U68U/P0GWwFMOv14xfyg4Fqwk1g5wOiV1zWJ2mEzhTz+44IiKoargOdPYV6EMMbU+00mhPA10d8qxCpUiaKfiqlAdL7zB0OL0MyKJjEyvNCqKVdsIufj/ddhNmVWQta2CCDUe8E74kQjvdtTBu+Hb2N+YtxNpW24np4WahDc8cAduFVU5I5ncwjO2gX5YIuz8Luc6CgLoNcJL7KDzv+A/l8T/wSv4DYQjxH/mALIl9xG2VMuHSEa65G9vcT2XyV1tR9Jtx4P31z908sp+zDtoywo8n8lwjd45z2n1pB3RUHu1VsDh1wu961sXOwA6eXSOKmGst41wFszrwCgm9IRnvhj7KYaXhttfG0B82qfzUr5Dxfh2umanLlzFHh5P2zQtWYjtmTAn9XjYU4QxeMkfcSNCHr4GFuFxgylZQsIUx7N7F9SxdZJkyQv8LTha6J9RcADTq+3sQKbo7SaW0S/C107ItZsmPluc3ogUNRe+obodi04h0eslnYzeXpUUNZnDT0FGx1nX2DeTk/v7NedCV+9dwjpLxIUVUurHWJjZ5M9ZBaK+WRW5OQr0ciMRNdgDRJI83RX3fwykqyv3mEvoA032thL6/Y0Uci5sN5+QbRcXhceHGrFNSOU3jlvUNSBVaygiHFsF+ZrkffXo141La8GMyi16P6DhwnxUqyQ4fLrOU+ZXf83o4pkKwCXieaqrGtZmBOY+VkKDoA1sARBKfALGZnWCiN/XNpWcXrpm+mVvJlOneRdRDt+s+m0PGJ3O2+vmAShdW525eyjb6GB5+lGAYUzfsez9gYeIAeNFEbFvHM81ZDAFbJ2vlMJpxjyedcnTa9tl23SuCXper6J5Vrc4YOCJ6NbSbS4ry3QC8l+yhi5/uKJ4+L3D3A3S+9AMx1XRB7CuUv4foJDwOLgrSzx8THQIpGFzShNbqmYCsCf90YlCkz1jgGGnzNzxSL+28HAF9DNZGixrss5M0/wy8B4QTFeDh1lfB4eHuBvxerS91S83mbsEnVP4ZQxWZa6Lest7cSs33Ee2SxdcWVgx7byQFnFHVdxXSIvsddIEDtVQNCGpIWsP1fCXLKsHMwy6GSGVwNwUaG99pDoDBH5YDA8bEbvRuej5e1ZkQlKbYg+Dsb8+52trbRvuqvZvpzo7cP7fvUDXB0ZtKrzMs4K54/wokzegaY1qGo2mH41AbMsLxN+8KYB3MBe6NLWLzhWY8gpUYI5JbwTHlxKWcbhTz8gdWtvUpyLgU9KFX8CfGLIhgCcFD0ct6gPlihgKTdCTgqSrBMiAj8VnRWQw43RNqAk9KfkAkDkfvFdwoEz7ji84SuR+Rp8HiymiYLEsa1moPhWbGtDL56BA2VqJCSVskXNk7Xm1aPZr5PGdsfWd/yq/voFu32otKvqA0rsYpRv0lWV7SpM/x0labHYINgJn5YSX5BvfFU+H8hM5LvNykk4uH1l0Ed2VJzQI0bQqvveMKUQLmkr/My9AzBEyJ/Ds76lRIXE686oghM12KzfANNEI0c+6UX8/94zTV4V1lrgEjT874gzZ0xCkTekULQg7T5AD9psr5ERX8b6luFDRcJNfIT4g9mevJ4iwRduimUDRkgUltcOslLo5wO9/lcBGvGJWgA9FPD9ET2H7yOdGnA07xzP7WOavAxKVQln2Jp22Z2IzeYAUK8iNaryElEfUimAvUXXLxDAazpEXQAtiM1W7xPOGQjAFVgvqST8qVEM4g5AssPyAsH1A0JTQi+fB0Ahq60nEh4ABK1KOf01mTXroxPRvPda4Je6o/8DeUD5AnxdKfjxeX580Hk83FYz9zfi7oXlyynlOlAbSVWLkFOnuVQuQDjoONhUeTNpGjpmPdhDg6AxIgTqi3+qIfIgcsbY2xIwSpUJqbCr81Mo6JyTI5obo9YpMp0gWTQlQROZGUF9vO7MXf/9lBPp1mOAhZ1YoxZ5LO+ju9wV1XfQhbwKDebQyGQTn1wZmZf5Q4bqmPBdomPUKfjkWhOVuPNVCpwTS55VAwlFXw5tOJTUqkn6ccpxR8yleFZ8hTugCdI1YkDAjTOKkqVpblMdbaipp07CWqeMrvT4NzUC01YBRF7qJ+I1rpGLBUz5goicjBdCfMXITV93KNb7KH+gQMQb5c6Np0PQSY3HU6149zZnD4ZzLmWIzBYhQr9hH6cbP3aFFht8CMBnEz1l23Lc+RbtzUHFWa0Vwq68IiDYWcNfX4O0OpsqdzEFOm6O3jpiJX3e0lJDvczu8vl7qzfb21XO3UTxFq0q000xzO120ljxNa7kXUQJhkn6KV7cmSfINZpPqZySRDGWAKuZxW0EtGbixhuQuyhlN6K+PzcWRznrzVJLrArtKD9i2RsjiLAH5jmI2bVn227QweKEgshRPImRACWNeEKmn3igEbhyoe6y4a8S6IUokW4ah+08daQ4WhCVfS/NX1ACdca2cmktLNJlsFzlAaQMGKdHgvyM/idrGuldCbIW0/GwNR5sVI6Uxf2nIX1asHKP5aODb1hjmoCZ0K0i03rXquw8vY+iAzMPDNy6Vmy+tzsFMvnfULpkW1DX9i+f7ywQrMWCI4okjJzPsjGwXQ2GAJ54J/WC+7S+Rxz9fnL9+0PEx0oHNByle3XfkzsFXW2nBfAvU3JYGRNcAmIcEF+gBgRx6pDoIflaLGvb0enyNGETx54xrgw5zSGpPkDpcfGRoB/yK6mEht4MGIVSI89pOiIM7qTDBg/O5cArOoAIHI1FmMVqxTpVOdmVjSgg9+l7QD5nydLUwhHORcIaOoTp1wfWegAoSzkPGT24ROu7wADPlZDouVmlY9Y8C/AKwUQKiQPcw3OgepqhTxd+uvRtlKhcq6bbz4WpHJNQAVOI+s4dAA03LBCE9Ti8Qwxed4BIQz6oDY3gYkiaVMcm01MIBGvkAPZEnTvWIXdMQrmdI2XpVH3T1i60e/6Hkmpk2TkYx2fO3Xk7xXK3HvQyibE+4CNNzNF6bfhE/5cuOZ2DbSVp0JE/3KCfMkVnejDJH7pSiXmzaKtE4bTlcXP+DeTifpV7RttILX/+qIioorG2maILHnd/CBy2pv80CwsUvdyhfgngU0UoyudZS+DzaC9vk/7TaF+2RGPdiKiQixpWewtzbmpU1ARm1MGL/jp+Et38gJJd37jxlj0ppcwX2cVfQhucGlvIPutFqecQiour3SERJv53XgTm8WBNFyiDUQ2p+TEOWosqzYgpjAGUxqNaS7NAfSScLOrdGDofLLKy7176ns8xKuAS3qDMG42Ss5btZ3v5oDuOB2qupOdgrkeQTUUajlLPm8r+sQpywWESj1PK37jlfvWKvfqVezSLfNTLt/GX+QmXLj9eab/8yyj+G2l6BOm7KdecZt80Xlwm9gM1EfqlblN1MXzQZSE29K5ddfgwKRMwu0aSedOSZ/Mi1v2ohv8zMUtP6L9oQVgRmtZLqHi5qASdrVOxdkSr9iolXzRupCNCnaVLH2wRZRyPwRIu255MfZmh9PXPTxjOz5ffcTGUX50Lj353f+wtKUlEzs4tBjB6RW5y1pnIvQgn+n3w0BM6pvDVxE3NiOuDfkdH4H3Dqb/itZxeHhr2vHh1Iot7zGbgKERhVuldNj7uhvvTAQzYqzsGh8xdP0Kbdpn6Y82ee0KqHcdGBFXcIlmrE7euTZpzZyhBdHNvgN/jGB+bbuihjucYzo+L43jAzarq4TdYg7PsrO3Rc/5IkDGfuemtQ51n2ZysTNurY7eSrVen8Xmqs/5kSx3qXizUzkkhLbeCOq52E54sDaQyHoBvaV3FYy3bfhgzdANavWpYimWq+Fq69DeTEOngzb6YziaajhqoJTVlBrAYB0r2YFDkwHJVeEbBvloYJRLggt2yjycgx7xyLqYNdSo5MhDyalLUj0cSzb+rumQNT5v4Snl6Jog+1BytKbxJetQ1BbC0ZqlGcnPoswqCI6XjLMJ+C5D7q8IHLqIy2Dc0IiZ4IjN59nSuX9v4A3yFTIK3lqAswW8BXo/xyV8r5tnsT0Mvl0QiczyaiFdB+4Z4v5SAZm5DFIWX6jHG6I5YHYBM3RPcn+lD9lSCSmPKQFvCATOFumeuYTkWgEpzyvhZhgoTfRxyWECBBgJICvMzfvX8gMuFW/PxhtqHnFzDhDEiZ3Ksb0vmAt50yDQ70dU5r2vfJEaYy3O33vWfCx8oNto0U0ekAGRLQbfUczGbvEyx0DbdZPh6eOcpFt3MayRSLDhU1GCjcEZUfi1cdzH3+/bNXxleR3cBddTs1wqlVLi5umYL32c/jlbxAYNkXbOsckh/pgPIiBWSAiLH2TNtRxnhKB+5lovZqgXpSeZ6Ev07qxglzs2K++9O4SSkq0RBc3deZGRRhQP0gjDtUGCuIzNtJiByQ8biBnwA6puD+BpdbdnlNSNhjg0EF1Q9+MquYOw5AmeF5YfAki2rJiBcBpX8JoWxAdcR4bKKV29tlfK50TEx+17t+x2oNT50mUn/BP4iT7LoNs21lgXzgdkIFA5B9ybxRWj/OA4VOhKV3/GLCvAXKKR9kXW6nDYP6bFR9EF0B6edFWrKq5JwqkUQNxwF3uKrN0YzT7RbpjberobWSKWJaFtKhF+iEP34d44VrRjWFGRb3gjnAegXbf3Vutez98txfvvPHhTLxDQuLUUI8Kk1pthJYSkTtuIgaZHjUCvAJQinXnWgNN0QdRO97Q/DGwyIOiUktT3nQHFM5muq3zRKxHaJcBLBFBLG7U/UJ/Q9IkX0Xg1peQfF8ka8TWA8CzG4S0ipvlj1QPzm0KwGjec9nGi6eb4P41HrMKGW2r4plFhpywerPUGvDrbHBL74uM4zIHMMcMZiy9+AlMqbL1KbD2lDU0DDB8wBxQkOUA0iRwPhNA3GY1/FZOnt9RndVNbCep/lUV4Qv54bpnNjvq4tqqSlvQCq8mS2/kUFoZA9UGkF+MsFFx1xEHswrtFw+Db7lI9Fw+wxh2PYy/4+qp7AaywBSNP2ht1y19XcyteA4oF282Gf4M/lj+U39bhl0sTbyKmt0o0SFWUgmwNaYlgQUm+HxdhIbg04APsb/VMHKgmJKMLQEfuOrT7VKwDUc624ta39vNkQkdz7T2hpaN0HyJT0O1blShPSy2bpoNdVoChHoh5LEGSsc1g+QACLP3Tsl6NaER6C9AvnO+67XiJfXudUW57NoQtVpOfE/mrpVIjRN7a9dOuc1Uqs0Iww9+TqlKGMUbeH+Bpc3WFjJW0Y6aUX6RWeBZRUak8U25VwZeik/mAqEs+UDj6tfF1FlfAlV/UKS9TqrhQUqK6hl4PGnjEg6dyaoas++Ov88AS+W9vhPY6L/DOcUINgi+JjjB4OJUnCuUA9S6weRfq7cB622ZNtJMmpjUcsZeNlzYevYnpLZKaTTF3kVQhqwsNNLRvpaQQQRo1E/lc2QbFqiWluDf3DX98LJOQRCswBQEhhZaS9/+tqc0l9Ws3cqdIntJ9QGJrQSqa1B67KN7dCqnaUN0Kxf2mVQ0kLjZYqhEPYwId8+/6GZIHExmu3asn8Y14zZ7/IU0cR/AooVtdHzxVvHPYwe74bjAoOXQo5/uDP45tym3+C27BJIE2B+ByDYsPhYJnZQIVDHRZU9v1lKNdwl/H+N2vJ+h5/heGepOzSEXXODnXmKz84zvSFWF1O54pFMmCpHgUCbqpJK4FV9HYWZGtmw7PkjJlYto2jSzd6/G4vesIU/v0+Hzcr4B3hDgy1bVsQvM8LrDU5fJ7ApGsNAqH/LM4pPIbd23VDySWYklN5CNAn1GiaaLy0WDmDzS7RL/MZcX7n5FpzDODpAClnBgoliZUISEfoPM0NNuKqirsQSKZp1U7B20S5JSmP0e/VSIiiwfTTz8iPI1kY3lmrwQEPOfkjOd+qgSy4NgWpxxk/C35X2+pbK5CZhtrKVk+VUvSHR7ZgBvg1VZP7MKX6RkDggJHc9wOCIwKbvbfysCjmnAFfNHslrXnj/EDvyTQmwAaYvO7BDeFEhfrR6GxWuRCZ+Ydq7b6XjOxsFDidoCp0V38RMLwlCOx2YY6f/MXQMsBlBfoF763AYwb/blBM5xPVCjYq4LW5vCgUQbjlKXLcqDmysIPEUvcnK9WlVPCdJ4WcxsigKfDOSiw5ytyXFTCiGNX0ycSvCM1e/KTOD82DYoifvHfVDjf7PbV+uJj9fjZYKL0XnxKR2udXor3VytzLd+WM4ZqUQcYmgxO9UL31Ioj9dSghe+t7iVDabBSvi5TwG7kwlWxUgWZy5FBMwa5YLJ8HTlgKmkxIw1KkzBVULApIffUcUuFG7j5VwjXw3bFhyE9AKo5AKfTX4L3cRB+ESdFghejB0OFOzpvpYU7wgvBHQq2HdIXGehPk/YZ7dbZcE9Yh3Wl69ltLD0pj3V09G66OSzoMat5pz8WnAdrnr76+Gss+p2g6UoKUM5j6uTNNbrL3H336EpcDy7l/SIuJaN/bo3KVC6HaEMrL2B+5gmUKisolq7IqMMxRMruzBkyiexW+HzEPuE8DpmrNjFuJUa98aczWhrxcI6ShSwMlGdPpytYYez4IZ5tPD6eLgsN+UajfuCqrj5DxJrzL4QwxrX9n7d3gk/sMXaekej4B6vNNz6mAbSfRR2/e3z2LVZu42a38KFgKPXnPyMR5Jtz5d+Ffl94dfgxl3wjv6V25cyACbDk/XTtyTqHC70zFOKExXd7R9Lp/DgUfI20SHZkjqg+U/oDEViDYPAtWcMM
*/