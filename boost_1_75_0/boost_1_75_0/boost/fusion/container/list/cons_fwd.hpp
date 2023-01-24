/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONS_FWD_HPP_INCLUDED)
#define BOOST_FUSION_CONS_FWD_HPP_INCLUDED

namespace boost { namespace fusion
{
    struct nil_;
    #ifndef nil
    typedef nil_ nil;
    #endif

    template <typename Car, typename Cdr = nil_>
    struct cons;
}}

#endif


/* cons_fwd.hpp
+uVr/P46Qe7LBV9l+BAuuwlDeZ6tz/N+ffk6r3PTDN734Q7xVNZ1grH28zltq4R1ults3wL2SeaWKnGNsNa2XNDT0e9xfm6yl8XtzVQWez/iZWtYnAUvtloLd/JYeFsJj4VzS6j/P3qSPZ9LqM0pGcppWDqEpycImJw8i7ebIOCZp5F/ksTzp47gedYwzKdYD63n+YOFudnSV+x4G/4gj1+iCQaSrZuEmChG0Nn+QgzbwvcOo3+Gmctu9Ls8j1zA6bn1A6fZNEmxjaHWDWeUsTXZ2pmt44RYTYO5DU+YyesfOJPT1n06zz/eyNv1EuyYRrAhs1+ws8PeG/CcNo7j1p5Q/AFhLD6dwdOLhPXipcx+4rJj4y6zNf3Clh7Utgu0Lc+x4/lju2lbi+byPFUsTsQYprocae0v+Hh9hfWscobPaOuhlzifq7Zxea2byHl+hNGfYb013Y4PO4vo/MkaIf49IYw7K5I4H9YIen1rGKdnajKnZ/nz/H6nUXZ9n1hMdbPt6zyPRuC5SVhnHz2ZpzXCGn3wZDv61d9SnY0QYsBLAv18/0y0VTPVjp4Uhc9ewnrNXoG21Lk8vWKxUhb7kF1KuD+ZUkJleuSo4h9GWiM+5LwqWcHrXyWkA4Q13CPCeqIsrKEvZmMutjPhX1EfLEBYc0wVYszM8Up+CfuxxWRdD8fdxdzmxxYpPg+TY7h1BsNSrHWVsHY2/2Ve
*/