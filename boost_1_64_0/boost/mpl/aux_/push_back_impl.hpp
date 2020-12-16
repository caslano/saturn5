
#ifndef BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

struct has_push_back_arg {};

// agurt 05/feb/04: no default implementation; the stub definition is needed 
// to enable the default 'has_push_back' implementation below
template< typename Tag >
struct push_back_impl
{
    template< typename Sequence, typename T > struct apply
    {
        // should be instantiated only in the context of 'has_push_back_impl';
        // if you've got an assert here, you are requesting a 'push_back' 
        // specialization that doesn't exist.
        BOOST_MPL_ASSERT_MSG(
              ( boost::is_same< T, has_push_back_arg >::value )
            , REQUESTED_PUSH_BACK_SPECIALIZATION_FOR_SEQUENCE_DOES_NOT_EXIST
            , ( Sequence )
            );
    };
};

template< typename Tag >
struct has_push_back_impl
{
    template< typename Seq > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::has_type< push_back< Seq, has_push_back_arg > >
    {
#else
    {
        typedef aux::has_type< push_back< Seq, has_push_back_arg > > type;
        BOOST_STATIC_CONSTANT(bool, value = 
              (aux::has_type< push_back< Seq, has_push_back_arg > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, push_back_impl)
BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, has_push_back_impl)

}}

#endif // BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED

/* push_back_impl.hpp
zQ/ZZ+1TUD49jSIXzKTSi2P54ls3Uaqjz8x2bkDB7TJap/SBWnEK341SyNLkChMv/ANXLfShbtkJ8Yjz/HG+DiV+G8QvKKdAZW4bv2ORjSe1wuyp0BDaP+UTbTvWB2uWfaLx84xo+vI8dnC4B21sEGfrZBZA6KkZjYkPoePVBuiVP4Imf49n5Z+GkOzbrTyspQJ+xt+5ExdD5fr77F2/zzhqWEDbXm6hee6ROKynDPlaJ2SOySLnovvc7WQEJDeZQW1xJ94/OcRfXNhIr60z2Pct4qhvlyXJY3pwNFPn72+b0+tpa7jreWMas70TN0+uJr3DN5hZiwzNkXNhzEgPGl7qdLLFFOoiWfgwvpGejA1Bpe41rJ39hZe/8aXMvu08Qj4N2c0X4WTxCgUdgexUYD5FfeiP+UsVsbPLlslKWJPW2i7WGWiEx/Pi+fb+y3G32YUX5D6kubY9XEHoOe1YG0n+y0YJ7J2r/FOxE/0xXQ+tbZJ4eLyCFKsr0UC3uMfyQJqdf4MdaAjE2etT+UOBTJt11LGRmx+gojKJH/84GRG10rxUMK04uPINjvvfp0JtS+4eVEXLc9xxpqIcMRsV8Nh1HLYkxHHROwKsySCdrNMHk55wfzwJP0Ii/dyYdlESlVzLh7FvHDrq+vBLKbtozcgXPEmjjUQndrJtE9To8I1sfqJ7N0LWajNPzUr6ntWKUUUZ5NdLGsanLsCo3J41vVxMM+I203aDfqi1nEayT6VJvsic5l4PJdP3MbRkTwL8FIdg/f6TVLzrHFtmIcCalp/h2Xt+0ITnhvRjdxXObNDieX2ryUo3G6GpZ2ivxAdS8uNQL5vLN+UaIKyvKKXGFmL0zh0I/HIEr3saaG3hHTrUp5t3FS/GRVkndrXfO9R5j2Xr9siQUdQUln1gJGlULcW+IR3Y5iWHZd0ZZFXTwxU/a0Er0YeinCyof/0rZv14AkFlNtfuHgjxHyeo3OENCSXG8cn+GfgoH07jOsLIIKwPbbYndKzpg+mTldBLtg19NObBbKkCXC7dwn39LHpyNpbmiCTAaMwAaM/rjUijMZTAN7Haij60WpazoxNXUciLVr4tbAilfQnGm9e+0J0ixhdZacFEU4quCCtQ7y4ZyBc6YLj/DBomX01Nc2fRnBJhHNplhubdOshXTKGxLcKUeGQT1g9/i0eDIvnUFQ3kPvYo+9C9mEYE2bJ1adl0JccZniOVkL9wAUaZjMaoeFt2+Vo07OXdoWWlQSYD9Fhw630q7xFHTPkc2r8/nUw3OcBK2BBNlW/oXuJLpnm2kAZ+LkKCfygstnxB5ukfmOQui2qTs/BtKMX7kbloHBFB7pOE6IvYNBozVBj7f0zmI0Z/p5QiHz7B6zhSBTTMRWqgZwaeG1yNZ4m5CNe/C3GvidxSaCmqitoE38Ut/Aj+wGJCCvCmazs380+DhIgK1xI7TOcM36JIbTkc3Gv55ne5tKRnEDulX06SA9eysHgrun0nEN1qM9HUVMCT5p3F+DZ1djZDgQonrGRytzpIYpMMWyFlTXrDKnHswE4qL/zIGnIJXrPDUdP3FKYPD2cGrBrLg5S5qeYZOmJwGWM3tyKncRq2S/Shu3b9KMXfFArX69nYzQYouxCE70pnIXfcil+cfBjPWw148QkhKOkosIDiJKxKXEUyj0+TSkMw33xnOX76XWeRyTvxvbs/mqWSsd8uABNGTYSq7EnatVUR9Q+W4NCkK5i8dyhNHihJnyiKnXOwJefbUrSlfBtmvt2LDQMK6WTEEWoROgfrKBGM2WYi2By7GVoOY6k76hbk9LNJceERdm79d+jVbWT7RrZhWZU0ljp6UWf8LqT5daBX+Ee+TDQ=
*/