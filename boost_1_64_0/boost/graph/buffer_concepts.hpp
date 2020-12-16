//            Copyright Daniel Trebbien 2010.
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE_1_0.txt or the copy at
//         http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BUFFER_CONCEPTS_HPP
#define BOOST_GRAPH_BUFFER_CONCEPTS_HPP 1
#include <boost/concept_check.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/concept/detail/concept_def.hpp>
namespace boost
{

BOOST_concept(Buffer, (B))
{
    typedef typename B::value_type value_type;
    typedef typename B::size_type size_type;

    BOOST_CONCEPT_USAGE(Buffer)
    {
        typedef typename boost::add_reference< value_type >::type reference;

        BOOST_CONCEPT_ASSERT((Assignable< value_type >));

        buf.push(g_ct);
        buf.pop();
        reference t = buf.top();
        boost::ignore_unused_variable_warning(t);
    }

    void const_constraints(const B& cbuf)
    {
        typedef typename boost::add_const<
            typename boost::remove_reference< value_type >::type >::type&
            const_reference;

        const_reference ct = cbuf.top();
        s = cbuf.size();
        if (cbuf.empty())
            dummy = __LINE__;
    }

    int dummy;

    static const value_type g_ct;
    size_type s;
    B buf;
};

BOOST_concept(UpdatableQueue, (Q)) : Buffer< Q >
{
    BOOST_CONCEPT_USAGE(UpdatableQueue) { q.update(g_ct); }

    void const_constraints(const Q& cq)
    {
        if (cq.contains(g_ct))
            dummy = __LINE__;
    }

    int dummy;

    static const typename Buffer< Q >::value_type g_ct;
    Q q;
};

BOOST_concept(KeyedUpdatableQueue, (Q)) : UpdatableQueue< Q >
{
    typedef typename Q::key_type key_type;
    typedef typename Q::key_map key_map;

    BOOST_CONCEPT_USAGE(KeyedUpdatableQueue)
    {
        BOOST_CONCEPT_ASSERT((boost::ReadWritePropertyMapConcept< key_map,
            typename Buffer< Q >::value_type >));
    }

    void const_constraints(const Q& cq)
    {
        km = cq.keys();
        k = get(km, g_ct);
    }

    static const typename Buffer< Q >::value_type g_ct;
    key_type k;
    key_map km;
    Q q;
};

} // end `namespace boost`
#include <boost/concept/detail/concept_undef.hpp>

#endif // !BOOST_GRAPH_BUFFER_CONCEPTS_HPP

/* buffer_concepts.hpp
lldd3Z52pDvSc+AA3e7LTRxASxfOHZTP7ER/7OB/0/spug9S2vvMRXKRzuDuUEUaqTpeDZN4nYeNXZeO32+j/pEzQOqj7Lxjaolu08L0l5reewftFN8XaHQaLL80Shmp4eEN9W5vgki2NwVMs78JpKSe7ZTQvFaQRK/EpmS+ssHr8s5xI/QVCQmNg9P8p6RX07eRonjeBJSFoJdSO7f9VT6b0NljbKzI9B3RmZNs+kSV0v/BWWdZaqPsp2ePJCT6OwmSP91M2bcM2yAq/aZZmOlz+ASQ/6yM29RXlWHUMfZXoD3kBjZPJPKa9wJo0li1O5EujpKZ33XvctinRsn0RG9OurtqI3w20X2kKXd4DrYt09wm2jmfEWEPpuVVUDs/kd+LMV2NNmM49CYB43NnUmYvgyc8k6/Aywc09Wv1YVsDFnbOqD/cD31tNFoE8XxSlfH37IvGuiFuPWptfVD4dzzRH/MZGrcw/354P6slaTpzhvNmrX0PTRecd4HMh7I2fhXcdKCZHP9e0XP52WQEv4fCL+WJCr0nmff64W4QhHAH/oZ2EgM+9gJA4q4U0k6F3JZCaQRWGQHh6Z6dw0WZIEyAInylTyTD08cf3b0P8YwWYqP8NLMMr1RPLurKPY/94KQQ8Nt1IwNSF46GwivfZxXdeJ/PRPWIIi/GBkr0Qn33Nk4X47ImWe9SL6GgeLTX4YNOZg/mlrGpf7fuPvweHmwI0PccLPQBwvFFs/o5Pj22/Xg0PNd/g5n6pt8oJp9TPTHzYZXJWu4cn4DUbfs67BDEEiHogbVtN2K/OZ64iA+bCP/4gN31U5cum6j26cFe4zfy27leabj4Y3nR7OT1GQJKR31nfPkHH3r575v0tOfIf5Yp2HEHjDEYcz6a5QrSgE1+jWn/YzCEn2774VXM7e1CqYqls1NSf5s/pkOun4KcwNP2owxDqPN2PzjlH95y7As9Dh6QFS9BsPewVYf3g/U1qTBe3Nc09vXfC+cfG+3040ew/Phx5sclwhypjCHdJXxjNhNmTb7BUJahAYyLPxrdpvjivkiQS/VtC6sA9XJUrPJqa7jyU6SgPBg9VQFpp1dzX/Y+OwJbgCr2EBBZaNFQ3MOPRc51Ry74i854YtUk/pA5KkM51ivTEGu2aObvMNIJR8mgx8vIanc+XwJLIZHi4nZkjyylp/3KUvsZnCwqxVjupkaUeHtocR4QyYcil/Wo2RHpZlL5LUcRzF7Ohdq1dl1vPP9sJl79c6ANJn34ueoppA4yzgt35wruGm2AIJnp8ZoNwYZ12SZU1S4t3vngnsbSly+r90IYafFQo1rCveNHO5EDyMaD+XXUilBvHt8biscxJ3tsz1YFqbdD/1VsbId1lIMnKYbF08UY/Rem9NjwnuTT8H4hGhKrlJlSPf+yT3/+5Wz1ye3mkydPNtdqQBsXAlvlFymvqMzr007k8za2WOJ5vbVP7txOa0Gggr2z/2Zu/s9lY/nL2L7gqCOj+ZcLmQw5isXxmfr8LSr9U4UrSCcCZT5mxAx/a5OFrvPjMd1GMipbhStJPP+yVjLY473OifpQmEosGOaCFu+nZVz22r3fQJnjbO/k8cGJXbDf1lmL/Rjy05+NhsbZeRnTZ4sx88H8Hyf36GXx4P4PYVd1InBXmZR1XVdDCaofwNRfjeH1oMp25yPSdHz/BYQQgZLRP4udoxA0eidoKZZmJRi881vnFyi96MLCMQfgy2js0g/IAfzxWB3croYXMEJSGPUH+40yayA/KH/6KYqrrXTM+JXOezw9mqIFJsRpNcpyEDXBqxYf8Li6HZUbUWkvRvTpkIDwA+wRhs4FcubSpHC1OVo5oyNd6mnKuNE=
*/