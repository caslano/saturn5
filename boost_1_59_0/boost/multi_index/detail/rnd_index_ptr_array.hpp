/* Copyright 2003-2022 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RND_INDEX_PTR_ARRAY_HPP
#define BOOST_MULTI_INDEX_DETAIL_RND_INDEX_PTR_ARRAY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/core/noncopyable.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/rnd_index_node.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* pointer structure for use by random access indices */

template<typename Allocator>
class random_access_index_ptr_array:private noncopyable
{
  typedef random_access_index_node_impl<
    typename rebind_alloc_for<
      Allocator,
      char
    >::type
  >                                         node_impl_type;

public:
  typedef typename node_impl_type::pointer  value_type;
  typedef typename rebind_alloc_for<
    Allocator,value_type
  >::type                                   value_allocator;
  typedef allocator_traits<value_allocator> alloc_traits;
  typedef typename alloc_traits::pointer    pointer;
  typedef typename alloc_traits::size_type  size_type;

  random_access_index_ptr_array(
    const Allocator& al,value_type end_,size_type sz):
    size_(sz),
    capacity_(sz),
    spc(al,capacity_+1)
  {
    *end()=end_;
    end_->up()=end();
  }

  size_type size()const{return size_;}
  size_type capacity()const{return capacity_;}

  void room_for_one()
  {
    if(size_==capacity_){
      reserve(capacity_<=10?15:capacity_+capacity_/2);
    }
  }

  void reserve(size_type c)
  {
    if(c>capacity_)set_capacity(c);
  }

  void shrink_to_fit()
  {
    if(capacity_>size_)set_capacity(size_);
  }

  pointer begin()const{return ptrs();}
  pointer end()const{return ptrs()+size_;}
  pointer at(size_type n)const{return ptrs()+n;}

  void push_back(value_type x)
  {
    *(end()+1)=*end();
    (*(end()+1))->up()=end()+1;
    *end()=x;
    (*end())->up()=end();
    ++size_;
  }

  void erase(value_type x)
  {
    node_impl_type::extract(x->up(),end()+1);
    --size_;
  }

  void clear()
  {
    *begin()=*end();
    (*begin())->up()=begin();
    size_=0;
  }

  void swap(random_access_index_ptr_array& x)
  {
    std::swap(size_,x.size_);
    std::swap(capacity_,x.capacity_);
    spc.swap(x.spc);
  }

  template<typename BoolConstant>
  void swap(random_access_index_ptr_array& x,BoolConstant swap_allocators)
  {
    std::swap(size_,x.size_);
    std::swap(capacity_,x.capacity_);
    spc.swap(x.spc,swap_allocators);
  }

private:
  size_type                        size_;
  size_type                        capacity_;
  auto_space<value_type,Allocator> spc;

  pointer ptrs()const
  {
    return spc.data();
  }

  void set_capacity(size_type c)
  {
    auto_space<value_type,Allocator> spc1(spc.get_allocator(),c+1);
    node_impl_type::transfer(begin(),end()+1,spc1.data());
    spc.swap(spc1);
    capacity_=c;
  }
};

