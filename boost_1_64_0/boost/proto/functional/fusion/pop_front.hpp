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
Iqsz/IflkaLiGCsoKTtoDYqjXVeR2+3x1deO3h8BHDsBiaBhJtf47qAM40IvUtxNwL6fyH/xXwazzR4gaH5E1TMY6OZ/09boePjS2f/j6yD//UWhL4mWzVMbCm6gfEUIE9pwJWqkWB7BZ6hhGb6pZvNqaO7/BqYngnUvwy5Tnned4rVuc3sQUHZdpH+Op4Kl+qoScdJOXzZrSO05vRqkVsxV5KfCAXmCzPyAjQNOjUuhxYLeARVRXwlT0rugXAB7AlBAmyR6qrFz2bOFI3ezkr4KpxmbCeSg1P+4oIUKM0qDkSe+LjSutkoTN9uqRk3+hNYZA8jOk8WaMTL0BXXdcu6bMdZSfk/t4PY0CA7U3gmo8c1VlwlistZcEtFcM/HQwxp0er7t1JkLj5VG3XoYnihJxKxTQ/MuLMneuO7bIO4Us1Xst3bTArZJ2csnpVLVgjBIuxyDRoSegxjxLyagPALo59famQoUkPwOiLEkg9CSzFLh4DyI8ERdLTR3UoC8upnVFaSctSDdCABn7k5wit0Xz1cikW7TwDLhQXcbpMyx5zWPlTmIrp73aA==
*/