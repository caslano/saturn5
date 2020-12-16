///////////////////////////////////////////////////////////////////////////////
/// \file pass_through.hpp
///
/// Definition of the pass_through transform, which is the default transform
/// of all of the expression generator metafunctions such as unary_plus<>, plus<>
/// and nary_expr<>.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_PASS_THROUGH_HPP_EAN_12_26_2006
#define BOOST_PROTO_TRANSFORM_PASS_THROUGH_HPP_EAN_12_26_2006

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/detail/ignore_unused.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<
            typename Grammar
          , typename Domain
          , typename Expr
          , typename State
          , typename Data
          , long Arity = arity_of<Expr>::value
        >
        struct pass_through_impl
        {};

        #include <boost/proto/transform/detail/pass_through_impl.hpp>

        template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
        struct pass_through_impl<Grammar, Domain, Expr, State, Data, 0>
          : transform_impl<Expr, State, Data>
        {
            typedef Expr result_type;

            /// \param e An expression
            /// \return \c e
            /// \throw nothrow
            BOOST_FORCEINLINE
            BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename pass_through_impl::expr_param)
            operator()(
                typename pass_through_impl::expr_param e
              , typename pass_through_impl::state_param
              , typename pass_through_impl::data_param
            ) const
            {
                return e;
            }
        };

    } // namespace detail

    /// \brief A PrimitiveTransform that transforms the child expressions
    /// of an expression node according to the corresponding children of
    /// a Grammar.
    ///
    /// Given a Grammar such as <tt>plus\<T0, T1\></tt>, an expression type
    /// that matches the grammar such as <tt>plus\<E0, E1\>::type</tt>, a
    /// state \c S and a data \c V, the result of applying the
    /// <tt>pass_through\<plus\<T0, T1\> \></tt> transform is:
    ///
    /// \code
    /// plus<
    ///     T0::result<T0(E0, S, V)>::type
    ///   , T1::result<T1(E1, S, V)>::type
    /// >::type
    /// \endcode
    ///
    /// The above demonstrates how child transforms and child expressions
    /// are applied pairwise, and how the results are reassembled into a new
    /// expression node with the same tag type as the original.
    ///
    /// The explicit use of <tt>pass_through\<\></tt> is not usually needed,
    /// since the expression generator metafunctions such as
    /// <tt>plus\<\></tt> have <tt>pass_through\<\></tt> as their default
    /// transform. So, for instance, these are equivalent:
    ///
    /// \code
    /// // Within a grammar definition, these are equivalent:
    /// when< plus<X, Y>, pass_through< plus<X, Y> > >
    /// when< plus<X, Y>, plus<X, Y> >
    /// when< plus<X, Y> > // because of when<class X, class Y=X>
    /// plus<X, Y>         // because plus<> is both a
    ///                    //   grammar and a transform
    /// \endcode
    ///
    /// For example, consider the following transform that promotes all
    /// \c float terminals in an expression to \c double.
    ///
    /// \code
    /// // This transform finds all float terminals in an expression and promotes
    /// // them to doubles.
    /// struct Promote
    ///  : or_<
    ///         when<terminal<float>, terminal<double>::type(_value) >
    ///         // terminal<>'s default transform is a no-op:
    ///       , terminal<_>
    ///         // nary_expr<> has a pass_through<> transform:
    ///       , nary_expr<_, vararg<Promote> >
    ///     >
    /// {};
    /// \endcode
    template<typename Grammar, typename Domain /* = deduce_domain*/>
    struct pass_through
      : transform<pass_through<Grammar, Domain> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::pass_through_impl<Grammar, Domain, Expr, State, Data>
        {};
    };

    /// INTERNAL ONLY
    ///
    template<typename Grammar, typename Domain>
    struct is_callable<pass_through<Grammar, Domain> >
      : mpl::true_
    {};

}} // namespace boost::proto

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* pass_through.hpp
fnztDeDfRFgLP4kp/7vAP+Pw59n1hdsjvhp3dHwweYs+cAI+G4MvM0XsH98E/sc4nfjuwMdpxefAf+Pwx4G3SjvZDn10HocvOiXjv/N9NBVwvn5mbrUvwPuAc/XT/r7LL8B/pH9f//or8O8F+2N8s2MfHT5zrD/8/ncTW31kw1+dP26MXzBl3L5PB3wrDn8P+KzR1ZzA1+PwwbCvGfFfHPiyHH4m8Hh9K8bXRN8P2KuPJhCMfx4vxMG3B359D/x+4IuIvu8AfDJB/mlvMT5VD3w24OMJ8HWxef7UAvwY4Aty5Xvv+jh+uAX47/idN7zB4BO35HM6lz8u/d3Anw3z2YfrLuknPCduXyZi8AkjfArgS3F44R7m/XDgSwjKtwPwuQTvf+wPfBlB+e8AfiV+J+Pwln9+FvhhHD77vTG16c4FfQ4vAm+VxgZ+JDf+ce094fNTNeLSx4BPy+Fv3Y3/gI8Txo/AZxfkf5Lz4vqdqAueBb6cIH0Z+PQC/G7gFwvev7kH+CIC+e94Ptp/Qf0VgU8jwPcEXgGzeRn8gRti+V1yQR9imxjn5fcJ8EkE9L8Dfh5HH+Vvx2d0YR8dw+Gz3BCXb0HgX3P8HeCt2lgI+JfE5z/2zydcJLb/c4DPGvJn7Ct/XyM+bVzffjHsS5D+D+Ai+hNdgvhSUP/rAJ9AkP4q4PMw4/98+meAn91am83g00f4+8AP5vCfb4njyw+AH8jhq94ay3enS8X5qwEXlX9v4HMJ8POBj9O6/jc8YXoV/ALgswvwe3uU74ke8nm2B/4y8EUE/YNXgC/EYPz+ba8CX0DwfaePgc8o+L7TOJeJ+Y8LXMS/D7iI/zTARfxfB973b/KRxHHN4f8f/x//H/8f/x//H/8f/x//H/8f/x//H/8freOvr//C8jeso74P/w0vmysUcrvaQbVa8nO2F+Dcq1cCt+zk3IodX+X9wPKCei1V7JomQnNDdbdUyJWDXMmt7FytBX6u5jkFZ9itOIV+e5FF+q0g8NyheuD4/Qva1XLNLTlev1sJHK9ilRYiIXHfs2O6voO7I7um7FqN5t083Z/yrM0cy7OL/Sv0z+u4tf7w5g6NC795Mdi/CC7JXhZ5qo54Vrl/GNyRj92XXnKh3G5upVDdze/f2QXxTDosfalecHCaSqcyS6SXHEilc/UwQ3bVc/Cb380PCm41VTRGEaQKy+aqNafiV+ue7TRP/dJimVQmlR7Olf2cVauFEkjZ+kxN5z7fIJi3q5Vhd0SV7uDAMg265fC5Sk+JQBx+bvcl0stAIKIHIy7t2znLr2RSRbk0IZ9dB1JJshQW3E9J0q/tbPtLaQrOL1qwt9xufhZGZ4yWWwM12eKE4lLNQVdzC92QKsGOIgGzCgUvlaQm8Z90RcIEpKVVKlp+UTaRs2tNOonnqcqQrRSTdbEkKkM5U7HDKLsVPDpk+coZ6/SOnltRdmPd9LfslO3aHnlflSZnlW4FVVnVlVtELZRa4BdklanuqrLvauBNmctmYsityiaxvT1qgXLb1yk6ZNoquSMV2TyE7jG/6/Aesumqtl9TzXmH1IM9akYspWyVSlVbthi+NewgrrN3Vs1CbPhooAK75kq7wmD3IF8YShWlwsf+ebMD0eViDVwvNW4MNm4srUVuIGsmeTs7A0sqEkxrlYZJzeYvo1o8IT22vBkz5cWNrOEct+gxZRjbHDMceCll01o8lbW0lZzJswktFRBsF3nQUJGTsIi9g6pzaTJdcik9uSA9n+sll9aTg4BkXG7cMlXwZFxaVYBbDXtQHh7o6LaOFJTDoo7QIopo9TtyyFYrMk7S5cGzA9m8W3ED1WGGmC/S2o7vB0XPsQq+VXM=
*/