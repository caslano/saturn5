/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2004 Daniel Wallin
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_DYNAMIC_HPP
#define BOOST_PHOENIX_SCOPE_DYNAMIC_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#define BOOST_PHOENIX_DYNAMIC_TEMPLATE_PARAMS(R, DATA, I, ELEM)                 \
      BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE_ELEM(2, 0, ELEM)                      \
/**/

#define BOOST_PHOENIX_DYNAMIC_CTOR_INIT(R, DATA, I, ELEM)                       \
    BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE_ELEM(2, 1, ELEM)(init<I>(this))         \
/**/

#define BOOST_PHOENIX_DYNAMIC_MEMBER(R, DATA, I, ELEM)                          \
    BOOST_PP_CAT(member, BOOST_PP_INC(I)) BOOST_PP_TUPLE_ELEM(2, 1, ELEM);      \
/**/

#define BOOST_PHOENIX_DYNAMIC_FILLER_0(X, Y)                                    \
    ((X, Y)) BOOST_PHOENIX_DYNAMIC_FILLER_1                                     \
/**/

#define BOOST_PHOENIX_DYNAMIC_FILLER_1(X, Y)                                    \
    ((X, Y)) BOOST_PHOENIX_DYNAMIC_FILLER_0                                     \
/**/

#define BOOST_PHOENIX_DYNAMIC_FILLER_0_END
#define BOOST_PHOENIX_DYNAMIC_FILLER_1_END

#define BOOST_PHOENIX_DYNAMIC_BASE(NAME, MEMBER)                                \
struct NAME                                                                     \
    : ::boost::phoenix::dynamic<                                                \
        BOOST_PP_SEQ_FOR_EACH_I(                                                \
                BOOST_PHOENIX_DYNAMIC_TEMPLATE_PARAMS                           \
              , _                                                               \
              , MEMBER)                                                         \
    >                                                                           \
{                                                                               \
    NAME()                                                                      \
        : BOOST_PP_SEQ_FOR_EACH_I(BOOST_PHOENIX_DYNAMIC_CTOR_INIT, _, MEMBER)   \
    {}                                                                          \
                                                                                \
    BOOST_PP_SEQ_FOR_EACH_I(BOOST_PHOENIX_DYNAMIC_MEMBER, _, MEMBER)            \
}                                                                               \
/**/

#define BOOST_PHOENIX_DYNAMIC(NAME, MEMBER)                                     \
    BOOST_PHOENIX_DYNAMIC_BASE(                                                 \
        NAME                                                                    \
      , BOOST_PP_CAT(BOOST_PHOENIX_DYNAMIC_FILLER_0 MEMBER,_END)                \
    )                                                                           \
/**/

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(dynamic_member)
  , (proto::terminal<proto::_>)
    (proto::terminal<proto::_>)
)

namespace boost { namespace phoenix
{
    template <typename DynamicScope>
    struct dynamic_frame : noncopyable
    {
        typedef typename DynamicScope::tuple_type tuple_type;

        dynamic_frame(DynamicScope const& s)
            : tuple()
            , save(s.frame)
            , scope(s)
        {
            scope.frame = this;
        }

        template <typename Tuple>
        dynamic_frame(DynamicScope const& s, Tuple const& init)
            : tuple(init)
            , save(s.frame)
            , scope(s)
        {
            scope.frame = this;
        }

        ~dynamic_frame()
        {
            scope.frame = save;
        }

        tuple_type& data() { return tuple; }
        tuple_type const& data() const { return tuple; }

        private:
            tuple_type tuple;
            dynamic_frame *save;
            DynamicScope const& scope;
    };

    struct dynamic_member_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename N, typename Scope, typename Context>
        struct result<This(N, Scope, Context)>
        {
            typedef
                typename boost::remove_pointer<
                    typename proto::detail::uncvref<
                        typename proto::result_of::value<Scope>::type
                    >::type
                >::type
                scope_type;
            typedef 
                typename scope_type::dynamic_frame_type::tuple_type
                tuple_type;

            typedef
                typename fusion::result_of::at_c<
                    tuple_type
                  , proto::detail::uncvref<
                        typename proto::result_of::value<N>::type
                    >::type::value
                >::type
                type;

        };

        template <typename N, typename Scope, typename Context>
        typename result<dynamic_member_eval(N, Scope, Context)>::type
        operator()(N, Scope s, Context const &) const
        {
            return
                fusion::at_c<
                    proto::detail::uncvref<
                        typename proto::result_of::value<N>::type
                    >::type::value
                >(
                    proto::value(s)->frame->data()
                );
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::dynamic_member, Dummy>
        : call<dynamic_member_eval>
    {};

//#if defined(BOOST_PHOENIX_NO_VARIADIC_SCOPE)
    template <
        BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_DYNAMIC_LIMIT)
      , typename Dummy = void
    >
    struct dynamic;

