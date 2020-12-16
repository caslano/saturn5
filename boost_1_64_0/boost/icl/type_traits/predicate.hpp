/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_PREDICATE_HPP_JOFA_101102
#define BOOST_ICL_TYPE_TRAITS_PREDICATE_HPP_JOFA_101102

namespace boost{namespace icl
{
    // naming convention
    // predicate: n-ary predicate
    // property:  unary predicate
    // relation:  binary predicate

    // Unary predicates

    template <class Type>
    class property
    {
    public:
        typedef Type argument_type;
        typedef bool result_type;
    };

    template <class Type>
    class member_property : public property<Type>
    {
    public:
        member_property( bool(Type::* pred)()const ): property<Type>(), m_pred(pred){}
        bool operator()(const Type& x)const { return (x.*m_pred)(); }
    private:
        bool(Type::* m_pred)()const;
    } ;

    // Binary predicates: relations

    template <class LeftT, class RightT>
    class relation
    {
    public:
        typedef LeftT first_argument_type;
        typedef RightT second_argument_type;
        typedef bool result_type;
    };


}} // namespace icl boost

#endif


/* predicate.hpp
HtgrhZsw0ZlthjV8Ys1P18UMx1THJrqxGZlXmJXmEjIsUubBZRFC8nC4YIiSZPgrcI2tfztD9qz9hd8zCJ/gfJs9rl5G+W4b5SqXc4WHlV0LkWAzPea4FGPXfD0qcWYbbkQjTnSLtT5E6TDiHJ6grP9N4CJHcPafJxUBR8Q048M9NN17r2BlAIt8hHexTi6lUw6UJmQJy3p2c3whMwl6GFVWTJ+J+ZC0djy63Mqr1aDL8yFHRaJ9V77YV+MxxEwaV1jXR1ZKuCZiTWQ1cLz/xnvmj0r+mom9l20CF2tPSJN8F+w+0MuE+6khR5aTB26CfLwFP/FMbXJs4Ro3MdL8Zr8jh7OvbGs/eL0Ujvf2zzdkwmjAVlQeFUY5r/Uk2j+Zacipg4CZK8R9pIFEewf8KLndAcuBp++PwPs8vFNZZeN9Od6pbMrxfj/eW9CeA95X4KfLL8CN+B1Jj+ygyOdSeR8DYWjN63Kpnr8L6HoVR+WHvQGjnq+U+GG/iI/rdN75Yr2M5W7Fv19G1ufBeCPdrxk2QtA+80Pi2Lyg4Xg+Tqjm58VGtyGMJ0im8Hua04BaqALS0KOxpQt/0DgBijhi4fjsO93bibvmpLjFXooYQ9I4Ki1UQdb4/ZqPx9QyitxWH85SHIA1BniOtHKaLpHsFvdvIFbhxBhM0wxfeaWOPNCEZFbHZ5mhgB4iH4eZMZ/BLJKuo/BGPLMNz2HGy2hKh5JOp5JOUUZcvrEjyboiSinkH72wO+Ij5d8qn8DRY5aZ0HLBQxYawlRxFnqDxm+RgLKGISXFJieD1zdkoyAjXDn5hVNHJXA9O526n7GIwqEvEoIiwhWIqAReRCH6CQR16J2LVBEsxJkOPlCpTM8SLOdAuep4PYAbjOkoEKVujStmVCd+lDYRisMgWjY7Y/jhvflt02rLyKuHxpeb+5Q510TzzKX4Jq1gOsaCYygfDahDHxa4rHV4EfchmXXL8NH3tbWPvtc6hw43OrZwcj/7U0iMX0U/ezfcNgv96PJPV5tLd6XT1kHRRLczw9UQnsbAYWZlnbpdjoiRvuWK3p2sM5sZVtZKEUbeOxkKd7OTrX1BpsBxHEuVOApBXyzPC+BORj+xWIojGqE5hIFrLHALJVwTgVsOXGIO8kBu8VsdId0gw18zXoumvE4ycM0FbqcUXwuB+yJCe0EGriWvQYty4jzsQ35OkPJj16x78w6N+j2z3lfPstZzsnb0em/oQ+uAfBNgXmGmq4Ako5ChTs28QzYsbcC40rEbXlA4VXjF+F/eFSB3pLRkaGqqQMDtzXUbDrxXY1fF3JIBja0dSOF98o6PwFUG/XQYtkCc+7IM19mPn3fuOR2xHRLWVcpw5boKnNmiA4DbuMeGPqSpdDfxpIib6lstuzbQzMrrE7+dZx1juHHHGG78MYbLPsZwOccYLvcYw/0nzzbU96mfLMUsU5KkDwvZcOdpdfcP9kfa2u2PWfuHqxodWzj5WVtVW1/6/irrWNtWZZW5G+BWZdTv0hwwHXRLH13VcBnFFyoFhCY94ZxpaXQlc7rLnVaQlV8I/W91T5zWE4oMbw2rDygnWru2KQLyHqL8jDxCeS89xnBfND5KuCfbNrgMG8aT1vuVbhLpCZ5sO7Ke3ea29vDW+GnrVX6y0Hsweat7Da11iT5e8FOywDG/Ta+26kKMAP1KeZ8C7sS2Vh2LcoHjOB6ttvLsnJqG8aA43qu/i+O9lr7CPXFMYYHLZT1f7DbODmvKmWIZTX2IssVhhpfC1L/egrX2PPKl+FxSfFn5w2Udtf6qcsENosCSBh597di+r639AH4qHuN641iwcVA+LXYUWbKziNZG9qF8Nnl9zJGNSWY=
*/