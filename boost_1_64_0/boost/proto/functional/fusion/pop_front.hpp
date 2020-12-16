///////////////////////////////////////////////////////////////////////////////
/// \file pop_front.hpp
/// Proto callables Fusion pop_front
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_POP_FRONT_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_POP_FRONT_HPP_EAN_11_27_2010

#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::pop_front() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::pop_front() algorithm on its argument. This is
    /// useful for defining a CallableTransform like \c pop_front(_)
    /// which removes the first child from a Proto expression node.
    /// Such a transform might be used as the first argument to the
    /// \c proto::fold\<\> transform; that is, fold all but
    /// the first child.
    struct pop_front
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq>
        struct result<This(Seq)>
          : result<This(Seq const &)>
        {};

        template<typename This, typename Seq>
        struct result<This(Seq &)>
          : fusion::result_of::pop_front<Seq>
        {};

        template<typename Seq>
        typename fusion::result_of::pop_front<Seq>::type
        operator ()(Seq &seq) const
        {
            // Work around a const-correctness issue in Fusion
            typedef typename fusion::result_of::pop_front<Seq>::type result_type;
            return result_type(fusion::next(fusion::begin(seq)), fusion::end(seq));
        }

        template<typename Seq>
        typename fusion::result_of::pop_front<Seq const>::type
        operator ()(Seq const &seq) const
        {
            return fusion::pop_front(seq);
        }
    };
}}}

#endif

/* pop_front.hpp
WMM+YOb75emvKa9rGfbIjeFftKVZDOPve+Ee1ojyGsbfV+2HsbOoL8Fsec73abtPWTysH8ul0RsTbSh3Yf2Z2Zta+tC9m9Pnib/t9ahhYdQjYa2YzZ5wc5qyGTCb/5gLDHZixmlr6j2wLvz+Dl6k/MyC8fPtKJ5Ez8yBDWT7vFHRerQy+9pVjFzYur7DgmtTn4fxZ7rfrTqYzgDzYHbuX05UtxEwU95f2iw0ovPB7Hg9fNGwgmKtvW+67/bplLswH2bz/a4/pPPBWjPbX7SrnrIKbS+NhpruUGZUx7BnvXUd50D3B3NjVvSmeSHNB1g7ZkumfmypLAbmyezjUeNpTqfCajDz7NNspLJ0GO+7Fe1ejFJWDOOzo/azTF9lZdpebvY5/yedoa5hbx3jYnyD7g9WndmryVFedD4Y30vQF82d6HwwM2Zjv81cTvcH43u53XR/d2WZsBo8d4/HH1GWDWvBcyl6UhqdD+bG632C0W2afxaG82h56J/T6OywZsy+n76xnPoEzIlZ58uJbyk/Yd143d50PUd3BOM17fzVtVKaHTB3Zh1Czv5KvQ5my+zQcK/vlZlbVjFyZtazKP+pMk8YX3fP9P5SZf4wXkcTd/xI7wuFefE8W/32H8oSYDzn960K2UPng/Hz7emyazqdT9vnwNgv6f5KYY2YPT5y+YAyCyvDGfcoP+EPOh+Mz/BFzXoEKAuD8Rz8obf/JmVJsKbM/OfaNaU8g/G9lDS9SfdeBGvO7LOziTQDzK0N91kj4PFhZR6wWjw/J39epswbZs6s6dgNjajGYDyvu+9t9y3NHFhLPo/iXb9Qth7G+9nFrIRqdA8wa2YRH9u8m7cwnvN1oxbl0vlsDPt8adTaULoHGK+xYceq3qVagdkzu2D0IfXrCFh93st/uLmOZhWMn/3mhpF0vnRYQ14Px6ZSX8rT9tKn6ZmlVEfaGaofOk7r7G2rGPVhM64yuXsU5RKM5/XQtuaDqZ/BeI19/enhJpRnMJ5Lk8Le5VkGzJFZ3qvtl5Tla+s6XW46iuaRZju+PXNRmWM9w5k6+M9P/kn1DvNkdstvJNXmDBh/5qtSv7N0BhivI6vTH42huQkzZeYxLvQ83QPMlc/i8BX96B5gTZh5jfFqQGewM6yxUaNq3Ke5AuN322ro9hyqB80y9my6TLMfxvN63DnvPKp3WGNmu+q4GFM9wHh+Phhdjc5XCeM5cfpZ5TLKJXvD+dC3c7i5Mh9YA2aBo59RLwiG8X3uLf58qLJYWB1mNU+1H0bng/H7O3rD8xtl+2G8Vjb3CdhNeQbjtWlx4TD18lKYI3/mqOBWykzrG35mD1pSmUFnh/G5EtPferEyL5gt73UWxw/Q3cJqMzOp7/Tu+wrMhNnB9jV6Um3C+D0ceBpziGoTZsPjufBePsUMZs7sTbd2fal/wqyZHem91Zt6j2bd6zyinMiG8Xg+nZfZUVmhFjObFT86Uay1MySP+3Y1xbqBYQ5ujtx/VJkbjMfF4mgF1YMnzJLZlKKFM2muwHhcdu45YUY5COPn8y5d0JL6tfa+PZ4Lh1MPgfH8HG2z/hblrm4tL6TQPWjvuxjlQvN2C8yKmd2c57QuA2bOrJfrvm50D7BaPHevZmZRX4LVZfZk/PrZVO8wnrvua15Wpb4Lc2bmcHWeL+W8g2EPmTjs7WhlvjA+p2+8vDCQehbMhdm9hwdeKUuA8VhPGmpJ50uCVecz4GiXIMpdzb7v3HkpxRNWg1mYRSrVQxqM9+SNeeM2UJ+A8dpc9Oa7scqKYXw+/DpigR/FxdFwBtj3OLKM4gLj954fEER9KQjG97m61oxS6gUw3s92nyprryxas9B1479Vlgw=
*/