/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONS_07172005_0843)
#define FUSION_CONS_07172005_0843

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/container/list/nil.hpp>
#include <boost/fusion/container/list/cons_iterator.hpp>
#include <boost/fusion/container/list/detail/begin_impl.hpp>
#include <boost/fusion/container/list/detail/end_impl.hpp>
#include <boost/fusion/container/list/detail/at_impl.hpp>
#include <boost/fusion/container/list/detail/value_at_impl.hpp>
#include <boost/fusion/container/list/detail/empty_impl.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    template <typename Car, typename Cdr /*= nil_*/>
    struct cons : sequence_base<cons<Car, Cdr> >
    {
        typedef mpl::int_<Cdr::size::value+1> size;
        typedef cons_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef forward_traversal_tag category;
        typedef Car car_type;
        typedef Cdr cdr_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons()
            : car(), cdr() {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit cons(typename detail::call_param<Car>::type in_car)
            : car(in_car), cdr() {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons(
            typename detail::call_param<Car>::type in_car
          , typename detail::call_param<Cdr>::type in_cdr)
            : car(in_car), cdr(in_cdr) {}
        
        template <typename Car2, typename Cdr2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons(cons<Car2, Cdr2> const& rhs)
            : car(rhs.car), cdr(rhs.cdr) {}

#if BOOST_WORKAROUND(BOOST_GCC, / 100 == 406) && !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
        // Workaround for `array used as initializer` compile error on gcc 4.6 w/ c++0x.
        template <typename = void>
#endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons(cons const& rhs)
            : car(rhs.car), cdr(rhs.cdr) {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        cons(
            Sequence const& seq
          , typename boost::enable_if<
                mpl::and_<
                    traits::is_sequence<Sequence>
                  , mpl::not_<is_base_of<cons, Sequence> >
                  , mpl::not_<is_convertible<Sequence, Car> > > // use copy to car instead
              , detail::enabler_
            >::type = detail::enabler
        )
            : car(*fusion::begin(seq))
            , cdr(fusion::next(fusion::begin(seq)), mpl::true_()) {}

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons(Iterator const& iter, mpl::true_ /*this_is_an_iterator*/)
            : car(*iter)
            , cdr(fusion::next(iter), mpl::true_()) {}

        template <typename Car2, typename Cdr2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons& operator=(cons<Car2, Cdr2> const& rhs)
        {
            car = rhs.car;
            cdr = rhs.cdr;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons& operator=(cons const& rhs)
        {
            car = rhs.car;
            cdr = rhs.cdr;
            return *this;
        }

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::enable_if<
            mpl::and_<
                traits::is_sequence<Sequence>
              , mpl::not_<is_convertible<Sequence, Car> > >
          , cons&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type Iterator;
            Iterator iter = fusion::begin(seq);
            this->assign_from_iter(iter);
            return *this;
        }

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void assign_from_iter(Iterator const& iter)
        {
            car = *iter;
            cdr.assign_from_iter(fusion::next(iter));
        }

        car_type car;
        cdr_type cdr;
    };
}}

#endif


/* cons.hpp
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
*/