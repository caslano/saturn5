/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_NUMERIC_HPP_JOFA_100322
#define BOOST_ICL_TYPE_TRAITS_IS_NUMERIC_HPP_JOFA_100322

#include <limits>
#include <complex>
#include <functional>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_fixed_numeric
{
    typedef is_fixed_numeric type;
    BOOST_STATIC_CONSTANT(bool, value = (0 < std::numeric_limits<Type>::digits));
};

template <class Type> struct is_std_numeric
{
    typedef is_std_numeric type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (std::numeric_limits<Type>::is_specialized));
};

template <class Type> struct is_std_integral
{
    typedef is_std_integral type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (std::numeric_limits<Type>::is_integer));
};

template <class Type> struct is_numeric
{
    typedef is_numeric type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_< is_std_numeric<Type>
                 , boost::is_integral<Type> 
                 , is_std_integral<Type> >::value) );
};

template <class Type> 
struct is_numeric<std::complex<Type> >
{
    typedef is_numeric type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

//--------------------------------------------------------------------------
template<class Type, class Compare, bool Enable = false>
struct numeric_minimum
{
    static bool is_less_than(Type){ return true; }
    static bool is_less_than_or(Type, bool){ return true; }
};

template<class Type> 
struct numeric_minimum<Type, std::less<Type>, true>
{
    static bool is_less_than(Type value)
    { return std::less<Type>()((std::numeric_limits<Type>::min)(), value); }

    static bool is_less_than_or(Type value, bool cond)
    { return cond || is_less_than(value); }
};

template<class Type> 
struct numeric_minimum<Type, std::greater<Type>, true>
{
    static bool is_less_than(Type value)
    { return std::greater<Type>()((std::numeric_limits<Type>::max)(), value); }

    static bool is_less_than_or(Type value, bool cond)
    { return cond || is_less_than(value); }
};

//--------------------------------------------------------------------------
template<class Type> 
struct is_non_floating_point
{
    typedef is_non_floating_point type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::not_< is_floating_point<Type> >::value));
};

}} // namespace boost icl

#endif



