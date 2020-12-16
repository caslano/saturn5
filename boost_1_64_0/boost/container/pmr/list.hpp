//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_LIST_HPP
#define BOOST_CONTAINER_PMR_LIST_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/list.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using list = boost::container::list<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a list
//! that uses a polymorphic allocator
template<class T>
struct list_of
{
   typedef boost::container::list
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* list.hpp
nNkLjtoPC5HxWo5s/mwLrEDEFb87dC6sTNSyqfrD52DVvBYxX15PhmV9oph3a1Ss2bTHjH9jqUNY053NV6CWXpbzJL7fJetXLKKY+3Rqj5mpBeYj8zEzvy0OSzzdKec9rmRmJ8fOjLJUxdLJ/MzMfh6WR+ZlZu7DwopMnczunldTDasUdv/61Q/AGoQ1LFozDtZOZjNr/u25v8B6RS3n3Vm8COY6IzruwhsO3wbzkfG4wvN2fwKLJ+O1mPvosDQyp2WWIeI+7n7kClieEhcm8zM7Imn1EYdsuqucxfloZtfEwSoVq1asVrF6xRoVa1asVbF2xToV6yazmJnjGKxf2FNJ1lCYeyStI24r93XAAsL6bjjlclgymVN76YqFyGxm5hldWFi0Z8YZrEzkNPs6WJVidSKnmX+BtSq1dCu1uILO5g869z1exD1+0QcXwtLIeC1HtdS6YdlkXmZba8+/CxYOOve9OOg8Xkod7U5XObNhsROjrFKxasVqFatXrFGYOXeDNZP5mP2U/UIHrIvMZjbyMf+1sAEyL7N1fZ3Hwqwzo9sz82cwm8xiZtYtLKhYIhmv87rma2GuDDJe521F9g2wXDJe519PXwFzFZI5LbNixUoVK1esUrFqxWqV5dKoWKvo+7HNNf2wLrE88549OgYWUWpxn+VsFpnNbIjrhmGwIBlv792d1z0LSyHjdd61pq0Blinixtw8fjQsX5jZL8FKo3Oy+7B0bsHsFLqHYs6JYPVkHmb8+eRGZn5+vKW4ZmanCmtVrF2xTsW6FetVrF+xiGLus6PNzDnCLGYyzlbMr1hQsXjFEhVLVixVsXSl75lKXEixHMXyFAsrVqhYsWKlipU79n2+q5LZiNjbBuPIqhWrVaxesUbFmhVrVaxdsU7FuhXrVaxfsYhi7jhnsxSzFfMrFlQsXrFExZIVSxVm5kpg6WReZuZ7h7BsMpvZ4kmjmmAFwibN3l8MK1NqqRDGx3yVMHNuA6tR+lAnbG1z20xYg6jzwtpTemFtwjaMqhkL6yHz8rjf7n8WFhFmvjsC845y7rtPsYBicWS8vTfu862AJZP5mOXkzBwNyxK28FHX97Awmc3suyuW/ggrFXbxtnOuh1WLWkJ9c9fBGkTc00/9fjysTYnrVvreq1i/YhHF3KOdzVLMJvPxcfZLfhEsgcxmtu6Gr2GuNDIvs9P3XQdzhUSced4GFhZ21sKOEKxUmN993eWwatHetTNK/wlrEHELXv3jZ7A2YZN9F46A9Yic5vtnsIhYLub5JZhvTHROcw0LSyBz2hckkVnMzLk3LI3MaT+RwUyuvyzFspVachXLV6xAaa9IsRKxzOr/83wXrErYbcc9vwXWIKzi49E1sDYyL7PUCyN3wrqFvZz6y65DFnYNsDpPi50+WCeZK97ZPGRBZpP+0PI55s8SWFwg9u6oubUkMpvZRv/OfliGsD+VHPseLJfMO2js99jp+VYWdzoZ/2Z/uakFxmshq1SsWrFaxeoVaySzmPFnPFuVPnQrOXsV61csopj7HGezFLMV8wvjzzkGFYtXLJHMO2jsWpT2ISzuDLH9ZZBZMLHvyVbichXLV6xAtLcy/repsBLFKpScVYrVKFbn2He6z8XiRsbOj36nULE2xToU61KsR7E+xQYUc51LfWf2TOWM12BeMi8z8xwZLEjmlDNesURh5vkzWDKZj9muS25JgmUpObOFmWMjLFeJy1esQCwXPiZKoutk3xOY4apmOc/k44ysVrF6xRoVa1asVbF2xTrJLGam77BeYea+BSyC5QKj+xYw33nRZu5bwBLJeM4f4tYeB0sVcZXl+e/CsoXtyFk6DVZI5tSHUsUqRU5zXgc=
*/