//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/utility for most recent version including documentation.

// call_traits: defines typedefs for function usage
// (see libs/utility/call_traits.htm)

/* Release notes:
   23rd July 2000:
      Fixed array specialization. (JM)
      Added Borland specific fixes for reference types
      (issue raised by Steve Cleary).
*/

#ifndef BOOST_DETAIL_CALL_TRAITS_HPP
#define BOOST_DETAIL_CALL_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif
#include <cstddef>

#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/detail/workaround.hpp>

namespace boost{

namespace detail{

template <typename T, bool small_>
struct ct_imp2
{
   typedef const T& param_type;
};

template <typename T>
struct ct_imp2<T, true>
{
   typedef const T param_type;
};

template <typename T, bool isp, bool b1, bool b2>
struct ct_imp
{
   typedef const T& param_type;
};

template <typename T, bool isp, bool b2>
struct ct_imp<T, isp, true, b2>
{
   typedef typename ct_imp2<T, sizeof(T) <= sizeof(void*)>::param_type param_type;
};

template <typename T, bool isp, bool b1>
struct ct_imp<T, isp, b1, true>
{
   typedef typename ct_imp2<T, sizeof(T) <= sizeof(void*)>::param_type param_type;
};

template <typename T, bool b1, bool b2>
struct ct_imp<T, true, b1, b2>
{
   typedef const T param_type;
};

}

template <typename T>
struct call_traits
{
public:
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   //
   // C++ Builder workaround: we should be able to define a compile time
   // constant and pass that as a single template parameter to ct_imp<T,bool>,
   // however compiler bugs prevent this - instead pass three bool's to
   // ct_imp<T,bool,bool,bool> and add an extra partial specialisation
   // of ct_imp to handle the logic. (JM)
   typedef typename boost::detail::ct_imp<
      T,
      ::boost::is_pointer<T>::value,
      ::boost::is_arithmetic<T>::value,
      ::boost::is_enum<T>::value
   >::param_type param_type;
};

template <typename T>
struct call_traits<T&>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};

#if BOOST_WORKAROUND( __BORLANDC__,  < 0x5A0 )
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T>
struct call_traits<T&const>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};
template <typename T>
struct call_traits<T&volatile>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};
template <typename T>
struct call_traits<T&const volatile>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};

template <typename T>
struct call_traits< T * >
{
   typedef T * value_type;
   typedef T * & reference;
   typedef T * const & const_reference;
   typedef T * const param_type;  // hh removed const
};
#endif
#if !defined(BOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
template <typename T, std::size_t N>
struct call_traits<T [N]>
{
private:
   typedef T array_type[N];
public:
   // degrades array to pointer:
   typedef const T* value_type;
   typedef array_type& reference;
   typedef const array_type& const_reference;
   typedef const T* const param_type;
};

template <typename T, std::size_t N>
struct call_traits<const T [N]>
{
private:
   typedef const T array_type[N];
public:
   // degrades array to pointer:
   typedef const T* value_type;
   typedef array_type& reference;
   typedef const array_type& const_reference;
   typedef const T* const param_type;
};
#endif

}

#endif // BOOST_DETAIL_CALL_TRAITS_HPP

