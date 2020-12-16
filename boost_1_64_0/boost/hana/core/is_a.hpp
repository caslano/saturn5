/*!
@file
Defines `boost::hana::is_a` and `boost::hana::is_an`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_IS_A_HPP
#define BOOST_HANA_CORE_IS_A_HPP

#include <boost/hana/fwd/core/is_a.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // is_a
    //////////////////////////////////////////////////////////////////////////
    template <typename DataType, typename T>
    struct is_a_t<DataType, T>
        : integral_constant<bool,
            std::is_same<DataType, typename hana::tag_of<T>::type>::value
        >
    { };

    template <typename DataType>
    struct is_a_t<DataType> {
        template <typename T>
        constexpr auto operator()(T const&) const
        { return hana::is_a<DataType, T>; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_IS_A_HPP

/* is_a.hpp
Qd0ztsuuwOqQdcj3+pfUB7MgW9/b/rrsJqw22biWH36UGrRzL5pulfdZrvaccdt6+CgzK2pqYsW5LpZzTpkTrAjlbE+RZruUucMcOdcjC9+X7MJ4/z5enDZbaodxDQGD7VpK7TCuYdmcMc+kdpgzmaHD3gbKNsF4b6PfWDaXucP4PWE3stke6RmM9/bZ8lNDlOXAuGer6pktlLkXw7uVrM+udu+kZzCu/Xja1VHSM5gP2dmSnW7JTsNKkK0+N1Z2JRLGvfaqeeC8shgY72bErSyZbTyMez1h+IRmytK1c8PSggOlL7BKZFO37X8ptRc3PmdoNf6wMgPMjZ9l4tvvn38w7ku1vVO/5wVWhuzk8LQSUrt2vw9T6v2uLBpWj6xcrzkjlaXAONf9xj8vJ5mA8Wx9q56SLOXCDGRJjQukvnxYFbJHbYM+yr6bGb93Rw/OuSr1wXh+M5/ky2zDYd5kawakL1UWBzOQ9eq3qbCyBBjX1zX3mZWyJFh5smJTqi+WucPMuIa6Z+V+GTDOp8X058Okdpg92cQiKx2UmZkbn4t5MmehzB3Gzzmg0uzLykJgHmRRFXwilfWB8U6vjNr/STIP4/fn4rHHO8m7AFaczr0I+YdYGoznZxM87JTUB7Mmi52V+5Nk3sLUpCzZqJm3d8tOw3i265L9q8jcYZ5kVTxbRSiLgvG+v9j18JjUB+N+Hi0x8A+ZLcySzPmo3xxlqbCQbxb+zdwNg1OlPhjP4cOD5glSXwlTk7pk+T8uD5YZwfh+G02bNJHswpzIBoZlPpPd1M61K7SmmOQaVolsdefbD2RvYfycOwKOF5X5waqSHXf/2Ebqg3E/DS2Le0l9lsb93LRnh/TFF8bnTl9ymyHzg/mRhV4/cF3qg3F9de9PqyP1wXzJAqftkfdEsvYsz0cYHsv+ac/y0fbOMmW5sEY022707wh6WRl/jtUP8h8n+weLoHMN+u37h7JpMN6xtDEj+ytLhHHmM/p22CQ5g/FzxpW511lZOox3eqeDr5zLgxnIgjfNf6SsAFaZ7OWZ7CMyo5LG71Yflze+MiNYLbLhpTcMkz2CmZMtbV1iu7J4WHWyxJoOhSRnMDOyQ29K15L6YHZkF195ZynL0c6lPLJOkflp58bcvGohtcMsyDz+3p+vzMza+PtLly6fGilzh/G5W0mLr8jctXNJZtnRykJhnBe7qUvfyE7D+LN4UsjCHtJPGNf38EvyEsk8rDzZwc4lDZJ57X6t/r5/RvZdu181p7rnZB+0+rLfnUuXXsPKkW0rm20t+24wzmeQRY96ygwwd7Ij1d63lJ7BuGf9zH44JT2DBZB1td8QK7XDSpG9L7hdX/YIxp9VI7Y83KIsG+ZItr1crcKyKzB/skafV7ZV5mRjalKa92jpEnn3BMF+IHPfMummPCeMPxszm52cJfsAq8nP0v836XUazIx3rIHvLtkHGO9f3o710yXXMGuyOpvrV5A52JqadKP30uXmGy9KzmD8nC7r3vWTGmC8t9PsG2coS4VVIQvLOhOq7I52zdHe+d+/18H4Xbdiens3eU47U5MgMu+AZ7MlEzCee4N9FSRLUbB6ZP6VsvfLPsBoH5CfPotkH2C8Dz8E9j8u+wArxvOb/oP0MxvGNdx1nWsr9cG49nPvmp2QGcF4H+r17LhUcmZv/Fk8O7/5O2W+MM7L5Vvb/5LaYby3gxZWNpXZwmqT+czamSTzg5mTFa8cKjNKt9e+67++1l/23cE4Z8MWbpQdM8BsyI7fmnVTatCs6La1UkMwjGdU63PgSZk7zIm/g0UuzJHaYYFkHY6X2qcsEcY/T9/s9VGymwTjd0HfCS8spS8wnnujn/0nym4=
*/