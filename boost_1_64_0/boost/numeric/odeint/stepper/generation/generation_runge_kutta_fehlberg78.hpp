/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_fehlberg78.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Runge-Kutta-Fehlberg 78 method.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_fehlberg78.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_fehlberg78< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_fehlberg78< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};





} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED

/* generation_runge_kutta_fehlberg78.hpp
cWtKMusiFQ7U9sR9Clkv2X/WK76G7eGj2HBcMGs2Rr509DflxqoQWbWAbk0HtJKEJqu1hZKSA/ovlVTYt1JhG2TYnnTYPcZBLiSrIgT9wAxavTINdYOA+kepoIVpENakPKdycjVyuTnlO5aZc7f8gpTXUPltFLuCvmLT65MTgCLXhgM0SQSWE4PVl9Kju4njyy0Sx8mAriAjFkOmj6UD47dyDdNq0OKJEQL1/0paDOpdFk6G2UmrxfgAdXio6ssgnbis1ocRwZyRuYc4PQfsO2U92xxgQd54447E2l7paUCcEM/Y6Ux2IBPzG35/yVQoz8M9bzhMa4QpajVYsVKrWA9JZpoHloqx0QnOXDg8koCSWw4z6WxB/tzvfKGaTK3Y1tP1BTms3HzKrDnz0maqJIq5sXouVeWbI1Y/IfXijNVPtQrSd+hfQ1JjAXOHY6GRQ01ALHl2IYzsQrygWP84kBuMF9hsh/TkIOyz85j4r9GvZhZtVPPsBoSXphvGBG/PSat5ytpCkT9wUDMrGHuAaIA7FhWc9Ke7WE+ntrdzXerIs5mAuLX+ObzRB5wN/2PsldCzjI3c4SkM90YOrXWMwktbJ6LUMUpkpcfeIxgQaDsW/1OPiOX+fIMnmaf57euB/6hV6sgnKVI/Pskah+naVbZY1XWCJFqrlljOyv/WDhAN92PJvZ4exfzem1bhKPGdIbz9nhNWS+b7TT3eF/Z4/+7J7u+Te4Tf0yP8/QjvAY86MQ9U8XatHQuGQrb19Uhzlp0apFaYB4dGR7rGhfAt9ZnhMlkl0G10NBJDMpb2mKOkPaJtbHrSt88Bv+fOfAkGS48MSSalkKew7FCQO4eNg/awfzA8WGtkVp0Vbg4P4T5kJ7j7gKrnhJP/fKOvPKdk1AVJjKVH0C8w240uS86l4YjuOm41J4bbkTNYCxt8OIQ5Mk83DHu0Pt6ZBa4NlGV4Zxa67nlE7koerw14xpJkDymqP0b61/a4Kp+fSJercqe3bc0arbqYIXx/OeW/d9VNHY3FwFMhJVHRx+CSn58MZUd2F0baKrTFTi3opilAZ0ubAv9eka1CLBMatfbVUN7avaEcQYVi3//P7aErAAs/8A/l7xBT8vI+sdEY9p+UNVSTO9ILj7G6dm+XK84pjidMtzsgEEHq/UEhFhmAGJrODN5duS2IuXBFuWq1KNTzioy5nvk6zuMo68Dk7QiNBvx1TQtshKyQ5cFUesNckdMPj1rlwogNJwRG0v/L8IcvJy8seFrw1Fro+uf19j9/keaAyyc9Yj+5+uZRGzoF6VqvAn7oNSTdWfz0/32n9B+a9l8gBBDzGLrjqAwtTIeq9N/KVJy9PHzrw7z5dp0Nbxa8gbEYLEDAsUXqxenEUxmh3ihyVAYo9L8Z/uoSuNB6y1VdHWBDPsv6YUIoT8XcvF0RJmiMP76TDVLe2kg/Xrsaf/R3XtpzvKgJRLafLOsIRrpWudZxkw9k6UUOhbL0hhzFzelwMRYm2qYuUuYuSOe7e7XW8d9yeuDvT/MqNV85IQ9TF5rVrp2sviynu0MdYroTe/Ra/HqAwwL3AQnxwIdS8X2JFwK1wN6CLqAaHQgx/GqOxQ7JRM0FRncIj1JvMhOo64E4s4wVHWzA8V2CJcGsTZDWtcmVkj6cOfJNCDuX2rcKNkPArS5LlT+p/Wr0G9YLqTPHTqfo/WYVc9U6JGnPF0LZXFGgXYhe16ZyWtWuiNBfdopQroa5EDsOJlR+cNLPQwri9Q8LI7X6R/jQ5/ZlHd2EfDy6rmstLRzJIKn3pShpC/e/6X/4vdUi7WWcMeEj6sNPtuzGE9z+fMXk8Z8NXV5/lDzSirHqw2Y2s/UjwBY=
*/