    // Bring in the rest ...
    #include <boost/phoenix/scope/detail/cpp03/dynamic.hpp>
//#else
//    // TODO:
//#endif
}}

#endif

/* dynamic.hpp
PxIubodfqebjkxlyVzDPSafGtXnOGnNfNFmwtnIapuL8jmYy/FWumUiZk9FUPDcZ3UtCcFg+b6Fwmvk0PijGQTrTPvBHuPEEfbJOV7LpR/+EDh/s40yhiTbHhEBmyrLiVpzIaFpnTknO6bit3asV+joNfaSQyFvmDp2C6i0+149B2AnLVEcazVzGihXDOD26HdKj3KfAcsx9Kk9wrJi7lRP/SaUwcavZmKm+7tXwrFjMVGVO3Jk0n1BUbkevOqmEYXRM6pWWTfwFU9wZiGz5xC11xLQPetpXKbh0lc1FTbTV2ZmMI1NOWgNxZzNmVNhrfhlXyRP/fMac2psQ7ej+LBDaKYhCVhRxpDqhkiZ4KJomBeRnMqJbYcX2/VnkOmVaVlVcXGFoptJ5FD/Fhj/VtrMeAqKk5ECT5kaHw1OIcgxlPGrGYVUfY08lclPRfEzpjsPQHKBop034J5PKDx+Cs9d+K7rXxovl6Gt6K7HPQsZGs8kZ299pc+S8p5q4G8VwVI0xOcLJ7gBRDDslMRRylQ6FWBqezqIk5SbNQiq6D1FFx1RrIe23KknqPKzyl1JtSXHitCWLinJKPdXnHDEU8fUwThiXlBL/RJyzZT/6kgRym1tb5BtVTMPLhzMlG83aB08lXHVrFEzFwclnbmct+iSf2oCxiFJCRC9LdstDNKjnKQuF3J0GrJyk91mRXCyfU/jpvQnLnMCVCNIK6GkTGulaBd+VXfF1iYh2fljRFHL59JQJUbiq40YTXGtCB29n0Ibl8ojKkYnkjOA4bkTJWvQrUrB/Cf4UqSbCahE/pCBF6U7vgzYTcUjJ6hsvcFF28Gi0E43gjgXlZgVLHIyTjsR5QMSVTuNPdCa3tE5JF75qnCUkwfhmIRfVyoKKSF12Yt8j4o2PW2ypADqdKg32OfQImrkS2qAWWugnUXvzY1Y070PH+YtRC5fBEjoUXzRkMZThyLg9Rjb89JQpjCUTMWpV3PRCrNKNAZNKOZdIHz4o/UlUCK4gHh6K1EuXQraz4jQaFCfcajGTtzgm1uqYld9vofRTo4aCqt2cWkpXbMuE1r8FcWjyqPa5qQStVeY40yXc4n7HWdgUf6fQRTAGiVAcStoAOjR/rB5WAeWYjGtkbsNNg5Xi8ZG7bZf4aDyEyl1AHVfDB2lUZPjAtJKR3CNJst09jJcfN74R+fBBenPBVaWSC7BoochjwsqDgJZ/p6hO6voTHNP24xSNJVy6l6LhkkDCC5mkqofuVlvo5TsBlII81Wjyk7EMtxP4mIEHCgkn4Wn+8CAPplP29wiqwHD+J/SZj5pDIb94ohZnZqot5+Gcl5/MdIL5Wd58ZWSmx4I91WHLxqU5bUUjEv6WYr27RCiOEm6PnQK6UaHn5olUF0HVikRlkmXjcJ+H7sAZTKiYRBSHTz6bFHzqCfNQvjQOGILH01OYfLhl5/5E6KZjGD3nUD+mTWmu+BYaDV+2FWJQmKs9YnoqTRBQCh0T67Rp/8rDtMg1mU0IvR4v2ptoEk9qdSJODVZVgqYZVBLNaG4mpYKEDj22laUsRvari3o4TNIHWlUU1Wjah0594WRv5yjGvN+ByKgRRMOI0ok+mFpGV7x5vcmdzOczOSpD0zMyYndwuRJJg6oSJzSCXMRFB5Yp5LmwkDIlPxMYKGAKXpz1qGxy5Clp0g1oMwNpMPCiOj4uE5sS/JSNS40Vt5B5vTnQ9UwjjELGpWQvLTJZFg4cGhWT6uGEBu0nBoiIagr1oRSfG34h0PH1lqq0DjmDDlGCQ0dT3cREAblNlLQy4aHBHJlumiqRL2+yhelU9y90NGry5JHQcY+LSbRE5aHJpyl5LpocigGtmckcTac=
*/