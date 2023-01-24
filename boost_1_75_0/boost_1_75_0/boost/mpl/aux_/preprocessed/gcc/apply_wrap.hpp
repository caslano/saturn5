
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
3/u0n/0N//et6eXlrqEGj6Oy8ltEVYjUHMrqwPRiMsspyYHgfhzs23Pqs3PyM+7PM72Ax6XwlMXBQ3HQCuLhcBgppyvLL5wJLrZor604QbxGAbmp6bgRvbp9F4kkrE210P6YLzQK1HyQweXqno/2va93+FlWqP3HM62bzrOoA5XSvkBZaq6Cb1JUdX1ePEMMBBEoP6ULk3L1+mfMAFJehdofKOomjSU/eoDQ0/max5cqYMYCRUloHf39+FkbWK37ba/dsgIAwGuXJZ3JaBON4TmUpJG/AhpyWZZaQIE5JdOkV7OFM5ehC8dJU6suPFX9LWIdvKfGPNRJNiY4/UARISND36b/xndvsCxOHzB94/+DokNe2Q1CxzdydCHq6ipjMU8lapWTQGnJ47qw8M1hOzOUg84p05+DR8px+bc93k1wSGn0t0RF8+9LVMmI2BDktnxlfhcdykoN/kKy/uunFdtGfL7vAdEWa3lPIbVryIJj5NAwp+1NQDb/ScEP5RPB4Peccc5znDblqudLEZ7rRTT2s++pk8O4CKfFcqv1Jb8FF3N9yr6ZBOWieUb84YZr0kIfV6Y5wxUAGdGmLQDpfxXCsUv/zqImpKM4U6x/y6blWhxGoMDpRr/ZFl0+XYF5o1WweJGbm5IX/ADWfauPrI+g74fYMZn8uJ40Ned+wLOWiq43kXQqXZYkj37BbVQe2IQeb1pcYMBpRwVU
*/