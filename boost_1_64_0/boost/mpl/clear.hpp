
#ifndef BOOST_MPL_CLEAR_HPP_INCLUDED
#define BOOST_MPL_CLEAR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/clear_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct clear
    : clear_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,clear,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, clear)

}}

#endif // BOOST_MPL_CLEAR_HPP_INCLUDED

/* clear.hpp
BaeCWf6v+A78J/xgbxHfkajzw/bFPeWcY2z+DMnvHLY60EvOFcbDt39yoj6Jmmvfph4np5WNzrcXy9cxOFiaS2fBYHbIJ3dcmOjHeIqPF2f9fudjROn1v92FX/Xq3E7HKy5GxJm5cc7+SLNHGdoH05X9HB8QBgr5dKs3v2pXTXulHB9OWv6ui6LKL+ZXKV98UfLyAVVemv7Qee6jlROg/eeLTcG+KSp1AFYBY0JSycyo1PZy0nJcWWhcE8nj6Lvl58r9caJ/wTOlY4G+vdi3IIiRkD3RuZnBus0jovRS62Ht/zlBnOueMOeTHuoBXZiYidu57na982y3u9Q41x3TPWYxeaa+WVOofvW53GTZeQ47Bz5KRyBFjuyLSmwPczk9e70xEr6/eGExwZPKbtyihTsyxUiF4z6Cyc+dvecAvOVk5L4EnwYxuMfUrT3A0kyPuoUXqt8tFp7vs5nenjvUsPvv6ZYj4bQTXEaCWlnJ1eroCyrawehxWsEHoU/OBaGx+XJd33+cgv8df875yk/Pjj9fGYBHhRiiaXfhHPdx+S9lMdaaPfDe8ES73vN13OL/SeSAn/9B9xB9Wpz+ehnv86T+k+iTq6kulV0c0MckdZ5E9tMiJwF+Bxds+66zTR+rWNKSPIbdJosk2TnYKXdy9D6MBzsb55/1pyWx3+dg/5t0ar2C4wJkW1HrO1nRDbJvOxYrOFwwF8C3HOuQw1FGWQ8xR1l5OivnbSR82p8uRL3gRp/lCLvAAPhAXuuQc6+8ViPzdnmtReZnc2Ki4/3cGz1Ais5T+Yx1N7kP7BXsbWMmc11yN95TlLV7iAuqvWaSYSTdGQcxSts3udJaefXp5e8d4/ifYIF+nPNOizql/CkDJYq3RQpU5W3M0sWrln2kOhxr+NMjfCJeHIvMHVYjQKgMh4mFfbJ5addNMB4vlzO1aox36guonUf6meFOcLSf3dOM3uFSXdRm6BVdjNmiA9p7Wo60zziu8rly9GtRVyRjC3PDcf/Z7qtKnxrfT2tOfvvkflqfSrMHydcAfdD+b1Co/KRZQaFSN71C1wqQZkVJ2BH+XaFoKbAlb+NXyo8V5jN4RUyHJioM8fhKTTOjazovuqbvFwq3SFb+lPOiyg/iVynfnV8ps96nTx6fQ+zIaWptZ48tjNOvZP8yjaZOYbx+FQhJpa0KE+lXuEm6ieRifBhljmkLwJNZWguQBPfPHjrTuX+UxbgcNZ3SWeJfuI+arpe7HWbg0KgoBrLxROSkw3LR7ApmI9ZEBtBJw2hXguSK0EDx5Z+BQu6FRYAvoB5vako1LFVqQsjWgNnfSG5X2cnimQT1L/WpWUfYZ4nF354qtekwS+JP9dY4EQVRLb0Ui97BsYtu4NTgovukSF+HSAHJnYhIyB2kDIjeFNTKGDjbkd30GK79t2FOjn5VTpw8OtBWtK70rBmBb3Y0upIZgWkyAhWdmnTWRKnUctYku0lnTe4Wv8leGOUyWbPipa10xCWRaaxg6WENg/vACUYGjWUFy9RO3TQhSv/KkmS+q9uuLUByfFCRQcf8U/QvVyyVrtZHzvmmU6x1+v6rfAnhcyyWV17at4kPH9NxyGd8AVGj9W1c2BvxPaL507Tvu+6DR09wtJI6hRuuvN5IFqj6SK9wjnjE2b84Q7SFuDVKU+eEc1/HezTvoy6GrikspzrKlUeTxz56OmigGXex0kjKSSOhlD90jLqYW81P15iPdEFPdpohmiIU60HfE14S9kbf3qZcmlog3KlcG3Gc+O9WN6k9SfdDDp2u6Bvgi9yBpI5iAjvdvBx12ZLyeLZ296XOv85q4+X7706S9fdz2jY/Lof2TUlpyjE7WYoU5eo=
*/