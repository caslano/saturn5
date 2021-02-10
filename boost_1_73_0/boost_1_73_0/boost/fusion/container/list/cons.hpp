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
C9RNcDooycwfFGLIE/CgwWcVYKCtulomWRTgQK0yJwVegepZAMquBZ7Y0o8Lyl3A8NAxU7MAA/SKgvTCZyhZhR99hDFwtGVYzEmyOXFDS8nUosyLdfBSRynoy2MA3lk7Dac5V+Tjej9S7GLNgmOrG0Y/L8UDyA/D+BBE5nASArhLiSObXFmhWbOk7vJ8OFNhnKUOfsprPg/KIaga2PInivhsfoO/J+Ws4ZuOBD3wK4r8LDDkY/A1jGigrln/U3Xnjh216u5fp01b6qp3/b8QfB9fD24G/fGHH/uji8sBC6PsrVc8AE9MYVEU3ZVAiAfg+Ory58FZvWHJLY9pABPcke3In0/fjnouI+/Y2HOhM8kdERKma8lUIHq89o46OT4+bqtv61/hao/oG/EOZADYAFsw/vvbV9D9zKhU/SkNM91ir5oadNXgL9fDG/Dhxx9G596o/04oKHgAduHINUb1Up2BHVpYlHjSVn3wqYj1lyg7wucIVYAXMzBpIDpphPoeBZBCyCQ/L9pVmJDSiUJzmCFMHLtDYTCWRMwZwkQHZhIKbfwRgKgWAIW9oC01lLyYWc/Czz5y/G2fFQENuS/bkP1WEV5nGyjelLBkaRUDQkEFhyBbRJW2FYSzmWdDht4irzzYGDSaESDSCfnH
*/