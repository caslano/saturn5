///////////////////////////////////////////////////////////////////////////////
/// \file push_back.hpp
/// Proto callables Fusion push_back
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_BACK_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_PUSH_BACK_HPP_EAN_11_27_2010

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_back() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::push_back() algorithm on its argument.
    struct push_back
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq, typename T>
        struct result<This(Seq, T)>
          : fusion::result_of::push_back<
                typename boost::add_const<typename boost::remove_reference<Seq>::type>::type
              , typename boost::remove_const<typename boost::remove_reference<T>::type>::type
            >
        {};

        template<typename Seq, typename T>
        typename fusion::result_of::push_back<Seq const, T>::type
        operator ()(Seq const &seq, T const &t) const
        {
            return fusion::push_back(seq, t);
        }
    };
}}}

#endif

/* push_back.hpp
a8As7Yb7LOqRsHrMitsXBCvLhdky2+r0yx90dpgZszZ3un+trEw7w2XrNy8pl2D8jr4+1z5GmZGToT1al1ONegHMgtnr9iZ0PnsYr5Wf1n9+m3oBjNd78POZF6gXwJyYJW6+8Zh6K4yfIWBXIPXBCJg5M7/5wR2URcHsmaV83vIzymuYNZ+bdV5ZK0uBefBa+ePwFmU5MDdmH82sMpf6J8ydWe4BJx9lNs6GvbXDkUXuNI9gjswWVO+3WVkgTD2zDsxpwzojyjPY53+b3992qOc+yhejhlWMFjM73Wce9ZA4mPq9mdqw0Wfm3KT8hKm/M/If6zD+1RuqP5g7s/3LTtooq9QspNnVETQfXPBZilnl64NHqcZgJsx6OT2YQTUGa8DMxy+vnO4WVoPZ3gHF1WnewhyYHTjkak/ng7Vh1qC4Ha3LhVVnZtfppRWdHebGbPjALc2ojmCNma1I+i1JmaMr+jyzkt43UqgeYPbMalRx7q7MH+bErDDRqbWycFgtZvsijU/Q/IPZMht0fyrNlXgYP/uqfUOuKsuC9f5vvvxtVi+2OFO9N6pi1JPZxKff0fkCYfze3y5worqNgvH7+yMnexrNW1hNZisbJf9IswNmw4znZzpM/Z6jOWxd2Cff0dyEOTH7bJp7P6qHxngms2Tb1X9RbcKaMFu627EBzQeYA7Pr12q3p/yEWTGbY151Oc1UWANm/SfZ16Z7gNkzO59u5kK9B8bPsHZP/a/pjmD1mL0acbCHsgKYI7NDvne6KCuHqRqrBfM5PPcu1S3Mntm12G05FBc31C2zh/2qNad+DTNl5nRvNOV1AOzj/+bL33a47+Zcmv0wd7bueNNRtlR/sEbM/D4qOENzDObKrO2erda0T3fUH7NjdZ3oO6yPZkWTNm1XFgrj7zMyrXdeWSxMfSaqCfu6yqnRdEew+swWzT76sbJMWBtmCx9u/SedAVaNmUnPGiPpjrT3XY26cITO18Rw3dBB2XY0b5tQbcJwt59HG9H5YGZs3bhZ3+fR3IQ5MpscOtqb5gPMlFm4Y1gBzU1YO2YH57YxpvyE1WJW+UevnXS3sCbM9nlfP0Bnh5kwO/aPjCLKT1hNZklTB9hTX2qK2c9sUNspARQzzU73evGnMhfNAif37UQ9GcZjNsbiFNW7D6wGs+6tZm6ieoDxM7h+04ZyIgDG47nGuslhmn+aVQw/9hH1F+2ZF9p1o3wJ09Z1bvHEiO5Ws+Cxkx/RfNCso9NmqulozZo1m/mc6kGzpOONfqJ+psXM0vWrycqSYPz+ljYIHEp1pJlPtybTlaVptqdg/bvfs9LsYNptC2XZmlXt/MNXyvI0G2Dje0pZoWaXHg2iM5Rodm5R688odzVrN3X+LJo5HoZ2bfmDzcrMNWs/49RFqmnNtq3oPlGZm2abi7rRfPfSrEfdyQtpjmmWdu/1LspPzfytLl1VFgzjd5s6tMUGykHN7GZ330LzT7N/Jb0qpTzTbG3RInpfnGYt5+ZRHSVqNjZkhLmy9ZpVbO6wUVmqZq9/D6Des18zR1enQ9TPNHtyalkE9TPNGvimONEs1uzL403SlBVrlpAWkkHzQbOpPWvvpz6o2eKt34ynPtjM0KaMSqd6sIHxnvzBn29qUh+EZVWBufj9bV2nTPxAWVFz/Lkgtm6I/c0pdAYYz5e+PpUr6QwwU2a7bwY8UFYB4/sc36uvozLjFobPNBp2gnqyBYyvy5q7ZogyR802rTw0RpmHZlVbN6R+5q1Zi7nVmlEvh/EzlHUIKKNa0dZ5Vp3vTLUCq8Ps+yPJM5SFa+uSkzzWU0+G1Wa28M74FOq72rpLhzf/QrNYszs5Ay4rS9ZsQPffw5U=
*/