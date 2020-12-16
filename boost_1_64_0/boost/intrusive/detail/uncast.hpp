/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_UNCAST_HPP
#define BOOST_INTRUSIVE_DETAIL_UNCAST_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class ConstNodePtr>
struct uncast_types
{
   typedef typename pointer_traits<ConstNodePtr>::element_type element_type;
   typedef typename remove_const<element_type>::type           non_const_type;
   typedef typename pointer_traits<ConstNodePtr>::
      template rebind_pointer<non_const_type>::type            non_const_pointer;
   typedef pointer_traits<non_const_pointer>                   non_const_traits;
};

template<class ConstNodePtr>
static typename uncast_types<ConstNodePtr>::non_const_pointer
   uncast(const ConstNodePtr & ptr)
{
   return uncast_types<ConstNodePtr>::non_const_traits::const_cast_from(ptr);
}

} //namespace detail {
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_UTILITIES_HPP

/* uncast.hpp
q7u+/YFOHdu3G+1syqn+ggpBBtbpY9WdLe2sEj1TQanL/jyrc2h9E/lF3n/1t6tlmk3fBF7XzznkldoS1ZDuU5YJnrm4Hxog/K/oFNT9IN6n9HP3nHu3i/5Rr8f7OodXj7ANjsM2Ds8dU40+dLC/8Ns4FlnD595GRd2WrCgrrhCXbnf12xhi/YJfMR55sg4Oi/Mr8Kb6NPW9cwh1Dl7Vc4/Z3x0R52/QLmEfW2iOQ4qnWrOvekXwXa9dzPGPDLSVfan0i+H0izba+iM4ttMDu4Mecfn+6ZLo8Hzk5Fhk28+mB9P8hd9PWe4zxkaibXyEj11u7+uQj+P4SApwu+D5sTYfkl2r3Pec+cj+E/SssU2cvxj9Wn+V/yC9e/8hr/K5uS/w1mj/9TJLeBF0M59/dBPlQbCTcn0oeGeKZy3RtwzGwTT60GkOYyLkHZPGa0sxeZ3fmYjnhXtcjoG/3SF+trrITV805jR/4bezL9oOug+6lXex8TO8XXY7BlfeJbS+iPySL6Esqc68OI9j6r6I6RXvs1W+RF613yVJvEnkdeq3qsT5m9hv8f03ZOdgnNlvXSH4bjT7rUNp0GlYaP3WZX2wZzH4d3n07+786csuHeFP0EfyJ+kduziW5PTMMFz9nJXRNdDHOPdKH3xy5V8ZXUPzr4yu7p+zMrr+p56zeiMryDAC/7iHrIE5kKHcb7PKVX6bXTB9weLMPIRVNfr9RR5hh1X4qW6TQXq1OK5LSw2I5Yi8ISvyNvoQyho90iprJXh9KlnL15TnLa8oxvAin7Wc5fVJdXxHH51XT6wv5FPXMfmlZwL3+kEW6ney3lAmjhllBtZRi0LvxdC7WqU3HsnWFrurI6QP6G/wbqGoyi5ucJC+R9tZn4nUF+XhGMozYnNS15pRVl1fTcUYmKmriFs6b+Hs83V3FLK/nOqsZ20Yvoi8lb5YPdoq5+vgrVPIKbmikPelNuStk3xxV0LbvlgXhi9CFosvokxbX9wwxqr3H5FHg0JvuqKrOmoIwRcbwvDFl1Pd++JbCl0fhBCNgbqWFa+HK5aWnpxT6EIeuZzDp1vL6YpnjabAckw3iuPcCSd7Nkk+dGVi2z7UFIYPQRaLD6FMiw+Np771Y6363g9BWoL0XVu50pWuLZLvFArecm+FynckXnN+pYu6Uuhp+k6hOIbygup0Z7o/h7uYUy3ol2n4103oiBkvos8uKCrKW15a4G68V+sW2n0I+QPmaBaXFqnuQ8grtz8hluqeFrzu72mDZMBH9ArmmGEfcX4W0uA3vl0sfk/XUvFeU36u+al4d9Kxc84D7jtpG953sk8QNlDed8p1XX2GX4B0CjIO9CN9nCWwrkvKoHpJkeWdrnp8xVJ3XoiirmfyBt7ThxA723wXGzy3lWXK/b9vvFrX+BhZV8wPXrNqLbqrgpJSd/rGx7jXNz7mX6/vMeC7nUKPT6yOx2wfT0Edt9g+DsKZIm5CZtRTmy7NfHpJz59V3Prl4lduDz3OsTqeQuhxCtRxte3iSoQeT6Gj4kzbxc/uK+JW7Lj3h797/qnLTlyZWJ80OubT8+zjf6vjfNvHj1DHm7CPw62O+2AfX0Mdv9wu7oZ9fIrjjBuNj3iXUg87norvQ6Tvo6XvWEch4qoX4Pv70nfM0+R3sY5CfG/F93XS9/Unv4sxiWpgCehmfl/DONZZxholrqeqDoob7WWci7XAGOA64GDgeuAwYBXwAuAVwIuAVwKPck2Dj/lewHz19AuY7xjGx04HDgCOZ9znCcDTgWcC5wInAhcBzwIuBk5i/jWgFub/W+YfD9rK/M9hPOnpzG8mcBJwNnAmcA4wGzgX+A3gPGARcD6wjHGpveQ=
*/