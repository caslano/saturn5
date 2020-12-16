
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
GK0mIedRK1ZLe9etzDWfuJoj/nU6VbQUCeNuhLI1U0aqBstmfVnUVZRPBop4NpLE+9KkiYpq7H0HTulSpsmLAirqORRqyUXWGKl9aJDsihqc5mBQFlOllTk5tnuEEPmmua5E7TJK3mV64q5lKEvWQa9jVmjOVlJpfAJQ0BaF/kvS2LdcX9I0mqZ9vL69/en+DvkiXU8Ln/D4Xh9Y6ahK1YINjVKGU44AMSxc7S7O61UAkdQg9jXQJh4UxEiICtglJnw6HeP2Vy2UviGWYE0++hritawiXsvHt9OiBjnG1BCynlgFK4pTNR4hyY6h3D3ru1yoXQ7PNJkdU2PMNqdinjmVzzA8ESmlR6K9anoOEugMFufS6pPqDM+dpfVBI3cpMBmNUgn0KiTQqI7qOWY13k+szUaM3wUlUiVtyhjT+zDLrUiftP1WxnOvgvCEIGVFQfRGaZJZCSTnIqjT2CxbTe5hEjarN90SUIWUKTnvYafde31+MlKVnhZlVcDKFLn3KPKCaZ3Eze2Vyj/snJB9KYCEWflzB2TCi8KN9obLKxkFoGUXyuTudtreRRrQcCdkpBTh81rj4Hg3JLuq4roH5rjC1UAw7BS0U+YABkf4gDKoMW6YjyBcA1VBvCu9hnel16ClUhrXY/ac3T3oxAjo5tXi1ShV0tLpGKt2Lk1P6AReRF1D51SqgadHda1aF517rb/g5aBi86IyKoWJLYjPXip87poP9iqukxd6dIb7hPqeN1W5MSnuBTP7gbCobLqesZmgiPhZ8lQUXHgndaGSitAb1VCLKhJMyfSn01SKeE5QdKGzhaasWqeJCgVT7fUcFVaBXDtJrOnplGJyY50xtFeLY8V36mTetJ+AcWoXKW9j1nWoqV7nbU3vgLXZq2BzakVjHKJyaYAyNjng9T4DsHy8yGtIbU4p6YUSIpHPGYHp7HYyUm8hNWb4ZNwcuaaQmW51zelwQNcLGbt5R08TXTlxz1mvgV/eBVqdXwIf+5IT33TWNSjm+PBar4yWe92Emob54DRIf9VLf8JVr8hrEYm+XJXH0btKueyqV5/yrl/Pmltxw4rlVKwQ9bokrzx7FWiQ9sdPTs23TnXVHolpjv2Jwp/KTKvqL6TNbvfnaW+rhNf74s+ft+qtbNk2fL8isJXv0WBOlVXSlCbzzQOeV4c9XkLCOd45eh+x+8qEWcVqsV07hbqdnSZlA+5LbIrjXJj70mvz5PKVuw3VJDzP36+UHCerqeoVMpiK7BX9/nxFNpM5vCKXlFFxYovnktlO0VufQk994jZblh02BqV7oaDmSaPeZwTDfcXpawZ7m8D3mr/3mr7/bfbqTV5fs1Rvb/rbmnfbmf42pt449DYMMvF+k1IXtEbdjrapiCPMvnBCT+EEWzhe4QsnmMLxuv7CCdXCKW9rRP74SaW4emPXb876jRnqZRx6yzj4MvY6X8b1m796g9dv7t4bG22tKXc1RD+b3MunqwqR2UwU71wr09gh5EgEITvchDmzFWRqCcNaia4Vf0g7ZVFqqGEVT5PjZCN0JDf3Kvu0x8XjZl1XYuuDXTh6ndq8wGkZSYWZsQrb/PW6/Xp96Ne3+9bNNxh023gHpki8jreM1zF5XocORr+ezzCjYr/EaviksYr4ocf3sqBe7rGFq2EzrOKVLHCva/b9mrjYrE/LmDsdlxJV9e8XbugvQNPGeV1MZ6/+/QJ2TZjX1oufjZzXyW2o2iM98kFyWKO30b0UIY8hW8wBEnltJjchZVYUZPVbMYRU7qrGIXPpp+oZBOSquRU3iz+bVSkvF4WUaiJBqn2UUeMoqVrmn7t+RJOYxUXEguCbHpx0PWuWISglO8CkRkbzIJM=
*/