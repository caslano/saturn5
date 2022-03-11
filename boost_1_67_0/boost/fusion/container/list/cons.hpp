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