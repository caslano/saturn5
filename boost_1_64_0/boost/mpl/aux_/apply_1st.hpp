
#ifndef BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED
#define BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

struct apply_1st
{
    template< typename Pair, typename T > struct apply
        : apply2<
              typename Pair::first
            , typename Pair::second
            , T
            >
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

/* apply_1st.hpp
a97hIJyUStwdnBZob4x7QPrsSPtlctwYyf+9HvQPsI6X8dvH6m3XEdfUVH5+2DHgGrvCd6Afug/4zIyb7VcySt4p+vitQ3qrES920MqdAwNQCaKWcy5ANWg4OXBExRYcC6uKZnAL4gNEdWAfwuynwE2RSpT29igxZ0wvslQUhSDwL/Jw0KgjZ8DE4t/fFpve6pxkP6bFzo+kQqfSQNpiSUATD/eEc4jYgpq4l1viI7Zd6sKm6i/lGUIfdkEjeoomm6Ho4yZuGl/Fij53pwnjkBT4LYcSD86DZYQ6RcL8WPzklmKKSpuz74+8AnepqEA/vW/uEbsizXXh2ynC540LX3sZKn2vK5jBwT3CHlRCeMrDHj/jv1By/DMnmIA+3036IzbCvBa0jiTMf+5ShLmXkgUVAucUIICY/D4I8vsgsH0zFYz0YFZVNxmnAQigj45GqujTs0Zq8pq2iOTTnGpLtDr8M9NI9MTDFZx5RUQMw0xB1QxS7qmQNBWkTWXL8n0+yQEidYn3r2lE7N/F/MhKl3gUF3mIqSH2pAdG/vUVGfKHW/0QnQPy2ZpQaMGifL7iwsPDmbD4K3/fKUSuihKn78C0Wx0WfdHGIvmqXyUtWxopk/41DaFjpOv49wTlAXcDU4z7Okt6fzM3ctRipBzJJ+L9d378+3Hsjcn3Z79gkvvv+iTxv63+o/HVD6SwERhpzBM3jNdcOSXqhhG+XqQumwdXAvmeYznGlZSGRV8y3LYz2ymcp2LxiVq0f8IDlKZjc/ON/gca8HITOARUtyt8PXWisW5ZmrUfxkPLkGr7qVlRextoV3/FcGrZD9aeKyz1/Py4y9e7rNrH4prLIrA56qDwijVKbGaphdeuz5GwOVO4/0nhQ5uEaEsdNc6QFaB4uH38SzVK4JcxGY+FOkr3i5L2m3+VLTZXHfn9eeRQxmDF22dXQuKLC2TSz7ndaH660efPxHZ4VBuQNM4PTMYuwrbeVYx9FEN/r8rQ8vA6RvZdRbiWkPCJI5BSWuh4sHAkJnzSaOTf6GJC+L+MNaF14AUGLTObfphQmV7qsGLl+RhVnm1EuU5afShTGDv+73XJz3PrybHlH5feEJvemV+S+HyH8uLjl2cmJ/avsX1ycnizkvSff21s/JKL/X+F5G/sryrcQ6ZpVcrAdBBdSI1YHD7tf3qpFTw/Cf9kyBX6fOFqjgim71U8hOwxSnBrvgXLbslwwOu6rrq9tM/d5w7BVG+Pi4hcUfirAusVi0j94fYQOIrfsmAGAvtV75TGIdBPtyKSTk+vXs18K1eoG9hUD3GTqO1WtR/Q3AChA1FFFgcoexPzqWRbwWw2mPFz5rc6nqkrfA468Ip880vgDq2HLDs6AcA910+FjgKP7x+KgJkuwxO2tiso//0XPwlqTIwvr52k4htCF0U9xXIYUmPPX7OZe+Uj/4KMJOUzSRn1h4+JNLbkaOVimfNGuAkpsN+BfZOYG3YuhfVQTE0Pt6dkNQ3dmXRZDZaZeie2ku9EEULe2Ah8B/baX0cD4xnXqXTs4x2jj668gOTvx0tkXb7HE2xjnK+7w0udu0vAD/gskPy8h66Kj08eTaF++dWJ8UXrqxLnuwcnzp9zanz4Bp8aFz7TdW20Pd/2q5KP58VAYnj+dk7i/K5GAvovhf7/fGUC+m0IKVVKzxZtzCt60A8rtDSQ6i+suGLmWjrkkgMv77zuttxuDdK+KWUpTwrv4aXEvEG0TBFME6QLIk37rSeIT+hrnzkxWl8bFkHUs7A7KcCxdJVvZpM9FWhdXxijDWXpwDyPHr3F7+R6k0n527tJSMQcpDf3Mu+oarSnhoOswvdud2mwRHngFV/Kc8z6dJA=
*/