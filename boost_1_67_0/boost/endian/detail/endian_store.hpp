#ifndef BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/detail/endian_reverse.hpp>
#include <boost/endian/detail/order.hpp>
#include <boost/endian/detail/integral_by_size.hpp>
#include <boost/endian/detail/is_trivially_copyable.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/static_assert.hpp>
#include <cstddef>
#include <cstring>

namespace boost
{
namespace endian
{

namespace detail
{

template<class T, std::size_t N1, BOOST_SCOPED_ENUM(order) O1, std::size_t N2, BOOST_SCOPED_ENUM(order) O2> struct endian_store_impl
{
};

} // namespace detail

// Requires:
//
//    sizeof(T) must be 1, 2, 4, or 8
//    1 <= N <= sizeof(T)
//    T is TriviallyCopyable
//    if N < sizeof(T), T is integral or enum

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) Order>
inline void endian_store( unsigned char * p, T const & v ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8 );
    BOOST_STATIC_ASSERT( N >= 1 && N <= sizeof(T) );

    return detail::endian_store_impl<T, sizeof(T), order::native, N, Order>()( p, v );
}

namespace detail
{

// same endianness, same size

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O> struct endian_store_impl<T, N, O, N, O>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_trivially_copyable<T>::value );

        std::memcpy( p, &v, N );
    }
};

// same size, reverse endianness

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O1, BOOST_SCOPED_ENUM(order) O2> struct endian_store_impl<T, N, O1, N, O2>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_trivially_copyable<T>::value );

        typename integral_by_size<N>::type tmp;
        std::memcpy( &tmp, &v, N );

        endian_reverse_inplace( tmp );

        std::memcpy( p, &tmp, N );
    }
};

// truncating store 2 -> 1

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 2, Order, 1, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 2 ];
        boost::endian::endian_store<T, 2, order::little>( tmp, v );

        p[0] = tmp[0];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 2, Order, 1, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 2 ];
        boost::endian::endian_store<T, 2, order::big>( tmp, v );

        p[0] = tmp[1];
    }
};

// truncating store 4 -> 1

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 1, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::little>( tmp, v );

        p[0] = tmp[0];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 1, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::big>( tmp, v );

        p[0] = tmp[3];
    }
};

// truncating store 4 -> 2

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 2, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 2, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::big>( tmp, v );

        p[0] = tmp[2];
        p[1] = tmp[3];
    }
};

// truncating store 4 -> 3

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 3, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 3, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::big>( tmp, v );

        p[0] = tmp[1];
        p[1] = tmp[2];
        p[2] = tmp[3];
    }
};

// truncating store 8 -> 1

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 1, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 1, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[7];
    }
};

// truncating store 8 -> 2

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 2, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 2, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[6];
        p[1] = tmp[7];
    }
};

// truncating store 8 -> 3

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 3, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 3, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[5];
        p[1] = tmp[6];
        p[2] = tmp[7];
    }
};

// truncating store 8 -> 4

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 4, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 4, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[4];
        p[1] = tmp[5];
        p[2] = tmp[6];
        p[3] = tmp[7];
    }
};

// truncating store 8 -> 5

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 5, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 5, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[3];
        p[1] = tmp[4];
        p[2] = tmp[5];
        p[3] = tmp[6];
        p[4] = tmp[7];
    }
};

// truncating store 8 -> 6

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 6, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
        p[5] = tmp[5];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 6, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[2];
        p[1] = tmp[3];
        p[2] = tmp[4];
        p[3] = tmp[5];
        p[4] = tmp[6];
        p[5] = tmp[7];
    }
};

// truncating store 8 -> 7

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 7, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
        p[5] = tmp[5];
        p[6] = tmp[6];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 7, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[1];
        p[1] = tmp[2];
        p[2] = tmp[3];
        p[3] = tmp[4];
        p[4] = tmp[5];
        p[5] = tmp[6];
        p[6] = tmp[7];
    }
};

} // namespace detail

} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED

