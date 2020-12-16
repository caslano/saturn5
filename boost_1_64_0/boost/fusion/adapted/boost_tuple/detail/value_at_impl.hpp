/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09262006_1926)
#define BOOST_FUSION_VALUE_AT_IMPL_09262006_1926

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : tuples::element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
5+ydbvJbyOpYk40rMTj18+6LjeE6nGs7b+levAllnXkhG199yTOncT5prffSdX4H83TmX84e5uomz3zF91ZX/mOP1mdjberXsnHkW9lYr1sbvCNW6czb2RiHNbrEs7BS1/hDbNb5d5yTd7OxQdf5HizWLd6EJTqz0XcQy3SRT8RyXeWrsUA3+Bks1B3e/j37u6Wzx/3vu7cu8VWYoZv8pc3WN83hzv+yMUXXP/S7t0VPTNexVU/shPG6wMdioq7wYYN6YpKu8U0YqZv8Ckbr+EhPdGOMzvNBGKfLfCqG6SpfjUG6wc8hpzvc89GeGKoL/NjHe2K9jqE++8meWKvLmZ54AGO28h3nf2zbE1md364nvrJ9T2R0jfcd1hMb0jPz94b3xGbd4Lu6eyJvTjHrvhinMz09sTtWmVPkE7FGV/lqrNQNfhxLdJu36O2JhTrDe2G5LvHpWKZrfDsW6xbvn7Nu7tXg7hE9MUUX+HJMTeP8IKbrFu/T3xMzdJmPHOiJWbrO92B2msN753tirq7ytZinG/yfHXpigS5+qieOw3hd4SswMc3h2NGcQdaNT8UyXeOXsUbHyJ74JjbrCjeR+4h35z12sm66xNchZ06Tu3c2P70X/wqzzKlzB+PMyezSEydgiq7y05ilO3zAKPdN78u3YbFucX5X72VOkS/HEt3gj33afuk8n4oNusZtDHPf+Iznxxhd4QcxzJw27zHafNcv8XWYYU6TM7uZb06Bf4VJus7vYobOfNbzY1Vac34aC3WHj/ic90r34qcwXXeSC94lPRu/jZU6s3tP/ATr0zi/jaHmZz5vPzFaN3j4F+yXLvClGJ3enYePMV8X+FLMTfN59BfNN17iWzFdt/iLXzInjfOtWJ/Wlr+4h33XJb4VK9M4f3Gsd0/7y7diqm7xxD29bzoP/BSW6w4f8WXfzTTOT2FQeneevpffB13jtzFeZ8Z5d4xM785vY5DO7G0cs9N8HrqP+ekd+VJM1Q0e/hVz0jhfirXpPPPworOhC3wplqdxHrmvc57ehZdjoe7w1K86V7rGbSzWsR9j6EedE37nINdP49/oiUMP7YmNunBYT5yFJbrO92CVbvHLWKk7vO3h1lbn+SCs0WU+F8t1ncuT7It71fjsIzyPbvKZx/TENN2Z4ux9y17o6rd74r9l76JLx/ld+o5n1fFd3/3jvWca/15PnPR938c0/6Se2HW699VlHnay71qaw0ef2hNjdfu0nrj4Z9ZTN/mDM+yxbv28J3Y402d0kc8627vo8jnuOdu76/hFT/wRy3WbV/3Su+v8r3wfsUbX+GVs1jHH9xGrdIUfxAbd5v3PdSZ1mZ/GtI+Z/2vnAZN1nT9ynn3Ref4F1ppf5+653td4kW/FMN3m/c93rnSZX73A91qXLvQ5lHWm5r0v7omKLlzi92Se/62LfAdG6jYffWlPTNBV3ojROn9ZT8xHSTd5+uX2Ttd54vyeaKT5/NgV9lcXrrQev4EuLbBmV9lH3aj7Pbnab6uu8zm/93y6yTP+0BNL0xw+a2FPrEjj/MdremLwYGeD+6/1TOn6fALCeJWfRjbN4QOu87umy3w/Ruk277/Ib2sa59swVrd4l+t7oqCLfA0m6Cbv9MeeKKZxzizuiaqu8TKUdIvfQlnHjT3xOUxO8/l7mKYr/KmG85Pm8zO3OE+6vqQn+m61Lmk+T/+Ldxnivnz5Uu9oPHN7TzyMgvG4oyc+8VfPrPN398QtTe+V+h7n9l7nMN2Lz1/uvOn8/T0x50HPqgsreqL2sPUZoh9xT+R1h7/csn+69Lgz9YQ9Haz556joGt+DmbrFY570/UpzeMtV9lQXuPyUNXKdBn+ATno=
*/