/* call_traits.hpp
e1ESDqK6kdhZ4jDLxKjGYVwF+057tf9zKzvtVx45zCuiL+RaP+HsPgpIEf0K8CUI5Su49e9R9LGNLCv39vmCfG5a29E7FdVLnlzouFtlWuYCNWs5qsPRr9aFpSVCnKOZrbtpCmk5RjguGgrPn1eotgrMNjSraYATymWUnKDzs4+Jo0Vrt5Lo5qo/y1Fwl+HzsxhRYMpSoIz1cpym8J5ff7TOid8f5xVre8mFJcNkZtrEwX+TCtZp1zz9zKV3TqH3GTqAQeyfooCBwiNxe1W7pIryZnTfthRmb0Y/ImaW63QjxAU9aNROWgIVi4Y5tVZfvpyrJ/ZJw7rubcsrTjSzz8rwhCKa7Mh3E5OqNuQ35wGbZ8RlW3Zhmx1s4bX1ZRsd+l9Md0EzzMmyCfPy1blNmxz+ciH2RrDbhOZdGcdd2RypK46Zvr7so0K9eWCQXE3MVdhJVawTppaAeQjWl0ImHjaGg4ahNhdipIwVchAMZzFKMMAS5BZWk26cAtRjHKUn+G+ZJY82jXHgdmU/XxOer4NFEmh2gkitlr6716cQ+ovCgtlCx+QDxdOc2NYjfFt90KN4cdKZawJl7B4qU/YbZOHX7X18FfqXBFn1dcpTDCVMvHGrItQck7inWldLloU7x3kcSgOO+B05XrG5xT27FQfGwXiG3kt4+Jc81ciVSAxibxfZlBI749ZItsKF/gKuo0202E5orZjhtkKyTj09E3DG2u5wmDXjhg8HzUDbBrzhXfc8FYu2r/fXh5HhMb6VUUL6uFDcJseDRPG2Ag757+C7zPS73Dssj6w/EQRo/TJKEjQwZEqmOttALxNWAPPeMEezWEdXF2QKTmDnjtJ/OYMnNwGcEMz5SsYgNTywEt5FQyVdFEc2DSzboEtuk5Ncvm5DmWMibC+iZzVx8QZwo805zsN57nxRKj7HJKQWzN/Yx0K9hzPxRC9DmetiNpG9vB49ikkctHxD70wGc7i83WKhsWQUFKWwhr4jK1Zy8Gw/+UpfwqgHtpjyq7IRi25XGTnMTQEcG2txhKuf5nSo3N+Kb+eahlOjYR47L9U1uPAEVSn2p3XSQODSoCG0ESpLgr0e70eGj+1rUqTGR+aHOGbzuynikwekLC1ZZ/KT/TU9Zy7f2nQHHt6vhvbiOVNhcag7zvdMaJLhLHI26BMjUQDqYS5fM+Uz7hptGhDO86vi21S65P/20/OAsWxMK+WV6b5wQEzA3uXmw0pay9EPn+1u9Ph4e3i6r3Z2ewqSkTi3bU6Npuia0UcMe+8NEiQ0QBdBbO6gPAXhKzyeT4gg7x8xhlDznzRPbrEdH6KtOJxv3FPOLGk+GF5D9YqtnZ/d9fBVDnylN1/RX8FEwFtpjg1mDHSuKWDkrKmzoAZNFV5lFXb+a2iAuup8FQDTwy5RvB6TJeXTfhXXVRh0EavLYHtdya1Zw5WyUQgJqzTtJ5xygbpVkPjzV2C3rPOB6ERmN+HaGnv/6QRl3Joyccu3Me3jcBAgo24dE1MCu8mXFXxcDuqtH3D3/Az0vH1yCeN4Eoc+YsX47laNVAK1Qlxj06Tn1LGvFM+H8Nv6AbqXdufLSSWGgSuyL+t1UzXjUbDJj7kYOboVeLu0i8ZembnaqxUJZCDXU46NwBiNgLRrIYA+2nIPK5DZi717AZ9w6kg11UmMe/MtxBWSBKa/kwNnycFZEfkdWwM3Lm7WXkh78NxmFCfrdsAzBPKrVHz2uicx3D3xIKhUIvaF3hY9YQO3JwnyjJTf9bE8SrSzPa+gx1pA9U1Jr5eTHInHfOXTnsX4p9IGNygzIoqG/+aiw5h9SYoPuQ2IHD3QP2pJ7UwKcg5hBulOaP9wikkAVESzkuKv+adcbJnO7KVsZQGhz3GGQNkntIui+sL8ZbxfagQijnf6Vya7LCNYbkTxcArX098dh/vglDtO8AB9YavBjODQVLonOkhtM+Oh3anv1wYxkc4ty94iSdu1Q0ITlt10CtsHouRc1hHqcchzu+rajMi21fY+e5vhgPVXXz+HQQtql9RJ6VmaTz1oC/nA0tIaPl84LDLXMYYc4ZORHD9HnEy0p8bDCh88L+mjtJBMPx0K8OTHKTuAk+R5gcvYDQ4oZ8FApG8leeQfvpgfwLREX+csPBKBVBtLzXw9fbBaTC9YFRJ6VjIDRnjmn+3i9o2mMKxyP/CQSs2tW+l1H5LtNykn3jaX1vpr4AQyEXtghaBFvVuYel/2e5KIcYDmosNtJLJT7S9Rw3jpto7vjxLayYoaRs1ZGnFwB7CVKZC9We3nSwmzKPuyOOo8snPxplXhHafmavOiRUOGFoOQJqD78FbjGNwXfCkoM8nXyKP7AURvBk+l9VMdC6BqIjrfOBleRrZ9XI9Pap9TW5oLXiT2ZPliEDhY8QE7bGiEj3+tb9kFoa044NG3Z3cbGxcD0D7/ehoSnxl66YID/6UFOkKBxFCHJrmxGV5j+5C/h8ejIFiLYkGMY4KwZJzrdji2YOwgnQhqT7gRxNq9E8l9/mPVJJPeVLKB4Ph3TkRgo1byKA3rDS7OzEIqyhoHfccWvVTJ8EfsQRDsQTIWq1tFl+LxzVdVA4HWfi+6jG1vzNHEaZ5jnmfhkS8laJCnNSTJlqRIICEGcPMvQfj1McM7VuiSyxC+ps/nEaKHsGwAUhgm59AmVADM5msLh4bJSiPTiei8CGe79N7e9GWJiWbpwLtDsFe8iDPNutrV44zi9fdql1FOx019VPw9KocYUDsVuKIJ84gKx2J9XTYi6eXLC3BrCMD2UvuAf0CHTWW1d07NwlfYQYpTHRzrdzkngkukRMqC/GaRlJ0P3dATh+9dMTEmkp81x/h+UiDJjIRdy7T3eawVQIZL1YyaCTGtyo2hPoJ1dTenSno4QvzL4on6yia8hcs74r8ZL3Aqb3L/nSYV/JXc+MnzQEgh8D2qN+9j6z6ek9sFGXv34drEaAD3h5mREpnW3qTgPG7F63tuHhFkofHDgYlXvI26NXulYayjGE9SVo9bQRH9GEyR0kzrgUZxuYNYpNE04lxJ0qo/WOxO6obhvjSrFHfC/R0V3k+9s4g28vY6zFcaRp7rHV++SwMPgjBwKX1MVyEP9nkM4tEjY8GbFyqj5POJbeUSa1kkgiCjvHUfINEBI73e/BT52qUQ8U2C84dDme26EH6Fo0q7HC7jhjB3IEsykXw2qoidZcAvVAnM7HX205My1fZ14GYf5D4kLPSS0m9wuLIqo1/TuNbtWO2zp28h+zU/AELdwbXo5+/FE/gjQ5QRSkhDVAyuSVGGmM1akhHXeuJo9FskaJfsXXkhnGfGS5NfIkvyQnqsA4RWQwDH0Jlph4kQZrBwWvKhVt8EyjtJ8tiIVtzbJcBg/GOTFTc12/h0VNZOLsiLNbmdb2D7/i/AWP51ORBbz9W98d2N8AtOERx9WpLDsE+70rIxKpgEdPNKJxRhYsOtZu3UQhxTN1nuYq2CiSBJNgTRGdRqyRUrqX9MsrGmNl9NVN5WIdrvjmDv5jNXWFnBVrhmliYGLjaOyatvii3wm0N1X1MyHtaUM7WrbeZgK7+9iUMjWAcNhllXf571+CZs/6X/4HdYgxSm0fz3A8PKa8t+s3n+ykubJOUBpjlJhis61V5trXrVZRGGGTiCrwFQHulpcIfX5QRW2qVmCZbKqdxSjxZh0JcAgtn3GqyFou27f7hWAAjvuMUwJ6yaV/Liiyjo7b5kOfWzvtMqC/nCp6pIRH1T32010bzIqg7oQlrlXdyfjyiLYRvykEQ5hnPEusWtrfAdLszzc+d0Phox0zZWbmZVtVgGBwFu9WKgnK53kuduy/1yjgeils5WZKpazB0AuTfOgCdduTFwLcH9xYCiNxJmna5p3zVF8vJAZ09utp/S9wdNyR8F9hs7QKeAJyQ/VEGmAks0rHM4huP+8Z7eO6i95yIObnuZOCZbNvHKFFFoFkR2sGYN7xASCxaIDPnuxvXvmm5eFSc0zZTx+jYRceUGwj4pQlhfjmReipg2bnPn7XBfWW1HOlt/x5PjfhsgEL0necAkUrQeg2tPRO0/NMxe1cMFcSUUCd93swWfgNotVZmZ2j01GXoQXs0qOuWqmMajLg18JXLMgJXyYbuYGPE8KaQckuiDaXfej+pbqI06luNT6ks1Utro+aTQgGqzqpP1hXQDHouJbehyxACy5BnTIxwxL4yj2FbeJxi5VvImKByNIL+C7tdS3ict8KeJMOTCRN0zL1zlQkFdyCONAxidvDD4irNZFG24I9cBvi3bZQxy615OC40yo4UyDVd5F0LSSPz51B90g6J0XzcTs1TR/HAFnvewhyj6XncYN6k2BRNSkQPckbeksOpv9pXlJGqzAV4Mm8KKdj7Ygb7PWunNsY4CCzFIWa3jCxHgjagOwMHjyXXNp7STOI5AqxPNxmihZZgy1oYujgfJfKGS/NoShf3xQHmsFQu50V5UJRJKKpd8Ho9QRWrpVT25affWrOD7XeP3WmmZbjqnFsE13S75KzGi1zcdwpDtvr7R2mRXiCcfUAAOLPHTJkFTIm9QwRzMBniBmnEmmx1KaMq+DVsTRQu3fLDmzT5kU9i6HxpruKbl7CwgRdmVd+9mceuI+4tp+JHyGx3Y1p95m4bzYDpo44jjFja4rwDZSMwA/pfmOQ6Db1VTzYt6C7emqViVJcx1Fl3ZnhSk83KRvfGf9sHTDpKYLmRNhlrada6YyM7SEdLyLq4h7IesqCSNXaQHMh/thVeGC7J8TmPI4CCagn7FTrTI+c50h+QDLmP3md6OOsDNHjCjm3Yf0d0xHZXpKOWMgWobDDlvr+wcnzbkOdNexLMB57+Pqo1t9s/OmTUPYZJHG3IsiyyJ9kI/ugOtHQIh64LI1GzjythbVNZnt2oVb9YFqp0CaWdweOWktXNR0VwkjWhdUSsRPp/hPHDB3C/T92G+YFnhRqXbf3HtE2Y0Ltauo7z1MjbzUkhvKXCGX9WI33S9qahjgYNLR2gXV5pldRQSeTANkBwcgftoPRmtuc2frA2CkROGeToyiilmUf5I+RYNuZEAoVgyxNi8+5s61Oc1rEEVyyl7LdqujnvL4UxyIgbRGQPT+10drTCv2YEPKK9FQMhWGI3qawzxMmdNb1mdN1V+3EqtvJAd/TA+9zwXzILzNhEGTtMu1fnE1nuzOZ6LsY2QLTE6AZkUKzWUe/TmUyf41W3nSkzY18kI3IbgXq/0adeS+eg1bxKikRSJswaRaYfJtHc4A3WvHejj+XI63U5dnfe+38XuviBFGO+ddvfYXP98PyybRTfSXLcVPvz1vHBdtJL3ZEGijT9w8Ee7/8pmIvQ8lJQJ0GljJm/TLT6/WU0W4+McoEKE+FAgdsr8akmbmsypfmd7qWRZaqioXNvBjcH7qSD1lkRu3gP92XNlHvpXemWGRflwh3A7VE2te5f9KmT4N6zXcgXwn262bwfu8AnxrlSOlZkCI+XX604Aj3Ua/n1ktMUIVcLUCGZAaNwC61P7kxGJxPDDqrUjXkv0Q6zuaWfJdq3bZCLhGecMbbek2DUfkOWHxa6b5h4rYOcW88TqtchsyFD5FIb3Cter+M2hA1dFhrgylNpeESB0DVhL2Cje6WJMmKch9MlvNoGvmEezD8cZ3v7rQuMryUIwHA8391c5Ncs6e52UNXWBkilMmj1RI6UAIKf18Rr/u4rbCMOQEqc12pz9qo5PPf/0d9pb7YxxYh48Iqx2Zxcrj4JPEN0axAZ7Bl09T3Jddc4NTIlSOz7H3J0FB03D1HNUin1UCvFcbQN2r/izAZtQOq9SVPTCPDS5wCI548BTml08qPyD+ZQTcnENBy3rXcEEPo1UyMSXy9zq/oKx6g06U1yhyYSnMiOgBOvkmRGTNqToK7tOP5AmgTJWhd/4wJmhQgvhpuXD+3RpO9PhDJnpvEoo6KWX4AXoqzzYwEkmpmbJumHWyz3NATC/fqk84HancTyknMSCiLXNsYF/SYSd75+8R27xaqLaDJjXP82OrwkIzHU7EZ/qift2BhGpltIQ9O888nFWDWsJ9LJwGHoje5257g9EimjK4Zn804qBa98Ec2d0nGnY9MnlSBpnZYi4wgvbpbe+3FQVIQsQPJv56Znc2a1EkpP/uT996Evz0psRlwj6JvxPz6oySfbYxUyIF4jgSiMJPQ7NzKKESiL+BlC2Q04iW/euEWWEvQmVxM/bC7ztVpJUAjQoYh5u1rrOFOPhxhqj81RWFVVayCTvVGSDKDRRf0f0g6cxxNqZ59SlyXRQiQBF4cb8nDRdLEScPyEEtPZZtRih6PMDmFdydc8jfIp2kMDAJfTSEeC7a9dzQ8+lHWmmpbJgJg/bWR6dVFjGkgN7tgoZPDH+yzyfkIPG3rIMV6qVb2vm7ZsmnkkGGeQ4zixJQU4DbhttHHBR5QR7DXk+6te+CKo6a7IkNvS4JHxA1gs3puDlakUH7gJSbYtpZAWIoSI8KJMPh+95m7Lcv6O09XbJPARiCtQvTDTmnLcGE7dBPSI6SC9hPLx3JiYMvNrBgtvbu++GNWmsh0osjL+B+LB1QSd9Hl4Cy2cnoRgDpb9pgNHduaCdNw8ma8lXmV6wRXbvkX/hAW7gNqaG39TLzZ2GkPfQzFbGS3q3e3L1Gg87dYl2nfbUuG9VxQfL7Qmf5hFVfKCzQxvaxSyS9uuYr8Ychaj/VI9l1G1uQdw0brn1Sp8jqGb7Y/fzVqJzsPbp33eBYyudLO+5gU0V8kdZVhMlLMOZAj+iWhGwS/vGEyH1ISk8ebHrwVDOO74dX8LZMpfuSVVgFU/uoLrZ7K7P9FHojDwCzQtMtjGTD9OllKso++FqlnJtjoUAOshVv3R/vElnUMlj6IM5Sr9bCZmulx24st8j+PHAv7ryVy8GENSe5q1lCZlH/jQleFcidjwPMXSY4+DO2QCIypUj2wfY15Jq0a3Nq9QNCbVBU4f8/frmwUSOEFBr4VOaDYgKF1k394MYk5Q3MPrUF77w5Fb2uyT4LyUyYED2aufCv/ny/sD04VUEgHN7bftHQFJEU7tDJzFQaqlVLQ6KocB/v0k0phA1Nr48bwbu/NG4cPQk2Knmi3su3WPRQDEH29ToJrpKPi+XbMdn7og5CfnyOGDPEmOkfC8figktk5wd6fouqWtrYXsKOUNl02POJDfalWn8WYhyjJbBRjSizoLtGSAABwzOLT4OJaoWzat3bsbLNkEG9+yyTC2dCoBudptwm2LxlROnNAV1kVgOXSLaEe1ev22ITVwx+f9EphW4IzgUvH+Bqz3z6ulG3LbN9v7jJGieMr4+DQzXTDY/hkyVrFUGERbQq3UguM0GHT/ErqPsrAaBn4jcZQWCBY4enIVZp4dRnAY8dGHTvfBsbLCynpu2NUpXSeKQ/VpoF6cXZdHbe7hjr2zqonjiL85J2uRxGK77aHttqjhPwqRwlk9jO/FPwAChrQT+grgERHviLt8zstpJQioesC/Jb3OPmK8zlxt67tBd1lGTQ8+5gudVwMxWE5q5k8/hKMNt1ed85g3DwAeaXKW89Gzmk3+dFQLnwoMkOhNtlif3Gw+ePSyzU4womRuHsJT2ZiZGJOaWMASGVSPSNNQRWsCIk3s/4J/5kZyu+gIR+1iTw85NygTKO+as37+aCpXpj2w0xaMBcX61K6mYkWfUoz53ORdbPP+5WisabVlR6ZC3aGcwl7AkUOhRTgBxLMpIdhNVZnYQCdIC+qMe7siPHMwmoPJssGCXpQ9HdeOy22qN8NXY4wS5NDnxLE6rfEgsnLLJqKrOciAO8tlcXcPgScHqBqo3jZB6E2Z1J1XzUJBG0ZpBdjGp8ZmYPZfJwjd0pYnPnBrShw+us/XYczKoRPrFXIWevqpYUrguwRVAH3O/YgYSMu+5+IEn1V/KfXad1PXR4AZ+PFXcVSOpSjB5dAlOEuM8Gz8C50hc7trsR4T3pOl6nKN/aQvZviqh9syQVW90B2/hL3rBQwAnq9IqejDVRS9AESkOjvDDKZIi/Oa9T6It+FA6LqmYbHFY0a35vsxG5O8VsDDwkkHfMno+xyPBxbFZzhZQrRXF6zXOHS0dwSLr/0eYgZ/3mSz7xLX6gpP5LHNRGd23Dub7buMqh3Z8c7elQ4gXIvxc7Rjc2xRIRedL4V5f7DHamRn1OHZBAfuCrBUtYULTKCc93xKBa0kRk2V0mBftliyHD+J1BmunT1gFz7euE6hflHdNPmOpnJzZh3rQdmG9TH2Btl9qHOGZDJ2N3AO99GpsBIfA8Mwc6NPpHNKRW69iAbnZGGhzwgjds1yTJ81YslJB8Rs1hGR16acyFpQBZxSm2paIZygR8/D2JSfZymvSbPdF3SvMuNwOB8o7UyDqwlRbFezyEaO24WVeCquaoy309BoERi0OjWJ/Nz8MrzOzy3gx9YkNwm6hHxUY1LXQKLS9qSjGg2gaktwBaO6M87qRbBqleKljUWlI/Uue7ye27+eCNxx/k7M880g/Ql4cNBgt4R9AHRbH3JirycKZWdVIfE3my98Qnw3/+0OsMiAdlm1e5GlE4+sKbHVLVX5qWSPTCmfMxGjSuiLtLvgO++KS23F6lae9JY8uwh7RAfyxk/JqxhN7kSTtCrqXmFL2tna6161+nhG5uc79FRi65VYRuouHgUkUMVbAasEk7S2Sv5t3VJxm9apvW2EGjBAKwN5dP37QkVFPLEHGATZGsSHMDsIXBkm4vD5HpeWRLdy1fo7uselUBEB1lBTjXOxTfi6Ur80w7YNi9R31HUlSXuHAr0dSfK6HQWoxXRetGOZwfzj57qf22/4WxMkZl+NhPdYf5uWBYTL6SoQT/uStqTBP/BmPqRa/Sok9bdT/yCOh+4tWHY+yI0SxySzbFvPneIdn93J0AAiZesQshP4DOuUrCdfThS1lPWnWhLDacBoZZ8fFjhBqkFIEcaxZAH7i2BQSwWgK8JXYvDLxA8xKkdT7wQj+pFsDPhqySD+HNtFBMSfF6TnUq6vRXM2IJqJfDyHJbv/0oo/u7bp/ru/QKcGriuiSFUIhwE+1epMZFQY8P9q3He3uhgqfZ48SqTjZ5D3NuScpOHi7TxxPzRXjiqgFPWmGSYwtxLU3J3tKxtnw7aS9Iox8xkw8Oy7iDxUP22jWeDzH2cWlr7BHztpncUbOxvQ=
*/