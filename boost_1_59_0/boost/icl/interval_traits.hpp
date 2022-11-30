/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926
#define BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926

#include <boost/icl/type_traits/domain_type_of.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>

namespace boost{ namespace icl
{

template<class Type> struct interval_traits;

template<class Type>
struct domain_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type type;
};

//------------------------------------------------------------------------------
//- Adapter class
//------------------------------------------------------------------------------
template<class Type> struct interval_traits
{
    typedef interval_traits                     type;
    typedef typename domain_type_of<Type>::type domain_type;

    static Type construct(const domain_type& lo, const domain_type& up);

    static domain_type upper(const Type& inter_val);
    static domain_type lower(const Type& inter_val);
};

template<class Type>
struct difference_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename difference_type_of<domain_type>::type type;
};

template<class Type>
struct size_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename size_type_of<domain_type>::type type;
};

}} // namespace boost icl

#endif



/* interval_traits.hpp
sf2lBbYde6HAFxjQmy9VO5tbnWnn7qDSCaKTLikHZuaflIds1rzmxVD5QONuRWEvUhDBEE2cwVfD07XwFijQ/TkQ+65JYaXvhyEt6p+7luhD3ptpbsyfNY4XrM+TVMfgvRlgqrKGbeF8sd/e9yuATM6EH3J8mJjVThhpqGauUmtUpyN0U4KefSQnGRZRIAt8ax6Rqjp136CsQE4xffBpLL84KaUgVDn0qR3y+RDorjfR5+HPWG6MD0fxrpQ6TmeOY34/mlozFAckHOr5eBF/cZDGVaa/SqRkmmNuyt8r0p8CZAVFapPaOI5ZKP+sMloGPbNXNdonpkJDHdxb1EN+l0NeRroeoFeYukwTp5mrPzRMelFYxDROg+BLeKLHAsbPTmb7BGRs0O6q3sjwbbVZq+zjrMRDQUsfE6pm7h23m1KmG5CsxTsvkNR2qYPYfn9hoPLNdFL5/umQswpEU4eJ2A4SA04aN3Plgqcqifj7zev3R5VGffBjoV6vmTN5Vl8NeK30otPmb5NYiOAzplO43BvTg57ievDSEb3Eqpra/YE9RBzoJSNwSdef9I1BA4UEoRgQoxt32d/QHJPZZGHAocThKX6nGkmdtnWNGesc0H+aTrpPDHBXnzfQpPdsJNdRHfMByJUD3c5/0NzRN5cPaZiYb/wj1veW/GJgrlPy0LpCsfGX87Tlpkgpvq2KRC1LfYuEetzJxZ0W4VvzgSHQPb0P10TspHqxsBLU5D1Gwp3FPF68gq7jWF0nQixyPku7OJ+icpuTFknUkjXNJOPD0HFLWcE7wx5OgtN1URdSU0VJAys0aOeK8UooC36rN4iv1LUKOAjdeQT5DYa9O+vDUHGLi5y2rw0oA9r4q+JbYvcPMgv5yRybqWfZ8xybrpbddC/TCcwN0mUf2mOROApa3eZodLeOmYG5NvKxioS7eb7w2XSYa1Zm9R0ibQLKWv6rMx3qQrE7OR3qgR2CwitR0e7/Lj78DY9R8ONiYF8z1RxekFxf9Wg3xrAqFyciUloa58cPzt2yF2W6GaRJxtD7+UCdDnNTHSzsPItdX806kvw2ExHHqcnjjKLjjMhMSxqIbWvYZT5b877H3S30voxJPWkVT52C7rbhJS1H+TqS0sUGr9SBc/NVAFxlrKjZbkcp5E8jHraZFI/3mlzDpypfsAb30xsMCZm+pBw6r7DR7bekTX/yKduB0NnS4soxFikUjn/mFg4zmrf4AXmYi4egUij522AS9G9TlvpENaz46n5h3WBjlNFeQWe+IY+CXF/SOTJHN17Q8zsHZ7IPThbfr5W39caQzDsV4rY+IB1Hd8pdFi1nvn5G8E0dGgtXzdRqoWAaU0tOHVguHjMeOT7C5Gf5k27YsvSDZsgFpt47rTTwTZE6Teg6zvvyboJPJXpd6u57V+6Mu9bTVjOSAb40NjMdQj/Y2+zR9W2ww2FzMHdO9Y6T1reJzCm74dMP58xxvK2498J867gpZIrxjbAJwnSDCQgeRhTbC5G1qTObTRZ31dpxVPu3PrIL7yZEnPAFLgIQU3BcGsp13816XxV6Uwl6U/d60aZrZokuKW/7lYGcxQsI9kH66RHC+wLr04E/1n1cGkTujWL3h8KAF/byGrcSWXR60u7qU8zhU+41x52RAe7sAQTconuBA60FT2YnaKhEdUNDFFu+EbheJgxLhzGEt/i3SrQlh9Vp83ZwPMBo56/7jvGjpzOVxqD3icN9icdmuUllQDjMsTjMtouixOtxuUtTOxrHvHp2gMJMIzmNjlKARHWaW4/fr/0cITO9uecirNA7wAO40b0zAaxZg9lYlFikWVcpvZRlWPfp1PknwbIaIG+iSkp2fjK13MHuC23LDegSTMvr0kHnF3JAdCPeusB6z17UBtKeV+gWt0dO6wQrxlDCkvI78QdYzUwgQ8G6bbhw+r6fsjXdrh5Xy+0KSbKiwKi2uy+SvJmCmT4BKF8y01sDHMdylCltys9YO2zsw8+5dfI7IBMpy3Y74UTG7fNytCPCDKk91Dx2gNg0baxxJzjXC3ZPkYJzcs90FHi0J/7p1acVty/UWJPJcEi281GpQJgq4wdf31mMdSuI06Aq0FNTM2Dh8T5L3cBADdSJ6ynLUQwmbGB7A4NEOeWwb7LPDTwlazPfopfRag3SqfrEUhTdxdixgAA/NWJr8047BLr7Bo1CYyOyByTMwLgM2xrw8R3IiVqkcer3jxUEydHWHxisoDk5ikzvFDykOhWhs9pFXpTueoWmoeBmE/AptxQeeik6EK/0gr4lBwA8RB0hKKEvHtFL4pG9xgdrjE2tFxh0Neaqs+QXGu701Ka1usJGykfmDEZykKPp0A7AYg5hI6MoTY0lWaoCaxaOeTvzTPJBONQq+H0u9cUjr/3cNaRkP07Q+5s0Ll2jmyNbmQ1Mca4dq3sAOeUcFRwycFD2wVHakEKJIL7mVQTROPoZhFBfnjOz7qqZhlI2kI9nk0zbAwJXgybtzLflOyX3COQe0XN0pWpAueu0ElF7sX6vIsj5kF18c/0H4A3hYG9pHYhGSJZ1CrK+fQ8u92km5sQYk4uCBDcg02UMWxiXi65C2xx7fXDgE99QT3/jUqPCtOOmwT5inTj8VosIBg0R8ypKu+Hw5k1uiBrTpyZcXHady9Z7JoNJvM+cEJ4cqNPqBem/8YwsIrj++nZkaS76AJBi7TqKp5Tkwlhu6lgNnYrsn6buaCJ3saJ6RqlaQp4x3R01NsvPfW4pTXs6TkoqOKTebl6moRYd6kw4Jto7U1RvkP2LvKNsm0WiOLQcXKUpgzD3f1luXLE8xRahvS+Ztgb3OorcCZHP1pa26wcfsmZqhkYTRHdlvoIe2gp/2e40VNg4/c6cCQKHMDxwai/pqmvturtD00O16EOtlAlNS7ilhmDjq+aWvAm8oRnHkQQwAttlzXi+Jp6OHVZ0mWoYvEf8gr+3kHRPuXFGq2SB72457IXTv5+rJACdbeL7PuI7nKXwgLdp+USYhYTiJMxkiewB7syvxxnj241+NvxbV+uVS5nIDA6D31CvRlK+M0nyUHalF9P1h3IgH/ViqWBu7V0/ZgsEbA1QSUTPG/iJ6Rkv51giwlaisL8FQHfzQeU84o6g+lMGQ5FN+isuty5Rxk+qd45tK2j4jEMuGHwoiGeyc6Y3K+uLxg9LEO3sQwQqJ5oCR/KhmqvOQQBKmyypUHKuV6RjE8Pj85IB2t4UxdLM/sUYg2o+CwEau9sLHV+8CChdm8WAdpptwmwo0rpdFhUTDLyiKJtxGZii/pu1f4lswE/e88DDcgwyNsKKMXY8vj0SMD6XmCGUQj7tpFAn29XA/dZ7+sLAXYnM5p9mSflnY5nUojSCaYZ5RSHdueK7v9sHH458dXFxZmsTEjPKZ5+cHCoiNvuDhdi9KzQqsPHVPXOC/0O4pw0YO5RIfH+Ie5g+I7qOKb6SGL6UcimrDQpVOtn5RkDPVwowEC0+zmKWvssX6/0c7hMhMVHnUX7OK+qUmY7TNaLvQ4GQMMd9Wsx4PYBLjHgPwcA4yfQfh+gDBXlBDHBpcIPh67F8JR+MXqUAgQuTCYfFeSrkeYg96OmfjMentO700pm9sxb9hDOHV7X+GS/UWydsEuweKB7w1epM4YbkwgMRqZK/5FtR5WOu6/htEanXyonqCESpd4es/8602u0ZcPgQ8brUBzWnVQ55MUkWglHifsjeHo3EzthweTzc/qlae80CjgV33lk0xYNKkdjV26SkVlvAz5Pyc/QL8L9fWh0RnWaEwU5g9vglOKf9m4PCjSK9IEsXktwAFmMZACPCza7FaeSUiuueEjrrynjEgVvk0gcq/nH/ZodJoizMWhTJGkkpVJ63rB1STE+3ek2JC1uuqiUyb/iXALTp3DBttC5Hm/NBAmCMuGoHifp5KKBNRZr90CdxTxrqxC+gSTOnpZeQ2LG6VO5gj6SDry2n4vyPLCahMGtyRvd+Vms1Cq91bWzcuiLKgL0tsotHFFsKhoXw1K6EI02qJWtziCWQbvbf2LbEfpjhjQR3fpQyQmFCuyRFuNaaC6ertsMsMz7ZP3wF8e/SoWQGbt7pSKVmOzHgVw74VQ2CuibojUz9D8u9/HbhdugF+tew6E8RSmFGbSu75jAzPxXQ+OcxK2dQM4IhDfLOtPbO8IJwRzdHBzfp9pX88ZcbXQlAoWTTMWStbtjlACZdgr/PSGoBWwmT2MZJwx2r7ernmhRycX3tax/i45rjFPG/v+hAUTNchfr3ro0IeneZBGN/zOeNB0VKnDI34eE0bkJhJ09T1w1g9o0EuUYa7s5Swri1NJE8488EwSnXDVUmeznrToO/2RfUXK9GNGug2Z4sOYZtSD8CsllNprdd+P7UrkMluvblMWUSxycHnRHE9RyP4iI+Ot/YqYGwBW/YWp7eFn92qAlFDgrIkIUIamYJ9kYCAvJiXaZ2bUz1bLWJUz12a6BNnHhrD0TY6r0dZnQjpFmr0vBTR5irRn5jTydwhTUBpfSCDp4oIPqJcU8GvzFtalIp9zSuxZOxUK4xMeQsHtG2R/qxuO1CL5BLwxRjEqm2QtXvtOyrcL6i434JEhKUxi7viegWbBZ3TjF0Vdxe7dD6Hu1ObhystXCH4ERWNWVP8RgsGO1FJB2rman3chpYRPJEPJHhmGZYTpn1CuFA2hw9QjiT8ZFBIhF2AkFvhtxV7AUX0PeKo/E1kYL2qK1H7TNy2rWa+y92lEcxproVbKmU5gu0xZi+U/X6tA+SELe6jar8V2/XqA3DK3C5jvXhn5GK48Jgr+I63aFkqKcGMAUm7TyTuAArLavmOifJJ8EopyKLqMLtqz3zScSjulCshxGg1yWgXhvCYAZebsLpturInUCpSNyF3hRzQyxlV5F7dxcTnd9KczyTJ9ng+yVWnpUGXQfi2/f1jNRHsqejKT3QtOUH1BRO4LcyosLalV8QyGuFd9hBdWBj0tBn9vi5JvVXXWyCMRKzSRXQdoQoUatXOV1xiTHi1P1nwoGZfz+FZ6/glV96SUWB8jeGsgoWMy3IjQPk5vpbGiuFY2NPmblrVD2QMsd5QcR3ypdCF9uVlbZpmjWRyOdzIcrIXMKnzzpHjzym7HXKsganb6PIGFQ24nf1lDvDdJHehC5qvE3rUwA6BtUINLr41aF6umQa79OWDT2TNSd0ShXhbzSKE5foJ68yzZO6tNKbSDKYoUs56ahFPlIMX9qbpK6izenXWYV5SdievMPr92QUVjfTCeKWh6OgcMQiA4HKv+ufdzO5bvs1UaGFJeeyL7ED5v8xYR+VDvxlgjdVur80SUR4c7ISVf2g+FCS1MPkRUK1OG3I3JobifwSgc4py5+0eXaM98Xl3VqyAP+XWX25EGSy7yUpGLFl1Tnak8O6jSEZtHXpEM8byNqtIeizZVUwuhhJlobRf2GiuYNKNKAcHXA4aL6XSuBIurJw1KrsAfxNxJB7kg7iX+cakBTaClkdG3GfJCT3t1oai8ZauV5FqlWSyR7sZlO7IBmspLuWAiOfXnZy2NeCd6YzgPViKU6XlZOModojozpEbf/CxDbi80AL1s10UuTj1edpPLBo1xFyTb9j1EtalNSL08dXQEhPwDOg+Ak/O0Tdav9GfC2FJ2f8QIIy68x8X+q8uykbVQ2cqS5nwe9fbGxxTZejUCuWc8uFyci3iPppu8GEK4wGTmesVnwsS0ygoVf1lgovio/bHpid+l1JxVnTogqwjFupeERtZ164tG+kts7ZZeBfkOfl/EoGo8tqVsMCiOK++/5sP+pMGqBhN9tCmfOKt6P1uQ8J3sJa3Anv6h6GEtqBdG9vbuuwzWbjwRtNarRdBBDOU9tL58NP7fLmLDt8aOqpg3DrtTK3f6goin3FsNGtDdP5vc1jcnov0oUhVlhIpOU6CyPLZwWxAas8+0k8Vp2xiT15PPN5q2XeWn7ehxtY2fs5FkY5SPjAnp0cBhDSRxwlfzPkQrMF7A6kz8Rukgku0QMqfbjC//6ZtyfHTdjS+phxEfzXmJbKiJSosjCkk1sk3/+7Fcf4G1NSqGaPHuafyAmZfKiZaXDRCnzyb1wEyN0ZKKeH4/J6VYrJJohLJmsXWYuMfsUa3g1ziGLqyLK3X+0C13oTRhQcMDAzbkSPFPQZKXXuC2Fq41yYC+btqWFnMaphxVKc5Ru0aBHHb6HRKcvE8nt3seAItfhl6uncICwgwPVOv9kfWCbIAeouyGaZCVUw4gQR03LxOtwAA5wo/6+OIEo+EVTuTGEHSH835JuLBQfjGrAyYl2nBKoh0+m92vVsu2NijjPFXCqYBm3IS09EFJzNjVLQe7oDkiu2b1qIN9IgZ+fOvjIpZZ+I8wQXtKMBiSQwJkbrOq+Zn7GgicEUlq+bf5qhthXzwqmjViDh4TCrUWLKSuthRGInRxLdzD2GlQ9+w8Y9xg6RoP1f82/B8Acu4k07zY4YDqk7W1wR5y/fvZkGUQocePo03JgZdKbXejZ3oBnQ8xLdSeDsRqR+j/Mgxh2+mKMmCjgSiTe3GG40xhzYvdKe5ev5D6oYO8ludBhZKnBzoMRZebd69Clo32EK09Bx85wSIXWbPM3sx4k5cZ37i+yNi8kH4DIPvM7n1tfzy7th9t1Z3NMkmEWDVx5aSvpdThFl4ezj4GJpZFqrl99um8XmEfXZAJBrhjVEQ4hFigCBrvkNbEoD4VUvIi+LuJ46RjUqk56aRhoNYfWTph45inhZ2TXQRYaOStURv+qbUS+oiiFqtjfYq+c+us+ZA44X3vTviafGaVZJZAiAIJV6lAgsddl1Pss81NQ7vH7pzScMEvAEHaZJ7s9qsF6pTuCiK4pmhBsbHMYxc7B7kYWkYo+flotX+GSx5MxdH3I5KvHkIvY+cGcoN7e4FpfcATegcgBRHvkCHTlL1BYCCyG/nKDEZUcmHQczlw+PaCnqoNhdpEipqGhPAxjKRPQOJ148dC0LEHaicNeNyogyq+wWh3ciSCRWJ4HJBVMlZo9LHuk0YcZg3Ul4SlMdrOZ55CG4ZWtg3eEYkj60K/6MjVVCaaQKKQX8stAgf/HeTkSIPw/iQOg+FPzd+fS7ibFFnXGh5afhpp7jFF2oeYKbFiv0v04HPJW7iXl4XZyty7lip2IdDrkYVUfVc29mtNXMJNSjI6xby9gD4I/o9Mj8LdD2XD6MeAeAnJ5IbSaQlnOHvTmFHFV8in8bZRm1Jz+AtPOR1m48/52zr9L29FJays4dk8Lj0xMRI5Y09HOYKyuXkq4KRxynDCKTJ40VBwSNYm5SzIg1cB0+Wggx4x1T0kNQ0Xa+ouloX9K4G1PZKI6w5IOeQ5MrQ4viAq4khQKHBA2gc/WNddRNRw+2+fYjesn64OzZcd9y9Im9icXf4NactwAALP/TeoQHGgc2jkBXjjRC80UHGGGlADEQaReBttUH6voWx/5WAwPKsdFVrpqEM1yAeGx0k77h2ynqXr3Yrg1QbHqOpGDqbgnvie475oxMvmuGO+8ZMbSQijKYbHyAXx/Qa0hj3s0tKZd4LU+K3MoI5uHA8V24M54LTJ2FkNCu/AZIlX7nvkJ/ySNWChQZKtv04onthUo3cG1yyY9phOUvENhJlRwtocbP
*/