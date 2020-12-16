/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DYNAMIC_INTERVAL_TRAITS_HPP_JOFA_100926
#define BOOST_ICL_DYNAMIC_INTERVAL_TRAITS_HPP_JOFA_100926

namespace boost{ namespace icl
{

class interval_bounds;
template<class DomainT> class bounded_value;


//------------------------------------------------------------------------------
//- Adapter class
//------------------------------------------------------------------------------
template<class Type>
struct dynamic_interval_traits
{
    typedef typename Type::domain_type    domain_type;
    typedef typename Type::domain_compare domain_compare;

    static Type construct(const domain_type& lo, const domain_type& up, interval_bounds bounds);
    static Type construct_bounded(const bounded_value<domain_type>& lo, 
                                  const bounded_value<domain_type>& up);
};


}} // namespace boost icl

#endif



/* dynamic_interval_traits.hpp
skQCcbIihW3HpmYOCIsM7MaNCe3NcaAW4KI9L/bHXsrD3DyRw9/df7nYtS+PmyBUyBUyJ37V2oyeJ9FNyE2S/oPzoJ3lin9wHqVqJcykR4bKE181mGCwwdAAg7dqMFH9MlNXnpjVRZDACufJWP5SGX6zWV2VYgwilr8ymRUjkLIi+QpWhCSDFSTgV2XbkwViRbr21tu5uCfaubj91dBbVc4ODo8l9eRsO7dENlXkpfnHzqk1shPt5BXLC+AlshXCdAE7gydSCqrcpkK3xH/42AnFOHBVdkXPk56A00pn/0WJrHShWC4cJPClptN5WZrxVvYObdo6Ojl7+Xaq6vIlCakCvvZmRcSFhVG/PqERPfzDQoP8qrYcuTBZrLNz+ob6rH/lvyxybtqrlmbGMjM0M2TlWrOsWWadzdiYriyxauI/6l8zap5/ImGdhmSF//T8JGH7XVzd2rl7tO/g2dE/IDCI04XKLddK9ISenh49lBuW67P+ldS3p52LpyieHo+DEvU4NeDcj6d+MdGiisdTIRNkaR9QLwzNVQGMMfXbhs1qi9821PfJyPRmI8+XzfJV1a9Njh8d7FRXHcY6VMswBlNVvRytemaV5NWtZHn1Kslz0ZrXTLUOV1VeOVJ9Vb32leR10MpTL49P8ugFqvMSK8kTVJIn1Gxfxf4u0joPWEZ03sZK5t2kVU8971i9iu1T71s+MpjLO0vXI/+o6+03+Ou2f2VA1zPRClZfq/Jqa+W9UeXVUuX9a2dq1VK4f0w36pwTS8glkORJ04RZ1K9SkeQpEYuyybEQJPGUIkVVr3dYlFiYqHViV6P+OaS7bjOqbVLMNZr9YyJcubGh4ZyqrQO3E91nIdeOLJabS9XuuVW931ZhO5QKPvPe6fbHe+cf75nkflnldWYIZMKk7H/ovpguUKRwRcIE3XsjDzdY0u6RAV05gbGqPCGdFxoRywnmROvkxcRGh0YE0/WkWF0iV5Al1Tp+AaGxqjpcuUBBPbCRMmobuPwErfEUAT+Nq8DDolaeRCTCbVIzjSc3LJ0rlQnThQo8w2qfJ/RTHUunrkzAS8QaJTr1yJOcVj0Jl5eYoDMtkvDTNPXxFKcpw7r5bsKKuklC7C52WV03mBPBicbduzcniDptseBUnXMZT1UCGU8h4Ga0Uy8DeQrqCaW9u049heoJgaVTT0kqaurhaYjsns402qBiWiFIVzUMI4/sFFkumRakJwgSqZrI/et8sSCTsUzNiivJZ65LyqNaUyePPLZUlsflK7KY+UoxtQTdPPp01+SRS5VQnMwV8yVSZCNpncNk+zX7hUBIqlRwE3kKnqZeVGBsvKoWfU7rTpNNU8+PNbkpsqUCzTRZs+5hrKRMyTzGFSb+Ki/WPyCMOnkSK1mWQsJNoLaFOQ+1SWSTtedBU0lFON9w4qoPLrOMzFR5vgSQyWyadalPas10ryiOas9xwvIVAgW9ldQMjDp/LI+LDVQvVp2nObxICe3dacbUxlFxA6YzZTgJyNVHFUuERlJ7wY1QPe/RQSGuLtS4mGoyrRZUX/OhgnF90uQzr3XIY14TSZ4wQZmkHqePL9UQ9PLpS1fFeZbIWIZOXpxmZRX5SoUkSibMwJHoJsiuyK80T5kgEvLpLFy+FHyZAFVUz0Lq6zm4ogVQkq7JD4rx50bFBXTj9KqoywnUZJFp5vpInmZ99HQ0YzkiCU5U1YVSIkzkpksSlSIB2kZ17UeMLxdwFbzkZPp4RHULjPHgShMEbuQWIcygF8PMl5PbF7OMKmJOu3B5omSJjMWom5aYRJbEIs80fLmHapHqvJhwnIjkbKNPLk0eUGSpVixXJIiYO0Qd+3ZuZI9Jos+Fiuk=
*/