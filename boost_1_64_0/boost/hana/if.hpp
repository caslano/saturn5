/*!
@file
Defines `boost::hana::if_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IF_HPP
#define BOOST_HANA_IF_HPP

#include <boost/hana/fwd/if.hpp>

#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/eval_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Cond, typename Then, typename Else>
    constexpr decltype(auto) if_t::operator()(Cond&& cond, Then&& then_, Else&& else_) const {
        using Bool = typename hana::tag_of<Cond>::type;
        using If = BOOST_HANA_DISPATCH_IF(if_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::if_(cond, then, else) requires 'cond' to be a Logical");
    #endif

        return If::apply(static_cast<Cond&&>(cond),
                         static_cast<Then&&>(then_),
                         static_cast<Else&&>(else_));
    }
    //! @endcond

    namespace detail {
        template <typename T>
        struct hold {
            T value;
            constexpr T&& operator()() && { return static_cast<T&&>(value); }
        };
    }

    template <typename L, bool condition>
    struct if_impl<L, when<condition>> : default_ {
        template <typename C, typename T, typename E>
        static constexpr auto apply(C&& c, T&& t, E&& e) {
            return hana::eval_if(static_cast<C&&>(c),
                detail::hold<T&&>{static_cast<T&&>(t)},
                detail::hold<E&&>{static_cast<E&&>(e)}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IF_HPP

/* if.hpp
PAcXFa9ozC6vbq9HEceYtf1v9cvy+JUtu5J9xTaLV5EPAipe73NgfWbRdhe33riG5p0rlzGO4jFx5U3LsyzO6ZNly5fhA+aSfUt/lsu/ObfElmtscDPnxsA9jhhZVqw7c+0Jzcjx39wT/h7yudW5fnN9uqW5Q+oW2nlr7buTXHrPkf+u/Srud1O2Obd9zy9355Wb8yqHzc/zGDPlofKmcvLc+sKQRa/nrMtad6icYUu5zKn1S+fTR2KUp+WPinKb5kfMoclYWxZwVUaWJS1bs+/+eW0/qf/8yrbvnNexrue8uK55EVLnlDom70mm1DmlvVcwhy/rXnJpx2dO37Y+Zy6eyttnlcVd6sqFz1umvGB9TTwSh19TN3P0HGf5cvrnPO3RMf7j63g9eQ91R3Xdzrnmujj9Mfu2Hc91ZPwZufyEc8TrJcbfMS7zcmebxjlcn84hv+d0vom75zDv6P9W7tVVFJN/cBxKI9fUP2o3m+TosG75DK0/ON7vbceIlGWLloWn1HFOx6ZpWfBH/ZPLvY+4D/zOPeHv+jWZs+pbsSz7Ae0TS2KzbRt9CH6vThaZsV327655fzFO4tJflP/snqCtGRoXdyz7Bn9Rx63la/Ka2sXkjG3ydC7pvLyUcb+UMnFWLmUd5ZvajtGac3NO2bitkrTP8rzjXMayjxuz5uQ3SDn9kNxUjJVlvSZf1W6SX7HcPXB50Zw2n6/6J7kZaeuc8Roo/9r+k2v0+23Hlu0qztvQ5Hz5k7n/K7mwzSE5mkQi5vRtzEFyxCgsmftXVW441hfM0y/Z/5Puu592z7+I8Vx3XPst34pb2vbmzgHLZm6jr5Nry03NActWOFGu6vfoJsp/ldNfmUsU+87Z65pfjjEXMZdtO7i188N2h592Lp8Yo2lzsW8MGDD7S9fO26qPwW3UI9ZJUXCc8Lpxmby3V16xPjp5jy8f+39R59B7i9/JIRHleXFMXHmP9V/ajp1zGgvtXXfdGV7ecdi6nH6RnZQvP/k8pM3yuk6CsfOmPrnnklzS96sbf3pXs+6a+kaVJfnuDYzzh51Tyo1/EHY3cJHmcwDAB7OEjo6OEEIIHd1p6Vi3U01v26u9xWJpu627ottSs3ctOSGEEEIIIYSOEEIIIYQQQgghhBBCXr5Tz9S03nx87zfz/P/P//15mZd2jEP/g+3DOAuk2bapHUts/M44lRs3NiivUC8xj+vou8xYscApumu1jxlWGCbTGEdJu9g6uIPxZcbjEVaJ/sB6Uk8adTTTxwlpOXSRq011rJd5rN5Ult3LhMzV6EO1hXm6OF2lfbdX9+1sI8YmMfNXRahS2j30KUubjGPfsmN7zTmFduPSb92m/EKbGP2p89TPzI15qpLWLK171Xay6fq57eKmuGz/CUY8nifL43LqlJHNBrPM/8xjhmgmQ94j4taqNOp+olxGyGbzx44v5j2ukrdbGVseL/xKJPWX1qW4or3dYq84wZrt+cwwanuU0x6flNYv5jiulucdU1+1/5eVT+oXbfuC9ojDi/r9DXUzTIF1OXgX82u/Cfv1EK5zbXyb8ymprLD8VsfVO43fB2x7l7yvt+Zfp+225bxZ+zyfG9f2t5hjedZHnfNeK75BvfKtvUN54uqYMRoyhrZvvEv0eEr5fcP69XbjJs/EGx1D6ptVzpLtjbZ3q6fqJuyTq57Tce/RVvKJvFdftWPSfoMep0xYe++zL0dY1L5JsWpEWfS/25zIv6yuk9pZIH3J9k2Pc4bl+YDo+SnlNI7qs+1Vth+RP4Mp/RjXpzoxizFtK3+rx7QzrQ0npC+/ST/0KVUfWvWzS78b1ZUtpoxI16ax96ubsG0n5O+235xxDHk=
*/