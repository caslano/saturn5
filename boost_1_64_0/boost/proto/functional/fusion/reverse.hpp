///////////////////////////////////////////////////////////////////////////////
/// \file reverse.hpp
/// Proto callables Fusion reverse
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_REVERSE_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_REVERSE_HPP_EAN_11_27_2010

#include <boost/fusion/include/reverse.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::reverse() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::reverse() algorithm on its argument. This is
    /// useful for defining a CallableTransform like \c reverse(_)
    /// which reverses the order of the children of a Proto
    /// expression node.
    struct reverse
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
          : fusion::result_of::reverse<Seq>
        {};

        template<typename Seq>
        typename fusion::result_of::reverse<Seq>::type
        operator ()(Seq &seq) const
        {
            // Work around a const-correctness issue in Fusion
            typedef typename fusion::result_of::reverse<Seq>::type result_type;
            return result_type(seq);
        }

        template<typename Seq>
        typename fusion::result_of::reverse<Seq const>::type
        operator ()(Seq const &seq) const
        {
            return fusion::reverse(seq);
        }
    };
}}}

#endif

/* reverse.hpp
Wdd1tz2VecBqMpsw+R80b71h/HwlnXtZUKy1Z77+cfS/qG5h/G5nB504QvMB5sJsWf8J9L7ETvT3Cv62PX8eo7ot0s5XpUEQ9aVSWFNmtzvXNaJ+1hmzitnvh77vpMwX5s5zyfz6BGXhsCbMPmy1bRj1EJgbs4imy4ZSL4fxPPMouHuV7hbWiVlyo6zRdEddqhgFsrOvs+l8i/YC+4DnoNW7zwVbYB2Z1XZO+IjeB+P58pHPxQ00G30xc5idKUlxplyCNWN2L3XQFurzMB7rN/79ZlDvgdXjsR60jvIzGmbB7LJV263K4mGuzOI/zm5BtQJrxGxzH8vZyvJgDZgNqvLyL8oJbS8RRe7p1Hs+MNxL2I/JdA82MH7vo04WLaZ8gdkzaxjYYZ+yEFh3dn9WV5eMoj4Ba8XWHUvd8e6zG4z3gjnWS/yVVX6gnX2t/z3qkV3x/YGZXf8vjtNeYI7MjA8G9KJ7gPmxff7a6fOeNONgXmydQ9Z5qrESGI9n0FebkymXumH+MZuYW0LPtIfxvXxz6vYp6i8wJ2Z7MpbE0IyDWTOre/9gF2URMEtmga6m26lfw3i/jto27yHdA3umCWz8tiyq6XSYKbNPMjOWUlxgjfg6OwsHqjFYDWZTcnyDafbDbJj1+G6HlbIKWG1m6yLHUKxN/TCPmD0tM5+szAJWn9mfK9t+oswTZsasduUVb6pbmBWzh6ert1EWCLNj9vxkj/7Ue2COzDov/jxNWaz2vgkn7en+EmB23LqGdKaeBavJzGb2HZrF6TB7ZoermpxQlgOrx6zAqeFQmg8wfg+Jxh1/otyF8Xs4ND7lC6oxbS/Nc+eMp3vojjnG7MKPwUHK3GAuzG7NnUn54g9rwMz9nn8c9UiYLbPITktbUm3C+N1+OmmVpbIkbS/BIYcfUMxg/AyBhWPWKsvU9rJ9spGNsgKYO7PjB4LnUk33wOdBZrP3j95NOQjrwKxt5exflQXAevxtfn/bpU8ffEs5AWvG1k0+2/3d52tYdWZD7GZ2U5YF8+K1ucZuirIyWGtm267ZGFGP7Ik/Q8fvIbo7rQuFtWU2dcgjmnGJ2rpczzufUr+GNWRmNtON7q8U5svMKPLlb8o8/PG5gNnv7d9YU6+D8b0sOfYX7SUexs+e1vO3hRQzGM+XkT3qNVCWD+P7dD3s2FxZOYznRM/rE2rT3fYyrL/ikwl76AwwnhOjQp696y8wD2YHWifEUM7DavPcjT5DNTZDe9/xIGdTOjvMmdmc3uMvKkuFOTI7lTDgjbJsWFNmHb5JeUb5AuvF8jPljVU7OkNvfK5j63zSGy+hfIHV5efbNSBSWSTMlNm5rpFUf1EwO94/39w4QPUA6/o/qwE71CWwH+UZzI3ZwYcfDaUzwBoye5R2cB7dXx98lmJWscqDYuYNM2W2Lefdz8p9NesVdnks9TNYZ2bfnPcpoxkA68Rs1pLU3tR7YLWYBYbcHEC9HObF7PnMmltpNsJsmOXv86GcNw8wfObP9Ve+UmYPa8Csz7jw4XR2GD9faeCvL+nsMDtmu6u06kS1CbNlFm/TrSXdu7aXyQdSfKmXw9owC7Bf+EJZmmYbnkbRGYpg7Zml9ck4Tufra3iG5dPHUDxdNNtXo4Uf1S2M79O4+EodigusNrOFts/X0L3DeJ5Z3rhmoSwcZs7s+75fDaaahjVm1q/5j9RDkmCqh1SHrY3PWaZsC6wqM3ez34ZRvcMsmI19u+wK9UGYE7MhgZer0oyD2TF7eOnRIaoj7X2uudvbUY+E1Wc2Ncp1PtVYP8N1EZ+Mv6nMBubG7EVeoDX1F5gDMzP3Pi8oz2C2zMJXFE2lPIM5Mrv/xbZm1CNhVsw=
*/