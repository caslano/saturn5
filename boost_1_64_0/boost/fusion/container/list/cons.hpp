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
TeprDrMcZWyE6OE+1N0Yxj+QsQ2MdTjRJuPqfs0y6k6lDocYQ3QQVxJ3Eo8QTxCbT/OxhRHTiNcQNxP3EI9Ms+p8rGAFK1jBClawghUqI/wj9f/UUSQ6c5QmAKdd/+9obdPqbGLkGSZN6p2SiHlKe/InStV1ZdmTXYmw2coeB7+4jDjXpJ56LjNQVm+ob1ivlqtOcRTXN0RI+hpJHfoGSd+NxNkss/AU6Yufkp51uml0pSdrppQbS5m4tBMvR12zPg87q5puYx56TfMwMycxVXJyenkoz3YeKGncIvXzTqmrzUJlO/vu8ZhG3dYuf72GezrzTLZ1KLZ229Yxum3tJ2X7Mg+JSdb6moS41fcHafM5s5yJGYb66cjq5vvl2FNueXZl9Izvi+J6y4OSrt2yL3bIvsjfWzpdsgPK7Gci9SGl0hZi3P7lGmvT27qMyqqDONNjcJqPbXn2jc3p7Vib5nUu3o/B2Veto9n98ReZV7163eajXXf5XZ/d/9JTj7UZZ5PfEjnPfKsa2+63k7LfAGyP7TEQO2AP7IhDsBOOw86YhF3wOMYQC2X5G2T5Phgpy4+V5cdhbxyHmTgeZ+MEXIsT8UachJJurs+e0x0oyw2SdAdLuntKuntJukMk3b0l3ZfI8lcS5drKNde1/HPVsnBXSJDl2/FiTMHBmIrzMQ2XYTquwql4M07D+3A63o+ZeBCz8CN04Bc4A7/FbFSu9bm6fB97ynO+z5d0NZd8t5B8Xyj5bin59pd8t5J8t5blF9jkOoa7Jd8NZN8pob8sP0yWG45DMQKT8VJcgJG4HgfgVhyIL2IUfo6DsQrLH4LNcCgGYzRehsMwHYfjIrwMN2IM7sAReKicY7dSPnjWjd/q7ditlE2e1eO3ejt268RsH1s+sYB4mFg9h/fP5Vjln1awghUqN5zR5/9p9pSJzoycwHhHdkol9f9PVp7/pa1WqDz/z5P2iXnENQ1ZdqH6G+2Ylnx5fPHq45MykhMzZzq8eba+lmXRXsqZp3vuyVCfQaYxUZ57JC18UMPTrNgfn8AtfN/xkFlanNkZp5GOKK3dn/NyR7K0NdOmOQJLt5d2aG3fAkrnQduen0geFkvbtwX4IOsu3OohD0rbUy/awrnnIw7b+hrzkaBNy03MmJmsvlOhOukqIqYqZSrbSt6pEGLMi/acuK1ByTscyJ9hP62TsoJD0q/hBeI9pGvTIyZ5pLN+em6ymr+4MvKXYJK/NHS9M4ClSttQB7YpnuZ6JYHsZ8/Hlr88U4+U43wY8TrWlWB2nKfzlojTOLaMx7ix/ayvtPMezzbsgRE4nXkLt6vp0JIQE6+U+7nScERW6undm3u0d2/WOG/bLq0tvJqWIv2+lPQd1d4dkJOcJNv0GLaxybR4NqrMe0I3b7LdNS8rYN7iacrM0kab6ewrQ1mOr8zLNObj+7LNhhVvM9nYctwx3ew8NbbhDNGmJaXNzJymTsvn89tNlGnhgTbJU4xhPc7pDpmeJnlV5pWsam2OC9mobKvEpHg53jh32nLs1CVfOXz+eSfbV38cEl3zsyDdudJd9neI3HJex7nXCpehsr+LHjXu78QMV9+fvDKOt3yT/blUvz9l2sqS/antn3Um+3KTzXxfFthK78tCNOxLtk0j5gkij78pZVWPSRs+2cdtdOVwUdry2A+ynYrLmhwey5o8lynF1FCmv7vIvuKuJj88crTxlA8PLH6yw79X1lSnujL9vnGz476uueLO+QUNiw7etWqf92VQZ1tZk3nZkaeyMu/Lprwtg/q0hdpOOKTOw0N/LVi/2X/yl188tHOapzLJU5dNRdnkPkfufwLYNjUxVFfG0wC7oz/2wEgMwkQ=
*/