
#ifndef BOOST_MPL_LOWER_BOUND_HPP_INCLUDED
#define BOOST_MPL_LOWER_BOUND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/less.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
#   define BOOST_MPL_CFG_STRIPPED_DOWN_LOWER_BOUND_IMPL
#endif

#if !defined(BOOST_MPL_CFG_STRIPPED_DOWN_LOWER_BOUND_IMPL)
#   include <boost/mpl/minus.hpp>
#   include <boost/mpl/divides.hpp>
#   include <boost/mpl/size.hpp>
#   include <boost/mpl/advance.hpp>
#   include <boost/mpl/begin_end.hpp>
#   include <boost/mpl/long.hpp>
#   include <boost/mpl/eval_if.hpp>
#   include <boost/mpl/prior.hpp>
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#else
#   include <boost/mpl/not.hpp>
#   include <boost/mpl/find.hpp>
#   include <boost/mpl/bind.hpp>
#endif

#include <boost/config.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_STRIPPED_DOWN_LOWER_BOUND_IMPL)

// agurt 23/oct/02: has a wrong complexity etc., but at least it works
// feel free to contribute a better implementation!
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    , typename pred_ = typename lambda<Predicate>::type
    >
struct lower_bound
    : find_if< Sequence, bind1< not_<>, bind2<pred_,_,T> > >
{
};

#else

namespace aux {

template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct lower_bound_step_impl;

template< 
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct lower_bound_step
{
    typedef typename eval_if<
          Distance
        , lower_bound_step_impl<Distance,Predicate,T,DeferredIterator>
        , DeferredIterator
        >::type type;
};
    
template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct lower_bound_step_impl
{
    typedef typename divides< Distance, long_<2> >::type offset_;
    typedef typename DeferredIterator::type iter_;
    typedef typename advance< iter_,offset_ >::type middle_;
    typedef typename apply2<
              Predicate
            , typename deref<middle_>::type
            , T
            >::type cond_;

    typedef typename prior< minus< Distance, offset_> >::type step_;
    typedef lower_bound_step< offset_,Predicate,T,DeferredIterator > step_forward_;
    typedef lower_bound_step< step_,Predicate,T,next<middle_> > step_backward_;
    typedef typename eval_if<
          cond_
        , step_backward_
        , step_forward_
        >::type type;
};


} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    >
struct lower_bound
{
 private:
    typedef typename lambda<Predicate>::type pred_;
    typedef typename size<Sequence>::type size_;

 public:
    typedef typename aux::lower_bound_step<
        size_,pred_,T,begin<Sequence>
        >::type type;
};

#endif // BOOST_MPL_CFG_STRIPPED_DOWN_LOWER_BOUND_IMPL

BOOST_MPL_AUX_NA_SPEC(2, lower_bound)

}}

#endif // BOOST_MPL_LOWER_BOUND_HPP_INCLUDED

/* lower_bound.hpp
jFgU1KvtPAinJMC+Rbvrr4Bpb4WYIuWTteXWhOyKeblpc5uHP0V4mB0OcHYFDCXYL/3A3LX5GVSIWp2KtwWBeanN5wboK05SO8Jv1VJssy6WjGL+2GIi3ePJ/SO9nKekoJtbJf283s5T0qwNMGtA+kkmvVUQzjfwAMLX0zmvnO7TOgn0vRJ9r6SVPTArPf8MV9Xde7mq2AXrB6R/0CteFX/s4VTxTz4PlpAacGDurnympIVZq8n9Pke2WV1Eoc2lUCeKyfGiMsXZNTA38yYi0BLJ4lWwrUzExMkkQMTE6YQdHttonrDW9JcGcxfZYiRkU2LpvNQATd0OefRShQci9qtHOO071QsRgrLtk7zOMbYnJZtKiNJTzAaEU6gcmLshpbgpGlWuMEYSeJsHXUi/pWJSY7m4QtnyU8RkvoPMnci0N2Y4dbITN0Bvah7HQmoLeeHhd9H9tCcUe54ua/yrwAaFFpdp1MkvYFDDF0nhfDYc6E6+JoIeDXGkQNDSplgKCRwVYYu07GiD3RfuHG6j4OGotLkrq3HZRxznMpfMW6yXqBGamo4nauprIcLVap0ODxFTG2KgrDU6FXNypUp9RaeyhyL7LJX6qk6Fb4j+kopBaIlhT8QENpLvWINPZqj0VQdEdf//qe/Hkf/T681/l3p3G/47RK+YEK2YrYH947/be8Xhv8Oj+W9u0kHzXz/0/4fHnm/Q23SSlRdVIOj7DdSDZroHZX21wq8RfDtIgVT+mZ0qWlewvMY0KhQun8biwqBHeZYoNGSV7oySMYgnBD1WgxIV6+zaqHxOpm4PkWZcj2bMSUEzoGEL93Rd+x0rRSHkZ7lL5KoSx1EJ+3jqsZwnuIPZAjcEcMek6A6eA0VbJfRxonlE455Igkcx1DBSSk5Aye+aSQ3bdZD5T6Cm1rrglFkP6ZuCLJpkfuUzCAN2POk7We3Rw76URFw8FJNz7jPHKDoUSqGVgUdY+kB08/eRatbHhoZAAzKQVg+jaGyPojrxtFal+MLDhW6msebkNpfivKfChZPfmLbiSXVYNdG5Vmd7xF/wYAEXfc2paDp7K2EN+6UdUQAdaEYzztiPFCRAeLh8d3BVNACug5CE/z0fE09wbBrvD9slfDq3wdc2xkzpaGPMUcmshpx7WfdrkFNqASlHbkpXbQRG4tNMhDQtzOZNn5Qy5wOsw4rqTnf27d9CVOR+Wg8F/U00s9e0UdkMGydW0gsLPlpZhT6BhfZ9iZegF9J/ggXPqw2W6YzF7e/zr9qeHVd0QHAxYCL0KhY6AHnkiIRvy1G1q7IeXFln3bQ//Yj8QUs9HlMjyxnYUwP87lsTlP6GACDI9iSejB1RzkZpcqoK6E3eAhvlqdbqlKWU2LYndAn7e8Er4TmivdfS/snyCq9UMOUdpYV2OCvHdoa/l5XVkGhYrFaXNafpSsIXFmlNzu8S1X5SMJ0NTL+w8XsSZRiT/L2aIaYSfFhMxlC4FJUp7TwjjmsRuIv+JRzfItC+v/z7mb5v+S/4GH3vILqLrBn6C2uh0quuXKry+8SL3wCgFqKpJ61UlX7bwwPbMPz8ful0zf32k6kq/tY1TWostuaEseYBBmtrhW5rRUqxUPYKWTpvcwZ8wmNpkvnwsWHMreyXlspJ1KUZ+hI33J6S2+a10XsM2X/xYwFyti88W6Jk4foClZ8tdVC3J8S+SQFRvc04c+mCKw4IBH/2oBCwYFU2MliOBhSKLhKosmZM8U2FHyH113zrq/XP37WtW//89uH71m9f1aZ2/fYd9cA/sQ78SfHx2yNpTpHoqu/EetSXUEd9v/PEzQ964rpjngCOmlbTPpCgCyYnekInE5jaU2ls6NmcVvM=
*/