/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM)
#define BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/container/vector.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::deref<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_of_impl.hpp
eXo08kxKlWd+Q8FPitlnek/nmOm9vDCNdO6Z6vJ+ja8wUbE4jXTxGuV5ZmrEl6q82b88AoovxnuerhjveYbFqPOs12/CKMViNPJM0MgzMVWe6XONPa8YzPKep2OWxjibpc6z25ZOO6kf0IKYpew7RFtr5JmAlodZyr5DtLVGOpjt3QJme4/PqZHONVsdX8qzcjFXNPKMn60RX6o8x0bcbkLxzfbeZo45Gv0wx3ubuTXSRWpYjIbFzfEee6JGOs8cdexH/kpXhPporvd09rne2yVsrvfYY+ZqzBWN8hLnqus5+fQv2WicxWrMlViNPopV59n1m7sF9ZFGnnEaecanyvPx1y9jqa018gyYp9HW89R5Vps25T7Nh3ne+yFGI8+4ed77KFEjz4D5GvWc7z1PF1oVZinnBaIuGpakYc4F3i1Gwzwa5ljo3SI1LFHD7Iu8m1vDEjQsYLF3C9OweA2DJd7NpWFxGpakYc6lGv2nYR60YGYp50uirZd5tzANi9Mwj4bZl2uUpzZ1eWpTl6dh9jiN8tSmLk9t6vI0zL5Cozy1qctTm7o8DbOv1ChPbery1KYuz6v17GRfZYAVYu9UBUqVL1V/YkbFHGsMMIhZ0vSDGxQLWCf2CML+WhRfVbF4tHbMttVcOInyXI9nZMx6/QvuUp4bDHCRWcFsfgupnhtxz8Ws46f21RVzo/Vidrdqwc2KwSb8LjmzHQ2rV1HMhdaY2bhclf5IsRKOhE1yna8KEX1pnUdL1DAP2mBmk58nuhSL/F1cV4RNTT99OJWXyuiagwb4WomxzBZHfXcoFoeWh1nKNUfUE+0as4LdWjmpnlvEWYKwjg+DhigWtlWsPcJo7UGL1zCIF+NMGI0zNKdXq9QuEq2asGoQHvH7zuGHFEvUMPs2/LwDsw1rWtxRLA7tILOYAfX6KBaz3QATmHVt2OeYYs4dBujH7FS6/WmpLmgdmJVpsZjq4topxoQwGhNoYV6t+BA32ihhTogIz7nrTAfFAnaJPhI2/fWedYrFoG0Wc7M6DCvXvvaNNIrF7zGAG6T1WFpiiWLOveL8TFifTxcGUzq0GszS7m28heqyzwDZmYU4T6VXzIG2ldm7bQ+iKd1+AzRj9Tx0LHMpxRIOqOuZLqbeSMVcB9X1fFjOlkDpDqrrWW1OzCDF7IfE+YSwiQ2G6ih2tN+ZPXmyawelOyz6SBjvI4eGOTXMpWFhGubWsEgNi/m/Js5wD8t1ogZERBw6ec+lWCJadmaWh7e60vkuWkWdtA8x90YoFok/aNNWL+1Fq8gxZMfFvBV2YWL7/lQemh8zXk+PhiWhRTBb0dKnCT2XOWGAScJq4t8m7f3l2ehJA2xh9uzz+LN0nnVKrru1Uj+LRKvOLLSOrQ2d12lYwGkRgzAZA/43tDxk6meYLrQqZOpninFowcxU13dWXu3UZ0FoQdLU+/czWBcy9X4l7Iz3dHFnvJcXr5GnB62KNPW+46x3i0QLJlPf2yR4teLD4JyMoQ70KE4xoDnR/JhRDGgutDzMKAa0yHOinsKonmiJaMHMUuoixsR5A30esx6Id8srYwLNwqza15YhNHbR+jHLX7VSeTrbRuvALN35LOXoHPqC2DMLk5+B7A1utFrC6uPfsCfG6oolohVkdrnN7t8Vgz8MUIrZjP6uZoo50dIyKzrvR4JiYWhl9dIKZK2eSTFHoliThX1Ju9ehWMBlA4QapF0a1Ceayrsqrg/CPnvunFMsHq0xs3kToZJi9msGOMZs94VmCWTXDVCEWcVhU99TDGguZtnOzMlCbYbWg9m0dB0uKua6YYDSzO5VXn1NsRi0T8xaH+13hvL8Sx1fBsetFRT7TQN0ZBY=
*/