/* is_numeric.hpp
7ILdZm2sJe2u6L1YSPA97XDjaiRo+bpa194nLePiyXpryEUWnmiQ+WH6TL/C09Ydd53X2CHsyzZ8rOy1u0Lpi1Ywlv5ZilkvBQNuJexQ/JOFSb1N4eKIt4emtqZBkwzXzms/gBEWHEEZAoiYV3dImGUA1D1QSw040CP1yNlZuqAx4zvur9yiekaSHL90if4TVDSxVBsVRPIxw4vN/XVn3WyDxf0yQzTMKzLAubtb45+hjHKfDRo4aKrEj7wFLpR2TYg8QvY/LHd4Pjq3o45SOMkVA/vsgqPQ/76cbJPZVVXUBoIAU7CnUyDsVzZICMTFDVa62Ty0oi57/GKwz9klJ1RJPfzMgTgrkPvfq9vxg4tetDOBP9EOxqQSKprS/+4dzhmcn7eeie2j6I1ULzIeRxDnV46oJcD1FEthKmhVqvSU4uHPOSG46ZKOw04rLOAE22TbODh6QgHTABx2vnpaZ5E0f2IkvLOYltZd5TlOD2kA6hkQEyoslIZaTgFjesAvN+lnSETQThYwr2lRo/+GZmnEsea8rB23j9nJfYxf2iQ7c84x9PNOFlmwd4Mf+TL5GGqT0vjZFaSLL75ipgrg0xKJjAfElZure/tdhx9WSrnH2KGFvUGIe4Mdm4fS4/aKkeLdfSDv2l1o8CSGSrhaivco9TpztzJuSs1VLXYMxpBRb+Ye63NulgWXbCj63/z8lxbbpqWoRAfrr3TqEj6WcU/c6id2IhYXq00Rwg8UJc0DWlU719MTK3pPan0BUWgbkXljYo9vc5zue1nPUoywlzYpzN3UonCL0JCcUwLXkBUXcHJfP2KfK52+RzlCo7YaVPiDmUC8YhE7Er3ekQqREGlfGVfNiMx9SUutaU2kWumc0pVMPTR+/Gd2zZKHOtjfwN+uijetop+LEMovQDHUzqB8fhWitvU10KFYnNekOWeA8V/csrMCOLWxo0xXDbc7oykb+Cm+wIVsYgyduT6P9vbTi3i8bEiFE9xbC8AiOsKWSACjcRAqA4XVN1X+Akv45Yt1ipq3XMDGe4p/xy4pGUK9SdEq10adOGTziMROdYODnWu/fTrw6wCThS0Dtz0wNLLXf7jlszeCtCmJ58hUU2+5xZB+c9sNPU72RJwIwq+8SEKpYbyoU3QIONiQVuKoaOqbnEKqOfz8Ing5us+WWRJ0jk4Y5FRIL3KFs1X4z02wdxCR6iC/cK+knogLoCQh2DKTEeYsVRsm9NzDcoDhufKWu+LqFSH+bgcgBolWb3TFA0ehIq207IHQLNqdXRfziCdVjuJUzbzwceP54aZtoZJZRtJDtTlwUR5pchhjR0UiU2pCrPgiGHcBez1ackUSRzAE3WC2eHKPIzzMTJnltK7XDFgG8DOxBcIZ69VlvIZ+3+wISUsQ6hwzHO8f6XWY918dWjxdvEZ2SXsp9GQLndftkUO3JCLiu+wCAn1OesHobbBHKIzYq3jeDukm45KK2zCu8m2FGo5b5ra0XMVt8BwTp37h58XYAZ2KCrL83MVwl4rx35sWz5uuKnj5n7qpLwMH/3Ouc/LNJgC0fl/fEbPBBl80oTTZ0J6jgEnMA1KN/ikumNxLY6pr1oRfsJCO/khyOYLTfC/iPBtxMBhsi/n+PaKcyqejbi/onJbDKKXudqPL/ZMnW15RM6q0eNT/uHwDOryf9nE8MTcGmaZd3WZmBPL+ULXsz9DV5cYdF3CKArcpVc81LgwjVK9SpN/XlLpwP4fI9mWUhu5g81KqRaecrKYxO1kjxjHafH+GwTVOV7RRw7guaiXpHuv1TNcDbyhckAbg2rZtu7e2bdu2bd3atm3btm3c2u7222STTeb5A5Nz5p3ZBOZbJLDjCnAsOhT0prmEfxB6cALnFUMVcexqf8D5dEvokke/XoNwdldcbSYAyMVTKj4NpwF99uKymWT7MNi4EWKR74La1gQ37IZvQ4fxJo7ZVjDp8ZkHejRsYv8w2lm/3fjAY6/GSYFBb3oZoH8pvrdituiCWxkOFUNHr0gTsD5l38rIcoWr6tM0AVKZ1EWbx8Z/HsOgOsY+dtROXT/xEjEtghU6jjF+glnKsDrjsIs136V49iotEcIlLDEimJs6o8c5Tgwx0OQp87qgGggA8u6QoJErojWZ+Kuzgb9NKbGVzs+CAlHo83MowjH6nnPj8LIpK8ByYk6HzCJD6525O5Wz/BiaU0velw/qw5imtEUPlFSZM/y7ohRxGBQzgYkERBlCnfgyrRJVPg8tY7TVtEce2EKwxk8EcBoXIr62haIAU2UECknugmgMv+RJaiqA1fp/PduQ5xwDfwUnO8S8Cqjs2Bmy9Zf/G4UvzMBmsc+DnQOz0QKQk0xw8LROoQn0+4NwaRuQ/Rmd+7kTofLBh2VGE/udEFg3gYHbprW9S19MMPvmzN01hMFnCF+8sjS22UZDBAjF051TOFzaCK3plBj6lMNxzmMiUnwnHJNqbGbJvC0Lo7Tp/meelN2bMllugXliL8pM2nK0BDALvo0ZLI8kdnsw7ZizBXv++NR1C0ZcJJlMy3nk8KuYMg4phI2ossYCy/o5RxOtpNw5ztWiu2D6Iw2RGyGUFTgCObFCxISOBi5+wXM+6r0Z7zYqXh2Fe9dEvX6qQfbE6HOktvogdzPSsGpXRjb1VAUmJl07fdyj0UzlDXDJzLm0MnChZHkzAxWYRPO8vO099pVmpg/8n/MuoDtpKagu3pMrmxxn1mK1XTybHKUFEh49MkwsKMNmO28/RZjTRmUstzDn8LW/rcx1ghdt3QXZmkIFDx0Hya058qUr72xfXlpiHVfZwAH4FsGeKYppayO66iYXmSh8QhcSjOo3gaMbQlmDt+psG8pC0UF2RGP8D+xLLGCep5CtoEgCg9Z9WBTELYQKv/iUbaa3ebHrRM+NFr/oW70ThxCaudK5JTscOTtIIY1hDtKaFpnLUZau0r+0TsjuvkFnoL1y4akaEhyv5HlZPNERa7X7yl1jIWWni4sgousILCVNiBi0gPc4WY9u2XPdHIwsYV3WaDJZheh3i3SXGaJ8F462PLC0Z+IdKkziDmuGVKiJxUHu70ViLksEEU9ncCNPMEJeuWJmXyblIwj7/sKEY1nb1Z30Wn9lhkjRpjmerau/3ixeO2MIsaT1dQ9rLMZG5WVrWyS679x1S7O1pxPZcuoLBoRyPXzwgmakqAX/ZmJCeTnqldJeqnYF0CuI2sllrhsvG8yh4FYirzBcFTh/jI3W4jTD3C8vthufaAN/hgOirvHFtRwP0OiJ2/bq+ffR3rL0go5LoYVGNAPLinb0gI1zS6MWy2YiQhnHFShQC9E2VG1fWsH1UgHavPW23bTNGb9q0xOZd6eZ+g3+pTyYf9Ab93tPeSCgtnBZ+26a3Tlhetl8P4aOWA6LnTwnGnfaJMdMnqy5yfFmFxRycH85Izvh9ixHCthPjSU0U24/f7I6bj30NbnyTeCLNWaxGuHZsh7Jwnslkcv3Bg426cMjy4vRLihRXclEZRE0AVbbT79mXyXtyCa1LbCKPHzN6gYljyETZ/X9MWKMsgU4rdwxHTuZ/JTStTFJO9iqKsHLuYnal4SyQBmpZ5kvu3VXEagpe3voVLwNEl3lZ6pWMyrzGrqgi/jGnOdEWoypovVaHpOWXDhXG1mtk1PLt7vBWkMjd1KHdhMeHj3gUDB9q+70Y40nwU//yFI2hJ6aji1LQszsNV+wt8exGI0fYCWxL8OkE7aGstvac4xsVoq7W5W80bmhV/WhKu0HiYmmxWj7R490RHpvIYIRxoRJJguE8uLNu7k+V3VCUWKV+7Vke3nLcOofzBNJnCvEZd3c6OxESun5NzzHSERMKuAR4flZ7v6ctZZFUhYfSE0QkUtWcNaQFn7RWgG4LqcJJ8rs9qyUuYIPiRP3J6Co4ZrwuIXPa9JpSaJUtpdUNBQC7SWAQ5Hi5YrwrCsCVGbj5bm1GE8j8Z5pVsMzYjU5v4OXAve+7KZC2L9iD1/vOLCxacuttrm2gRm6yxQC4Pi7nlJyqf6vqF3VXukLdge51QpDn9U+XA4BWAVbe/PooqSiDhDw4NXzt75ZykFEPxPgpfQwkIKJ5/j+3YJ/aXeNTcwsLf8o3zu+hT2cxLF5C9uiBgxbWu6KBbyfO3FoJ6CnxpW43/IFYCbqERcXwGlD5WbfrCSOMGC844yM4navNcLUVyN9jN65L/MfIMj9WZa+z3FARlBXA0mqLxHOT5n+Nrpn9e1CcyCVYKx/eL5RNiW0KY1L/GzUPLicQCIdadynzyTF5MjS/K1YL1tXyu/GvNmRZnX6fmvH4tsKAqdO1ADMXnT6cOWsJQahWyFV0z1icNNq/F5vjOqumYD4RwzFHOHsE+fW7Z9dYlwADF0HVldAVmywzc4cry30PbuzEtcP5N+OdA5xTKcfp2B2jIpeO1OBl0vvndWo948vrFcCg9N5eSE498d7N7o1vDt+c3ehehwUS3gmfGIZCFbW/TpSL31dKIf5vFmrzseyTboTumgkTro0IwfxWyegM2Vk75HsKQzmcrEHg1bsHKzDj3E36s+LxoEjAJYF8fHF8EQm9a4IjD5/Dsuvo7Q4xedBiUfYsB7sBoTJpD5vtOoYdQz+1AE3J1v1XIVTlN8Uy4j+od8GHvtiOomrDiSb/wiyeQ2flMcRDczIpAAQU67CGyQOhYE5zN0aDQD1Yu9LOYNZtOMMI89/EcaCwdsl9qWKuLuhB7xrq90JLXDYfK2Yq1LLdxHWEu5TrVBsSbekuzvABJkV6+/WadamGF1NFVixdRA6GcIJPn2ZYFKezLTovPyDTVEgelV5YDZXNuZ2bbcU8pnBy+GYMDybLxAADCkzJ5WrkJG1S1JgjHAFkh+vgdl+o231Ulsff+5lW+Y9VQKIZLNgXUVvTecMmvznEnlvcuoPmnl9gtGXBKunZWZCTQx83J8ZYUTypWdURzE8XRWU5zUnvzA/I8Tmm7jNzDBDnLatdHGKgyRhteTSOAed/f6Qc9V25JB3oHiXVON62b66vXOgNxmJzWnkPsZVq7vkCrAA7C/UkwVObjNg2zwXcauzbPH3JwsrEGlRs0e8TEyIMr3NlGT7wkZd0d7Qt4ga8si3pgK5Yq2Wg5R0CfycF/31J0yu/T/9PbFCDpKTvvEYEV+BrOZpHaptadwVUJFZ7EJZFL7feN9S1pN6AVmHfwIcQfSl3oUfk76kVBL2nP6lBuc4EeH6yKsX001Irxgvk4h1LWtDsk3Ey2c5EkTaL47KDOcb3e00CYfC8iZfDOho4279a1JA6byfEAmzao15up2AmNF88A0UlsxGDLC1FUtr60TMlk8aZx1b6/8zxM48Td2rQ209K3K516UQJbAvPLKSjTeo3vO1rR3zeg5jj4P+R96EqwSWPY5NUwNKWo6+KfMlc/72xaGL/h84pzczTGk16vnRvFikq+KnIHOav5cuiPnA19hxMMo3nHcnJKwXRDzZRe226EjmvRr/eFth63mQ4R/KgvGWfBznOjXvYx5lnzYvdhTLQ9Bt7hY4Hv+es+kqjsRi/FOujsiHXP7H/FDiT6uee4EDiWRIRAn4DohAPyKjzOm+RPq5F2Sgd6rJZwbz+OU+/kf/tSFYMeyvxjKA9Y1RBecmuqxvVDIBmPzlZrdue9AC9rscPonpzwk8AWLtEwd+zTGuqM/Zi37ccI2LuWzM9oDhXp8uYTTTNX7sKSgTlVDzT19LhUYAXTuoL4OOiFYN9Ewu9wo6wKqCIQtOFRk1RiKrb08IPiO9Z0GVVFBVKcWVIiVph5fbu0ZE6AV7aKLnyiMyg+S6kCXfJWvkxGr8bIE5NWmiV99eVj1rv4qR2jLkGMN8eyqmeSIEHXvJjImkBnLM6SZETnGF+mBYhZvX+8AmZg56n8GmUltmdiuYk9n9V6rxgcOUVE6Cs6Gj70+OkHr1fvvZjsagyiMghm0uj0P0j5XuwQKt5j1IsnA1oLvSCcG2uJ5ishkul9FPnUTPMy3vCbgaud4PZa3r2BHmj6qdY3rmnM2schCFc6nPswvDxeXzkiOcg44eCQ05gfTW0oQ6AnlsT1/+Km0+euhcufQvlxyKgQUI5GRwxLsMubXTEIf0zfxL0WxY/UrJRUxZucnT7ZdtAN5ySa3y4gJLXzP6NV/HVHoea9ybI8bgLeZzWp9nWC42W5iMpAyJtBnMD4hxvKqQFiSwNQ6Gh63fGwtrn0vKVE8Xhiaip23wn4ax9xOs7X0jMUa20WqHE1kOLQBpniyzkNfSy/ruABEUKqzMn4QzFgD9wjfUg6ERqT9IXYazhSMlC742oQ5mh8MUuNDHzv6e/9iDsWXFR7+mmL3Hy1ICoXKkVnxD1k36LkybaT2tNZNaMUeeTkTu55OENFDYRcNCQqFJILB9svD6iFKMeMXOktqGAvAIIykyUyLrVo/iDKJK38prQqQn1kPUWNiIFLmeQMEyMY1e+XGepbngHNiDMZRqpsCYj+tetJKgpp22IpNvOCqg49DdG0Q0hmuuFk2H+8kGafFBMTcwZjN7tut762blvIyg35o/cC06N6SbS+hl293p8VBygBLjbP7In69q/QwY8pzKsk6N15qWwA/voFyFLDt3CznBpgwBbc35bwLuCXK02QBTvFKSClQhvNfVU5fJiF3vMSuur0VkNjfnqc+xSy7F0ifVU/0EY5j8FUr2QSKXOK7wS/cP3MpIHLLbjNpIifJ2TUhUNrkYB33MplVEe7A6RKjf1pZ0l7gw7deJ939jO+KlCjzb8ujspDk97GQUb49h46WH0++qNVxxXT+bttTTfs113hn8+nC1BfV3xxta55utvu3o7ymKuuLVfN2O0zKlqXVHFtpDbuk8W7woMtUAzbhdXoLAbECh5XXfGOcyqu3A8jvXZAsNL17I274thwKICwH7+mQ8i0PYusP//h6e6GPnGhdBUDSZHnsLwAsk9+yv4GBcfL/doIIix1PPV5DYPKWMnfb6gELz1gyynb+nctLyM2mfLChZofZ393cnmr7ayJuhOILlL0kHo11P0rbtk8dTJ5OGcVCL9mIhQ0tHLmxbRCOuOV3laeYHBziR0U8HxgbnhhOlC/qL7JQ/Cm4cU2RC9+/yJzyFf3szgjJ5CdmtUomGOWp2tVXqJRnaMVnWg9tQ46K+7kwZvsfibYB+rGPw6IRUYS3J/YRwo/eLvD7Zd7L4Sp0sWwFXQhefag9DwRMEQ9homUFfYwmPhWFHItEpHpolqkPihgfbWThF9Mo7KcTVotXbS+8Kluot62B8dLsIZgFSuqAhyhAbuYYd2k0JdKbEQjQC0/XtHpjOHyV9Q1Pb/iweRILs5+EUilNIAIhJiMRud7fkkncD14A4nrYrFEXyL5LnqP9joOdWLNzNv3A7j39KeSSIqYzLy9GMDzPVprXc9hXveaw3TeTk0ejOw4Q2AR2nZKpt8HHpxhzQ1uEcJwDkmG5/AcV1CP4SWlZzmINgUzWKCSTmJVAn2sU7YY8B88RvrBNZST5T6UhTIL5LtVADovoWTgIboQVYF/sKomuz93h45mtKF0T5KRXD/+W5RYPOzRbjN/3D5xN7g/3kUSJFMVAyvqoUl/YpowrAGBlKB1+HMpYa793c6gFmAHk5BX8oLUBBSMtSIhwbTHCo5YT3ZsTGduv6PWIZOi2DvVtHFewhgE54llOpGjLJUGpRoyMslDIunyhaO2CJcvea2eGjjP8dVKGJhr/IdEjaPK6HTQPm8yMzXYCkooeHmuTk9ajpPyEwtyrnhht0TH9I7pNI49Gg1bJgMoReS9724sVNngVA42yetYkCfPkYkrvpNIzDdZmv1YaCCDQXQeuYrLExXKaFwHnzIl+XvmFWOY2XmWJrRmpkB7f/U/aai52tYVX1uqnT1J5QFi7jbNPhoQBkyoNohQkorTBEVB1YCWFU9NfM0S45UqiQWI4EJgBC5mtE/mewnTgjwp9qTDNHN0j4ogDyw2xqTBryTH2OPho7pFSOYDDRnhKOSxFIGzY+o53ZINwLfJve+KwSTMlqzwZmSMQV607GAAd/UlbIM/qgGhEo/bbxYRs9594id5r2y32SX6AeIspBT8B0erv4BHt9h2lZjDiaZwMgXtlKnkEhlA6FRTLu/pGLINsgJcgrfqnrBxTqhP/+negjl5sdcUUQaak04kwsQ6L18V/CLUaYnBz62l/0MuhzeoMxxapYuqaUyicpcYAMVU4x1zS7pbfXZx3u6un+HVUMDMtyoQMTLmJFc0f+zid39TPyqycUtcaHykqsO77Js78ow4TdohHsvH+f2CBOi5hiMmzh99gu0B/VruOi1g4MaLjyHlWqho0zpT6H+rSs8dZH2ZAxTCMcCZKv3eIWCUtTki7QZ93lg1XAi7NFXsNcopIsmD2QFpxhPM9A0ol5WCqQKvoQje59lSMCDURcyDQyN8AC/bbmRMkZ8VPzl5Pq9BxvxBVm7PEI69P2G1slUYo6AhWsXMz6XdOKSxMRMWYTkb5mOZGXwRKAhuviWUr3oDT7Ewmg3oFEy/xwj3gTy2uF+2qN3uG5C08MdpimLlNRBETIxFqfItESdaBAGxorHoWpIp/EzRUToQx65FNp7HVrpnTXCcngncpNNdONx3m+lc8P4yxL/Eo+KvhYTls3H/uAckKD+wbNhGn9cql+GiSf93HyHD1qbYOk5EF8WtjUh3CnTLcqev42wSR2y54V2qPQCNgF9n2UIt70OAkTQzesCMTYnuJaJx6YhAIgzIvOLBN7LeXdGq9kT6ABvrwybUpYovimgQtRw3zRGZmb0HR7903clZjvf9vBhf+7/2GYTRhRlhtfra6wCC1RgFLTGsWjglGn0trGJvAqfivsf0PnW9qk+NTwWeraxyQF7XFOLwSRcNORNYUnVygp0tVIvv0AbdelPgC0F3tXc6p1YsuemWcRznP+NgGHBwnm8+fn0v/H6mqK8E/AH544YoWnPbq4Vhp0YHIdaW9t7Zv3cp8s8k+IcTQ8V2A94GFO4VRoLFwQ7tQzB3LIyvdP0QCaFHetWuIMq9yf+ArZfAiVNoslonQ54rakGltUNgktF/uvUicQqxxLOnOI99klZiuZy21EAEgwQ0fsI9/b5LTtknlOx4ePPMx0O16qkxDn4ER6QUZEx3JYthRmAakXylUiPvFzsFpnKfB626hy2R8B+s5LmTA=
*/