template<typename Allocator>
void swap(
  random_access_index_ptr_array<Allocator>& x,
  random_access_index_ptr_array<Allocator>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* rnd_index_ptr_array.hpp
TIhEGcRGAG/YrJjXU7NzNdDHaUZaQWg4GLNs2bf9ubZz9c2FRGf54rUR+mEQ2EJ4dhU8bzThdygX5M2lQ7hCFOnwXs4HeogUVL7gJGtrsbK7P0g8izG6tipDS4HPp+urL5L5ZIA5IaeNb70Uhp/YjxHDyJnpsWpt20JrtGihPT3Ws379jEH4pldn766d8gS7v197jkhM2WFQ0MXLEXd7M7od4aPNxGP+ZD0+wCRbwyIlR59YVh89N4dfkdXEacXlYileWBYZvTW5oBn9Yd7IUzKejTGyw9EHtaqZsQL36BThfx6JNcAVYaNLfshrt++ugMxhAUcFvSQD6fGnh/QW+NalQ7CBwSNEHxPdNwTQRgmHXujWtxltpaqFZrAAFaPDjPFB5DWKREe0XZhoHhzq9kgZb5lRkDatfXG2dbYFeJ1ObhTb2wunGYTTsEMbLfmUPEU35IUixz6kmewrFFvO2vsHpwU84SrdTOeX8/YpzsVntM+51r6qx+Ql+PcDFzOsnlWSi8qOPydpzdt0GNke7Vjullo8lPzODaXAxLJ8kaJYCa9fXAUmuQq66KYM/YCsp9HjG/MSd9++LbOSiCgvxCbpQOrzhGKqwpnxi5mq7dpJWzL5K/f6rdQDd4c+tRvC6QfKCZ10IUHh5arUI44jmxPUaWa/HT0M608uZ7narSRfLn9d4Qhk8Y60dAx8xhwuWju06ND7EZjHR+6z6/MCadSEnkYS227d4XQjH7X0fL/acYbaNJQBPRFOmLk3d2BF3yCP0HnVH1mUNSxKDUpO8+CMw5Y4DqymxDml4HVj6E/65GPqy457FVoyyNelpEzpf1oy/7BT93VgRbOtosjDy8RQ5N4oGRDHrsgQxz5Qw0LdrnKeAogchfFs8i4mo6cmIUL43JCRt83J3KZpPLQ5/vA0bx4SZ7p7WwbttBUUfJZY5cGLie9piR1xKohAdn4LJv5tMKJX7DaJ19UhGiF93zr28VcAfBXNThnFW1BcnII4o3/vNdVtQnxCEwQj0HdGWeAJVnRK4GFXMOPTjWS4Rk+3ubfEq1jgSTbHo2bpEdOgf1xahit+2zED4/yXfHvIoOyZzGODpqYNIqb4Bnxl1ttJhS0JmB4Y1kI8w5GQech+pxm3V3OqHy5W4p+M1+M1MN/RdANDFLAnxbPCRDdms3PaWEvXfGQwbj9kUweovY7TM+QfZsTfMOASQF2fSolUoVRY0RatcA6P+3ALWz0q1FPVC2B612fs7nFm6n/50M9sI5DjiT/GLFNRPhndYjPb5zSGVYbP85hcibjKS3pZBk0x5CvLg9UvegxbKoASNySERk8qABAWfyyt6C935gRnOnDPbLM5nI0OxyuLEnYier6pbmxzHLWx9tBPSBJGFNYpwYdKGdzs+CyalQvcQfM2Dn/bwEwo5/8NWWpQhsbucHdc4sis5o+Q4Dn5/ci4Np/Jiw20L9lxVDihmGkdpVLf+HibUR86p0+sYGaPbrgVpzyMOLl5ccj/DLLrwsTNx8hth4aJUP6jtzLmqxx214m0rP7V5lMazQr1JxUaxg2Vtu1aszQZuz1H8QyoFTB3rQI8HbC/b2B+YKtpGqhmTAVSZERHTrqy5f5Y9uaq2o5UettD2yDiPVwvYI3REzL0NhSNbUD8qrIITeaItokAz9rKIS8KUOpgKBodYIQEeRWo/GXEednhM6NyFY76qDqoxzGfHu9MrqEfeSMNtdaSB2RHB03+TnSyYV1hx0hWuvrirCvWXgckKREBXVMrHiBcKX60wC9opqTe7Jkwomuck5yeQ0W2LgzPQRMlcFtLBNQhyxju5NOIQORNGUF0jLLM36wjeLSvrQYB1Ogo8UR0xF0HBSTp+EPdwz6A1D6AdxfGmIGH8uwATPoR2wotS81Vw7TWFv+mJ2tFPs2IIH7jtPUBkQVnvaxeqmkhol92aIXjCF6kDZ0i6UulPAstPN3TOYp4YkSZAV3U7KpRGYF0nDICZA7b/5Q06QNHwTY5sx7ji0UPhsCDc0wjDzwMGcbgzCsP7HLl0HAc1kxiksJ/4TiewBPWkD5TOFhCxe9mVihAdFxSWtQBNbwD3D0sMpkGbroDhWDgSsGCWrDMxCOr5nCcUpoHOMB8HhpUhUmQ2RcV7m8yhGyNHaeg/TwS4bGG3QO8kAzNQTdSqxK8xj7ftadJDXkK2ZItyPAbcEhj2qhPqL4B2hOD+bkdb+ROFwZaLt6L2cVellgzJ1EpXJBdNiJW0UtoR0f/o1ROspPUBKX0kANa+Ntd4aNp0Jua3hElGC9pQNiq1EPpJuJxBFBzBYr+Juu45agPa9ScnoQjfgpBu2ekkQKiPksqSmYyEQkseiTYt4/5DNCWmNORejLOkEIsoSxDrq9LjNnWMq2FVfuzmNWRSPKSqJ1Yc36qKuM/uVFGXaXNfJZgjmJl51CuOGlCec35+WIUeyypvCP5DMXYrBrchFbzXOZXYaC9SwzsfU+Ak5U1j5sM8ih+85YOPvHstJeOly6XHa+XbpedDpx4JbfOKYCzfg3evrMGEMk1GajrdoTl81Z32WKweAPDrzWXqNnz+U44D2L/rjst3eUFU0wGA4sq794D9otaT65EcePNOsSjEkZWSz6jrdpLi+wX/qf6vJISZWNIuVtM3dbQLNiF+wVrxzsKoPfKzHMbIyeJgAHSLOb0YKGHD1PXllECZPK8uUOuVPcXiiPJ2SgaVi7LIk4L+Em1krsufNdqWKLpA9EYYOISiS9haQ0KGUr+2PREHrw33NSUVEB9snCpAx8RZiRRK7qqoMcJprBL3YwIA0clXXNqEB+4AAXXO+RmV4BQUhICZ5rRAzdMm6Q8DTdtxAypAdcvvzAFu6jRp0WXJ4SYkD+NB4VGmbxRZkLN7vpFrlL3LAmh/k63sA39cQvtKGoDE2d5OF8IFMJVnfd2VFDxfAMR4QhgxXKP8ULKccz4F/aWvlBA8tjqc8qnPlnFFQmuuMuKCbtePBAZTq1w3ZFH8ZSMSgkcm2ICmFinYLpBFJ7ECRxVwv/8mGpzghba7R/HypRDoOUxl4/wKlfSeUEup5QcUddqRZvrLAUSLu01XXlDU1zxYr90c0E1y9QXYs5hCjlzSZ6qu7ECV2DOLeppFPDOD7fOJ/Sz+iZJtKoIAtBNarO/79DQGke34yIEfd8GZhoIYu+YXcUWLXV1JYg4evPR6DmGqOCs74RZgs+IqLOlQuvOUL0g2Ce50fVr4eXC9oYQm/4eQW6+j1yEjH84bVK+g/r1+d/jrWf37y5BdlVaUy66nAnG2JgAaN0Is3i/olRYWxKT7jCDriyHsVTPFFN1/vN3Whqgrycw67VQfb4aPzBTLnggHMrt7TFBqUsrLonYWC+QEw/8mhELXKIXC7y5ym/KlnlO0b2YW/FQlc6oZLR++4p4Mc1T2fuGuS+16o8ofYZ2lb68arVHWUhnAB0ykc8cE6FkcgsHZ9EW6BVByRKcI6NCYl/TyP/SQMkU7COjgs2aaRj1Dui5hLbB/jQpKDpXhl8zWy/fAfGgwnNKRoG9fuH6cgS2GsT01YP9FLpFPtjIgtC9a5uPdu8Mr0nl1EJa6rbxP9x7qLjBAWSk3qcZfPEjthLeuqA53DjjPR26I+h+iYrM/wDdFLwZuHJaF3M5YHOHtC4oGMWxb/ZNr7ZZnA5RI4sRQR+o6F5UcN6BfVeJvKjxuno4PTe4q5Whl3nA7QD66QlGr5yPQvJdmf2Mp9YH2Y7cj24/nCkSMrzA6TytfYB3etDdT9FidsjkTjjs+hD40HeUvNzM//hB5aVIT62wciHzEHNcWYtaBTT6JmARVyLafYxsKz4xy0we+MOJZgD3+LKdCMF5gaRg2vWOPTsQES/aVTRbn9uUfnYtUcMsgm6elwKYOUQkC/+OhVHv6tsEU6AHVBr+HgVo5kCRDiqNjHFHGipAj8IXmsC2VsiqSrlrBRMBqwGLWVG0df7EnhGYv51PXIdWkmpwE8s85iEicKdeARBOXepqBXPN4kssn+1+fivj6wGO0ctOACcgCpi4TEBQuoNeIph2ietSJHBkK9/W4N8OLmidDbqo5iQPC7OoCUBaq/kGm8tkwCbpN36Qi9PgX09UevEX0OmeAbgIl0h+27EqOGI+99YxJixg/CQ3s8H/nTKxlM/HjKyUDXeRDQzqY3zQ4skamCKiq4ABtNw3gCoTdREJRIUPutTSUT6Hk6Wr5hhDwGSNu52ZgwIdXIWHuvRLPv59+YJZkNcl1M/96UlZL02jqpkeUF7gFsIiuot4srMRPNGEVBCElGpis8E/nKC0wxSwSRtc5ev9sfudyBcoepEJxU5sDSgWFykRJuUt5J9Im4cVnwAdpu4xPhFj5jAIQ76Qx4g6GWczbKlPgFDIcUEBwJrpwF4ojqwXOSpU6TjfYDOo11FhnRecYunWV6A1NHR0ATNuqPuhU/ANPSFb8xzt6ga+QADFsU8izh6jHmEjLqIpH+We38I/BSTd5oabnIQaXctP1HuD9p6oTJn8PZ5euxbymylDZK18TmGugurvfjfH3xP/tpE+FnNAX1vpkQCY+YS6CKsE0hSjMmpO9iGRa4YPcrcFPlBg5+GwU9dyoeKTU4m9mOar0Z02wz3cKztu9pa7e4MtA4qFmsP5ckF2apFA8WWHOLiaZoDX3/EQSUXdPSvxiLbJC+XJgu5nOXQAGLAadGTAf4uDUrxnii3flI63wEOKiiQkgtRk/fsUxpq7+jGlCMfiXhtuVmAJ5+CXeCCVwDuK6eVDrCcv8HyGBTSJhsAGeWj9t8k+ub9e3aDDRgqdTa1nKw3qARs6giobgJ7m4D7Ia0Qew4yuWtnAsJ3hmFXiLlDsrt9e2GJhp/ZMRPgjBGnSZfZ0or/x2edh3mT9Ry7lb/NPxKHJcc6Nf+eoSQfBXRCljrydeTKda1xndX0QLUgl3uu6CfY1GgX8llyfrwBh8JbPtgvTEWTIYG4Zet6GIprW3gqREPSnc68NEybidxM3kfFzLo2Z3yVZwpi/Txpag3k4DwY3I+T9SkcE7D26/1wQPUYFMnMhI0uCzNYEfdIJmjlBknUJI46pbpigGcIF/kaQLovwbUWAHshWhdQRGwKBdt8gG5aLCpEtAIuiqCm4Exd2r2ZBwJ8nsBzJ3gh2SzTgXC1o0hwMeI6tsCQHg1SbV3SMfeARs1Dyvbmg8L3UKmidpmiN9towKeBpLI8Pp1ROaSTisCpZHivURDhz8dkCxK0CGgvolu0N0tgE8TPU+2BrG2qSKeBUSVUWejZO8nYCNvMoXcB29vfvrvntb2K/zVbCh41xivrgaZSyST0PifuTgoI7Qce+K5f8HjsCLp5sIMI3RX43uwiOCL9hbYHt0+4rNma8z82wNweSGE48ey6CKuBUAz7iPSRzeBCUWGJulIrOaSQiFXaE0ka5JgFSccsa0hc11tLXqr3SQwENGGTECFEZHCRqPno85z5TPs/jkYGhQvLt0LfPt/jTQ1YJk/vzNE/SREqANKqtgoIVAS0zh0v4fSSU8XnrD8lq512PC286Ne75v+VdHAr5jlsjhRf/rHAsoFM7FRWdf0YpVFB0x1ybcuaPFJMAC4oEpJ8Ht9AsvmZzXzo5Dfjo8XFQBHhGIkkD8B4kfnIBkN4FsVZ8EfPaBiKDX324AEmYaQrMqyIfS13LpLUPkSOcogIyY2Kh/z3GNxE8ssOSS0ro8LAea7NuI1haj86hlWO3BzoJ1NnB67KCRpVUEHBB0D/x2CaWiI4zuUdp6KtTyNTSka0qSfn4J/G9GxTrC6zmEV8yEFymp99hLwXafssEfjUQfAbICGFIlstLnncFGgfT6sZC2VFumCH03faFzEf8aya8BDGSexWQ8XU+J1Q2yZ5XRjsHk7IInLVLxscfDzmFzMJW1UjCO8IAMFdmkNcDni7OJYPx1yPegZ7ASr5DjhtMVOcBBbZuHa6UirdvS+yO4w2F/+QvtTI9fSpGqS+FVLQmfzxkCyZVVMeWBi/fO+0qnmB9bxz+phh1H7N59+hK5Gc+oBY8L0KSyOJn/Stu+5c+6q+8NFrhGFQE3Z5xU328wVzAxJJUeuU95HPifBdXP/84wvc0x2gOJ9wxY2CEKZGnVGaYreQwv7iqFqcG6LxxE+0f1TwWjaaisfEMsoqqzEqgH716e0b6KIjk6vxlwsgp4vX16V1bLah8klHgzGHpnzpF0HrZQ0TT7dX4NWw3zQO+lvj0WOtyQuCvlmwW5i9D+LGD2Wh1pETCK8zzomrw1NU1yUxc35+9Yo9BTAFsEv3WQVgNS2By0VlJiQH5R9/QBXZ7nG0hKIsrks/dyHpy1j6QVZCHRaJUfTpagojFlnloOcYpC5sfaNqWVhP9xzMvyf07ujU1Jv8b3UoBYfYKmPvvJln0zmPDW+stDkkEHxH/3jEhyf4fbQpT+txy5KjNGseYR6Wj5oRL3328aHISolTSbZXnUfAkr1ZtYVZvr0J4dZ+ebSyFdI5cxc3ESS4rN4ik0kqDat4ldURij5EnLEi7PMEY8ZAr14rpCjnFV4dSrfgif75qXFhO4VPRxuUcog+PHqAlw49K4a0BtBnP5r98IlEFbJ2q4VJwUzetvNw4z9gtbDSNW5oXcgsCCkx/gHPEe2VW8tnsYy/Dr5ozqFIT4aMigWsqnCjB8/rUHx57uWUbmjikReJgxNR/DM/hE72Lmo0Lc1TdPCQPq5xi6FqhwBb4nmar/GeTI7dJcGUZgum/RL/Gok6a1Busp98tbTlhRZpx6ErdeVIa5/jpZ03I5Qd1e+JR6j4PSIrS9hhNVKbHVI9uUR4dCDgGEnVN5XiGRE5DUVJZpNsS+spFoOXf+Z7iNmy7GqOnzXxSKvmJHBmVE7XzXY9qxOda9y/+EJ+cXpfWGDDUp9W/G0wAas9fHxcs1dvRpfMsTiAIbWVIYw0oDJcTiGd/Rk/D5zv44ve+2CVDPeafcAhTQ4/yusdYFyoDYoIm8qCdSaDWbfNURmoEm7zJ4lxMqk1XoDsd+rPWLXPJu1lI7EZS5IcGTz3D8f88D7So8BNC7LDildVHJ1+wx49JBjZLXndLSL/Y6yBHsYLnyR8cSVbASHqhrx0DRzHmX6dTNFFt88oOEyOiiKAnRKCaKTDj0+UIWQ5s5BtPQ5jT6+rz+mIHI9/SCe9vdBqxy2/0eAnObJlxPK1wJOMkQxZZbZWDKPhf9ogrITcSfbJ2CTx8+nfmB9qOFNEBFLSR9V9Z4h/qAwZFoadaX/CiOyplgAFpwcQe1WQQblhbigM714fOpy0dhd5EoHPceb33Xw62mLEi4rNFpeUJbKUwJjRWCmhiio33EwOdcNJqligkJymgFWA+sPgzMfsT8bpQUwMpAAAs/9O2mebRsEubtrhUHuT6TwlwzkotGWsiuaU9r9sOVMq2UDLKr/z53BioUkHPMS0EmPJATU5lZKLaSRNmYkkHg4AJF4ZcFoacfcTPXJAuDbA57TN4/sOVRrScqAq0qMv7J0oip+Y0R52SUcSVd0Aa8vbb+1EbKuYmgRqdmUgxU8h4gDNagrjiWhOOhIsq/ze+9tysiWCttr6xPdMr7nHm2c0OQNMzzZaEJfDDWaLk61NFslwEob9HlfWx+z7YtsghSGxXRJPo
*/