/* endian_store.hpp
KPGsbxWZ7HfeL1Z7rAeAEAYLQn1iOPAhNX8BZqtt1RkIDj7W1LvpodsMdbcVKxJB8xjqJqrnnByY/iXylf04O/C7mqqKJiYIzYYvD9mExosSqZHxq2ejNmRfmmaDE2lxUrm/8HFexK6nQURs8FPUcL2DWAewValgt61L2qonj9BWvSy8yl0aA17ikEyd8zHsw2QxUTRLrtZ4u1xhxKa4ojfIx7RRm8Y5HJTJTZM8K2lrxHgdaKuQt3JzkduWIcFKO5LIPN8L7WU7COEMhBZGUpUELVxKoloVjkjlnLWX0sLfwb1qQutoWkhTJ0uKRmjhHWsvytZLxezVK6qqfESK059TGTNZXgiyfmSSMXuGezKS6kTSoXlc9diwHb855dDhL59N2pcdftZJuNlKBd+//2OIzCrRcE5TJYju3/0OKn9fra2PLWyRj7UwSylf2M2ilk9WPKi0d5Fpix41g38G62qFuo4EZZbMXQs9rU/dE5//8LM0CV/d7choUx+EJAB+t+r7Xyb5kkXW/C+ch/QlSvrnRNLD8t8/cbuM13PMe/MRwxSb/+ZHSKgfUDW65L+scSUCVV/5CFjeHoSyqiD6O/Tr8X7jMZ8L3/zlYXxTEj/aBDsVmugy5f8JvnQroizbxlYskF1Z2IKIpawyMzmdJnHAtlkHSciqQ0rDsNk8yPp9BEJuq/OmqWOatjrEVGXX0GaIRcrz02xmt66tLS7lBYpIEmH7LWMrDOxss9nPJWfwNYevbIfVPMTfuvh3Pl85Z3vzdL5y5vXmIr72cUnOUd+M4/3ly5aM4uc8nEOOIQeAAIBDSwEAgP9//2mDnmzFl9FrCOrU0FSqBJUvlF3PLpfp+9n3E/FiHXX0MnFCrvo9hwcqoxnEWVGl1YxZqbTfGkmnNJIuqgCZBDFFRLVK1uhT6BK9IjkNMOMcMQJavmREjecE0q+O6lkynRukbd4yR6teoz+GY1OtekV0mcZHMlYzaquM5ifProIX92ImdfvQB7Ydv+rixE8jZfwYdSbm7IQyDkpRKi5wrBycWVgtSkpxsPYk/Y6IOqxYmdiF5atEJbNRI1UE1l5BjP0OPTfrUAI5sZ3hvxPgb5abXMMSPUMLDhE1GTlpnw9LmSy21YPr8eho5b3v86xcP2p9xifqTgzzBlXJ+EQGKKpqHlUVz4Izk3yli8/2UtPMAavMUMZc+1Yn839PwPd+lRd+4coewKW2a4g1MQJkcKlP90TySOLyj07uvUhRMNrgotRTKYrMGHLQXS7Td9HIw3dDg06S79YzR+ViIjRC5fh+F7m8zxx9NzT0Qau8C8/bnezehHSLCOkuj69AV7ziJexl4lRewtYOvBUbmxS754r5MwPHohO072NlqscCzK8gWh6/VcyfTi/eVhVs9GZwBRuH3IjFFvsdwfFSX/Z2MI1e+dWxfKai0pU4cl3hmwvhP5a2UKXmg+vYgT0D9tEkUq8U1Wtq7ag/BZA8xqNrXPKPtzHpUrP7/Az4bFavGX3c/Fe//dmob4su+dbonZ5KdH0qT1OYwHmyFewOm0gEC2xCeMFtFnvMYq9Z7EOGyCwtKLNrboZfWHVupRnrGrHBmQCLU+JQ/dHxItgNLrtDlOSd+rjgtXiGGGO0jDWRPA/PK/JPDRZ0ME0v85ih3mQiQkdiZtDl85DgWRrS1wkkJ73H2KUSacgJZTyihxz7DGXGdKfQzxpHVlyacivWJfROKnAdmJXwQwVh4r8GkXXkDWW2Q9xOuznXk1pZ9Cqjugq5t6sfcenjREk+TUAPa7S40D5V6Hpxr899r8cRJqQjBHJlPQh9BwQH/J1d+0PshJJHnKjdJ+RX3uUd6k9WcGqw5ydQVlKr0ZvEvV73GKfW7mRKeXNcSmnqjzIzSg33Qhydm7bT/ClOiKSYrpXkV2en9PLUhbiHni91eqv6Gp+vlTwQna4F/frVYjKxiqc5y/RKkV0Q6hYu6540Dy1bSX5BUBqS4MATn4qyuX+1m27k/Sz2imKPOygJaJhTEofBK/3wH9yulCTguQ4l+uUfEtTEmdrsNp45dnEoBxItfM/chSfasqrs2rv5B02nxktSWWaFBh2/SfbatEJS3WrLHlQhvLVlD2XX/kKtiYOdIIeJ2akoKZK3mMAw8MmlKKh45OH7GU2EAc8edfDQa2fekKdedrsQ14LKvP9e3Pv+u2eOnnmD/j/6wRuEjRpfTsFGHL8DaXOuVBE8Au3rWZFLBIw6ri0dJFS/dCiaHzgcz3UGnHjm15ZKfZy2tFfPVGyBxu+jvrZgXwY2Sqw/PjWSsagybG0FSyJn7GHN9lURt4Nr4dHVh4nZ1pnGNDVp4SNfIhLYlvk6jSzJBtSlsAF1KnzGIb628PV1vrbz9ThfO/jKAbHqOvnKcQPqupgFggjOjup1sLc26+bxtZSv8B5B1Bfkt2EL+7oH+PlDfH2Qr4gPKpcj9i8JEFX4oikGBrT2gKP1sVfNUEFsFYnKWkkkamDxYrO2Cz6tR6JPiNI1psURb+euMUvXIDLfh9arDYmAlhf4PGwkUAMxn7rfPnBcvTetTnwJ07p14lX+raLnWqjeOuBUY961pr6HjRUEoCxwIrvmLSyV7qPNbjDTxp8FjtAqcmfoVZJAzh5NIGvPckhAboB/Cy+ySakIz7XoQ2D4UlgtGXn4LhdNoZg3/5IglQNDo1CSavLYCFS9/Bo3Cly1VWuUot+yuiGJfOfnQ9DDpHR5kd2Yx4M6ywFjOy7fYTiVqipUgEP5Ny8P2RX2gU4u2MKfnh5OlAlLe82QndCzRNIqCEnkqFd2YkXkvz4/5HwadjrnfdiJzKNu6zYP2T0cd9QdcS/HiQTO0gkOxsPYovyc/XPkdI+6IxOXCwYbWhJ1pjLHU1nhdE51S40L9oy6n1BuPqHc+Hoxd2bgRLRA+xUzCzfajZyQJa1MAQ93kuBHecCCqMRDYu50+qJEBHMLgv7ol0VwSkEwJ3oHZtMrDIct4bwuFUjITGzVeOIqqJJwaqVc48Lp0k9S52u5LnEXznrdMMTdgK1aGkmPXl26iFDGXbP0HnHfLMiRxgW3nkEo5vCiwwm5899/RXInHI1ke+RSufM/PqEZ/MGvE3InIWplQvkeMd67sBOrbwl8su6BQDN+x+YJ3q/IYLV6eiK9+73q5bp3GGN/nMDYHyaIKEJyi0x9UiLQhh1+sOcP6M8ter99KULvS9ymEImJTMe9pheB6Uo9PfWMRmQPAK98MPCWWDpkBmlya99TCQCN6geIFnMC4ExFItqCUqHOXoUTR/EAflSvpDu2wnVu6Knlu0swYjRaMsQFwuHpYnDUp26jLd1guy8Xfmciv9BLnF7srrRABxXvcMd8zJpa88am9dwJd2jqXPS62jd1T+170cnW3enW3HRHocQYN4Ob7nM6NOsusZXdJY5W57jb3Rec77xcS7p78OJ7letNC/VXu6Hn4RrdLUas32VN8erp7s7RpkXqDgGv3INGM4Q0OEMo0WYiyLPBAZBc1ZnuZsi2ibFmMduEESfGB8Y6VX4KL6LHy1PYY6M3/3KwFXZgq/R/hC2RGUnjMEeXwMYkEep1YKOPD+nlqaedyFY8LijP+IxeDxBc6ncQkSSYU6cuIjNJJAmcfjAE0+0hbdc2Zhtg+WsEhzJ7QPrOSG0qcHbUq3A2Id2WBB6e2BbsdoP0BSVEf+Kp4z4mxWc5R+1ZzsdmP9/JNL5XX6ct7dOfUSTAYUf8i0UrVH3Mk2SeaTkj45lnJP09eqbl/T//vuv9M2jnTuZNWtH02Ss6bpvoT8H3X/wZOJNe5kzOEE4nzuS9YB+zJVP4VR897HyfV7/QTq7/ZxSUMU+n7WIZPYvAxlrnTSMUFesvGLzf2QvlfZbvXjdPtZs2oVewOsPyfWX5MtqRSy7KUz5qlb8Q+CR7CzgEtZjZFviH/2m1TzImednlYBJ4T/Gq9SW4m5FVSwVm38iiw5IPAOPgFiJfJFfH3Fhy5nboDmkKh5xRzCpVn55mQBAd8rsfI72RswU9d7uZUXIHBx3wt+blptF2b81kwDPXeOKT5JKVrMf6q+Bf5nDAv/4XmyRqZ2rmIYNmKMA3saAzJ7N2YE449R5mxZjdtXGyH74UHBTroWRa4WKTbcfU1+v+KZEp982nkmkDOV/8Bbn0X2w+zmN26d1HYbK+eDEhjZDYhE81A1f9zorCgdqW6i/WDqz5UuAV7tFtYpNapYZAIz+4QbyAB/bMX2PNsI4lqui6o8uWq+bLks1zTsDMSnHBfmY6Znf0YBKkwRmMEfPZygrO+i64Q30cWx7/89CwHR9HrAFNrXzxpk+SZl6JLIsKj6jcyNzFW5OQxW42nKDFk8QjEdvaiuojLnnrJ8M2Mjf+/ZPJDieVXk8jIjtUqCUGK9pc+uzKZGtfoNYKndYKxFbV2m+MtaWu6BXcHpJsn06FZ9VpWfTkqGzDXNlNKtEkV3ZjsuscwyOlhneXixPLeiYdJ2L9lydSuguAOv0GS8uBkQ4infMXnDpvGdloyobXSRY9LlF1Mp2z/P7FNX/v/1az56/WfOcTl+aINpdNcypFmujPOZV+JmUKyuxt21Pm4EwCwD9cMZJqM7li8Q6VEpdrRFbozzs13qRqvFxWaK72tLM4P1xxcR+dLNR3fzw8UvP/0Nd5aZfpa3CFipg2AAnmq3uTNt4QwJzzLHnrpwRsrC92Ec9aN6iw2RhiQNfBSJ31ui4xdTPdRAlEVD7uqBsqZPWOwK7OlZZ8qiCcVe32jUisOCvNyaGYkf8Jc85E7GpOESz9eG+C8SurqFRr/sG/QlUcgbGAUg+zYthqRh0IMpiiFJf/eX7YtpZ5Iq74FRXK+njyhWG7pCKSR9NW/DbcWGoH1nY7cxF5qOmXmIVXf5a0Gt8nitewndDDa1wJc28zuF3Zf9cDge/AkZBwIyBGGKfI+g5iePWdUWrETrEHVyHKQzudCOBrCaGk4ZS6m8gRDqh7hRtHO2xNnsZHvvV2eF38Fq2R7dRvkA9fP0Disb8icXi0TxUeMUl3c/9gNsCm3wnjKA61D/4+j967g4lY/4h+pbc4Z+xIsYqY2sEGxyBAi02LXh+5kvpON7M2rJ4o2lt7vBsubFid1SrxIL1wgBiO2RczHB+caQvuhVsy+I67omPoLo0Zjt1hcUQZrrjD3Iy+14ztplGYsT2ypvG8ff6DawdQzPjTp8YRd4U6+E4p8xCVQTD+YCfHIYDzRkclLO47khb3+5IW9x0XW9xvdyzun/9Kvy2/9tNRFvdOnnJAdwK4A4eTwC1mA6q1XQBjMCND6jVB8TvOQwe0nYcEuGkIegP75hOy9E3YN3czQLJQtknyb3ZN3sQHNNygyc2LTR7WL3j4t5d/e/n3oaTOQ2xqSWo+xCY+gOE+iU0s0XNXTO6Y2MTicF0e/+bjmbp8/s3HM3XT+Tcf0tTN5N98VFNXxL/5wKYOV+1HjFfKkbYdZpyBHykeSdl6K/yyA9GrvRy92lzGlnCw0CNmxn7eCV+ttjwI5vZzw3axqmTdL8QmHDGpxOGzuHncy9v7h8GC/Ai6lepbiQO5LcC/Y58Tm9hHfuYOVd7+JzyWc1Sd+L3ulBMCWz7+WAJf0pYxZu9ZS2SdMafQfZXEzuqD2TXfxiDmTCO8dDN7+d2Qcvb4TNY5lcG3lMCrGSF9wAsIPV++cy3tRRiA0Z5KBgmtFzHm2McoB41+0R+Wd98LgTY0BA+NTMbBryMuB0znCAH9sosQ0BxP/EvGSVuL5SOwZ74ymp4BIY6qF6X9YiK1UbGAA+JUiT7DtqNeJwvrDHGEx5qX1MDDOBjm13BwA+9TOeLPCKc1RE32yr522+5B3Isy+elrNvuUpPCoj3MG9CzH0UN/MBmUU48RQwYH0qKCT+wRpThiyODo9lxtQm/KgMGuvhMu9YuHIhoQn/1iS5wWNno1VfjbqY5j3DH58lQ2Ux8M0tQ/46HhfDFx0FXYMmfJ8oR7ABOrX/7YIVby4Tc4nBrTrP8fKkNa1v9da/i/6ww5uGW6/Cxnl/Y6ruml7KRHCM3BEMEcBz0Ec509ekT+kEb6Wo6rKoeAp2lOOQyNeeyCNyixxMuM+t5PGUCrywQT+PuzN+9MEWi2JQUaRMpxcahAP4IP2As9MKfm3SlveSXdZdeiJsHXANe/7pfGT/EXEujxFuWTeCObEUjXlKRTaP4SNsKr7fpUlUhDialnCXlGMuwGnCATN6B6KQZ7MCnyjYf7beNVPMrKthamwfTbnYkKp7upwre+6pgL+CLplfZb9NENmA22/FVhIqJ/Ul+79FLlGbR5EdyZarvBriiPpnEcYOHFY7ad8EKK2CTrtm1IRPWWf/mLbbfxOHHLwGrV9lENYdo4Eo7ZCzbAEMCS9EyOn9VvO6/VFM0JW7V4U9W5dYI/nPAj+VsStZRK61wlPAJyVKew/DBjZjMr2z6AD0V7Ffxv5U2fqj6aa+4Z6Z2YPy1im6XTwgw6abKEOqtmg7tjc78dE14xKBuLScLjbiFgJ2JUilexHsbvFBe20pntaJbxu+n8ZJnq5f2VSvFmoZc0CDfrc6LXiE05LIqgu2H7FdQiY0Mjk3nZnsrdHyW6Js/tgtX4vKZnAbTf2MVW425GJ9m1NyJClDuhDi0cIG4L5uI+OAyszMuuceP9MbmYUK8YDAxn13yE6EXP0JuedH6zALFzTsrmO8/ZFZ+FCrUCUdwfGovUBns1lgezt7JSoxFEjZFXE/W+ynU9dW1JhaNsPGTqQ4ET0UkVloFdEK6UH9UOU5NmrCGeYeoNYhhDLaOWnuy/YLdtyr/OGbJKzwDcdDQ+IyCY5Z6O5JMARnWfbbEbFMukIuc72q8xVJ1m767AEf24uWnadUhLNSNaIObOAN/vYNQpKbcM8Qtx+J9pvoLyxOlYq1JTf8mqryCOGNgGjvLoFaEOLdYUdYtQpxnaL0JnaZDaQRD56NRAW/RqBLnPEXpDW13TlWosca+c9RD8CRpojr7YzEeCOSKIaojkIYrMfgG7ykNgaVNDPDpnpDwV6C1VPx/Gjl0wdlwIt/g70V+Yhr8GJw7ilcu7qDau2CzfjxQjOJol/rg1TN1caG1lR+cFjwzbZjMPN7Oyklj/Q1DN7iee0N7mRTwEFeSJmadgA+AGqDsxNclsUTJEjVZxjY8/wL6Ohwrte80YfCvhWHLnlz4mGYDAeQBrzAdOV0Lf4GF4QXKMdNGGzCs8U/KJjy7YYjZiB9Ta0UJxb56JdAD7UpiGu9OYlrnFnDwteCia7fiiP5Mgf0c1gbppjYItWghrFGwXkxcssGnmaYDHwfXaz2OECB70R1oJ+asfjhhdEedSoVQmfUd5kaqUGsYh3pXqroFaSJqJF5kluSOPEfB843yOt1+mAu7Pz5FLvkRLz7obFWl/fiLSPr27k94t4VD7I4Ymyh3rrir9em0jW+xcJRbkaHf3IzKN45RUSp/FvWA3io4xueOsJNGmNiCCB3+g4tQFfYQO5k5HtLptBBOBk7rP/LJZ7RFHev7ew75b2pr+aC8C520Iy+/0DBObtAF5LGui7yB9RbEnzLFkH3mHIItBUM2DPlHdOcfxGdjJJFLsDMvMn57nqLMNBKf3iCtGNJyBk85JlTwjO08phWbGs1Px+H0SOd4/826o4SxrM+UTz0Nd2eCcS8X82TXfo3Ycx5FDcr5GkynAERhC2U/FhmhkGSK0PT4R6dd3q7xDewMn1xeK0G7R+lkqu2FtRqnRPjwnmnafCO6Al8Qhd4vjJHF2dr/dI4HNg3sLOUUUAowEjHsYwWQDtYg5aU5sXBpnE/u2ZX5TTQoIR3IqPkcbyQo1sUuLtHXlztIk/31oIOHOcojvdSc/CFUVbA9LN0TlIqsELpb7uPYfPZOsPf2i2vep2n/s1L5PbhpVO93ryewjVnBzWNb/K5IuuGlRBqtpuwWCu2NZZnC32divtjSs5jpnwemkKeFFd5Ru7eBemhBnGrbgpE/o23r+ASduK5egdI0onmLd483EJqWujkJbieMRjxE8lC6Q6sbBqPXI00KlaZ1uwOolCo7BAy9wDnoFu2IOLVzsoZGI8ZbeUZEQOFMBcUIqICpXKFFOKGMHtwcB3ronPb0eRrfFee7iXNgw9GFSTg3Lr/4EsKqMI/rmm3pXDyJahhPre9Nj5zhsbrBJzOkX+n4x2Qp1LAgjf8AJh4SjN8GGW4KdgKbQDtV15LvYa4ZOcyWduqoktlfc2+/U4ARhv3goV6YOhbA6jO73s8tAFweGTa8XemeB3kFjoQbUyh57iwOKinZxpCCNqFHC0iPUBb9HT0CtqeOCdO5L/aPSo6jghFzP/X9/HpKSm6rWu6AsCXYRuBCeN4OynlUmhQMVI3nltNsvUkzQpv7gDHQSGc9mRK5YDhUCEEfEjW+IuOw39e2mvkN+TO0gjh5JKavWmPoeklJMHWPp4lLyXXoPYoG4uTPMlR456SXizH2IN2ADsRkvEmJbiqgTJR5aFXPpaaz6dekqrIg6D8quvZJNkxaELT43kzPXIxRl9GoV29vaypqr6/lhdu3wCGrpkH+ZCWdLTzIWwh+LEs5sZ21aiNDZEVe1G59Wu++szLqQ3H0dfE9vDDbRdOIpipIciHrZNeeYqanKpzmDeDnNDHayF/xnFmFhzrK3FxGlgVO0qITaO03uP47VVZx+Fl2nWSU5YWqn8D25vwhJt7hM++NHx1J1gdZ1s8RhdV4YOEab/Yw6DbRyssxd/LAjhuhUL7F6Y+lpy7fA3a7UfPFnBeD4tLja+EaXy/hGtwt6t+BZx86c+I3Q6bZgr/9m+jDcvzBsl1WpusVSWbC0C3nXqutUy0awcyz1Rwt1rvtFz1MwCBgZ3NU8uItHlgntWKjdseSJtetXabHj+oTClsKjqdap8esjaWVc0Qnph1RHFe1PVMR5PkJnOf4nJibUgZ8u+hmfoiq6vMmr/NULKvkB4uU23VpBYDblhYSCklM1WsW5YbN2LwwDklvna2PZl6JRnRSCTdJWVWXX/jd+NCpLsD9i4q124MsV2UM2U1PO84kYkoN3sP8mkeZapjxu+IRzAmbFrqt8mMLYwL8RZHfEF3zsRquXvgFnmYpBkLBaJQheYbK5xIi7+FXCnfjG42LVhiqhHcBVz9JWrWSLCKIOlZXhCuKBDuxlI412tonAJMg=
*/